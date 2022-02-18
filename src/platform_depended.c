#include "platform_depended.h"


__attribute__ ((weak)) int save_buff_to_volatile_mem(void* ptr, size_t size)
{
  /*TODO: Implement Me!*/
  (void)ptr;
  (void)size;
  return (int)0;
}

__attribute__ ((weak)) int load_buff_from_volatile_mem(void* ptr, size_t size)
{
  /*TODO: Implement Me!*/
  (void)ptr;
  (void)size;
  return (int)0;
}

