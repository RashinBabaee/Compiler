/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: TO_DO
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
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern rs_intg line;
extern Token tokenizer();
extern rs_char* keywordTable[];
rs_intg syntaxErrorNumber = 0;

#define STR_LANGNAME	"RS"
#define LANG_WRTE		"println:"
#define LANG_READ		"input:"
#define LANG_MAIN		"Function main:"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_Equals = 0,

	KW_data,
	KW_code,
	KW_Int,
	KW_Real,
	KW_String,
	KW_If,
	KW_Then,
	KW_Else,
	KW_While,
	KW_Do,
	KW_End,
	KW_ElseIf,
	KW_Float,
	KW_Function,
	KW_Begin
};

/* Function definitions */
rs_void startParser();
rs_void matchToken(rs_intg, rs_intg);
rs_void syncErrorHandler(rs_intg);
rs_void printError();

/* TO_DO: Place ALL non-terminal function declarations */
rs_void codeSession();
rs_void dataSession();
rs_void optVarListDeclarations();
rs_void optionalStatements();
rs_void outputStatement();
rs_void outputVariableList();
rs_void program();
//rs_void statement();
//rs_void statements();
rs_void statementsPrime();

#endif
