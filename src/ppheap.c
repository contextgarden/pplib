
#include "pplib.h"

#define PPBYTES_HEAP_BLOCK 0xFFF
#define PPBYTES_HEAP_LARGE (PPBYTES_HEAP_BLOCK >> 2)
#define PPBYTES_HEAP_LEAST 4
#define PPSTRUCT_HEAP_BLOCK 0xFFF
#define PPSTRUCT_HEAP_LARGE (PPSTRUCT_HEAP_BLOCK >> 2)

void qqheap_init (qqheap *qheap)
{
  qqstruct_heap_init(&qheap->structheap, PPSTRUCT_HEAP_BLOCK, PPSTRUCT_HEAP_LARGE, 0);
  qqbytes_heap_init(&qheap->bytesheap, PPBYTES_HEAP_BLOCK, PPBYTES_HEAP_LARGE, 0);
  qqbytes_heap_setup_buffer(&qheap->bytesheap, &qheap->bytesbuffer, PPBYTES_HEAP_LEAST);
}

void qqheap_free (qqheap *qheap)
{
  qqstruct_heap_free(&qheap->structheap);
  qqbytes_heap_free(&qheap->bytesheap);
}

void qqheap_renew (qqheap *qheap)
{
  qqstruct_heap_clear(&qheap->structheap);
  qqbytes_heap_clear(&qheap->bytesheap);
  qqbytes_heap_setup_buffer(&qheap->bytesheap, &qheap->bytesbuffer, PPBYTES_HEAP_LEAST);
}

// qq tmp, to have same interface for a while. names and strings will be allocated from as other structs,
// initsize will be constant, so qqheap_buffer() will just return its permanent;y ready &qheap->bytesbuffer
iof * qqheap_buffer (qqheap *qheap, size_t objectsize, size_t initsize)
{
  iof *O;
  size_t space;
  O = qqbytes_buffer(qheap);
  O->buf = qqbytes_heap_some(&qheap->bytesheap, objectsize + initsize, &space);
  O->pos = O->buf + objectsize;
  O->end = O->buf + space;
  return O;
}

// qq tmp iof_flush() does the same interface as before
void * qqheap_flush (iof *O, size_t *psize)
{
  qqbytes_heap *qheap;
  void *data;
  //size_t space;
  qheap = (qqbytes_heap *)O->link;
  data = O->buf;
  *psize = (size_t)iof_size(O);
  qqbytes_heap_done(qheap, data, *psize);
  // makes no sense until we do that on every qqheap_buffer(); all that stuff will go
  //O->buf = qqbytes_heap_some(qheap, 0, &space);
  //O->pos = O->buf;
  //O->end = O->buf + space;
  return data;
}