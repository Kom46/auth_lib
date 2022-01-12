#ifndef __AUTH_H__
#define __AUTH_H__

#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

enum AUTH_RESULT_CODE
{
    AUTH_RESULT_OK,
    AUTH_RESULT_ERROR = -1,
    AUTH_RESULT_USER_LIMIT_EXECEED = -2,
    AUTH_RESULT_MALLOC_FAILED
};

static struct user
{
    /* data */
    char *username;
    char *password;
    struct user *next_user;
};

// initialize user list
void init_user_list(void);
// find user in list
struct user *find_user_in_list(char *username);
// validate password in user struct
bool validate_pass(struct user *userptr, char *pass);
// validate pass with given username and password
bool validate_user_pass(char *username, char *pass);
// register user
int register_user(char *username, char *pass);
// delete user by user
void delete_user(char *username);

#endif