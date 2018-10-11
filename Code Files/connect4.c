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
	} else if(side == 'W'){
		for(int i = 0; i < size; i++){
			if(board[move][i] != 0){
				if(i == 0){
					*lastCol = -1;
					*lastRow = -1;
					break;
				} else{
					board[move][i-1] = player;
					*lastRow = move;
					*lastCol = (i-1);
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

int DoPropogation(int board[MAX_SIZE][MAX_SIZE], int player, int rowIndex[], int colIndex[]){

	int j = 0;

	if(board[rowIndex[0]][colIndex[0]] == player){
		j++;
		if(board[rowIndex[1]][colIndex[1]] == player){
			j++;
			if(board[rowIndex[2]][colIndex[2]] == player){
				j++;
			}
		}
		if(board[rowIndex[3]][colIndex[3]] == player){
			j++;
			if(board[rowIndex[4]][colIndex[4]] == player){
				j++;
			}
		}
	}
	if(board[rowIndex[3]][colIndex[3]] == player){
		j++;
		if(board[rowIndex[4]][colIndex[4]] == player){
			j++;
			if(board[rowIndex[5]][colIndex[5]] == player){
				j++;
			}
		}
		if(board[rowIndex[0]][colIndex[0]] == player){
			j++;
			if(board[rowIndex[1]][colIndex[1]] == player){
				j++;
			}
		}
	}
	return j;
	}
	
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int counter = 0, i = 0, j = 0;
	int valuesToCheck[4];
	/* -------------- this is no longer broken :)))) ------------------------- */

	// Checking for available moves (DONE)
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			if(((i == 0) || (i == (size-1))) && (board[i][j] != 0)){
				counter++;
			} else if(((j == 0) || (j == (size-1))) && (board[i][j] != 0)){
				counter++;
			}
			}		
		}
	if(counter == (2*size + 2*(size-2))){
		return player;
	}
		
	// Row and Col positions for horizontal propogation
	int rowIndex1[] = {row,row,row,row,row,row};
	int colIndex1[] = {col+1, col+2, col+3, col-1, col-2, col-3};

	// Row and col positions for vertical propogation
	int rowIndex2[] = {row+1,row+2,row+3,row-1,row-2,row-3};
	int colIndex2[] = {col,col,col,col,col,col};

	// Row and col positions for diagonal propogation
	int rowIndex3[] = {row-1, row-2, row-3, row+1, row+2, row+3};
	int colIndex3[] = {col-1, col-2, col-3, col+1, col+2, col+3};


	// Carry out horizontal propogation
	j = DoPropogation(board, player, rowIndex1, colIndex1);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out vertical propogation
	j = DoPropogation(board, player, rowIndex2, colIndex2);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out positive diagonal propogation
	j = DoPropogation(board, player, rowIndex3, colIndex1);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out negative diagonal propogation
	j = DoPropogation(board, player, rowIndex3, colIndex3);
	if(j >= 3){
		return player;
	} else{
		return 0;
	}

}

void Append(char* s, char c) {
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

void GetDisplayBoardString(int board[MAX_SIZE][MAX_SIZE], int size, char *boardString)
{
	boardString[0] = '\0';
	// Create out the NORTH headings
		for(int i = 0; i < (size+4); i++){
			if((i == 0) || (i == 1) || (i == (size+2))){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, '-');
			} else if(i == (size+3)){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, '-');
				Append(boardString, '\n');
			} else if ((i > 1) && (i < (size+2))){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, 'N');
			}
		}

	// Create the north numbers
	for(int i = 0; i < (size+4); i++){
		if((i == 0) || (i == 1) || (i == (size+2))){
			// printf("%d, %d\n", strlen(boardString), i);
			Append(boardString, '-');
		} else if(i == (size+3)){
			// printf("%d, %d\n", strlen(boardString), i);
			Append(boardString, '-');
			Append(boardString, '\n');
		} else if ((i > 1) && (i < (size+2))){
			// printf("%d, %d\n", strlen(boardString), i);
			char numToStore = '0' + (i-2);
			Append(boardString, numToStore);
		}
	}

	// Create the middle shit
	int index;
	for(int j = 0; j < size; j++){
		for(int i = 0; i < (size+4); i++){
			if(i == 0){
				Append(boardString, 'W');
			} else if(i == 1){
				char numToStore = '0' + j;
				Append(boardString, numToStore);
			} else if(i == (size+2)){
				char numToStore = '0' + j;
				Append(boardString, numToStore);
			} else if(i == (size+3)){
				Append(boardString, 'E');
				Append(boardString, '\n');
			} else if ((i > 1) && (i < (size+2))){
				if(board[j][i-2] == 0){
					Append(boardString, '.');
				} else if(board[j][i-2] == 3){
					Append(boardString, '#');
				} else if(board[j][i-2] == 1){
					Append(boardString, 'X');
				} else if(board[j][i-2] == 2){
					Append(boardString, 'O');
				}
			}
		}
	}

	// Create the SOUTH numbers
	for(int i = 0; i < (size+4); i++){
		if((i == 0) || (i == 1) || (i == (size+2))){
			// printf("%d, %d\n", strlen(boardString), i);
			Append(boardString, '-');
		} else if(i == (size+3)){
			// printf("%d, %d\n", strlen(boardString), i);
			Append(boardString, '-');
			Append(boardString, '\n');
		} else if ((i > 1) && (i < (size+2))){
			// printf("%d, %d\n", strlen(boardString), i);
			char numToStore = '0' + (i-2);
			Append(boardString, numToStore);
		}
	}

	// Create the SOUTH headings
		for(int i = 0; i < (size+4); i++){
			if((i == 0) || (i == 1) || (i == (size+2))){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, '-');
			} else if(i == (size+3)){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, '-');
				Append(boardString, '\n');
			} else if ((i > 1) && (i < (size+2))){
				// printf("%d, %d\n", strlen(boardString), i);
				Append(boardString, 'S');
			}
		}
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
