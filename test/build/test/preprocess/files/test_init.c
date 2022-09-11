#include "src/platform_depended.h"
#include "src/auth.h"
#include "/var/lib/gems/2.7.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{

    UnityAssertEqualNumber((UNITY_INT)((AUTH_RESULT_OK)), (UNITY_INT)((init_user_list())), (

   ((void *)0)

   ), (UNITY_UINT)(7), UNITY_DISPLAY_STYLE_INT);

}



void tearDown(void)

{

}



void test_init( void )

{

    do {if ((((get_userlist_head())) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(16))));}} while(0);

    do {if ((((get_userlist_tail())) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(17))));}} while(0);

    do {if ((((get_userlist_tail()->next_user)) == 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(18))));}} while(0);

    do {if ((get_userlist_head() != get_userlist_tail())) {} else {UnityFail( ((" Expression Evaluated To FALSE")), (UNITY_UINT)((UNITY_UINT)(19)));}} while(0);

    do {if ((((find_user_in_list("unlisted"))) == 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(20))));}} while(0);

    do {if ((((find_user_in_list("admin"))) != 

   ((void *)0)

   )) {} else {UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)((UNITY_UINT)((UNITY_UINT)(21))));}} while(0);

    UnityAssertEqualString((const char*)((find_user_in_list("admin")->username)), (const char*)(("admin")), (

   ((void *)0)

   ), (UNITY_UINT)(22))

                                                                               ;

    UnityAssertEqualNumber((UNITY_INT)((AUTH_RESULT_OK)), (UNITY_INT)((register_user("xyz", "xyz"))), (

   ((void *)0)

   ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((AUTH_RESULT_OK)), (UNITY_INT)((register_user("abc", "abc"))), (

   ((void *)0)

   ), (UNITY_UINT)(25), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((AUTH_RESULT_OK)), (UNITY_INT)((register_user("bcd", "bcd"))), (

   ((void *)0)

   ), (UNITY_UINT)(26), UNITY_DISPLAY_STYLE_INT);

    print_user_list();

    do {if (((AUTH_RESULT_OK) != (register_user("bcd", "bcd")))) {} else {UnityFail( ((" Expected Not-Equal")), (UNITY_UINT)((UNITY_UINT)(28)));}} while(0);

    do {if ((get_userlist_head() != get_userlist_tail())) {} else {UnityFail( ((" Expression Evaluated To FALSE")), (UNITY_UINT)((UNITY_UINT)(29)));}} while(0);

}
