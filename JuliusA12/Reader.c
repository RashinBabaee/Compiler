/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2023
* Author: Rashin Babaee, 041043836 .. Sewmini Jayasinghe, 041057012
* Assignment 12
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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Jan 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main code for Reader (.c)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

 /*
 ***********************************************************
 * Function name: readerCreate
 * Purpose: Creates the buffer reader according to capacity, increment
	 factor and operational mode ('f', 'a', 'm')
 * Author: Svillen Ranev / Paulo Sousa
 * History/Versions: S22
 * Called functions: calloc(), malloc()
 * Parameters:
 *   size = initial capacity
 *   increment = increment factor
 *   mode = operational mode
 * Return value: bPointer (pointer to reader)
 * Algorithm: Allocation of memory according to inicial (default) values.
 * TODO ......................................................
 *	- Adjust datatypes for your LANGUAGE.
 *   - Use defensive programming
 *	- Check boundary conditions
 *	- Check flags.
 *************************************************************
 */

ReaderPointer readerCreate(rs_intg size, rs_intg increment, rs_intg mode) {
	ReaderPointer readerPointer;

	/* TO_DO: Defensive programming */
	
	/* TO_DO: Adjust the values according to parameters */
	if (increment == 0) {
		mode = MODE_FIXED;
	}
	if (size == 0) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;

	}
	//char mode = readerPointer->mode;
	if (mode != 'F' && mode != 'M' && mode != 'A') {
		return NULL;
	}
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return NULL;
	readerPointer->content = (rs_char*)malloc(size);
	/* TO_DO: Defensive programming */
	/* TO_DO: Initialize the histogram */
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* TO_DO: Initialize flags */
	/* TO_DO: The created flag must be signalized as EMP */
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, rs_char ch) {
	rs_char* tempReader = NULL;
	rs_intg newSize = 0;
	/* TO_DO: Defensive programming: check buffer and valid char (increment numReaderErrors) */
	if (readerPointer == NULL) {
		return  NULL;
	}
	if (ch < 0 || ch >= NCHAR) {
		readerPointer->numReaderErrors++;
		return readerPointer;
	}
	/* TO_DO: Reset Realocation */
	/* TO_DO: Test the inclusion of chars */
	if (readerPointer->position.wrte * (rs_intg)sizeof(rs_char) < readerPointer->size) {
		/* TO_DO: This buffer is NOT full */
		readerPointer->flags = readerPointer->flags &~ FUL;
	}
	else {
		/* TO_DO: Reset Full flag */
		readerPointer->flags = readerPointer->flags | FUL;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* TO_DO: Adjust new size */
			 newSize = readerPointer->size+readerPointer->increment*(rs_intg)sizeof(rs_char);
			/* TO_DO: Defensive programming */
			break;
		case MODE_MULTI:
			/* TO_DO: Adjust new size */
			newSize = readerPointer->size * readerPointer->increment*(rs_intg)sizeof(rs_char);
			/* TO_DO: Defensive programming */
			break;
		default:
			return NULL;
		}
		/* TO_DO: New reader allocation */
		if (newSize <= readerPointer->size) {
			return NULL;
		}
		tempReader = realloc(readerPointer->content,newSize);
		/* TO_DO: Defensive programming */
		if (tempReader == NULL) {
			return NULL;
		}
		/* TO_DO: Check Relocation */
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
		readerPointer->flags = readerPointer->flags | REL;
		
	}
	/* TO_DO: Add the char */
	//printf("%d ", ch);
	readerPointer->content[readerPointer->position.wrte++] = ch;
	readerPointer->flags = readerPointer->flags & ~EMP;
	readerPointer->flags = readerPointer->flags & ~FUL;
	/* TO_DO: Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerClear(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	readerPointer->position.read = 0;
	readerPointer->position.wrte = 0;
	readerPointer->position.mark = 0;
	readerPointer->flags = 0b01010000;
	/* TO_DO: Adjust flags original */
	return RS_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerFree(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (!readerPointer)
		return RS_FALSE;
	/* TO_DO: Free pointers */
	return RS_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerIsFull(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Check flag if buffer is FUL */
	return readerPointer ->flags & 0b10000000;

}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerIsEmpty(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Check flag if buffer is EMP */
	return readerPointer->flags & 0b01000000;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerSetMark(ReaderPointer const readerPointer, rs_intg mark) {
	/* TO_DO: Defensive programming */
	if (!readerPointer || mark<0 || mark > readerPointer->position.wrte)
		return RS_FALSE;
	/* TO_DO: Adjust mark */
	readerPointer->position.mark = mark;
	return RS_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerPrint(ReaderPointer const readerPointer) {
	rs_intg cont = 0;
	rs_char c;
	/* TO_DO: Defensive programming (including invalid chars) */
	c = readerGetChar(readerPointer);
	/* TO_DO: Check flag if buffer EOB has achieved */
	while (cont < readerPointer->position.wrte) {
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	rs_intg size = 0;
	rs_char c;
	/* TO_DO: Defensive programming */
	c = (rs_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* TO_DO: Defensive programming */
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerRecover(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	readerPointer->position.read = 0;
	//readerPointer->position.wrte = 0;
	//readerPointer->position.mark = 0;
	/* TO_DO: Recover positions */
	return RS_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerRetract(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */

	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	readerPointer->position.read--;
	/* TO_DO: Retract (return 1 pos read) */
	return RS_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_boln readerRestore(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	readerPointer->position.read  = readerGetPosMark(readerPointer);

	/* TO_DO: Restore positions (read/mark) */
	return RS_TRUE;
}



/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_char readerGetChar(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Check condition to read/wrte */
	/* TO_DO: Set EOB flag */
	/* TO_DO: Reset EOB flag */
	//printf("**** %d *****", readerPointer->content[readerPointer->position.read]);

	if (readerPointer->position.read < readerPointer->position.wrte-1) {
		readerPointer->flags = readerPointer->flags & 0b11101111;
		return readerPointer->content[readerPointer->position.read++];
	}
	else {
		readerPointer->flags = readerPointer->flags | 0b00010000;
		return '\0';
	}
	
	//printf("%d ", readerPointer ->position.wrte);
	
	
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_char* readerGetContent(ReaderPointer const readerPointer, rs_intg pos) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  NULL;

	}
	if (pos < 0) {
		return  NULL;
	}
	/* TO_DO: Return content (string) */
	return &readerPointer->content [pos];

}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetPosRead(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return read */
	return readerPointer->position.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetPosWrte(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return wrte */
	return readerPointer->position.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetPosMark(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return mark */
	return readerPointer->position.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetSize(ReaderPointer const readerPointer) {

	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return size */

	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetInc(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return increment */

	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerGetMode(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return mode */

	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
* TO_DO:
*   - Use defensive programming
*	- Check boundary conditions
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Return flags */
	return readerPointer->flags;
}


/*
***********************************************************
* Function name: readerShowStat
* Purpose: Returns the number of chars used.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerShowStat(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	if (readerPointer == NULL) {
		return  READER_ERROR;
	}
	/* TO_DO: Updates the histogram */
	rs_intg unique = 0;
	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] != 0) {
			unique++;
		}
	}
	return unique;
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
* TO_DO:
*   - Use defensive programming
*	- Adjust for your LANGUAGE.
*************************************************************
*/
rs_intg readerNumErrors(ReaderPointer const readerPointer) {
	/* TO_DO: Defensive programming */
	//Check(ReaderPointer);
	
	if (readerPointer == NULL) {
		return  -1;
	}
	/* TO_DO: return the number of errors */
	return readerPointer->numReaderErrors;
}