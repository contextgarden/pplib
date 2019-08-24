
#ifndef UTIL_MEM_STOCK_IOF_H
#define UTIL_MEM_STOCK_IOF_H

#include "utilmemstock.h"
#include "utiliof.h"

UTILAPI iof * stock8_setup_buffer (stock8 *stock, iof *O, size_t atleast);
UTILAPI iof * stock16_setup_buffer (stock16 *stock, iof *O, size_t atleast);
UTILAPI iof * stock32_setup_buffer (stock32 *stock, iof *O, size_t atleast);
UTILAPI iof * stock64_setup_buffer (stock64 *stock, iof *O, size_t atleast);

#endif