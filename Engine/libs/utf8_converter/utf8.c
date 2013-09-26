/*
 * Copyright (c) 2004, 2006, 2007, 2008 Kungliga Tekniska Högskolan
 * (Royal Institute of Technology, Stockholm, Sweden).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * original: http://www.opensource.apple.com/source/Heimdal/Heimdal-247.6/lib/wind/utf8.c
 * tweaks: removed dependency and re-defined errcodes
 */

#include "utf8.h"

int utf8toutf32(const unsigned char **pp, uint32_t *out)
{
	const unsigned char *p = *pp;
	unsigned c = *p;

	if (c & 0x80) {
		if ((c & 0xE0) == 0xC0) {
			const unsigned c2 = *++p;
			if ((c2 & 0xC0) == 0x80) {
				*out =  ((c  & 0x1F) << 6)
					| (c2 & 0x3F);
			} else {
				return WIND_ERR_INVALID_UTF8;
			}
		} else if ((c & 0xF0) == 0xE0) {
			const unsigned c2 = *++p;
			if ((c2 & 0xC0) == 0x80) {
				const unsigned c3 = *++p;
				if ((c3 & 0xC0) == 0x80) {
					*out =   ((c  & 0x0F) << 12)
						| ((c2 & 0x3F) << 6)
						|  (c3 & 0x3F);
				} else {
					return WIND_ERR_INVALID_UTF8;
				}
			} else {
				return WIND_ERR_INVALID_UTF8;
			}
		} else if ((c & 0xF8) == 0xF0) {
			const unsigned c2 = *++p;
			if ((c2 & 0xC0) == 0x80) {
				const unsigned c3 = *++p;
				if ((c3 & 0xC0) == 0x80) {
					const unsigned c4 = *++p;
					if ((c4 & 0xC0) == 0x80) {
						*out =   ((c  & 0x07) << 18)
							| ((c2 & 0x3F) << 12)
							| ((c3 & 0x3F) <<  6)
							|  (c4 & 0x3F);
					} else {
						return WIND_ERR_INVALID_UTF8;
					}
				} else {
					return WIND_ERR_INVALID_UTF8;
				}
			} else {
				return WIND_ERR_INVALID_UTF8;
			}
		} else {
			return WIND_ERR_INVALID_UTF8;
		}
	} else {
		*out = c;
	}

	*pp = p;

	return 0;
}

/**
 * Convert an UTF-8 string to an UCS4 string.
 *
 * @param in an UTF-8 string to convert.
 * @param out the resulting UCS4 strint, must be at least
 * wind_utf8ucs4_length() long.  If out is NULL, the function will
 * calculate the needed space for the out variable (just like
 * wind_utf8ucs4_length()).
 * @param out_len before processing out_len should be the length of
 * the out variable, after processing it will be the length of the out
 * string.
 *
 * @return returns 0 on success, an wind error code otherwise
 * @ingroup wind
 */

int wind_utf8ucs4(const char *in, unsigned *out, unsigned *out_len)
{
	const unsigned char *p;
	size_t o = 0;
	int ret;

	for (p = (const unsigned char *)in; *p != '\0'; ++p) {
		uint32_t u;

		ret = utf8toutf32(&p, &u);
		if (ret)
			return ret;

		if (out) {
			if (o >= *out_len)
				return WIND_ERR_OVERRUN;
			out[o] = u;
		}
		o++;
	}
	*out_len = o;
	return 0;
}

/**
 * Calculate the length of from converting a UTF-8 string to a UCS4
 * string.
 *
 * @param in an UTF-8 string to convert.
 * @param out_len the length of the resulting UCS4 string.
 *
 * @return returns 0 on success, an wind error code otherwise
 * @ingroup wind
 */

int wind_utf8ucs4_length(const char *in, size_t *out_len)
{
	return wind_utf8ucs4(in, NULL, out_len);
}

/**
 * Convert an UTF-8 string to an UCS4 string.
 *
 * @param in an UTF-8 string to convert.
 * @param out the resulting UCS4 strint, must be free with free().
 * @param out_len will be the length of the out string.
 *
 * @return returns 0 on success, an wind error code otherwise
 * @ingroup wind
 */

int wind_utf8ucs4_copy(const char *in, uint32_t **out, size_t *out_len)
{
	int ret;

	ret = wind_utf8ucs4_length(in, out_len);
	if (ret)
		return ret;
	if (*out_len > UINT_MAX / sizeof((*out)[0]))
		return ERANGE;

	*out = (uint32_t*)malloc(*out_len * sizeof(*out_len));
	if (*out == NULL) {
		*out_len = 0;
		return ENOMEM;
	}

	ret = wind_utf8ucs4(in, *out, out_len);
	if (ret) {
		free(*out);
		*out = NULL;
		*out_len = 0;
	}
	return ret;
}

