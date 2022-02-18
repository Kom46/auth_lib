#include "unity.h"
#include "auth.h"
#include "platform_depended.h"

void setUp(void)
{
    TEST_ASSERT_EQUAL_INT(AUTH_RESULT_OK, init_user_list());
}

void tearDown(void)
{
}

void test_init( void )
{
    TEST_ASSERT_NOT_NULL(get_userlist_head());
    TEST_ASSERT_NOT_NULL(get_userlist_tail());
    TEST_ASSERT_NULL(get_userlist_tail()->next_user);
    TEST_ASSERT(get_userlist_head() != get_userlist_tail());
    TEST_ASSERT_NULL(find_user_in_list("unlisted"));
    TEST_ASSERT_NOT_NULL(find_user_in_list(ADMIN_USERNAME));
    TEST_ASSERT_EQUAL_STRING(find_user_in_list(ADMIN_USERNAME)->username, 
                                                                ADMIN_USERNAME);
    // print_user_list();
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("xyz", "xyz"));
    // print_user_list();
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("abc", "abc"));
    // print_user_list();
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("bcd", "bcd"));
    print_user_list();
    TEST_ASSERT_NOT_EQUAL(AUTH_RESULT_OK, register_user("bcd", "bcd"));
    TEST_ASSERT(get_userlist_head() != get_userlist_tail());
}