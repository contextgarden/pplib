
#include "utilmemstockiof.h"

#define STOCK_BUFER_MIN_SIZE(O) (O)->space

static size_t stock8_writer (iof *O, iof_mode mode)
{
  stock8 *stock;
  size_t written, space;
  stock = (stock8 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      stock8_done(stock, O->buf, written);
      O->buf = _stock8_some(stock, STOCK_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = stock8_more(stock, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written; // eq (space - written)
    case IOFCLOSE:
      break;
  }
  return 0;
}

static size_t stock16_writer (iof *O, iof_mode mode)
{
  stock16 *stock;
  size_t written, space;
  stock = (stock16 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      stock16_done(stock, O->buf, written);
      O->buf = _stock16_some(stock, STOCK_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = stock16_more(stock, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
      break;
  }
  return 0;
}

static size_t stock32_writer (iof *O, iof_mode mode)
{
  stock32 *stock;
  size_t written, space;
  stock = (stock32 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      stock32_done(stock, O->buf, written);
      O->buf = _stock32_some(stock, STOCK_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = stock32_more(stock, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
      break;
  }
  return 0;
}

static size_t stock64_writer (iof *O, iof_mode mode)
{
  stock64 *stock;
  size_t written, space;
  stock = (stock64 *)O->link;
  switch (mode)
  {
    case IOFFLUSH:
      written = (size_t)iof_size(O);
      stock64_done(stock, O->buf, written);
      O->buf = _stock64_some(stock, STOCK_BUFER_MIN_SIZE(O), &space);
      O->pos = O->buf;
      O->end = O->buf + space;
      break;
    case IOFWRITE:
      written = (size_t)iof_size(O);
      space = written << 1;
      O->buf = stock64_more(stock, O->buf, written, space);
      O->pos = O->buf + written;
      O->end = O->buf + space;
      return written;
    case IOFCLOSE:
      break;
  }
  return 0;
}

iof * stock8_setup_buffer (stock8 *stock, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = stock8_some(stock, atleast, &space);
  if (iof_writer(O, (void *)stock, stock8_writer, data, space) == NULL) // sanity
    return NULL;
  O->space = atleast;
  return O;
}

iof * stock16_setup_buffer (stock16 *stock, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = stock16_some(stock, atleast, &space);
  if (iof_writer(O, (void *)stock, stock16_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

iof * stock32_setup_buffer (stock32 *stock, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = stock32_some(stock, atleast, &space);
  if (iof_writer(O, (void *)stock, stock32_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

iof * stock64_setup_buffer (stock64 *stock, iof *O, size_t atleast)
{
  void *data;
  size_t space;
  data = stock64_some(stock, atleast, &space);
  if (iof_writer(O, (void *)stock, stock64_writer, data, space) == NULL)
    return NULL;
  O->space = atleast;
  return O;
}

