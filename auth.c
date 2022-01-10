#include "auth.h"

#ifndef MAX_USER_NUM
#define MAX_USER_NUM 10
#endif
static struct user;

static const struct user
{
    const char *login = "admin";
    const char *pass = "admin";
    struct user *next_user = NULL;
} admin;

static struct user
{
    /* data */
    char *login;
    char *pass;
    struct user *next_user;
} *first_user = admin;

static const char *registered_logins[MAX_USER_NUM] = {""};
static const char *registered_passwords[MAX_USER_NUM] = {""};

void init_user_list(void)
{
    // first pointer for user list(points on admin struct)
    struct user *last_user = first_user;

    for (size_t i = 0; i < MAX_USER_NUM; i++)
    {
        // if there are no left registered logins
        if (!strlen(registered_logins[i]))
            break;
        if (!last_user)
        {
            last_user = (struct user *)malloc(sizeof(struct user));
        }
        assert(last_user != NULL);
    }
}
