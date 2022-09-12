#ifdef TEST

#include "unity.h"

#include "auth.h"
#include "platform_depended.h"
#include "sorting_functions.h"

void setUp(void)
{
    TEST_ASSERT_EQUAL_INT(AUTH_RESULT_OK, init_user_list());
}

void tearDown(void)
{
}

void test_sorting_functions_NeedToImplement(void)
{
    // TEST_IGNORE_MESSAGE("Need to Implement sorting_functions");
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("xyz", "xyz"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("abc", "abc"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("bcd", "bcd"));
    print_user_list();
    struct user a = {.username = "abc"}, b = {.username = "bcd"};
    TEST_ASSERT_EQUAL_PTR(&a, user_alphabetic_sort(&a, &b));
    struct user * head, *tail;
    head = get_userlist_head();
    tail = get_userlist_tail();
    // stack_sort_list(&head, &tail);
    print_user_list();
}

#endif // TEST
