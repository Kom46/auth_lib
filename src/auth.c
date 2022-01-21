#include "auth.h"

#ifndef MAX_USER_NUM
#define MAX_USER_NUM 128
#endif

#ifndef ADMIN_USERNAME
#define ADMIN_USERNAME "admin"
#endif

#ifndef ADMIN_PASSWORD
#define ADMIN_PASSWORD "admin"
#endif

static struct user admin = {.username = ADMIN_USERNAME, .password = ADMIN_PASSWORD, .next_user = NULL};

static const struct user registered_users[MAX_USER_NUM] = {NULL};

void init_user_list(void)
{
    // first pointer for user list(right after administrator)
    userlist_head = &admin;
    userlist_tail = userlist_head;
    for (struct user *ptr = registered_users; (ptr != NULL) && (ptr < (register_user + MAX_USER_NUM)); ptr++)
    {
        userlist_tail->next_user = (struct user *)malloc(sizeof(struct user));
        memcpy(userlist_tail->next_user, ptr, sizeof(struct user));
        userlist_tail = userlist_tail->next_user;
        userlist_tail->next_user = NULL;
    }
}

struct user *find_user_in_list(char *username)
{
    struct user *ptr = userlist_head;
    while (ptr != NULL)
    {
        if (!strcmp(ptr->username, username))
        {
            break;
        }
        else
        {
            ptr = ptr->next_user;
        }
    }
    return ptr;
}

bool validate_password(struct user *userptr, char *password)
{
    bool result = false;
#if defined(AUTH_PASSWORD_NO_ENCRYPTION)
    result = !strcmp(userptr->password, password);
#endif // AUTH_PASSWORD_NO_ENCRYPTION
    return result;
}

bool validate_user_password(char *username, char *password)
{
    bool result = false;
    struct user *ptr = find_user_in_list(username);
    if (ptr != NULL)
    {
        result = validate_password(ptr, password);
    }
    return result;
}

int register_user(char *username, char *password)
{
    int result = AUTH_RESULT_OK;
    if (!((registered_users_count + 1) >= MAX_USER_NUM))
    {
        return AUTH_RESULT_USER_LIMIT_EXECEED;
    }
    struct user *ptr = userlist_tail;
    while (ptr->next_user != NULL)
    {
        ptr = ptr->next_user;
    }
    ptr->next_user = (struct user *)malloc(sizeof(struct user));
    if (ptr->next_user == NULL)
    {
        return AUTH_RESULT_MALLOC_FAILED;
    }
    ptr->next_user->username = strdup(username);
    ptr->next_user->password = strdup(password);
    ptr->next_user->next_user = NULL;
    userlist_tail = ptr->next_user;
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

struct sort_stack_item
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
    //default result
    result = ptr1;
    ptr1->next_user = NULL;
    ptr2->next_user = NULL;
    char *username_ptr1 = strlwr(strdup(ptr1->username));
    char *username_ptr2 = strlwr(strdup(ptr2->username));
    for (int i = 0; i < MIN(strlen(ptr1->username), strlen(ptr2->username)); i++)
    {
        if (username_ptr1[i] < username_ptr2[i])
        {
            ptr2->next_user = ptr1;
            result = ptr2;
            break;
        }
    };
    free(username_ptr1);
    free(username_ptr2);
    return result;
}
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
        userlist_tail = (*ptr)->next_user;
        while (userlist_tail->next_user != NULL)
        {
            userlist_tail = userlist_tail->next_user;
        }
    }
}

// TODO: add save/load functions for lib
