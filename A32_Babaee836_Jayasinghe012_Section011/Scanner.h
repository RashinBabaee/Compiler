/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Rashin Babaee, 041043836 .. Sewmini Jayasinghe, 041057012
* Assignment 22
* Professors: Paulo Sousa
************************************************************

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@                                                               @@@@
@@          /       ==============================        /          @@
@         ////           @@       @@ #@                  ////         @
@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @
@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @
@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @
@     (((((/)))((    ------------------------------    ((((./////*    @
@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @
@    ///// / /////   ==============================  * ////* / ////   @
@     ///// ///// ((                               (( ///// /////     @
@    ((((   / , (((((                             (((((  //   /(((    @
@    (((((((/ . (((((                          (((((* / (((((((       @
@      (((((( //((((/((((                    *((((/((((/( (((((/      @
@       .//,   * /   (((((                   (((((  ///    .//.       @
@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @
@         //////// ,// ((( /////,     ////// ((( //  /////// *        @
@            (((((((((,// * /////     /////   (//(((((((((            @
@            ((((((((((((/////         //.///  (((((((((((.           @
@                   (///////// //(   (//.//////////                   @
@                  (/////////             //////////                  @
@                                                                     @
@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@
@@@@                                                               @@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Sep 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 7   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	VARID_T,	/*  2: */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/*  10: Run-time error token */
	INL_T,		/* 11: Integer Litaral */
	FLL_T,		/* 12: Floating point literal*/
	SEOF_T,		/* 13: Source end-of-file token */
	ROP_T,		/* 14: Relational Operator token*/
	OP_T,		/* 15: Operator token*/
	EQ_T,		/* 16: Equal token*/
	MOP_T,		/* 17: Mathematical operator token*/
	LOP_T,		/* 18: Logical operator token*/
	VOP_T,		/* 19: Variable operator token*/
	CMA_T		/* 20: Comma token*/


};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	rs_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	rs_intg intValue;						/* integer literal attribute (value) */
	rs_intg keywordIndex;					/* keyword index in the keyword table */
	rs_intg contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	rs_real floatValue;					/* floating-point literal attribute (value) */
	rs_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	rs_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	rs_byte flags;			/* Flags information */
	union {
		rs_intg intValue;				/* Integer value */
		rs_real floatValue;			/* Float value */
		rs_char* stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	rs_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '.'
#define CHRCOL3 ':'
#define CHRCOL4 '"'
#define CHRCOL7 '~'

/* These constants will be used on VID / MID function */
#define MNIDPREFIX ':'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Illegal state */
#define ESNR	6		/* Error state with no retract */
#define ESWR	7		/* Error state with retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 10

/* TO_DO: Transition table - type of states defined in separate table */

static rs_intg transitionTable[][TABLE_COLUMNS] = {

	/*[a-z], [0-9],    .,    :,    ", SEOF, ~, other, [A-Z], ' ',
	   L(0),  D(1), U(2), M(3), Q(4), E(5),  O(6) */

	{     1,   11, ESNR, 9,    4, ESNR,    9,  15,  15, 9}, // S0: NOAS
	{     1,     1,    8,    2, ESWR, 10,    8,  8,  1,  8}, // S1: NOAS (funcID)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS, FS,  FS}, // S2: ASNR (funcID MNID_T)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS, FS ,  FS}, // S3: 
	{     4,     4,    4,    4,    5, ESWR,    4,  4 ,  4,  4}, // S4: NOAS (funcSL)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S5: ASNR (funcSL SL)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S6: ASNR (ES)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S7: ASWR (ER)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S8: ASWR (funcID VARID_T)
	{     3,     3,    9,   9,    9, 16,    9,  9,  3,  16}, // S9: NOAS(funcKEY)	
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S10: ASNR (SEOF)
	{     12,   11, 13, ESNR,    12,  ESWR,  12,  12,  12,  12},  // S11: NOAS (funcIL)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S12: ASWR (funcIL INL_T)
	{     14,   13, ESNR, ESNR,    14,  ESWR,  14,  14,  14,  14},  // S13: NOAS (funcIL)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S14: ASWR (funcIL FLL_T)
	{     15,   16, ESNR, ESNR,    16,  17,  16,  16,  15,  16},  // S15: NOAS (funcKEY)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S16: ASWR (funcKEY)
	{    FS,    FS,   FS,   FS,   FS,   FS,   FS,  FS,  FS,  FS}, // S17: ASNR (funcKEY)
};

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static rs_intg stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	FSNR, /* 06 (Err1 - no retract) */
	FSWR,  /* 07 (Err2 - retract) */
	FSWR,	/*08*/
	NOFS,/*09*/
	FSNR,/*10*/
	NOFS,//11
	FSWR,//12
	NULL,//13
	FSWR,//14
	NULL,//15
	FSWR,//16
	FSNR,//17

};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
rs_intg startScanner(ReaderPointer psc_buf);
Token tokenizer(rs_void);
static rs_intg nextClass(rs_char c);				/* character class function */
static rs_intg nextState(rs_intg, rs_char);		/* state machine function */
rs_void printToken(Token t);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(rs_char* lexeme);

/* Declare accepting states functions */
Token funcSL	(rs_char lexeme[]);
Token funcID	(rs_char lexeme[]);
Token funcKEY	(rs_char lexeme[]);
Token funcErr	(rs_char lexeme[]);
Token funcIL	(rs_char lexeme[]);
Token funcFL    (rs_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] - Methods */
	funcKEY,	/* KEY  [03] - Keywords */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] - String Literal */
	funcErr,	/* ERR1 [06] - No retract */
	funcErr,		/* ERR2 [07] - Retract */
	funcID,//8
	NULL,//9
	funcKEY,//10
	NULL,//11
	funcIL,//12
	NULL,//13
	funcFL,//14
	NULL,//15
	funcKEY,//16
	funcKEY//17
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 29

/* TO_DO: Define the list of keywords */
static rs_char* keywordTable[KWT_SIZE] = {
	"=", /*0*/
	"+", /*1*/
	"-",/*2*/
	"*",/*3*/
	"/",/*4*/
	"%",/*5*/
	"<",/*6*/
	">",/*7*/
	"<=",/*8*/
	">=",/*9*/
	"==",/*10*/
	"!=",/*11*/
	"Do",/*12*/
	"While",/*13*/
	"End",/*14*/
	"If",/*15*/
	"ElseIf",/*16*/
	"Else",/*17*/
	"Int",/*18*/
	"Float",/*19*/
	"::",/*20*/
	"String",/*21*/
	"Then",/*22*/
	"&&",/*23*/
	"||",/*24*/
	"^",/*25*/
	"!",/*26*/
	"Function",/*27*/
	"Begin"/*28*/
	
};

/* About indentation (useful for positional languages (ex: Python, Cobol) */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rs_char indentationCharType;
	rs_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
rs_intg numScannerErrors;

#endif
