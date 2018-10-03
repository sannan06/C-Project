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

	for(int i = 0; i < length; i++){
		if((i+3) > (length-1)){
			break;
		}
		if((values[i] == values[i+1]) && (values[i] == values[i+2])
			&& (values[i] == values[i+3])){
			return i;
		}
	}

	return -1;

}

int ToThePowerOf(int base, int exponent){

	int result = 1;
	for(int i = 0; i < exponent; i++){
		result *= base;
	}
	return result;
}

int BinaryToDecimal(int binary)
{
	int digits[100], i = 0, decimal = 0;
	
	while(binary > 0){
		digits[i] = binary % 10;
		binary = binary/10;
		i++;
	}

	for(int j = 0; j < i; j++){
		decimal += digits[j] * (ToThePowerOf(2, j));
	}

	return decimal;
}

double MedianAbility(double abilities[], int length)
{
	for(int i = 0; i < length; i++){
		for(int j = (i+1); j < length; j++){
			if(abilities[i] > abilities[j]){
				double temp = abilities[j];
				abilities[j] = abilities[i];
				abilities[i] = temp;
			}
		}
	}

	// for(int i = 0; i < length; i++){
	// 	printf("%f ", abilities[i]);
	// }

	// If odd number of array elements
	if(length%2){
		int index = (length+1)/2;
		return abilities[index-1];
	} else{
		double firstValue = abilities[(length/2)-1];
		double secondValue = abilities[length/2];
		return ((firstValue+secondValue)/2.0);
	}

}

void RemoveCharacter(char *name, int i, int length){

	for(int j = i; j < length; j++){
		name[j] = name[j+1];
	}

}

void RemoveSpaces(char *name)
{
	int length = strlen(name), i = 0, j = 0;
	
	// for(int i = 0; i < length; i++){
	// 	if((name[i] == ' ') && (name[i+1] == ' ')){
	// 		RemoveCharacter(name, i, length);
	// 		printf("%s\n", name);
	// 	}
	// }

	while(name[i] != '\0') {
		if((name[i] == ' ') && (name[i+1] == ' ')){
			RemoveCharacter(name, i, length);
			continue;
		}
		i++;		
	}

}

void InitialiseBoard(int board[MAX_SIZE][MAX_SIZE], int size)
{
	// Set everything within size = 0
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			board[i][j] = 0;
		}
	}

	if(size%2){
		int middle = size/2; 
		board[middle][middle] = 3;
	} else{
		int middle = size/2;
		board[middle][middle] = 3;
		board[middle][middle-1] = 3;
		board[middle-1][middle] = 3;
		board[middle-1][middle-1] = 3;
	}

}

void AddMoveToBoard(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int player, int *lastRow, int *lastCol)
{
	if(side == 'N'){
		for(int i = 0; i < size; i++){
			if(board[i][move] != 0){
				if(i == 0){
					*lastRow = -1;
					*lastCol = -1;
					break;
				} else{
					board[i-1][move] = player;
					*lastRow = (i-1);
					*lastCol = move;
					break;
				}
			} else if(i == (size-1)){
				board[i][move] = player;
				*lastRow = i;
				*lastCol = move;
				break;	
			}
		}
	} else if(side == 'S'){
		for(int i = (size-1); i >= 0; i--){
			// printf("Testing row: %d, column: %d\n", i, move);
			if(board[i][move] != 0){
				if(i == (size-1)){
					// printf("Working\n");
					*lastRow = -1;
					*lastCol = -1;
					break;
				} else{
					// printf("Entered here\n");
					board[i+1][move] = player;
					*lastRow = (i+1);
					*lastCol = move;
					break;
				}
			} else if(i == 0){
				// printf("Reached end of grid\n");
				board[i][move] = player;
				*lastRow = i;
				*lastCol = move;
				break;
			}
		}		
	} else if(side == 'E'){
		for(int i = (size - 1); i >= 0; i--){
			// printf("Testing row: %d, column: %d\n", move, i);
			if(board[move][i] != 0){
				if(i == (size-1)){
					*lastRow = -1;
					*lastCol = -1;
					break;
				} else{
					board[move][i+1] = player;
					*lastRow = move;
					*lastCol = (i+1);
					break;
				}
			} else if(i == 0){
				board[move][i] = player;
				*lastRow = move;
				*lastCol = i;
				break;
			}
		}
	} else{
		for(int i = 0; i < size; i++){
			if(board[move][i] != 0){
				if(i == 0){
					*lastCol = -1;
					*lastRow = -1;
					break;
				} else{
					board[move][i-1] = player;
					*lastRow = move;
					*lastCol = (i+1);
					break;
				}
			} else if(i == (size-1)){
				board[move][i] = player;
				*lastRow = move;
				*lastCol = i;
				break;
			}
		}
	}
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
