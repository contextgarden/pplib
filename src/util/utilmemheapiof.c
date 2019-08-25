
#include "utilmemheapiof.h"

#define HEAP_BUFER_MIN_SIZE(O) (O)->space

static size_t heap8_writer (iof *O, iof_mode mode)
{
  heap8 *heap;
  size_t written, space;
  heap = (heap8 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      heap8_done(heap, O->buf, written);
      O->buf = _heap8_some(heap, HEAP_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = heap8_more(heap, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written; // eq (space - written)
    case IOFCLOSE:
    default:
      break;
  }
  return 0;
}

static size_t heap16_writer (iof *O, iof_mode mode)
{
  heap16 *heap;
  size_t written, space;
  heap = (heap16 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      heap16_done(heap, O->buf, written);
      O->buf = _heap16_some(heap, HEAP_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = heap16_more(heap, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
    default:
      break;
  }
  return 0;
}

static size_t heap32_writer (iof *O, iof_mode mode)
{
  heap32 *heap;
  size_t written, space;
  heap = (heap32 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      heap32_done(heap, O->buf, written);
      O->buf = _heap32_some(heap, HEAP_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = heap32_more(heap, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
    default:
      break;
  }
  return 0;
}

static size_t heap64_writer (iof *O, iof_mode mode)
{
  heap64 *heap;
  size_t written, space;
  heap = (heap64 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      heap64_done(heap, O->buf, written);
      O->buf = _heap64_some(heap, HEAP_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = heap64_more(heap, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
    default:
      break;
  }
  return 0;
}

iof * heap8_setup_buffer (heap8 *heap, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = heap8_some(heap, atleast, &space);
  if (iof_writer(O, (void *)heap, heap8_writer, data, space) == NULL) // sanity
    return NULL;
  O->space = atleast;
  return O;
}

iof * heap16_setup_buffer (heap16 *heap, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = heap16_some(heap, atleast, &space);
  if (iof_writer(O, (void *)heap, heap16_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

iof * heap32_setup_buffer (heap32 *heap, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = heap32_some(heap, atleast, &space);
  if (iof_writer(O, (void *)heap, heap32_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

iof * heap64_setup_buffer (heap64 *heap, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = heap64_some(heap, atleast, &space);
  if (iof_writer(O, (void *)heap, heap64_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

