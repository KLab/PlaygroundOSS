/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*  A Bison parser, made from csharp.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	THEN	258
#define	ELSE	259
#define	RANK_SPECIFIER	260
#define	IDENTIFIER	261
#define	INTEGER_LITERAL	262
#define	REAL_LITERAL	263
#define	CHARACTER_LITERAL	264
#define	STRING_LITERAL	265
#define	ABSTRACT	266
#define	AS	267
#define	BASE	268
#define	BOOL	269
#define	BREAK	270
#define	BYTE	271
#define	CASE	272
#define	CATCH	273
#define	CHAR	274
#define	CHECKED	275
#define	CLASS	276
#define	CONST	277
#define	CONTINUE	278
#define	DECIMAL	279
#define	DEFAULT	280
#define	DELEGATE	281
#define	DO	282
#define	DOUBLE	283
#define	ENUM	284
#define	EVENT	285
#define	EXPLICIT	286
#define	EXTERN	287
#define	FALSE	288
#define	FINALLY	289
#define	FIXED	290
#define	FLOAT	291
#define	FOR	292
#define	FOREACH	293
#define	GOTO	294
#define	IF	295
#define	IMPLICIT	296
#define	IN	297
#define	INT	298
#define	INTERFACE	299
#define	INTERNAL	300
#define	IS	301
#define	LOCK	302
#define	LONG	303
#define	NAMESPACE	304
#define	NEW	305
#define	NULL_LITERAL	306
#define	OPERATOR	307
#define	OUT	308
#define	OVERRIDE	309
#define	PARAMS	310
#define	PARTIAL	311
#define	PRIVATE	312
#define	PROTECTED	313
#define	PUBLIC	314
#define	READONLY	315
#define	REF	316
#define	RETURN	317
#define	SBYTE	318
#define	SEALED	319
#define	SHORT	320
#define	SIZEOF	321
#define	STACKALLOC	322
#define	STATIC	323
#define	STRUCT	324
#define	SWITCH	325
#define	THIS	326
#define	THROW	327
#define	TRUE	328
#define	TRY	329
#define	TYPEOF	330
#define	UINT	331
#define	ULONG	332
#define	UNCHECKED	333
#define	UNSAFE	334
#define	USHORT	335
#define	USING	336
#define	VIRTUAL	337
#define	VOID	338
#define	VOLATILE	339
#define	WHILE	340
#define	STRING	341
#define	OBJECT	342
#define	GEN_LT	343
#define	GEN_GT	344
#define	ASSEMBLY	345
#define	FIELD	346
#define	METHOD	347
#define	MODULE	348
#define	PARAM	349
#define	PROPERTY	350
#define	TYPE	351
#define	GET	352
#define	SET	353
#define	ADD	354
#define	REMOVE	355
#define	COMMA	356
#define	LEFT_BRACKET	357
#define	RIGHT_BRACKET	358
#define	GT	359
#define	GTGT	360
#define	LT	361
#define	PLUSEQ	362
#define	MINUSEQ	363
#define	STAREQ	364
#define	DIVEQ	365
#define	MODEQ	366
#define	XOREQ	367
#define	ANDEQ	368
#define	OREQ	369
#define	LTLT	370
#define	GTGTEQ	371
#define	LTLTEQ	372
#define	EQEQ	373
#define	NOTEQ	374
#define	LEQ	375
#define	GEQ	376
#define	ANDAND	377
#define	OROR	378
#define	PLUSPLUS	379
#define	MINUSMINUS	380
#define	ARROW	381

#line 32 "csharp.y"

#define YYERROR_VERBOSE
	extern int yylineno;
	#include "lex.yy.h"

	#include <stdio.h>
	#include <stdarg.h>
	#include <string.h>
	#include <stdlib.h>
	#include "y.tab.h"
	// Bring the standard library into the
	// global namespace
	
#ifdef _WIN32
	#define alloca
	#define VSPRINTF(buf, format, ...) vsprintf_s(buf, 1024, format, __VA_ARGS__ )
	#define SPRINTF(buf, format, ...) sprintf_s(buf, 1024, format, __VA_ARGS__ )
#else
	#define VSPRINTF(buf, format...) vsprintf(buf, format)
	#define SPRINTF(buf, format...) sprintf(buf, format)
#endif

	// Prototypes to keep the compiler happy
	void yyerror (const char *error);
	const char* makeUniqueId(const char* body);
	
	extern "C" {
		int yyparse(void);
		int yylex(void);
		int yywrap();
	}

	#include "include.h"

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#ifndef YYDEBUG
#define YYDEBUG 1
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		941
#define	YYFLAG		-32768
#define	YYNTBASE	146

#define YYTRANSLATE(x) ((unsigned)(x) <= 381 ? yytranslate[x] : 406)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   133,     2,     2,     2,   138,   132,     2,   129,
   130,   127,   135,     2,   136,   131,   137,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   128,   145,     2,
   142,     2,   141,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,   139,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   143,   140,   144,   134,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
   116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
   126
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
    20,    21,    22,    27,    28,    32,    34,    35,    40,    42,
    44,    46,    48,    50,    52,    54,    56,    58,    60,    62,
    64,    66,    68,    70,    72,    74,    76,    78,    80,    82,
    84,    87,    90,    93,    96,    99,   100,   103,   105,   107,
   109,   113,   115,   118,   121,   125,   127,   129,   131,   133,
   135,   137,   139,   141,   143,   145,   147,   149,   151,   153,
   155,   161,   165,   169,   173,   174,   181,   186,   187,   189,
   194,   199,   200,   202,   204,   208,   210,   214,   219,   222,
   225,   227,   233,   241,   245,   246,   248,   253,   258,   263,
   268,   272,   275,   280,   282,   284,   286,   288,   290,   292,
   295,   298,   300,   303,   306,   308,   311,   314,   317,   319,
   321,   323,   328,   334,   341,   347,   353,   354,   356,   358,
   361,   363,   365,   367,   371,   375,   379,   381,   385,   389,
   391,   395,   399,   401,   405,   409,   413,   417,   421,   425,
   427,   431,   435,   437,   441,   443,   447,   449,   453,   455,
   459,   461,   465,   467,   473,   477,   479,   481,   483,   485,
   487,   489,   491,   493,   495,   497,   499,   501,   503,   505,
   507,   509,   511,   513,   515,   517,   519,   521,   523,   525,
   527,   529,   531,   533,   535,   537,   539,   543,   544,   546,
   548,   551,   553,   557,   560,   563,   566,   568,   572,   574,
   578,   580,   582,   584,   590,   594,   596,   600,   604,   607,
   609,   611,   613,   615,   617,   619,   621,   623,   625,   629,
   634,   637,   638,   644,   648,   649,   651,   653,   656,   659,
   661,   664,   668,   671,   673,   675,   677,   679,   682,   688,
   696,   706,   707,   709,   710,   712,   713,   715,   717,   719,
   721,   723,   725,   729,   738,   740,   742,   744,   746,   748,
   751,   754,   758,   763,   767,   771,   772,   774,   778,   782,
   786,   791,   793,   796,   803,   806,   807,   809,   812,   815,
   818,   824,   830,   832,   834,   841,   843,   847,   851,   854,
   857,   858,   860,   861,   863,   864,   866,   867,   874,   875,
   877,   879,   882,   885,   889,   894,   896,   899,   901,   903,
   909,   913,   915,   918,   920,   922,   924,   926,   928,   930,
   932,   933,   935,   937,   940,   942,   944,   946,   948,   950,
   952,   954,   956,   958,   960,   962,   964,   966,   968,   970,
   971,   981,   982,   984,   987,   989,   993,   997,   998,  1000,
  1002,  1005,  1007,  1009,  1011,  1013,  1015,  1017,  1019,  1021,
  1023,  1025,  1032,  1038,  1041,  1050,  1059,  1061,  1065,  1066,
  1070,  1071,  1073,  1075,  1077,  1079,  1081,  1083,  1087,  1089,
  1091,  1097,  1098,  1101,  1102,  1104,  1106,  1111,  1121,  1124,
  1127,  1128,  1129,  1131,  1132,  1134,  1140,  1146,  1148,  1150,
  1157,  1168,  1171,  1174,  1180,  1186,  1195,  1201,  1207,  1210,
  1215,  1217,  1219,  1227,  1238,  1240,  1242,  1244,  1246,  1248,
  1250,  1252,  1254,  1256,  1258,  1260,  1262,  1264,  1266,  1268,
  1270,  1272,  1274,  1276,  1278,  1280,  1282,  1290,  1298,  1303,
  1309,  1310,  1312,  1318,  1324,  1332,  1334,  1336,  1338,  1340,
  1341,  1350,  1351,  1353,  1356,  1360,  1361,  1363,  1365,  1368,
  1370,  1372,  1374,  1376,  1378,  1380,  1382,  1384,  1386,  1387,
  1392,  1393,  1396,  1398,  1399,  1401,  1405,  1406,  1415,  1416,
  1418,  1421,  1425,  1426,  1428,  1430,  1433,  1435,  1437,  1439,
  1441,  1450,  1459,  1460,  1462,  1472,  1485,  1489,  1493,  1500,
  1507,  1514,  1516,  1519,  1520,  1529,  1530,  1532,  1535,  1539,
  1544,  1545,  1547,  1549,  1553,  1556,  1561,  1572,  1574,  1576,
  1579,  1586,  1594,  1595,  1597,  1600,  1602,  1604,  1606,  1608,
  1610,  1612,  1614,  1616,  1618,  1620,  1624,  1627,  1628,  1630,
  1632,  1636,  1637,  1638,  1639,  1640,  1641
};

static const short yyrhs[] = {   147,
     0,     7,     0,     8,     0,     9,     0,    10,     0,    51,
     0,    73,     0,    33,     0,   289,     0,   152,     0,     0,
     0,    88,   151,   154,    89,     0,     0,   289,   153,   150,
     0,   156,     0,     0,   156,   101,   155,   154,     0,   157,
     0,   164,     0,   158,     0,   149,     0,   159,     0,   163,
     0,   160,     0,    14,     0,   161,     0,   162,     0,    24,
     0,    63,     0,    16,     0,    65,     0,    80,     0,    43,
     0,    76,     0,    48,     0,    77,     0,    19,     0,    36,
     0,    28,     0,   156,   127,     0,    83,   127,     0,   164,
   166,     0,   158,   166,     0,   289,   166,     0,     0,   166,
   165,     0,     5,     0,   217,     0,   169,     0,   168,   101,
   169,     0,   217,     0,    61,   167,     0,    53,   167,     0,
     6,   128,   169,     0,   173,     0,   171,     0,   146,     0,
   187,     0,   174,     0,   175,     0,   178,     0,   181,     0,
   182,     0,   185,     0,   172,     0,   189,     0,   194,     0,
   190,     0,   191,     0,    26,   129,   317,   130,   222,     0,
   129,   217,   130,     0,   170,   131,     6,     0,   159,   131,
     6,     0,     0,   171,   150,   129,   176,   177,   130,     0,
   152,   129,   177,   130,     0,     0,   168,     0,   170,   102,
   180,   103,     0,   289,   102,   180,   103,     0,     0,   180,
     0,   217,     0,   180,   101,   217,     0,    71,     0,    13,
   131,     6,     0,    13,   102,   180,   103,     0,   195,   124,
     0,   195,   125,     0,   186,     0,    50,   156,   129,   177,
   130,     0,    50,   157,   102,   180,   103,   165,   188,     0,
    50,   164,   360,     0,     0,   360,     0,    75,   129,   156,
   130,     0,    75,   129,    83,   130,     0,    20,   129,   217,
   130,     0,    78,   129,   217,   130,     0,   195,   126,     6,
     0,   132,   199,     0,    66,   129,   156,   130,     0,   170,
     0,   289,     0,   183,     0,   184,     0,   192,     0,   195,
     0,   133,   199,     0,   134,   199,     0,   200,     0,   124,
   199,     0,   125,   199,     0,   196,     0,   135,   199,     0,
   136,   199,     0,   127,   199,     0,   197,     0,   198,     0,
   193,     0,   129,   217,   130,   196,     0,   129,   204,   127,
   130,   199,     0,   129,   289,   166,   201,   130,   199,     0,
   129,   159,   201,   130,   199,     0,   129,    83,   201,   130,
   199,     0,     0,   202,     0,   203,     0,   202,   203,     0,
   166,     0,   127,     0,   199,     0,   204,   127,   199,     0,
   204,   137,   199,     0,   204,   138,   199,     0,   204,     0,
   205,   135,   204,     0,   205,   136,   204,     0,   205,     0,
   206,   115,   205,     0,   206,   105,   205,     0,   206,     0,
   207,   106,   206,     0,   207,   104,   206,     0,   207,   120,
   206,     0,   207,   121,   206,     0,   207,    46,   156,     0,
   207,    12,   156,     0,   207,     0,   208,   118,   207,     0,
   208,   119,   207,     0,   208,     0,   209,   132,   208,     0,
   209,     0,   210,   139,   209,     0,   210,     0,   211,   140,
   210,     0,   211,     0,   212,   122,   211,     0,   212,     0,
   213,   123,   212,     0,   213,     0,   213,   141,   217,   128,
   217,     0,   199,   216,   217,     0,   142,     0,   107,     0,
   108,     0,   109,     0,   110,     0,   111,     0,   112,     0,
   113,     0,   114,     0,   116,     0,   117,     0,   214,     0,
   215,     0,   217,     0,   217,     0,   226,     0,   227,     0,
   221,     0,   222,     0,   225,     0,   236,     0,   238,     0,
   249,     0,   262,     0,   269,     0,   274,     0,   275,     0,
   276,     0,   277,     0,   250,     0,   279,     0,   143,   223,
   144,     0,     0,   224,     0,   220,     0,   224,   220,     0,
   145,     0,     6,   128,   220,     0,   228,   145,     0,   233,
   145,     0,   156,   229,     0,   230,     0,   229,   101,   230,
     0,     6,     0,     6,   142,   231,     0,   217,     0,   360,
     0,   232,     0,    67,   156,   102,   217,   103,     0,    22,
   156,   234,     0,   235,     0,   234,   101,   235,     0,     6,
   142,   218,     0,   237,   145,     0,   175,     0,   186,     0,
   215,     0,   183,     0,   184,     0,   197,     0,   198,     0,
   239,     0,   242,     0,    40,   240,   241,     0,   129,   219,
   130,   221,     0,     4,   221,     0,     0,    70,   129,   217,
   130,   243,     0,   143,   244,   144,     0,     0,   245,     0,
   246,     0,   245,   246,     0,   247,   224,     0,   248,     0,
   247,   248,     0,    17,   218,   128,     0,    25,   128,     0,
   251,     0,   252,     0,   253,     0,   261,     0,    79,   222,
     0,    85,   129,   219,   130,   221,     0,    27,   221,    85,
   129,   219,   130,   145,     0,    37,   129,   254,   145,   255,
   145,   256,   130,   221,     0,     0,   257,     0,     0,   258,
     0,     0,   259,     0,   228,     0,   260,     0,   219,     0,
   260,     0,   237,     0,   260,   101,   237,     0,    38,   129,
   156,     6,    42,   217,   130,   221,     0,   263,     0,   264,
     0,   265,     0,   266,     0,   268,     0,    15,   145,     0,
    23,   145,     0,    39,     6,   145,     0,    39,    17,   218,
   145,     0,    39,    25,   145,     0,    62,   267,   145,     0,
     0,   217,     0,    72,   267,   145,     0,    74,   222,   270,
     0,    74,   222,   273,     0,    74,   222,   270,   273,     0,
   271,     0,   270,   271,     0,    18,   129,   149,   272,   130,
   222,     0,    18,   222,     0,     0,     6,     0,    34,   222,
     0,    20,   222,     0,    78,   222,     0,    47,   129,   217,
   130,   221,     0,    81,   129,   278,   130,   221,     0,   228,
     0,   217,     0,    35,   129,   156,   280,   130,   221,     0,
   281,     0,   280,   101,   281,     0,     6,   142,   217,     0,
   283,   284,     0,   283,   296,     0,     0,   292,     0,     0,
   389,     0,     0,   296,     0,     0,   284,    49,   289,   287,
   291,   288,     0,     0,   145,     0,     6,     0,   290,     6,
     0,     6,   131,     0,   290,     6,   131,     0,   143,   283,
   285,   144,     0,   293,     0,   292,   293,     0,   294,     0,
   295,     0,    81,     6,   142,   289,   145,     0,    81,   148,
   145,     0,   297,     0,   296,   297,     0,   286,     0,   298,
     0,   302,     0,   352,     0,   365,     0,   380,     0,   388,
     0,     0,   300,     0,   301,     0,   300,   301,     0,    11,
     0,    32,     0,    45,     0,    50,     0,    54,     0,    57,
     0,    58,     0,    59,     0,    60,     0,    64,     0,    68,
     0,    79,     0,    82,     0,    84,     0,    56,     0,     0,
   284,   299,    21,     6,   316,   303,   304,   307,   288,     0,
     0,   305,     0,   128,   306,     0,   149,     0,   306,   101,
   149,     0,   143,   308,   144,     0,     0,   309,     0,   310,
     0,   309,   310,     0,   311,     0,   312,     0,   313,     0,
   326,     0,   333,     0,   337,     0,   340,     0,   345,     0,
   349,     0,   298,     0,   284,   299,    22,   156,   234,   145,
     0,   284,   299,   156,   229,   145,     0,   314,   319,     0,
   284,   299,   156,   289,   316,   129,   317,   130,     0,   284,
   299,    83,   289,   316,   129,   317,   130,     0,     6,     0,
   315,   101,     6,     0,     0,    88,   315,    89,     0,     0,
   320,     0,   156,     0,    83,     0,   222,     0,   145,     0,
   321,     0,   320,   101,   321,     0,   322,     0,   325,     0,
   284,   324,   156,     6,   323,     0,     0,   142,   217,     0,
     0,    61,     0,    53,     0,   284,    55,   156,     6,     0,
   284,   299,   156,   289,   404,   143,   327,   144,   405,     0,
   330,   328,     0,   331,   329,     0,     0,     0,   331,     0,
     0,   330,     0,   284,    97,   405,   332,   404,     0,   284,
    98,   405,   332,   404,     0,   222,     0,   145,     0,   284,
   299,    30,   156,   229,   145,     0,   284,   299,    30,   156,
   289,   402,   143,   334,   144,   403,     0,   335,   336,     0,
   336,   335,     0,   284,    99,   403,   222,   402,     0,   284,
   100,   403,   222,   402,     0,   284,   299,   338,   404,   143,
   327,   144,   405,     0,   156,    71,   102,   320,   103,     0,
   156,   339,   102,   320,   103,     0,   290,    71,     0,   284,
   299,   341,   350,     0,   342,     0,   344,     0,   156,    52,
   343,   129,   156,     6,   130,     0,   156,    52,   343,   129,
   156,     6,   101,   156,     6,   130,     0,   135,     0,   136,
     0,   133,     0,   134,     0,   124,     0,   125,     0,    73,
     0,    33,     0,   127,     0,   137,     0,   138,     0,   132,
     0,   140,     0,   139,     0,   115,     0,   105,     0,   118,
     0,   119,     0,   104,     0,   106,     0,   121,     0,   120,
     0,    41,    52,   156,   129,   156,     6,   130,     0,    31,
    52,   156,   129,   156,     6,   130,     0,   284,   299,   346,
   351,     0,     6,   129,   317,   130,   347,     0,     0,   348,
     0,   128,    13,   129,   177,   130,     0,   128,    71,   129,
   177,   130,     0,   284,   299,   134,     6,   129,   130,   222,
     0,   222,     0,   145,     0,   222,     0,   145,     0,     0,
   284,   299,    69,     6,   353,   354,   356,   288,     0,     0,
   355,     0,   128,   306,     0,   143,   357,   144,     0,     0,
   358,     0,   359,     0,   358,   359,     0,   311,     0,   312,
     0,   313,     0,   326,     0,   333,     0,   337,     0,   340,
     0,   345,     0,   298,     0,     0,   143,   361,   362,   144,
     0,     0,   364,   363,     0,   101,     0,     0,   231,     0,
   364,   101,   231,     0,     0,   284,   299,    44,     6,   366,
   367,   369,   288,     0,     0,   368,     0,   128,   306,     0,
   143,   370,   144,     0,     0,   371,     0,   372,     0,   371,
   372,     0,   373,     0,   375,     0,   378,     0,   376,     0,
   284,   374,   156,     6,   129,   317,   130,   379,     0,   284,
   374,    83,     6,   129,   317,   130,   379,     0,     0,    50,
     0,   284,   374,   156,     6,   404,   143,   377,   144,   405,
     0,   284,   374,   156,    71,   102,   320,   103,   404,   143,
   377,   144,   405,     0,   284,    97,   379,     0,   284,    98,
   379,     0,   284,    97,   379,   284,    98,   379,     0,   284,
    98,   379,   284,    97,   379,     0,   284,   374,    30,   156,
     6,   379,     0,   145,     0,   143,   144,     0,     0,   284,
   299,    29,     6,   382,   381,   384,   288,     0,     0,   383,
     0,   128,   161,     0,   143,   385,   144,     0,   143,   386,
   101,   144,     0,     0,   386,     0,   387,     0,   386,   101,
   387,     0,   284,     6,     0,   284,     6,   142,   218,     0,
   284,   299,    26,   318,     6,   316,   129,   317,   130,   145,
     0,   390,     0,   391,     0,   390,   391,     0,   400,   102,
   392,   395,   103,   401,     0,   400,   102,   392,   395,   101,
   103,   401,     0,     0,   393,     0,   394,   128,     0,    90,
     0,    91,     0,    30,     0,    92,     0,    93,     0,    94,
     0,    95,     0,    62,     0,    96,     0,   396,     0,   395,
   101,   396,     0,   398,   397,     0,     0,   399,     0,   149,
     0,   129,   179,   130,     0,     0,     0,     0,     0,     0,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   127,   128,   129,   130,   131,   132,   135,   136,   146,   149,
   156,   157,   159,   165,   165,   169,   170,   171,   183,   184,
   187,   188,   191,   192,   195,   196,   199,   200,   201,   204,
   205,   206,   207,   208,   209,   210,   211,   212,   215,   216,
   219,   220,   223,   224,   225,   229,   230,   234,   242,   246,
   247,   250,   251,   252,   253,   256,   257,   260,   261,   262,
   263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
   276,   280,   283,   284,   287,   287,   288,   291,   292,   295,
   296,   300,   301,   305,   306,   309,   312,   313,   316,   319,
   322,   325,   328,   330,   333,   334,   337,   338,   341,   344,
   347,   350,   353,   356,   357,   358,   359,   360,   363,   364,
   365,   366,   369,   372,   375,   376,   377,   378,   379,   380,
   381,   389,   392,   395,   399,   404,   411,   412,   415,   416,
   419,   420,   424,   425,   426,   427,   430,   431,   432,   435,
   436,   437,   440,   441,   442,   443,   444,   445,   446,   449,
   450,   451,   454,   455,   458,   459,   462,   463,   466,   467,
   470,   471,   474,   475,   477,   480,   481,   482,   483,   484,
   485,   486,   487,   488,   489,   490,   494,   495,   498,   501,
   516,   517,   518,   521,   522,   523,   524,   525,   526,   527,
   528,   529,   530,   531,   532,   533,   536,   539,   540,   544,
   545,   548,   551,   554,   555,   558,   561,   562,   565,   566,
   569,   570,   571,   574,   577,   580,   581,   584,   587,   590,
   591,   592,   593,   594,   595,   596,   599,   600,   605,   617,
   620,   621,   625,   628,   631,   632,   635,   636,   639,   642,
   643,   646,   647,   650,   651,   652,   653,   656,   659,   663,
   667,   674,   675,   678,   679,   682,   683,   686,   687,   690,
   693,   696,   697,   700,   790,   791,   792,   793,   794,   797,
   800,   803,   804,   805,   808,   811,   812,   815,   818,   821,
   824,   830,   831,   834,   837,   840,   841,   844,   847,   850,
   853,   858,   862,   863,   867,   871,   872,   875,   884,   885,
   888,   889,   892,   893,   896,   897,   900,   900,   905,   906,
   915,   916,   919,   920,   924,   927,   928,   931,   932,   935,
   938,   941,   942,   945,   946,   949,   950,   951,   952,   953,
   964,   965,   968,   969,   972,   973,   974,   975,   976,   977,
   978,   979,   980,   981,   982,   983,   984,   985,   986,   990,
   997,  1001,  1002,  1005,  1008,  1009,  1012,  1015,  1016,  1019,
  1020,  1023,  1024,  1025,  1026,  1027,  1028,  1029,  1030,  1031,
  1033,  1036,  1041,  1044,  1057,  1063,  1072,  1073,  1076,  1077,
  1081,  1082,  1085,  1086,  1089,  1090,  1093,  1094,  1097,  1098,
  1101,  1109,  1110,  1113,  1114,  1115,  1119,  1127,  1133,  1134,
  1135,  1138,  1139,  1142,  1143,  1146,  1152,  1158,  1159,  1162,
  1163,  1169,  1170,  1173,  1179,  1185,  1195,  1197,  1200,  1204,
  1207,  1208,  1211,  1212,  1215,  1216,  1217,  1218,  1219,  1220,
  1221,  1222,  1223,  1224,  1225,  1226,  1227,  1228,  1229,  1230,
  1231,  1232,  1233,  1234,  1235,  1236,  1240,  1241,  1244,  1257,
  1264,  1265,  1268,  1269,  1285,  1295,  1296,  1299,  1300,  1305,
  1310,  1313,  1314,  1317,  1320,  1323,  1324,  1327,  1328,  1331,
  1332,  1333,  1334,  1335,  1336,  1337,  1338,  1340,  1345,  1345,
  1348,  1349,  1352,  1353,  1357,  1358,  1363,  1367,  1371,  1372,
  1375,  1378,  1381,  1382,  1385,  1386,  1389,  1390,  1391,  1392,
  1396,  1406,  1418,  1419,  1422,  1428,  1436,  1437,  1438,  1439,
  1442,  1447,  1448,  1453,  1455,  1460,  1461,  1464,  1467,  1468,
  1471,  1472,  1475,  1476,  1479,  1480,  1485,  1491,  1494,  1495,
  1498,  1500,  1504,  1505,  1508,  1511,  1512,  1513,  1514,  1515,
  1516,  1517,  1518,  1519,  1522,  1523,  1526,  1529,  1530,  1533,
  1536,  1543,  1546,  1549,  1552,  1555,  1558
};

static const char * const yytname[] = {   "$","error","$undefined.","THEN","ELSE",
"RANK_SPECIFIER","IDENTIFIER","INTEGER_LITERAL","REAL_LITERAL","CHARACTER_LITERAL",
"STRING_LITERAL","ABSTRACT","AS","BASE","BOOL","BREAK","BYTE","CASE","CATCH",
"CHAR","CHECKED","CLASS","CONST","CONTINUE","DECIMAL","DEFAULT","DELEGATE","DO",
"DOUBLE","ENUM","EVENT","EXPLICIT","EXTERN","FALSE","FINALLY","FIXED","FLOAT",
"FOR","FOREACH","GOTO","IF","IMPLICIT","IN","INT","INTERFACE","INTERNAL","IS",
"LOCK","LONG","NAMESPACE","NEW","NULL_LITERAL","OPERATOR","OUT","OVERRIDE","PARAMS",
"PARTIAL","PRIVATE","PROTECTED","PUBLIC","READONLY","REF","RETURN","SBYTE","SEALED",
"SHORT","SIZEOF","STACKALLOC","STATIC","STRUCT","SWITCH","THIS","THROW","TRUE",
"TRY","TYPEOF","UINT","ULONG","UNCHECKED","UNSAFE","USHORT","USING","VIRTUAL",
"VOID","VOLATILE","WHILE","STRING","OBJECT","GEN_LT","GEN_GT","ASSEMBLY","FIELD",
"METHOD","MODULE","PARAM","PROPERTY","TYPE","GET","SET","ADD","REMOVE","COMMA",
"LEFT_BRACKET","RIGHT_BRACKET","GT","GTGT","LT","PLUSEQ","MINUSEQ","STAREQ",
"DIVEQ","MODEQ","XOREQ","ANDEQ","OREQ","LTLT","GTGTEQ","LTLTEQ","EQEQ","NOTEQ",
"LEQ","GEQ","ANDAND","OROR","PLUSPLUS","MINUSMINUS","ARROW","'*'","':'","'('",
"')'","'.'","'&'","'!'","'~'","'+'","'-'","'/'","'%'","'^'","'|'","'?'","'='",
"'{'","'}'","';'","literal","boolean_literal","namespace_name","type_name","opt_generic",
"@1","qualified_identifier_opt_generic","@2","genericlist","@3","type","non_array_type",
"simple_type","primitive_type","numeric_type","integral_type","floating_point_type",
"pointer_type","array_type","rank_specifiers_opt","rank_specifier","variable_reference",
"argument_list","argument","primary_expression","primary_expression_no_parenthesis",
"delegate_expression","parenthesized_expression","member_access","invocation_expression",
"@4","argument_list_opt","element_access","expression_list_opt","expression_list",
"this_access","base_access","post_increment_expression","post_decrement_expression",
"new_expression","object_creation_expression","array_creation_expression","array_initializer_opt",
"typeof_expression","checked_expression","unchecked_expression","pointer_member_access",
"addressof_expression","sizeof_expression","postfix_expression","unary_expression_not_plusminus",
"pre_increment_expression","pre_decrement_expression","unary_expression","cast_expression",
"type_quals_opt","type_quals","type_qual","multiplicative_expression","additive_expression",
"shift_expression","relational_expression","equality_expression","and_expression",
"exclusive_or_expression","inclusive_or_expression","conditional_and_expression",
"conditional_or_expression","conditional_expression","assignment","assignment_operator",
"expression","constant_expression","boolean_expression","statement","embedded_statement",
"block","statement_list_opt","statement_list","empty_statement","labeled_statement",
"declaration_statement","local_variable_declaration","variable_declarators",
"variable_declarator","variable_initializer","stackalloc_initializer","local_constant_declaration",
"constant_declarators","constant_declarator","expression_statement","statement_expression",
"selection_statement","if_statement","ifpart","opt_else","switch_statement",
"switch_block","switch_sections_opt","switch_sections","switch_section","switch_labels",
"switch_label","iteration_statement","unsafe_statement","while_statement","do_statement",
"for_statement","for_initializer_opt","for_condition_opt","for_iterator_opt",
"for_initializer","for_condition","for_iterator","statement_expression_list",
"foreach_statement","jump_statement","break_statement","continue_statement",
"goto_statement","return_statement","expression_opt","throw_statement","try_statement",
"catch_clauses","catch_clause","identifier_opt","finally_clause","checked_statement",
"unchecked_statement","lock_statement","using_statement","resource_acquisition",
"fixed_statement","fixed_pointer_declarators","fixed_pointer_declarator","compilation_unit",
"using_directives_opt","attributes_opt","namespace_member_declarations_opt",
"namespace_declaration","@5","comma_opt","qualified_identifier","qualifier",
"namespace_body","using_directives","using_directive","using_alias_directive",
"using_namespace_directive","namespace_member_declarations","namespace_member_declaration",
"type_declaration","modifiers_opt","modifiers","modifier","class_declaration",
"@6","class_base_opt","class_base","interface_type_list","class_body","class_member_declarations_opt",
"class_member_declarations","class_member_declaration","constant_declaration",
"field_declaration","method_declaration","method_header","name_list","opt_generic_fct",
"formal_parameter_list_opt","return_type","method_body","formal_parameter_list",
"formal_parameter","fixed_parameter","fixed_parameter_opt_default","parameter_modifier_opt",
"parameter_array","property_declaration","accessor_declarations","set_accessor_declaration_opt",
"get_accessor_declaration_opt","get_accessor_declaration","set_accessor_declaration",
"accessor_body","event_declaration","event_accessor_declarations","add_accessor_declaration",
"remove_accessor_declaration","indexer_declaration","indexer_declarator","qualified_this",
"operator_declaration","operator_declarator","overloadable_operator_declarator",
"overloadable_operator","conversion_operator_declarator","constructor_declaration",
"constructor_declarator","constructor_initializer_opt","constructor_initializer",
"destructor_declaration","operator_body","constructor_body","struct_declaration",
"@7","struct_interfaces_opt","struct_interfaces","struct_body","struct_member_declarations_opt",
"struct_member_declarations","struct_member_declaration","array_initializer",
"@8","variable_initializer_list_opt","opt_comma","variable_initializer_list",
"interface_declaration","@9","interface_base_opt","interface_base","interface_body",
"interface_member_declarations_opt","interface_member_declarations","interface_member_declaration",
"interface_method_declaration","new_opt","interface_property_declaration","interface_indexer_declaration",
"interface_accessors","interface_event_declaration","interface_empty_body","enum_declaration",
"@10","enum_base_opt","enum_base","enum_body","enum_member_declarations_opt",
"enum_member_declarations","enum_member_declaration","delegate_declaration",
"attributes","attribute_sections","attribute_section","attribute_target_specifier_opt",
"attribute_target_specifier","attribute_target","attribute_list","attribute",
"attribute_arguments_opt","attribute_name","attribute_arguments","ENTER_attrib",
"EXIT_attrib","ENTER_accessor_decl","EXIT_accessor_decl","ENTER_getset","EXIT_getset",
""
};
#endif

static const short yyr1[] = {     0,
   146,   146,   146,   146,   146,   146,   147,   147,   148,   149,
   150,   151,   150,   153,   152,   154,   155,   154,   156,   156,
   157,   157,   158,   158,   159,   159,   160,   160,   160,   161,
   161,   161,   161,   161,   161,   161,   161,   161,   162,   162,
   163,   163,   164,   164,   164,   165,   165,   166,   167,   168,
   168,   169,   169,   169,   169,   170,   170,   171,   171,   171,
   171,   171,   171,   171,   171,   171,   171,   171,   171,   171,
   172,   173,   174,   174,   176,   175,   175,   177,   177,   178,
   178,   179,   179,   180,   180,   181,   182,   182,   183,   184,
   185,   186,   187,   187,   188,   188,   189,   189,   190,   191,
   192,   193,   194,   195,   195,   195,   195,   195,   196,   196,
   196,   196,   197,   198,   199,   199,   199,   199,   199,   199,
   199,   200,   200,   200,   200,   200,   201,   201,   202,   202,
   203,   203,   204,   204,   204,   204,   205,   205,   205,   206,
   206,   206,   207,   207,   207,   207,   207,   207,   207,   208,
   208,   208,   209,   209,   210,   210,   211,   211,   212,   212,
   213,   213,   214,   214,   215,   216,   216,   216,   216,   216,
   216,   216,   216,   216,   216,   216,   217,   217,   218,   219,
   220,   220,   220,   221,   221,   221,   221,   221,   221,   221,
   221,   221,   221,   221,   221,   221,   222,   223,   223,   224,
   224,   225,   226,   227,   227,   228,   229,   229,   230,   230,
   231,   231,   231,   232,   233,   234,   234,   235,   236,   237,
   237,   237,   237,   237,   237,   237,   238,   238,   239,   240,
   241,   241,   242,   243,   244,   244,   245,   245,   246,   247,
   247,   248,   248,   249,   249,   249,   249,   250,   251,   252,
   253,   254,   254,   255,   255,   256,   256,   257,   257,   258,
   259,   260,   260,   261,   262,   262,   262,   262,   262,   263,
   264,   265,   265,   265,   266,   267,   267,   268,   269,   269,
   269,   270,   270,   271,   271,   272,   272,   273,   274,   275,
   276,   277,   278,   278,   279,   280,   280,   281,   282,   282,
   283,   283,   284,   284,   285,   285,   287,   286,   288,   288,
   289,   289,   290,   290,   291,   292,   292,   293,   293,   294,
   295,   296,   296,   297,   297,   298,   298,   298,   298,   298,
   299,   299,   300,   300,   301,   301,   301,   301,   301,   301,
   301,   301,   301,   301,   301,   301,   301,   301,   301,   303,
   302,   304,   304,   305,   306,   306,   307,   308,   308,   309,
   309,   310,   310,   310,   310,   310,   310,   310,   310,   310,
   310,   311,   312,   313,   314,   314,   315,   315,   316,   316,
   317,   317,   318,   318,   319,   319,   320,   320,   321,   321,
   322,   323,   323,   324,   324,   324,   325,   326,   327,   327,
   327,   328,   328,   329,   329,   330,   331,   332,   332,   333,
   333,   334,   334,   335,   336,   337,   338,   338,   339,   340,
   341,   341,   342,   342,   343,   343,   343,   343,   343,   343,
   343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
   343,   343,   343,   343,   343,   343,   344,   344,   345,   346,
   347,   347,   348,   348,   349,   350,   350,   351,   351,   353,
   352,   354,   354,   355,   356,   357,   357,   358,   358,   359,
   359,   359,   359,   359,   359,   359,   359,   359,   361,   360,
   362,   362,   363,   363,   364,   364,   366,   365,   367,   367,
   368,   369,   370,   370,   371,   371,   372,   372,   372,   372,
   373,   373,   374,   374,   375,   376,   377,   377,   377,   377,
   378,   379,   379,   381,   380,   382,   382,   383,   384,   384,
   385,   385,   386,   386,   387,   387,   388,   389,   390,   390,
   391,   391,   392,   392,   393,   394,   394,   394,   394,   394,
   394,   394,   394,   394,   395,   395,   396,   397,   397,   398,
   399,   400,   401,   402,   403,   404,   405
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     0,     0,     4,     0,     3,     1,     0,     4,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     2,     2,     2,     2,     2,     0,     2,     1,     1,     1,
     3,     1,     2,     2,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     5,     3,     3,     3,     0,     6,     4,     0,     1,     4,
     4,     0,     1,     1,     3,     1,     3,     4,     2,     2,
     1,     5,     7,     3,     0,     1,     4,     4,     4,     4,
     3,     2,     4,     1,     1,     1,     1,     1,     1,     2,
     2,     1,     2,     2,     1,     2,     2,     2,     1,     1,
     1,     4,     5,     6,     5,     5,     0,     1,     1,     2,
     1,     1,     1,     3,     3,     3,     1,     3,     3,     1,
     3,     3,     1,     3,     3,     3,     3,     3,     3,     1,
     3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
     1,     3,     1,     5,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     3,     0,     1,     1,
     2,     1,     3,     2,     2,     2,     1,     3,     1,     3,
     1,     1,     1,     5,     3,     1,     3,     3,     2,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     3,     4,
     2,     0,     5,     3,     0,     1,     1,     2,     2,     1,
     2,     3,     2,     1,     1,     1,     1,     2,     5,     7,
     9,     0,     1,     0,     1,     0,     1,     1,     1,     1,
     1,     1,     3,     8,     1,     1,     1,     1,     1,     2,
     2,     3,     4,     3,     3,     0,     1,     3,     3,     3,
     4,     1,     2,     6,     2,     0,     1,     2,     2,     2,
     5,     5,     1,     1,     6,     1,     3,     3,     2,     2,
     0,     1,     0,     1,     0,     1,     0,     6,     0,     1,
     1,     2,     2,     3,     4,     1,     2,     1,     1,     5,
     3,     1,     2,     1,     1,     1,     1,     1,     1,     1,
     0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
     9,     0,     1,     2,     1,     3,     3,     0,     1,     1,
     2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     6,     5,     2,     8,     8,     1,     3,     0,     3,
     0,     1,     1,     1,     1,     1,     1,     3,     1,     1,
     5,     0,     2,     0,     1,     1,     4,     9,     2,     2,
     0,     0,     1,     0,     1,     5,     5,     1,     1,     6,
    10,     2,     2,     5,     5,     8,     5,     5,     2,     4,
     1,     1,     7,    10,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     7,     7,     4,     5,
     0,     1,     5,     5,     7,     1,     1,     1,     1,     0,
     8,     0,     1,     2,     3,     0,     1,     1,     2,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
     0,     2,     1,     0,     1,     3,     0,     8,     0,     1,
     2,     3,     0,     1,     1,     2,     1,     1,     1,     1,
     8,     8,     0,     1,     9,    12,     3,     3,     6,     6,
     6,     1,     2,     0,     8,     0,     1,     2,     3,     4,
     0,     1,     1,     3,     2,     4,    10,     1,     1,     2,
     6,     7,     0,     1,     2,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     3,     2,     0,     1,     1,
     3,     0,     0,     0,     0,     0,     0
};

static const short yydefact[] = {   301,
     0,   303,   302,   316,   318,   319,   311,     0,     9,     0,
   331,   324,   303,   322,   325,   326,   327,   328,   329,   330,
   304,   528,   529,     0,   317,   313,     0,   321,   312,   335,
   336,   337,     0,   338,   339,   349,   340,   341,   342,   343,
   344,   345,   346,   347,   348,     0,   332,   333,   331,   323,
   530,   533,   311,     0,   314,   307,     0,     0,     0,     0,
     0,   334,   538,   543,   536,   537,   539,   540,   541,   542,
   544,     0,   534,     0,   320,     0,   379,    26,    31,    38,
    29,    40,    39,    34,    36,    30,    32,    35,    37,    33,
   384,    22,    10,   383,    19,    21,    23,    25,    27,    28,
    24,    20,    14,     0,   516,   487,   460,   550,    14,     0,
   545,   548,   535,   301,   309,     0,   350,    42,    41,    48,
    44,    43,    11,    45,   379,     0,   514,   517,   489,   462,
     0,   553,    82,   547,   549,   303,   310,   308,   377,     0,
   352,    12,    15,     0,   518,     0,     0,     0,   490,     0,
     0,   463,   553,   546,   531,     2,     3,     4,     5,     0,
     0,     0,     8,     0,     6,     0,    86,     7,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    58,
     1,     0,     0,   104,    57,    66,    56,    60,    61,    62,
     0,    83,    63,    64,   106,   107,    65,    91,    59,    67,
    69,    70,   108,   121,    68,   109,   115,   119,   120,   133,
   112,   137,   140,   143,   150,   153,   155,   157,   159,   161,
   163,   177,   178,    84,   105,     0,   303,   380,     0,     0,
     0,   353,     0,   303,   303,   309,   355,   491,   303,   309,
   464,   303,   309,   532,     0,     0,     0,   303,     0,     0,
    19,    20,     0,     0,     0,   113,   114,   118,   127,   127,
   137,     0,   105,   102,   110,   111,   116,   117,    78,     0,
     0,     0,     0,   551,     0,    89,    90,     0,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   166,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   315,   378,   354,   303,   309,     0,    16,   394,
     0,   382,   387,   389,   390,     0,     0,   522,   523,   515,
     0,   503,     0,   303,   495,   497,   498,   500,   499,   488,
   331,   478,   470,   471,   472,     0,   473,   474,   475,   476,
   477,     0,   303,   468,   461,     0,    87,     0,     0,    78,
     0,   479,    94,     0,     0,     0,     0,   132,   131,     0,
   128,   129,     0,     0,    72,   127,   311,     0,     0,    79,
    50,     0,    52,    74,     0,    73,    75,    85,   101,   165,
   134,   135,   136,   133,   138,   139,   142,   141,   149,   148,
   145,   144,   146,   147,   151,   152,   154,   156,   158,   160,
   162,     0,     0,   331,   371,     0,   303,   360,   362,   363,
   364,   365,   366,   367,   368,   369,   370,   351,    13,    17,
   396,     0,   395,     0,     0,   303,   525,   519,   303,   356,
   504,     0,   492,   496,     0,   198,   386,   385,   374,   465,
   469,    88,    99,     0,     0,     0,   481,   103,    98,    97,
   100,     0,   130,     0,     0,   122,     0,     0,    54,    49,
    53,     0,    77,    80,    78,     0,    81,     0,   357,   361,
     0,     0,     0,   527,   388,     0,   520,   524,     0,     0,
     0,   311,     0,     0,     0,     0,     0,     0,   556,     0,
   421,   422,     0,   311,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   276,     0,   276,     0,     0,
     0,     0,     0,   202,    10,     0,    23,    61,   106,   107,
    91,   119,   120,     0,   222,   200,   183,   184,     0,   199,
   185,   181,   182,     0,     0,   186,     0,   187,   227,   228,
   188,   195,   244,   245,   246,   247,   189,   265,   266,   267,
   268,   269,   190,   191,   192,   193,   194,   196,   105,    71,
    92,    46,     0,   211,   485,   213,   212,     0,   484,   126,
   125,   123,     0,    55,    51,     0,   164,     0,    18,   397,
   392,   179,   526,     0,     0,   556,     0,   303,     0,     0,
     0,     0,   379,   311,     0,     0,     0,   207,   379,     0,
     0,     0,   457,   456,   420,   459,   458,   449,     0,   270,
   289,     0,   271,     0,     0,   252,     0,     0,     0,     0,
     0,   232,     0,   277,     0,     0,     0,     0,   290,   248,
     0,     0,   209,   206,   197,   201,   204,   205,   219,    95,
    46,     0,   480,   483,   482,   124,    76,     0,     0,   391,
     0,   303,   303,     0,   303,     0,     0,     0,   216,     0,
   554,     0,     0,     0,     0,   432,   431,   443,   440,   444,
   439,   441,   442,   446,   445,   429,   430,   433,   436,   427,
   428,   425,   426,   434,   435,   438,   437,     0,   303,     0,
   373,     0,     0,   419,   303,   303,   203,   215,     0,     0,
   258,   262,     0,   253,   259,     0,   272,     0,   274,   180,
     0,     0,   229,     0,   275,     0,   278,     0,     0,   279,
   282,   280,   294,   293,     0,     0,    93,    96,    47,     0,
   486,     0,   393,     0,   512,   511,     0,     0,   303,     0,
   451,     0,     0,   372,   410,     0,     0,     0,   303,   210,
     0,     0,   208,   303,   303,     0,     0,     0,   303,   303,
     0,     0,     0,   296,   254,     0,     0,   273,     0,   231,
     0,     0,     0,   285,   288,   283,   281,     0,     0,     0,
     0,   513,     0,     0,     0,     0,   556,     0,   450,   452,
   218,   217,   303,     0,     0,     0,     0,   417,     0,     0,
   418,   557,   557,   557,     0,   399,   403,     0,   400,   405,
     0,     0,     0,     0,   260,     0,   255,   263,     0,   230,
   291,   235,   233,   286,   292,   249,   214,   455,   502,   501,
     0,     0,   557,     0,     0,     0,     0,     0,   303,   303,
     0,     0,   376,     0,   375,   557,     0,     0,   416,     0,
   298,   297,   295,   256,     0,     0,     0,     0,   236,   237,
     0,   240,   287,     0,   303,   303,   505,   303,    78,    78,
   555,   555,   555,     0,   412,     0,   413,   448,   447,     0,
   423,   398,   409,   408,   556,   556,   250,     0,   257,   261,
     0,     0,   243,   234,   238,   239,   241,     0,     0,     0,
     0,     0,     0,     0,     0,   411,     0,   406,   407,     0,
   264,   242,   284,     0,     0,   557,   453,   454,   554,   554,
     0,   251,   509,   510,   506,   414,   415,   424,     0,     0,
     0
};

static const short yydefgoto[] = {   180,
   181,     8,    92,   143,   233,   182,   123,   318,   481,   526,
    95,    96,   183,    98,    99,   100,   101,   102,   650,   369,
   469,   380,   381,   184,   185,   186,   187,   188,   189,   475,
   382,   190,   191,   192,   193,   194,   195,   196,   197,   198,
   199,   737,   200,   201,   202,   203,   204,   205,   206,   207,
   208,   209,   210,   211,   370,   371,   372,   212,   213,   214,
   215,   216,   217,   218,   219,   220,   221,   222,   223,   290,
   383,   593,   721,   536,   537,   538,   539,   540,   541,   542,
   543,   544,   607,   608,   575,   576,   545,   668,   669,   546,
   547,   548,   549,   632,   723,   550,   833,   868,   869,   870,
   871,   872,   551,   552,   553,   554,   555,   713,   826,   898,
   714,   827,   899,   715,   556,   557,   558,   559,   560,   561,
   635,   562,   563,   730,   731,   874,   732,   564,   565,   566,
   567,   735,   568,   773,   774,   939,     2,   320,   226,    12,
    76,   138,   225,    10,   115,     3,     4,     5,     6,    13,
    14,    15,    46,    47,    48,    16,   141,   231,   232,   238,
   317,   416,   417,   418,   343,   344,   345,   346,   140,   117,
   321,   104,   449,   322,   323,   324,   660,   434,   325,   347,
   768,   816,   819,   769,   770,   895,   348,   848,   849,   850,
   349,   499,   611,   350,   500,   501,   698,   502,   351,   503,
   799,   800,   427,   615,   618,    17,   130,   151,   152,   243,
   352,   353,   354,   577,   457,   578,   655,   579,    18,   129,
   148,   149,   240,   333,   334,   335,   336,   442,   337,   338,
   796,   339,   746,    19,   146,   127,   128,   236,   327,   328,
   329,    20,    21,    22,    23,    72,    73,    74,   110,   111,
   134,   112,   135,    24,   155,   756,   914,   612,   857
};

static const short yypact[] = {    -8,
    94,    89,    -8,-32768,-32768,-32768,   132,    69,-32768,   125,
  1085,-32768,    33,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    89,-32768,    99,-32768,-32768,   262,-32768,   180,-32768,
-32768,-32768,   262,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   281,  1278,-32768,  1422,-32768,
-32768,   194,   253,   269,-32768,-32768,   428,  1003,   436,   467,
   472,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   262,-32768,   297,-32768,   338,   398,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   364,-32768,-32768,   404,-32768,   504,-32768,-32768,-32768,-32768,
-32768,   504,   504,   526,   405,-32768,-32768,-32768,-32768,   230,
-32768,   408,-32768,    -8,   389,   532,-32768,-32768,-32768,-32768,
-32768,-32768,   452,-32768,   398,   178,-32768,-32768,   413,   414,
    35,-32768,  2250,-32768,-32768,   -50,-32768,-32768,-32768,   225,
   415,-32768,-32768,   416,-32768,   403,   262,   406,-32768,   262,
   409,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   107,
   421,   422,-32768,  2434,-32768,   424,-32768,-32768,   425,   432,
  2250,  2250,  2250,  1995,  2250,  2250,  2250,  2250,  2250,-32768,
-32768,   437,   417,   142,   -23,-32768,-32768,-32768,-32768,-32768,
   435,   466,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   312,-32768,-32768,-32768,   630,
-32768,   255,   -14,   -35,   171,   301,   438,   429,   431,   453,
   172,-32768,-32768,-32768,   -16,   430,   -10,-32768,   570,   262,
   434,-32768,  2434,   -39,   120,   389,-32768,   489,   157,   389,
   489,   168,   389,-32768,  2250,   585,  2250,   -39,   364,   271,
   490,    11,  2434,  2479,  2250,-32768,-32768,-32768,    18,    20,
   268,   464,    13,-32768,-32768,-32768,-32768,-32768,  1915,   589,
  2250,   590,   468,-32768,  2250,-32768,-32768,   598,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  2250,
  2250,  2250,  2250,  2250,  2250,  2250,  2250,  2434,  2434,  2250,
  2250,  2250,  2250,  2250,  2250,  2250,  2250,  2250,  2250,  2250,
  2250,  2250,-32768,-32768,   489,   177,   389,   516,    85,   348,
   476,   507,-32768,-32768,-32768,   603,   471,   510,-32768,-32768,
   262,   562,   473,   179,-32768,-32768,-32768,-32768,-32768,-32768,
  1278,-32768,-32768,-32768,-32768,   287,-32768,-32768,-32768,-32768,
-32768,   475,   215,-32768,-32768,   345,-32768,   486,   491,  1915,
  2250,-32768,-32768,    81,   202,   288,   492,-32768,-32768,   493,
    18,-32768,   498,  2075,  2330,    18,   293,  2250,  2250,   519,
-32768,   499,-32768,-32768,   346,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   255,   255,   -14,   -14,   404,   404,
   -35,   -35,   -35,   -35,   171,   171,   301,   438,   429,   431,
   453,   505,   349,  1278,-32768,   488,   222,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,  2434,-32768,  2434,   496,    89,   494,-32768,   234,-32768,
-32768,  1196,-32768,-32768,  1800,  1504,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,   495,   513,   356,  1784,-32768,-32768,-32768,
-32768,  2250,-32768,  2250,  2250,-32768,   514,  1915,-32768,-32768,
-32768,  1915,-32768,-32768,  1915,  2250,-32768,  2403,-32768,-32768,
  2434,    16,    30,-32768,-32768,  2250,-32768,-32768,  2434,    40,
    25,   329,  2434,  2434,   582,   583,    41,    31,-32768,   319,
-32768,-32768,   322,   298,   500,   -62,  2434,   501,  1644,   508,
   518,   520,   374,   521,   523,  2250,   524,  2250,   495,   206,
   495,   528,   529,-32768,   437,    42,   417,   -25,   127,   135,
   170,   207,   217,   630,-32768,-32768,-32768,-32768,   515,  1504,
-32768,-32768,-32768,   517,   530,-32768,   531,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    37,-32768,
-32768,   504,  2434,-32768,-32768,-32768,-32768,   522,   559,-32768,
-32768,-32768,  2250,-32768,-32768,   533,-32768,   658,-32768,-32768,
   527,-32768,-32768,    44,   536,   542,   571,   -39,    45,    47,
  2434,  2434,   398,   103,   236,   572,   -22,-32768,   -29,    62,
   575,   535,-32768,-32768,-32768,-32768,-32768,-32768,  1504,-32768,
-32768,    45,-32768,   595,  2434,  2170,  2434,   537,  2250,   538,
  2250,   677,  2250,-32768,   539,  2250,   540,   304,-32768,-32768,
  2170,  2250,   544,   586,-32768,-32768,-32768,-32768,-32768,   545,
   504,    86,-32768,  1784,-32768,-32768,-32768,   560,  2250,-32768,
   323,   -39,   -39,   551,    89,   565,   554,    88,-32768,   122,
-32768,   343,   355,   568,  1784,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   596,    89,   720,
-32768,   599,   584,-32768,    89,   241,-32768,   628,   601,    48,
-32768,-32768,   588,-32768,   633,    49,-32768,   605,-32768,-32768,
   621,  1644,-32768,   623,-32768,   624,-32768,   238,   495,   304,
-32768,-32768,-32768,-32768,   625,   629,-32768,-32768,-32768,  2250,
-32768,   631,-32768,   587,-32768,-32768,   632,   634,    89,   384,
   607,  2250,   752,-32768,-32768,   620,  2434,  2434,   -39,-32768,
  2434,   400,-32768,   -39,   241,   412,   397,   622,   242,   243,
  2250,   626,   146,-32768,  2250,  2250,   731,-32768,  1644,-32768,
  1644,   636,   262,-32768,-32768,-32768,-32768,  1644,  1644,   671,
   495,-32768,   323,   323,   419,   639,-32768,    56,-32768,-32768,
-32768,-32768,    89,    50,    52,   646,    54,-32768,   647,   640,
-32768,-32768,-32768,-32768,   682,-32768,-32768,   688,-32768,-32768,
   661,  2250,   786,  1644,-32768,   648,-32768,-32768,  2250,-32768,
-32768,   372,-32768,   788,-32768,-32768,-32768,-32768,-32768,-32768,
   323,   323,-32768,   652,   667,   668,   354,   654,    89,    89,
   669,   672,-32768,   148,-32768,-32768,   369,   369,-32768,   656,
-32768,-32768,-32768,  2250,   674,  2250,   678,   664,   372,-32768,
  1364,-32768,-32768,   675,   244,   246,-32768,    89,  1915,  1915,
-32768,-32768,-32768,   709,-32768,   711,-32768,-32768,-32768,  2434,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   681,-32768,   633,
  1644,   684,-32768,-32768,-32768,  1504,-32768,   495,   715,   717,
   673,   686,   689,   495,   495,-32768,    55,-32768,-32768,  1644,
-32768,-32768,-32768,   323,   323,-32768,-32768,-32768,-32768,-32768,
   690,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   818,   821,
-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,   -65,   641,-32768,   -38,-32768,   344,-32768,    66,
   666,-32768,    29,-32768,   705,-32768,-32768,   676,   184,   -93,
   457,-32768,   -89,-32768,-32768,-32768,-32768,-32768,    53,-32768,
  -359,-32768,-32768,  -183,-32768,-32768,   152,   181,-32768,   196,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   469,
   382,   411,   407,-32768,  -196,-32768,   474,  -139,   208,   110,
   221,   541,   547,   543,   534,   548,-32768,-32768,   462,-32768,
   477,  -615,  -627,  -529,  -485,  -301,-32768,   -34,-32768,-32768,
-32768,  -416,  -482,   139,  -556,-32768,-32768,   224,    95,-32768,
  -614,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    -9,
-32768,   -12,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    -3,-32768,-32768,-32768,-32768,-32768,-32768,
   347,-32768,-32768,-32768,   133,-32768,   134,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    39,-32768,   753,     0,-32768,-32768,
-32768,  -133,    -1,   368,-32768,-32768,   870,-32768,-32768,   743,
     4,  -221,  -303,-32768,   833,-32768,-32768,-32768,-32768,  -122,
-32768,-32768,-32768,   465,  -289,  -277,  -276,-32768,-32768,  -120,
  -240,-32768,-32768,  -459,   445,-32768,-32768,-32768,-32768,  -267,
   118,-32768,-32768,   114,   116,    28,  -232,-32768,    38,    43,
  -227,-32768,-32768,  -219,-32768,-32768,-32768,-32768,  -217,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   546,  -248,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   553,-32768,-32768,-32768,-32768,
    12,-32768,  -764,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   454,-32768,-32768,-32768,   872,-32768,-32768,-32768,-32768,   764,
-32768,-32768,-32768,-32768,   744,  -402,  -353,  -590,  -739
};


#define	YYLAST		2562


static const short yytable[] = {     9,
   455,    11,   121,   363,   144,   664,   108,   359,   122,   124,
   646,   712,    49,   718,   736,   120,    50,   120,   703,    93,
   342,   590,   120,   624,   120,    54,   419,   241,   839,   840,
   596,    56,  -300,    93,   261,   591,   604,   445,   420,   421,
    53,   120,   -14,   644,   448,   595,    53,   643,   422,   661,
   667,  -552,   604,   772,   777,   851,   103,   852,   116,   854,
   931,   356,  -552,   373,   142,   108,   247,    29,   845,   296,
   109,   -14,     1,   858,   859,  -220,   875,   876,   700,   297,
   446,   237,   605,   423,   237,   312,    97,   385,   424,   707,
  -381,  -552,    93,  -305,   415,   597,   425,   741,   426,     7,
   -14,   606,   330,   877,  -220,   -11,   340,   315,    93,   355,
   478,    93,   -14,  -556,   312,   586,   892,   670,   760,  -220,
   294,   295,   701,    94,   -14,    93,   846,   419,   413,   109,
    29,   342,   704,  -306,  -552,    49,   801,   153,   312,   420,
   421,   -14,   119,   821,   368,   109,   368,   825,   109,   422,
   270,   119,   570,   362,   395,   396,   119,   119,   122,   933,
   934,   828,   103,   -14,   237,   -14,   118,   118,   119,   376,
   119,   119,   263,   119,   119,   119,   119,   456,   119,   467,
   119,   119,   298,   428,   423,   430,   935,   740,   753,   424,
  -552,    93,    97,    79,    93,   415,    80,   425,   614,   426,
    52,   617,   260,  -209,   621,   750,   844,   119,   245,   711,
   458,   119,   119,    28,    93,    93,   299,   638,   639,   640,
    84,  -552,   700,    63,   734,    85,    49,  -223,   109,   250,
    50,   103,   754,    26,   326,  -224,   780,   246,   332,   762,
    86,   341,    87,   271,   675,   766,   823,  -209,   890,   712,
   902,   103,   103,    88,    89,    64,  -223,    90,  -552,    93,
    93,    97,    26,  -521,  -224,   440,   755,    53,   676,  -552,
  -221,  -223,   272,    27,   300,   824,   301,   891,  -552,  -224,
  -552,    97,    97,    65,    66,    67,    68,    69,    70,    71,
   302,   303,    93,   830,   310,   831,   103,   103,   319,  -221,
  -493,    57,   835,   836,   918,   919,    58,  -225,   677,    59,
    55,  -466,   311,   228,  -221,   414,  -552,  -226,   364,   366,
  -358,   728,  -494,  -552,    60,   229,    97,    97,   118,   109,
   131,   459,   132,   332,   255,  -552,  -225,   729,   863,   678,
   679,   680,  -552,  -552,  -552,  -552,  -226,  -552,   446,    61,
   681,  -225,   341,   682,   683,   684,   685,   666,  -467,   686,
   687,  -226,   688,   399,   400,  -359,   783,   689,   690,   691,
   692,   693,   694,   695,   696,   697,   646,   487,   584,   628,
   446,   291,   585,    26,  -401,  -402,  -404,  -507,   866,  -508,
   629,   292,   293,    93,   374,    93,   867,   119,   630,   360,
   431,   738,   432,    93,   292,   293,    93,   525,   433,   401,
   402,   403,   404,    75,   119,   921,   414,   460,   304,   305,
   468,   747,   748,    26,   113,   619,   784,   785,    26,   446,
   103,   447,   103,    77,   932,   276,   277,   278,   326,    93,
   103,   105,    93,   103,   569,   275,   275,   452,   474,   275,
    93,   477,   881,   882,    93,    93,   275,   598,   572,    26,
    97,   446,    97,   613,   446,   744,   616,   745,    93,   119,
    97,   757,   106,    97,   527,   124,   103,   107,   651,   103,
   114,   119,   674,   758,   436,   116,   797,   103,   702,   838,
   118,   103,   103,   812,   813,   603,   609,   482,   528,   483,
   436,   525,   808,   397,   398,   103,    97,   491,   120,    97,
   498,   446,   436,   893,   811,   841,   842,    97,   806,   912,
   913,    97,    97,   809,   405,   406,   936,   937,   915,   916,
   119,   125,   126,   137,    93,    97,   133,   139,   569,   142,
   147,   150,   230,   498,   234,   235,   319,   270,   239,   247,
   248,   242,   253,   254,   594,   894,   894,   651,   599,   600,
   255,   528,    93,    93,   274,   269,   275,   307,   527,   306,
   308,   103,   622,   313,   309,   314,   316,   256,   257,   258,
   525,   264,   265,   266,   267,   268,    93,   525,    93,   331,
   357,   361,   528,   375,   384,   386,   387,   529,   671,   103,
   103,    97,   525,   389,   429,   435,   923,   436,   437,   224,
   439,   441,   929,   930,   438,   453,   443,   569,   450,   472,
   454,   461,   462,   103,   569,   103,   530,   464,   473,    97,
    97,   479,   476,   601,   602,   486,   625,   446,   652,   569,
   484,   531,   571,   583,   620,   623,   626,   527,   627,   631,
   262,   633,   636,    97,   527,    97,   641,   642,   645,   654,
   529,   647,   657,   658,   662,   653,   672,   673,   659,   527,
   663,   528,   665,   699,   648,   649,   705,   706,   528,   709,
   722,   717,   719,   725,   727,   675,   700,   362,   742,   530,
   710,   529,   716,   749,   751,   752,   759,   391,   392,   393,
   394,   394,   394,   394,   531,   767,   394,   394,   394,   394,
   394,   394,   394,   394,   394,   394,   394,   834,    93,    93,
   530,   224,    93,   358,   761,   643,   765,   764,   753,   771,
   792,   367,   775,   776,   798,   531,   279,   280,   281,   282,
   283,   284,   285,   286,    93,   287,   288,   224,   795,   778,
   779,   388,   781,   782,   788,   103,   103,   667,   789,   103,
   791,   793,   803,   794,   767,   814,   390,   822,   815,   818,
   529,   289,   829,   837,   528,   853,   855,   529,   832,   813,
   391,   109,   843,   856,   812,    97,    97,   412,   224,    97,
   860,   772,   864,   873,   878,   879,   880,   883,   888,   530,
   897,   889,   847,   901,   908,   903,   530,   904,   882,   881,
   920,   922,   924,   925,   531,   927,   926,   940,   928,   938,
   941,   531,   804,   805,   589,   273,   807,   532,   528,   251,
   145,   528,   525,   528,   739,   471,   906,   224,   763,   252,
   528,   528,   410,   466,   463,   708,   407,   802,   884,   886,
   409,    93,   534,   408,   470,   470,   533,   411,   907,   905,
   900,   862,   786,   787,   637,   610,   136,   525,   580,   569,
   581,   582,    25,   529,   909,   910,   528,   795,   227,    62,
   485,   480,   810,   820,   817,   896,   444,   887,   103,   911,
   532,   885,   488,    51,   154,     0,   244,     0,   451,   527,
     0,     0,   530,     0,   569,     0,     0,   535,     0,     0,
     0,     0,     0,     0,     0,   534,   528,   531,    97,   533,
     0,   532,     0,   528,     0,     0,     0,   529,     0,     0,
   529,     0,   529,   574,   527,     0,     0,     0,     0,   529,
   529,     0,     0,     0,     0,     0,   534,     0,     0,     0,
   533,     0,   587,   528,     0,   917,   530,     0,   528,   530,
     0,   530,   592,     0,     0,     0,     0,     0,   530,   530,
   535,   531,   528,     0,   531,   529,   531,     0,     0,     0,
     0,     0,     0,   531,   531,     0,     0,     0,     0,   656,
     0,     0,   634,     0,   634,     0,     0,     0,     0,     0,
   532,   535,     0,     0,   530,     0,     0,   532,    53,     0,
     0,     0,     0,     0,     0,   529,    78,     0,    79,   531,
     0,    80,   529,     0,     0,   534,    81,     0,     0,   533,
    82,     0,   534,     0,     0,     0,   533,     0,    83,     0,
     0,     0,     0,     0,   530,    84,     0,     0,     0,     0,
    85,   530,   529,     0,     0,     0,     0,   529,     0,   531,
     0,     0,     0,     0,     0,    86,   531,    87,     0,     0,
     0,   529,     0,     0,     0,     0,     0,     0,    88,    89,
   535,   530,    90,     0,  -299,    91,   530,   535,     0,     0,
     0,     0,     0,     0,     0,    30,   531,     0,     0,     0,
   530,   531,     0,   532,     0,   592,     0,   720,     0,   724,
     0,     0,   726,     0,     0,   531,    31,   733,   720,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   534,    32,
   574,     0,   533,    33,    34,   743,     0,     0,    35,     0,
    36,    37,    38,    39,    40,     0,     0,     0,    41,     0,
     0,   574,    42,     0,     0,     0,     0,   532,     0,     0,
   532,     0,   532,    43,     0,     0,    44,     0,    45,   532,
   532,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   534,   535,     0,   534,   533,   534,     0,   533,
     0,   533,     0,     0,   534,   534,     0,     0,   533,   533,
     0,    53,     0,     0,     0,   532,     0,     0,     0,    78,
     0,    79,     0,     0,    80,     0,   790,     0,     0,    81,
     0,     0,     0,    82,     0,   489,     0,     0,   592,     0,
   534,    83,     0,     0,   533,     0,     0,   535,    84,     0,
   535,     0,   535,    85,     0,   532,     0,   720,     0,   535,
   535,   720,   532,     0,     0,     0,     0,     0,    86,     0,
    87,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   534,    88,    89,     0,   533,    90,     0,   534,   490,     0,
     0,   533,   532,     0,     0,   535,     0,   532,    30,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   861,     0,
     0,   532,     0,     0,     0,   865,     0,   534,     0,    31,
     0,   533,   534,     0,     0,     0,   533,     0,     0,     0,
     0,     0,    32,     0,     0,   535,   534,    34,     0,     0,
   533,    35,   535,    36,    37,    38,    39,    40,     0,     0,
     0,    41,   592,     0,     0,    42,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    43,     0,     0,    44,
     0,    45,   535,     0,     0,     0,     0,   535,     0,   504,
   156,   157,   158,   159,     0,     0,   160,    78,   505,    79,
   866,   535,    80,   506,     0,   507,   508,    81,   867,   162,
   509,    82,     0,     0,     0,     0,   163,     0,   510,    83,
   511,   512,   513,   514,     0,     0,    84,     0,     0,     0,
   515,    85,     0,   164,   165,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   516,    86,     0,    87,   166,
     0,     0,    30,   517,   167,   518,   168,   519,   169,    88,
    89,   520,   521,    90,   522,     0,   249,     0,   523,     0,
     0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    32,     0,     0,     0,
    33,    34,     0,     0,     0,    35,     0,    36,    37,    38,
    39,    40,     0,     0,     0,    41,     0,   171,   172,    42,
   173,     0,   174,     0,     0,   175,   176,   177,   178,   179,
    43,     0,     0,    44,     0,    45,   446,     0,   524,   504,
   156,   157,   158,   159,     0,     0,   160,    78,   505,    79,
     0,     0,    80,   506,     0,   507,   508,    81,     0,   162,
   509,    82,     0,     0,     0,     0,   163,     0,   510,    83,
   511,   512,   513,   514,     0,     0,    84,     0,     0,     0,
   515,    85,     0,   164,   165,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   516,    86,     0,    87,   166,
     0,     0,     0,   517,   167,   518,   168,   519,   169,    88,
    89,   520,   521,    90,   522,     0,   249,     0,   523,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   171,   172,     0,
   173,     0,   174,     0,     0,   175,   176,   177,   178,   179,
     0,     0,     0,     0,     0,     0,   446,     0,   524,    53,
   156,   157,   158,   159,     0,     0,   160,    78,   505,    79,
     0,     0,    80,   506,     0,     0,   508,    81,     0,   162,
   509,    82,     0,     0,     0,     0,   163,     0,   510,    83,
   511,   512,   513,   514,     0,     0,    84,     0,     0,     0,
   515,    85,     0,   164,   165,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   516,    86,     0,    87,   166,
     0,     0,     0,   517,   167,   518,   168,   519,   169,    88,
    89,   520,   521,    90,   522,     0,     0,     0,   523,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   171,   172,     0,
   173,     0,   174,     0,     0,   175,   176,   177,   178,   179,
     0,     0,     0,     0,     0,     0,   446,     0,   524,    53,
   156,   157,   158,   159,     0,     0,   160,    78,     0,    79,
     0,     0,    80,   161,     0,   492,     0,    81,     0,   162,
     0,    82,     0,    78,     0,    79,   163,     0,    80,    83,
    57,   493,     0,    81,     0,    58,    84,    82,    59,   494,
   495,    85,     0,   164,   165,    83,     0,     0,     0,     0,
   496,     0,    84,    60,     0,     0,    86,    85,    87,   166,
   573,     0,     0,     0,   167,     0,   168,     0,   169,    88,
    89,   170,    86,    90,    87,     0,     0,     0,    61,     0,
     0,     0,     0,     0,     0,    88,    89,     0,     0,    90,
     0,     0,   497,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   171,   172,     0,
   173,     0,   174,     0,     0,   175,   176,   177,   178,   179,
   377,   156,   157,   158,   159,     0,   362,   160,    78,     0,
    79,     0,     0,    80,   161,     0,     0,     0,    81,     0,
   162,     0,    82,     0,     0,     0,     0,   163,     0,     0,
    83,     0,     0,     0,     0,     0,     0,    84,     0,     0,
     0,     0,    85,     0,   164,   165,     0,   378,     0,     0,
     0,     0,     0,     0,     0,   379,     0,    86,     0,    87,
   166,     0,     0,     0,     0,   167,     0,   168,     0,   169,
    88,    89,   170,     0,    90,     0,     0,     0,     0,     0,
    53,   156,   157,   158,   159,     0,     0,   160,    78,     0,
    79,     0,     0,    80,   161,     0,     0,     0,    81,     0,
   162,     0,    82,     0,     0,     0,     0,   163,     0,     0,
    83,     0,     0,     0,     0,     0,     0,    84,   171,   172,
     0,   173,    85,   174,   164,   165,   175,   176,   177,   178,
   179,     0,     0,     0,     0,     0,     0,    86,     0,    87,
   166,     0,     0,     0,     0,   167,     0,   168,     0,   169,
    88,    89,   170,     0,    90,     0,     0,   259,     0,     0,
    53,   156,   157,   158,   159,     0,     0,   160,    78,     0,
    79,     0,     0,    80,   161,     0,     0,     0,    81,     0,
   162,     0,    82,     0,     0,     0,     0,   163,     0,     0,
    83,     0,     0,     0,     0,     0,     0,    84,   171,   172,
     0,   173,    85,   174,   164,   165,   175,   176,   177,   178,
   179,     0,     0,     0,     0,     0,     0,    86,     0,    87,
   166,     0,     0,     0,     0,   167,     0,   168,     0,   169,
    88,    89,   170,     0,    90,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    53,   156,   157,   158,   159,
     0,     0,   160,    78,     0,    79,     0,     0,    80,   161,
     0,     0,     0,    81,     0,   162,     0,    82,   171,   172,
     0,   173,   163,   174,   465,    83,   175,   176,   177,   178,
   179,     0,    84,     0,     0,     0,     0,    85,     0,   164,
   165,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    86,     0,    87,   166,     0,     0,     0,     0,
   167,     0,   168,     0,   169,    88,    89,   170,     0,    90,
     0,     0,   249,     0,     0,    53,   156,   157,   158,   159,
     0,     0,   160,    78,     0,    79,     0,     0,    80,   161,
     0,     0,     0,    81,     0,   162,     0,    82,     0,     0,
     0,     0,   163,     0,     0,    83,     0,     0,     0,     0,
     0,     0,    84,   171,   172,     0,   173,    85,   174,   164,
   165,   175,   176,   177,   178,   179,     0,     0,     0,     0,
     0,     0,    86,     0,    87,   166,     0,     0,     0,     0,
   167,     0,   168,     0,   169,    88,    89,   170,     0,    90,
     0,     0,     0,     0,     0,    53,   156,   157,   158,   159,
     0,     0,   160,    78,     0,    79,     0,     0,    80,   161,
     0,     0,     0,    81,     0,   162,     0,    82,     0,     0,
     0,     0,   163,     0,     0,    83,     0,     0,     0,     0,
     0,     0,    84,   171,   172,     0,   173,    85,   174,   164,
   165,   175,   176,   177,   178,   179,     0,     0,     0,     0,
     0,     0,    86,     0,    87,   166,     0,     0,     0,     0,
   167,     0,   168,     0,   169,    88,    89,   170,   492,    90,
     0,     0,     0,     0,     0,     0,    78,     0,    79,     0,
     0,    80,     0,    57,   493,     0,    81,     0,    58,     0,
    82,    59,   494,   495,     0,     0,     0,     0,    83,    53,
     0,     0,     0,   496,     0,    84,    60,    78,     0,    79,
    85,     0,    80,     0,     0,     0,     0,    81,   174,     0,
     0,    82,   176,   177,     0,    86,     0,    87,     0,    83,
     0,    61,     0,     0,     0,     0,    84,     0,    88,    89,
     0,    85,    90,     0,    53,   497,     0,     0,     0,     0,
     0,     0,    78,     0,    79,     0,    86,    80,    87,     0,
     0,     0,    81,     0,     0,     0,    82,     0,     0,    88,
    89,     0,     0,    90,    83,     0,   249,     0,     0,     0,
     0,    84,     0,     0,     0,     0,    85,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   588,     0,     0,     0,
     0,    86,     0,    87,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    88,    89,     0,     0,    90,     0,
     0,   365
};

static const short yycheck[] = {     1,
   360,     2,    96,   252,   125,   596,    72,   248,   102,   103,
   540,   626,    13,   629,   642,     5,    13,     5,   609,    58,
   242,     6,     5,   509,     5,    27,   316,   150,   793,   794,
     6,    33,     0,    72,   174,     6,     6,   341,   316,   316,
     6,     5,     6,   526,   346,     6,     6,     6,   316,     6,
     6,   102,     6,     6,     6,     6,    58,     6,    88,     6,
     6,   245,   102,   260,    88,   131,   129,     6,    13,   105,
    72,    88,    81,   813,   814,   101,   841,   842,   101,   115,
   143,   147,    52,   316,   150,   102,    58,   271,   316,   619,
   130,   102,   131,   144,   316,    71,   316,   654,   316,     6,
    88,    71,   236,   843,   130,   129,   240,   230,   147,   243,
   414,   150,   129,   143,   102,   475,   856,   600,   675,   145,
   135,   136,   145,    58,    88,   164,    71,   417,   312,   131,
     6,   353,    71,   144,   102,   136,   752,   103,   102,   417,
   417,   129,   127,   771,   127,   147,   127,   775,   150,   417,
   131,   127,   454,   143,   294,   295,   127,   127,   252,   924,
   925,   776,   164,   127,   230,   129,   127,   127,   127,   263,
   127,   127,   174,   127,   127,   127,   127,   361,   127,   376,
   127,   127,    12,   317,   417,   101,   926,   102,   101,   417,
   102,   230,   164,    16,   233,   417,    19,   417,   500,   417,
   102,   503,   174,   101,   506,   665,   797,   127,   102,   626,
   130,   127,   127,   145,   253,   254,    46,   519,   520,   521,
    43,   102,   101,    30,   641,    48,   227,   101,   230,   164,
   227,   233,   145,   131,   235,   101,   722,   131,   239,   699,
    63,   242,    65,   102,   142,   705,   101,   145,   101,   864,
   866,   253,   254,    76,    77,    62,   130,    80,   102,   298,
   299,   233,   131,   144,   130,   331,   145,     6,    33,   102,
   101,   145,   131,   142,   104,   130,   106,   130,   102,   145,
   102,   253,   254,    90,    91,    92,    93,    94,    95,    96,
   120,   121,   331,   779,   123,   781,   298,   299,   233,   130,
   144,    21,   788,   789,   895,   896,    26,   101,    73,    29,
   131,   144,   141,    89,   145,   316,   102,   101,   253,   254,
   144,    18,   144,   102,    44,   101,   298,   299,   127,   331,
   101,   130,   103,   334,   129,   102,   130,    34,   824,   104,
   105,   106,   102,   102,   102,   102,   130,   102,   143,    69,
   115,   145,   353,   118,   119,   120,   121,   598,   144,   124,
   125,   145,   127,   298,   299,   144,   129,   132,   133,   134,
   135,   136,   137,   138,   139,   140,   906,   144,   468,     6,
   143,   127,   472,   131,   144,   144,   144,   144,    17,   144,
    17,   137,   138,   432,   127,   434,    25,   127,    25,   129,
    53,   650,    55,   442,   137,   138,   445,   446,    61,   300,
   301,   302,   303,   145,   127,   901,   417,   130,   118,   119,
   128,   662,   663,   131,   128,   128,   728,   729,   131,   143,
   432,   145,   434,     6,   920,   124,   125,   126,   439,   478,
   442,     6,   481,   445,   446,   101,   101,   103,   103,   101,
   489,   103,    99,   100,   493,   494,   101,   129,   103,   131,
   432,   143,   434,   145,   143,   143,   145,   145,   507,   127,
   442,   129,     6,   445,   446,   569,   478,     6,   572,   481,
   143,   127,   603,   129,   101,    88,   103,   489,   609,   791,
   127,   493,   494,    97,    98,   497,   498,   432,   446,   434,
   101,   540,   103,   296,   297,   507,   478,   442,     5,   481,
   445,   143,   101,   145,   103,    97,    98,   489,   759,   879,
   880,   493,   494,   764,   304,   305,   929,   930,   882,   883,
   127,     6,   128,   145,   573,   507,   129,     6,   540,    88,
   128,   128,   128,   478,   129,   143,   481,   131,   143,   129,
   129,   143,   129,   129,   489,   857,   858,   651,   493,   494,
   129,   509,   601,   602,   130,   129,   101,   139,   540,   132,
   140,   573,   507,   144,   122,     6,   143,   171,   172,   173,
   619,   175,   176,   177,   178,   179,   625,   626,   627,   101,
     6,   102,   540,   130,     6,     6,   129,   446,   600,   601,
   602,   573,   641,     6,    89,   130,   908,   101,     6,   133,
   101,    50,   914,   915,   144,   130,   144,   619,   144,   101,
   130,   130,   130,   625,   626,   627,   446,   130,   130,   601,
   602,   144,   128,    52,    52,   142,   129,   143,   573,   641,
   145,   446,   130,   130,   145,   145,   129,   619,   129,   129,
   174,   129,   129,   625,   626,   627,   129,   129,   144,   101,
   509,   145,   130,     6,   129,   144,   601,   602,   142,   641,
   129,   619,   102,   102,   145,   145,   102,   143,   626,    85,
     4,   145,   145,   145,   145,   142,   101,   143,   129,   509,
   625,   540,   627,   143,   130,   142,   129,   291,   292,   293,
   294,   295,   296,   297,   509,   706,   300,   301,   302,   303,
   304,   305,   306,   307,   308,   309,   310,   783,   757,   758,
   540,   245,   761,   247,   129,     6,   143,   129,   101,   129,
   144,   255,   145,   101,   128,   540,   107,   108,   109,   110,
   111,   112,   113,   114,   783,   116,   117,   271,   749,   145,
   130,   275,   130,   130,   130,   757,   758,     6,   130,   761,
   130,   130,   143,   130,   765,   144,   290,   142,   769,   770,
   619,   142,    42,   103,   722,   130,   130,   626,   143,    98,
   374,   783,   144,   144,    97,   757,   758,   311,   312,   761,
   130,     6,   145,     6,   143,   129,   129,   144,   130,   619,
   145,   130,   803,   130,   130,   128,   626,   144,   100,    99,
   130,   128,    98,    97,   619,   130,   144,     0,   130,   130,
     0,   626,   757,   758,   481,   185,   761,   446,   776,   164,
   126,   779,   871,   781,   651,   379,   871,   361,   700,   164,
   788,   789,   309,   375,   371,   622,   306,   753,   849,   850,
   308,   890,   446,   307,   378,   379,   446,   310,   871,   869,
   864,   823,   730,   730,   518,   498,   114,   906,   462,   871,
   464,   465,     3,   722,   875,   876,   824,   878,   136,    47,
   436,   417,   765,   770,   769,   858,   334,   850,   890,   878,
   509,   849,   439,    22,   131,    -1,   153,    -1,   353,   871,
    -1,    -1,   722,    -1,   906,    -1,    -1,   446,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   509,   864,   722,   890,   509,
    -1,   540,    -1,   871,    -1,    -1,    -1,   776,    -1,    -1,
   779,    -1,   781,   457,   906,    -1,    -1,    -1,    -1,   788,
   789,    -1,    -1,    -1,    -1,    -1,   540,    -1,    -1,    -1,
   540,    -1,   476,   901,    -1,   890,   776,    -1,   906,   779,
    -1,   781,   486,    -1,    -1,    -1,    -1,    -1,   788,   789,
   509,   776,   920,    -1,   779,   824,   781,    -1,    -1,    -1,
    -1,    -1,    -1,   788,   789,    -1,    -1,    -1,    -1,   583,
    -1,    -1,   516,    -1,   518,    -1,    -1,    -1,    -1,    -1,
   619,   540,    -1,    -1,   824,    -1,    -1,   626,     6,    -1,
    -1,    -1,    -1,    -1,    -1,   864,    14,    -1,    16,   824,
    -1,    19,   871,    -1,    -1,   619,    24,    -1,    -1,   619,
    28,    -1,   626,    -1,    -1,    -1,   626,    -1,    36,    -1,
    -1,    -1,    -1,    -1,   864,    43,    -1,    -1,    -1,    -1,
    48,   871,   901,    -1,    -1,    -1,    -1,   906,    -1,   864,
    -1,    -1,    -1,    -1,    -1,    63,   871,    65,    -1,    -1,
    -1,   920,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
   619,   901,    80,    -1,     0,    83,   906,   626,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    11,   901,    -1,    -1,    -1,
   920,   906,    -1,   722,    -1,   629,    -1,   631,    -1,   633,
    -1,    -1,   636,    -1,    -1,   920,    32,   641,   642,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   722,    45,
   654,    -1,   722,    49,    50,   659,    -1,    -1,    54,    -1,
    56,    57,    58,    59,    60,    -1,    -1,    -1,    64,    -1,
    -1,   675,    68,    -1,    -1,    -1,    -1,   776,    -1,    -1,
   779,    -1,   781,    79,    -1,    -1,    82,    -1,    84,   788,
   789,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   776,   722,    -1,   779,   776,   781,    -1,   779,
    -1,   781,    -1,    -1,   788,   789,    -1,    -1,   788,   789,
    -1,     6,    -1,    -1,    -1,   824,    -1,    -1,    -1,    14,
    -1,    16,    -1,    -1,    19,    -1,   740,    -1,    -1,    24,
    -1,    -1,    -1,    28,    -1,    30,    -1,    -1,   752,    -1,
   824,    36,    -1,    -1,   824,    -1,    -1,   776,    43,    -1,
   779,    -1,   781,    48,    -1,   864,    -1,   771,    -1,   788,
   789,   775,   871,    -1,    -1,    -1,    -1,    -1,    63,    -1,
    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   864,    76,    77,    -1,   864,    80,    -1,   871,    83,    -1,
    -1,   871,   901,    -1,    -1,   824,    -1,   906,    11,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   822,    -1,
    -1,   920,    -1,    -1,    -1,   829,    -1,   901,    -1,    32,
    -1,   901,   906,    -1,    -1,    -1,   906,    -1,    -1,    -1,
    -1,    -1,    45,    -1,    -1,   864,   920,    50,    -1,    -1,
   920,    54,   871,    56,    57,    58,    59,    60,    -1,    -1,
    -1,    64,   866,    -1,    -1,    68,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,    82,
    -1,    84,   901,    -1,    -1,    -1,    -1,   906,    -1,     6,
     7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
    17,   920,    19,    20,    -1,    22,    23,    24,    25,    26,
    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
    37,    38,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
    47,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
    -1,    -1,    11,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    -1,    83,    -1,    85,    -1,
    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,
    49,    50,    -1,    -1,    -1,    54,    -1,    56,    57,    58,
    59,    60,    -1,    -1,    -1,    64,    -1,   124,   125,    68,
   127,    -1,   129,    -1,    -1,   132,   133,   134,   135,   136,
    79,    -1,    -1,    82,    -1,    84,   143,    -1,   145,     6,
     7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
    -1,    -1,    19,    20,    -1,    22,    23,    24,    -1,    26,
    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
    37,    38,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
    47,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    -1,    83,    -1,    85,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,    -1,
   127,    -1,   129,    -1,    -1,   132,   133,   134,   135,   136,
    -1,    -1,    -1,    -1,    -1,    -1,   143,    -1,   145,     6,
     7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
    -1,    -1,    19,    20,    -1,    -1,    23,    24,    -1,    26,
    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
    37,    38,    39,    40,    -1,    -1,    43,    -1,    -1,    -1,
    47,    48,    -1,    50,    51,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    -1,    -1,    -1,    85,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,    -1,
   127,    -1,   129,    -1,    -1,   132,   133,   134,   135,   136,
    -1,    -1,    -1,    -1,    -1,    -1,   143,    -1,   145,     6,
     7,     8,     9,    10,    -1,    -1,    13,    14,    -1,    16,
    -1,    -1,    19,    20,    -1,     6,    -1,    24,    -1,    26,
    -1,    28,    -1,    14,    -1,    16,    33,    -1,    19,    36,
    21,    22,    -1,    24,    -1,    26,    43,    28,    29,    30,
    31,    48,    -1,    50,    51,    36,    -1,    -1,    -1,    -1,
    41,    -1,    43,    44,    -1,    -1,    63,    48,    65,    66,
    67,    -1,    -1,    -1,    71,    -1,    73,    -1,    75,    76,
    77,    78,    63,    80,    65,    -1,    -1,    -1,    69,    -1,
    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    80,
    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,   125,    -1,
   127,    -1,   129,    -1,    -1,   132,   133,   134,   135,   136,
     6,     7,     8,     9,    10,    -1,   143,    13,    14,    -1,
    16,    -1,    -1,    19,    20,    -1,    -1,    -1,    24,    -1,
    26,    -1,    28,    -1,    -1,    -1,    -1,    33,    -1,    -1,
    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
    -1,    -1,    48,    -1,    50,    51,    -1,    53,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    61,    -1,    63,    -1,    65,
    66,    -1,    -1,    -1,    -1,    71,    -1,    73,    -1,    75,
    76,    77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,
     6,     7,     8,     9,    10,    -1,    -1,    13,    14,    -1,
    16,    -1,    -1,    19,    20,    -1,    -1,    -1,    24,    -1,
    26,    -1,    28,    -1,    -1,    -1,    -1,    33,    -1,    -1,
    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,   124,   125,
    -1,   127,    48,   129,    50,    51,   132,   133,   134,   135,
   136,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,
    66,    -1,    -1,    -1,    -1,    71,    -1,    73,    -1,    75,
    76,    77,    78,    -1,    80,    -1,    -1,    83,    -1,    -1,
     6,     7,     8,     9,    10,    -1,    -1,    13,    14,    -1,
    16,    -1,    -1,    19,    20,    -1,    -1,    -1,    24,    -1,
    26,    -1,    28,    -1,    -1,    -1,    -1,    33,    -1,    -1,
    36,    -1,    -1,    -1,    -1,    -1,    -1,    43,   124,   125,
    -1,   127,    48,   129,    50,    51,   132,   133,   134,   135,
   136,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    65,
    66,    -1,    -1,    -1,    -1,    71,    -1,    73,    -1,    75,
    76,    77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
    -1,    -1,    13,    14,    -1,    16,    -1,    -1,    19,    20,
    -1,    -1,    -1,    24,    -1,    26,    -1,    28,   124,   125,
    -1,   127,    33,   129,   130,    36,   132,   133,   134,   135,
   136,    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,    50,
    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    63,    -1,    65,    66,    -1,    -1,    -1,    -1,
    71,    -1,    73,    -1,    75,    76,    77,    78,    -1,    80,
    -1,    -1,    83,    -1,    -1,     6,     7,     8,     9,    10,
    -1,    -1,    13,    14,    -1,    16,    -1,    -1,    19,    20,
    -1,    -1,    -1,    24,    -1,    26,    -1,    28,    -1,    -1,
    -1,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
    -1,    -1,    43,   124,   125,    -1,   127,    48,   129,    50,
    51,   132,   133,   134,   135,   136,    -1,    -1,    -1,    -1,
    -1,    -1,    63,    -1,    65,    66,    -1,    -1,    -1,    -1,
    71,    -1,    73,    -1,    75,    76,    77,    78,    -1,    80,
    -1,    -1,    -1,    -1,    -1,     6,     7,     8,     9,    10,
    -1,    -1,    13,    14,    -1,    16,    -1,    -1,    19,    20,
    -1,    -1,    -1,    24,    -1,    26,    -1,    28,    -1,    -1,
    -1,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
    -1,    -1,    43,   124,   125,    -1,   127,    48,   129,    50,
    51,   132,   133,   134,   135,   136,    -1,    -1,    -1,    -1,
    -1,    -1,    63,    -1,    65,    66,    -1,    -1,    -1,    -1,
    71,    -1,    73,    -1,    75,    76,    77,    78,     6,    80,
    -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,
    -1,    19,    -1,    21,    22,    -1,    24,    -1,    26,    -1,
    28,    29,    30,    31,    -1,    -1,    -1,    -1,    36,     6,
    -1,    -1,    -1,    41,    -1,    43,    44,    14,    -1,    16,
    48,    -1,    19,    -1,    -1,    -1,    -1,    24,   129,    -1,
    -1,    28,   133,   134,    -1,    63,    -1,    65,    -1,    36,
    -1,    69,    -1,    -1,    -1,    -1,    43,    -1,    76,    77,
    -1,    48,    80,    -1,     6,    83,    -1,    -1,    -1,    -1,
    -1,    -1,    14,    -1,    16,    -1,    63,    19,    65,    -1,
    -1,    -1,    24,    -1,    -1,    -1,    28,    -1,    -1,    76,
    77,    -1,    -1,    80,    36,    -1,    83,    -1,    -1,    -1,
    -1,    43,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   134,    -1,    -1,    -1,
    -1,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,    80,    -1,
    -1,    83
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 1:
#line 127 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 2:
#line 128 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 3:
#line 129 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 4:
#line 130 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 5:
#line 131 "csharp.y"
{ R(); yyval.value = registerString(yyvsp[0].value);;
    break;}
case 6:
#line 132 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 7:
#line 135 "csharp.y"
{ R(); yyval.value.type = TYPE_BOOL; yyval.value.v.i = 1; ;
    break;}
case 8:
#line 136 "csharp.y"
{ R(); yyval.value.type = TYPE_BOOL; yyval.value.v.i = 0; ;
    break;}
case 9:
#line 146 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; ;
    break;}
case 10:
#line 149 "csharp.y"
{

							 R(); yyval.type = TypeObject::getTypeObject(yyvsp[0].text, TYPE_UNRESOLVED)->setGeneric(GetGenericType());
							 PopGenericType();
						 ;
    break;}
case 11:
#line 156 "csharp.y"
{ R(); ;
    break;}
case 12:
#line 157 "csharp.y"
{ 
			lex_in_generic(); 
		;
    break;}
case 13:
#line 159 "csharp.y"
{
			lex_out_generic(); R(); 
		;
    break;}
case 14:
#line 165 "csharp.y"
{ PushGenericType(GetGenericType()); ;
    break;}
case 15:
#line 165 "csharp.y"
{ R(); ;
    break;}
case 16:
#line 169 "csharp.y"
{ R(); addGenericType(yyvsp[0].type); 	;
    break;}
case 17:
#line 170 "csharp.y"
{ R(); addGenericType(yyvsp[-1].type); ;
    break;}
case 19:
#line 183 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 20:
#line 184 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 21:
#line 187 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 22:
#line 188 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 23:
#line 191 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 24:
#line 192 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 25:
#line 195 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 26:
#line 196 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_BOOL); ;
    break;}
case 27:
#line 199 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 28:
#line 200 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 29:
#line 201 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported decimal/Decimal type"); ;
    break;}
case 30:
#line 204 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_SBYTE	);	;
    break;}
case 31:
#line 205 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_BYTE	);	;
    break;}
case 32:
#line 206 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_SHORT	);	;
    break;}
case 33:
#line 207 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_USHORT	);	;
    break;}
case 34:
#line 208 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_INT		); 	;
    break;}
case 35:
#line 209 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_UINT	); 	;
    break;}
case 36:
#line 210 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_LONG	); 	;
    break;}
case 37:
#line 211 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_ULONG	); 	;
    break;}
case 38:
#line 212 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_CHAR	); 	;
    break;}
case 39:
#line 215 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_FLOAT); 	;
    break;}
case 40:
#line 216 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_DOUBLE); 	;
    break;}
case 41:
#line 219 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addPointer();						;
    break;}
case 42:
#line 220 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_VOID)->addPointer(); ;
    break;}
case 43:
#line 223 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addRank(yyvsp[0].tmpValue);	;
    break;}
case 44:
#line 224 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addRank(yyvsp[0].tmpValue);	;
    break;}
case 45:
#line 226 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(yyvsp[-1].text, TYPE_UNRESOLVED)->addRank(yyvsp[0].tmpValue);	;
    break;}
case 46:
#line 229 "csharp.y"
{ R(); yyval.tmpValue = 0;		;
    break;}
case 47:
#line 231 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[-1].tmpValue; ;
    break;}
case 48:
#line 234 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; ;
    break;}
case 49:
#line 242 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 50:
#line 246 "csharp.y"
{ R(); yyval.expr = CreateMultipleExpr(yyvsp[0].expr); 		;
    break;}
case 51:
#line 247 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[0].expr);	;
    break;}
case 52:
#line 250 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 								;
    break;}
case 53:
#line 251 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_REF, yyvsp[0].expr);	;
    break;}
case 54:
#line 252 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_REF, yyvsp[0].expr);	;
    break;}
case 55:
#line 253 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "Named arguments are not supported yet"); ;
    break;}
case 56:
#line 256 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 57:
#line 257 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 58:
#line 260 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_CTE)->setValue(yyvsp[0].value); ;
    break;}
case 59:
#line 261 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 60:
#line 262 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 61:
#line 263 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 62:
#line 264 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 63:
#line 265 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 64:
#line 266 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 65:
#line 267 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 66:
#line 268 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 67:
#line 269 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 68:
#line 270 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 69:
#line 271 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 70:
#line 272 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 71:
#line 276 "csharp.y"
{ R(); yyval.expr = CreateDelegateExpr(yyvsp[-2].variable, yyvsp[0].statement); ;
    break;}
case 72:
#line 280 "csharp.y"
{ R(); yyval.expr = yyvsp[-1].expr->addParenthesis(); ;
    break;}
case 73:
#line 283 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_DOT, yyvsp[-2].expr)->setIdentifier(yyvsp[0].text);	;
    break;}
case 74:
#line 284 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT,yyvsp[-2].type->m_definitionAC->m_name))->setIdentifier(yyvsp[0].text);	;
    break;}
case 75:
#line 287 "csharp.y"
{ PushGenericType(GetGenericType()); ;
    break;}
case 76:
#line 287 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_INVOKE, yyvsp[-5].expr, yyvsp[-1].expr)->addGenericType(PopGenericType())->patchSubInvoke();	;
    break;}
case 77:
#line 288 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_INVOKE, CreateLeafExpr(EXPR_IDENT,yyvsp[-3].text), yyvsp[-1].expr)->addGenericType(GetGenericType())->patchSubInvoke(); PopGenericType(); ;
    break;}
case 78:
#line 291 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 79:
#line 292 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 80:
#line 295 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, yyvsp[-3].expr, yyvsp[-1].expr);	;
    break;}
case 81:
#line 296 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_IDENT,yyvsp[-3].text), yyvsp[-1].expr); ;
    break;}
case 82:
#line 300 "csharp.y"
{ R(); yyval.expr = NULL;								;
    break;}
case 83:
#line 301 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;							;
    break;}
case 84:
#line 305 "csharp.y"
{ R(); yyval.expr = CreateMultipleExpr(yyvsp[0].expr); 		;
    break;}
case 85:
#line 306 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[0].expr); 	;
    break;}
case 86:
#line 309 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_THIS);			;
    break;}
case 87:
#line 312 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_BASE))->setIdentifier(yyvsp[0].text); ;
    break;}
case 88:
#line 313 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_BASE), yyvsp[-1].expr);;
    break;}
case 89:
#line 316 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PLUSPLUS, yyvsp[-1].expr);	;
    break;}
case 90:
#line 319 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_MINUSMINUS, yyvsp[-1].expr);;
    break;}
case 91:
#line 322 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 92:
#line 325 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_NEW, yyvsp[-1].expr)->setType(yyvsp[-3].type); ;
    break;}
case 93:
#line 329 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_NEW, yyvsp[-3].expr, yyvsp[0].expr)->setType(yyvsp[-5].type)->setRank(yyvsp[-1].tmpValue)->setArrayNew(true); ;
    break;}
case 94:
#line 330 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_NEW, NULL, yyvsp[0].expr)->setType(yyvsp[-1].type)->setArrayNew(false); ;
    break;}
case 95:
#line 333 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 96:
#line 334 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 97:
#line 337 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"typeof()"); yyval.expr = CreateLeafExpr(EXPR_TYPEOF)->setType(yyvsp[-1].type); ;
    break;}
case 98:
#line 338 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"typeof(void)"); ;
    break;}
case 99:
#line 341 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"checked"); yyval.expr = CreateSingleExpr(EXPR_CHECKED, yyvsp[-1].expr); ;
    break;}
case 100:
#line 344 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"unchecked"); yyval.expr = CreateSingleExpr(EXPR_UNCHECKED, yyvsp[-1].expr); ;
    break;}
case 101:
#line 347 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "-> operator not supported yet"); yyval.expr = CreateSingleExpr(EXPR_ARROW, yyvsp[-2].expr)->setIdentifier(yyvsp[0].text); ;
    break;}
case 102:
#line 350 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "& adress operator not supported yet."); yyval.expr = CreateSingleExpr(EXPR_ADRESSOF, yyvsp[-1].expr);		;
    break;}
case 103:
#line 353 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "sizeof() operator not supported yet"); yyval.expr = CreateLeafExpr(EXPR_SIZEOF)->setType(yyvsp[-1].type);	;
    break;}
case 104:
#line 356 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 105:
#line 357 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_IDENT,yyvsp[0].text); ;
    break;}
case 106:
#line 358 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 107:
#line 359 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 108:
#line 360 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 109:
#line 363 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 110:
#line 364 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_NOT, yyvsp[0].expr);		;
    break;}
case 111:
#line 365 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_LNOT, yyvsp[0].expr);		;
    break;}
case 112:
#line 366 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 113:
#line 369 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PREINCR, yyvsp[0].expr);	;
    break;}
case 114:
#line 372 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PREDECR, yyvsp[0].expr);	;
    break;}
case 115:
#line 375 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 116:
#line 376 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNARYPLUS, yyvsp[0].expr);	;
    break;}
case 117:
#line 377 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNARYMINUS, yyvsp[0].expr);	;
    break;}
case 118:
#line 378 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Unary * operator"); yyval.expr = CreateSingleExpr(EXPR_UNARYMULT, yyvsp[0].expr);	;
    break;}
case 119:
#line 379 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 120:
#line 380 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 121:
#line 381 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 122:
#line 389 "csharp.y"
{
		R(); yyval.expr = CreateDoubleExpr(EXPR_CAST, yyvsp[-2].expr, yyvsp[0].expr);		
	;
    break;}
case 123:
#line 392 "csharp.y"
{
		R(); yyval.expr = CreateDoubleExpr(EXPR_CAST_PTR, yyvsp[-3].expr, yyvsp[0].expr);	
	;
    break;}
case 124:
#line 396 "csharp.y"
{
		yyval.expr = CreateSingleExpr(EXPR_CAST, yyvsp[0].expr)->setType(TypeObject::getTypeObject(yyvsp[-4].text, TYPE_UNRESOLVED)->addRank(yyvsp[-3].tmpValue),yyvsp[-2].quals);
	;
    break;}
case 125:
#line 400 "csharp.y"
{	R();
		// $2.type, $3.quals, $5.expr
		yyval.expr = CreateSingleExpr(EXPR_CAST, yyvsp[0].expr)->setType(yyvsp[-3].type,yyvsp[-2].quals);
	;
    break;}
case 126:
#line 405 "csharp.y"
{	R();
		//  $3.quals, $5.expr
		yyval.expr = CreateSingleExpr(EXPR_CAST, yyvsp[0].expr)->setType(TypeObject::getTypeObject(TYPE_VOID),yyvsp[-2].quals);
	;
    break;}
case 127:
#line 411 "csharp.y"
{	R();	yyval.quals = NULL;		;
    break;}
case 128:
#line 412 "csharp.y"
{	R();	yyval.quals = yyvsp[0].quals;	;
    break;}
case 129:
#line 415 "csharp.y"
{	R();	yyval.quals = new Quals(yyvsp[0].tmpValue);	;
    break;}
case 130:
#line 416 "csharp.y"
{	R();	yyval.quals = yyvsp[-1].quals->addQuals(yyvsp[0].tmpValue);	;
    break;}
case 131:
#line 419 "csharp.y"
{	yyval.tmpValue = yyvsp[0].tmpValue;		;
    break;}
case 132:
#line 420 "csharp.y"
{	yyval.tmpValue = -1;				;
    break;}
case 133:
#line 424 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 134:
#line 425 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MULT, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 135:
#line 426 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DIV, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 136:
#line 427 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MOD, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 137:
#line 430 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 138:
#line 431 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_PLUS, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 139:
#line 432 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MINUS, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 140:
#line 435 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 141:
#line 436 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LSHFT, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 142:
#line 437 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_RSHFT, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 143:
#line 440 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 144:
#line 441 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LESS, yyvsp[-2].expr, yyvsp[0].expr);			;
    break;}
case 145:
#line 442 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MORE, yyvsp[-2].expr, yyvsp[0].expr);			;
    break;}
case 146:
#line 443 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LESSEQ, yyvsp[-2].expr, yyvsp[0].expr);		;
    break;}
case 147:
#line 444 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MOREEQ, yyvsp[-2].expr, yyvsp[0].expr);		;
    break;}
case 148:
#line 445 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_IS, yyvsp[-2].expr)->setType(yyvsp[0].type);	;
    break;}
case 149:
#line 446 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_AS, yyvsp[-2].expr)->setType(yyvsp[0].type);	;
    break;}
case 150:
#line 449 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 151:
#line 450 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_EQUTST, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 152:
#line 451 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DIFFTST, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 153:
#line 454 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 154:
#line 455 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LAND, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 155:
#line 458 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 156:
#line 459 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LXOR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 157:
#line 462 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 158:
#line 463 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LOR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 159:
#line 466 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 160:
#line 467 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_AND, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 161:
#line 470 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 162:
#line 471 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_OR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 163:
#line 474 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 164:
#line 475 "csharp.y"
{ R(); yyval.expr = CreateTripleExpr(EXPR_COND, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 165:
#line 477 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr((EnumExpressionType)yyvsp[-1].tmpValue, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 166:
#line 480 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_EQ;		;
    break;}
case 167:
#line 481 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_PLUSEQ;	;
    break;}
case 168:
#line 482 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_MINUSEQ;	;
    break;}
case 169:
#line 483 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_STAREQ;	;
    break;}
case 170:
#line 484 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_DIVEQ;	;
    break;}
case 171:
#line 485 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_MODEQ;	;
    break;}
case 172:
#line 486 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_XOREQ;	;
    break;}
case 173:
#line 487 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_ANDEQ;	;
    break;}
case 174:
#line 488 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_OREQ;	;
    break;}
case 175:
#line 489 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_RSHFTEQ;	;
    break;}
case 176:
#line 490 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_LSHFTEQ;	;
    break;}
case 177:
#line 494 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 178:
#line 495 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 179:
#line 498 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 180:
#line 501 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 181:
#line 516 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 182:
#line 517 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 183:
#line 518 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 184:
#line 521 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 185:
#line 522 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 186:
#line 523 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 187:
#line 524 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 188:
#line 525 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 189:
#line 526 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 190:
#line 527 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 191:
#line 528 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 192:
#line 529 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 193:
#line 530 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 194:
#line 531 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 195:
#line 532 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 196:
#line 533 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 197:
#line 536 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_BLOCK, NULL, yyvsp[-1].statement); ;
    break;}
case 198:
#line 539 "csharp.y"
{ R(); yyval.statement = NULL; ;
    break;}
case 199:
#line 540 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 200:
#line 544 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 201:
#line 545 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement ? yyvsp[-1].statement->addNext(yyvsp[0].statement) : yyvsp[0].statement; ;
    break;}
case 202:
#line 548 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_NULL, NULL, NULL); ;
    break;}
case 203:
#line 551 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_LABEL, NULL, yyvsp[0].statement)->addLabel(yyvsp[-2].text);	;
    break;}
case 204:
#line 554 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement;	;
    break;}
case 205:
#line 555 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement;	;
    break;}
case 206:
#line 558 "csharp.y"
{ R(); yyval.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, yyvsp[0].variable, yyvsp[-1].type); ;
    break;}
case 207:
#line 561 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable; ;
    break;}
case 208:
#line 562 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[0].variable); ;
    break;}
case 209:
#line 565 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[0].text);	;
    break;}
case 210:
#line 566 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-2].text)->setInitializer(yyvsp[0].expr); ;
    break;}
case 211:
#line 569 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 212:
#line 570 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 213:
#line 571 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 214:
#line 574 "csharp.y"
{ R(); /* Only in unsafe code from spec */compilerError(ERR_NOT_SUPPORTED_YET,"stackalloc"); ;
    break;}
case 215:
#line 577 "csharp.y"
{ R(); yyval.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, yyvsp[0].variable, yyvsp[-1].type)->setConstant(); ;
    break;}
case 216:
#line 580 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable; ;
    break;}
case 217:
#line 581 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[0].variable); ;
    break;}
case 218:
#line 584 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-2].text)->setInitializer(yyvsp[0].expr); ;
    break;}
case 219:
#line 587 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement; ;
    break;}
case 220:
#line 590 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAP_EXP, NULL, NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 221:
#line 591 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAP_EXP, NULL, NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 222:
#line 592 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_ASSIGN_EXPR, NULL, NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 223:
#line 593 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_POSTINCR,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 224:
#line 594 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_POSTDECR,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 225:
#line 595 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_PREINCR ,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 226:
#line 596 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_PREDECR ,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 227:
#line 599 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 228:
#line 600 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 229:
#line 605 "csharp.y"
{
		R();
		if (yyvsp[0].statement) {
			// IF-ELSE
			yyval.statement = CreateStatement(STM_IF, NULL, yyvsp[-1].statement)->addChild(yyvsp[0].statement)->setExpression(yyvsp[-1].expr);
		} else {
			// IF
			yyval.statement = CreateStatement(STM_IF, NULL, yyvsp[-1].statement)->setExpression(yyvsp[-1].expr);
		}
	;
    break;}
case 230:
#line 617 "csharp.y"
{ yyval.expr = yyvsp[-2].expr; yyval.statement = yyvsp[0].statement; ;
    break;}
case 231:
#line 620 "csharp.y"
{ yyval.statement = yyvsp[0].statement; ;
    break;}
case 232:
#line 621 "csharp.y"
{ yyval.statement = NULL; ;
    break;}
case 233:
#line 625 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_SWITCH, NULL, yyvsp[0].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 234:
#line 628 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement; ;
    break;}
case 235:
#line 631 "csharp.y"
{ R(); yyval.statement = NULL; ;
    break;}
case 236:
#line 632 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 237:
#line 635 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 238:
#line 636 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 239:
#line 639 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addChild(yyvsp[0].statement); ;
    break;}
case 240:
#line 642 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 241:
#line 643 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 242:
#line 646 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CASE, NULL, NULL		)->setExpression(yyvsp[-1].expr); ;
    break;}
case 243:
#line 647 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CASEDEFAULT, NULL, NULL); ;
    break;}
case 244:
#line 650 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 245:
#line 651 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 246:
#line 652 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 247:
#line 653 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 248:
#line 656 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_UNSAFE, NULL, yyvsp[0].statement); ;
    break;}
case 249:
#line 660 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WHILE, NULL, yyvsp[0].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 250:
#line 664 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_DOWHILE, NULL, yyvsp[-5].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 251:
#line 668 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_FOR, NULL, yyvsp[-7].statement)	->setExpression	 (yyvsp[-4].expr)
																	->addChildNilWrap(yyvsp[-6].statement)
																	->addChildNilWrap(yyvsp[-2].statement)
																	->addChildNilWrap(yyvsp[0].statement); ;
    break;}
case 252:
#line 674 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 253:
#line 675 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 254:
#line 678 "csharp.y"
{ R(); yyval.expr = NULL;		;
    break;}
case 255:
#line 679 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 256:
#line 682 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 257:
#line 683 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 258:
#line 686 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 259:
#line 687 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 260:
#line 690 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 261:
#line 693 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 262:
#line 696 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 263:
#line 697 "csharp.y"
{ R(); yyval.statement = yyvsp[-2].statement->addNext(yyvsp[0].statement); ;
    break;}
case 264:
#line 709 "csharp.y"
{
											R(); 
											const char* enumVar = makeUniqueId("enumerator");
											PushGenericType(GetGenericType());
											addGenericType(yyvsp[-5].type);
											// NOTE: Requires System.Collections.Generic;
											TypeObject* enumType =
												TypeObject::getTypeObject("IEnumerator", TYPE_UNRESOLVED)
												->setGeneric(GetGenericType());
											PopGenericType();

											yyval.statement =
												/* IEnumerator<T> enumerator = $6.GetEnumerator() */
												CreateVarStatement(
													STM_LOCALVAR,
													NULL, // next
													NULL, // child
													CreateVarInstance(
														enumVar
													)->setInitializer(
														CreateDoubleExpr(
															EXPR_INVOKE,
															CreateSingleExpr(EXPR_DOT, yyvsp[-2].expr)->setIdentifier("GetEnumerator"),
															NULL
														)->patchSubInvoke()
													),
													enumType
												) ->addNext(
													CreateStatement(STM_TRY, NULL, NULL)
													->addChild(
														CreateStatement(
															STM_BLOCK,
															NULL,
															CreateStatement(
																STM_WHILE, 
																NULL, 
																CreateStatement(
																	STM_BLOCK,
																	NULL,
																	CreateVarStatement(
																		STM_LOCALVAR,
																		yyvsp[0].statement, // next
																		NULL, // child
																		CreateVarInstance(
																			yyvsp[-4].text
																		)->setInitializer(
																			CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT, enumVar))->setIdentifier("Current")
																		),
																		yyvsp[-5].type
																	)
																)
															) -> setExpression(
																/* enumerator.MoveNext() */
																CreateDoubleExpr(
																	EXPR_INVOKE,
																	CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT, enumVar))->setIdentifier("MoveNext"),
																	NULL // no args
																)->patchSubInvoke()
															)
														)
													) -> addNext (
														CreateStatement(STM_FINALLY, NULL, NULL)
														->addChild(
															CreateStatement(
																STM_BLOCK,
																NULL,
																CreateStatement(STM_WRAP_EXP, NULL, NULL) -> setExpression(
																	/* enumerator.Dispose() */
																	CreateDoubleExpr(
																		EXPR_INVOKE,
																		CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT, enumVar))->setIdentifier("Dispose"),
																		NULL // no args
																	)->patchSubInvoke()
																)
															)
														)
													)
												);
										;
    break;}
case 265:
#line 790 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 266:
#line 791 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 267:
#line 792 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 268:
#line 793 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 269:
#line 794 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 270:
#line 797 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_BREAK, NULL, NULL); ;
    break;}
case 271:
#line 800 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CONTINUE, NULL, NULL); ;
    break;}
case 272:
#line 803 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTO, NULL,NULL)->addLabel(yyvsp[-1].text);	;
    break;}
case 273:
#line 804 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTOCASE, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 274:
#line 805 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTODEFAULT, NULL,NULL); ;
    break;}
case 275:
#line 808 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_RETURN, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 276:
#line 811 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 277:
#line 812 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 278:
#line 815 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_THROW, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 279:
#line 818 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-1].statement)->addNext(yyvsp[0].statement); 
										;
    break;}
case 280:
#line 821 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-1].statement)->addNext(yyvsp[0].statement);
										;
    break;}
case 281:
#line 825 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-2].statement)->addNext(yyvsp[-1].statement)->addNext(yyvsp[0].statement);
										;
    break;}
case 282:
#line 830 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 283:
#line 831 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 284:
#line 834 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CATCH, NULL, NULL)
														->addChild(yyvsp[0].statement)->addLabel(yyvsp[-2].text)->addType(yyvsp[-3].type); 
													;
    break;}
case 285:
#line 837 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CATCH, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 286:
#line 840 "csharp.y"
{ R(); yyval.text = NULL; ;
    break;}
case 287:
#line 841 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; ;
    break;}
case 288:
#line 844 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_FINALLY, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 289:
#line 847 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported 'checked' statement"); yyval.statement = CreateStatement(STM_CHECKED, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 290:
#line 850 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_UNCHECKED, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 291:
#line 853 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported 'lock' statement"); yyval.statement = CreateStatement(STM_LOCK, NULL, NULL)
														->addChild(yyvsp[0].statement)->setExpression(yyvsp[-2].expr);
													;
    break;}
case 292:
#line 859 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Unsupported 'using' statement"); yyval.statement = CreateStatement(STM_USING, NULL, NULL)->addChild(yyvsp[-2].statement)->addChild(yyvsp[0].statement); ;
    break;}
case 293:
#line 862 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement ;
    break;}
case 294:
#line 863 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement ;
    break;}
case 295:
#line 868 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"FIXED not supported."); ;
    break;}
case 296:
#line 871 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 297:
#line 872 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 298:
#line 875 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 299:
#line 884 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 300:
#line 885 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 301:
#line 888 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 302:
#line 889 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 303:
#line 892 "csharp.y"
{ R(); yyval.attribute = NULL; ;
    break;}
case 304:
#line 893 "csharp.y"
{ R(); yyval.attribute = yyvsp[0].attribute; ;
    break;}
case 305:
#line 896 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 306:
#line 897 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 307:
#line 900 "csharp.y"
{ R(); useOrCreateNameSpace(yyvsp[-2].attribute, yyvsp[0].text); ;
    break;}
case 308:
#line 901 "csharp.y"
{ R();	// Unstack.
										unuseNameSpace();		;
    break;}
case 309:
#line 905 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 310:
#line 906 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 311:
#line 915 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; 	display(yyvsp[0].text);		;
    break;}
case 312:
#line 916 "csharp.y"
{ R(); yyval.text = concat2(yyvsp[-1].text, yyvsp[0].text); 		;
    break;}
case 313:
#line 919 "csharp.y"
{ R(); yyval.text = concat2(yyvsp[-1].text, "."); 			;
    break;}
case 314:
#line 920 "csharp.y"
{ R(); yyval.text = concat3(yyvsp[-2].text, yyvsp[-1].text, "."); 	;
    break;}
case 315:
#line 924 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 316:
#line 927 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 317:
#line 928 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 318:
#line 931 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 319:
#line 932 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 320:
#line 935 "csharp.y"
{ R(); createAlias(yyvsp[-3].text, yyvsp[-1].text); 	;
    break;}
case 321:
#line 938 "csharp.y"
{ R(); addUsingNameSpace(yyvsp[-1].text); 		;
    break;}
case 322:
#line 941 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 323:
#line 942 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 324:
#line 945 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 325:
#line 946 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 326:
#line 949 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 327:
#line 950 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 328:
#line 951 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 329:
#line 952 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 330:
#line 953 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 331:
#line 964 "csharp.y"
{ R(); yyval.tmpValue = 0;				;
    break;}
case 332:
#line 965 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 	;
    break;}
case 333:
#line 968 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 				;
    break;}
case 334:
#line 969 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue | yyvsp[-1].tmpValue; 	;
    break;}
case 335:
#line 972 "csharp.y"
{ R(); yyval.tmpValue = ATT_ABSTRACT;	;
    break;}
case 336:
#line 973 "csharp.y"
{ R(); yyval.tmpValue = ATT_EXTERN;		;
    break;}
case 337:
#line 974 "csharp.y"
{ R(); yyval.tmpValue = ATT_INTERNAL;	;
    break;}
case 338:
#line 975 "csharp.y"
{ R(); yyval.tmpValue = ATT_NEW;		;
    break;}
case 339:
#line 976 "csharp.y"
{ R(); yyval.tmpValue = ATT_VIRTUAL;	;
    break;}
case 340:
#line 977 "csharp.y"
{ R(); yyval.tmpValue = ATT_PRIVATE;	;
    break;}
case 341:
#line 978 "csharp.y"
{ R(); yyval.tmpValue = ATT_PROTECTED;	;
    break;}
case 342:
#line 979 "csharp.y"
{ R(); yyval.tmpValue = ATT_PUBLIC;		;
    break;}
case 343:
#line 980 "csharp.y"
{ R(); yyval.tmpValue = ATT_READONLY;	;
    break;}
case 344:
#line 981 "csharp.y"
{ R(); yyval.tmpValue = ATT_SEALED;		;
    break;}
case 345:
#line 982 "csharp.y"
{ R(); yyval.tmpValue = ATT_STATIC;		;
    break;}
case 346:
#line 983 "csharp.y"
{ R(); yyval.tmpValue = ATT_UNSAFE;		;
    break;}
case 347:
#line 984 "csharp.y"
{ R(); yyval.tmpValue = ATT_VIRTUAL;	;
    break;}
case 348:
#line 985 "csharp.y"
{ R(); yyval.tmpValue = ATT_VOLATILE;	;
    break;}
case 349:
#line 986 "csharp.y"
{ R(); yyval.tmpValue = ATT_PARTIAL;	;
    break;}
case 350:
#line 991 "csharp.y"
{ R();
		gCurrentAC = CreateClass(	yyvsp[-4].attribute, 
						yyvsp[-3].tmpValue, 
						yyvsp[-1].text);
						
		gCurrentAC->setGenericParam();
	;
    break;}
case 351:
#line 997 "csharp.y"
{ R(); unuseNameSpace(); ;
    break;}
case 352:
#line 1001 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 353:
#line 1002 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 354:
#line 1005 "csharp.y"
{ R(); /* Do nothing */						;
    break;}
case 355:
#line 1008 "csharp.y"
{ R(); gCurrentAC->addInheritance(yyvsp[0].type);	;
    break;}
case 356:
#line 1009 "csharp.y"
{ R(); gCurrentAC->addInheritance(yyvsp[0].type);	;
    break;}
case 357:
#line 1012 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 358:
#line 1015 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 359:
#line 1016 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 360:
#line 1019 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 361:
#line 1020 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 362:
#line 1023 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 363:
#line 1024 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 364:
#line 1025 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 365:
#line 1026 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 366:
#line 1027 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 367:
#line 1028 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 368:
#line 1029 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 369:
#line 1030 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 370:
#line 1031 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 371:
#line 1033 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 372:
#line 1036 "csharp.y"
{ R();
																			// Trick : CONST C# is STATIC member in C++ to match C# behavior.
																			gCurrentAC->addVariable(yyvsp[-5].attribute, (yyvsp[-4].tmpValue & ~ATT_CONST) | ATT_STATIC, yyvsp[-2].type, yyvsp[-1].variable );	;
    break;}
case 373:
#line 1041 "csharp.y"
{ R(); gCurrentAC->addVariable(yyvsp[-4].attribute, yyvsp[-3].tmpValue, yyvsp[-2].type, yyvsp[-1].variable );				;
    break;}
case 374:
#line 1044 "csharp.y"
{ R(); gCurrentMethod = gCurrentAC->addMethod(
																			yyvsp[-1].attribute,	// Attributes
																			yyvsp[-1].tmpValue,	// Modified REF/OUT
																			yyvsp[-1].text,		// Func Name
																			yyvsp[-1].variable,	// Link list of variable
																			yyvsp[0].statement,	// Code
																			yyvsp[-1].type			// Return value.
																		 );
																		  gCurrentMethod->setGenericParam();
																		;
    break;}
case 375:
#line 1058 "csharp.y"
{ R(); 	yyval.attribute 	= yyvsp[-7].attribute; 
		yyval.tmpValue  	= yyvsp[-6].tmpValue;
		yyval.text			= yyvsp[-4].text;
		yyval.variable		= yyvsp[-1].variable;
		yyval.type			= yyvsp[-5].type;								;
    break;}
case 376:
#line 1064 "csharp.y"
{ R(); 	yyval.attribute 	= yyvsp[-7].attribute; 
		yyval.tmpValue  	= yyvsp[-6].tmpValue;
		yyval.text			= yyvsp[-4].text;
		yyval.variable		= yyvsp[-1].variable;
		yyval.type			= TypeObject::getTypeObject(TYPE_VOID);	;
    break;}
case 377:
#line 1072 "csharp.y"
{ R(); addGenericName(yyvsp[0].text); 	;
    break;}
case 378:
#line 1073 "csharp.y"
{ R(); addGenericName(yyvsp[0].text);		;
    break;}
case 379:
#line 1076 "csharp.y"
{ R(); ;
    break;}
case 380:
#line 1077 "csharp.y"
{ R(); ;
    break;}
case 381:
#line 1081 "csharp.y"
{ R(); yyval.variable = NULL;								;
    break;}
case 382:
#line 1082 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable;						;
    break;}
case 383:
#line 1085 "csharp.y"
{ R(); yyval.type = yyvsp[0].type;								;
    break;}
case 384:
#line 1086 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_VOID);	;
    break;}
case 385:
#line 1089 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;						;
    break;}
case 386:
#line 1090 "csharp.y"
{ R(); yyval.statement = NULL;								;
    break;}
case 387:
#line 1093 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable;							;
    break;}
case 388:
#line 1094 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[0].variable);	;
    break;}
case 389:
#line 1097 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable ;						;
    break;}
case 390:
#line 1098 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable ;						;
    break;}
case 391:
#line 1102 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-1].text)
														->setAttribute(yyvsp[-4].attribute)
														->setModifier(yyvsp[-3].tmpValue)
														->setType(yyvsp[-2].type)
														->setInitializer(yyvsp[0].expr);							;
    break;}
case 392:
#line 1109 "csharp.y"
{ R();  yyval.expr		= NULL;								;
    break;}
case 393:
#line 1110 "csharp.y"
{ R();  yyval.expr		= yyvsp[0].expr;							;
    break;}
case 394:
#line 1113 "csharp.y"
{ R();	yyval.tmpValue	= 0;								;
    break;}
case 395:
#line 1114 "csharp.y"
{ R();	yyval.tmpValue = ATT_REF;							;
    break;}
case 396:
#line 1115 "csharp.y"
{ R();	yyval.tmpValue	= ATT_REF;							;
    break;}
case 397:
#line 1119 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[0].text)
														->setType(yyvsp[-1].type)
														->setAttribute(yyvsp[-3].attribute)
														->setIsEndLessParam();
														compilerError(ERR_NOT_SUPPORTED_YET, "params keyword is not supported");
													;
    break;}
case 398:
#line 1130 "csharp.y"
{ R(); gCurrentAC->addProperty(yyvsp[-8].attribute, yyvsp[-7].tmpValue, yyvsp[-6].type, yyvsp[-5].text, yyvsp[-2].accessor);	;
    break;}
case 399:
#line 1133 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(yyvsp[-1].accessor, yyvsp[0].accessor);	;
    break;}
case 400:
#line 1134 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(yyvsp[0].accessor, yyvsp[-1].accessor);	;
    break;}
case 401:
#line 1135 "csharp.y"
{ R(); yyval.accessor = CreateAccessor((Accessor*)NULL,(Accessor*)NULL); ;
    break;}
case 402:
#line 1138 "csharp.y"
{ R(); yyval.accessor = NULL;			;
    break;}
case 403:
#line 1139 "csharp.y"
{ R(); yyval.accessor = yyvsp[0].accessor;	;
    break;}
case 404:
#line 1142 "csharp.y"
{ R(); yyval.accessor = NULL;			;
    break;}
case 405:
#line 1143 "csharp.y"
{ R(); yyval.accessor = yyvsp[0].accessor;	;
    break;}
case 406:
#line 1149 "csharp.y"
{ R(); yyval.accessor  = CreateAccessor(yyvsp[-4].attribute, yyvsp[-1].statement);	;
    break;}
case 407:
#line 1155 "csharp.y"
{ R(); yyval.accessor  = CreateAccessor(yyvsp[-4].attribute, yyvsp[-1].statement);	;
    break;}
case 408:
#line 1158 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; 	;
    break;}
case 409:
#line 1159 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 410:
#line 1162 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 411:
#line 1166 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 412:
#line 1169 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 413:
#line 1170 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 414:
#line 1176 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 415:
#line 1182 "csharp.y"
{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	;
    break;}
case 416:
#line 1189 "csharp.y"
{	R();
		yyvsp[-2].accessor->setAsIndexer(yyvsp[-5].type, yyvsp[-5].variable);
		gCurrentAC->addProperty(yyvsp[-7].attribute, yyvsp[-6].tmpValue, yyvsp[-2].accessor);
	;
    break;}
case 417:
#line 1195 "csharp.y"
{ R(); yyval.variable  = yyvsp[-1].variable; yyval.type = yyvsp[-4].type; ;
    break;}
case 418:
#line 1197 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Explicit implementation of an interface indexer is not supported yet"); ;
    break;}
case 419:
#line 1200 "csharp.y"
{ R(); yyval.text = concat2(yyvsp[-1].text, "this"); ;
    break;}
case 420:
#line 1204 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 421:
#line 1207 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 422:
#line 1208 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 423:
#line 1211 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Overloading operator not supported."); ;
    break;}
case 424:
#line 1212 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Overloading operator not supported."); ;
    break;}
case 425:
#line 1215 "csharp.y"
{ R(); yyval.tmpValue = OP_PLUS;  ;
    break;}
case 426:
#line 1216 "csharp.y"
{ R(); yyval.tmpValue = OP_MINUS; ;
    break;}
case 427:
#line 1217 "csharp.y"
{ R(); yyval.tmpValue = OP_LNOT;  ;
    break;}
case 428:
#line 1218 "csharp.y"
{ R(); yyval.tmpValue = OP_NOT;   ;
    break;}
case 429:
#line 1219 "csharp.y"
{ R(); yyval.tmpValue = OP_PLUSPLUS;   ;
    break;}
case 430:
#line 1220 "csharp.y"
{ R(); yyval.tmpValue = OP_MINUSMINUS; ;
    break;}
case 431:
#line 1221 "csharp.y"
{ R(); yyval.tmpValue = OP_TRUE;  ;
    break;}
case 432:
#line 1222 "csharp.y"
{ R(); yyval.tmpValue = OP_FALSE; ;
    break;}
case 433:
#line 1223 "csharp.y"
{ R(); yyval.tmpValue = OP_MULT;  ;
    break;}
case 434:
#line 1224 "csharp.y"
{ R(); yyval.tmpValue = OP_DIV;   ;
    break;}
case 435:
#line 1225 "csharp.y"
{ R(); yyval.tmpValue = OP_MOD;   ;
    break;}
case 436:
#line 1226 "csharp.y"
{ R(); yyval.tmpValue = OP_AND;   ;
    break;}
case 437:
#line 1227 "csharp.y"
{ R(); yyval.tmpValue = OP_OR;    ;
    break;}
case 438:
#line 1228 "csharp.y"
{ R(); yyval.tmpValue = OP_XOR;   ;
    break;}
case 439:
#line 1229 "csharp.y"
{ R(); yyval.tmpValue = OP_LSHFT; ;
    break;}
case 440:
#line 1230 "csharp.y"
{ R(); yyval.tmpValue = OP_RSHFT; ;
    break;}
case 441:
#line 1231 "csharp.y"
{ R(); yyval.tmpValue = OP_EQUAL; ;
    break;}
case 442:
#line 1232 "csharp.y"
{ R(); yyval.tmpValue = OP_DIFF;  ;
    break;}
case 443:
#line 1233 "csharp.y"
{ R(); yyval.tmpValue = OP_MORE;  ;
    break;}
case 444:
#line 1234 "csharp.y"
{ R(); yyval.tmpValue = OP_LESS;  ;
    break;}
case 445:
#line 1235 "csharp.y"
{ R(); yyval.tmpValue = OP_MOREEQ;;
    break;}
case 446:
#line 1236 "csharp.y"
{ R(); yyval.tmpValue = OP_LESSEQ;;
    break;}
case 447:
#line 1240 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 448:
#line 1241 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 449:
#line 1244 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addConstructor(
			yyvsp[-3].attribute,	// Attributes
			yyvsp[-2].tmpValue,	// Modifier
			yyvsp[-1].text,		// Func Name
			yyvsp[-1].variable,	// Link list of variable
			yyvsp[0].statement,	// Code
			yyvsp[-1].expr,		// Call to Base or this with arguments.
			yyvsp[-1].tmpValue		// -1 : Nothing, 0 : Base Call, 1 : This Call.
		);
	;
    break;}
case 450:
#line 1257 "csharp.y"
{ R(); 	yyval.text		= yyvsp[-4].text; 
																					yyval.variable = yyvsp[-2].variable; 
																					yyval.expr		= yyvsp[0].expr; 
																					yyval.tmpValue	= yyvsp[0].tmpValue;
																				;
    break;}
case 451:
#line 1264 "csharp.y"
{ R(); yyval.expr	= NULL;		yyval.tmpValue = -1;			;
    break;}
case 452:
#line 1265 "csharp.y"
{ R(); yyval.expr	= yyvsp[0].expr;	yyval.tmpValue = yyvsp[0].tmpValue;	;
    break;}
case 453:
#line 1268 "csharp.y"
{ R(); yyval.expr			= yyvsp[-1].expr;	yyval.tmpValue = 0;	;
    break;}
case 454:
#line 1269 "csharp.y"
{ R(); yyval.expr			= yyvsp[-1].expr;	yyval.tmpValue = 1; compilerError(ERR_NOT_SUPPORTED_YET,"'this' access in constructor initialization is not supported yet."); ;
    break;}
case 455:
#line 1285 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addDestructor(
			yyvsp[-6].attribute,	// Attributes
			yyvsp[-5].tmpValue,	// Modifier
			yyvsp[-3].text,		// Func Name
			yyvsp[0].statement
		);
  ;
    break;}
case 456:
#line 1295 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 457:
#line 1296 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 458:
#line 1299 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 459:
#line 1300 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 460:
#line 1305 "csharp.y"
{ R(); 	gCurrentAC = CreateStruct(	yyvsp[-3].attribute, 
																					yyvsp[-2].tmpValue, 
																					yyvsp[0].text
																				); 
													;
    break;}
case 461:
#line 1310 "csharp.y"
{ R(); unuseNameSpace(); ;
    break;}
case 462:
#line 1313 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 463:
#line 1314 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 464:
#line 1317 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 465:
#line 1320 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 466:
#line 1323 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 467:
#line 1324 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 468:
#line 1327 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 469:
#line 1328 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 470:
#line 1331 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 471:
#line 1332 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 472:
#line 1333 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 473:
#line 1334 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 474:
#line 1335 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 475:
#line 1336 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 476:
#line 1337 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 477:
#line 1338 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 478:
#line 1340 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 479:
#line 1345 "csharp.y"
{ GenerateInitList(); ;
    break;}
case 480:
#line 1345 "csharp.y"
{ R(); PopInitList(); yyval.expr = yyvsp[-1].expr; 	;
    break;}
case 481:
#line 1348 "csharp.y"
{ R(); yyval.expr = NULL; 			;
    break;}
case 482:
#line 1349 "csharp.y"
{ R(); yyval.expr = yyvsp[-1].expr; 		;
    break;}
case 485:
#line 1357 "csharp.y"
{ R(); yyval.expr = getInitList()->addExpression(yyvsp[0].expr);	;
    break;}
case 486:
#line 1358 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[0].expr); 		;
    break;}
case 487:
#line 1363 "csharp.y"
{ R(); 	gCurrentAC = CreateInterface(	yyvsp[-3].attribute, 
																								yyvsp[-2].tmpValue, 
																								yyvsp[0].text);
														;
    break;}
case 488:
#line 1368 "csharp.y"
{ R();  unuseNameSpace(); ;
    break;}
case 489:
#line 1371 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 490:
#line 1372 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 491:
#line 1375 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 492:
#line 1378 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 493:
#line 1381 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 494:
#line 1382 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 495:
#line 1385 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 496:
#line 1386 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 497:
#line 1389 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 498:
#line 1390 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 499:
#line 1391 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 500:
#line 1392 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 501:
#line 1396 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addMethod(
			yyvsp[-7].attribute,	// Attributes
			yyvsp[-6].tmpValue,
			yyvsp[-4].text,		// Func Name
			yyvsp[-2].variable,	// Link list of variable
			yyvsp[0].statement,	// Code
			yyvsp[-5].type			// Return value.
		);	
	;
    break;}
case 502:
#line 1406 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addMethod(
			yyvsp[-7].attribute,	// Attributes
			yyvsp[-6].tmpValue,
			yyvsp[-4].text,		// Func Name
			yyvsp[-2].variable,	// Link list of variable
			yyvsp[0].statement,	// Code
			TypeObject::getTypeObject(TYPE_VOID)	// Return value.
		);
	;
    break;}
case 503:
#line 1418 "csharp.y"
{ R(); yyval.tmpValue = 0; 			;
    break;}
case 504:
#line 1419 "csharp.y"
{ R(); yyval.tmpValue = ATTR_NEW; 	;
    break;}
case 505:
#line 1425 "csharp.y"
{ R(); gCurrentAC->addProperty(yyvsp[-8].attribute, yyvsp[-7].tmpValue, yyvsp[-6].type, yyvsp[-5].text, yyvsp[-2].accessor);	;
    break;}
case 506:
#line 1432 "csharp.y"
{ R(); yyvsp[-2].accessor->setAsIndexer(yyvsp[-9].type, yyvsp[-6].variable); gCurrentAC->addProperty(yyvsp[-11].attribute, yyvsp[-10].tmpValue, yyvsp[-2].accessor);	;
    break;}
case 507:
#line 1436 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-2].attribute,NULL), NULL); ;
    break;}
case 508:
#line 1437 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(NULL, CreateAccessor(yyvsp[-2].attribute,NULL)); ;
    break;}
case 509:
#line 1438 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-5].attribute,NULL), CreateAccessor(yyvsp[-2].attribute,NULL)); ;
    break;}
case 510:
#line 1439 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-2].attribute,NULL), CreateAccessor(yyvsp[-5].attribute,NULL)); ;
    break;}
case 511:
#line 1442 "csharp.y"
{ R(); compilerError(ERR_NOT_SUPPORTED,"event not supported"); ;
    break;}
case 512:
#line 1447 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 513:
#line 1448 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 514:
#line 1453 "csharp.y"
{ R();
		gCurrEnum = CreateEnum(yyvsp[-4].attribute, yyvsp[-3].tmpValue, yyvsp[-1].text, yyvsp[0].type);
  ;
    break;}
case 515:
#line 1455 "csharp.y"
{ R();
	// Do nothing.
  ;
    break;}
case 516:
#line 1460 "csharp.y"
{ R(); yyval.type = NULL;    ;
    break;}
case 517:
#line 1461 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 518:
#line 1464 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 519:
#line 1467 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 520:
#line 1468 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 522:
#line 1472 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 523:
#line 1475 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 524:
#line 1476 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 525:
#line 1479 "csharp.y"
{ R(); gCurrEnum->addEntry(yyvsp[-1].attribute, yyvsp[0].text, NULL); ;
    break;}
case 526:
#line 1480 "csharp.y"
{ R(); gCurrEnum->addEntry(yyvsp[-3].attribute, yyvsp[-2].text, yyvsp[0].expr); ;
    break;}
case 527:
#line 1486 "csharp.y"
{ R(); CreateDelegate(yyvsp[-9].attribute, yyvsp[-8].tmpValue, yyvsp[-6].type, yyvsp[-5].text, yyvsp[-2].variable)->setGenericParam(); ;
    break;}
case 528:
#line 1491 "csharp.y"
{ R(); yyval.attribute = yyvsp[0].attribute; ;
    break;}
case 529:
#line 1494 "csharp.y"
{ R(); yyval.attribute = CreateAttributeWithChild(yyvsp[0].attribute); 		;
    break;}
case 530:
#line 1495 "csharp.y"
{ R(); yyval.attribute = yyvsp[-1].attribute->addChildAttribute(yyvsp[0].attribute); ;
    break;}
case 531:
#line 1499 "csharp.y"
{ R();	yyval.attribute = yyvsp[-2].attribute->setSpecifier(yyvsp[-3].tmpValue); ;
    break;}
case 532:
#line 1501 "csharp.y"
{ R();	yyval.attribute = yyvsp[-3].attribute->setSpecifier(yyvsp[-4].tmpValue); ;
    break;}
case 533:
#line 1504 "csharp.y"
{ R(); yyval.tmpValue = 0; 					;
    break;}
case 534:
#line 1505 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 		;
    break;}
case 535:
#line 1508 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[-1].tmpValue; 		;
    break;}
case 536:
#line 1511 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_ASSEMBLY ; 	;
    break;}
case 537:
#line 1512 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_FIELD;		;
    break;}
case 538:
#line 1513 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_EVENT;		;
    break;}
case 539:
#line 1514 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_METHOD;		;
    break;}
case 540:
#line 1515 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_MODULE;		;
    break;}
case 541:
#line 1516 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_PARAM;		;
    break;}
case 542:
#line 1517 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_PROPERTY;	;
    break;}
case 543:
#line 1518 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_RETURN;		;
    break;}
case 544:
#line 1519 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_TYPE;		;
    break;}
case 545:
#line 1522 "csharp.y"
{ R(); yyval.attribute = CreateAttribute(yyvsp[0].type, yyvsp[0].expr);				;
    break;}
case 546:
#line 1523 "csharp.y"
{ R(); yyval.attribute = yyvsp[-2].attribute->addAttribute(yyvsp[0].type, yyvsp[0].expr); ;
    break;}
case 547:
#line 1526 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type; yyval.expr= yyvsp[0].expr; ;
    break;}
case 548:
#line 1529 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 549:
#line 1530 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr ; 	;
    break;}
case 550:
#line 1533 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; 	;
    break;}
case 551:
#line 1536 "csharp.y"
{ R(); yyval.expr = yyvsp[-1].expr ; 	;
    break;}
case 552:
#line 1543 "csharp.y"
{ R(); lex_enter_attrib(); 	/*Do nothing*/ ;
    break;}
case 553:
#line 1546 "csharp.y"
{ R(); lex_exit_attrib(); 	/*Do nothing*/ ;
    break;}
case 554:
#line 1549 "csharp.y"
{ R(); lex_enter_accessor();	/*Do nothing*/ ;
    break;}
case 555:
#line 1552 "csharp.y"
{ R(); lex_exit_accessor();	/*Do nothing*/ ;
    break;}
case 556:
#line 1555 "csharp.y"
{ R(); lex_enter_getset();	/*Do nothing*/ ;
    break;}
case 557:
#line 1558 "csharp.y"
{ R(); lex_exit_getset();	/*Do nothing*/ ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 1562 "csharp.y"


#include <stdio.h>
#include "lexParser.inc"

int runCompiler(const char *str)
{
	//
	// Setup to avoid using files in Lex
	//
	YY_BUFFER_STATE pState = yy_scan_string(str);
	yy_switch_to_buffer(pState);

	yyparse();

	//
	// Destroy lex read context.
	//
	yy_delete_buffer(pState);

	return 0;
}


void yyerror(const char* s) {
  fprintf(stdout,"%d:%s LA=[%s]\n",yylineno,s,yytname[YYTRANSLATE(yychar)]);
  while (1) {
	// Endless loop.
  }
}

int isatty(int fildes) {
	return 1;	// unistd descriptor used by parser, but we use memory stream. Always 1.
}

void error (const char* msg,...) {
	va_list	argp;
	char pszBuf [1024];
	char log [1024];

	va_start(argp, msg);
	VSPRINTF( pszBuf, msg, argp);
	va_end(argp);

	SPRINTF(log, "Line %i : %s @%s\n", yylineno, pszBuf, yytext);

	printf(log);
}

int uniqueIdCount = 0;
const char* makeUniqueId(const char* body) {
	char buf[10];
	_itoa(uniqueIdCount++, buf, 10);
	return concat3("__", body, buf);
}
