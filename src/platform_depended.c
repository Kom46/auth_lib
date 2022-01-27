#include <stdlib.h>

#if defined(W25QXX)
#include "w25qxx.h"
#endif

#ifndef FLASH_START_ADDRESS
#define FLASH_START_ADDRESS 0x0
#endif

#ifndef FLASH_END_ADDRESS
#define FLASH_END_ADDRESS 0xfff
#endif

int save_buff_to_volatile_mem(void *ptr, size_t size)
{
    int result = 0;
    size = (size > (FLASH_END_ADDRESS - FLASH_START_ADDRESS)) ? 
                        (FLASH_END_ADDRESS - FLASH_START_ADDRESS) : size;
#if defined(W25QXX)
    W25qxx_EraseSector(W25qxx_PageToSector(FLASH_START_ADDRESS));
    W25qxx_WriteSector((uint8_t *)ptr, W25qxx_PageToSector(FLASH_START_ADDRESS), 0, size);
#endif
    return result;
}

int load_buff_from_volatile_mem(void *ptr, size_t size)
{
    int result = 0;
    #if defined(W25QXX)
    W25qxx_ReadBytes((uint8_t *)ptr, FLASH_START_ADDRESS, size);
    #endif
    return result;
}