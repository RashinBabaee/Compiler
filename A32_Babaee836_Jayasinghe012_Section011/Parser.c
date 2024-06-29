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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
 /* TO_DO: This is the function to start the parser - check your program definition */

rs_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}

rs_boln isKeyword( char* tokenAttribute) {
	if (lookahead.code != KW_T) {
		return RS_FALSE;
	}
	if (tokenAttribute == NULL) {
		return RS_FALSE;
	}
	if (strcmp(keywordTable[lookahead.attribute.codeType], tokenAttribute) != 0){
		return RS_FALSE;
	}
	else {
		return RS_TRUE;
	}
}

rs_void matchToken2(rs_intg tokenCode, char* tokenAttribute) {
	//printf("**************lookahead %d : %d %s\n", lookahead.code, lookahead.attribute.codeType, keywordTable[lookahead.attribute.codeType]);
	//printf("**************%d : %s\n", tokenCode, tokenAttribute);
	rs_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:

		if (tokenAttribute != NULL && strcmp (keywordTable[lookahead.attribute.codeType] , tokenAttribute) != 0)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	int eos = 0;
	if (lookahead.code == 9 && lookahead.code != tokenCode) {
		eos = 1;
		matchFlag = 1;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		if (eos == 0) {
			}
		
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
	if (eos == 1) {
		matchToken2(tokenCode, tokenAttribute);
	}
}
/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
 /* TO_DO: This is the main code for match - check your definition */


rs_void matchToken(rs_intg tokenCode, rs_intg tokenAttribute) {
	//printf("**************lookahead %d : %d\n", lookahead.code, lookahead.attribute.codeType);
	//printf("**************%d : %d\n", tokenCode, tokenAttribute);
	rs_intg matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	int eos = 0;
	if (lookahead.code == 9 && lookahead.code != tokenCode) {
		
		eos = 1;
		matchFlag = 1;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		if (eos == 0) {
			}
		
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
	if (eos == 1) {
		matchToken2(tokenCode, tokenAttribute);
	}
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
 /* TO_DO: This is the function to handler error - adjust basically datatypes */
rs_void syncErrorHandler(rs_intg syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
 /* TO_DO: This is the function to error printing - adjust basically datatypes */
rs_void printError() {
	Token t = lookahead;
	//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	//printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;

	case VARID_T:
		printf("VARID_T\n");
		break;
	case RTE_T:
		printf("RTE_T\n");
		break;
	case INL_T:
		printf("INL_T\n");
		break;
	case FLL_T:
		printf("FLL_T\n");
		break;
	case ROP_T:
		printf("ROP_T\n");
		break;
	case OP_T:
		printf("OP_T\n");
		break;
	case EQ_T:
		printf("EQ_T\n");
		break;
	case MOP_T:
		printf("MOP_T\n");
		break;
	case LOP_T:
		printf("LOP_T\n");
		break;
	case VOP_T:
		printf("VOP_T\n");
		break;
	case CMA_T:
		printf("CMA_T\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
rs_void program() {
	switch (lookahead.code) {
	case KW_T:
		matchToken2(KW_T, "Function");
		matchToken(MNID_T, NO_ATTR);
		matchToken(LPR_T, NO_ATTR);
		matchToken(RPR_T, NO_ATTR);
		matchToken2(KW_T, "Begin");
		//matchToken(EOS_T,NO_ATTR);
		codeSession();
		matchToken2(KW_T, "End");
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LBR_T, NO_ATTR);
			dataSession();
			codeSession();
			matchToken(RBR_T, NO_ATTR);
			break;
		}
		else {
			;
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */
rs_void dataSession() {
	matchToken(KW_T, KW_data);
	matchToken(LBR_T, NO_ATTR);
	optVarListDeclarations();
	matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Data Session parsed");
}

/*
 ************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_real), KW_T (KW_string)}.
 ***********************************************************
 */
rs_void optVarListDeclarations() {
	switch (lookahead.code) {
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
rs_void codeSession() {
	//matchToken(KW_T, KW_code);
	//matchToken(LBR_T, NO_ATTR);
	optionalStatements();
	//matchToken(RBR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

rs_void operation() {
	
	//matchToken(MOP_T, NO_ATTR);
	switch (lookahead.code) {
	case LPR_T:
		matchToken(LPR_T, NO_ATTR);
		if (lookahead.code == RPR_T) {
			matchToken(RPR_T, NO_ATTR);
			break;
		}
		operation();
		matchToken(RPR_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FLL_T:
		matchToken(FLL_T, NO_ATTR);
		break;
	case VARID_T:
		matchToken(VARID_T, NO_ATTR);
		break;
	}
	

	switch (lookahead.code) {
	case MOP_T:
		matchToken(MOP_T, NO_ATTR);
		operation();
		break;
	case ROP_T:
		matchToken(ROP_T, NO_ATTR);
		operation();
		break;
	case LOP_T:
		matchToken(LOP_T, NO_ATTR);
		operation();
		break;
	case OP_T:
		matchToken(OP_T, NO_ATTR);
		operation();
		break;
	case EQ_T:
		matchToken(EQ_T, NO_ATTR);
		operation();
		break;
	case CMA_T:
		matchToken(CMA_T, NO_ATTR);
		operation();
	}
	
	printf("%s%s\n", STR_LANGNAME, ": Mathematical Operation parsed");
}

rs_void operationList() {
	operation();
	if (lookahead.code==CMA_T) {
		matchToken(CMA_T, NO_ATTR);
		operation();
	}
}

/* TO_DO: Continue the development (all non-terminal functions) */

rs_void variableList() {
	
	if (lookahead.code == VOP_T) {
		matchToken(VOP_T, NO_ATTR);
		matchToken2(KW_T, NULL);
	}
	if (lookahead.code == CMA_T) {
		matchToken(CMA_T, NO_ATTR);
		matchToken(VARID_T, NO_ATTR);
		variableList();
	}

}

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
rs_void optionalStatements() {
	switch (lookahead.code) {
	case VARID_T:
		
		matchToken(VARID_T, NO_ATTR);
		switch (lookahead.code) {

		case VOP_T:
			variableList();
			//matchToken(VOP_T, NO_ATTR);
			//matchToken2(KW_T, NULL);
			//matchToken(EOS_T, NO_ATTR);
			optionalStatements();
			break;
		case EQ_T:
			
			matchToken(EQ_T, NO_ATTR);
			operation();
			//matchToken(EOS_T, NO_ATTR);
			optionalStatements();
			break;
		
		default:
			;//Empty
		}
		break;
	case MNID_T:
		matchToken(MNID_T, NO_ATTR);

		operationList();
	//	matchToken(EOS_T, NO_ATTR);
		optionalStatements();
			break;
	case KW_T:
		if (isKeyword("While")) {
			matchToken2(KW_T, "While");
			operation();
			matchToken2(KW_T, "Do");
			optionalStatements();
			matchToken2(KW_T, "End");
			optionalStatements();
		}
		if (isKeyword("If")) {
			matchToken2(KW_T, "If");
			operation();
			matchToken2(KW_T, "Then");
			optionalStatements();
			if (isKeyword("Else")) {
				matchToken2(KW_T, "Else");
				optionalStatements();
			}
			matchToken2(KW_T, "End");
			optionalStatements();
		}
		break;
		
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
/*rs_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}*/

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
/*rs_void statementsPrime() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			statements();
			break;
		}
	default:
		; //empty string
	}
}*/

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
/*rs_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		default:
			printError();
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}*/

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
rs_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableList();
	matchToken(RPR_T, NO_ATTR);
	//matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
rs_void outputVariableList() {
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}
