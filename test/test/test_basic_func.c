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

void test_basic_func( void )
{
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, register_user("abc", "abc"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, validate_user_password("abc", "abc"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OPERATION_NOT_PERMITED, 
                                            validate_user_password("abc", "bcd"));
    TEST_ASSERT_TRUE(validate_password(find_user_in_list("abc"), "abc"));
    TEST_ASSERT_FALSE(validate_password(find_user_in_list("abc"), "bcd"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, 
                change_user_pass_by_handle(find_user_in_list("abc"), "bcd"));
    TEST_ASSERT_EQUAL(0, strcmp(find_user_in_list("abc")->password, "bcd"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, 
            change_user_pass_by_username("abc", "xyz"));
    TEST_ASSERT_EQUAL(0, strcmp(find_user_in_list("abc")->password, "xyz"));
    TEST_ASSERT_EQUAL(AUTH_RESULT_OK, change_admin_pass("abc", ADMIN_PASSWORD));
    TEST_ASSERT_EQUAL(0, strcmp(get_admin_user()->password, "abc"));
    delete_user("abc");
    TEST_ASSERT_NULL(find_user_in_list("abc"));
}