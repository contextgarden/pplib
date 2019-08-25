
#ifndef PP_HEAP_H
#define PP_HEAP_H

#include "utilmem.h"

#define pp_malloc util_malloc
//#define pp_callic util_calloc
//#define pp_realloc util_realloc
#define pp_free util_free

// qq

#include "utilmemheapiof.h"
//#include "utilmeminfo.h"

#if 0 // tmp bytes heap 2-bytes aligned
#define qqbytes_heap heap16
#define qqbytes_heap_init(heap, space, large, flags) (heap16_init(heap, space, large, flags), heap16_head(heap))
#define qqbytes_heap_take(heap, size) _heap16_take(heap, size)
#define qqbytes_heap_some(heap, size, pspace) _heap16_some(heap, size, pspace) // tmp
#define qqbytes_heap_done(heap, data, written) heap16_done(heap, data, written) // tmp
#define qqbytes_heap_setup_buffer(heap, iof, atleast) heap16_setup_buffer(heap, iof, atleast)
#define qqbytes_heap_clear(heap) heap16_clear(heap)
#define qqbytes_heap_free(heap) heap16_free(heap)
#define qqbytes_heap_info(heap, info, append) heap16_stats(heap, info, append)
#else // tmp bytes heap 8-bytes aligned
#define qqbytes_heap heap64
#define qqbytes_heap_init(heap, space, large, flags) (heap64_init(heap, space, large, flags), heap64_head(heap))
#define qqbytes_heap_take(heap, size) _heap64_take(heap, size)
#define qqbytes_heap_some(heap, size, pspace) _heap64_some(heap, size, pspace) // tmp
#define qqbytes_heap_done(heap, data, written) heap64_done(heap, data, written) // tmp
#define qqbytes_heap_setup_buffer(heap, iof, atleast) heap64_setup_buffer(heap, iof, atleast)
#define qqbytes_heap_clear(heap) heap64_clear(heap)
#define qqbytes_heap_free(heap) heap64_free(heap)
#define qqbytes_heap_info(heap, info, append) heap64_stats(heap, info, append)
#endif

#define qqstruct_heap heap64
#define qqstruct_heap_init(heap, space, large, flags) (heap64_init(heap, space, large, flags), heap64_head(heap))
#define qqstruct_heap_take(heap, size) _heap64_take(heap, size)
#define qqstruct_heap_clear(heap) heap64_clear(heap)
#define qqstruct_heap_free(heap) heap64_free(heap)
#define qqstruct_heap_info(heap, info, append) heap64_stats(heap, info, append)

#define qqbytes_take(qheap, size) qqbytes_heap_take(&(qheap)->bytesheap, size)
#define qqbytes_buffer(qheap) (&(qheap)->bytesbuffer)
#define qqstruct_take(qheap, size) qqstruct_heap_take(&(qheap)->structheap, size)

typedef struct {
  qqbytes_heap bytesheap;
  qqstruct_heap structheap;
  iof bytesbuffer;
} qqheap;

void qqheap_init (qqheap *qheap);
void qqheap_free (qqheap *qheap);
void qqheap_renew (qqheap *qheap);
iof * qqheap_buffer (qqheap *qheap, size_t objectsize, size_t initsize);
void * qqheap_flush (iof *O, size_t *psize);

#endif