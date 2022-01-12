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

static struct user registered_users[MAX_USER_NUM] = {NULL};

static int registered_users_count = 1;

void init_user_list(void)
{
    // first pointer for user list(right after administrator)
    struct user **last_user = &admin.next_user;
    for (struct user *ptr = registered_users; (ptr != NULL) && (ptr < (register_user + MAX_USER_NUM)); ptr++)
    {
        *last_user = ptr;
        last_user = &ptr->next_user;
        registered_users_count++;
    }
}

struct user *find_user_in_list(char *username)
{
    struct user *ptr = &admin;
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
    struct user *ptr = admin.next_user;
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
    return result;
}

void delete_user(char *username)
{
    // you cannot delete admin
    assert(strcmp(username, ADMIN_USERNAME));
    for (struct user *ptr = &admin; ptr != NULL; ptr = ptr->next_user)
    {
        if (!strcmp(ptr->next_user->username, username))
        {
            // if we match user, delete it
            struct user *tmp = ptr->next_user;
            ptr->next_user = tmp->next_user;
            memset(tmp, 0, sizeof(struct user));
            break;
        }
    }
}