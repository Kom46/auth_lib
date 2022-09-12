#ifndef __SORTING_FUNCTIONS_H__
#define __SORTING_FUNCTIONS_H__
/**
 * @brief 
 * 
 * @param ptr 
 * @param userlist_tail 
 */
void stack_sort_list(struct user **ptr, struct user **userlist_tail);
/**
 * @brief 
 * 
 * @param ptr1 
 * @param ptr2 
 * @return struct user* 
 */
struct user *user_alphabetic_sort(struct user *ptr1, struct user *ptr2);

#endif