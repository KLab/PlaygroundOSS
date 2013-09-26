#include "api/yajl_parse.h"
#include "yajl_parser.h"


#define MSGPACK_NO_ERROR		(yajl_status_ok)
#define MSGPACK_CANCEL			(yajl_status_client_canceled)
#define MSGPACK_ERROR			(yajl_status_error)

#define MSG_PACK_nil				0xc0
#define MSG_PACK_reservedA 			0xc1
#define MSG_PACK_false 				0xc2
#define MSG_PACK_true 				0xc3
#define MSG_PACK_reservedB 			0xc4
#define MSG_PACK_reservedC 			0xc5
#define MSG_PACK_reservedD 			0xc6
#define MSG_PACK_reservedE 			0xc7
#define MSG_PACK_reservedF 			0xc8
#define MSG_PACK_reservedG 			0xc9
#define MSG_PACK_float 				0xca
#define MSG_PACK_double 			0xcb
#define MSG_PACK_uint_8 			0xcc
#define MSG_PACK_uint_16 			0xcd
#define MSG_PACK_uint_32 			0xce
#define MSG_PACK_uint_64 			0xcf
#define MSG_PACK_int_8 				0xd0
#define MSG_PACK_int_16 			0xd1
#define MSG_PACK_int_32 			0xd2
#define MSG_PACK_int_64 			0xd3
#define MSG_PACK_reservedH 			0xd4
#define MSG_PACK_reservedI 			0xd5
#define MSG_PACK_reservedJ 			0xd6
#define MSG_PACK_reservedK 			0xd7
#define MSG_PACK_reservedL 			0xd8
#define MSG_PACK_reservedM 			0xd9
#define MSG_PACK_raw_16 			0xda
#define MSG_PACK_raw_32 			0xdb
#define MSG_PACK_array_16 			0xdc
#define MSG_PACK_array_32 			0xdd
#define MSG_PACK_map_16 			0xde
#define MSG_PACK_map_32 			0xdf

#define CHCK_PARSER(x)		if (!(x)) { \
								error = MSGPACK_CANCEL; ptr = endPtr; \
							}

#define CHCK_PARSER_LOOP(x)	if (!(x)) { \
								error = MSGPACK_CANCEL; ptr = endPtr; break; \
							}

// ReserveA : Constant Pool
// ReserveB : Ref Constant Pool 8
// ReserveC : Ref Constant Pool 16
// ReserveD : PatternCount 16
int msgpack_parse(	yajl_handle		hand,
					const unsigned char*	jsonText,
					int						jsonTextLength
				)
{
	bjson_handle*	bjsn= &hand->msgpack;

	int error			= MSGPACK_NO_ERROR;
	const yajl_callbacks * callbacks = hand->callbacks;
	// cp_entry*	cp		= 0;
	void*		ctx		= bjsn->ctx;

	int	type;
	int currBlockType;
	int count;
	long long int longValue;
	int rle;
	unsigned char	c;
	unsigned int	stackCount	[100];
	unsigned char	stackType	[100];
	unsigned char	stackDepth	= 0;
	const unsigned char*	ptr			= jsonText;
	const unsigned char*	endPtr		= &jsonText[jsonTextLength];

	while (ptr != endPtr) {
	
	shortCut:
		c = *ptr++;
		
		if (c == MSG_PACK_reservedA) {
			rle	  = ((ptr[0]<<8) | (ptr[1]));
			ptr		+= 2;
			c = *ptr++;
		} else {
			rle	  = 1;
		}
		
		switch (c) {
		default:
			if (c < 0x80) {
				// 0x00..7F		: Positive Num
				count = c;
			} else {
				// 0xe0 - 0xff 	: Negative Num
				count = ((char)c);
			}
		performIntCall:
			do {
				CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx, count));
			} while (--rle);
			
			type = currBlockType;

			break;
		//
		// Fix Map 80-8F
		//
		case 0x80:
		case 0x81:
		case 0x82:
		case 0x83:
		case 0x84:
		case 0x85:
		case 0x86:
		case 0x87:
		case 0x88:
		case 0x89:
		case 0x8A:
		case 0x8B:
		case 0x8C:
		case 0x8D:
		case 0x8E:
		case 0x8F:
			count = c - 0x80;
			
			goto shortCut;
			
		//
		// Fix Array 90-9F
		//
		case 0x90:
		case 0x91:
		case 0x92:
		case 0x93:
		case 0x94:
		case 0x95:
		case 0x96:
		case 0x97:
		case 0x98:
		case 0x99:
		case 0x9A:
		case 0x9B:
		case 0x9C:
		case 0x9D:
		case 0x9E:
		case 0x9F:		
			count = c - 0x90;
			goto shortCut;
			
		//
		// Fix Raw A0-BF
		//
		case 0xA0:
		case 0xA1:
		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		case 0xA8:
		case 0xA9:
		case 0xAA:
		case 0xAB:
		case 0xAC:
		case 0xAD:
		case 0xAE:
		case 0xAF:
		case 0xB0:
		case 0xB1:
		case 0xB2:
		case 0xB3:
		case 0xB4:
		case 0xB5:
		case 0xB6:
		case 0xB7:
		case 0xB8:
		case 0xB9:
		case 0xBA:
		case 0xBB:
		case 0xBC:
		case 0xBD:
		case 0xBE:
		case 0xBF:
			count = c - 0xA0;
			break;
		case MSG_PACK_nil:
			do {
				CHCK_PARSER_LOOP(callbacks->yajl_null(ctx));
			} while (--rle);
			type = currBlockType;
			break;
		case MSG_PACK_reservedA	: // RLE Encoding
			// Do nothing here.
			break;
		case MSG_PACK_false 	: 
			do {
				CHCK_PARSER_LOOP(callbacks->yajl_boolean(ctx,0));	// False
			} while (--rle);
			type = currBlockType;
			break;
		case MSG_PACK_true 		: 
			do {
				CHCK_PARSER_LOOP(callbacks->yajl_boolean(ctx,1));	// True
			} while (--rle);
			type = currBlockType;
			break;
		case MSG_PACK_reservedB	: 
			break;
		case MSG_PACK_reservedC	: 
			break;
		case MSG_PACK_reservedD	: 
			break;
		case MSG_PACK_reservedE	: 
			break;
		case MSG_PACK_reservedF	: 
			break;
		case MSG_PACK_reservedG	: 
			break;
		case MSG_PACK_float 	: 
			count = (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			do {
				CHCK_PARSER_LOOP(callbacks->yajl_double(ctx,(double)(*((float*)(&count)))));	// Int -> Float raw memory -> Double.
			} while (--rle);
			type = currBlockType;
			break;
		case MSG_PACK_double 	: 
			count		= (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			longValue	= count;
			longValue  <<= 32;
			count		= (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			longValue	|= count;

			do {
				CHCK_PARSER_LOOP(callbacks->yajl_double(ctx,(*((double*)(&longValue)))));	// Int64 -> Double raw memory
			} while (--rle);
			type = currBlockType;
			break;
			
		case MSG_PACK_uint_8 	: 
			count = *ptr++;
			goto performIntCall;
			
		case MSG_PACK_uint_16 	: 
			count = (ptr[0]<<8) | ptr[1]; ptr+=2;
			goto performIntCall;
			
		case MSG_PACK_uint_32 	: 
			count		= (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			longValue	= (unsigned int)count;

			do {
				CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx,longValue));
			} while (--rle);
			type = currBlockType;
			break;
			
		case MSG_PACK_uint_64 	: 
		case MSG_PACK_int_64 	: 
			count		= (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			longValue	= count;
			longValue  <<= 32;
			count		= (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			longValue	|= count;

			do {
				CHCK_PARSER_LOOP(callbacks->yajl_integer(ctx,longValue));
			} while (--rle);
			type = currBlockType;
			break;
			
		case MSG_PACK_int_8 	: 
			count = (char)*ptr++;
			goto performIntCall;
			
		case MSG_PACK_int_16 	: 
			count = (short)((ptr[0]<<8) | ptr[1]); ptr+=2;
			goto performIntCall;
			
		case MSG_PACK_int_32 	: 
			count = (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			goto performIntCall;
			
		case MSG_PACK_reservedH	: 
		case MSG_PACK_reservedI	: 
		case MSG_PACK_reservedJ	: 
		case MSG_PACK_reservedK	: 
		case MSG_PACK_reservedL	: 
		case MSG_PACK_reservedM	: 
			break;
			
		case MSG_PACK_raw_16 	: 
			count = (short)((ptr[0]<<8) | ptr[1]); ptr+=2;
			if (type == 1) {
				// Key.
				CHCK_PARSER(callbacks->yajl_map_key(ctx,ptr,count,-1));
			} else {
				// String.
				CHCK_PARSER(callbacks->yajl_string(ctx,ptr,count,-1));
				type = currBlockType;
			}
			break;
		case MSG_PACK_raw_32 	: 
			count = (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			if (type == 1) {
				// Key.
				CHCK_PARSER(callbacks->yajl_map_key(ctx,ptr,count,-1));
			} else {
				// String.
				CHCK_PARSER(callbacks->yajl_string(ctx,ptr,count,-1));
				type = currBlockType;
			}
			break;
		case MSG_PACK_array_16 	: 
			count = (unsigned short)((ptr[0]<<8) | ptr[1]); ptr+=2;
			stackCount	[++stackDepth]	= count;
			stackType	[stackDepth]	= 1;
			CHCK_PARSER(callbacks->yajl_start_array(ctx, count));
			currBlockType = 1;
			goto shortCut;
		case MSG_PACK_array_32 	: 
			count = (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			stackCount[++stackDepth]	= (unsigned int)count;
			stackType	[stackDepth]	= 1;
			CHCK_PARSER(callbacks->yajl_start_array(ctx, (unsigned int)count));
			currBlockType = 1;
			goto shortCut;
		case MSG_PACK_map_16 	: 
			count = (unsigned short)((ptr[0]<<8) | ptr[1]); ptr+=2;
			stackCount[++stackDepth]	= (unsigned int)count;
			stackType	[stackDepth]	= 0;
			CHCK_PARSER(callbacks->yajl_start_map(ctx, count));
			currBlockType = 0;
			goto shortCut;
		case MSG_PACK_map_32 	: 
			count = (int)((ptr[0]<<24) | (ptr[1]<<16) | (ptr[2]<<8) | ptr[3]); ptr+=4;
			stackCount[++stackDepth]	= (unsigned int)count;
			stackType	[stackDepth]	= 0;
			CHCK_PARSER(callbacks->yajl_start_map(ctx, (unsigned int)count));
			currBlockType = 0;
			goto shortCut;
		}
		
		if ((stackDepth > 0) && ((--stackCount[stackDepth]) == 0)) {
			if (stackType[stackDepth] == 0) {
				CHCK_PARSER(callbacks->yajl_end_array(ctx));
			} else {
				CHCK_PARSER(callbacks->yajl_end_map(ctx));
			}
			stackDepth--;
			currBlockType = stackType[stackDepth];
			type = currBlockType;
		}
	}

	return error;
}
