/*
 * original: http://www.opensource.apple.com/source/Heimdal/Heimdal-247.6/lib/wind/utf8.c
 * tweaks: removed dependency and re-defined errcodes
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>

#define WIND_ERR_INVALID_UTF8 -969269754
#define WIND_ERR_OVERRUN -969269758

// uint32_t is already defined in standard Android headers
#if !defined(__ANDROID__)
typedef unsigned int uint32_t;
#endif

int utf8toutf32(const unsigned char **pp, uint32_t *out);
int wind_utf8ucs4(const char *in, unsigned *out, unsigned *out_len);
int wind_utf8ucs4_length(const char *in, size_t *out_len);
int wind_utf8ucs4_copy(const char *in, uint32_t **out, size_t *out_len);

#ifdef __cplusplus
}
#endif /* __cplusplus */
