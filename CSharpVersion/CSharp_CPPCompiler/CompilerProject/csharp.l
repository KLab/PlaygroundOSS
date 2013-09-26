/*** 
 *** C# parser/scanner
 *** Copyright 2002 James Power, NUI Maynooth, Ireland <james.power@may.ie>
 *** This version: 19 Feb 2002
 ***
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the <organization> nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY <copyright holder> ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ***/
%{
#include <string.h>
// #include "csharp.tab.h"
#include "y.tab.h"

  void lexical_error(const char *);
  static int token_for(const char *);
  static int is_allowed_char(const char );
  static SValue getValueInt(const char* text);
  static SValue getValueReal(const char* text);
  static SValue getValueChar(const char* text);
  static SValue getValueString(const char* text);
  static SValue getValueNull();
  static int getRank(const char* text);
%}

%option noyywrap
%option yylineno
%option stack

single_line_comment    "//".*

white_space            [ \t\n\r]

preprocessor           ^[ \t]*#.*

dec_digit              [0-9]
hex_digit              [0-9A-Fa-f]
int_suffix             [UuLl]|[Uu][Ll]|[Ll][Uu]
dec_literal            {dec_digit}+{int_suffix}?
hex_literal            0[xX]{hex_digit}+{int_suffix}?
integer_literal        {dec_literal}|{hex_literal}

real_suffix            [FfDdMm]
sign                   [+\-]
exponent_part          [eE]{sign}?{dec_digit}+
whole_real1            {dec_digit}+{exponent_part}{real_suffix}?
whole_real2            {dec_digit}+{real_suffix}
part_real              {dec_digit}*\.{dec_digit}+{exponent_part}?{real_suffix}?
real_literal           {whole_real1}|{whole_real2}|{part_real}

single_char            [^\\\']
simple_esc_seq         \\[\'\"\\0abfnrtv]
uni_esc_seq1           \\u{hex_digit}{4}
uni_esc_seq2           \\U{hex_digit}{8}
uni_esc_seq            {uni_esc_seq1}|{uni_esc_seq2}
hex_esc_seq            \\x{hex_digit}{1,4}
character              {single_char}|{simple_esc_seq}|{hex_esc_seq}|{uni_esc_seq1}
character_literal      \'{character}\'


single_string_char     [^\\\"]
reg_string_char        {single_string_char}|{simple_esc_seq}|{hex_esc_seq}|{uni_esc_seq}
regular_string         \"{reg_string_char}*\"
single_verbatim_char   [^\"]
quote_esc_seq          \"\"
verb_string_char       {single_verbatim_char}|{quote_esc_seq}
verbatim_string        @\"{verb_string_char}*\"
string_literal         {regular_string}|{verbatim_string}


letter_char            [A-Za-z]
ident_char             {dec_digit}|{letter_char}|"_"|"@"
identifier             ({letter_char}|"_"){ident_char}*
at_identifier          \@{identifier}


rank_specifier         "["{white_space}*(","{white_space}*)*"]"


%x IN_COMMENT IN_GENERIC

%s IN_ATTRIB IN_ACCESSOR IN_GETSET 

%%

{preprocessor}        { ; /* ignore */ }
{white_space}         { ; /* ignore */ }
<IN_GENERIC>{preprocessor}        { ; /* ignore */ }
<IN_GENERIC>{white_space}         { ; /* ignore */ }

"/*"                  { yy_push_state(IN_COMMENT); }
<IN_COMMENT>.         { ; /* ignore */ }
<IN_COMMENT>\n        { ; /* ignore */ }
<IN_COMMENT>"*/"      { yy_pop_state();}

{single_line_comment} { ; /* ignore */ }
<IN_GENERIC>{single_line_comment} { ; /* ignore */ }

                      /* yytext yylval.xxx */
{integer_literal}     { yylval.value = getValueInt(yytext);		return INTEGER_LITERAL; 	}
<IN_GENERIC>{integer_literal}     { yylval.value = getValueInt(yytext);		return INTEGER_LITERAL; 	}
{real_literal}        { yylval.value = getValueReal(yytext);	return REAL_LITERAL; 		}
<IN_GENERIC>{real_literal}        { yylval.value = getValueReal(yytext);	return REAL_LITERAL; 		}
{character_literal}   { yylval.value = getValueChar(yytext);	return CHARACTER_LITERAL; 	}
<IN_GENERIC>{character_literal}   { yylval.value = getValueChar(yytext);	return CHARACTER_LITERAL; 	}
{string_literal}      { yylval.value = getValueString(yytext);	return STRING_LITERAL; 		}
<IN_GENERIC>{string_literal}      { yylval.value = getValueString(yytext);	return STRING_LITERAL; 		}

","   { return COMMA; }
<IN_GENERIC>","   { return COMMA; }
"["   { return LEFT_BRACKET; }
<IN_GENERIC>"["   { return LEFT_BRACKET; }
"]"   { return RIGHT_BRACKET; }
<IN_GENERIC>"]"   { return RIGHT_BRACKET; }

{rank_specifier}     { yylval.tmpValue = getRank(yytext); /*printf("Rank : %s\n",yytext);*/ return RANK_SPECIFIER; }
<IN_GENERIC>{rank_specifier}     { yylval.tmpValue = getRank(yytext); /*printf("Rank : %s\n",yytext);*/ return RANK_SPECIFIER; }

                      /*** Multi-Character Operators ***/
"+="  { return PLUSEQ;	}
"-="  { return MINUSEQ;	}
"*="  { return STAREQ;	}
"/="  { return DIVEQ;	}
"%="  { return MODEQ;	}
"^="  { return XOREQ;	}
"&="  { return ANDEQ;	}
"|="  { return OREQ;	}
"<<"  { return LTLT;	}
<INITIAL>">>"  { return GTGT;	}	/* Trick for >> handling in generic */
">>=" { return GTGTEQ;	}
"<<=" { return LTLTEQ;	}
"=="  { return EQEQ;	}
"!="  { return NOTEQ;	}
"<="  { return LEQ;		}
">="  { return GEQ;		}
"&&"  { return ANDAND;	}
"||"  { return OROR;	}
"++"  { return PLUSPLUS;	}
"--"  { return MINUSMINUS;	}
"->"  { return ARROW;	}
">"	  { return GT;	  }
<IN_GENERIC>">"	  { return GT;	  }
"<"	  { return LT;	  }
<IN_GENERIC>"<"	  { return LT;	  }
"$<"	{ return GEN_LT; }
"$>"	{ return GEN_GT; }
<IN_GENERIC>"$<" { return GEN_LT; }
<IN_GENERIC>"$>" { return GEN_GT; }

                      /*** Those context-sensitive "keywords" ***/

<IN_ATTRIB>"assembly"    { return ASSEMBLY; }
<IN_ATTRIB>"field"       { return FIELD; }
<IN_ATTRIB>"method"      { return METHOD; }
<IN_ATTRIB>"module"      { return MODULE; }
<IN_ATTRIB>"param"       { return PARAM; }
<IN_ATTRIB>"property"    { return PROPERTY; }
<IN_ATTRIB>"type"        { return TYPE; }

<IN_ACCESSOR>"add"       { return ADD; }
<IN_ACCESSOR>"remove"    { return REMOVE; }

<IN_GETSET>"get"         { return GET; }
<IN_GETSET>"set"         { return SET; }

{identifier}          { return token_for(yytext); }
<IN_GENERIC>{identifier}          { return token_for(yytext); }

{at_identifier}       { yylval.text = concat(yytext); return IDENTIFIER; }


.     { 
        if (is_allowed_char(yytext[0])) return yytext[0];
        else lexical_error("invalid token"); 
      }
%%


static struct name_value {
  char *name;
  int value;
} name_value;
static struct name_value keywords [] = { 
 /* This list must remain sorted!!! */
    {"abstract", ABSTRACT},
    {"as", AS},
    {"base", BASE},
    {"bool", BOOL},
    {"break", BREAK},
    {"byte", BYTE},
    {"case", CASE},
    {"catch", CATCH},
    {"char", CHAR},
    {"checked", CHECKED},
    {"class", CLASS},
    {"const", CONST},
    {"continue", CONTINUE},
    {"decimal", DECIMAL},
    {"default", DEFAULT},
    {"delegate", DELEGATE},
    {"do", DO},
    {"double", DOUBLE},
    {"else", ELSE},
    {"enum", ENUM},
    {"event", EVENT},
    {"explicit", EXPLICIT},
    {"extern", EXTERN},
    {"false", FALSE},
    {"finally", FINALLY},
    {"fixed", FIXED},
    {"float", FLOAT},
    {"for", FOR},
    {"foreach", FOREACH},
    {"goto", GOTO},
    {"if", IF},
    {"implicit", IMPLICIT},
    {"in", IN},
    {"int", INT},
    {"interface", INTERFACE},
    {"internal", INTERNAL},
    {"is", IS},
    {"lock", LOCK},
    {"long", LONG},
    {"namespace", NAMESPACE},
    {"new", NEW},
    {"null", NULL_LITERAL},
    {"object", OBJECT},
    {"operator", OPERATOR},
    {"out", OUT},
    {"override", OVERRIDE},
    {"params", PARAMS},
	{"partial", PARTIAL},
    {"private", PRIVATE},
    {"protected", PROTECTED},
    {"public", PUBLIC},
    {"readonly", READONLY},
    {"ref", REF},
    {"return", RETURN},
    {"sbyte", SBYTE},
    {"sealed", SEALED},
    {"short", SHORT},
    {"sizeof", SIZEOF},
    {"stackalloc", STACKALLOC},
    {"static", STATIC},
    {"string", STRING},
    {"struct", STRUCT},
    {"switch", SWITCH},
    {"this", THIS},
    {"throw", THROW},
    {"true", TRUE},
    {"try", TRY},
    {"typeof", TYPEOF},
    {"uint", UINT},
    {"ulong", ULONG},
    {"unchecked", UNCHECKED},
    {"unsafe", UNSAFE},
    {"ushort", USHORT},
    {"using", USING},
    {"virtual", VIRTUAL},
    {"void", VOID},
    {"volatile", VOLATILE},
    {"while", WHILE}
/* This list must remain sorted!!! */
  };    


int checkCppWord(const char* id) {
	switch (id[0]) {
	case 'a':
		if (id[1] == 'l') {
			if (strcmp("alignas", id) ==0) { return 0; }
			if (strcmp("alignof", id) == 0) { return 0; }
		} else
		if (id[1] == 'n') {
			if (strcmp("and", id) ==0) { return 0; }
			if (strcmp("and_eq", id) == 0) { return 0; }
		} else
		{
			if (strcmp("asm", id) ==0) { return 0; }
			if (strcmp("auto", id) == 0) { return 0; }
		}
		break;
	case 'b':
		if (id[1] == 'i') {
			if (strcmp("bitand", id) ==0) { return 0; }
			if (strcmp("bitor", id) == 0) { return 0; }
		}
		break;
		// "bool"
		// "break",
	case 'c':
		// "case",
		// "catch",
		// "char",

		if (id[1] == 'h') {
			if (strcmp("char16_t", id) ==0) { return 0; }
			if (strcmp("char32_t", id) ==0) { return 0; }
		} else {
			if (strcmp("compl", id) ==0) { return 0; }
			if (strcmp("contexpr", id) ==0) { return 0; }
			if (strcmp("const_cast", id) ==0) { return 0; }
		}
		
		// "class",
		// "compl",
		// "const",
		// "constexpr",
		// "const_cast",
		// "continue",
		break;
	case 'd':
		if (id[1] == 'e') {
			if (strcmp("decltype", id) ==0) { return 0; }
			if (strcmp("delete",   id) ==0) { return 0; }
			if (strcmp("deprecated",   id) ==0) { return 0; }
		} else if (id[1] == 'y') {
			if (strcmp("dynamic_cast",   id) ==0) { return 0; }
		} else if (id[1] == 'l') {
			if (strcmp("dllimport",   id) ==0) { return 0; }
			if (strcmp("dllexport",   id) ==0) { return 0; }
		}
		// "decltype",
		// "default",
		// "delete",
		// "do",
		// "double",
		// "dynamic_cast",
		break;
	case 'e':
		// "else",
		// "enum",
		// "explicit",
		if (id[1] == 'x') {
			if (strcmp("export",   id) ==0) { return 0; }
		} else if (id[1] == 'a') {
			if (strcmp("each",   id) ==0) { return 0; }
		}
		// "export",
		// "extern",
		break;
	case 'f':
		// "false",
		// "final",
		if (id[1]=='i') {
			if (strcmp("final",   id) ==0) { return 0; }
		} else
		// "float",
		// "for",
		if (id[1]=='r') {
			if (strcmp("friend",   id) ==0) { return 0; }
			if (strcmp("friend_as",   id) ==0) { return 0; }
		}
		//"friend",
		break;
	case 'g':
		// "goto",
		if (id[1]=='o') {
			if (strcmp("goto",   id) ==0) { return 0; }
		} else if (id[1] == 'c') {
			if (strcmp("gcnew",   id) ==0) { return 0; }
		} else if (id[1] == 'e') {
			if (strcmp("generic",   id) ==0) { return 0; }
		}
		break;
	case 'i':
		// "if",
		//"inline",
		if (id[1]=='n') {
			if (strcmp("inline",   id) ==0) { return 0; }
			if (strcmp("initonly",   id) ==0) { return 0; }
			if (strcmp("interior_ptr",   id) ==0) { return 0; }
		}
		// "int",
		break;
	case 'l':
		// "long",
		if (id[1]=='i') {
			if (strcmp("literal",   id) ==0) { return 0; }
		}
		break;
	case 'm':
		// "mutable",
		if (id[1]=='u') {
			if (strcmp("mutable",   id) ==0) { return 0; }
		}
		break;
	case 'n':
//		"namespace",
//		"new",
		if (id[1]=='o') {
			int len = strlen(id);
			if (len >= 7) {
				if (strcmp("noinline",   id) ==0) { return 0; }
				if (strcmp("noreturn",   id) ==0) { return 0; }
				if (strcmp("novtable",   id) ==0) { return 0; }
				if (strcmp("nothrow",   id) ==0) { return 0; }
				if (strcmp("noexcept",   id) ==0) { return 0; }
			} else {
				if (strcmp("not",   id) ==0) { return 0; }
				if (strcmp("not_eq",   id) ==0) { return 0; }
			}
		} else if (id[1]=='u') {
			if (strcmp("nullptr",   id) ==0) { return 0; }
		} else if (id[1]=='a') {
			if (strcmp("naked",   id) ==0) { return 0; }
		}
		//"noexcept",
		//"not",
		//"not_eq",
		//"nullptr",
		break;
	case 'o':
		if (id[1]=='p') {
			if (strcmp("operator",   id) ==0) { return 0; }
		} else
		if (id[1]=='r') {
			if (strcmp("or", id) ==0) { return 0; }
			if (strcmp("or_eq", id) ==0) { return 0; }
		} else {
			if (strcmp("override", id) ==0) { return 0; }
		}
		break;
	case 'p':
		// "private",
		// "protected",
		// "public",
		if (strcmp("property", id) ==0) { return 0; }
		break;
	case 'r':
		if (id[1]=='e') {
			if (strcmp("register", id) ==0) { return 0; }
			if (strcmp("reinterpret_cast", id) ==0) { return 0; }
		}
		// "return"
		break;
	case 's':
//		"short",
//		"signed",
		if (id[1]=='i') {
			if (strcmp("signed", id) ==0) { return 0; }
		} else
//		"sizeof",
//		"static",
		if (id[1]=='t') {
			if (strcmp("static_assert", id) ==0) { return 0; }
			if (strcmp("static_cast", id) ==0) { return 0; }
		} else
		if (id[1]=='a') {
			if (strcmp("safecast", id) ==0) { return 0; }
		} else {
			if (strcmp("selectany", id) ==0) { return 0; }
		}
//		"struct",
//		"switch",
		break;
	case 't':
//		static const char* t_keywords [] = { 
		if (id[1]=='e') {
			if (strcmp("template", id) ==0) { return 0; }
		} else
//		"this",
		if (id[1]=='h') {
			if (strcmp("thread_local", id) ==0) { return 0; }
		} else
//		"throw",
//		"true",
//		"try",
		if (id[1]=='y') {
			if (strcmp("typedef", id) ==0) { return 0; }
			if (strcmp("typeid", id) ==0) { return 0; }
			if (strcmp("typename", id) ==0) { return 0; }
		};
		break;
	case 'u':
		if (id[1]=='n') {
			if (strcmp("union", id) ==0) { return 0; }
			if (strcmp("unsigned", id) ==0) { return 0; }
		} else {
			if (strcmp("uuid", id) ==0) { return 0; }
		}
		// "using"
		break;
	case 'v':
//		"virtual",
//		"void",
//      "volatile"
		break;
	case 'w':
		if (id[1]=='c') {
			if (strcmp("wchar_t", id) ==0) { return 0; }
		}
//		"while",
		break;
	case 'x':
		if (id[1]=='o') {
			if (strcmp("xor", id) ==0) { return 0; }
			if (strcmp("xor_eq", id) ==0) { return 0; }
		}
		break;
	case '_':
		if (id[1]=='_') {
			if (strcmp("__abstract", id) == 0) { return 0; }
			if (strcmp("__alignof", id) == 0) { return 0; }
			if (strcmp("__asm", id) == 0) { return 0; }
			if (strcmp("__assume", id) == 0) { return 0; }
			if (strcmp("__based", id) == 0) { return 0; }
			if (strcmp("__box", id) == 0) { return 0; }
			if (strcmp("__cdecl", id) == 0) { return 0; }
			if (strcmp("__declspec", id) == 0) { return 0; }
			if (strcmp("__delegate", id) == 0) { return 0; }
			if (strcmp("__event", id) == 0) { return 0; }
			if (strcmp("__except", id) == 0) { return 0; }
			if (strcmp("__fastcall", id) == 0) { return 0; }
			if (strcmp("__finally", id) == 0) { return 0; }
			if (strcmp("__forceinline", id) == 0) { return 0; }
			if (strcmp("__gc", id) == 0) { return 0; }
			if (strcmp("__hook", id) == 0) { return 0; }
			if (strcmp("__identifier", id) == 0) { return 0; }
			if (strcmp("__if_exists", id) == 0) { return 0; }
			if (strcmp("__if_not_exists", id) == 0) { return 0; }
			if (strcmp("__inline", id) == 0) { return 0; }
			if (strcmp("__int8", id) == 0) { return 0; }
			if (strcmp("__int16", id) == 0) { return 0; }
			if (strcmp("__int32", id) == 0) { return 0; }
			if (strcmp("__int64", id) == 0) { return 0; }
			if (strcmp("__interface", id) == 0) { return 0; }
			if (strcmp("__leave", id) == 0) { return 0; }
			if (strcmp("__m64", id) == 0) { return 0; }
			if (strcmp("__m128", id) == 0) { return 0; }
			if (strcmp("__m128d", id) == 0) { return 0; }
			if (strcmp("__m128i", id) == 0) { return 0; }
			if (strcmp("__multiple_inheritance", id) == 0) { return 0; }
			if (strcmp("__nogc", id) == 0) { return 0; }
			if (strcmp("__noop", id) == 0) { return 0; }
			if (strcmp("__pin", id) == 0) { return 0; }
			if (strcmp("__property", id) == 0) { return 0; }
			if (strcmp("__raise", id) == 0) { return 0; }
			if (strcmp("__sealed", id) == 0) { return 0; }
			if (strcmp("__single_inheritance", id) == 0) { return 0; }
			if (strcmp("__stdcall", id) == 0) { return 0; }
			if (strcmp("__super", id) == 0) { return 0; }
			if (strcmp("__try", id) == 0) { return 0; }
			if (strcmp("__try_cast", id) == 0) { return 0; }
			if (strcmp("__unaligned", id) == 0) { return 0; }
			if (strcmp("__unhook", id) == 0) { return 0; }
			if (strcmp("__uuidof", id) == 0) { return 0; }
			if (strcmp("__value", id) == 0) { return 0; }
			if (strcmp("__virtual_inheritance", id) == 0) { return 0; }
			if (strcmp("__w64", id) == 0) { return 0; }
			if (strcmp("__wchar_t", id) == 0) { return 0; }
		}
	}

	return 1;
};

/* Conduct a binary search for lexeme in the keywords array
 * between indices start (inclusive) and finish (exclusive)
 */
static int bin_search(const char *lexeme, int start, int finish)
{
  if (start >= finish) {/* Not found */
      if (checkCppWord(lexeme) == 0) {
		  compilerError(ERR_USER,"C++ keyword used as identifier");
	  }
	  yylval.text = concat(lexeme); 
	  return IDENTIFIER;
  } else {
    int mid = (start+finish)/2;
    int cmp = strcmp(lexeme,keywords[mid].name);
    if (cmp == 0) {
	  if (keywords[mid].value == OBJECT || keywords[mid].value == STRING) {
		yylval.text = (keywords[mid].value == OBJECT) ? "System.Object" : "System.String";
		return IDENTIFIER;
	  }
      return keywords[mid].value;
    } else if (cmp < 0) {
      return bin_search(lexeme,start,mid);
    } else {
      return bin_search(lexeme,mid+1,finish);
	}
  }
}

static int token_for(const char *lexeme)
{

  static int num_keywords = sizeof(keywords) / sizeof(name_value);
  int token = bin_search(lexeme,0,num_keywords);
  if (token == -1) {
    token = IDENTIFIER;
	/*printf("lexeme:%s\n",lexeme);*/
	yylval.text = concat(lexeme); 
  } else if (token == NULL_LITERAL) {
	yylval.value = getValueNull();
  }
  return token;
}

static int is_allowed_char(const char c)
{
  static char allowed [] = {
    '.', ';', ':',
    '(', ')', '{', '}', '<', '>',
    '+', '-', '*', '/', '%', '&', '|', '!', '~', '^',
    '=', '?',
  };
  static int num_allowed = sizeof(allowed) / sizeof(char);
  int i;
  for (i=0; i<num_allowed; i++) {
    if (allowed[i]==c) 
      return 1;
  }
  return 0;
}

static SValue getValueInt(const char* text) {
	SValue v;
	int len = strlen(text);
	int mode = 0;
	if ((text[len-1]=='U') || (text[len-1]=='u')) {	mode |= 1;	}
	if ((text[len-1]=='L') || (text[len-1]=='l')) {	mode |= 2;	}

	if (mode) {
		if ((text[len-2]=='U') || (text[len-2]=='u')) {	mode |= 1;	}
		if ((text[len-2]=='L') || (text[len-2]=='l')) {	mode |= 2;	}
	}
		
	int hexaMode = 10;
	const char* p = text;
	if ((text[0] == '0') && (text[1] == 'x' || text[1]=='X')) {
		hexaMode = 16;
		p += 2; // Skip 0x
	}
	
	// We have a valid string anyway.
	long out = 0;
	do {
		int v = *p++;
		if (v >= '0' && v <= '9') {
			v -= '0';
		} else
		if (v >= 'A' && v <= 'F') {
			v -= 'A' - 10;
		} else
		if (v >= 'a' && v <= 'f') {
			v -= 'a' - 10;
		} else {
			// Reach end : char 0, U, L etc...
			break;
		}
		
		out = (out * hexaMode) + v;
	} while(1);
	
	switch (mode) {
	case 0:
		v.type	= TYPE_INT;
		v.v.i	= (int)out;
		break;
	case 1:
		v.type	= TYPE_UINT;
		v.v.ui	= (unsigned int)out;
		break;
	case 2:
		v.type	= TYPE_LONG;
		v.v.l	= (long)out;
		break;
	default:
	case 3:
		v.type	= TYPE_ULONG;
		v.v.ul	= (unsigned long)out;
		break;
	}
	return v;
}

static SValue getValueReal(const char* text) {
	SValue v;
	double d;
	char buff[70];	// Tmp buffer
	int strL = strlen(text);
	char c = text[strL-1];
	const char* ptrRead = text;
	int isFloat = 0;
	if ((c == 'F') || (c == 'f') || (c == 'D') || (c == 'd') || (c == 'M') || (c == 'm')) {
		if ((c == 'F') || (c == 'f')) {
			isFloat = 1;
		}
		memcpy(buff,text,strL-1);
		buff[strL] = 0;
		ptrRead = buff;
	}
	sscanf(ptrRead, "%lf", &d);
	if (!isFloat) {
		v.type	= TYPE_DOUBLE;
		v.v.d	= d;
	} else {
		v.type	= TYPE_FLOAT;
		v.v.f	= (float)d;
	}
	return v;
}

static SValue getValueChar(const char* text) {
	SValue v;
	v.type	= TYPE_CHAR;
	const char* t = &text[1];
	u16 ch = 0;
	if (*t == '\\') {
		switch (t[1]) {
		case 'U':
			v.type = TYPE_STRING;
			// TODO : reencode to utf8 !
			compilerError(ERR_NOT_SUPPORTED_YET, " Support complex unicode.");
			break;
		case 'u':
		case 'x':
		{
			int hexaMode = 16;
			// We have a valid string anyway.
			int out = 0;
			const char* p = &t[2];
			do {
				int v = *p++;
				if (v >= '0' && v <= '9') {
					v -= '0';
				} else
				if (v >= 'A' && v <= 'F') {
					v -= 'A';
				} else
				if (v >= 'a' && v <= 'f') {
					v -= 'a';
				} else {
					// Reach end : char 0, ' etc...
					break;
				}
				
				out = (out * hexaMode) + v;
			} while(1);
			// Read 4 hex char
			ch = out;
		}	break;
		case 'a':	ch = 0x0007;	break;
		case 'b':	ch = 0x0008;	break;
		case 'f':	ch = 0x000C;	break;
		case 'n':	ch = 0x000A;	break;
		case 'r':	ch = 0x000D;	break;
		case 't':	ch = 0x0009;	break;
		case 'v':	ch = 0x000B;	break;
		case '0':	ch = 0;			break;
		case '\'':	ch = 0x0027;	break;
		case '\"':	ch = 0x0022;	break;
		case '\\':	ch = 0x005C;	break;
		default:
			compilerError(ERR_USER, "Invalid Char sequence /%c .", t[1]);
		}
	} else {
		if (*t >= 128) {
			compilerError(ERR_NOT_SUPPORTED_YET, " Support UTF8 -> Unicode.");
		} else {
			ch = *t;
		}
	}
	v.v.i = ch;
	return v;
}

static SValue getValueString(const char* text) {
	SValue v;
	v.type	= TYPE_STRING;
	char* pchar = strdup(&text[1]);		// For now UTF8 as is., skip '"'
	int strl = strlen(pchar);
	if (strl) {
		pchar[strl-1] = 0; // Patch last '"'
	}
	v.v.str	= pchar;
	return v;
}

static int getRank(const char* text) {
	int res = 1;
	while (*text != 0) {
		if (*text == ',') {
			res++;
		}
		text++;
	}
	return res;
}

static SValue getValueNull() {
	SValue v;
	v.type	= TYPE_NULL;
	return v;
}


void lexical_error(const char *msg)
{
  fprintf(stderr,"%d:lexical error (%s) [%s]\n",yylineno,msg,yytext);
}


/*** Switch on/off context-sensitive "keywords" ***/
/* I don't like it any more than you do.  */
static int genCount = 0;
void lex_in_generic(void) {
	if (genCount == 0) {
		yy_push_state(IN_GENERIC);
	}
	genCount++;
}
void lex_out_generic(void) {
	genCount--;
	if (genCount == 0) {
		yy_pop_state();
	}
}
void lex_enter_attrib(void)
{
  yy_push_state(IN_ATTRIB);
}
void lex_exit_attrib(void)
{
  yy_pop_state();
}
void lex_enter_accessor(void)
{
  yy_push_state(IN_ACCESSOR);
}
void lex_exit_accessor(void)
{
  yy_pop_state();
}
void lex_enter_getset(void)
{
  yy_push_state(IN_GETSET);
}
void lex_exit_getset(void)
{
  yy_pop_state();
}
