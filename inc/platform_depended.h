#ifndef __PLATFORM_DEPENED_H__
#define __PLATFORM_DEPENED_H__

#if defined(FREERTOS)
#ifndef malloc(size)
#define malloc(size) pvPortMalloc(size)
#endif
#ifndef free(ptr)
#define free(ptr) pvPortFree(ptr)
#endif
#endif

int save_buff_to_volatile_mem(void *ptr, size_t size);
int load_buff_from_volatile_mem(void *address, void *ptr, size_t size);

#endif