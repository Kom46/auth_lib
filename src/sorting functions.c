#include "auth.h"
#include "string.h"

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