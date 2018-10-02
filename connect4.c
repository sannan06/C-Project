/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** Please replace this comment with your name and ID number ***
This is the file that you will be submitting for marking
Complete the definitions of the functions in this file
DO NOT REMOVE ANY FUNCTION DEFINITIONS - they all must be present when you submit this file
*/

int SecondPlacePrize(int prize1, int prize2, int prize3)
{
	if((prize1 >= prize2) && (prize1 >= prize3)){
		if(prize2 >= prize3){
			return prize2;
		} else{
			return prize3;
		}
	} else if((prize2 >= prize1) && (prize2 >= prize3)){
		if(prize1 >= prize3){
			return prize1;
		} else{
			return prize3;
		}
	} else{
		if(prize2 >= prize1){
			return prize2;
		} else{
			return prize1;
		}
	}
}

int FourInARow(int values[], int length)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	return (values[0]+length)-(values[0]+length);
}

int BinaryToDecimal(int binary)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	return binary-binary;
}

double MedianAbility(double abilities[], int length)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	return (abilities[0]+length)-(abilities[0]+length);
}

void RemoveSpaces(char *name)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	name[0] = '\0';
}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	board[0][0] = size-size-1;
}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	*lastRow = 0;
	*lastCol = 0;
	board[0][0] = (size+side+move+player)-(size+side+move+player);
}

int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	return (board[0][0]+size+player+row+col)-(board[0][0]+size+player+row+col);
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	board[0][0] = size-size;
	boardString[0] = '\0';
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	*side = 'N';
	*move = 0;
	board[0][0] = (size+player)-(size+player);
}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	// This definition is WRONG.  To avoid compiler warnings, all of the input variables have been
	// referred to below.  Fix this function by *deleting this comment* and the code below, and
	// writing a correct definition.  If you do not attempt this task, leave this definition unchanged.
	*side = 'N';
	*move = 0;
	board[0][0] = (size+player)-(size+player);
}
