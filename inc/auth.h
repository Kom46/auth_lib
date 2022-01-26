#ifndef __AUTH_H__
#define __AUTH_H__

#include <stdbool.h>

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MAX_USER_NUM
#define MAX_USER_NUM 128
#endif

#ifndef MAX_USERNAME_LEN
#define MAX_USERNAME_LEN 8
#endif

#ifndef MAX_PASSWORD_LEN
#define MAX_PASSWORD_LEN 8
#endif

enum AUTH_RESULT_CODE
{
    AUTH_RESULT_OK,
    AUTH_RESULT_ERROR = -1,
    AUTH_RESULT_USER_LIMIT_EXECEED = -2,
    AUTH_RESULT_MALLOC_FAILED,
    AUTH_RESULT_PASS_VALIDATION_FAILED,
    AUTH_RESULT_USER_NOT_FOUND,
    AUTH_RESULT_OPERATION_NOT_PERMITED
};

struct user
{
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    struct user *next_user;
} *userlist_head = NULL, *userlist_tail = NULL;
/**
 * @brief function for user list initialization
 * 
 * @return result code in enum AUTH_RESULT_CODE
 */
int init_user_list(void);
/**
 * @brief function for finding user in user list
 * 
 * @param username[in] username for search
 * @return user handle struct user*
 */
struct user *find_user_in_list(char *username);
/**
 * @brief validate user pass for operation permitions
 * 
 * @param userptr[in] user handle
 * @param pass[in] user pass
 * @return true if validation succeed
 * @return false if validation failed
 */
bool validate_pass(struct user *userptr, char *pass);
/**
 * @brief validate password by username
 * 
 * @param username[in] username for searching user in user list
 * @param pass[in] password for validation
 * @return result code in enum AUTH_RESULT_CODE 
 */
int validate_user_pass(char *username, char *pass);
/**
 * @brief register user in system
 * 
 * @param username[in] username for new user
 * @param pass[in] pass for new user
 * @return result code in enum AUTH_RESULT_CODE
 */
int register_user(char *username, char *pass);
/**
 * @brief delete user from list
 * 
 * @param username[in] username for user to delete
 */
void delete_user(char *username);
/**
 * @brief sort linked list function
 * @details sorts linked list in alphabetic order with degradated lists method
 * @param ptr[in] pointer from sorting started(interpret in function as list head)
 */
void stack_sort_list(struct user **ptr);
/**
 * @brief change user pass by it's handle
 * 
 * @param huser[in] user handle
 * @param new_pass[in] new pass for user
 * @return result code in enum AUTH_RESULT_CODE
 */
int change_user_pass_by_handle(struct user *huser, char *new_pass);
/**
 * @brief change user pass by username
 * 
 * @param username[in] username of user
 * @param new_pass[in] new pass for user
 * @return result code in enum AUTH_RESULT_CODE
 */
int change_user_pass_by_username(char *username, char *new_pass);
/**
 * @brief change admin password
 * 
 * @param new_pass[in] new pass for admin
 * @param confirmation[in] old pass of admin user for confirmation
 * @return result code in enum AUTH_RESULT_CODE
 */
int change_admin_pass(char *new_pass, char *confirmation);

struct user * load_users(void);

int save_users(const struct user *head);
#endif