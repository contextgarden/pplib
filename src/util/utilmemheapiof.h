
#ifndef UTIL_MEM_HEAP_IOF_H
#define UTIL_MEM_HEAP_IOF_H

#include "utilmemheap.h"
#include "utiliof.h"

UTILAPI iof * heap8_setup_buffer (heap8 *heap, iof *O, size_t atleast);
UTILAPI iof * heap16_setup_buffer (heap16 *heap, iof *O, size_t atleast);
UTILAPI iof * heap32_setup_buffer (heap32 *heap, iof *O, size_t atleast);
UTILAPI iof * heap64_setup_buffer (heap64 *heap, iof *O, size_t atleast);

#endif