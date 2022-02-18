#include "src/platform_depended.h"
#include "src/auth.h"
#include "/var/lib/gems/2.5.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


void setUp(void)

{



}



void tearDown(void)

{

}



void test_init( void )

{

    UnityAssertEqualNumber((UNITY_INT)((AUTH_RESULT_OK)), (UNITY_INT)((init_user_list())), (

   ((void *)0)

   ), (UNITY_UINT)(16), UNITY_DISPLAY_STYLE_INT);

}
