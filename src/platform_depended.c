#include "platform_depended.h"

#if defined(W25QXX)
#include "w25qxx.h"

// flash start address for storing user information
#define FLASH_START_ADDR 0x000000
// flash end address for storing user information
#define FLASH_END_ADDR 0x000F00

int save_buff_to_volatile_mem(void *ptr, size_t size)
{
  int result = 0;
  if ((FLASH_START_ADDR + size) <= FLASH_END_ADDR)
  {
    W25qxx_EraseSector(FLASH_START_ADDR);
    W25qxx_WriteSector(ptr, FLASH_START_ADDR, 0, (uint32_t)size);
  }
  else
  {
    result = -1;
  }
  return result;
}

int load_buff_from_volatile_mem(void *ptr, size_t size)
{
  int result = 0;
  if ((FLASH_START_ADDR + size) <= FLASH_END_ADDR)
  {
    W25qxx_ReadSector(ptr, FLASH_START_ADDR, 0, (uint32_t)size);
  }
  else
  {
    result = -1;
  }
  return result;
}

#else

__attribute__((weak)) int save_buff_to_volatile_mem(void *ptr, size_t size)
{
  /*TODO: Implement Me!*/
  (void)ptr;
  (void)size;
  return (int)0;
}

__attribute__((weak)) int load_buff_from_volatile_mem(void *ptr, size_t size)
{
  /*TODO: Implement Me!*/
  (void)ptr;
  (void)size;
  return (int)0;
}
#endif
