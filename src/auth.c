#include "auth.h"
#include "platform_depended.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

static struct user *admin;
int registered_users_count = 0;

static struct user *userlist_head = NULL, *userlist_tail = NULL;

struct user *load_users(void)
{
    struct user *result = NULL;
    struct user list_buff[MAX_USER_NUM] = {0}, reference_struct = {0};
    load_buff_from_volatile_mem((void *)list_buff, sizeof(struct user) * MAX_USER_NUM);
    struct user *ptr = list_buff, *tmp = result;
    for (size_t i = 0; i < MAX_USER_NUM; i++)
    {
        if (!memcmp(ptr, &reference_struct, sizeof(struct user)))
        {
            // if we are here, data in ptr are zero
            break;
        }
        tmp = (struct user *)malloc(sizeof(struct user));
        if (tmp == NULL)
        {
            break;
        }
        // tmp->username = strdup(ptr->username);
        // tmp->password = strdup(ptr->password);
        memcpy(tmp, ptr, sizeof(struct user));
        tmp->next_user = NULL;
        tmp = tmp->next_user;
    }
    return result;
}

int save_users(const struct user *head)
{
    int result = AUTH_RESULT_OK;
    struct user list_buff[MAX_USER_NUM] = {0};
    struct user *ptr = userlist_head;
    for (size_t i = 0; i < MAX_USER_NUM; i++)
    {
        if (ptr != NULL)
        {
            // fill array
            memcpy(&list_buff[i], ptr, sizeof(struct user));
            ptr = ptr->next_user;
        }
        else
        {
            // we go to the end of list
            break;
        }
    }
    save_buff_to_volatile_mem((void *)list_buff, sizeof(struct user) * MAX_USER_NUM);
    return result;
}

static struct user *allocate_default_users(void)
{
    struct user *result = (struct user *)malloc(sizeof(struct user));
    if (result != NULL)
    {
        // result->username = strdup(ADMIN_USERNAME);
        // result->password = strdup(ADMIN_PASSWORD);
        strcpy(result->username, ADMIN_USERNAME);
        strcpy(result->password, ADMIN_PASSWORD);
        result->next_user = (struct user *)malloc(sizeof(struct user));
        if (result->next_user != NULL)
        {
            // result->next_user->username = strdup(DEF_USER_USERNAME);
            // result->next_user->password = strdup(DEF_USER_PASSWORD);
            strcpy(result->next_user->username, DEF_USER_USERNAME);
            strcpy(result->next_user->password, DEF_USER_PASSWORD);
            result->next_user->next_user = NULL;
        }
    }

    return result;
}

int init_user_list(void)
{
    int result = AUTH_RESULT_OK;
    userlist_head = load_users();
    if (userlist_head == NULL)
    {
        if ((userlist_head = allocate_default_users()) == NULL)
        {
            return AUTH_RESULT_MALLOC_FAILED;
        }
    }

    userlist_tail = userlist_head;
    // find tail
    while (userlist_tail->next_user != NULL)
    {
        userlist_tail = userlist_tail->next_user;
        registered_users_count++;
    }
    // if we do not have admin in user list
    if ((admin = find_user_in_list(ADMIN_USERNAME)) == NULL)
    {
        register_user(ADMIN_USERNAME, ADMIN_PASSWORD);
        registered_users_count++;
    }
    // stack_sort_list(&userlist_head);
    return result;
}

struct user *find_user_in_list(char *username)
{
    struct user *result = NULL;
    struct user *ptr = userlist_head;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->username, username))
        {
            result = ptr;
            break;
        }
        else
        {
            ptr = ptr->next_user;
        }
    }
    return result;
}

bool validate_password(struct user *userptr, char *password)
{
    bool result = false;
#if !defined(AUTH_PASSWORD_ENCRYPTION)
    result = !strcmp(userptr->password, password);
#else
#endif // AUTH_PASSWORD_NO_ENCRYPTION
    return result;
}

int validate_user_password(char *username, char *password)
{
    int result = AUTH_RESULT_OK;
    struct user *ptr = find_user_in_list(username);
    if (ptr != NULL)
    {
        result = (validate_password(ptr, password) ? AUTH_RESULT_OK : AUTH_RESULT_OPERATION_NOT_PERMITED);
    }
    else
    {
        result = AUTH_RESULT_USER_NOT_FOUND;
    }
    return result;
}

int change_user_pass_by_handle(struct user *huser, char *new_pass)
{
    int result = (huser != admin)
                     ? AUTH_RESULT_OK
                     : AUTH_RESULT_OPERATION_NOT_PERMITED;
    if (result == AUTH_RESULT_OK)
    {
        // free(huser->password);
        // huser->password = strdup(new_pass);
        strcpy(huser->password, new_pass);
        // if (huser->password == NULL)
        // {
        //     result = AUTH_RESULT_MALLOC_FAILED;
        // }
    }
    return result;
}

int change_user_pass_by_username(char *username, char *new_pass)
{
    int result = (strcmp(username, admin->username)) ? AUTH_RESULT_OK : AUTH_RESULT_OPERATION_NOT_PERMITED;
    if (result == AUTH_RESULT_OK)
    {
        struct user *huser = find_user_in_list(username);
        // free(huser->password);
        // huser->password = strdup(new_pass);
        // if (huser->password == NULL)
        // {
        //     result = AUTH_RESULT_MALLOC_FAILED;
        // }
        strcpy(huser->password, new_pass);
    }
    return result;
}

int change_admin_pass(char *new_pass, char *confirmation)
{
    int result = AUTH_RESULT_OK;
    result = (validate_password(admin, confirmation) ? AUTH_RESULT_OK : AUTH_RESULT_PASS_VALIDATION_FAILED);
    if (result == AUTH_RESULT_OK)
    {
        // free(admin->password);
        // admin->password = strdup(new_pass);
        // if (admin->password == NULL)
        // {
        //     result = AUTH_RESULT_MALLOC_FAILED;
        // }
        strcpy(admin->password, new_pass);
    }
    return result;
}

int register_user(char *username, char *password)
{
    int result = AUTH_RESULT_OK;

    if ((registered_users_count + 1) >= MAX_USER_NUM)
    {
        return AUTH_RESULT_USER_LIMIT_EXECEED;
    }
    if (find_user_in_list(username) != NULL)
    {
        return AUTH_RESULT_USER_ALREADY_EXIST;
    }
    
    struct user *ptr = userlist_tail;
    while (ptr->next_user != NULL)
    {
        ptr = ptr->next_user;
    }
    if (!strcmp(username, ADMIN_USERNAME) && (admin != NULL))
    {
        // we cant register admin twice
        return AUTH_RESULT_OPERATION_NOT_PERMITED;
    }
    else
    {
        ptr->next_user = (struct user *)malloc(sizeof(struct user));
    }
    if (ptr->next_user == NULL)
    {
        return AUTH_RESULT_MALLOC_FAILED;
    }
    else
    {
        if (!strcmp(username, ADMIN_USERNAME))
        {
            // change pointer to admin
            admin = ptr->next_user;
        }
    }

    // ptr->next_user->username = strdup(username);
    // ptr->next_user->password = strdup(password);
    strcpy(ptr->next_user->username, username);
    strcpy(ptr->next_user->password, password);
    ptr->next_user->next_user = NULL;
    userlist_tail = ptr->next_user;
    // if we register admin
    if (!strcmp(username, ADMIN_USERNAME))
    {
        admin = ptr;
    }
    // stack_sort_list(&userlist_head);
    return result;
}

void delete_user(char *username)
{
    // you cannot delete admin
    assert(strcmp(username, ADMIN_USERNAME));
    for (struct user *ptr = userlist_head; ptr != NULL; ptr = ptr->next_user)
    {
        if (!strcmp(ptr->next_user->username, username))
        {
            // if we match user, delete it
            struct user *tmp = ptr->next_user;
            ptr->next_user = tmp->next_user;
            free(tmp);
            break;
        }
    }
}

static struct sort_stack_item
{
    int level;
    struct user *ptr;
};

//  2 users alphabetic sort username
struct user *user_alphabetic_sort(struct user *ptr1, struct user *ptr2)
{
    struct user *result = NULL;
    if ((ptr1 == NULL) || (ptr2 == NULL))
    {
        return result;
    }
    // default result
    result = ptr1;
    ptr1->next_user = NULL;
    ptr2->next_user = NULL;
    char *username_ptr1 = strdup(ptr1->username);
    char *username_ptr2 = strdup(ptr2->username);
    if (strcmp(username_ptr1, username_ptr2) < 0)
    {
        ptr2->next_user = ptr1;
        result = ptr2;
    }
    free(username_ptr1);
    free(username_ptr2);
    return result;
}
// TODO: Fix sorting function
// sort user list from ptr
void stack_sort_list(struct user **ptr)
{
    struct sort_stack_item sort_stack[MAX_USER_NUM];
    memset(sort_stack, 0, sizeof(struct sort_stack_item) * MAX_USER_NUM);
    int sort_stack_pos = 0;
    struct user *sort_ptr = *ptr;
    while (sort_ptr != NULL)
    {
        sort_stack[sort_stack_pos].level = 1;
        sort_stack[sort_stack_pos].ptr = sort_ptr;
        sort_ptr = sort_ptr->next_user;
        sort_stack[sort_stack_pos].ptr->next_user = NULL;
        sort_stack_pos++;
        while ((sort_stack_pos > 1) &&
               (sort_stack[sort_stack_pos - 2].level == sort_stack[sort_stack_pos - 1].level))
        {
            sort_stack[sort_stack_pos - 2].ptr =
                user_alphabetic_sort(sort_stack[sort_stack_pos - 2].ptr,
                                     sort_stack[sort_stack_pos - 1].ptr);
            sort_stack[sort_stack_pos - 2].level++;
            sort_stack_pos--;
        }
    }
    while (sort_stack_pos > 1)
    {
        sort_stack[sort_stack_pos - 2].ptr =
            user_alphabetic_sort(sort_stack[sort_stack_pos - 2].ptr,
                                 sort_stack[sort_stack_pos - 1].ptr);
        sort_stack[sort_stack_pos - 2].level++;
        sort_stack_pos--;
    }
    if (sort_stack_pos > 0)
    {
        *ptr = sort_stack[0].ptr;
        for (struct user *tmp = (*ptr)->next_user; tmp != NULL;
                                            tmp = tmp->next_user)
        {
            userlist_tail = tmp;
        }
    }
}

struct user *get_admin_user(void)
{
    return admin;
}

struct user *get_userlist_head(void)
{
    return userlist_head;
}

struct user *get_userlist_tail(void)
{
    return userlist_tail;
}

void print_user_list(void)
{
    struct user *ptr = userlist_head;
    if (ptr == NULL)
        return;
    for (struct user *ptr = userlist_head; ptr != NULL; ptr = ptr->next_user)
    {
        printf("user:%s\tpassword:%s\tpointer:%p\n", ptr->username,
               ptr->password, ptr);
    }
}