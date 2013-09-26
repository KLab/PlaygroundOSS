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

#define	RANK_SPECIFIER	258
#define	IDENTIFIER	259
#define	INTEGER_LITERAL	260
#define	REAL_LITERAL	261
#define	CHARACTER_LITERAL	262
#define	STRING_LITERAL	263
#define	ABSTRACT	264
#define	AS	265
#define	BASE	266
#define	BOOL	267
#define	BREAK	268
#define	BYTE	269
#define	CASE	270
#define	CATCH	271
#define	CHAR	272
#define	CHECKED	273
#define	CLASS	274
#define	CONST	275
#define	CONTINUE	276
#define	DECIMAL	277
#define	DEFAULT	278
#define	DELEGATE	279
#define	DO	280
#define	DOUBLE	281
#define	ELSE	282
#define	ENUM	283
#define	EVENT	284
#define	EXPLICIT	285
#define	EXTERN	286
#define	FALSE	287
#define	FINALLY	288
#define	FIXED	289
#define	FLOAT	290
#define	FOR	291
#define	FOREACH	292
#define	GOTO	293
#define	IF	294
#define	IMPLICIT	295
#define	IN	296
#define	INT	297
#define	INTERFACE	298
#define	INTERNAL	299
#define	IS	300
#define	LOCK	301
#define	LONG	302
#define	NAMESPACE	303
#define	NEW	304
#define	NULL_LITERAL	305
#define	OBJECT	306
#define	OPERATOR	307
#define	OUT	308
#define	OVERRIDE	309
#define	PARAMS	310
#define	PRIVATE	311
#define	PROTECTED	312
#define	PUBLIC	313
#define	READONLY	314
#define	REF	315
#define	RETURN	316
#define	SBYTE	317
#define	SEALED	318
#define	SHORT	319
#define	SIZEOF	320
#define	STACKALLOC	321
#define	STATIC	322
#define	STRING	323
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
#define	ASSEMBLY	341
#define	FIELD	342
#define	METHOD	343
#define	MODULE	344
#define	PARAM	345
#define	PROPERTY	346
#define	TYPE	347
#define	GET	348
#define	SET	349
#define	ADD	350
#define	REMOVE	351
#define	COMMA	352
#define	LEFT_BRACKET	353
#define	RIGHT_BRACKET	354
#define	GT	355
#define	PLUSEQ	356
#define	MINUSEQ	357
#define	STAREQ	358
#define	DIVEQ	359
#define	MODEQ	360
#define	XOREQ	361
#define	ANDEQ	362
#define	OREQ	363
#define	LTLT	364
#define	GTGTEQ	365
#define	LTLTEQ	366
#define	EQEQ	367
#define	NOTEQ	368
#define	LEQ	369
#define	GEQ	370
#define	ANDAND	371
#define	OROR	372
#define	PLUSPLUS	373
#define	MINUSMINUS	374
#define	ARROW	375

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



#define	YYFINAL		932
#define	YYFLAG		-32768
#define	YYNTBASE	142

#define YYTRANSLATE(x) ((unsigned)(x) <= 375 ? yytranslate[x] : 396)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   127,     2,     2,     2,   132,   126,     2,   123,
   124,   122,   129,     2,   130,   125,   131,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   137,   141,   121,
   138,   133,   136,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,   134,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   139,   135,   140,   128,     2,     2,     2,     2,
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
   116,   117,   118,   119,   120
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
    21,    22,    25,    29,    32,    36,    37,    38,    40,    42,
    44,    46,    48,    50,    52,    54,    56,    58,    60,    62,
    64,    66,    68,    70,    72,    74,    76,    78,    80,    82,
    84,    86,    88,    91,    94,    97,   100,   103,   104,   107,
   109,   111,   113,   117,   119,   122,   125,   127,   129,   131,
   133,   135,   137,   139,   141,   143,   145,   147,   149,   151,
   153,   157,   161,   165,   169,   174,   179,   180,   182,   187,
   192,   193,   195,   197,   201,   203,   207,   212,   215,   218,
   220,   226,   234,   238,   239,   241,   246,   251,   256,   261,
   265,   268,   273,   275,   277,   279,   281,   283,   285,   288,
   291,   293,   296,   299,   301,   304,   307,   310,   312,   314,
   316,   321,   327,   334,   340,   346,   352,   353,   355,   357,
   360,   362,   364,   366,   370,   374,   378,   380,   384,   388,
   390,   394,   396,   400,   404,   408,   412,   416,   420,   422,
   426,   430,   432,   436,   438,   442,   444,   448,   450,   454,
   456,   460,   462,   468,   472,   474,   476,   478,   480,   482,
   484,   486,   488,   490,   492,   494,   496,   498,   500,   502,
   504,   506,   508,   510,   512,   514,   516,   518,   520,   522,
   524,   526,   528,   530,   532,   534,   538,   539,   541,   543,
   546,   548,   552,   555,   558,   561,   563,   567,   569,   573,
   575,   577,   579,   585,   589,   591,   595,   599,   602,   604,
   606,   608,   610,   612,   614,   616,   618,   620,   626,   634,
   640,   644,   645,   647,   649,   652,   655,   657,   660,   664,
   667,   669,   671,   673,   675,   678,   684,   692,   702,   703,
   705,   706,   708,   709,   711,   713,   715,   717,   719,   721,
   725,   734,   736,   738,   740,   742,   744,   747,   750,   754,
   759,   763,   767,   768,   770,   774,   778,   782,   787,   789,
   792,   799,   806,   809,   810,   812,   815,   818,   821,   827,
   833,   835,   837,   844,   846,   850,   854,   857,   860,   861,
   863,   864,   866,   867,   869,   870,   877,   878,   880,   882,
   885,   888,   892,   897,   899,   902,   904,   906,   912,   916,
   918,   921,   923,   925,   927,   929,   931,   933,   935,   936,
   938,   940,   943,   945,   947,   949,   951,   953,   955,   957,
   959,   961,   963,   965,   967,   969,   971,   972,   981,   982,
   984,   987,   990,   995,   997,  1001,  1005,  1006,  1008,  1010,
  1013,  1015,  1017,  1019,  1021,  1023,  1025,  1027,  1029,  1031,
  1033,  1040,  1046,  1049,  1057,  1065,  1066,  1068,  1070,  1072,
  1074,  1076,  1078,  1082,  1084,  1086,  1092,  1093,  1096,  1097,
  1099,  1101,  1106,  1116,  1119,  1122,  1123,  1124,  1126,  1127,
  1129,  1135,  1141,  1143,  1145,  1152,  1163,  1166,  1169,  1175,
  1181,  1182,  1192,  1198,  1204,  1207,  1212,  1214,  1216,  1224,
  1235,  1237,  1239,  1241,  1243,  1245,  1247,  1249,  1251,  1253,
  1255,  1257,  1259,  1261,  1263,  1265,  1267,  1269,  1272,  1274,
  1276,  1278,  1280,  1281,  1289,  1297,  1302,  1308,  1309,  1311,
  1317,  1323,  1331,  1333,  1335,  1337,  1339,  1340,  1349,  1350,
  1352,  1355,  1359,  1360,  1362,  1364,  1367,  1369,  1371,  1373,
  1375,  1377,  1379,  1381,  1383,  1385,  1389,  1394,  1395,  1397,
  1399,  1403,  1404,  1413,  1414,  1416,  1419,  1423,  1424,  1426,
  1428,  1431,  1433,  1435,  1437,  1439,  1448,  1457,  1458,  1460,
  1470,  1483,  1487,  1491,  1498,  1505,  1512,  1514,  1517,  1518,
  1527,  1528,  1530,  1533,  1537,  1542,  1543,  1545,  1547,  1551,
  1554,  1559,  1569,  1571,  1573,  1576,  1583,  1591,  1592,  1594,
  1597,  1599,  1601,  1603,  1605,  1607,  1609,  1611,  1613,  1615,
  1617,  1621,  1624,  1625,  1627,  1629,  1633,  1634,  1635,  1636,
  1637,  1638
};

static const short yyrhs[] = {   143,
     0,     5,     0,     6,     0,     7,     0,     8,     0,    50,
     0,    73,     0,    32,     0,   281,     0,   281,   146,     0,
     0,   121,   147,     0,   151,   149,   148,     0,   100,   150,
     0,    97,   150,   147,     0,     0,     0,   152,     0,   160,
     0,   153,     0,   145,     0,   154,     0,   158,     0,   159,
     0,   155,     0,    12,     0,   156,     0,   157,     0,    22,
     0,    62,     0,    14,     0,    64,     0,    80,     0,    42,
     0,    76,     0,    47,     0,    77,     0,    17,     0,    35,
     0,    26,     0,    51,     0,    68,     0,   151,   122,     0,
    83,   122,     0,   160,   162,     0,   153,   162,     0,   281,
   162,     0,     0,   162,   161,     0,     3,     0,   211,     0,
   165,     0,   164,    97,   165,     0,   211,     0,    60,   163,
     0,    53,   163,     0,   168,     0,   167,     0,   142,     0,
   181,     0,   169,     0,   170,     0,   172,     0,   175,     0,
   176,     0,   179,     0,   183,     0,   188,     0,   184,     0,
   185,     0,   123,   211,   124,     0,   166,   125,     4,     0,
   154,   125,     4,     0,   158,   125,     4,     0,   167,   123,
   171,   124,     0,   281,   123,   171,   124,     0,     0,   164,
     0,   166,    98,   174,    99,     0,   281,    98,   174,    99,
     0,     0,   174,     0,   211,     0,   174,    97,   211,     0,
    71,     0,    11,   125,     4,     0,    11,    98,   174,    99,
     0,   189,   118,     0,   189,   119,     0,   180,     0,    49,
   151,   123,   171,   124,     0,    49,   152,    98,   174,    99,
   161,   182,     0,    49,   160,   352,     0,     0,   352,     0,
    75,   123,   151,   124,     0,    75,   123,    83,   124,     0,
    18,   123,   211,   124,     0,    78,   123,   211,   124,     0,
   189,   120,     4,     0,   126,   193,     0,    65,   123,   151,
   124,     0,   166,     0,   281,     0,   177,     0,   178,     0,
   186,     0,   189,     0,   127,   193,     0,   128,   193,     0,
   194,     0,   118,   193,     0,   119,   193,     0,   190,     0,
   129,   193,     0,   130,   193,     0,   122,   193,     0,   191,
     0,   192,     0,   187,     0,   123,   211,   124,   190,     0,
   123,   198,   122,   124,   193,     0,   123,   281,   162,   195,
   124,   193,     0,   123,   154,   195,   124,   193,     0,   123,
   158,   195,   124,   193,     0,   123,    83,   195,   124,   193,
     0,     0,   196,     0,   197,     0,   196,   197,     0,   162,
     0,   122,     0,   193,     0,   198,   122,   193,     0,   198,
   131,   193,     0,   198,   132,   193,     0,   198,     0,   199,
   129,   198,     0,   199,   130,   198,     0,   199,     0,   200,
   109,   199,     0,   200,     0,   201,   121,   200,     0,   201,
   133,   200,     0,   201,   114,   200,     0,   201,   115,   200,
     0,   201,    45,   151,     0,   201,    10,   151,     0,   201,
     0,   202,   112,   201,     0,   202,   113,   201,     0,   202,
     0,   203,   126,   202,     0,   203,     0,   204,   134,   203,
     0,   204,     0,   205,   135,   204,     0,   205,     0,   206,
   116,   205,     0,   206,     0,   207,   117,   206,     0,   207,
     0,   207,   136,   211,   137,   211,     0,   193,   210,   211,
     0,   138,     0,   101,     0,   102,     0,   103,     0,   104,
     0,   105,     0,   106,     0,   107,     0,   108,     0,   110,
     0,   111,     0,   208,     0,   209,     0,   211,     0,   211,
     0,   220,     0,   221,     0,   215,     0,   216,     0,   219,
     0,   230,     0,   232,     0,   241,     0,   254,     0,   261,
     0,   266,     0,   267,     0,   268,     0,   269,     0,   242,
     0,   271,     0,   139,   217,   140,     0,     0,   218,     0,
   214,     0,   218,   214,     0,   141,     0,     4,   137,   214,
     0,   222,   141,     0,   227,   141,     0,   151,   223,     0,
   224,     0,   223,    97,   224,     0,     4,     0,     4,   138,
   225,     0,   211,     0,   352,     0,   226,     0,    66,   151,
    98,   211,    99,     0,    20,   151,   228,     0,   229,     0,
   228,    97,   229,     0,     4,   138,   212,     0,   231,   141,
     0,   170,     0,   180,     0,   209,     0,   177,     0,   178,
     0,   191,     0,   192,     0,   233,     0,   234,     0,    39,
   123,   213,   124,   215,     0,    39,   123,   213,   124,   215,
    27,   215,     0,    70,   123,   211,   124,   235,     0,   139,
   236,   140,     0,     0,   237,     0,   238,     0,   237,   238,
     0,   239,   218,     0,   240,     0,   239,   240,     0,    15,
   212,   137,     0,    23,   137,     0,   243,     0,   244,     0,
   245,     0,   253,     0,    79,   216,     0,    85,   123,   213,
   124,   215,     0,    25,   215,    85,   123,   213,   124,   141,
     0,    36,   123,   246,   141,   247,   141,   248,   124,   215,
     0,     0,   249,     0,     0,   250,     0,     0,   251,     0,
   222,     0,   252,     0,   213,     0,   252,     0,   231,     0,
   252,    97,   231,     0,    37,   123,   151,     4,    41,   211,
   124,   215,     0,   255,     0,   256,     0,   257,     0,   258,
     0,   260,     0,    13,   141,     0,    21,   141,     0,    38,
     4,   141,     0,    38,    15,   212,   141,     0,    38,    23,
   141,     0,    61,   259,   141,     0,     0,   211,     0,    72,
   259,   141,     0,    74,   216,   262,     0,    74,   216,   265,
     0,    74,   216,   262,   265,     0,   263,     0,   262,   263,
     0,    16,   123,   158,   264,   124,   216,     0,    16,   123,
   145,   264,   124,   216,     0,    16,   216,     0,     0,     4,
     0,    33,   216,     0,    18,   216,     0,    78,   216,     0,
    46,   123,   211,   124,   215,     0,    81,   123,   270,   124,
   215,     0,   222,     0,   211,     0,    34,   123,   151,   272,
   124,   215,     0,   273,     0,   272,    97,   273,     0,     4,
   138,   211,     0,   275,   276,     0,   275,   288,     0,     0,
   284,     0,     0,   379,     0,     0,   288,     0,     0,   276,
    48,   281,   279,   283,   280,     0,     0,   141,     0,     4,
     0,   282,     4,     0,     4,   125,     0,   282,     4,   125,
     0,   139,   275,   277,   140,     0,   285,     0,   284,   285,
     0,   286,     0,   287,     0,    81,     4,   138,   281,   141,
     0,    81,   144,   141,     0,   289,     0,   288,   289,     0,
   278,     0,   290,     0,   294,     0,   344,     0,   355,     0,
   370,     0,   378,     0,     0,   292,     0,   293,     0,   292,
   293,     0,     9,     0,    31,     0,    44,     0,    49,     0,
    54,     0,    56,     0,    57,     0,    58,     0,    59,     0,
    63,     0,    67,     0,    79,     0,    82,     0,    84,     0,
     0,   276,   291,    19,     4,   295,   296,   299,   280,     0,
     0,   297,     0,   137,   158,     0,   137,   298,     0,   137,
   158,    97,   298,     0,   145,     0,   298,    97,   145,     0,
   139,   300,   140,     0,     0,   301,     0,   302,     0,   301,
   302,     0,   303,     0,   304,     0,   305,     0,   316,     0,
   323,     0,   327,     0,   331,     0,   337,     0,   341,     0,
   290,     0,   276,   291,    20,   151,   228,   141,     0,   276,
   291,   151,   223,   141,     0,   306,   309,     0,   276,   291,
   151,   281,   123,   307,   124,     0,   276,   291,    83,   281,
   123,   307,   124,     0,     0,   310,     0,   151,     0,    83,
     0,   216,     0,   141,     0,   311,     0,   310,    97,   311,
     0,   312,     0,   315,     0,   276,   314,   151,     4,   313,
     0,     0,   138,   142,     0,     0,    60,     0,    53,     0,
   276,    55,   151,     4,     0,   276,   291,   151,   281,   394,
   139,   317,   140,   395,     0,   320,   318,     0,   321,   319,
     0,     0,     0,   321,     0,     0,   320,     0,   276,    93,
   395,   322,   394,     0,   276,    94,   395,   322,   394,     0,
   216,     0,   141,     0,   276,   291,    29,   151,   223,   141,
     0,   276,   291,    29,   151,   281,   392,   139,   324,   140,
   393,     0,   325,   326,     0,   326,   325,     0,   276,    95,
   393,   216,   392,     0,   276,    96,   393,   216,   392,     0,
     0,   276,   291,   329,   328,   394,   139,   317,   140,   395,
     0,   151,    71,    98,   310,    99,     0,   151,   330,    98,
   310,    99,     0,   282,    71,     0,   276,   291,   332,   342,
     0,   333,     0,   336,     0,   151,    52,   334,   123,   151,
     4,   124,     0,   151,    52,   334,   123,   151,     4,    97,
   151,     4,   124,     0,   129,     0,   130,     0,   127,     0,
   128,     0,   118,     0,   119,     0,    73,     0,    32,     0,
   122,     0,   131,     0,   132,     0,   126,     0,   135,     0,
   134,     0,   109,     0,   112,     0,   113,     0,   133,   335,
     0,   121,     0,   115,     0,   114,     0,   100,     0,     0,
    40,    52,   151,   123,   151,     4,   124,     0,    30,    52,
   151,   123,   151,     4,   124,     0,   276,   291,   338,   343,
     0,     4,   123,   307,   124,   339,     0,     0,   340,     0,
   137,    11,   123,   171,   124,     0,   137,    71,   123,   171,
   124,     0,   276,   291,   128,     4,   123,   124,   216,     0,
   216,     0,   141,     0,   216,     0,   141,     0,     0,   276,
   291,    69,     4,   345,   346,   348,   280,     0,     0,   347,
     0,   137,   298,     0,   139,   349,   140,     0,     0,   350,
     0,   351,     0,   350,   351,     0,   303,     0,   304,     0,
   305,     0,   316,     0,   323,     0,   327,     0,   331,     0,
   337,     0,   290,     0,   139,   353,   140,     0,   139,   354,
    97,   140,     0,     0,   354,     0,   225,     0,   354,    97,
   225,     0,     0,   276,   291,    43,     4,   356,   357,   359,
   280,     0,     0,   358,     0,   137,   298,     0,   139,   360,
   140,     0,     0,   361,     0,   362,     0,   361,   362,     0,
   363,     0,   365,     0,   368,     0,   366,     0,   276,   364,
   151,     4,   123,   307,   124,   369,     0,   276,   364,    83,
     4,   123,   307,   124,   369,     0,     0,    49,     0,   276,
   364,   151,     4,   394,   139,   367,   140,   395,     0,   276,
   364,   151,    71,    98,   310,    99,   394,   139,   367,   140,
   395,     0,   276,    93,   369,     0,   276,    94,   369,     0,
   276,    93,   369,   276,    94,   369,     0,   276,    94,   369,
   276,    93,   369,     0,   276,   364,    29,   151,     4,   369,
     0,   141,     0,   139,   140,     0,     0,   276,   291,    28,
     4,   372,   371,   374,   280,     0,     0,   373,     0,   137,
   156,     0,   139,   375,   140,     0,   139,   376,    97,   140,
     0,     0,   376,     0,   377,     0,   376,    97,   377,     0,
   276,     4,     0,   276,     4,   138,   212,     0,   276,   291,
    24,   308,     4,   123,   307,   124,   141,     0,   380,     0,
   381,     0,   380,   381,     0,   390,    98,   382,   385,    99,
   391,     0,   390,    98,   382,   385,    97,    99,   391,     0,
     0,   383,     0,   384,   137,     0,    86,     0,    87,     0,
    29,     0,    88,     0,    89,     0,    90,     0,    91,     0,
    61,     0,    92,     0,   386,     0,   385,    97,   386,     0,
   388,   387,     0,     0,   389,     0,   145,     0,   123,   173,
   124,     0,     0,     0,     0,     0,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   121,   122,   123,   124,   125,   126,   129,   130,   140,   143,
   146,   147,   151,   154,   155,   158,   159,   163,   164,   167,
   168,   171,   172,   173,   176,   177,   180,   181,   182,   185,
   186,   187,   188,   189,   190,   191,   192,   193,   196,   197,
   200,   201,   204,   205,   208,   209,   210,   214,   215,   219,
   227,   231,   232,   235,   236,   237,   240,   241,   244,   245,
   246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
   258,   261,   262,   263,   266,   267,   272,   273,   276,   277,
   281,   282,   286,   287,   290,   293,   294,   297,   300,   303,
   306,   309,   311,   314,   315,   318,   319,   322,   325,   328,
   331,   334,   337,   338,   339,   340,   341,   344,   345,   346,
   347,   350,   353,   356,   357,   358,   359,   360,   361,   362,
   370,   371,   372,   376,   380,   384,   391,   392,   395,   396,
   399,   400,   404,   405,   406,   407,   410,   411,   412,   415,
   416,   420,   421,   422,   423,   424,   425,   426,   429,   430,
   431,   434,   435,   438,   439,   442,   443,   446,   447,   450,
   451,   454,   455,   457,   460,   461,   462,   463,   464,   465,
   466,   467,   468,   469,   470,   474,   475,   478,   481,   496,
   497,   498,   501,   502,   503,   504,   505,   506,   507,   508,
   509,   510,   511,   512,   513,   516,   519,   520,   524,   525,
   528,   531,   534,   535,   538,   541,   542,   545,   546,   549,
   550,   551,   554,   557,   560,   561,   564,   567,   570,   571,
   572,   573,   574,   575,   576,   579,   580,   583,   584,   587,
   590,   593,   594,   597,   598,   601,   605,   606,   609,   610,
   613,   614,   615,   616,   619,   622,   626,   630,   637,   638,
   641,   642,   645,   646,   649,   650,   653,   656,   659,   660,
   663,   671,   672,   673,   674,   675,   678,   681,   684,   685,
   686,   689,   692,   693,   696,   699,   702,   705,   711,   712,
   715,   718,   721,   724,   725,   728,   731,   734,   737,   742,
   746,   747,   751,   755,   756,   759,   768,   769,   772,   773,
   776,   777,   780,   781,   784,   784,   789,   790,   799,   800,
   803,   804,   808,   811,   812,   815,   816,   819,   822,   825,
   826,   829,   830,   833,   834,   835,   836,   837,   848,   849,
   852,   853,   856,   857,   858,   859,   860,   861,   862,   863,
   864,   865,   866,   867,   868,   869,   873,   881,   884,   885,
   888,   889,   890,   893,   894,   897,   900,   901,   904,   905,
   908,   909,   910,   911,   912,   913,   914,   915,   916,   918,
   921,   924,   927,   939,   945,   953,   954,   957,   958,   961,
   962,   965,   966,   969,   970,   973,   981,   982,   985,   986,
   987,   991,   998,  1004,  1005,  1006,  1009,  1010,  1013,  1014,
  1017,  1023,  1029,  1030,  1033,  1034,  1040,  1041,  1044,  1050,
  1056,  1060,  1064,  1066,  1069,  1073,  1076,  1077,  1080,  1081,
  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,  1093,
  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,  1103,
  1104,  1106,  1107,  1111,  1112,  1115,  1126,  1133,  1134,  1137,
  1138,  1154,  1164,  1165,  1168,  1169,  1174,  1179,  1182,  1183,
  1186,  1189,  1192,  1193,  1196,  1197,  1200,  1201,  1202,  1203,
  1204,  1205,  1206,  1207,  1209,  1214,  1215,  1218,  1219,  1222,
  1223,  1228,  1232,  1236,  1237,  1240,  1243,  1246,  1247,  1250,
  1251,  1254,  1255,  1256,  1257,  1261,  1271,  1283,  1284,  1287,
  1293,  1301,  1302,  1303,  1304,  1307,  1312,  1313,  1318,  1320,
  1325,  1326,  1329,  1332,  1333,  1336,  1337,  1340,  1341,  1344,
  1345,  1350,  1356,  1359,  1360,  1363,  1365,  1369,  1370,  1373,
  1376,  1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,  1387,
  1388,  1391,  1394,  1395,  1398,  1401,  1408,  1411,  1414,  1417,
  1420,  1423
};

static const char * const yytname[] = {   "$","error","$undefined.","RANK_SPECIFIER",
"IDENTIFIER","INTEGER_LITERAL","REAL_LITERAL","CHARACTER_LITERAL","STRING_LITERAL",
"ABSTRACT","AS","BASE","BOOL","BREAK","BYTE","CASE","CATCH","CHAR","CHECKED",
"CLASS","CONST","CONTINUE","DECIMAL","DEFAULT","DELEGATE","DO","DOUBLE","ELSE",
"ENUM","EVENT","EXPLICIT","EXTERN","FALSE","FINALLY","FIXED","FLOAT","FOR","FOREACH",
"GOTO","IF","IMPLICIT","IN","INT","INTERFACE","INTERNAL","IS","LOCK","LONG",
"NAMESPACE","NEW","NULL_LITERAL","OBJECT","OPERATOR","OUT","OVERRIDE","PARAMS",
"PRIVATE","PROTECTED","PUBLIC","READONLY","REF","RETURN","SBYTE","SEALED","SHORT",
"SIZEOF","STACKALLOC","STATIC","STRING","STRUCT","SWITCH","THIS","THROW","TRUE",
"TRY","TYPEOF","UINT","ULONG","UNCHECKED","UNSAFE","USHORT","USING","VIRTUAL",
"VOID","VOLATILE","WHILE","ASSEMBLY","FIELD","METHOD","MODULE","PARAM","PROPERTY",
"TYPE","GET","SET","ADD","REMOVE","COMMA","LEFT_BRACKET","RIGHT_BRACKET","GT",
"PLUSEQ","MINUSEQ","STAREQ","DIVEQ","MODEQ","XOREQ","ANDEQ","OREQ","LTLT","GTGTEQ",
"LTLTEQ","EQEQ","NOTEQ","LEQ","GEQ","ANDAND","OROR","PLUSPLUS","MINUSMINUS",
"ARROW","'<'","'*'","'('","')'","'.'","'&'","'!'","'~'","'+'","'-'","'/'","'%'",
"'>'","'^'","'|'","'?'","':'","'='","'{'","'}'","';'","literal","boolean_literal",
"namespace_name","type_name","opt_generic","genericlist","continuity","ENTER_generic",
"END_generic","type","non_array_type","simple_type","primitive_type","numeric_type",
"integral_type","floating_point_type","class_type","pointer_type","array_type",
"rank_specifiers_opt","rank_specifier","variable_reference","argument_list",
"argument","primary_expression","primary_expression_no_parenthesis","parenthesized_expression",
"member_access","invocation_expression","argument_list_opt","element_access",
"expression_list_opt","expression_list","this_access","base_access","post_increment_expression",
"post_decrement_expression","new_expression","object_creation_expression","array_creation_expression",
"array_initializer_opt","typeof_expression","checked_expression","unchecked_expression",
"pointer_member_access","addressof_expression","sizeof_expression","postfix_expression",
"unary_expression_not_plusminus","pre_increment_expression","pre_decrement_expression",
"unary_expression","cast_expression","type_quals_opt","type_quals","type_qual",
"multiplicative_expression","additive_expression","shift_expression","relational_expression",
"equality_expression","and_expression","exclusive_or_expression","inclusive_or_expression",
"conditional_and_expression","conditional_or_expression","conditional_expression",
"assignment","assignment_operator","expression","constant_expression","boolean_expression",
"statement","embedded_statement","block","statement_list_opt","statement_list",
"empty_statement","labeled_statement","declaration_statement","local_variable_declaration",
"variable_declarators","variable_declarator","variable_initializer","stackalloc_initializer",
"local_constant_declaration","constant_declarators","constant_declarator","expression_statement",
"statement_expression","selection_statement","if_statement","switch_statement",
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
"namespace_declaration","@1","comma_opt","qualified_identifier","qualifier",
"namespace_body","using_directives","using_directive","using_alias_directive",
"using_namespace_directive","namespace_member_declarations","namespace_member_declaration",
"type_declaration","modifiers_opt","modifiers","modifier","class_declaration",
"@2","class_base_opt","class_base","interface_type_list","class_body","class_member_declarations_opt",
"class_member_declarations","class_member_declaration","constant_declaration",
"field_declaration","method_declaration","method_header","formal_parameter_list_opt",
"return_type","method_body","formal_parameter_list","formal_parameter","fixed_parameter",
"fixed_parameter_opt_default","parameter_modifier_opt","parameter_array","property_declaration",
"accessor_declarations","set_accessor_declaration_opt","get_accessor_declaration_opt",
"get_accessor_declaration","set_accessor_declaration","accessor_body","event_declaration",
"event_accessor_declarations","add_accessor_declaration","remove_accessor_declaration",
"indexer_declaration","@3","indexer_declarator","qualified_this","operator_declaration",
"operator_declarator","overloadable_operator_declarator","overloadable_operator",
"optGT","conversion_operator_declarator","constructor_declaration","constructor_declarator",
"constructor_initializer_opt","constructor_initializer","destructor_declaration",
"operator_body","constructor_body","struct_declaration","@4","struct_interfaces_opt",
"struct_interfaces","struct_body","struct_member_declarations_opt","struct_member_declarations",
"struct_member_declaration","array_initializer","variable_initializer_list_opt",
"variable_initializer_list","interface_declaration","@5","interface_base_opt",
"interface_base","interface_body","interface_member_declarations_opt","interface_member_declarations",
"interface_member_declaration","interface_method_declaration","new_opt","interface_property_declaration",
"interface_indexer_declaration","interface_accessors","interface_event_declaration",
"interface_empty_body","enum_declaration","@6","enum_base_opt","enum_base","enum_body",
"enum_member_declarations_opt","enum_member_declarations","enum_member_declaration",
"delegate_declaration","attributes","attribute_sections","attribute_section",
"attribute_target_specifier_opt","attribute_target_specifier","attribute_target",
"attribute_list","attribute","attribute_arguments_opt","attribute_name","attribute_arguments",
"ENTER_attrib","EXIT_attrib","ENTER_accessor_decl","EXIT_accessor_decl","ENTER_getset",
"EXIT_getset",""
};
#endif

static const short yyr1[] = {     0,
   142,   142,   142,   142,   142,   142,   143,   143,   144,   145,
   146,   146,   147,   148,   148,   149,   150,   151,   151,   152,
   152,   153,   153,   153,   154,   154,   155,   155,   155,   156,
   156,   156,   156,   156,   156,   156,   156,   156,   157,   157,
   158,   158,   159,   159,   160,   160,   160,   161,   161,   162,
   163,   164,   164,   165,   165,   165,   166,   166,   167,   167,
   167,   167,   167,   167,   167,   167,   167,   167,   167,   167,
   168,   169,   169,   169,   170,   170,   171,   171,   172,   172,
   173,   173,   174,   174,   175,   176,   176,   177,   178,   179,
   180,   181,   181,   182,   182,   183,   183,   184,   185,   186,
   187,   188,   189,   189,   189,   189,   189,   190,   190,   190,
   190,   191,   192,   193,   193,   193,   193,   193,   193,   193,
   194,   194,   194,   194,   194,   194,   195,   195,   196,   196,
   197,   197,   198,   198,   198,   198,   199,   199,   199,   200,
   200,   201,   201,   201,   201,   201,   201,   201,   202,   202,
   202,   203,   203,   204,   204,   205,   205,   206,   206,   207,
   207,   208,   208,   209,   210,   210,   210,   210,   210,   210,
   210,   210,   210,   210,   210,   211,   211,   212,   213,   214,
   214,   214,   215,   215,   215,   215,   215,   215,   215,   215,
   215,   215,   215,   215,   215,   216,   217,   217,   218,   218,
   219,   220,   221,   221,   222,   223,   223,   224,   224,   225,
   225,   225,   226,   227,   228,   228,   229,   230,   231,   231,
   231,   231,   231,   231,   231,   232,   232,   233,   233,   234,
   235,   236,   236,   237,   237,   238,   239,   239,   240,   240,
   241,   241,   241,   241,   242,   243,   244,   245,   246,   246,
   247,   247,   248,   248,   249,   249,   250,   251,   252,   252,
   253,   254,   254,   254,   254,   254,   255,   256,   257,   257,
   257,   258,   259,   259,   260,   261,   261,   261,   262,   262,
   263,   263,   263,   264,   264,   265,   266,   267,   268,   269,
   270,   270,   271,   272,   272,   273,   274,   274,   275,   275,
   276,   276,   277,   277,   279,   278,   280,   280,   281,   281,
   282,   282,   283,   284,   284,   285,   285,   286,   287,   288,
   288,   289,   289,   290,   290,   290,   290,   290,   291,   291,
   292,   292,   293,   293,   293,   293,   293,   293,   293,   293,
   293,   293,   293,   293,   293,   293,   295,   294,   296,   296,
   297,   297,   297,   298,   298,   299,   300,   300,   301,   301,
   302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
   303,   304,   305,   306,   306,   307,   307,   308,   308,   309,
   309,   310,   310,   311,   311,   312,   313,   313,   314,   314,
   314,   315,   316,   317,   317,   317,   318,   318,   319,   319,
   320,   321,   322,   322,   323,   323,   324,   324,   325,   326,
   328,   327,   329,   329,   330,   331,   332,   332,   333,   333,
   334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
   334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
   334,   335,   335,   336,   336,   337,   338,   339,   339,   340,
   340,   341,   342,   342,   343,   343,   345,   344,   346,   346,
   347,   348,   349,   349,   350,   350,   351,   351,   351,   351,
   351,   351,   351,   351,   351,   352,   352,   353,   353,   354,
   354,   356,   355,   357,   357,   358,   359,   360,   360,   361,
   361,   362,   362,   362,   362,   363,   363,   364,   364,   365,
   366,   367,   367,   367,   367,   368,   369,   369,   371,   370,
   372,   372,   373,   374,   374,   375,   375,   376,   376,   377,
   377,   378,   379,   380,   380,   381,   381,   382,   382,   383,
   384,   384,   384,   384,   384,   384,   384,   384,   384,   385,
   385,   386,   387,   387,   388,   389,   390,   391,   392,   393,
   394,   395
};

static const short yyr2[] = {     0,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
     0,     2,     3,     2,     3,     0,     0,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     2,     2,     2,     2,     2,     0,     2,     1,
     1,     1,     3,     1,     2,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     3,     3,     3,     3,     4,     4,     0,     1,     4,     4,
     0,     1,     1,     3,     1,     3,     4,     2,     2,     1,
     5,     7,     3,     0,     1,     4,     4,     4,     4,     3,
     2,     4,     1,     1,     1,     1,     1,     1,     2,     2,
     1,     2,     2,     1,     2,     2,     2,     1,     1,     1,
     4,     5,     6,     5,     5,     5,     0,     1,     1,     2,
     1,     1,     1,     3,     3,     3,     1,     3,     3,     1,
     3,     1,     3,     3,     3,     3,     3,     3,     1,     3,
     3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
     3,     1,     5,     3,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     3,     0,     1,     1,     2,
     1,     3,     2,     2,     2,     1,     3,     1,     3,     1,
     1,     1,     5,     3,     1,     3,     3,     2,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     5,     7,     5,
     3,     0,     1,     1,     2,     2,     1,     2,     3,     2,
     1,     1,     1,     1,     2,     5,     7,     9,     0,     1,
     0,     1,     0,     1,     1,     1,     1,     1,     1,     3,
     8,     1,     1,     1,     1,     1,     2,     2,     3,     4,
     3,     3,     0,     1,     3,     3,     3,     4,     1,     2,
     6,     6,     2,     0,     1,     2,     2,     2,     5,     5,
     1,     1,     6,     1,     3,     3,     2,     2,     0,     1,
     0,     1,     0,     1,     0,     6,     0,     1,     1,     2,
     2,     3,     4,     1,     2,     1,     1,     5,     3,     1,
     2,     1,     1,     1,     1,     1,     1,     1,     0,     1,
     1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     0,     8,     0,     1,
     2,     2,     4,     1,     3,     3,     0,     1,     1,     2,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     6,     5,     2,     7,     7,     0,     1,     1,     1,     1,
     1,     1,     3,     1,     1,     5,     0,     2,     0,     1,
     1,     4,     9,     2,     2,     0,     0,     1,     0,     1,
     5,     5,     1,     1,     6,    10,     2,     2,     5,     5,
     0,     9,     5,     5,     2,     4,     1,     1,     7,    10,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
     1,     1,     0,     7,     7,     4,     5,     0,     1,     5,
     5,     7,     1,     1,     1,     1,     0,     8,     0,     1,
     2,     3,     0,     1,     1,     2,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     3,     4,     0,     1,     1,
     3,     0,     8,     0,     1,     2,     3,     0,     1,     1,
     2,     1,     1,     1,     1,     8,     8,     0,     1,     9,
    12,     3,     3,     6,     6,     6,     1,     2,     0,     8,
     0,     1,     2,     3,     4,     0,     1,     1,     3,     2,
     4,     9,     1,     1,     2,     6,     7,     0,     1,     2,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     3,     2,     0,     1,     1,     3,     0,     0,     0,     0,
     0,     0
};

static const short yydefact[] = {   299,
     0,   301,   300,   314,   316,   317,   309,     0,     9,     0,
   329,   322,   301,   320,   323,   324,   325,   326,   327,   328,
   302,   523,   524,     0,   315,   311,     0,   319,   310,   333,
   334,   335,     0,   336,   337,   338,   339,   340,   341,   342,
   343,   344,   345,   346,     0,   330,   331,   329,   321,   525,
   528,   309,     0,   312,   305,     0,     0,     0,     0,     0,
   332,   533,   538,   531,   532,   534,   535,   536,   537,   539,
     0,   529,     0,   318,     0,   347,    26,    31,    38,    29,
    40,    39,    34,    36,    41,    30,    32,    42,    35,    37,
    33,   379,    21,   378,    18,    20,    22,    25,    27,    28,
    23,    24,    19,    11,     0,   511,   482,   457,   545,    11,
     0,   540,   543,   530,   299,   307,   349,    44,    43,    50,
    46,    45,     0,    10,    47,     0,     0,   509,   512,   484,
   459,     0,   548,    81,   542,   544,   301,   308,   306,     0,
     0,   350,     0,    12,    16,   301,   513,     0,     0,     0,
   485,     0,     0,   460,   548,   541,   526,     2,     3,     4,
     5,     0,     0,     8,     0,     6,     0,    85,     7,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    59,     1,     0,     0,   103,    58,    57,    61,    62,    63,
     0,    82,    64,    65,   105,   106,    66,    90,    60,    67,
    69,    70,   107,   120,    68,   108,   114,   118,   119,   133,
   111,   137,   140,   142,   149,   152,   154,   156,   158,   160,
   162,   176,   177,    83,   104,     0,   301,   354,   351,   352,
   301,   307,     0,   389,     0,   377,   382,   384,   385,   301,
   307,   486,   301,   307,   461,   301,   307,   527,     0,     0,
     0,     0,    18,    19,     0,     0,     0,   112,   113,   117,
   127,   127,   127,   137,     0,   104,   101,   109,   110,   115,
   116,     0,     0,     0,     0,    77,   546,     0,    88,    89,
     0,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   165,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    77,   313,     0,     0,   329,   370,
     0,   301,   359,   361,   362,   363,     0,   364,   365,   366,
   367,   368,   369,   348,    17,    17,    13,   391,     0,   390,
     0,     0,   301,     0,     0,   517,   518,   510,   498,     0,
   301,   490,   492,   493,   495,   494,   483,   329,   475,   467,
   468,   469,   470,   471,   472,   473,   474,     0,   301,   465,
   458,     0,    86,     0,    77,     0,   478,    93,     0,     0,
     0,     0,   132,   131,     0,   128,   129,     0,     0,     0,
    71,   127,    73,    74,     0,    72,     0,     0,    78,    52,
     0,    54,    84,   100,   164,   134,   135,   136,   133,   138,
   139,   141,   148,   147,   145,   146,   143,   144,   150,   151,
   153,   155,   157,   159,   161,     0,     0,     0,   353,   355,
     0,   356,   360,   197,   381,   380,   373,     0,    14,     0,
     0,   522,   383,   520,   514,   301,   499,     0,   487,   491,
     0,   462,   466,    87,    98,     0,     0,     0,   210,   480,
   212,   211,     0,   479,   102,    97,    96,    99,     0,   130,
     0,     0,     0,   121,     0,    79,    56,    51,    55,     0,
    75,     0,    80,    76,   309,     0,     0,     0,     0,     0,
     0,     0,   411,     0,   417,   418,     0,   309,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   273,
     0,   273,     0,     0,     0,     0,     0,   201,     0,    22,
    23,    62,   105,   106,    90,   118,   119,     0,   221,   199,
   182,   183,     0,   198,   184,   180,   181,     0,     0,   185,
     0,   186,   226,   227,   187,   194,   241,   242,   243,   244,
   188,   262,   263,   264,   265,   266,   189,   190,   191,   192,
   193,   195,   104,    15,   392,   387,     0,   515,   519,     0,
     0,     0,    91,    48,     0,   476,     0,   126,   124,   125,
   122,     0,    53,   163,   301,     0,     0,     0,     0,     0,
     0,   208,     0,     0,     0,   206,   551,     0,     0,   551,
   454,   453,   416,   456,   455,   446,     0,   267,   287,     0,
   268,     0,     0,   249,     0,     0,     0,     0,     0,     0,
   274,     0,     0,     0,     0,   288,   245,     0,     0,   208,
   205,   196,   200,   203,   204,   218,     0,   386,   178,   521,
     0,     0,   551,     0,    94,    48,     0,   477,   481,   123,
     0,     0,     0,   215,     0,   549,     0,     0,   301,     0,
     0,   428,   427,   435,   436,   437,   441,   440,   425,   426,
   439,   429,   432,   423,   424,   421,   422,   430,   431,   443,
   434,   433,     0,   301,     0,   372,   301,     0,   415,   301,
     0,   202,   214,     0,     0,   255,   259,     0,   250,   256,
     0,   269,     0,   271,   179,     0,     0,   272,     0,   275,
     0,     0,   276,   279,   277,   292,   291,     0,     0,   388,
     0,   301,   301,     0,   301,    92,    95,    49,     0,   448,
     0,     0,   371,   405,     0,     0,     0,     0,     0,   209,
   442,   438,     0,     0,   207,     0,   301,     0,   301,     0,
     0,     0,   294,   251,     0,     0,   270,     0,     0,     0,
     0,   283,   286,   280,   278,     0,     0,     0,   507,   506,
     0,     0,   301,     0,   213,     0,   447,   449,   217,   216,
   301,     0,     0,   375,   452,     0,   413,   374,     0,     0,
   301,   301,   414,     0,     0,     0,     0,     0,   257,     0,
   252,   260,     0,   228,   289,   232,   230,   284,   284,   290,
   246,   508,     0,     0,     0,     0,   551,     0,     0,     0,
     0,   301,   301,     0,     0,     0,   552,   552,   552,     0,
   394,   398,     0,   395,   400,   552,     0,   296,   295,   293,
   253,     0,     0,     0,     0,     0,   233,   234,     0,   237,
   285,     0,     0,   497,   496,     0,     0,   552,     0,    77,
    77,   550,   550,   550,     0,   407,     0,   408,   445,   444,
     0,   419,     0,     0,   393,   412,   247,     0,   254,   258,
     0,   229,     0,   240,   231,   235,   236,   238,     0,     0,
   301,   301,   500,   301,     0,     0,     0,     0,   406,     0,
   404,   403,   551,   551,     0,   261,   239,   282,   281,     0,
     0,     0,   450,   451,   549,   549,     0,   401,   402,   248,
     0,     0,   552,   409,   410,   420,   504,   505,   501,     0,
     0,     0
};

static const short yydefgoto[] = {   181,
   182,     8,    93,   124,   144,   337,   233,   438,   519,    95,
    96,   183,    98,    99,   100,   184,   102,   103,   645,   384,
   477,   399,   400,   185,   186,   187,   188,   189,   401,   190,
   191,   192,   193,   194,   195,   196,   197,   198,   199,   726,
   200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
   210,   211,   385,   386,   387,   212,   213,   214,   215,   216,
   217,   218,   219,   220,   221,   222,   223,   293,   402,   640,
   706,   530,   531,   532,   533,   534,   535,   536,   537,   538,
   595,   596,   460,   461,   539,   653,   654,   540,   541,   542,
   543,   544,   807,   846,   847,   848,   849,   850,   545,   546,
   547,   548,   549,   698,   800,   878,   699,   801,   879,   700,
   550,   551,   552,   553,   554,   555,   622,   556,   557,   713,
   714,   852,   715,   558,   559,   560,   561,   718,   562,   752,
   753,   930,     2,   234,   226,    12,    75,   139,   225,    10,
   116,     3,     4,     5,     6,    13,    14,    15,    45,    46,
    47,    16,   117,   141,   142,   230,   232,   321,   322,   323,
   324,   325,   326,   327,   235,   105,   437,   236,   237,   238,
   638,   341,   239,   328,   790,   831,   834,   791,   792,   903,
   329,   821,   822,   823,   330,   600,   493,   599,   331,   494,
   495,   683,   742,   496,   332,   497,   777,   778,   333,   603,
   606,    17,   131,   153,   154,   247,   368,   369,   370,   462,
   463,   464,    18,   130,   150,   151,   244,   350,   351,   352,
   353,   448,   354,   355,   816,   356,   770,    19,   148,   128,
   129,   241,   345,   346,   347,    20,    21,    22,    23,    71,
    72,    73,   111,   112,   135,   113,   136,    24,   157,   735,
   897,   688,   873
};

static const short yypact[] = {   -30,
    83,    20,   -30,-32768,-32768,-32768,   205,    -4,-32768,   203,
  2508,-32768,    28,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    20,-32768,   113,-32768,-32768,   253,-32768,   171,-32768,
-32768,-32768,   253,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   200,  1247,-32768,  2702,-32768,-32768,
   407,   204,   101,-32768,-32768,   286,   343,   340,   369,   391,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
   253,-32768,   264,-32768,   259,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   287,-32768,   293,-32768,   426,-32768,-32768,-32768,-32768,
-32768,-32768,   426,    65,   442,   295,-32768,-32768,-32768,   297,
   328,-32768,   337,-32768,   -30,   339,   351,-32768,-32768,-32768,
-32768,-32768,  1695,-32768,-32768,   368,   274,-32768,-32768,   370,
   383,    34,-32768,  2308,-32768,-32768,   -33,-32768,-32768,   185,
   388,-32768,   287,-32768,   293,   221,-32768,   396,   253,   403,
-32768,   253,   419,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    18,   410,-32768,  1695,-32768,   437,-32768,-32768,   438,
   439,  2308,  2308,  2308,  2031,  2308,  2308,  2308,  2308,  2308,
-32768,-32768,   440,   443,   210,   441,-32768,-32768,-32768,-32768,
   445,   466,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   261,-32768,-32768,-32768,   611,
-32768,   244,   117,   462,    15,   279,   446,   444,   447,   460,
   -81,-32768,-32768,-32768,   104,   450,   -29,-32768,   480,   487,
    47,   339,   -47,    67,   461,   489,-32768,-32768,-32768,    80,
   339,   487,   119,   339,   487,   125,   339,-32768,  2308,   587,
  2308,   211,   494,    19,  1695,  2662,  2308,-32768,-32768,-32768,
    51,    59,    60,   281,   471,    21,-32768,-32768,-32768,-32768,
-32768,   592,   593,  2308,   594,  1942,-32768,  2308,-32768,-32768,
   595,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,  2308,  2308,  2308,  2308,  2308,  2308,  2308,  1695,
  1695,  2308,  2308,  2308,  2308,  2308,  2308,  2308,  2308,  2308,
  2308,  2308,  2308,  2308,  1942,-32768,   253,   253,  1247,-32768,
   463,   137,-32768,-32768,-32768,-32768,   289,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  1695,-32768,
  1695,   464,    20,   598,   468,   507,-32768,-32768,   557,   469,
   142,-32768,-32768,-32768,-32768,-32768,-32768,  1247,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   470,   153,-32768,
-32768,   336,-32768,   492,  1942,  2308,  1843,-32768,   315,   323,
   341,   493,-32768,-32768,   497,    51,-32768,   498,   499,  2120,
  2397,    51,-32768,-32768,   373,-32768,  2308,  2308,   527,-32768,
   501,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   244,
   244,   117,   293,   293,   462,   462,   462,   462,    15,    15,
   279,   446,   444,   447,   460,   490,   378,   502,   487,-32768,
  2467,-32768,-32768,  1468,-32768,-32768,-32768,  1695,-32768,    72,
    73,-32768,-32768,   491,-32768,   154,-32768,  2618,-32768,-32768,
  2574,-32768,-32768,-32768,-32768,   509,   379,  1695,-32768,-32768,
-32768,-32768,   495,   537,-32768,-32768,-32768,-32768,  2308,-32768,
  2308,  2308,  2308,-32768,   516,-32768,-32768,-32768,-32768,  1942,
-32768,  2308,-32768,-32768,   360,  1695,  1695,   589,   590,    75,
   639,    57,-32768,   325,-32768,-32768,   363,   246,   504,   217,
  1695,   506,  1606,   525,   526,   530,   359,   531,   532,  2308,
   533,  2308,   511,   238,   511,   534,   535,-32768,    78,   440,
   443,   151,   157,   165,   173,   186,   187,   611,-32768,-32768,
-32768,-32768,   520,  1468,-32768,-32768,-32768,   539,   540,-32768,
   541,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,    82,-32768,-32768,   529,  2308,-32768,-32768,  1695,
    79,    71,-32768,   426,   163,-32768,  1744,-32768,-32768,-32768,
-32768,  2308,-32768,-32768,   221,    86,    87,  1695,  1695,   545,
   561,   283,   950,   588,   -39,-32768,   564,    44,   591,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,  1468,-32768,-32768,    86,
-32768,   603,  1695,  2219,  1695,   549,  2308,   550,  2308,  2308,
-32768,   551,  2308,   553,   326,-32768,-32768,  2219,  2308,   558,
   600,-32768,-32768,-32768,-32768,-32768,   226,-32768,-32768,-32768,
    88,   572,   575,   601,   562,   426,  2308,-32768,-32768,-32768,
   576,   567,   -31,-32768,   -27,-32768,   327,   333,   221,   582,
  1843,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   607,
-32768,-32768,   585,    20,   706,-32768,   221,   581,-32768,    20,
   584,-32768,   627,   602,    90,-32768,-32768,   597,-32768,   629,
    91,-32768,   599,-32768,-32768,   604,   605,-32768,   606,-32768,
   245,   511,   326,-32768,-32768,-32768,-32768,   608,   610,-32768,
   364,   221,   221,   609,    20,-32768,-32768,-32768,   632,   613,
  2308,   735,-32768,-32768,   612,  1695,  1695,   618,   511,-32768,
-32768,-32768,  1695,   409,-32768,   620,   162,   414,   162,  2308,
   614,   228,-32768,  2308,  2308,   705,-32768,  1606,  1606,   616,
   185,-32768,-32768,-32768,-32768,  1606,  1606,   624,-32768,-32768,
   641,   645,    20,   415,-32768,    30,-32768,-32768,-32768,-32768,
    20,    92,    93,-32768,-32768,    94,-32768,-32768,   422,   630,
   175,   182,-32768,   633,   648,  2308,   749,  1606,-32768,   634,
-32768,-32768,  2308,   751,-32768,   102,-32768,   772,   772,-32768,
-32768,-32768,   364,   364,   429,   642,-32768,   658,   663,   430,
   647,    20,    20,   664,   669,   229,-32768,-32768,-32768,   700,
-32768,-32768,   702,-32768,-32768,-32768,   655,-32768,-32768,-32768,
  2308,   675,  1606,  2308,   665,   660,   102,-32768,  1330,-32768,
-32768,   679,   680,-32768,-32768,   364,   364,-32768,   666,  1942,
  1942,-32768,-32768,-32768,   710,-32768,   712,-32768,-32768,-32768,
  1695,-32768,   380,   380,-32768,-32768,-32768,   684,-32768,   629,
  1606,-32768,   672,-32768,-32768,-32768,  1468,-32768,   511,   511,
   197,   206,-32768,    20,   686,   687,   511,   511,-32768,    96,
-32768,-32768,-32768,-32768,  1606,-32768,-32768,-32768,-32768,   718,
   720,   674,-32768,-32768,-32768,-32768,   692,-32768,-32768,-32768,
   364,   364,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   817,
   818,-32768
};

static const short yypgoto[] = {   188,
-32768,-32768,   -68,-32768,   381,-32768,-32768,   486,    31,   659,
-32768,    23,-32768,   699,-32768,   -34,-32768,   662,   183,   -90,
   432,-32768,   352,-32768,-32768,-32768,-32768,    25,  -308,-32768,
-32768,  -215,-32768,-32768,    97,   149,-32768,   251,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,   452,   394,   408,
   367,-32768,  -242,-32768,   448,  -138,   536,   138,   223,   523,
   524,   538,   543,   547,-32768,-32768,   428,-32768,   484,  -607,
  -603,  -529,  -495,  -323,-32768,    -8,-32768,-32768,-32768,  -572,
  -484,   159,  -548,-32768,-32768,   235,   114,-32768,  -602,-32768,
-32768,-32768,-32768,-32768,-32768,     4,-32768,     1,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,     6,
-32768,-32768,-32768,-32768,-32768,-32768,   345,-32768,-32768,-32768,
   156,    58,   160,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    81,-32768,   760,    -2,-32768,-32768,-32768,   155,     0,   384,
-32768,-32768,   874,-32768,-32768,   742,     3,  -214,  -113,-32768,
   834,-32768,-32768,-32768,-32768,  -134,-32768,-32768,-32768,   563,
  -207,  -206,  -203,-32768,  -566,-32768,-32768,  -416,   548,-32768,
-32768,-32768,-32768,  -202,   134,-32768,-32768,   106,    95,    10,
  -201,-32768,    70,    66,  -200,-32768,-32768,-32768,  -199,-32768,
-32768,-32768,-32768,-32768,  -197,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   544,  -252,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   552,
-32768,-32768,-32768,-32768,     2,-32768,  -783,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   453,-32768,-32768,-32768,   878,-32768,
-32768,-32768,-32768,   773,-32768,-32768,-32768,-32768,   754,  -378,
  -315,  -591,  -724
};


#define	YYLAST		2786


static const short yytable[] = {    11,
     9,   378,   109,   436,   633,   121,   428,   612,   691,   703,
    48,   697,   122,   125,   242,    49,   320,   245,   651,   388,
   389,   120,   101,   120,   300,   719,    53,  -298,   649,   854,
   855,   359,    55,   372,   631,   312,   264,    52,   360,   361,
   818,   696,   362,   363,   364,   365,   366,    29,   367,   335,
     1,   724,   336,   120,   313,   717,   104,   685,   395,   301,
   592,   120,   120,   109,  -547,   732,   456,   120,  -547,   685,
   110,   228,   891,   892,   643,   565,   566,   692,    52,    97,
   228,   630,   642,   228,   120,   -11,     7,    94,   101,   652,
   592,   721,   738,   751,   756,   824,   825,   826,   427,   917,
   819,   686,   655,   874,   875,   229,  -303,   320,   593,   733,
  -304,   876,   740,   734,   689,   249,   844,  -547,   314,   338,
   746,   339,   104,   779,   845,  -547,   340,   594,   302,   303,
   101,   110,   155,   893,    48,   304,    28,   927,   928,   110,
   263,   644,   250,   315,  -547,    97,   795,   305,   110,   475,
   799,   110,   802,   145,   359,   771,   772,   377,   410,   411,
   457,   360,   361,   122,   104,   362,   363,   364,   365,   366,
   602,   367,   383,   605,   266,   392,   609,  -547,   119,   314,
   383,   383,   429,   272,   273,   123,  -357,    97,    52,   625,
   626,   627,   119,   119,   119,   252,   118,   262,   929,   119,
   118,   314,   123,   -11,   315,   431,    29,   119,   119,   119,
    51,   119,   119,   119,   119,   119,  -547,   119,    56,  -516,
   101,   101,  -547,    57,    48,   859,   315,    58,   319,    49,
   158,   159,   160,   161,  -547,    85,   883,   344,   697,  -547,
   349,    74,    59,   358,   451,   297,   298,  -219,   228,   430,
  -547,  -547,    88,  -222,   104,   104,    52,   164,  -488,  -547,
   647,  -223,   804,   805,  -463,   101,   101,   744,    60,  -220,
   810,   811,  -547,   748,  -219,   166,  -358,    97,    97,  -547,
  -222,  -489,  -224,  -225,   119,   379,   381,    78,  -223,    76,
    79,  -219,  -464,   568,  -547,    54,  -220,  -222,   169,   104,
   104,  -396,   840,  -547,   101,  -223,   101,   274,   774,  -224,
  -225,   918,   919,  -220,  -397,    83,   110,   110,  -547,   319,
    84,  -399,    97,    97,   797,   871,  -224,  -225,    26,    26,
   413,   414,   119,   375,   275,    86,  -502,    87,   104,   251,
   104,   711,    27,   106,  -376,  -503,    52,   882,   349,    89,
    90,   798,   872,    91,    77,   434,    78,   633,   712,    79,
   257,    97,   616,    97,    80,   294,   358,   761,    81,   440,
    26,   441,   107,   617,   295,   296,   434,    82,   279,   280,
   281,   618,   607,   434,    83,   906,   334,   762,   763,    84,
   306,   307,   727,    85,   108,   348,   101,   115,   357,   521,
   114,   371,   390,   101,    86,  -309,    87,    26,   118,   920,
    88,   295,   296,   101,   119,   785,   101,   123,    89,    90,
   661,  -309,    91,   101,   132,    92,   133,   434,   120,   435,
   104,   127,   278,   563,   454,    62,   119,   104,   465,   415,
   416,   417,   418,   344,   118,   126,   466,   104,   119,   736,
   104,   101,   101,    97,   119,   737,   520,   104,   522,   134,
    97,   492,   119,   434,   467,   601,   101,    63,   145,   278,
    97,   476,   125,    97,   278,   278,   483,   574,   572,   138,
    97,   492,   585,   646,    26,   104,   104,   140,   575,   590,
   146,   597,    64,    65,    66,    67,    68,    69,    70,   521,
   104,   434,   768,   604,   769,   343,   149,   787,    97,    97,
   343,   343,   793,   817,   827,   828,   586,   587,   434,   152,
   901,   856,   857,    97,   862,   863,   231,   522,   419,   420,
   523,   610,   251,   563,   240,   101,   924,   925,   258,   259,
   260,   243,   267,   268,   269,   270,   271,   898,   899,   902,
   902,   895,   896,   101,   101,   646,   520,   246,   522,   255,
   256,   257,   278,   276,   272,   908,   909,   273,   277,   104,
   299,   308,   521,   915,   916,   311,   317,   309,   101,   521,
   101,   310,   524,   318,   342,   343,   656,   104,   104,   316,
   373,   376,    97,   521,   391,   393,   394,   396,   404,   523,
   641,   444,   432,   446,   442,   447,   563,   445,   449,   452,
    97,    97,   104,   563,   104,   455,   468,   224,   657,   658,
   469,   471,   472,   480,   481,   484,   482,   563,   567,   520,
   523,   522,   573,   577,   576,    97,   520,    97,   522,   582,
   588,   589,   591,   695,   608,   701,   611,   613,   614,   434,
   520,   524,   615,   619,   620,   623,   628,   629,   265,   632,
   406,   407,   408,   409,   409,   409,   637,   659,   409,   409,
   409,   409,   409,   409,   409,   409,   409,   409,   409,   634,
   635,   636,   524,   660,   525,   684,   687,   694,   690,   702,
   704,   708,   808,   710,   722,   661,   685,   723,   725,   730,
   377,   101,   101,   523,   731,   739,   741,   743,   101,   630,
   523,   282,   283,   284,   285,   286,   287,   288,   289,   747,
   290,   291,   749,   732,   750,   755,   809,   758,   759,   760,
   775,   766,   224,   767,   374,   104,   104,   754,   652,   757,
   382,   784,   104,   788,   789,   803,   789,   773,   292,   776,
   781,   796,   751,   525,   806,   524,   406,   224,    97,    97,
   110,   403,   524,   812,   813,    97,   782,   783,   814,   829,
   815,   837,   836,   786,   841,   851,   405,   843,   820,   522,
   860,   858,   522,   522,   525,   861,   864,   869,   830,   833,
   522,   522,   870,   828,   827,   877,   426,   224,   881,   885,
   528,   884,   889,   890,   894,   863,   862,   905,   907,   913,
   914,   921,   922,   923,   521,   926,   931,   932,   564,   865,
   867,   439,   522,   253,   720,   147,   254,   526,   728,   479,
   421,   583,   422,   470,   412,   578,   101,   579,   580,   581,
   887,   527,   474,   745,   693,   780,   880,   423,   563,   888,
   886,   523,   521,   424,   523,   523,   624,   525,   425,   224,
   459,   529,   523,   523,   525,   522,   853,   522,   764,   528,
   104,   520,   765,   522,   137,   598,    25,   839,   227,    61,
   478,   478,   794,   904,   433,   832,   563,   866,   910,   911,
   443,   815,   868,    97,   523,   912,   526,   835,   569,    50,
   528,   900,   450,   524,   156,   522,   524,   524,   248,   520,
   527,   522,   453,     0,   524,   524,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   526,     0,   522,
   529,     0,     0,     0,     0,     0,     0,   523,     0,   523,
     0,   527,     0,     0,     0,   523,   524,     0,   650,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   529,     0,     0,     0,   584,     0,     0,     0,     0,
     0,     0,     0,   528,     0,     0,     0,   523,     0,     0,
   528,   662,     0,   523,     0,     0,     0,     0,     0,   524,
     0,   524,     0,   621,     0,   621,     0,   524,     0,     0,
   526,   523,     0,     0,     0,   525,     0,   526,   525,   525,
     0,     0,     0,     0,   527,     0,   525,   525,     0,     0,
     0,   527,   663,     0,     0,     0,     0,     0,     0,   524,
     0,     0,     0,     0,   529,   524,     0,     0,     0,     0,
     0,   529,     0,     0,     0,     0,     0,     0,   525,     0,
   639,     0,     0,   524,     0,     0,     0,     0,   664,     0,
   459,   665,   666,   667,   668,     0,     0,   669,   670,     0,
   671,   672,     0,     0,     0,   673,   674,   675,   676,   677,
   678,   679,   680,   681,   682,     0,     0,     0,     0,     0,
     0,   525,     0,   525,     0,     0,     0,     0,     0,   525,
   639,     0,   705,   707,     0,     0,   709,     0,     0,     0,
     0,   716,   705,     0,     0,     0,     0,     0,     0,     0,
     0,   528,     0,     0,   528,   528,     0,     0,     0,     0,
   729,   525,   528,   528,     0,     0,     0,   525,     0,     0,
     0,     0,     0,     0,   459,     0,     0,     0,   526,     0,
     0,   526,   526,     0,     0,   525,     0,     0,     0,   526,
   526,     0,   527,     0,   528,   527,   527,     0,     0,     0,
     0,     0,     0,   527,   527,     0,     0,     0,     0,     0,
     0,     0,   529,     0,     0,   529,   529,     0,     0,     0,
     0,   526,     0,   529,   529,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   527,     0,   528,     0,   528,
     0,     0,     0,     0,   639,   528,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   529,     0,     0,     0,     0,
     0,     0,     0,   705,   526,     0,   526,   705,     0,     0,
     0,     0,   526,     0,     0,     0,     0,   528,   527,     0,
   527,     0,     0,   528,     0,    30,   527,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   529,     0,
   529,   528,     0,     0,   526,     0,   529,    31,     0,   838,
   526,     0,     0,     0,     0,     0,   842,     0,   527,     0,
    32,     0,     0,     0,   527,    34,     0,     0,   526,     0,
    35,     0,    36,    37,    38,    39,     0,     0,   529,    40,
     0,     0,   527,    41,   529,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    42,     0,   639,    43,     0,
    44,     0,   529,   498,   158,   159,   160,   161,     0,     0,
   162,    77,   499,    78,   844,     0,    79,   500,     0,   501,
   502,    80,   845,     0,   503,    81,     0,     0,     0,     0,
     0,   164,     0,   504,    82,   505,   506,   507,   508,     0,
     0,    83,     0,     0,     0,   509,    84,     0,   165,   166,
    85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   510,    86,     0,    87,   167,     0,     0,    88,     0,   511,
   168,   512,   169,   513,   170,    89,    90,   514,   515,    91,
   516,     0,   143,     0,   517,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,   172,   173,     0,
     0,   174,   175,     0,     0,   176,   177,   178,   179,   180,
     0,     0,     0,     0,     0,     0,     0,     0,   434,     0,
   518,   498,   158,   159,   160,   161,     0,     0,   162,    77,
   499,    78,     0,     0,    79,   500,     0,   501,   502,    80,
     0,     0,   503,    81,     0,     0,     0,     0,     0,   164,
     0,   504,    82,   505,   506,   507,   508,     0,     0,    83,
     0,     0,     0,   509,    84,     0,   165,   166,    85,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   510,    86,
     0,    87,   167,     0,     0,    88,     0,   511,   168,   512,
   169,   513,   170,    89,    90,   514,   515,    91,   516,     0,
   143,     0,   517,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   172,   173,     0,     0,   174,
   175,     0,     0,   176,   177,   178,   179,   180,     0,     0,
     0,     0,     0,     0,     0,     0,   434,     0,   518,    52,
   158,   159,   160,   161,     0,     0,   162,    77,   499,    78,
     0,     0,    79,   500,     0,     0,   502,    80,     0,     0,
   503,    81,     0,     0,     0,     0,     0,   164,     0,   504,
    82,   505,   506,   507,   508,     0,     0,    83,     0,     0,
     0,   509,    84,     0,   165,   166,    85,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   510,    86,     0,    87,
   167,     0,     0,    88,     0,   511,   168,   512,   169,   513,
   170,    89,    90,   514,   515,    91,   516,     0,     0,     0,
   517,     0,     0,     0,     0,     0,     0,     0,    52,     0,
     0,     0,     0,     0,     0,     0,    77,     0,    78,     0,
     0,    79,     0,     0,     0,     0,    80,     0,     0,     0,
    81,     0,     0,   172,   173,     0,     0,   174,   175,    82,
     0,   176,   177,   178,   179,   180,    83,     0,     0,     0,
     0,    84,     0,     0,   434,    85,   518,    52,   158,   159,
   160,   161,     0,     0,   162,    77,    86,    78,    87,     0,
    79,   163,    88,     0,     0,    80,     0,     0,     0,    81,
    89,    90,     0,     0,    91,   164,     0,   143,    82,     0,
     0,     0,     0,     0,     0,    83,     0,     0,     0,     0,
    84,     0,   165,   166,    85,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    86,     0,    87,   167,   458,
     0,    88,     0,     0,   168,     0,   169,     0,   170,    89,
    90,   171,     0,    91,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    52,   158,   159,   160,
   161,     0,     0,   162,    77,     0,    78,     0,     0,    79,
   163,   172,   173,     0,    80,   174,   175,     0,    81,   176,
   177,   178,   179,   180,   164,     0,     0,    82,     0,     0,
     0,     0,   377,   648,    83,     0,     0,     0,     0,    84,
     0,   165,   166,    85,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    86,     0,    87,   167,   458,     0,
    88,     0,     0,   168,     0,   169,     0,   170,    89,    90,
   171,     0,    91,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    52,   158,   159,   160,   161,
     0,     0,   162,    77,     0,    78,     0,     0,    79,   163,
   172,   173,     0,    80,   174,   175,     0,    81,   176,   177,
   178,   179,   180,   164,     0,     0,    82,     0,     0,     0,
     0,   377,     0,    83,     0,     0,     0,     0,    84,     0,
   165,   166,    85,     0,   397,     0,     0,     0,     0,     0,
     0,   398,     0,    86,     0,    87,   167,     0,     0,    88,
     0,     0,   168,     0,   169,     0,   170,    89,    90,   171,
     0,    91,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    52,   158,   159,   160,   161,     0,
     0,   162,    77,     0,    78,     0,     0,    79,   163,     0,
     0,     0,    80,     0,     0,     0,    81,     0,     0,   172,
   173,     0,   164,   174,   175,    82,     0,   176,   177,   178,
   179,   180,    83,     0,     0,     0,     0,    84,     0,   165,
   166,    85,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    86,     0,    87,   167,     0,     0,    88,     0,
     0,   168,     0,   169,     0,   170,    89,    90,   171,     0,
    91,     0,     0,   261,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    52,   158,   159,   160,   161,     0,     0,
   162,    77,     0,    78,     0,     0,    79,   163,     0,     0,
     0,    80,     0,     0,     0,    81,     0,     0,   172,   173,
     0,   164,   174,   175,    82,     0,   176,   177,   178,   179,
   180,    83,     0,     0,     0,     0,    84,     0,   165,   166,
    85,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    86,     0,    87,   167,     0,     0,    88,     0,     0,
   168,     0,   169,     0,   170,    89,    90,   171,     0,    91,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    52,   158,   159,   160,   161,     0,     0,   162,
    77,     0,    78,     0,     0,    79,   163,   172,   173,     0,
    80,   174,   175,   473,    81,   176,   177,   178,   179,   180,
   164,     0,     0,    82,     0,     0,     0,     0,     0,     0,
    83,     0,     0,     0,     0,    84,     0,   165,   166,    85,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    86,     0,    87,   167,     0,     0,    88,     0,     0,   168,
     0,   169,     0,   170,    89,    90,   171,     0,    91,     0,
     0,   143,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    52,   158,   159,   160,   161,     0,     0,   162,    77,
     0,    78,     0,     0,    79,   163,     0,     0,     0,    80,
     0,     0,     0,    81,     0,     0,   172,   173,     0,   164,
   174,   175,    82,     0,   176,   177,   178,   179,   180,    83,
     0,     0,     0,     0,    84,     0,   165,   166,    85,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    86,
     0,    87,   167,     0,     0,    88,     0,     0,   168,     0,
   169,     0,   170,    89,    90,   171,     0,    91,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    52,   158,   159,   160,   161,     0,     0,   162,    77,     0,
    78,     0,     0,    79,   163,     0,     0,     0,    80,     0,
     0,     0,    81,     0,     0,   172,   173,     0,   164,   174,
   175,    82,     0,   176,   177,   178,   179,   180,    83,     0,
     0,     0,     0,    84,     0,   165,   166,    85,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
    87,   167,     0,     0,    88,     0,     0,   168,     0,   169,
   485,   170,    89,    90,   171,     0,    91,     0,    77,     0,
    78,     0,     0,    79,     0,    56,   486,     0,    80,     0,
    57,     0,    81,     0,    58,   487,   488,     0,     0,     0,
     0,    82,     0,     0,     0,     0,   489,  -297,    83,    59,
     0,     0,     0,    84,     0,     0,    30,    85,     0,   175,
     0,     0,     0,   177,   178,     0,     0,     0,    86,     0,
    87,     0,     0,     0,    88,    60,     0,     0,    31,     0,
     0,     0,    89,    90,     0,     0,    91,     0,     0,   490,
     0,    32,     0,     0,     0,    33,    34,     0,     0,     0,
     0,    35,     0,    36,    37,    38,    39,     0,     0,     0,
    40,     0,     0,     0,    41,     0,     0,   485,     0,     0,
     0,     0,     0,     0,     0,    77,    42,    78,     0,    43,
    79,    44,    56,   486,   491,    80,     0,    57,     0,    81,
     0,    58,   487,   488,     0,     0,     0,     0,    82,     0,
     0,     0,     0,   489,     0,    83,    59,     0,     0,     0,
    84,    52,     0,     0,    85,     0,     0,     0,     0,    77,
     0,    78,     0,     0,    79,    86,     0,    87,     0,    80,
     0,    88,    60,    81,     0,     0,   570,     0,     0,    89,
    90,     0,    82,    91,     0,     0,   490,     0,     0,    83,
     0,     0,     0,     0,    84,    52,     0,     0,    85,     0,
     0,     0,     0,    77,     0,    78,     0,     0,    79,    86,
     0,    87,     0,    80,     0,    88,     0,    81,     0,     0,
     0,     0,     0,    89,    90,     0,    82,    91,     0,     0,
   571,     0,     0,    83,     0,     0,     0,     0,    84,     0,
    30,     0,    85,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    86,     0,    87,     0,     0,     0,    88,
     0,     0,    31,     0,     0,     0,     0,    89,    90,     0,
     0,    91,     0,     0,   380,    32,     0,     0,     0,    33,
    34,     0,     0,     0,     0,    35,     0,    36,    37,    38,
    39,     0,     0,     0,    40,     0,     0,     0,    41,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    42,     0,     0,    43,     0,    44
};

static const short yycheck[] = {     2,
     1,   254,    71,   327,   534,    96,   315,   503,   600,   617,
    13,   614,   103,   104,   149,    13,   231,   152,   585,   262,
   263,     3,    57,     3,    10,   629,    27,     0,   577,   813,
   814,   246,    33,   249,   519,   117,   175,     4,   246,   246,
    11,   614,   246,   246,   246,   246,   246,     4,   246,    97,
    81,   643,   100,     3,   136,   628,    57,    97,   274,    45,
     4,     3,     3,   132,    98,    97,   375,     3,    98,    97,
    71,   140,   856,   857,     4,     4,     4,   607,     4,    57,
   149,     4,     4,   152,     3,     4,     4,    57,   123,     4,
     4,     4,   659,     4,     4,     4,     4,     4,   314,     4,
    71,   141,   587,   828,   829,   140,   140,   322,    52,   141,
   140,   836,   661,   141,    71,    98,    15,    98,    98,    53,
   687,    55,   123,   731,    23,    98,    60,    71,   114,   115,
   165,   132,    99,   858,   137,   121,   141,   921,   922,   140,
   175,    71,   125,   123,    98,   123,   750,   133,   149,   392,
   754,   152,   755,   123,   369,   722,   723,   139,   297,   298,
   376,   369,   369,   254,   165,   369,   369,   369,   369,   369,
   494,   369,   122,   497,   175,   266,   500,    98,   122,    98,
   122,   122,   317,   125,   125,   121,   140,   165,     4,   513,
   514,   515,   122,   122,   122,   165,   122,   175,   923,   122,
   122,    98,   121,   122,   123,   319,     4,   122,   122,   122,
    98,   122,   122,   122,   122,   122,    98,   122,    19,   140,
   255,   256,    98,    24,   227,   817,   123,    28,   231,   227,
     5,     6,     7,     8,    98,    51,   844,   240,   841,    98,
   243,   141,    43,   246,   358,   129,   130,    97,   317,   318,
    98,    98,    68,    97,   255,   256,     4,    32,   140,    98,
    98,    97,   758,   759,   140,   300,   301,   684,    69,    97,
   766,   767,    98,   690,   124,    50,   140,   255,   256,    98,
   124,   140,    97,    97,   122,   255,   256,    14,   124,     4,
    17,   141,   140,   140,    98,   125,   124,   141,    73,   300,
   301,   140,   798,    98,   339,   141,   341,    98,   725,   124,
   124,   903,   904,   141,   140,    42,   317,   318,    98,   322,
    47,   140,   300,   301,    97,    97,   141,   141,   125,   125,
   300,   301,   122,   123,   125,    62,   140,    64,   339,   123,
   341,    16,   138,     4,   124,   140,     4,   843,   351,    76,
    77,   124,   124,    80,    12,   139,    14,   887,    33,    17,
   123,   339,     4,   341,    22,   122,   369,   123,    26,   339,
   125,   341,     4,    15,   131,   132,   139,    35,   118,   119,
   120,    23,   137,   139,    42,   881,   232,   711,   712,    47,
   112,   113,   645,    51,     4,   241,   431,   139,   244,   434,
   137,   247,   122,   438,    62,   123,    64,   125,   122,   905,
    68,   131,   132,   448,   122,   739,   451,   121,    76,    77,
   138,   139,    80,   458,    97,    83,    99,   139,     3,   141,
   431,   137,    97,   434,    99,    29,   122,   438,   124,   302,
   303,   304,   305,   446,   122,     4,   124,   448,   122,   123,
   451,   486,   487,   431,   122,   123,   434,   458,   434,   123,
   438,   431,   122,   139,   124,   141,   501,    61,   438,    97,
   448,    99,   563,   451,    97,    97,    99,    99,   448,   141,
   458,   451,   123,   574,   125,   486,   487,   137,   458,   490,
   123,   492,    86,    87,    88,    89,    90,    91,    92,   534,
   501,   139,   139,   141,   141,    97,   137,    99,   486,   487,
    97,    97,    99,    99,    93,    94,   486,   487,   139,   137,
   141,    93,    94,   501,    95,    96,   139,   503,   306,   307,
   434,   501,   123,   534,   139,   570,   915,   916,   172,   173,
   174,   139,   176,   177,   178,   179,   180,   863,   864,   873,
   874,   860,   861,   588,   589,   646,   534,   139,   534,   123,
   123,   123,    97,   123,   125,   889,   890,   125,   124,   570,
   109,   126,   607,   897,   898,   116,    97,   134,   613,   614,
   615,   135,   434,    97,   124,    97,   587,   588,   589,   140,
     4,    98,   570,   628,   124,     4,     4,     4,     4,   503,
   570,     4,   140,    97,   141,    49,   607,   140,   140,   140,
   588,   589,   613,   614,   615,   124,   124,   134,   588,   589,
   124,   124,   124,    97,   124,   124,   137,   628,   138,   607,
   534,   607,   124,    97,   140,   613,   614,   615,   614,   124,
    52,    52,     4,   613,   141,   615,   141,   123,   123,   139,
   628,   503,   123,   123,   123,   123,   123,   123,   175,   140,
   294,   295,   296,   297,   298,   299,   138,   123,   302,   303,
   304,   305,   306,   307,   308,   309,   310,   311,   312,   141,
   141,   141,   534,   123,   434,    98,   123,    85,    98,   141,
   141,   141,   761,   141,   123,   138,    97,   123,    98,   124,
   139,   736,   737,   607,   138,   124,   100,   123,   743,     4,
   614,   101,   102,   103,   104,   105,   106,   107,   108,   139,
   110,   111,   139,    97,   123,    97,   761,   124,   124,   124,
    99,   124,   249,   124,   251,   736,   737,   141,     4,   141,
   257,   124,   743,   124,   747,    41,   749,   139,   138,   137,
   139,   138,     4,   503,   139,   607,   390,   274,   736,   737,
   761,   278,   614,   140,   124,   743,   736,   737,   124,   140,
   773,   124,   140,   743,   141,     4,   293,    27,   781,   755,
   123,   140,   758,   759,   534,   123,   140,   124,   791,   792,
   766,   767,   124,    94,    93,   141,   313,   314,   124,   140,
   434,   137,   124,   124,   139,    96,    95,   124,   137,   124,
   124,    94,    93,   140,   849,   124,     0,     0,   438,   822,
   823,   336,   798,   165,   637,   127,   165,   434,   646,   398,
   308,   480,   309,   386,   299,   469,   871,   471,   472,   473,
   849,   434,   391,   685,   610,   732,   841,   310,   849,   849,
   847,   755,   887,   311,   758,   759,   512,   607,   312,   376,
   377,   434,   766,   767,   614,   841,   809,   843,   713,   503,
   871,   849,   713,   849,   115,   492,     3,   797,   137,    46,
   397,   398,   749,   874,   322,   791,   887,   822,   891,   892,
   343,   894,   823,   871,   798,   894,   503,   792,   446,    22,
   534,   871,   351,   755,   132,   881,   758,   759,   155,   887,
   503,   887,   369,    -1,   766,   767,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   534,    -1,   905,
   503,    -1,    -1,    -1,    -1,    -1,    -1,   841,    -1,   843,
    -1,   534,    -1,    -1,    -1,   849,   798,    -1,   582,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   534,    -1,    -1,    -1,   482,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   607,    -1,    -1,    -1,   881,    -1,    -1,
   614,    32,    -1,   887,    -1,    -1,    -1,    -1,    -1,   841,
    -1,   843,    -1,   510,    -1,   512,    -1,   849,    -1,    -1,
   607,   905,    -1,    -1,    -1,   755,    -1,   614,   758,   759,
    -1,    -1,    -1,    -1,   607,    -1,   766,   767,    -1,    -1,
    -1,   614,    73,    -1,    -1,    -1,    -1,    -1,    -1,   881,
    -1,    -1,    -1,    -1,   607,   887,    -1,    -1,    -1,    -1,
    -1,   614,    -1,    -1,    -1,    -1,    -1,    -1,   798,    -1,
   567,    -1,    -1,   905,    -1,    -1,    -1,    -1,   109,    -1,
   577,   112,   113,   114,   115,    -1,    -1,   118,   119,    -1,
   121,   122,    -1,    -1,    -1,   126,   127,   128,   129,   130,
   131,   132,   133,   134,   135,    -1,    -1,    -1,    -1,    -1,
    -1,   841,    -1,   843,    -1,    -1,    -1,    -1,    -1,   849,
   617,    -1,   619,   620,    -1,    -1,   623,    -1,    -1,    -1,
    -1,   628,   629,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   755,    -1,    -1,   758,   759,    -1,    -1,    -1,    -1,
   647,   881,   766,   767,    -1,    -1,    -1,   887,    -1,    -1,
    -1,    -1,    -1,    -1,   661,    -1,    -1,    -1,   755,    -1,
    -1,   758,   759,    -1,    -1,   905,    -1,    -1,    -1,   766,
   767,    -1,   755,    -1,   798,   758,   759,    -1,    -1,    -1,
    -1,    -1,    -1,   766,   767,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   755,    -1,    -1,   758,   759,    -1,    -1,    -1,
    -1,   798,    -1,   766,   767,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   798,    -1,   841,    -1,   843,
    -1,    -1,    -1,    -1,   731,   849,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   798,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   750,   841,    -1,   843,   754,    -1,    -1,
    -1,    -1,   849,    -1,    -1,    -1,    -1,   881,   841,    -1,
   843,    -1,    -1,   887,    -1,     9,   849,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   841,    -1,
   843,   905,    -1,    -1,   881,    -1,   849,    31,    -1,   796,
   887,    -1,    -1,    -1,    -1,    -1,   803,    -1,   881,    -1,
    44,    -1,    -1,    -1,   887,    49,    -1,    -1,   905,    -1,
    54,    -1,    56,    57,    58,    59,    -1,    -1,   881,    63,
    -1,    -1,   905,    67,   887,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    79,    -1,   844,    82,    -1,
    84,    -1,   905,     4,     5,     6,     7,     8,    -1,    -1,
    11,    12,    13,    14,    15,    -1,    17,    18,    -1,    20,
    21,    22,    23,    -1,    25,    26,    -1,    -1,    -1,    -1,
    -1,    32,    -1,    34,    35,    36,    37,    38,    39,    -1,
    -1,    42,    -1,    -1,    -1,    46,    47,    -1,    49,    50,
    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    61,    62,    -1,    64,    65,    -1,    -1,    68,    -1,    70,
    71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
    81,    -1,    83,    -1,    85,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,
    -1,   122,   123,    -1,    -1,   126,   127,   128,   129,   130,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,
   141,     4,     5,     6,     7,     8,    -1,    -1,    11,    12,
    13,    14,    -1,    -1,    17,    18,    -1,    20,    21,    22,
    -1,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    32,
    -1,    34,    35,    36,    37,    38,    39,    -1,    -1,    42,
    -1,    -1,    -1,    46,    47,    -1,    49,    50,    51,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
    -1,    64,    65,    -1,    -1,    68,    -1,    70,    71,    72,
    73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
    83,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,   122,
   123,    -1,    -1,   126,   127,   128,   129,   130,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,     4,
     5,     6,     7,     8,    -1,    -1,    11,    12,    13,    14,
    -1,    -1,    17,    18,    -1,    -1,    21,    22,    -1,    -1,
    25,    26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    34,
    35,    36,    37,    38,    39,    -1,    -1,    42,    -1,    -1,
    -1,    46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    64,
    65,    -1,    -1,    68,    -1,    70,    71,    72,    73,    74,
    75,    76,    77,    78,    79,    80,    81,    -1,    -1,    -1,
    85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    14,    -1,
    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
    26,    -1,    -1,   118,   119,    -1,    -1,   122,   123,    35,
    -1,   126,   127,   128,   129,   130,    42,    -1,    -1,    -1,
    -1,    47,    -1,    -1,   139,    51,   141,     4,     5,     6,
     7,     8,    -1,    -1,    11,    12,    62,    14,    64,    -1,
    17,    18,    68,    -1,    -1,    22,    -1,    -1,    -1,    26,
    76,    77,    -1,    -1,    80,    32,    -1,    83,    35,    -1,
    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
    47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,    66,
    -1,    68,    -1,    -1,    71,    -1,    73,    -1,    75,    76,
    77,    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,
     8,    -1,    -1,    11,    12,    -1,    14,    -1,    -1,    17,
    18,   118,   119,    -1,    22,   122,   123,    -1,    26,   126,
   127,   128,   129,   130,    32,    -1,    -1,    35,    -1,    -1,
    -1,    -1,   139,   140,    42,    -1,    -1,    -1,    -1,    47,
    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    62,    -1,    64,    65,    66,    -1,
    68,    -1,    -1,    71,    -1,    73,    -1,    75,    76,    77,
    78,    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
    -1,    -1,    11,    12,    -1,    14,    -1,    -1,    17,    18,
   118,   119,    -1,    22,   122,   123,    -1,    26,   126,   127,
   128,   129,   130,    32,    -1,    -1,    35,    -1,    -1,    -1,
    -1,   139,    -1,    42,    -1,    -1,    -1,    -1,    47,    -1,
    49,    50,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
    -1,    60,    -1,    62,    -1,    64,    65,    -1,    -1,    68,
    -1,    -1,    71,    -1,    73,    -1,    75,    76,    77,    78,
    -1,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,    -1,
    -1,    11,    12,    -1,    14,    -1,    -1,    17,    18,    -1,
    -1,    -1,    22,    -1,    -1,    -1,    26,    -1,    -1,   118,
   119,    -1,    32,   122,   123,    35,    -1,   126,   127,   128,
   129,   130,    42,    -1,    -1,    -1,    -1,    47,    -1,    49,
    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    62,    -1,    64,    65,    -1,    -1,    68,    -1,
    -1,    71,    -1,    73,    -1,    75,    76,    77,    78,    -1,
    80,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,     4,     5,     6,     7,     8,    -1,    -1,
    11,    12,    -1,    14,    -1,    -1,    17,    18,    -1,    -1,
    -1,    22,    -1,    -1,    -1,    26,    -1,    -1,   118,   119,
    -1,    32,   122,   123,    35,    -1,   126,   127,   128,   129,
   130,    42,    -1,    -1,    -1,    -1,    47,    -1,    49,    50,
    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    62,    -1,    64,    65,    -1,    -1,    68,    -1,    -1,
    71,    -1,    73,    -1,    75,    76,    77,    78,    -1,    80,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,     4,     5,     6,     7,     8,    -1,    -1,    11,
    12,    -1,    14,    -1,    -1,    17,    18,   118,   119,    -1,
    22,   122,   123,   124,    26,   126,   127,   128,   129,   130,
    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,
    42,    -1,    -1,    -1,    -1,    47,    -1,    49,    50,    51,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    62,    -1,    64,    65,    -1,    -1,    68,    -1,    -1,    71,
    -1,    73,    -1,    75,    76,    77,    78,    -1,    80,    -1,
    -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,     4,     5,     6,     7,     8,    -1,    -1,    11,    12,
    -1,    14,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,
    -1,    -1,    -1,    26,    -1,    -1,   118,   119,    -1,    32,
   122,   123,    35,    -1,   126,   127,   128,   129,   130,    42,
    -1,    -1,    -1,    -1,    47,    -1,    49,    50,    51,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
    -1,    64,    65,    -1,    -1,    68,    -1,    -1,    71,    -1,
    73,    -1,    75,    76,    77,    78,    -1,    80,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     4,     5,     6,     7,     8,    -1,    -1,    11,    12,    -1,
    14,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
    -1,    -1,    26,    -1,    -1,   118,   119,    -1,    32,   122,
   123,    35,    -1,   126,   127,   128,   129,   130,    42,    -1,
    -1,    -1,    -1,    47,    -1,    49,    50,    51,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
    64,    65,    -1,    -1,    68,    -1,    -1,    71,    -1,    73,
     4,    75,    76,    77,    78,    -1,    80,    -1,    12,    -1,
    14,    -1,    -1,    17,    -1,    19,    20,    -1,    22,    -1,
    24,    -1,    26,    -1,    28,    29,    30,    -1,    -1,    -1,
    -1,    35,    -1,    -1,    -1,    -1,    40,     0,    42,    43,
    -1,    -1,    -1,    47,    -1,    -1,     9,    51,    -1,   123,
    -1,    -1,    -1,   127,   128,    -1,    -1,    -1,    62,    -1,
    64,    -1,    -1,    -1,    68,    69,    -1,    -1,    31,    -1,
    -1,    -1,    76,    77,    -1,    -1,    80,    -1,    -1,    83,
    -1,    44,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,
    -1,    54,    -1,    56,    57,    58,    59,    -1,    -1,    -1,
    63,    -1,    -1,    -1,    67,    -1,    -1,     4,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    12,    79,    14,    -1,    82,
    17,    84,    19,    20,   128,    22,    -1,    24,    -1,    26,
    -1,    28,    29,    30,    -1,    -1,    -1,    -1,    35,    -1,
    -1,    -1,    -1,    40,    -1,    42,    43,    -1,    -1,    -1,
    47,     4,    -1,    -1,    51,    -1,    -1,    -1,    -1,    12,
    -1,    14,    -1,    -1,    17,    62,    -1,    64,    -1,    22,
    -1,    68,    69,    26,    -1,    -1,    29,    -1,    -1,    76,
    77,    -1,    35,    80,    -1,    -1,    83,    -1,    -1,    42,
    -1,    -1,    -1,    -1,    47,     4,    -1,    -1,    51,    -1,
    -1,    -1,    -1,    12,    -1,    14,    -1,    -1,    17,    62,
    -1,    64,    -1,    22,    -1,    68,    -1,    26,    -1,    -1,
    -1,    -1,    -1,    76,    77,    -1,    35,    80,    -1,    -1,
    83,    -1,    -1,    42,    -1,    -1,    -1,    -1,    47,    -1,
     9,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    62,    -1,    64,    -1,    -1,    -1,    68,
    -1,    -1,    31,    -1,    -1,    -1,    -1,    76,    77,    -1,
    -1,    80,    -1,    -1,    83,    44,    -1,    -1,    -1,    48,
    49,    -1,    -1,    -1,    -1,    54,    -1,    56,    57,    58,
    59,    -1,    -1,    -1,    63,    -1,    -1,    -1,    67,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    79,    -1,    -1,    82,    -1,    84
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
#line 121 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 2:
#line 122 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 3:
#line 123 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 4:
#line 124 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 5:
#line 125 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 6:
#line 126 "csharp.y"
{ R(); yyval.value = yyvsp[0].value; ;
    break;}
case 7:
#line 129 "csharp.y"
{ R(); yyval.value.type = TYPE_BOOL; yyval.value.v.i = 1; ;
    break;}
case 8:
#line 130 "csharp.y"
{ R(); yyval.value.type = TYPE_BOOL; yyval.value.v.i = 0; ;
    break;}
case 9:
#line 140 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; ;
    break;}
case 10:
#line 143 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(yyvsp[-1].text, TYPE_UNRESOLVED); /* TODO : generic here -> Sub type*/ ;
    break;}
case 11:
#line 146 "csharp.y"
{ R(); yyval.type = NULL;		;
    break;}
case 12:
#line 147 "csharp.y"
{ R(); yyval.type = yyvsp[0].type;	;
    break;}
case 13:
#line 151 "csharp.y"
{ R(); yyval.type = yyvsp[-2].type; 	;
    break;}
case 14:
#line 154 "csharp.y"
{ R(); ;
    break;}
case 15:
#line 155 "csharp.y"
{ R(); ;
    break;}
case 16:
#line 158 "csharp.y"
{ R(); lex_in_generic();		;
    break;}
case 17:
#line 159 "csharp.y"
{ R(); lex_out_generic();	;
    break;}
case 18:
#line 163 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 19:
#line 164 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 20:
#line 167 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 21:
#line 168 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 22:
#line 171 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 23:
#line 172 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 24:
#line 173 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 25:
#line 176 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 26:
#line 177 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 27:
#line 180 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 28:
#line 181 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 30:
#line 185 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_SBYTE);		;
    break;}
case 31:
#line 186 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_BYTE);		;
    break;}
case 32:
#line 187 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_SHORT);		;
    break;}
case 33:
#line 188 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_USHORT);		;
    break;}
case 34:
#line 189 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_INT); 		;
    break;}
case 35:
#line 190 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_UINT); 		;
    break;}
case 36:
#line 191 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_LONG); 		;
    break;}
case 37:
#line 192 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_ULONG); 		;
    break;}
case 38:
#line 193 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_CHAR); 		;
    break;}
case 39:
#line 196 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_FLOAT); 		;
    break;}
case 40:
#line 197 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_DOUBLE); 	;
    break;}
case 41:
#line 200 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_OBJECT); 	;
    break;}
case 42:
#line 201 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_STRING); 	;
    break;}
case 43:
#line 204 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addPointer();						;
    break;}
case 44:
#line 205 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_VOID)->addPointer(); ;
    break;}
case 45:
#line 208 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addRank(yyvsp[0].tmpValue);	;
    break;}
case 46:
#line 209 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addRank(yyvsp[0].tmpValue);	;
    break;}
case 47:
#line 211 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type->addRank(yyvsp[0].tmpValue);	;
    break;}
case 48:
#line 214 "csharp.y"
{ R(); yyval.tmpValue = 0;		;
    break;}
case 49:
#line 216 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[-1].tmpValue; ;
    break;}
case 50:
#line 219 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; ;
    break;}
case 51:
#line 227 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 52:
#line 231 "csharp.y"
{ R(); yyval.expr = CreateMultipleExpr(yyvsp[0].expr); 		;
    break;}
case 53:
#line 232 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[-1].expr);	;
    break;}
case 54:
#line 235 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 								;
    break;}
case 55:
#line 236 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_REF, yyvsp[-1].expr);	;
    break;}
case 56:
#line 237 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_OUT, yyvsp[-1].expr);	;
    break;}
case 57:
#line 240 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 58:
#line 241 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 59:
#line 244 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_CTE)->setValue(yyvsp[0].value); ;
    break;}
case 60:
#line 245 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 61:
#line 246 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 62:
#line 247 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 63:
#line 248 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 64:
#line 249 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 65:
#line 250 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 66:
#line 251 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 67:
#line 252 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 68:
#line 253 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 69:
#line 254 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 70:
#line 255 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 71:
#line 258 "csharp.y"
{ R(); yyval.expr = yyvsp[-1].expr->addParenthesis(); ;
    break;}
case 72:
#line 261 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DOT, yyvsp[-2].expr, yyvsp[-1].expr);	;
    break;}
case 73:
#line 262 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DOT, yyvsp[-2].expr, yyvsp[-1].expr);	;
    break;}
case 74:
#line 263 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DOT, yyvsp[-2].expr, yyvsp[-1].expr);	;
    break;}
case 75:
#line 266 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_INVOKE, yyvsp[-3].expr, yyvsp[-1].expr);	;
    break;}
case 76:
#line 267 "csharp.y"
{ R();
	yyval.expr = CreateDoubleExpr(EXPR_INVOKE, NULL, yyvsp[-1].expr)->setIdentifier(yyvsp[-3].text);
  ;
    break;}
case 77:
#line 272 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 78:
#line 273 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 79:
#line 276 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, yyvsp[-3].expr, yyvsp[-1].expr);	;
    break;}
case 80:
#line 277 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, yyvsp[-3].expr, yyvsp[-1].expr);	;
    break;}
case 81:
#line 281 "csharp.y"
{ R(); yyval.expr = NULL;								;
    break;}
case 82:
#line 282 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;							;
    break;}
case 83:
#line 286 "csharp.y"
{ R(); yyval.expr = CreateMultipleExpr(yyvsp[0].expr); 		;
    break;}
case 84:
#line 287 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[0].expr); 	;
    break;}
case 85:
#line 290 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_THIS);			;
    break;}
case 86:
#line 293 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_BASE))->setIdentifier(yyvsp[0].text); ;
    break;}
case 87:
#line 294 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_BASE), yyvsp[-1].expr);;
    break;}
case 88:
#line 297 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PLUSPLUS, yyvsp[-1].expr);	;
    break;}
case 89:
#line 300 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_MINUSMINUS, yyvsp[-1].expr);;
    break;}
case 90:
#line 303 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 91:
#line 306 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_NEW, yyvsp[-1].expr)->setType(yyvsp[-3].type); ;
    break;}
case 92:
#line 310 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_NEW, yyvsp[-3].expr, yyvsp[0].expr)->setType(yyvsp[-5].type)->setRank(yyvsp[-1].tmpValue)->setArrayNew(); ;
    break;}
case 93:
#line 311 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_NEW, NULL, yyvsp[0].expr)->setArrayNew(); ;
    break;}
case 94:
#line 314 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 95:
#line 315 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 96:
#line 318 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_TYPEOF)->setType(yyvsp[-1].type); ;
    break;}
case 97:
#line 319 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"typeof(void)"); ;
    break;}
case 98:
#line 322 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_CHECKED, yyvsp[-1].expr); ;
    break;}
case 99:
#line 325 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNCHECKED, yyvsp[-1].expr); ;
    break;}
case 100:
#line 328 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_ARROW, yyvsp[-2].expr)->setIdentifier(yyvsp[0].text); ;
    break;}
case 101:
#line 331 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_ADRESSOF, yyvsp[-1].expr);		;
    break;}
case 102:
#line 334 "csharp.y"
{ R(); yyval.expr = CreateLeafExpr(EXPR_SIZEOF)->setType(yyvsp[-1].type);	;
    break;}
case 103:
#line 337 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 104:
#line 338 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 105:
#line 339 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 106:
#line 340 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 107:
#line 341 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 108:
#line 344 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 109:
#line 345 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_NOT, yyvsp[0].expr);		;
    break;}
case 110:
#line 346 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_LNOT, yyvsp[0].expr);		;
    break;}
case 111:
#line 347 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 112:
#line 350 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PREINCR, yyvsp[0].expr);	;
    break;}
case 113:
#line 353 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_PREDECR, yyvsp[0].expr);	;
    break;}
case 114:
#line 356 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 115:
#line 357 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNARYPLUS, yyvsp[0].expr);	;
    break;}
case 116:
#line 358 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNARYMINUS, yyvsp[0].expr);	;
    break;}
case 117:
#line 359 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_UNARYMULT, yyvsp[0].expr);	;
    break;}
case 118:
#line 360 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 119:
#line 361 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 120:
#line 362 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 121:
#line 370 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_CAST, yyvsp[-2].expr, yyvsp[0].expr);		;
    break;}
case 122:
#line 371 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_CAST_PTR, yyvsp[-3].expr, yyvsp[-1].expr);	;
    break;}
case 123:
#line 373 "csharp.y"
{ R();
		// TODO Cast D
	;
    break;}
case 124:
#line 377 "csharp.y"
{ R();
		// TODO Cast E
	;
    break;}
case 125:
#line 381 "csharp.y"
{ R();
		// TODO Cast F
	;
    break;}
case 126:
#line 385 "csharp.y"
{ R();
		// TODO Cast G
	;
    break;}
case 133:
#line 404 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 134:
#line 405 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MULT, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 135:
#line 406 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DIV, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 136:
#line 407 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MOD, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 137:
#line 410 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 138:
#line 411 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_PLUS, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 139:
#line 412 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MINUS, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 140:
#line 415 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 141:
#line 416 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LSHFT, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 142:
#line 420 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 143:
#line 421 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LESS, yyvsp[-2].expr, yyvsp[0].expr);			;
    break;}
case 144:
#line 422 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MORE, yyvsp[-2].expr, yyvsp[0].expr);			;
    break;}
case 145:
#line 423 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LESSEQ, yyvsp[-2].expr, yyvsp[0].expr);		;
    break;}
case 146:
#line 424 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_MOREEQ, yyvsp[-2].expr, yyvsp[0].expr);		;
    break;}
case 147:
#line 425 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_IS, yyvsp[-2].expr)->setType(yyvsp[0].type);	;
    break;}
case 148:
#line 426 "csharp.y"
{ R(); yyval.expr = CreateSingleExpr(EXPR_AS, yyvsp[-2].expr)->setType(yyvsp[0].type);	;
    break;}
case 149:
#line 429 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 150:
#line 430 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_EQUTST, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 151:
#line 431 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_DIFFTST, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 152:
#line 434 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 153:
#line 435 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LAND, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 154:
#line 438 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 155:
#line 439 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LXOR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 156:
#line 442 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 157:
#line 443 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_LOR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 158:
#line 446 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 159:
#line 447 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_AND, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 160:
#line 450 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 161:
#line 451 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr(EXPR_OR, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 162:
#line 454 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 163:
#line 455 "csharp.y"
{ R(); yyval.expr = CreateTripleExpr(EXPR_COND, yyvsp[-4].expr, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 164:
#line 457 "csharp.y"
{ R(); yyval.expr = CreateDoubleExpr((EnumExpressionType)yyvsp[-1].tmpValue, yyvsp[-2].expr, yyvsp[0].expr);	;
    break;}
case 165:
#line 460 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_EQ;		;
    break;}
case 166:
#line 461 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_PLUSEQ;	;
    break;}
case 167:
#line 462 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_MINUSEQ;	;
    break;}
case 168:
#line 463 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_STAREQ;	;
    break;}
case 169:
#line 464 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_DIVEQ;	;
    break;}
case 170:
#line 465 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_MODEQ;	;
    break;}
case 171:
#line 466 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_XOREQ;	;
    break;}
case 172:
#line 467 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_ANDEQ;	;
    break;}
case 173:
#line 468 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_OREQ;	;
    break;}
case 174:
#line 469 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_RSHFTEQ;	;
    break;}
case 175:
#line 470 "csharp.y"
{ R(); yyval.tmpValue	= EXPR_ASS_LSHFTEQ;	;
    break;}
case 176:
#line 474 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 177:
#line 475 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 178:
#line 478 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 179:
#line 481 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 180:
#line 496 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 181:
#line 497 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 182:
#line 498 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 183:
#line 501 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 184:
#line 502 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 185:
#line 503 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 186:
#line 504 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 187:
#line 505 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 188:
#line 506 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 189:
#line 507 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 190:
#line 508 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 191:
#line 509 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 192:
#line 510 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 193:
#line 511 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 194:
#line 512 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 195:
#line 513 "csharp.y"
{ R(); yyval.statement	= yyvsp[0].statement; ;
    break;}
case 196:
#line 516 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_BLOCK, NULL, yyvsp[-1].statement); ;
    break;}
case 197:
#line 519 "csharp.y"
{ R(); yyval.statement = NULL; ;
    break;}
case 198:
#line 520 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 199:
#line 524 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 200:
#line 525 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement ? yyvsp[-1].statement->addNext(yyvsp[0].statement) : yyvsp[0].statement; ;
    break;}
case 201:
#line 528 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_NULL, NULL, NULL); ;
    break;}
case 202:
#line 531 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_LABEL, yyvsp[0].statement, NULL)->addLabel(yyvsp[-2].text);	;
    break;}
case 203:
#line 534 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement;	;
    break;}
case 204:
#line 535 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement;	;
    break;}
case 205:
#line 538 "csharp.y"
{ R(); yyval.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, yyvsp[0].variable, yyvsp[-1].type); ;
    break;}
case 206:
#line 541 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable; ;
    break;}
case 207:
#line 542 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[0].variable); ;
    break;}
case 208:
#line 545 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[0].text);	;
    break;}
case 209:
#line 546 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-2].text)->setInitializer(yyvsp[0].expr); ;
    break;}
case 210:
#line 549 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 211:
#line 550 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 212:
#line 551 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; ;
    break;}
case 213:
#line 554 "csharp.y"
{ R(); /* Only in unsafe code from spec */compilerError(UNSUPPORTED,"stackalloc"); ;
    break;}
case 214:
#line 557 "csharp.y"
{ R(); yyval.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, yyvsp[0].variable, yyvsp[-1].type)->setConstant(); ;
    break;}
case 215:
#line 560 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable; ;
    break;}
case 216:
#line 561 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[0].variable); ;
    break;}
case 217:
#line 564 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-2].text)->setInitializer(yyvsp[0].expr); ;
    break;}
case 218:
#line 567 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement; ;
    break;}
case 219:
#line 570 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 220:
#line 571 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 221:
#line 572 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 222:
#line 573 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_POSTINCR,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 223:
#line 574 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_POSTDECR,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 224:
#line 575 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_PREINCR ,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 225:
#line 576 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WRAPPER_PREDECR ,NULL,NULL)->setExpression(yyvsp[0].expr); ;
    break;}
case 226:
#line 579 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 227:
#line 580 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 228:
#line 583 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_IF, NULL, yyvsp[0].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 229:
#line 584 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_IF, NULL, yyvsp[-2].statement)->addChild(yyvsp[0].statement)->setExpression(yyvsp[-4].expr); ;
    break;}
case 230:
#line 587 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_SWITCH, NULL, yyvsp[0].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 231:
#line 590 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement; ;
    break;}
case 232:
#line 593 "csharp.y"
{ R(); yyval.statement = NULL; ;
    break;}
case 233:
#line 594 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 234:
#line 597 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 235:
#line 598 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 236:
#line 601 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addChild(yyvsp[0].statement); ;
    break;}
case 237:
#line 605 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 238:
#line 606 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 239:
#line 609 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CASE, NULL, NULL		)->setExpression(yyvsp[-1].expr); ;
    break;}
case 240:
#line 610 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CASEDEFAULT, NULL, NULL); ;
    break;}
case 241:
#line 613 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 242:
#line 614 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 243:
#line 615 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 244:
#line 616 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 245:
#line 619 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_UNSAFE, NULL, yyvsp[0].statement); ;
    break;}
case 246:
#line 623 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_WHILE, NULL, yyvsp[0].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 247:
#line 627 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_DOWHILE, NULL, yyvsp[-5].statement)->setExpression(yyvsp[-2].expr); ;
    break;}
case 248:
#line 631 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_FOR, NULL, yyvsp[-7].statement)	->setExpression	 (yyvsp[-4].expr)
																	->addChildNilWrap(yyvsp[-6].statement)
																	->addChildNilWrap(yyvsp[-2].statement)
																	->addChildNilWrap(yyvsp[0].statement); ;
    break;}
case 249:
#line 637 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 250:
#line 638 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 251:
#line 641 "csharp.y"
{ R(); yyval.expr = NULL;		;
    break;}
case 252:
#line 642 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 253:
#line 645 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 254:
#line 646 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 255:
#line 649 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 256:
#line 650 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 257:
#line 653 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 258:
#line 656 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 259:
#line 659 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 260:
#line 660 "csharp.y"
{ R(); yyval.statement = yyvsp[-2].statement->addNext(yyvsp[0].statement); ;
    break;}
case 261:
#line 664 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_FOREACH, NULL, NULL)
											->setExpression(yyvsp[-2].expr)
											->addType(yyvsp[-5].type)
											->addChild(yyvsp[0].statement); 
										;
    break;}
case 262:
#line 671 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 263:
#line 672 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 264:
#line 673 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 265:
#line 674 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 266:
#line 675 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 267:
#line 678 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_BREAK, NULL, NULL); ;
    break;}
case 268:
#line 681 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CONTINUE, NULL, NULL); ;
    break;}
case 269:
#line 684 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTO, NULL,NULL)->addLabel(yyvsp[-1].text);	;
    break;}
case 270:
#line 685 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTOCASE, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 271:
#line 686 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_GOTODEFAULT, NULL,NULL); ;
    break;}
case 272:
#line 689 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_RETURN, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 273:
#line 692 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 274:
#line 693 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr; 	;
    break;}
case 275:
#line 696 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_THROW, NULL, NULL)->setExpression(yyvsp[-1].expr); ;
    break;}
case 276:
#line 699 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-1].statement)->addNext(yyvsp[0].statement); 
										;
    break;}
case 277:
#line 702 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-1].statement)->addNext(yyvsp[0].statement);
										;
    break;}
case 278:
#line 706 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild(yyvsp[-2].statement)->addNext(yyvsp[-1].statement)->addNext(yyvsp[0].statement);
										;
    break;}
case 279:
#line 711 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; ;
    break;}
case 280:
#line 712 "csharp.y"
{ R(); yyval.statement = yyvsp[-1].statement->addNext(yyvsp[0].statement); ;
    break;}
case 281:
#line 715 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CATCH, NULL, NULL)
														->addChild(yyvsp[0].statement)->addLabel(yyvsp[-2].text)->addType(yyvsp[-3].type); 
													;
    break;}
case 282:
#line 718 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CATCH, NULL, NULL)
														->addChild(yyvsp[0].statement)->addLabel(yyvsp[-2].text)->addType(yyvsp[-3].type); 
													;
    break;}
case 283:
#line 721 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CATCH, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 284:
#line 724 "csharp.y"
{ R(); yyval.text = NULL; ;
    break;}
case 285:
#line 725 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; ;
    break;}
case 286:
#line 728 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_FINALLY, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 287:
#line 731 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_CHECKED, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 288:
#line 734 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_UNCHECKED, NULL, NULL)->addChild(yyvsp[0].statement); ;
    break;}
case 289:
#line 737 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_LOCK, NULL, NULL)
														->addChild(yyvsp[0].statement)->setExpression(yyvsp[-2].expr);
													;
    break;}
case 290:
#line 743 "csharp.y"
{ R(); yyval.statement = CreateStatement(STM_USING, NULL, NULL)->addChild(yyvsp[-2].statement)->addChild(yyvsp[0].statement); ;
    break;}
case 291:
#line 746 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement ;
    break;}
case 292:
#line 747 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement ;
    break;}
case 293:
#line 752 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"FIXED not supported."); ;
    break;}
case 294:
#line 755 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 295:
#line 756 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 296:
#line 759 "csharp.y"
{ R(); /* When FIXED Support */ ;
    break;}
case 297:
#line 768 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 298:
#line 769 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 299:
#line 772 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 300:
#line 773 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 301:
#line 776 "csharp.y"
{ R(); yyval.attribute = NULL; ;
    break;}
case 302:
#line 777 "csharp.y"
{ R(); yyval.attribute = yyvsp[0].attribute; ;
    break;}
case 303:
#line 780 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 304:
#line 781 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 305:
#line 784 "csharp.y"
{ R(); useOrCreateNameSpace(yyvsp[-2].attribute, yyvsp[0].text); ;
    break;}
case 306:
#line 785 "csharp.y"
{ R();	// Unstack.
										unuseNameSpace();		;
    break;}
case 307:
#line 789 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 308:
#line 790 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 309:
#line 799 "csharp.y"
{ R(); yyval.text = yyvsp[0].text; 	display(yyvsp[0].text);					;
    break;}
case 310:
#line 800 "csharp.y"
{ R(); yyval.text = concat(yyvsp[-1].text, yyvsp[0].text); 		;
    break;}
case 311:
#line 803 "csharp.y"
{ R(); yyval.text = concat(yyvsp[-1].text, "."); 			;
    break;}
case 312:
#line 804 "csharp.y"
{ R(); yyval.text = concat(yyvsp[-2].text, yyvsp[-1].text, "."); 	;
    break;}
case 313:
#line 808 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 314:
#line 811 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 315:
#line 812 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 316:
#line 815 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 317:
#line 816 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 318:
#line 819 "csharp.y"
{ R(); createAlias(yyvsp[-3].text, yyvsp[-1].text); 	;
    break;}
case 319:
#line 822 "csharp.y"
{ R(); addUsingNameSpace(yyvsp[-1].text); 		;
    break;}
case 320:
#line 825 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 321:
#line 826 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 322:
#line 829 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 323:
#line 830 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 324:
#line 833 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 325:
#line 834 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 326:
#line 835 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 327:
#line 836 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 328:
#line 837 "csharp.y"
{ R(); /* Nothing to do here */ ;
    break;}
case 329:
#line 848 "csharp.y"
{ R(); yyval.tmpValue = 0;				;
    break;}
case 330:
#line 849 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 	;
    break;}
case 331:
#line 852 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 				;
    break;}
case 332:
#line 853 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue | yyvsp[-1].tmpValue; 	;
    break;}
case 333:
#line 856 "csharp.y"
{ R(); yyval.tmpValue = ATT_ABSTRACT;	;
    break;}
case 334:
#line 857 "csharp.y"
{ R(); yyval.tmpValue = ATT_EXTERN;		;
    break;}
case 335:
#line 858 "csharp.y"
{ R(); yyval.tmpValue = ATT_INTERNAL;	;
    break;}
case 336:
#line 859 "csharp.y"
{ R(); yyval.tmpValue = ATT_NEW;		;
    break;}
case 337:
#line 860 "csharp.y"
{ R(); yyval.tmpValue = ATT_VIRTUAL;	;
    break;}
case 338:
#line 861 "csharp.y"
{ R(); yyval.tmpValue = ATT_PRIVATE;	;
    break;}
case 339:
#line 862 "csharp.y"
{ R(); yyval.tmpValue = ATT_PROTECTED;	;
    break;}
case 340:
#line 863 "csharp.y"
{ R(); yyval.tmpValue = ATT_PUBLIC;		;
    break;}
case 341:
#line 864 "csharp.y"
{ R(); yyval.tmpValue = ATT_READONLY;	;
    break;}
case 342:
#line 865 "csharp.y"
{ R(); yyval.tmpValue = ATT_SEALED;		;
    break;}
case 343:
#line 866 "csharp.y"
{ R(); yyval.tmpValue = ATT_STATIC;		;
    break;}
case 344:
#line 867 "csharp.y"
{ R(); yyval.tmpValue = ATT_UNSAFE;		;
    break;}
case 345:
#line 868 "csharp.y"
{ R(); yyval.tmpValue = ATT_VIRTUAL;	;
    break;}
case 346:
#line 869 "csharp.y"
{ R(); yyval.tmpValue = ATT_VOLATILE;	;
    break;}
case 347:
#line 874 "csharp.y"
{ R();
		// modify gCurrentNameSpace
		useOrCreateNameSpace(yyvsp[-3].attribute,yyvsp[0].text);
		gCurrentAC = CreateClass(	yyvsp[-3].attribute, 
						yyvsp[-2].tmpValue, 
						yyvsp[0].text);
						
	;
    break;}
case 348:
#line 881 "csharp.y"
{ R(); unuseNameSpace(); ;
    break;}
case 349:
#line 884 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 350:
#line 885 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 351:
#line 888 "csharp.y"
{ R(); gCurrentAC->setAncestor(yyvsp[0].type);	;
    break;}
case 352:
#line 889 "csharp.y"
{ R(); /* Do nothing */						;
    break;}
case 353:
#line 890 "csharp.y"
{ R(); gCurrentAC->setAncestor(yyvsp[-2].type);	;
    break;}
case 354:
#line 893 "csharp.y"
{ R(); gCurrentAC->addInterface(yyvsp[0].type);	;
    break;}
case 355:
#line 894 "csharp.y"
{ R(); gCurrentAC->addInterface(yyvsp[0].type);	;
    break;}
case 356:
#line 897 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 357:
#line 900 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 358:
#line 901 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 359:
#line 904 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 360:
#line 905 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 361:
#line 908 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 362:
#line 909 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 363:
#line 910 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 364:
#line 911 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 365:
#line 912 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 366:
#line 913 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 367:
#line 914 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 368:
#line 915 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 369:
#line 916 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 370:
#line 918 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 371:
#line 921 "csharp.y"
{ R(); gCurrentAC->addVariable(yyvsp[-5].attribute, yyvsp[-4].tmpValue, yyvsp[-2].type, yyvsp[-1].variable )->setConst();	;
    break;}
case 372:
#line 924 "csharp.y"
{ R(); gCurrentAC->addVariable(yyvsp[-4].attribute, yyvsp[-3].tmpValue, yyvsp[-2].type, yyvsp[-1].variable );				;
    break;}
case 373:
#line 927 "csharp.y"
{ R(); gCurrentMethod = gCurrentAC->addMethod(
																			yyvsp[-1].attribute,	// Attributes
																			yyvsp[-1].tmpValue,	// Modified REF/OUT
																			yyvsp[-1].text,		// Func Name
																			yyvsp[-1].variable,	// Link list of variable
																			yyvsp[0].statement,	// Code
																			yyvsp[-1].type			// Return value.
																		 );
																		;
    break;}
case 374:
#line 940 "csharp.y"
{ R(); 	yyval.attribute 	= yyvsp[-6].attribute; 
		yyval.tmpValue  	= yyvsp[-5].tmpValue;
		yyval.text			= yyvsp[-3].text;
		yyval.variable		= yyvsp[-1].variable;
		yyval.type			= yyvsp[-4].type;								;
    break;}
case 375:
#line 946 "csharp.y"
{ R(); 	yyval.attribute 	= yyvsp[-6].attribute; 
		yyval.tmpValue  	= yyvsp[-5].tmpValue;
		yyval.text			= yyvsp[-3].text;
		yyval.variable		= yyvsp[-1].variable;
		yyval.type			= TypeObject::getTypeObject(TYPE_VOID);	;
    break;}
case 376:
#line 953 "csharp.y"
{ R(); yyval.variable = NULL;								;
    break;}
case 377:
#line 954 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable;						;
    break;}
case 378:
#line 957 "csharp.y"
{ R(); yyval.type = yyvsp[0].type;								;
    break;}
case 379:
#line 958 "csharp.y"
{ R(); yyval.type = TypeObject::getTypeObject(TYPE_VOID);	;
    break;}
case 380:
#line 961 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;						;
    break;}
case 381:
#line 962 "csharp.y"
{ R(); yyval.statement = NULL;								;
    break;}
case 382:
#line 965 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable;							;
    break;}
case 383:
#line 966 "csharp.y"
{ R(); yyval.variable = yyvsp[-2].variable->addVariable(yyvsp[-1].variable);	;
    break;}
case 384:
#line 969 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable ;						;
    break;}
case 385:
#line 970 "csharp.y"
{ R(); yyval.variable = yyvsp[0].variable ;						;
    break;}
case 386:
#line 974 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[-1].text)
														->setAttribute(yyvsp[-4].attribute)
														->setModifier(yyvsp[-3].tmpValue)
														->setType(yyvsp[-2].type)
														->setValue(yyvsp[0].value);								;
    break;}
case 387:
#line 981 "csharp.y"
{ R();  yyval.value.type = TYPE_UNRESOLVED;				;
    break;}
case 388:
#line 982 "csharp.y"
{ R();  yyval.value = yyvsp[0].value;							;
    break;}
case 389:
#line 985 "csharp.y"
{ R();	yyval.tmpValue	= 0;								;
    break;}
case 390:
#line 986 "csharp.y"
{ R();	yyval.tmpValue = ATT_REF;							;
    break;}
case 391:
#line 987 "csharp.y"
{ R();	yyval.tmpValue	= ATT_OUT;							;
    break;}
case 392:
#line 991 "csharp.y"
{ R(); yyval.variable = CreateVarInstance(yyvsp[0].text)
														->setType(yyvsp[-1].type)
														->setAttribute(yyvsp[-3].attribute)
														->setIsEndLessParam();
													;
    break;}
case 393:
#line 1001 "csharp.y"
{ R(); gCurrentAC->addProperty(yyvsp[-8].attribute, yyvsp[-7].tmpValue, yyvsp[-6].type, yyvsp[-5].text, yyvsp[-2].accessor);	;
    break;}
case 394:
#line 1004 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(yyvsp[-1].accessor, yyvsp[0].accessor);	;
    break;}
case 395:
#line 1005 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(yyvsp[0].accessor, yyvsp[-1].accessor);	;
    break;}
case 396:
#line 1006 "csharp.y"
{ R(); yyval.accessor = CreateAccessor((Accessor*)NULL,(Accessor*)NULL); ;
    break;}
case 397:
#line 1009 "csharp.y"
{ R(); yyval.accessor = NULL;			;
    break;}
case 398:
#line 1010 "csharp.y"
{ R(); yyval.accessor = yyvsp[0].accessor;	;
    break;}
case 399:
#line 1013 "csharp.y"
{ R(); yyval.accessor = NULL;			;
    break;}
case 400:
#line 1014 "csharp.y"
{ R(); yyval.accessor = yyvsp[0].accessor;	;
    break;}
case 401:
#line 1020 "csharp.y"
{ R(); yyval.accessor  = CreateAccessor(yyvsp[-4].attribute, yyvsp[-1].statement);	;
    break;}
case 402:
#line 1026 "csharp.y"
{ R(); yyval.accessor  = CreateAccessor(yyvsp[-4].attribute, yyvsp[-1].statement);	;
    break;}
case 403:
#line 1029 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement; 	;
    break;}
case 404:
#line 1030 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 405:
#line 1033 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 406:
#line 1037 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 407:
#line 1040 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 408:
#line 1041 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 409:
#line 1047 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 410:
#line 1053 "csharp.y"
{ R();	compilerError(UNSUPPORTED,"event not supported");	;
    break;}
case 411:
#line 1056 "csharp.y"
{ R();	
		gCurrentAC->addProperty(yyvsp[-2].attribute, yyvsp[-1].tmpValue, yyvsp[0].indexer);
	;
    break;}
case 413:
#line 1064 "csharp.y"
{ R(); yyval.indexer = CreateIndexer(yyvsp[-4].type, yyvsp[-1].variable);	;
    break;}
case 414:
#line 1066 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"qualified this[] accessor property not supported."); ;
    break;}
case 415:
#line 1069 "csharp.y"
{ R(); yyval.text = concat(yyvsp[-1].text, "this"); ;
    break;}
case 416:
#line 1073 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 417:
#line 1076 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 418:
#line 1077 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 419:
#line 1080 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"Overloading operator not supported."); ;
    break;}
case 420:
#line 1081 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"Overloading operator not supported."); ;
    break;}
case 421:
#line 1084 "csharp.y"
{ R(); yyval.tmpValue = OP_PLUS;  ;
    break;}
case 422:
#line 1085 "csharp.y"
{ R(); yyval.tmpValue = OP_MINUS; ;
    break;}
case 423:
#line 1086 "csharp.y"
{ R(); yyval.tmpValue = OP_LNOT;  ;
    break;}
case 424:
#line 1087 "csharp.y"
{ R(); yyval.tmpValue = OP_NOT;   ;
    break;}
case 425:
#line 1088 "csharp.y"
{ R(); yyval.tmpValue = OP_PLUSPLUS;   ;
    break;}
case 426:
#line 1089 "csharp.y"
{ R(); yyval.tmpValue = OP_MINUSMINUS; ;
    break;}
case 427:
#line 1090 "csharp.y"
{ R(); yyval.tmpValue = OP_TRUE;  ;
    break;}
case 428:
#line 1091 "csharp.y"
{ R(); yyval.tmpValue = OP_FALSE; ;
    break;}
case 429:
#line 1092 "csharp.y"
{ R(); yyval.tmpValue = OP_MULT;  ;
    break;}
case 430:
#line 1093 "csharp.y"
{ R(); yyval.tmpValue = OP_DIV;   ;
    break;}
case 431:
#line 1094 "csharp.y"
{ R(); yyval.tmpValue = OP_MOD;   ;
    break;}
case 432:
#line 1095 "csharp.y"
{ R(); yyval.tmpValue = OP_AND;   ;
    break;}
case 433:
#line 1096 "csharp.y"
{ R(); yyval.tmpValue = OP_OR;    ;
    break;}
case 434:
#line 1097 "csharp.y"
{ R(); yyval.tmpValue = OP_XOR;   ;
    break;}
case 435:
#line 1098 "csharp.y"
{ R(); yyval.tmpValue = OP_LSHFT; ;
    break;}
case 436:
#line 1099 "csharp.y"
{ R(); yyval.tmpValue = OP_EQUAL; ;
    break;}
case 437:
#line 1100 "csharp.y"
{ R(); yyval.tmpValue = OP_DIFF;  ;
    break;}
case 438:
#line 1101 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue;  ;
    break;}
case 439:
#line 1102 "csharp.y"
{ R(); yyval.tmpValue = OP_LESS;  ;
    break;}
case 440:
#line 1103 "csharp.y"
{ R(); yyval.tmpValue = OP_MOREEQ;;
    break;}
case 441:
#line 1104 "csharp.y"
{ R(); yyval.tmpValue = OP_LESSEQ;;
    break;}
case 442:
#line 1106 "csharp.y"
{ yyval.tmpValue = OP_RSHFT;	;
    break;}
case 443:
#line 1107 "csharp.y"
{ yyval.tmpValue = OP_MORE;	;
    break;}
case 444:
#line 1111 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 445:
#line 1112 "csharp.y"
{ R(); /* TODO When support operator */	;
    break;}
case 446:
#line 1115 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addConstructor(
			yyvsp[-3].attribute,	// Attributes
			yyvsp[-2].tmpValue,	// Modifier
			yyvsp[-1].text,		// Func Name
			yyvsp[-1].variable,	// Link list of variable
			yyvsp[0].statement	// Code
		);
	;
    break;}
case 447:
#line 1126 "csharp.y"
{ R(); 	yyval.text		= yyvsp[-4].text; 
																					yyval.variable = yyvsp[-2].variable; 
																					yyval.expr		= yyvsp[0].expr; 
																					yyval.tmpValue	= yyvsp[0].tmpValue;
																				;
    break;}
case 448:
#line 1133 "csharp.y"
{ R(); yyval.expr	= NULL;		yyval.tmpValue = -1;			;
    break;}
case 449:
#line 1134 "csharp.y"
{ R(); yyval.expr	= yyvsp[0].expr;	yyval.tmpValue = yyvsp[0].tmpValue;	;
    break;}
case 450:
#line 1137 "csharp.y"
{ R(); yyval.expr			= yyvsp[-1].expr;	yyval.tmpValue = 0;	;
    break;}
case 451:
#line 1138 "csharp.y"
{ R(); yyval.expr			= yyvsp[-1].expr;	yyval.tmpValue = 1;	;
    break;}
case 452:
#line 1154 "csharp.y"
{ R();
		gCurrentMethod = gCurrentAC->addDestructor(
			yyvsp[-6].attribute,	// Attributes
			yyvsp[-6].tmpValue,	// Modifier
			yyvsp[-4].text,		// Func Name
			yyvsp[0].statement
		);
  ;
    break;}
case 453:
#line 1164 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 454:
#line 1165 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 455:
#line 1168 "csharp.y"
{ R(); yyval.statement = yyvsp[0].statement;	;
    break;}
case 456:
#line 1169 "csharp.y"
{ R(); yyval.statement = NULL;			;
    break;}
case 457:
#line 1174 "csharp.y"
{ R(); 	gCurrentAC = CreateStruct(	yyvsp[-3].attribute, 
																					yyvsp[-2].tmpValue, 
																					yyvsp[0].text
																				); 
													;
    break;}
case 458:
#line 1179 "csharp.y"
{ R(); unuseNameSpace(); ;
    break;}
case 459:
#line 1182 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 460:
#line 1183 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 461:
#line 1186 "csharp.y"
{ R(); /* Do nothing */ 	;
    break;}
case 462:
#line 1189 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 463:
#line 1192 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 464:
#line 1193 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 465:
#line 1196 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 466:
#line 1197 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 467:
#line 1200 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 468:
#line 1201 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 469:
#line 1202 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 470:
#line 1203 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 471:
#line 1204 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 472:
#line 1205 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 473:
#line 1206 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 474:
#line 1207 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 475:
#line 1209 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 476:
#line 1214 "csharp.y"
{ R(); yyval.expr = yyvsp[-1].expr; 	;
    break;}
case 477:
#line 1215 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr; 	;
    break;}
case 478:
#line 1218 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 479:
#line 1219 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 480:
#line 1222 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr;	;
    break;}
case 481:
#line 1223 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr->addExpression(yyvsp[-1].expr); ;
    break;}
case 482:
#line 1228 "csharp.y"
{ R(); 	gCurrentAC = CreateInterface(	yyvsp[-3].attribute, 
																								yyvsp[-2].tmpValue, 
																								yyvsp[0].text);
														;
    break;}
case 483:
#line 1233 "csharp.y"
{ R();  unuseNameSpace(); ;
    break;}
case 484:
#line 1236 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 485:
#line 1237 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 486:
#line 1240 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 487:
#line 1243 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 488:
#line 1246 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 489:
#line 1247 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 490:
#line 1250 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 491:
#line 1251 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 492:
#line 1254 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 493:
#line 1255 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 494:
#line 1256 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 495:
#line 1257 "csharp.y"
{ R(); /* Do nothing */	;
    break;}
case 496:
#line 1261 "csharp.y"
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
case 497:
#line 1271 "csharp.y"
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
case 498:
#line 1283 "csharp.y"
{ R(); yyval.tmpValue = 0; 			;
    break;}
case 499:
#line 1284 "csharp.y"
{ R(); yyval.tmpValue = ATTR_NEW; 	;
    break;}
case 500:
#line 1290 "csharp.y"
{ R(); gCurrentAC->addProperty(yyvsp[-8].attribute, yyvsp[-7].tmpValue, yyvsp[-6].type, yyvsp[-5].text, yyvsp[-2].accessor);	;
    break;}
case 501:
#line 1297 "csharp.y"
{ R(); gCurrentAC->addProperty(yyvsp[-11].attribute, yyvsp[-10].tmpValue, yyvsp[-9].type, yyvsp[-8].text, yyvsp[-5].accessor);	;
    break;}
case 502:
#line 1301 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-2].attribute,NULL), NULL); ;
    break;}
case 503:
#line 1302 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(NULL, CreateAccessor(yyvsp[-2].attribute,NULL)); ;
    break;}
case 504:
#line 1303 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-5].attribute,NULL), CreateAccessor(yyvsp[-2].attribute,NULL)); ;
    break;}
case 505:
#line 1304 "csharp.y"
{ R(); yyval.accessor = CreateAccessor(CreateAccessor(yyvsp[-2].attribute,NULL), CreateAccessor(yyvsp[-5].attribute,NULL)); ;
    break;}
case 506:
#line 1307 "csharp.y"
{ R(); compilerError(UNSUPPORTED,"event not supported"); ;
    break;}
case 507:
#line 1312 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 508:
#line 1313 "csharp.y"
{ R(); yyval.statement = NULL;	;
    break;}
case 509:
#line 1318 "csharp.y"
{ R();
		gCurrEnum = CreateEnum(yyvsp[-4].attribute, yyvsp[-3].tmpValue, yyvsp[-1].text, yyvsp[0].type);
  ;
    break;}
case 510:
#line 1320 "csharp.y"
{ R();
	// Do nothing.
  ;
    break;}
case 511:
#line 1325 "csharp.y"
{ R(); yyval.type = NULL;    ;
    break;}
case 512:
#line 1326 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; ;
    break;}
case 513:
#line 1329 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type; ;
    break;}
case 514:
#line 1332 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 515:
#line 1333 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 517:
#line 1337 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 518:
#line 1340 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 519:
#line 1341 "csharp.y"
{ R(); /* Do nothing */ ;
    break;}
case 520:
#line 1344 "csharp.y"
{ R(); gCurrEnum->addEntry(yyvsp[-1].attribute, yyvsp[0].text, NULL); ;
    break;}
case 521:
#line 1345 "csharp.y"
{ R(); gCurrEnum->addEntry(yyvsp[-3].attribute, yyvsp[-2].text, yyvsp[0].expr); ;
    break;}
case 522:
#line 1351 "csharp.y"
{ R(); /* TODO V Delegate */ ;
    break;}
case 523:
#line 1356 "csharp.y"
{ R(); yyval.attribute = yyvsp[0].attribute; ;
    break;}
case 524:
#line 1359 "csharp.y"
{ R(); yyval.attribute = CreateAttributeWithChild(yyvsp[0].attribute); 		;
    break;}
case 525:
#line 1360 "csharp.y"
{ R(); yyval.attribute = yyvsp[-1].attribute->addChildAttribute(yyvsp[0].attribute); ;
    break;}
case 526:
#line 1364 "csharp.y"
{ R();	yyval.attribute = yyvsp[-2].attribute->setSpecifier(yyvsp[-3].tmpValue); ;
    break;}
case 527:
#line 1366 "csharp.y"
{ R();	yyval.attribute = yyvsp[-3].attribute->setSpecifier(yyvsp[-4].tmpValue); ;
    break;}
case 528:
#line 1369 "csharp.y"
{ R(); yyval.tmpValue = 0; 					;
    break;}
case 529:
#line 1370 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[0].tmpValue; 		;
    break;}
case 530:
#line 1373 "csharp.y"
{ R(); yyval.tmpValue = yyvsp[-1].tmpValue; 		;
    break;}
case 531:
#line 1376 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_ASSEMBLY ; 	;
    break;}
case 532:
#line 1377 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_FIELD;		;
    break;}
case 533:
#line 1378 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_EVENT;		;
    break;}
case 534:
#line 1379 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_METHOD;		;
    break;}
case 535:
#line 1380 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_MODULE;		;
    break;}
case 536:
#line 1381 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_PARAM;		;
    break;}
case 537:
#line 1382 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_PROPERTY;	;
    break;}
case 538:
#line 1383 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_RETURN;		;
    break;}
case 539:
#line 1384 "csharp.y"
{ R(); yyval.tmpValue = ATTRB_TYPE;		;
    break;}
case 540:
#line 1387 "csharp.y"
{ R(); yyval.attribute = CreateAttribute(yyvsp[0].type, yyvsp[0].expr);				;
    break;}
case 541:
#line 1388 "csharp.y"
{ R(); yyval.attribute = yyvsp[-2].attribute->addAttribute(yyvsp[0].type, yyvsp[0].expr); ;
    break;}
case 542:
#line 1391 "csharp.y"
{ R(); yyval.type = yyvsp[-1].type; yyval.expr= yyvsp[0].expr; ;
    break;}
case 543:
#line 1394 "csharp.y"
{ R(); yyval.expr = NULL; 		;
    break;}
case 544:
#line 1395 "csharp.y"
{ R(); yyval.expr = yyvsp[0].expr ; 	;
    break;}
case 545:
#line 1398 "csharp.y"
{ R(); yyval.type = yyvsp[0].type; 	;
    break;}
case 546:
#line 1401 "csharp.y"
{ R(); yyval.expr = yyvsp[-2].expr ; 	;
    break;}
case 547:
#line 1408 "csharp.y"
{ R(); lex_enter_attrib(); 	/*Do nothing*/ ;
    break;}
case 548:
#line 1411 "csharp.y"
{ R(); lex_exit_attrib(); 	/*Do nothing*/ ;
    break;}
case 549:
#line 1414 "csharp.y"
{ R(); lex_enter_accessor();	/*Do nothing*/ ;
    break;}
case 550:
#line 1417 "csharp.y"
{ R(); lex_exit_accessor();	/*Do nothing*/ ;
    break;}
case 551:
#line 1420 "csharp.y"
{ R(); lex_enter_getset();	/*Do nothing*/ ;
    break;}
case 552:
#line 1423 "csharp.y"
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
#line 1427 "csharp.y"


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
