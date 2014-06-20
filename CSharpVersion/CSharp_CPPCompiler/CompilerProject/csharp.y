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

/* Based on Appendix C of the C# Language Specification,
 *  version 0.28 of 5/7/2001
 */
%{
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
%}

%right THEN ELSE


/* Special tokens to help disambiguate rank_specifiers */
%token RANK_SPECIFIER

/* C.1.4 Tokens */
%token IDENTIFIER 
%token INTEGER_LITERAL REAL_LITERAL CHARACTER_LITERAL STRING_LITERAL


/* C.1.7 KEYWORDS */ 
%token  ABSTRACT AS BASE BOOL BREAK
%token  BYTE CASE CATCH CHAR CHECKED
%token  CLASS CONST CONTINUE DECIMAL DEFAULT
%token  DELEGATE DO DOUBLE ENUM
%token  EVENT EXPLICIT EXTERN FALSE FINALLY
%token  FIXED FLOAT FOR FOREACH GOTO
%token  IF IMPLICIT IN INT INTERFACE
%token  INTERNAL IS LOCK LONG NAMESPACE
%token  NEW NULL_LITERAL OPERATOR OUT
%token  OVERRIDE PARAMS PARTIAL PRIVATE PROTECTED PUBLIC
%token  READONLY REF RETURN SBYTE SEALED
%token  SHORT SIZEOF STACKALLOC STATIC
%token  STRUCT SWITCH THIS THROW TRUE
%token  TRY TYPEOF UINT ULONG UNCHECKED
%token  UNSAFE USHORT USING VIRTUAL VOID
%token  VOLATILE WHILE
%token	STRING OBJECT
%token  GEN_LT GEN_GT

/* The ones that seem to be context sensitive */
/* Attribute Targets */
%token ASSEMBLY FIELD METHOD MODULE PARAM PROPERTY TYPE
/* Accessor types */
%token GET SET 
/* Event accessor declarations */
%token ADD REMOVE

/*** PUNCTUATION AND SINGLE CHARACTER OPERATORS ***/
%token COMMA
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token GT GTGT LT

/*** MULTI-CHARACTER OPERATORS ***/
%token PLUSEQ MINUSEQ STAREQ DIVEQ MODEQ
%token XOREQ  ANDEQ   OREQ LTLT GTGTEQ LTLTEQ EQEQ NOTEQ
%token LEQ GEQ ANDAND OROR PLUSPLUS MINUSMINUS ARROW

%start compilation_unit  /* I think */

%%

/*
 *	Literal Section Done
 */
 
/***** C.1.8 Literals *****/
literal
  : boolean_literal				{ R(); $$.value = $1.value; }
  | INTEGER_LITERAL				{ R(); $$.value = $1.value; }
  | REAL_LITERAL				{ R(); $$.value = $1.value; }
  | CHARACTER_LITERAL			{ R(); $$.value = $1.value; }
  | STRING_LITERAL				{ R(); $$.value = registerString($1.value);}
  | NULL_LITERAL				{ R(); $$.value = $1.value; }
  ;
boolean_literal
  : TRUE						{ R(); $$.value.type = TYPE_BOOL; $$.value.v.i = 1; }
  | FALSE						{ R(); $$.value.type = TYPE_BOOL; $$.value.v.i = 0; }
  ;
/********** C.2 Syntactic grammar **********/

/*
 *	Type Section Done
 */

/***** C.2.1 Basic concepts *****/
namespace_name
  : qualified_identifier				{ R(); $$.text = $1.text; }
  ;
type_name
  : qualified_identifier_opt_generic {

							 R(); $$.type = TypeObject::getTypeObject($1.text, TYPE_UNRESOLVED)->setGeneric(GetGenericType());
							 PopGenericType();
						 }
  ;
opt_generic
  : /* Nothing */								{ R(); }
  | GEN_LT	{ 
			lex_in_generic(); 
		} genericlist GEN_GT {
			lex_out_generic(); R(); 
		}
  ;

qualified_identifier_opt_generic
  : qualified_identifier { PushGenericType(GetGenericType()); } opt_generic	{ R(); }
  ;
  
genericlist
  : type								{ R(); addGenericType($1.type); 	}
  | type COMMA { R(); addGenericType($1.type); } genericlist
  ;
/*
genericlist
  : type  continuity					{ R(); addGenericType($1.type); }
  ;
continuity 
  : 									{ R(); }
  | COMMA genericlist					{ R(); addGenericType($2.type); }
  ;
*/
/***** C.2.2 Types *****/
type
  : non_array_type				{ R(); $$.type = $1.type; }
  | array_type					{ R(); $$.type = $1.type; }
  ;
non_array_type
  : simple_type					{ R(); $$.type = $1.type; }
  | type_name					{ R(); $$.type = $1.type; }
  ;
simple_type
  : primitive_type				{ R(); $$.type = $1.type; }
  | pointer_type				{ R(); $$.type = $1.type; }
  ;
primitive_type
  : numeric_type				{ R(); $$.type = $1.type; }
  | BOOL						{ R(); $$.type = TypeObject::getTypeObject(TYPE_BOOL); }
  ;
numeric_type
  : integral_type				{ R(); $$.type = $1.type; }
  | floating_point_type			{ R(); $$.type = $1.type; }
  | DECIMAL						{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported decimal/Decimal type"); }
  ;
integral_type
  : SBYTE 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_SBYTE	);	}
  | BYTE 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_BYTE	);	}
  | SHORT 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_SHORT	);	}
  | USHORT 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_USHORT	);	}
  | INT 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_INT		); 	}
  | UINT 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_UINT	); 	}
  | LONG 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_LONG	); 	}
  | ULONG 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_ULONG	); 	}
  | CHAR						{ R(); $$.type = TypeObject::getTypeObject(TYPE_CHAR	); 	}
  ;
floating_point_type
  : FLOAT 						{ R(); $$.type = TypeObject::getTypeObject(TYPE_FLOAT); 	}
  | DOUBLE						{ R(); $$.type = TypeObject::getTypeObject(TYPE_DOUBLE); 	}
  ;
pointer_type
  : type '*'					{ R(); $$.type = $1.type->addPointer();						}
  | VOID '*'					{ R(); $$.type = TypeObject::getTypeObject(TYPE_VOID)->addPointer(); }
  ;
array_type
  : array_type rank_specifier	{ R(); $$.type = $1.type->addRank($2.tmpValue);	}
  | simple_type rank_specifier	{ R(); $$.type = $1.type->addRank($2.tmpValue);	}
  | qualified_identifier rank_specifier
								{ R(); $$.type = TypeObject::getTypeObject($1.text, TYPE_UNRESOLVED)->addRank($2.tmpValue);	}
  ;
rank_specifiers_opt
  : /* Nothing */				{ R(); $$.tmpValue = 0;		}
  | rank_specifier rank_specifiers_opt	
								{ R(); $$.tmpValue = $1.tmpValue; }
  ;
rank_specifier
  : RANK_SPECIFIER				{ R(); $$.tmpValue = $1.tmpValue; }
  ;
  
  
  
  
/***** C.2.3 Variables *****/
variable_reference
  : expression											{ R(); $$.expr = $1.expr; }
  ;
/***** C.2.4 Expressions *****/
argument_list
  : argument											{ R(); $$.expr = CreateMultipleExpr($1.expr); 		}
  | argument_list COMMA argument						{ R(); $$.expr = $1.expr->addExpression($3.expr);	}
  ;
argument
  : expression											{ R(); $$.expr = $1.expr; 								}
  | REF variable_reference								{ R(); $$.expr = CreateSingleExpr(EXPR_REF, $2.expr);	}
  | OUT variable_reference								{ R(); $$.expr = CreateSingleExpr(EXPR_REF, $2.expr);	}
  | IDENTIFIER ':' argument								{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "Named arguments are not supported yet"); }
  ;
primary_expression
  : parenthesized_expression							{ R(); $$.expr = $1.expr; }
  | primary_expression_no_parenthesis					{ R(); $$.expr = $1.expr; }
  ;
primary_expression_no_parenthesis
  : literal												{ R(); $$.expr = CreateLeafExpr(EXPR_CTE)->setValue($1.value); }
  | array_creation_expression							{ R(); $$.expr = $1.expr; }
  | member_access										{ R(); $$.expr = $1.expr; }
  | invocation_expression								{ R(); $$.expr = $1.expr; }
  | element_access										{ R(); $$.expr = $1.expr; }
  | this_access											{ R(); $$.expr = $1.expr; }
  | base_access											{ R(); $$.expr = $1.expr; }
  | new_expression										{ R(); $$.expr = $1.expr; }
  | delegate_expression									{ R(); $$.expr = $1.expr; }
  | typeof_expression									{ R(); $$.expr = $1.expr; }
  | sizeof_expression									{ R(); $$.expr = $1.expr; }
  | checked_expression									{ R(); $$.expr = $1.expr; }
  | unchecked_expression								{ R(); $$.expr = $1.expr; }
  ;
  
delegate_expression
  : DELEGATE '(' formal_parameter_list_opt ')' block	{ R(); $$.expr = CreateDelegateExpr($3.variable, $5.statement); }
  ;

parenthesized_expression
  : '(' expression ')'									{ R(); $$.expr = $2.expr->addParenthesis(); }
  ;
member_access
  : primary_expression '.' IDENTIFIER					{ R(); $$.expr = CreateSingleExpr(EXPR_DOT, $1.expr)->setIdentifier($3.text);	}
  | primitive_type '.' IDENTIFIER						{ R(); $$.expr = CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT,$1.type->m_definitionAC->m_name))->setIdentifier($3.text);	}
  ;
invocation_expression
  : primary_expression_no_parenthesis 	opt_generic '(' { PushGenericType(GetGenericType()); } argument_list_opt ')' { R(); $$.expr = CreateDoubleExpr(EXPR_INVOKE, $1.expr, $5.expr)->addGenericType(PopGenericType())->patchSubInvoke();	}
  | qualified_identifier_opt_generic '(' argument_list_opt ')' { R(); $$.expr = CreateDoubleExpr(EXPR_INVOKE, CreateLeafExpr(EXPR_IDENT,$1.text), $3.expr)->addGenericType(GetGenericType())->patchSubInvoke(); PopGenericType(); }
  ;
argument_list_opt
  : /* Nothing */										{ R(); $$.expr = NULL; 		}
  | argument_list										{ R(); $$.expr = $1.expr;	}
  ;
element_access
  : primary_expression LEFT_BRACKET expression_list RIGHT_BRACKET	{ R(); $$.expr = CreateDoubleExpr(EXPR_ACCESS, $1.expr, $3.expr);	}
  | qualified_identifier LEFT_BRACKET expression_list RIGHT_BRACKET	{ R(); $$.expr = CreateDoubleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_IDENT,$1.text), $3.expr); }
  ;

expression_list_opt
  : /* Nothing */										{ R(); $$.expr = NULL;								}
  | expression_list										{ R(); $$.expr = $1.expr;							}
  ;
  
expression_list
  : expression											{ R(); $$.expr = CreateMultipleExpr($1.expr); 		}
  | expression_list COMMA expression					{ R(); $$.expr = $1.expr->addExpression($3.expr); 	}
  ;
this_access
  : THIS												{ R(); $$.expr = CreateLeafExpr(EXPR_THIS);			}
  ;
base_access
  : BASE '.' IDENTIFIER									{ R(); $$.expr = CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_BASE))->setIdentifier($3.text); }
  | BASE LEFT_BRACKET expression_list RIGHT_BRACKET		{ R(); $$.expr = CreateDoubleExpr(EXPR_ACCESS, CreateLeafExpr(EXPR_BASE), $3.expr);}
  ;
post_increment_expression
  : postfix_expression PLUSPLUS							{ R(); $$.expr = CreateSingleExpr(EXPR_PLUSPLUS, $1.expr);	}
  ;
post_decrement_expression
  : postfix_expression MINUSMINUS						{ R(); $$.expr = CreateSingleExpr(EXPR_MINUSMINUS, $1.expr);}
  ;
new_expression
  : object_creation_expression							{ R(); $$.expr = $1.expr;	}
  ;
object_creation_expression
  : NEW type '(' argument_list_opt ')'					{ R(); $$.expr = CreateSingleExpr(EXPR_NEW, $4.expr)->setType($2.type); }
  ;
array_creation_expression
  : NEW non_array_type LEFT_BRACKET expression_list RIGHT_BRACKET rank_specifiers_opt array_initializer_opt
														{ R(); $$.expr = CreateDoubleExpr(EXPR_NEW, $4.expr, $7.expr)->setType($2.type)->setRank($6.tmpValue)->setArrayNew(true); }
  | NEW array_type array_initializer					{ R(); $$.expr = CreateDoubleExpr(EXPR_NEW, NULL, $3.expr)->setType($2.type)->setArrayNew(false); }
  ;
array_initializer_opt
  : /* Nothing */										{ R(); $$.expr = NULL; 		}
  | array_initializer									{ R(); $$.expr = $1.expr;	}
  ;
typeof_expression
  : TYPEOF '(' type ')'									{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"typeof()"); $$.expr = CreateLeafExpr(EXPR_TYPEOF)->setType($3.type); }
  | TYPEOF '(' VOID ')'									{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"typeof(void)"); }
  ;
checked_expression
  : CHECKED '(' expression ')'							{ R(); compilerError(ERR_NOT_SUPPORTED,"checked"); $$.expr = CreateSingleExpr(EXPR_CHECKED, $3.expr); }
  ;
unchecked_expression
  : UNCHECKED '(' expression ')'						{ R(); compilerError(ERR_NOT_SUPPORTED,"unchecked"); $$.expr = CreateSingleExpr(EXPR_UNCHECKED, $3.expr); }
  ;
pointer_member_access
  : postfix_expression ARROW IDENTIFIER					{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "-> operator not supported yet"); $$.expr = CreateSingleExpr(EXPR_ARROW, $1.expr)->setIdentifier($3.text); }
  ;
addressof_expression
  : '&' unary_expression								{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "& adress operator not supported yet."); $$.expr = CreateSingleExpr(EXPR_ADRESSOF, $1.expr);		}
  ;
sizeof_expression
  : SIZEOF '(' type ')'									{ R(); compilerError(ERR_NOT_SUPPORTED_YET, "sizeof() operator not supported yet"); $$.expr = CreateLeafExpr(EXPR_SIZEOF)->setType($3.type);	}
  ;
postfix_expression
  : primary_expression									{ R(); $$.expr = $1.expr; }
  | qualified_identifier								{ R(); $$.expr = CreateLeafExpr(EXPR_IDENT,$1.text); }
  | post_increment_expression							{ R(); $$.expr = $1.expr; }
  | post_decrement_expression							{ R(); $$.expr = $1.expr; }
  | pointer_member_access								{ R(); $$.expr = $1.expr; }
  ;
unary_expression_not_plusminus
  : postfix_expression									{ R(); $$.expr = $1.expr; }
  | '!' unary_expression								{ R(); $$.expr = CreateSingleExpr(EXPR_NOT, $2.expr);		}
  | '~' unary_expression								{ R(); $$.expr = CreateSingleExpr(EXPR_LNOT, $2.expr);		}
  | cast_expression										{ R(); $$.expr = $1.expr; }
  ;
pre_increment_expression
  : PLUSPLUS unary_expression							{ R(); $$.expr = CreateSingleExpr(EXPR_PREINCR, $2.expr);	}
  ;
pre_decrement_expression
  : MINUSMINUS unary_expression							{ R(); $$.expr = CreateSingleExpr(EXPR_PREDECR, $2.expr);	}
  ;
unary_expression
  : unary_expression_not_plusminus						{ R(); $$.expr = $1.expr; }
  | '+' unary_expression								{ R(); $$.expr = CreateSingleExpr(EXPR_UNARYPLUS, $2.expr);	}
  | '-' unary_expression								{ R(); $$.expr = CreateSingleExpr(EXPR_UNARYMINUS, $2.expr);	}
  | '*' unary_expression								{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Unary * operator"); $$.expr = CreateSingleExpr(EXPR_UNARYMULT, $2.expr);	}
  | pre_increment_expression							{ R(); $$.expr = $1.expr; }
  | pre_decrement_expression							{ R(); $$.expr = $1.expr; }
  | addressof_expression								{ R(); $$.expr = $1.expr; }
  ;
/* For cast_expression we really just want a (type) in the brackets,
 * but have to do some factoring to get rid of conflict with expressions.
 * The paremtnesised expression in the first three cases below should be 
 * semantically restricted to an identifier, optionally follwed by qualifiers
 */
cast_expression
  : '(' expression ')' unary_expression_not_plusminus		{
		R(); $$.expr = CreateDoubleExpr(EXPR_CAST, $2.expr, $4.expr);		
	}
  | '(' multiplicative_expression '*' ')' unary_expression	{
		R(); $$.expr = CreateDoubleExpr(EXPR_CAST_PTR, $2.expr, $5.expr);	
	}
  | '(' qualified_identifier rank_specifier type_quals_opt ')' unary_expression
	{
		$$.expr = CreateSingleExpr(EXPR_CAST, $6.expr)->setType(TypeObject::getTypeObject($2.text, TYPE_UNRESOLVED)->addRank($3.tmpValue),$4.quals);
	}
  | '(' primitive_type type_quals_opt ')' unary_expression
	{	R();
		// $2.type, $3.quals, $5.expr
		$$.expr = CreateSingleExpr(EXPR_CAST, $5.expr)->setType($2.type,$3.quals);
	}
  | '(' VOID type_quals_opt ')' unary_expression
	{	R();
		//  $3.quals, $5.expr
		$$.expr = CreateSingleExpr(EXPR_CAST, $5.expr)->setType(TypeObject::getTypeObject(TYPE_VOID),$3.quals);
	}
  ;
		type_quals_opt
		  : /* Nothing */			{	R();	$$.quals = NULL;		}
		  | type_quals				{	R();	$$.quals = $1.quals;	}
		  ;
		type_quals
		  : type_qual				{	R();	$$.quals = new Quals($1.tmpValue);	}
		  | type_quals type_qual	{	R();	$$.quals = $1.quals->addQuals($2.tmpValue);	}
		  ;
		type_qual 
		  : rank_specifier 			{	$$.tmpValue = $1.tmpValue;		}
		  | '*'						{	$$.tmpValue = -1;				}
		  ;

multiplicative_expression
  : unary_expression											{ R(); $$.expr = $1.expr; }
  | multiplicative_expression '*' unary_expression				{ R(); $$.expr = CreateDoubleExpr(EXPR_MULT, $1.expr, $3.expr);	}
  | multiplicative_expression '/' unary_expression				{ R(); $$.expr = CreateDoubleExpr(EXPR_DIV, $1.expr, $3.expr);	}
  | multiplicative_expression '%' unary_expression				{ R(); $$.expr = CreateDoubleExpr(EXPR_MOD, $1.expr, $3.expr);	}
  ;
additive_expression
  : multiplicative_expression									{ R(); $$.expr = $1.expr; }
  | additive_expression '+' multiplicative_expression			{ R(); $$.expr = CreateDoubleExpr(EXPR_PLUS, $1.expr, $3.expr);	}
  | additive_expression '-' multiplicative_expression			{ R(); $$.expr = CreateDoubleExpr(EXPR_MINUS, $1.expr, $3.expr);	}
  ;
shift_expression
  : additive_expression											{ R(); $$.expr = $1.expr; }
  | shift_expression LTLT additive_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_LSHFT, $1.expr, $3.expr);	}
  | shift_expression GTGT additive_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_RSHFT, $1.expr, $3.expr);	}
  ;
relational_expression
  : shift_expression											{ R(); $$.expr = $1.expr; }
  | relational_expression LT shift_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_LESS, $1.expr, $3.expr);			}
  | relational_expression GT shift_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_MORE, $1.expr, $3.expr);			}
  | relational_expression LEQ shift_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_LESSEQ, $1.expr, $3.expr);		}
  | relational_expression GEQ shift_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_MOREEQ, $1.expr, $3.expr);		}
  | relational_expression IS type								{ R(); $$.expr = CreateSingleExpr(EXPR_IS, $1.expr)->setType($3.type);	}
  | relational_expression AS type								{ R(); $$.expr = CreateSingleExpr(EXPR_AS, $1.expr)->setType($3.type);	}
  ;
equality_expression
  : relational_expression										{ R(); $$.expr = $1.expr; }
  | equality_expression EQEQ relational_expression				{ R(); $$.expr = CreateDoubleExpr(EXPR_EQUTST, $1.expr, $3.expr);	}
  | equality_expression NOTEQ relational_expression				{ R(); $$.expr = CreateDoubleExpr(EXPR_DIFFTST, $1.expr, $3.expr);	}
  ;
and_expression
  : equality_expression											{ R(); $$.expr = $1.expr; }
  | and_expression '&' equality_expression						{ R(); $$.expr = CreateDoubleExpr(EXPR_LAND, $1.expr, $3.expr);	}
  ;
exclusive_or_expression
  : and_expression												{ R(); $$.expr = $1.expr; }
  | exclusive_or_expression '^' and_expression					{ R(); $$.expr = CreateDoubleExpr(EXPR_LXOR, $1.expr, $3.expr);	}
  ;
inclusive_or_expression
  : exclusive_or_expression										{ R(); $$.expr = $1.expr; }
  | inclusive_or_expression '|' exclusive_or_expression			{ R(); $$.expr = CreateDoubleExpr(EXPR_LOR, $1.expr, $3.expr);	}
  ;
conditional_and_expression
  : inclusive_or_expression										{ R(); $$.expr = $1.expr; }
  | conditional_and_expression ANDAND inclusive_or_expression	{ R(); $$.expr = CreateDoubleExpr(EXPR_AND, $1.expr, $3.expr);	}
  ;
conditional_or_expression
  : conditional_and_expression									{ R(); $$.expr = $1.expr; }
  | conditional_or_expression OROR conditional_and_expression	{ R(); $$.expr = CreateDoubleExpr(EXPR_OR, $1.expr, $3.expr);	}
  ;
conditional_expression
  : conditional_or_expression									{ R(); $$.expr = $1.expr; }
  | conditional_or_expression '?' expression ':' expression		{ R(); $$.expr = CreateTripleExpr(EXPR_COND, $1.expr, $3.expr, $5.expr);	}
  ;
assignment : unary_expression assignment_operator expression	{ R(); $$.expr = CreateDoubleExpr((EnumExpressionType)$2.tmpValue, $1.expr, $3.expr);	}
  ;
assignment_operator
  : '='					{ R(); $$.tmpValue	= EXPR_ASS_EQ;		}
  | PLUSEQ				{ R(); $$.tmpValue	= EXPR_ASS_PLUSEQ;	}
  | MINUSEQ				{ R(); $$.tmpValue	= EXPR_ASS_MINUSEQ;	}
  | STAREQ				{ R(); $$.tmpValue	= EXPR_ASS_STAREQ;	}
  | DIVEQ				{ R(); $$.tmpValue	= EXPR_ASS_DIVEQ;	}
  | MODEQ				{ R(); $$.tmpValue	= EXPR_ASS_MODEQ;	}
  | XOREQ				{ R(); $$.tmpValue	= EXPR_ASS_XOREQ;	}
  | ANDEQ 				{ R(); $$.tmpValue	= EXPR_ASS_ANDEQ;	}
  | OREQ				{ R(); $$.tmpValue	= EXPR_ASS_OREQ;	}
  | GTGTEQ				{ R(); $$.tmpValue	= EXPR_ASS_RSHFTEQ;	}
  | LTLTEQ				{ R(); $$.tmpValue	= EXPR_ASS_LSHFTEQ;	}
  ;
  
expression
  : conditional_expression		{ R(); $$.expr = $1.expr; }
  | assignment					{ R(); $$.expr = $1.expr; }
  ;
constant_expression
  : expression					{ R(); $$.expr = $1.expr; }
  ;
boolean_expression
  : expression					{ R(); $$.expr = $1.expr; }
  ;
  
  
  
  
  
  
  
  
  
  
  
/***** C.2.5 Statements *****/
statement						
  : labeled_statement				{ R(); $$.statement	= $1.statement; }
  | declaration_statement			{ R(); $$.statement	= $1.statement; }
  | embedded_statement				{ R(); $$.statement	= $1.statement; }
  ;
embedded_statement
  : block							{ R(); $$.statement	= $1.statement; }
  | empty_statement					{ R(); $$.statement	= $1.statement; }
  | expression_statement			{ R(); $$.statement	= $1.statement; }
  | selection_statement				{ R(); $$.statement	= $1.statement; }
  | iteration_statement				{ R(); $$.statement	= $1.statement; }
  | jump_statement					{ R(); $$.statement	= $1.statement; }
  | try_statement					{ R(); $$.statement	= $1.statement; }
  | checked_statement				{ R(); $$.statement	= $1.statement; }
  | unchecked_statement				{ R(); $$.statement	= $1.statement; }
  | lock_statement					{ R(); $$.statement	= $1.statement; }
  | using_statement					{ R(); $$.statement	= $1.statement; }
  | unsafe_statement				{ R(); $$.statement	= $1.statement; }
  | fixed_statement					{ R(); $$.statement	= $1.statement; }
  ;
block
  : '{' statement_list_opt '}'		{ R(); $$.statement = CreateStatement(STM_BLOCK, NULL, $2.statement); }
  ;
statement_list_opt
  : /* Nothing */					{ R(); $$.statement = NULL; }
  | statement_list					{ R(); $$.statement = $1.statement;	}
  ;

statement_list
  : statement						{ R(); $$.statement = $1.statement;	}
  | statement_list statement		{ R(); $$.statement = $1.statement ? $1.statement->addNext($2.statement) : $2.statement; }
  ;
empty_statement
  : ';'								{ R(); $$.statement = CreateStatement(STM_NULL, NULL, NULL); }
  ;
labeled_statement
  : IDENTIFIER ':' statement		{ R(); $$.statement = CreateStatement(STM_LABEL, NULL, $3.statement)->addLabel($1.text);	}
  ;
declaration_statement
  : local_variable_declaration ';'	{ R(); $$.statement = $1.statement;	}
  | local_constant_declaration ';'	{ R(); $$.statement = $1.statement;	}
  ;
local_variable_declaration
  : type variable_declarators		{ R(); $$.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, $2.variable, $1.type); }
  ;
variable_declarators
  : variable_declarator										{ R(); $$.variable = $1.variable; }
  | variable_declarators COMMA variable_declarator			{ R(); $$.variable = $1.variable->addVariable($3.variable); }
  ;
variable_declarator
  : IDENTIFIER												{ R(); $$.variable = CreateVarInstance($1.text);	}
  | IDENTIFIER '=' variable_initializer						{ R(); $$.variable = CreateVarInstance($1.text)->setInitializer($3.expr); }
  ;
variable_initializer
  : expression												{ R(); $$.expr = $1.expr; }
  | array_initializer										{ R(); $$.expr = $1.expr; }
  | stackalloc_initializer									{ R(); $$.expr = $1.expr; }
  ;
stackalloc_initializer
  : STACKALLOC type  LEFT_BRACKET expression RIGHT_BRACKET 	{ R(); /* Only in unsafe code from spec */compilerError(ERR_NOT_SUPPORTED_YET,"stackalloc"); }
  ; 
local_constant_declaration
  : CONST type constant_declarators							{ R(); $$.statement = CreateVarStatement(STM_LOCALVAR, NULL, NULL, $3.variable, $2.type)->setConstant(); }
  ;
constant_declarators
  : constant_declarator										{ R(); $$.variable = $1.variable; }
  | constant_declarators COMMA constant_declarator			{ R(); $$.variable = $1.variable->addVariable($3.variable); }
  ;
constant_declarator
  : IDENTIFIER '=' constant_expression						{ R(); $$.variable = CreateVarInstance($1.text)->setInitializer($3.expr); }
  ;
expression_statement
  : statement_expression ';'								{ R(); $$.statement = $1.statement; }
  ;
statement_expression
  : invocation_expression									{ R(); $$.statement = CreateStatement(STM_WRAP_EXP, NULL, NULL)->setExpression($1.expr); }
  | object_creation_expression								{ R(); $$.statement = CreateStatement(STM_WRAP_EXP, NULL, NULL)->setExpression($1.expr); }
  | assignment												{ R(); $$.statement = CreateStatement(STM_ASSIGN_EXPR, NULL, NULL)->setExpression($1.expr); }
  | post_increment_expression								{ R(); $$.statement = CreateStatement(STM_WRAPPER_POSTINCR,NULL,NULL)->setExpression($1.expr); }
  | post_decrement_expression								{ R(); $$.statement = CreateStatement(STM_WRAPPER_POSTDECR,NULL,NULL)->setExpression($1.expr); }
  | pre_increment_expression								{ R(); $$.statement = CreateStatement(STM_WRAPPER_PREINCR ,NULL,NULL)->setExpression($1.expr); }
  | pre_decrement_expression								{ R(); $$.statement = CreateStatement(STM_WRAPPER_PREDECR ,NULL,NULL)->setExpression($1.expr); }
  ;
selection_statement
  : if_statement											{ R(); $$.statement = $1.statement; }
  | switch_statement										{ R(); $$.statement = $1.statement; }
  ;
if_statement
	// if ( part1 ) statement opt_else
	
	: IF ifpart opt_else {
		R();
		if ($3.statement) {
			// IF-ELSE
			$$.statement = CreateStatement(STM_IF, NULL, $2.statement)->addChild($3.statement)->setExpression($2.expr);
		} else {
			// IF
			$$.statement = CreateStatement(STM_IF, NULL, $2.statement)->setExpression($2.expr);
		}
	}
  ;
  
ifpart	: '(' boolean_expression ')' embedded_statement	{ $$.expr = $2.expr; $$.statement = $4.statement; }
		;

opt_else: ELSE embedded_statement		{ $$.statement = $2.statement; }
		|	%prec THEN/* Do nothing */	{ $$.statement = NULL; }
		;
		
switch_statement
  : SWITCH '(' expression ')' switch_block	{ R(); $$.statement = CreateStatement(STM_SWITCH, NULL, $5.statement)->setExpression($3.expr); }
  ;
switch_block
  : '{' switch_sections_opt '}'				{ R(); $$.statement = $2.statement; }
  ;
switch_sections_opt
  : /* Nothing */							{ R(); $$.statement = NULL; }
  | switch_sections							{ R(); $$.statement = $1.statement; }
  ;
switch_sections
  : switch_section							{ R(); $$.statement = $1.statement; }
  | switch_sections switch_section			{ R(); $$.statement = $1.statement->addNext($2.statement); }
  ;
switch_section
  : switch_labels statement_list			{ R(); $$.statement = $1.statement->addChild($2.statement); }
  ;
switch_labels
  : switch_label							{ R(); $$.statement = $1.statement; }
  | switch_labels switch_label				{ R(); $$.statement = $1.statement->addNext($2.statement); }
  ;
switch_label
  : CASE constant_expression ':'			{ R(); $$.statement = CreateStatement(STM_CASE, NULL, NULL		)->setExpression($2.expr); }
  | DEFAULT ':'								{ R(); $$.statement = CreateStatement(STM_CASEDEFAULT, NULL, NULL); }
  ;
iteration_statement
  : while_statement							{ R(); $$.statement = $1.statement; }
  | do_statement							{ R(); $$.statement = $1.statement; }
  | for_statement							{ R(); $$.statement = $1.statement; }
  | foreach_statement						{ R(); $$.statement = $1.statement; }
  ;
unsafe_statement
  : UNSAFE block							{ R(); $$.statement = CreateStatement(STM_UNSAFE, NULL, $2.statement); }
  ;
while_statement
  : WHILE '(' boolean_expression ')' embedded_statement	
	{ R(); $$.statement = CreateStatement(STM_WHILE, NULL, $5.statement)->setExpression($3.expr); }
  ;
do_statement
  : DO embedded_statement WHILE '(' boolean_expression ')' ';'
	{ R(); $$.statement = CreateStatement(STM_DOWHILE, NULL, $2.statement)->setExpression($5.expr); }
  ;
for_statement
  : FOR '(' for_initializer_opt ';' for_condition_opt ';' for_iterator_opt ')' embedded_statement
	{ R(); $$.statement = CreateStatement(STM_FOR, NULL, $2.statement)	->setExpression	 ($5.expr)
																	->addChildNilWrap($3.statement)
																	->addChildNilWrap($7.statement)
																	->addChildNilWrap($9.statement); }
  ;
for_initializer_opt
  : /* Nothing */				{ R(); $$.statement = NULL;	}
  | for_initializer				{ R(); $$.statement = $1.statement; }
  ;
for_condition_opt
  : /* Nothing */				{ R(); $$.expr = NULL;		}
  | for_condition				{ R(); $$.expr = $1.expr; 	}
  ;
for_iterator_opt
  : /* Nothing */				{ R(); $$.statement = NULL;	}
  | for_iterator				{ R(); $$.statement = $1.statement; }
  ;
for_initializer
  : local_variable_declaration	{ R(); $$.statement = $1.statement; }
  | statement_expression_list	{ R(); $$.statement = $1.statement; }
  ;
for_condition
  : boolean_expression			{ R(); $$.expr = $1.expr; 	}
  ;
for_iterator
  : statement_expression_list	{ R(); $$.statement = $1.statement; }
  ;
statement_expression_list
  : statement_expression									{ R(); $$.statement = $1.statement; }
  | statement_expression_list COMMA statement_expression	{ R(); $$.statement = $1.statement->addNext($3.statement); }
  ;
foreach_statement
  : FOREACH '(' type IDENTIFIER IN expression ')' embedded_statement
										{
											R(); 
											const char* enumVar = makeUniqueId("enumerator");
											PushGenericType(GetGenericType());
											addGenericType($3.type);
											// NOTE: Requires System.Collections.Generic;
											TypeObject* enumType =
												TypeObject::getTypeObject("IEnumerator", TYPE_UNRESOLVED)
												->setGeneric(GetGenericType());
											PopGenericType();

											$$.statement =
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
															CreateSingleExpr(EXPR_DOT, $6.expr)->setIdentifier("GetEnumerator"),
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
																		$8.statement, // next
																		NULL, // child
																		CreateVarInstance(
																			$4.text
																		)->setInitializer(
																			CreateSingleExpr(EXPR_DOT, CreateLeafExpr(EXPR_IDENT, enumVar))->setIdentifier("Current")
																		),
																		$3.type
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
										}
  ;
jump_statement
  : break_statement						{ R(); $$.statement = $1.statement; }
  | continue_statement					{ R(); $$.statement = $1.statement; }
  | goto_statement						{ R(); $$.statement = $1.statement; }
  | return_statement					{ R(); $$.statement = $1.statement; }
  | throw_statement						{ R(); $$.statement = $1.statement; }
  ;
break_statement
  : BREAK ';'							{ R(); $$.statement = CreateStatement(STM_BREAK, NULL, NULL); }
  ;
continue_statement
  : CONTINUE ';'						{ R(); $$.statement = CreateStatement(STM_CONTINUE, NULL, NULL); }
  ;
goto_statement
  : GOTO IDENTIFIER ';'					{ R(); $$.statement = CreateStatement(STM_GOTO, NULL,NULL)->addLabel($2.text);	}
  | GOTO CASE constant_expression ';'	{ R(); $$.statement = CreateStatement(STM_GOTOCASE, NULL, NULL)->setExpression($3.expr); }
  | GOTO DEFAULT ';'					{ R(); $$.statement = CreateStatement(STM_GOTODEFAULT, NULL,NULL); }
  ;
return_statement
  : RETURN expression_opt ';'			{ R(); $$.statement = CreateStatement(STM_RETURN, NULL, NULL)->setExpression($2.expr); }
  ;
expression_opt
  : /* Nothing */						{ R(); $$.expr = NULL; 		}
  | expression							{ R(); $$.expr = $1.expr; 	}
  ;
throw_statement
  : THROW expression_opt ';'			{ R(); $$.statement = CreateStatement(STM_THROW, NULL, NULL)->setExpression($2.expr); }
  ;
try_statement
  : TRY block catch_clauses				{ R(); $$.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild($2.statement)->addNext($3.statement); 
										}
  | TRY block finally_clause			{ R(); $$.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild($2.statement)->addNext($3.statement);
										}
  | TRY block catch_clauses finally_clause
										{ R(); $$.statement = CreateStatement(STM_TRY, NULL, NULL)
											->addChild($2.statement)->addNext($3.statement)->addNext($4.statement);
										}
  ;
catch_clauses
  : catch_clause						{ R(); $$.statement = $1.statement; }
  | catch_clauses catch_clause			{ R(); $$.statement = $1.statement->addNext($2.statement); }
  ;
catch_clause
  : CATCH '(' type_name identifier_opt ')' block	{ R(); $$.statement = CreateStatement(STM_CATCH, NULL, NULL)
														->addChild($6.statement)->addLabel($4.text)->addType($3.type); 
													}
  | CATCH block										{ R(); $$.statement = CreateStatement(STM_CATCH, NULL, NULL)->addChild($2.statement); }
  ;
identifier_opt
  : /* Nothing */									{ R(); $$.text = NULL; }
  | IDENTIFIER										{ R(); $$.text = $1.text; }
  ;
finally_clause
  : FINALLY block									{ R(); $$.statement = CreateStatement(STM_FINALLY, NULL, NULL)->addChild($2.statement); }
  ;
checked_statement
  : CHECKED block									{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported 'checked' statement"); $$.statement = CreateStatement(STM_CHECKED, NULL, NULL)->addChild($2.statement); }
  ;
unchecked_statement
  : UNCHECKED block									{ R(); $$.statement = CreateStatement(STM_UNCHECKED, NULL, NULL)->addChild($2.statement); }
  ;
lock_statement
  : LOCK '(' expression ')' embedded_statement		{ R(); compilerError(ERR_NOT_SUPPORTED,"Unsupported 'lock' statement"); $$.statement = CreateStatement(STM_LOCK, NULL, NULL)
														->addChild($5.statement)->setExpression($3.expr);
													}
  ;
using_statement
  : USING '(' resource_acquisition ')' embedded_statement	
													{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Unsupported 'using' statement"); $$.statement = CreateStatement(STM_USING, NULL, NULL)->addChild($3.statement)->addChild($5.statement); }
  ;
resource_acquisition
  : local_variable_declaration						{ R(); $$.statement = $1.statement }
  | expression										{ R(); $$.statement = $1.statement }
  ;
fixed_statement
/*! : FIXED '(' pointer_type fixed_pointer_declarators ')' embedded_statement */
  : FIXED '('  type fixed_pointer_declarators ')' embedded_statement
																{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"FIXED not supported."); }
  ;
fixed_pointer_declarators
  : fixed_pointer_declarator									{ R(); /* When FIXED Support */ }
  | fixed_pointer_declarators COMMA fixed_pointer_declarator	{ R(); /* When FIXED Support */ }
  ;
fixed_pointer_declarator
  : IDENTIFIER '=' expression									{ R(); /* When FIXED Support */ }
  ;
  
  
  
  
  
  
compilation_unit
  : using_directives_opt attributes_opt 						{ R(); /* Nothing to do here */ }
  | using_directives_opt namespace_member_declarations			{ R(); /* Nothing to do here */ }
  ;
using_directives_opt
  : /* Nothing */												{ R(); /* Nothing to do here */ }
  | using_directives											{ R(); /* Nothing to do here */ }
  ;
attributes_opt
  : /* Nothing */												{ R(); $$.attribute = NULL; }
  | attributes													{ R(); $$.attribute = $1.attribute; }
  ;
namespace_member_declarations_opt
  : /* Nothing */												{ R(); /* Nothing to do here */ }
  | namespace_member_declarations								{ R(); /* Nothing to do here */ }
  ;
namespace_declaration
  : attributes_opt NAMESPACE qualified_identifier { R(); useOrCreateNameSpace($1.attribute, $3.text); } namespace_body comma_opt
									{ R();	// Unstack.
										unuseNameSpace();		}
  ;
comma_opt
  : /* Nothing */					{ R(); /* Nothing to do here */ }
  | ';'								{ R(); /* Nothing to do here */ }
  ;
/*
qualified_identifier
  : IDENTIFIER
  | qualified_identifier '.' IDENTIFIER
  ;
*/
qualified_identifier
  : IDENTIFIER						{ R(); $$.text = $1.text; 	display($1.text);		}
  | qualifier IDENTIFIER			{ R(); $$.text = concat2($1.text, $2.text); 		}
  ;
qualifier
  : IDENTIFIER '.' 					{ R(); $$.text = concat2($1.text, "."); 			}
  | qualifier IDENTIFIER '.' 		{ R(); $$.text = concat3($1.text, $2.text, "."); 	}
  ;
  
namespace_body
  : '{' using_directives_opt namespace_member_declarations_opt '}'	{ R(); /* Nothing to do here */ }
  ;
using_directives
  : using_directive												{ R(); /* Nothing to do here */ }
  | using_directives using_directive							{ R(); /* Nothing to do here */ }
  ;
using_directive
  : using_alias_directive										{ R(); /* Nothing to do here */ }
  | using_namespace_directive									{ R(); /* Nothing to do here */ }
  ;
using_alias_directive
  : USING IDENTIFIER '=' qualified_identifier ';' 				{ R(); createAlias($2.text, $4.text); 	}
  ;
using_namespace_directive
  : USING namespace_name ';' 									{ R(); addUsingNameSpace($2.text); 		}
  ;
namespace_member_declarations
  : namespace_member_declaration								{ R(); /* Nothing to do here */ }
  | namespace_member_declarations namespace_member_declaration	{ R(); /* Nothing to do here */ }
  ;
namespace_member_declaration
  : namespace_declaration										{ R(); /* Nothing to do here */ }
  | type_declaration											{ R(); /* Nothing to do here */ }
  ;
type_declaration
  : class_declaration											{ R(); /* Nothing to do here */ }
  | struct_declaration											{ R(); /* Nothing to do here */ }
  | interface_declaration										{ R(); /* Nothing to do here */ }
  | enum_declaration											{ R(); /* Nothing to do here */ }
  | delegate_declaration										{ R(); /* Nothing to do here */ }
  ;

/***** Modifiers *****/
/* This now replaces:
 * class_modifier, constant_modifier, field_modifier, method_modifier, 
 * property_modifier, event_modifier, indexer_modifier, operator_modifier, 
 * constructor_modifier, struct_modifier, interface_modifier, 
 * enum_modifier, delegate_modifier
 */
modifiers_opt
  : /* Nothing */		{ R(); $$.tmpValue = 0;				}
  | modifiers			{ R(); $$.tmpValue = $1.tmpValue; 	}
  ;
modifiers
  : modifier			{ R(); $$.tmpValue = $1.tmpValue; 				}
  | modifiers modifier	{ R(); $$.tmpValue = $2.tmpValue | $1.tmpValue; 	}
  ;
modifier
  : ABSTRACT			{ R(); $$.tmpValue = ATT_ABSTRACT;	}
  | EXTERN				{ R(); $$.tmpValue = ATT_EXTERN;		}
  | INTERNAL			{ R(); $$.tmpValue = ATT_INTERNAL;	}
  | NEW					{ R(); $$.tmpValue = ATT_NEW;		}
  | OVERRIDE			{ R(); $$.tmpValue = ATT_VIRTUAL;	}
  | PRIVATE				{ R(); $$.tmpValue = ATT_PRIVATE;	}
  | PROTECTED			{ R(); $$.tmpValue = ATT_PROTECTED;	}
  | PUBLIC				{ R(); $$.tmpValue = ATT_PUBLIC;		}
  | READONLY			{ R(); $$.tmpValue = ATT_READONLY;	}
  | SEALED				{ R(); $$.tmpValue = ATT_SEALED;		}
  | STATIC				{ R(); $$.tmpValue = ATT_STATIC;		}
  | UNSAFE				{ R(); $$.tmpValue = ATT_UNSAFE;		}
  | VIRTUAL				{ R(); $$.tmpValue = ATT_VIRTUAL;	}
  | VOLATILE			{ R(); $$.tmpValue = ATT_VOLATILE;	}
  | PARTIAL				{ R(); $$.tmpValue = ATT_PARTIAL;	}
  ;
/***** C.2.6 Classes *****/
class_declaration
  : attributes_opt modifiers_opt CLASS IDENTIFIER opt_generic_fct
	{ R();
		gCurrentAC = CreateClass(	$1.attribute, 
						$2.tmpValue, 
						$4.text);
						
		gCurrentAC->setGenericParam();
	} class_base_opt class_body comma_opt { R(); unuseNameSpace(); }
  ;
  
class_base_opt
  : /* Nothing */										{ R(); /* Do nothing */	}
  | class_base											{ R(); /* Do nothing */	}
  ;
class_base
  : ':' interface_type_list								{ R(); /* Do nothing */						}
  ;
interface_type_list
  : type_name											{ R(); gCurrentAC->addInheritance($1.type);	}
  | interface_type_list COMMA type_name					{ R(); gCurrentAC->addInheritance($3.type);	}
  ;
class_body
  : '{' class_member_declarations_opt '}'				{ R(); /* Do nothing */	}
  ;
class_member_declarations_opt
  : /* Nothing */										{ R(); /* Do nothing */	}
  | class_member_declarations							{ R(); /* Do nothing */	}
  ;
class_member_declarations
  : class_member_declaration							{ R(); /* Do nothing */	}
  | class_member_declarations class_member_declaration	{ R(); /* Do nothing */	}
  ;
class_member_declaration
  : constant_declaration								{ R(); /* Do nothing */	}
  | field_declaration									{ R(); /* Do nothing */	}
  | method_declaration									{ R(); /* Do nothing */	}
  | property_declaration								{ R(); /* Do nothing */	}
  | event_declaration									{ R(); /* Do nothing */	}
  | indexer_declaration									{ R(); /* Do nothing */	}
  | operator_declaration								{ R(); /* Do nothing */	}
  | constructor_declaration								{ R(); /* Do nothing */	}
  | destructor_declaration								{ R(); /* Do nothing */	}
/*  | static_constructor_declaration */
  | type_declaration									{ R(); /* Do nothing */	}
  ;
constant_declaration
  : attributes_opt modifiers_opt CONST type constant_declarators ';'	{ R();
																			// Trick : CONST C# is STATIC member in C++ to match C# behavior.
																			gCurrentAC->addVariable($1.attribute, ($2.tmpValue & ~ATT_CONST) | ATT_STATIC, $4.type, $5.variable );	}
  ;
field_declaration
  : attributes_opt modifiers_opt type variable_declarators ';'			{ R(); gCurrentAC->addVariable($1.attribute, $2.tmpValue, $3.type, $4.variable );				}
  ;
method_declaration
  : method_header method_body											{ R(); gCurrentMethod = gCurrentAC->addMethod(
																			$1.attribute,	// Attributes
																			$1.tmpValue,	// Modified REF/OUT
																			$1.text,		// Func Name
																			$1.variable,	// Link list of variable
																			$2.statement,	// Code
																			$1.type			// Return value.
																		 );
																		  gCurrentMethod->setGenericParam();
																		}
  ;
/* Inline return_type to avoid conflict with field_declaration */
method_header
  : attributes_opt modifiers_opt type qualified_identifier opt_generic_fct '(' formal_parameter_list_opt ')'	
	{ R(); 	$$.attribute 	= $1.attribute; 
		$$.tmpValue  	= $2.tmpValue;
		$$.text			= $4.text;
		$$.variable		= $7.variable;
		$$.type			= $3.type;								}
  | attributes_opt modifiers_opt VOID qualified_identifier opt_generic_fct '(' formal_parameter_list_opt ')'
	{ R(); 	$$.attribute 	= $1.attribute; 
		$$.tmpValue  	= $2.tmpValue;
		$$.text			= $4.text;
		$$.variable		= $7.variable;
		$$.type			= TypeObject::getTypeObject(TYPE_VOID);	}
  ;
  
name_list
  : IDENTIFIER					{ R(); addGenericName($1.text); 	}
  | name_list COMMA IDENTIFIER	{ R(); addGenericName($3.text);		}
  ;
opt_generic_fct
	:	/* Nothing */				{ R(); }
	|	GEN_LT name_list GEN_GT		{ R(); }
	;
	
formal_parameter_list_opt
  : /* Nothing */									{ R(); $$.variable = NULL;								}
  | formal_parameter_list							{ R(); $$.variable = $1.variable;						}
  ;
return_type
  : type											{ R(); $$.type = $1.type;								}
  | VOID											{ R(); $$.type = TypeObject::getTypeObject(TYPE_VOID);	}
  ;
method_body
  : block											{ R(); $$.statement = $1.statement;						}
  | ';'												{ R(); $$.statement = NULL;								}
  ;
formal_parameter_list
  : formal_parameter								{ R(); $$.variable = $1.variable;							}
  | formal_parameter_list COMMA formal_parameter	{ R(); $$.variable = $1.variable->addVariable($3.variable);	}
  ;
formal_parameter
  : fixed_parameter									{ R(); $$.variable = $1.variable ;						}
  | parameter_array									{ R(); $$.variable = $1.variable ;						}
  ;
fixed_parameter
  : attributes_opt parameter_modifier_opt type IDENTIFIER fixed_parameter_opt_default
													{ R(); $$.variable = CreateVarInstance($4.text)
														->setAttribute($1.attribute)
														->setModifier($2.tmpValue)
														->setType($3.type)
														->setInitializer($5.expr);							}
  ;
fixed_parameter_opt_default
  : /* Nothing */									{ R();  $$.expr		= NULL;								}
  | '=' expression									{ R();  $$.expr		= $2.expr;							}
  ;
parameter_modifier_opt
  : /* Nothing */									{ R();	$$.tmpValue	= 0;								}
  | REF												{ R();	$$.tmpValue = ATT_REF;							}
  | OUT												{ R();	$$.tmpValue	= ATT_REF;							}
  ;
parameter_array
/*!  : attributes_opt PARAMS array_type IDENTIFIER */
  : attributes_opt PARAMS type IDENTIFIER			{ R(); $$.variable = CreateVarInstance($4.text)
														->setType($3.type)
														->setAttribute($1.attribute)
														->setIsEndLessParam();
														compilerError(ERR_NOT_SUPPORTED_YET, "params keyword is not supported");
													}
  ;
property_declaration
  : attributes_opt modifiers_opt type qualified_identifier 
      ENTER_getset
    '{' accessor_declarations '}'
      EXIT_getset											{ R(); gCurrentAC->addProperty($1.attribute, $2.tmpValue, $3.type, $4.text, $7.accessor);	}
  ;
accessor_declarations
  : get_accessor_declaration set_accessor_declaration_opt	{ R(); $$.accessor = CreateAccessor($1.accessor, $2.accessor);	}
  | set_accessor_declaration get_accessor_declaration_opt	{ R(); $$.accessor = CreateAccessor($2.accessor, $1.accessor);	}
  | /* None */												{ R(); $$.accessor = CreateAccessor((Accessor*)NULL,(Accessor*)NULL); }
  ;
set_accessor_declaration_opt
  : /* Nothing */											{ R(); $$.accessor = NULL;			}
  | set_accessor_declaration								{ R(); $$.accessor = $1.accessor;	}
  ;
get_accessor_declaration_opt
  : /* Nothing */											{ R(); $$.accessor = NULL;			}
  | get_accessor_declaration								{ R(); $$.accessor = $1.accessor;	}
  ;
get_accessor_declaration
  : attributes_opt GET 
      EXIT_getset
    accessor_body
      ENTER_getset											{ R(); $$.accessor  = CreateAccessor($1.attribute, $4.statement);	}
  ;
set_accessor_declaration
  : attributes_opt SET 
      EXIT_getset
    accessor_body
      ENTER_getset											{ R(); $$.accessor  = CreateAccessor($1.attribute, $4.statement);	}
  ;
accessor_body
  : block																{ R(); $$.statement = $1.statement; 	}
  | ';'																	{ R(); $$.statement = NULL;			}
  ;
event_declaration
  : attributes_opt modifiers_opt EVENT type variable_declarators ';'	{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  | attributes_opt modifiers_opt EVENT type qualified_identifier 
      ENTER_accessor_decl 
    '{' event_accessor_declarations '}'
      EXIT_accessor_decl												{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  ;
event_accessor_declarations
  : add_accessor_declaration remove_accessor_declaration				{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  | remove_accessor_declaration add_accessor_declaration				{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  ;
add_accessor_declaration
  : attributes_opt ADD 									
      EXIT_accessor_decl 
    block 
      ENTER_accessor_decl												{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  ;
remove_accessor_declaration
  : attributes_opt REMOVE 
      EXIT_accessor_decl 
    block 
      ENTER_accessor_decl												{ R();	compilerError(ERR_NOT_SUPPORTED,"event not supported");	}
  ;
indexer_declaration
  : attributes_opt modifiers_opt indexer_declarator
      ENTER_getset
    '{' accessor_declarations '}'
      EXIT_getset
	{	R();
		$6.accessor->setAsIndexer($3.type, $3.variable);
		gCurrentAC->addProperty($1.attribute, $2.tmpValue, $6.accessor);
	}
  ;
indexer_declarator
  : type THIS LEFT_BRACKET formal_parameter_list RIGHT_BRACKET					{ R(); $$.variable  = $4.variable; $$.type = $1.type; }
/* | type type_name '.' THIS LEFT_BRACKET formal_parameter_list RIGHT_BRACKET */
  | type qualified_this LEFT_BRACKET formal_parameter_list RIGHT_BRACKET		{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Explicit implementation of an interface indexer is not supported yet"); }
  ;
qualified_this
  : qualifier THIS																{ R(); $$.text = concat2($1.text, "this"); }
  ;
/* Widen operator_declaration to make modifiers optional */
operator_declaration
  : attributes_opt modifiers_opt operator_declarator operator_body				{ R(); /* TODO When support operator */	}
  ;
operator_declarator
  : overloadable_operator_declarator											{ R(); /* TODO When support operator */	}
  | conversion_operator_declarator												{ R(); /* TODO When support operator */	}
  ;
overloadable_operator_declarator
  : type OPERATOR overloadable_operator '(' type IDENTIFIER ')'							{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Overloading operator not supported."); }
  | type OPERATOR overloadable_operator '(' type IDENTIFIER COMMA type IDENTIFIER ')'	{ R(); compilerError(ERR_NOT_SUPPORTED_YET,"Overloading operator not supported."); }
  ;
overloadable_operator
  : '+' 																				{ R(); $$.tmpValue = OP_PLUS;  }
  | '-' 																				{ R(); $$.tmpValue = OP_MINUS; }
  | '!' 																				{ R(); $$.tmpValue = OP_LNOT;  }
  | '~' 																				{ R(); $$.tmpValue = OP_NOT;   }
  | PLUSPLUS 																			{ R(); $$.tmpValue = OP_PLUSPLUS;   }
  | MINUSMINUS 																			{ R(); $$.tmpValue = OP_MINUSMINUS; }
  | TRUE 																				{ R(); $$.tmpValue = OP_TRUE;  }
  | FALSE																				{ R(); $$.tmpValue = OP_FALSE; }
  | '*' 																				{ R(); $$.tmpValue = OP_MULT;  }
  | '/' 																				{ R(); $$.tmpValue = OP_DIV;   }
  | '%' 																				{ R(); $$.tmpValue = OP_MOD;   }
  | '&' 																				{ R(); $$.tmpValue = OP_AND;   }
  | '|' 																				{ R(); $$.tmpValue = OP_OR;    }
  | '^' 																				{ R(); $$.tmpValue = OP_XOR;   }
  | LTLT 																				{ R(); $$.tmpValue = OP_LSHFT; }
  | GTGT 																				{ R(); $$.tmpValue = OP_RSHFT; }
  | EQEQ 																				{ R(); $$.tmpValue = OP_EQUAL; }
  | NOTEQ 																				{ R(); $$.tmpValue = OP_DIFF;  }
  | GT 																					{ R(); $$.tmpValue = OP_MORE;  }
  | LT 																					{ R(); $$.tmpValue = OP_LESS;  }
  | GEQ 																				{ R(); $$.tmpValue = OP_MOREEQ;}
  | LEQ																					{ R(); $$.tmpValue = OP_LESSEQ;}
  ;
  
conversion_operator_declarator
  : IMPLICIT OPERATOR type '(' type IDENTIFIER ')'										{ R(); /* TODO When support operator */	}
  | EXPLICIT OPERATOR type '(' type IDENTIFIER ')'										{ R(); /* TODO When support operator */	}
  ;
constructor_declaration
  : attributes_opt modifiers_opt constructor_declarator constructor_body				{ R();
		gCurrentMethod = gCurrentAC->addConstructor(
			$1.attribute,	// Attributes
			$2.tmpValue,	// Modifier
			$3.text,		// Func Name
			$3.variable,	// Link list of variable
			$4.statement,	// Code
			$3.expr,		// Call to Base or this with arguments.
			$3.tmpValue		// -1 : Nothing, 0 : Base Call, 1 : This Call.
		);
	}
  ;
constructor_declarator
  : IDENTIFIER '(' formal_parameter_list_opt ')' constructor_initializer_opt	{ R(); 	$$.text		= $1.text; 
																					$$.variable = $3.variable; 
																					$$.expr		= $5.expr; 
																					$$.tmpValue	= $5.tmpValue;
																				}
  ;
constructor_initializer_opt
  : /* Nothing */							{ R(); $$.expr	= NULL;		$$.tmpValue = -1;			}
  | constructor_initializer					{ R(); $$.expr	= $1.expr;	$$.tmpValue = $1.tmpValue;	}
  ;
constructor_initializer
  : ':' BASE '(' argument_list_opt ')'		{ R(); $$.expr			= $4.expr;	$$.tmpValue = 0;	}
  | ':' THIS '(' argument_list_opt ')'		{ R(); $$.expr			= $4.expr;	$$.tmpValue = 1; compilerError(ERR_NOT_SUPPORTED_YET,"'this' access in constructor initialization is not supported yet."); }
  ;
/* Widen from unsafe_opt STATIC to modifiers_opt */
/* This is now subsumed by constructor_declaration - delete
 * static_constructor_declaration
 *  : attributes_opt modifiers_opt IDENTIFIER '(' ')' block
 *  ;
 */
/* No longer needed after modification of static_constructor_declaration
 * unsafe_opt
 * : 
 * | UNSAFE
 * ;
 */
/* Widen from unsafe_opt to modifiers_opt */
destructor_declaration
  : attributes_opt modifiers_opt '~' IDENTIFIER '(' ')' block { R();
		gCurrentMethod = gCurrentAC->addDestructor(
			$1.attribute,	// Attributes
			$2.tmpValue,	// Modifier
			$4.text,		// Func Name
			$7.statement
		);
  }
  ;
operator_body
  : block			{ R(); $$.statement = $1.statement;	}
  | ';'				{ R(); $$.statement = NULL;			}
  ;
constructor_body /*** Added by JP - same as method_body ***/
  : block			{ R(); $$.statement = $1.statement;	}
  | ';'				{ R(); $$.statement = NULL;			}
  ;

/***** C.2.7 Structs *****/
struct_declaration
  : attributes_opt modifiers_opt STRUCT IDENTIFIER  { R(); 	gCurrentAC = CreateStruct(	$1.attribute, 
																					$2.tmpValue, 
																					$4.text
																				); 
													}
	struct_interfaces_opt struct_body comma_opt				{ R(); unuseNameSpace(); }
  ;
struct_interfaces_opt
  : /* Nothing */											{ R(); /* Do nothing */ 	}
  | struct_interfaces										{ R(); /* Do nothing */ 	}
  ;
struct_interfaces
  : ':' interface_type_list									{ R(); /* Do nothing */ 	}
  ;
struct_body
  : '{' struct_member_declarations_opt '}'					{ R(); /* Do nothing */	}
  ;
struct_member_declarations_opt
  : /* Nothing */											{ R(); /* Do nothing */	}
  | struct_member_declarations								{ R(); /* Do nothing */	}
  ;
struct_member_declarations
  : struct_member_declaration								{ R(); /* Do nothing */	}
  | struct_member_declarations struct_member_declaration	{ R(); /* Do nothing */	}
  ;
struct_member_declaration
  : constant_declaration									{ R(); /* Do nothing */	}
  | field_declaration										{ R(); /* Do nothing */	}
  | method_declaration										{ R(); /* Do nothing */	}
  | property_declaration									{ R(); /* Do nothing */	}
  | event_declaration										{ R(); /* Do nothing */	}
  | indexer_declaration										{ R(); /* Do nothing */	}
  | operator_declaration									{ R(); /* Do nothing */	}
  | constructor_declaration									{ R(); /* Do nothing */	}
/*  | static_constructor_declaration */
  | type_declaration										{ R(); /* Do nothing */	}
  ;

/***** C.2.8 Arrays *****/
array_initializer
  : '{' { GenerateInitList(); } variable_initializer_list_opt 	'}'	{ R(); PopInitList(); $$.expr = $3.expr; 	}
  ;
variable_initializer_list_opt
  : /* Nothing */											{ R(); $$.expr = NULL; 			}
  | variable_initializer_list opt_comma						{ R(); $$.expr = $1.expr; 		}
  ;
  
opt_comma	:	COMMA
			|	/* Do nothing */
			;
			
variable_initializer_list
  : variable_initializer									{ R(); $$.expr = getInitList()->addExpression($1.expr);	}
  | variable_initializer_list COMMA variable_initializer	{ R(); $$.expr = $1.expr->addExpression($3.expr); 		}
  ;

/***** C.2.9 Interfaces *****/
interface_declaration
  : attributes_opt modifiers_opt INTERFACE IDENTIFIER	{ R(); 	gCurrentAC = CreateInterface(	$1.attribute, 
																								$2.tmpValue, 
																								$4.text);
														}
														interface_base_opt interface_body comma_opt
														{ R();  unuseNameSpace(); }
  ;
interface_base_opt
  : /* Nothing */												{ R(); /* Do nothing */	}
  | interface_base												{ R(); /* Do nothing */	}
  ;
interface_base
  : ':' interface_type_list										{ R(); /* Do nothing */	}
  ;
interface_body
  : '{' interface_member_declarations_opt '}'					{ R(); /* Do nothing */	}
  ;
interface_member_declarations_opt
  : /* Nothing */												{ R(); /* Do nothing */	}
  | interface_member_declarations								{ R(); /* Do nothing */	}
  ;
interface_member_declarations
  : interface_member_declaration								{ R(); /* Do nothing */	}
  | interface_member_declarations interface_member_declaration	{ R(); /* Do nothing */	}
  ;
interface_member_declaration
  : interface_method_declaration								{ R(); /* Do nothing */	}
  | interface_property_declaration								{ R(); /* Do nothing */	}
  | interface_event_declaration									{ R(); /* Do nothing */	}
  | interface_indexer_declaration								{ R(); /* Do nothing */	}
  ;
/* inline return_type to avoid conflict with interface_property_declaration */
interface_method_declaration
  : attributes_opt new_opt type IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body { R();
		gCurrentMethod = gCurrentAC->addMethod(
			$1.attribute,	// Attributes
			$2.tmpValue,
			$4.text,		// Func Name
			$6.variable,	// Link list of variable
			$8.statement,	// Code
			$3.type			// Return value.
		);	
	}
  | attributes_opt new_opt VOID IDENTIFIER '(' formal_parameter_list_opt ')' interface_empty_body { R();
		gCurrentMethod = gCurrentAC->addMethod(
			$1.attribute,	// Attributes
			$2.tmpValue,
			$4.text,		// Func Name
			$6.variable,	// Link list of variable
			$8.statement,	// Code
			TypeObject::getTypeObject(TYPE_VOID)	// Return value.
		);
	}
  ;
new_opt
  : /* Nothing */		{ R(); $$.tmpValue = 0; 			}
  | NEW					{ R(); $$.tmpValue = ATTR_NEW; 	}
  ;
interface_property_declaration
  : attributes_opt new_opt type IDENTIFIER 
      ENTER_getset
    '{' interface_accessors '}'
      EXIT_getset								{ R(); gCurrentAC->addProperty($1.attribute, $2.tmpValue, $3.type, $4.text, $7.accessor);	}
  ;
interface_indexer_declaration
  : attributes_opt new_opt type THIS 
    LEFT_BRACKET formal_parameter_list RIGHT_BRACKET 
      ENTER_getset
    '{' interface_accessors '}'
      EXIT_getset								{ R(); $10.accessor->setAsIndexer($3.type, $6.variable); gCurrentAC->addProperty($1.attribute, $2.tmpValue, $10.accessor);	}
  ;

interface_accessors
  : attributes_opt GET interface_empty_body												{ R(); $$.accessor = CreateAccessor(CreateAccessor($1.attribute,NULL), NULL); }
  | attributes_opt SET interface_empty_body												{ R(); $$.accessor = CreateAccessor(NULL, CreateAccessor($1.attribute,NULL)); }
  | attributes_opt GET interface_empty_body attributes_opt SET interface_empty_body		{ R(); $$.accessor = CreateAccessor(CreateAccessor($1.attribute,NULL), CreateAccessor($4.attribute,NULL)); }
  | attributes_opt SET interface_empty_body attributes_opt GET interface_empty_body		{ R(); $$.accessor = CreateAccessor(CreateAccessor($4.attribute,NULL), CreateAccessor($1.attribute,NULL)); }
  ;
interface_event_declaration
  : attributes_opt new_opt EVENT type IDENTIFIER interface_empty_body					{ R(); compilerError(ERR_NOT_SUPPORTED,"event not supported"); }
  ;

/* mono seems to allow this */
interface_empty_body
  : ';'					{ R(); $$.statement = NULL;	}
  | '{' '}'				{ R(); $$.statement = NULL;	}
  ;

/***** C.2.10 Enums *****/
enum_declaration
  : attributes_opt modifiers_opt ENUM IDENTIFIER enum_base_opt { R();
		gCurrEnum = CreateEnum($1.attribute, $2.tmpValue, $4.text, $5.type);
  } enum_body comma_opt		{ R();
	// Do nothing.
  }
  ;
enum_base_opt
  : /* Nothing */											{ R(); $$.type = NULL;    }
  | enum_base												{ R(); $$.type = $1.type; }
  ;
enum_base
  : ':' integral_type										{ R(); $$.type = $2.type; }
  ;
enum_body
  : '{' enum_member_declarations_opt '}'					{ R(); /* Do nothing */ }
  | '{' enum_member_declarations COMMA '}'					{ R(); /* Do nothing */ }
  ;
enum_member_declarations_opt
  : /* Nothing */
  | enum_member_declarations								{ R(); /* Do nothing */ }
  ;
enum_member_declarations
  : enum_member_declaration									{ R(); /* Do nothing */ }
  | enum_member_declarations COMMA enum_member_declaration	{ R(); /* Do nothing */ }
  ;
enum_member_declaration
  : attributes_opt IDENTIFIER								{ R(); gCurrEnum->addEntry($1.attribute, $2.text, NULL); }
  | attributes_opt IDENTIFIER '=' constant_expression		{ R(); gCurrEnum->addEntry($1.attribute, $2.text, $4.expr); }
  ;

/***** C.2.11 Delegates *****/
delegate_declaration
  : attributes_opt modifiers_opt DELEGATE return_type IDENTIFIER opt_generic_fct '(' formal_parameter_list_opt ')' ';'
	{ R(); CreateDelegate($1.attribute, $2.tmpValue, $4.type, $5.text, $8.variable)->setGenericParam(); }
  ;

/***** C.2.12 Attributes *****/
attributes
  : attribute_sections						{ R(); $$.attribute = $1.attribute; }
  ;
attribute_sections
  : attribute_section						{ R(); $$.attribute = CreateAttributeWithChild($1.attribute); 		}
  | attribute_sections attribute_section	{ R(); $$.attribute = $1.attribute->addChildAttribute($2.attribute); }
  ;
attribute_section
  : ENTER_attrib LEFT_BRACKET attribute_target_specifier_opt attribute_list RIGHT_BRACKET EXIT_attrib
  { R();	$$.attribute = $4.attribute->setSpecifier($3.tmpValue); }
  | ENTER_attrib LEFT_BRACKET attribute_target_specifier_opt attribute_list COMMA RIGHT_BRACKET EXIT_attrib
  { R();	$$.attribute = $4.attribute->setSpecifier($3.tmpValue); }
  ;
attribute_target_specifier_opt
  : /* Nothing */				{ R(); $$.tmpValue = 0; 					}
  | attribute_target_specifier	{ R(); $$.tmpValue = $1.tmpValue; 		}
  ;
attribute_target_specifier
  : attribute_target ':'		{ R(); $$.tmpValue = $1.tmpValue; 		}
  ;
attribute_target
  : ASSEMBLY					{ R(); $$.tmpValue = ATTRB_ASSEMBLY ; 	}
  | FIELD						{ R(); $$.tmpValue = ATTRB_FIELD;		}
  | EVENT						{ R(); $$.tmpValue = ATTRB_EVENT;		}
  | METHOD						{ R(); $$.tmpValue = ATTRB_METHOD;		}
  | MODULE						{ R(); $$.tmpValue = ATTRB_MODULE;		}
  | PARAM						{ R(); $$.tmpValue = ATTRB_PARAM;		}
  | PROPERTY					{ R(); $$.tmpValue = ATTRB_PROPERTY;	}
  | RETURN						{ R(); $$.tmpValue = ATTRB_RETURN;		}
  | TYPE						{ R(); $$.tmpValue = ATTRB_TYPE;		}
  ;
attribute_list
  : attribute								{ R(); $$.attribute = CreateAttribute($1.type, $1.expr);				}
  | attribute_list COMMA attribute			{ R(); $$.attribute = $1.attribute->addAttribute($3.type, $3.expr); }
  ;
attribute
  : attribute_name attribute_arguments_opt	{ R(); $$.type = $1.type; $$.expr= $2.expr; }
  ;
attribute_arguments_opt
  : /* Nothing */				{ R(); $$.expr = NULL; 		}
  | attribute_arguments			{ R(); $$.expr = $1.expr ; 	}
  ;
attribute_name
  : type_name					{ R(); $$.type = $1.type; 	}
  ;
attribute_arguments
  : '(' expression_list_opt ')'	{ R(); $$.expr = $2.expr ; 	}
  ;



/** Dummy rules for those context-sensitive "keywords" **/
ENTER_attrib 
  : { R(); lex_enter_attrib(); 	/*Do nothing*/ }
  ;
EXIT_attrib 
  : { R(); lex_exit_attrib(); 	/*Do nothing*/ }
  ;
ENTER_accessor_decl 
  : { R(); lex_enter_accessor();	/*Do nothing*/ }
  ;
EXIT_accessor_decl
  : { R(); lex_exit_accessor();	/*Do nothing*/ }
  ;
ENTER_getset
  : { R(); lex_enter_getset();	/*Do nothing*/ }
  ;
EXIT_getset
  : { R(); lex_exit_getset();	/*Do nothing*/ }
  ;


%%

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
