#include "api/yajl_parse.h"
#include "yajl_parser.h"

#include <stdio.h>

#define BJSON_NO_ERROR		(yajl_status_ok)
#define BJSON_CANCEL		(yajl_status_client_canceled)
#define BJSON_ERROR			(yajl_status_error)

#define CHCK_PARSER(x)		if (!(x)) { \
								error = BJSON_CANCEL; parse = endStream; \
							}

#define CHCK_PARSER_LOOP(x)	if (!(x)) { \
								error = BJSON_CANCEL; parse = endStream; break; \
							}


int bjson_getCPCacheID(		yajl_handle		hand,
							int				cte_pool) {
	bjson_handle* bjsn	= &hand->bj;
	if ((cte_pool < bjsn->cp_count) && (cte_pool >= 0)) {
		return bjsn->cp[cte_pool].memberCache;
	} else {
		return -1;
	}
}

void bjson_setCPCacheID(	yajl_handle		hand,
							int				cte_pool,
							int				cacheID) {
	bjson_handle* bjsn	= &hand->bj;
	if ((cte_pool < bjsn->cp_count) && (cte_pool >= 0)) {
		bjsn->cp[cte_pool].memberCache = cacheID;
	} else {
		return;
	}
}

int bjson_parse(	yajl_handle		hand,
					const unsigned char*	jsonText,
					int						jsonTextLength
				)
{
	bjson_handle*	bjsn= &hand->bj;

	int error			= BJSON_NO_ERROR;
	const yajl_callbacks * callbacks = hand->callbacks;
	cp_entry*	cp		= 0;
	void*		ctx		= bjsn->ctx;

	const unsigned char* endStream	= &jsonText[jsonTextLength];
	const unsigned char* parse		= jsonText;

	// Parse header
	if ((parse[0] != 0xFF) || (parse[1] != 0xFF)) {
		error	= BJSON_ERROR;
		parse	= endStream;
	} else {
		parse += 2;
	}

	// Parse Pre-CP
	{
		int strSize;
		int cnt = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
		parse += 4;
		strSize = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
		parse += 4;

		if (cnt) {
			bjsn->cp_count = cnt;
			bjsn->cp	= (cp_entry*)hand->alloc.malloc(hand->alloc.ctx , cnt * sizeof(cp_entry));
			cp			= bjsn->cp;
			bjsn->strs	= NULL; // (unsigned char*)hand->alloc.malloc(hand->alloc.ctx, strSize);
			if (bjsn->cp /*&& bjsn->strs*/) {
				int n;
//				unsigned char* wPtr = bjsn->strs;
				for (n=0; n < cnt; n++) {
					// Size
					int len = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
					parse += 4;

					// String
					// memcpy(wPtr, parse, len);
					cp[n].string		= parse;

					// Read Ptr
					parse	+= len;
					// Write Ptr
					// wPtr	+= len;

					// Cache
					cp[n].stringlen		= len;
					cp[n].memberCache	= -1;
				}
			} else {
				error	= BJSON_ERROR;
				parse	= endStream;
			}
		}
	}
	
	// Parse Inner stream
	while (parse < endStream) {
		// printf("Comm %4i %i %i\n",commandID++, *parse, error);

		switch (*parse++) {
		case BJSN_END:
			parse = endStream;
			break;
		case BJSN_OPEN_OBJ:
			{
				int size = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				CHCK_PARSER(callbacks->yajl_start_map(ctx,size));
			}
			break;
		case BJSN_OPEN_ARR:
			{
				int size = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 8; // Skip type mask
				CHCK_PARSER(callbacks->yajl_start_array(ctx, size));
			}
			break;
		case BJSN_CLOSE_OBJ:
			CHCK_PARSER(callbacks->yajl_end_map(ctx));
			break;
		case BJSN_CLOSE_ARR:
			CHCK_PARSER(callbacks->yajl_end_array(ctx));
			break;
		case BJSN_STRING:
			{
				int idx = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4; 
				CHCK_PARSER(callbacks->yajl_string(ctx, cp[idx].string, cp[idx].stringlen, idx));
			}
			break;
		case BJSN_STRING_DIRECT:
			{
				int len = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				CHCK_PARSER(callbacks->yajl_string(ctx, parse, len, -1));
				parse += len;
			}
			break;
		case BJSN_MEMBER:
			{
				int idx = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				CHCK_PARSER(callbacks->yajl_map_key(ctx, cp[idx].string, cp[idx].stringlen, idx));
			}
			break;
		case BJSN_MEMBER_DIRECT:
			{
				int len = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				CHCK_PARSER(callbacks->yajl_map_key(ctx, parse, len, -1));
				parse += len;
			}
			break;
		case BJSN_NUMBER_I64:
			{
				// MSB 32/64
				int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				unsigned int idx2 = (parse[4] << 24) | (parse[5] << 16) | (parse[6] << 8) | parse[7];
				long long int l64 = (((long long int)idx)<<32) | idx2;
				parse += 8;
				CHCK_PARSER(callbacks->yajl_integer(ctx, l64));
			}
			break;
		case BJSN_NUMBER_DBL:
			{
				unsigned int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				unsigned int idx2 = (parse[4] << 24) | (parse[5] << 16) | (parse[6] << 8) | parse[7];
				unsigned long long int l64 = (((unsigned long long int)idx)<<32) | idx2;
				parse += 8;
				CHCK_PARSER(callbacks->yajl_double(ctx, (*((double*)&l64))));
			}
			break;
		case BJSN_NUMBER_I32:
			{
				int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				CHCK_PARSER(callbacks->yajl_integer(ctx, idx));
			}
			break;
		case BJSN_NUMBER_I16:
			{
				int idx  = (short)((parse[0] << 8) | parse[1]);
				idx <<= 16;
				idx >>= 16;
				parse += 2;
				CHCK_PARSER(callbacks->yajl_integer(ctx, idx));
			}
			break;
		case BJSN_NUMBER_I8:
			{
				int c = *parse++;
				c <<= 24;
				c >>= 24;
				CHCK_PARSER(callbacks->yajl_integer(ctx, c));
			}
			break;
		case BJSN_NUMBER_FLT:
			{
				int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				// int --trick--> float -> double
				CHCK_PARSER(callbacks->yajl_double(ctx, (double)(*((float*)&idx))));
			}
			break;
		case BJSN_CTE_TRUE:
			{
				CHCK_PARSER(callbacks->yajl_boolean(ctx, 1));
			}
			break;
		case BJSN_CTE_FALSE:
			{
				CHCK_PARSER(callbacks->yajl_boolean(ctx, 0));
			}
			break;
		case BJSN_CTE_NULL:
			{
				CHCK_PARSER(callbacks->yajl_null(ctx));
			}
			break;
		case BJSN_NUMBER_I8_RLE:
			{
				int idx  = (char)(*parse++);
				int count = parse[0]<<8 | parse[1];
				int n;
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx, idx));
				}
			}
			break;
		case BJSN_NUMBER_I16_RLE:
			{
				int count;
				int n;
				int idx  = (short)((parse[0] << 8) | parse[1]);
				parse += 2;
				count = parse[0]<<8 | parse[1];
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx, idx));
				}
			}
			break;
		case BJSN_NUMBER_I32_RLE:
			{
				int n;
				int count;
				int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				parse += 4;
				count = parse[0]<<8 | parse[1];
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx, idx));
				}
			}
			break;
		case BJSN_NUMBER_I64_RLE:
			{
				int count;
				int n;
				// MSB 32/64
				int idx  = (parse[0] << 24) | (parse[1] << 16) | (parse[2] << 8) | parse[3];
				unsigned int idx2 = (parse[4] << 24) | (parse[5] << 16) | (parse[6] << 8) | parse[7];
				long long int l64 = (((long long int)idx)<<32) | idx2;
				parse += 8;
				count = parse[0]<<8 | parse[1];
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx, l64));
				}
			}
			break;
		case BJSN_CTE_TRUE_RLE:
			{
				int n;
				int count = parse[0]<<8 | parse[1];
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_boolean(ctx, 1));
				}
			}
			break;
		case BJSN_CTE_FALSE_RLE:
			{
				int n;
				int count = parse[0]<<8 | parse[1];
				parse += 2;
				for (n=0; n < count; n++) {
					CHCK_PARSER_LOOP(callbacks->yajl_boolean(ctx, 0));
				}
			}
			break;
		default:
			error = BJSON_ERROR;
			goto exit;
		}
	}

exit:
	//
	// Free all allocated mem.
	//
	if (bjsn->cp_count) {
		if (bjsn->cp) {
			hand->alloc.free(hand->alloc.ctx, bjsn->cp);
			bjsn->cp = NULL;
		}

		if (bjsn->strs) {
			hand->alloc.free(hand->alloc.ctx, bjsn->strs);
			bjsn->strs = NULL;
		}
	}

	// Parse Post-CP
	return error;
}
