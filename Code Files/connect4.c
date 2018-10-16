/* ENGGEN131 Project - C Project - 2018 */
/* Connect Four */

#include "connect4.h"

/*
*** Sannan Hafeez 634451649 ***
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

int DoPropogation(int board[MAX_SIZE][MAX_SIZE], int player, int rowIndex[], int colIndex[], int size){

	int j = 0;

	if((rowIndex[0] > 0) && (rowIndex[0] < size) && (colIndex[0] > 0) && (colIndex[0] < size)){
		// printf("About to access row: %d, col: %d\n", rowIndex[0], colIndex[0]);
		if(board[rowIndex[0]][colIndex[0]] == player){
			j++;
			if((rowIndex[1] > 0) && (rowIndex[1] < size) && (colIndex[1] > 0) && (colIndex[1] < size)){
				// printf("About to access row: %d, col: %d\n", rowIndex[1], colIndex[1]);
				if(board[rowIndex[1]][colIndex[1]] == player){
					j++;
					if((rowIndex[2] > 0) && (rowIndex[2] < size) && (colIndex[2] > 0) && (colIndex[2] < size)){
						// printf("About to access row: %d, col: %d\n", rowIndex[2], colIndex[2]);
						if(board[rowIndex[2]][colIndex[2]] == player){
							j++;
						}
					}
				}
				if((rowIndex[3] > 0) && (rowIndex[3] < size) && (colIndex[3] > 0) && (colIndex[3] < size)){
					// printf("About to access row: %d, col: %d\n", rowIndex[3], colIndex[3]);
					if(board[rowIndex[3]][colIndex[3]] == player){
						j++;
						if((rowIndex[4] > 0) && (rowIndex[4] < size) && (colIndex[4] > 0) && (colIndex[4] < size)){
							// printf("About to access row: %d, col: %d\n", rowIndex[4], colIndex[4]);
							if(board[rowIndex[4]][colIndex[4]] == player){
								j++;
							}
						}
					}	
				}
			}
		}
	}

	if((rowIndex[3] > 0) && (rowIndex[3] < size) && (colIndex[3] > 0) && (colIndex[3] < size)){
		if(board[rowIndex[3]][colIndex[3]] == player){
			j++;
			if((rowIndex[4] > 0) && (rowIndex[4] < size) && (colIndex[4] > 0) && (colIndex[4] < size)){
				if(board[rowIndex[4]][colIndex[4]] == player){
					j++;
					if((rowIndex[4] > 0) && (rowIndex[4] < size) && (colIndex[4] > 0) && (colIndex[4] < size)){
						// printf("About to access row: %d, col: %d\n", rowIndex[5], colIndex[5]);
						if(board[rowIndex[5]][colIndex[5]] == player){
							j++;
						}
					}
				}
			}
			if((rowIndex[0] > 0) && (rowIndex[0] < size) && (colIndex[0] > 0) && (colIndex[0] < size)){
				if(board[rowIndex[0]][colIndex[0]] == player){
					j++;
					if((rowIndex[0] > 0) && (rowIndex[0] < size) && (colIndex[0] > 0) && (colIndex[0] < size)){
						if(board[rowIndex[1]][colIndex[1]] == player){
							j++;
						}
					}
				}
			}
		}
	}
	return j;
}
	
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int counter = 0, i = 0, j = 0;

	// Checking for available moves
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
	j = DoPropogation(board, player, rowIndex1, colIndex1, size);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out vertical propogation
	j = DoPropogation(board, player, rowIndex2, colIndex2, size);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out positive diagonal propogation
	j = DoPropogation(board, player, rowIndex3, colIndex1, size);
	if(j >= 3){
		return player;
	} else{
		j = 0;
	}

	// Carry out negative diagonal propogation
	j = DoPropogation(board, player, rowIndex3, colIndex3, size);
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

	// Create the middle stuff
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

void GetHeadingAndMove(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move, int row, int col)
{
	// Drop a move in every possible place until it lands in the right place :))))
	int lastRow, lastCol;

	// Try North
	for(int i = 0; i < size; i++){
		AddMoveToBoard(board, size, 'N', i, player, &lastRow, &lastCol);
		if((lastRow == row) && (lastCol == col)){
			*side = 'N';
			*move = i;
			return;
		}
	}

	// Try South
	for(int i = 0; i < size; i++){
		AddMoveToBoard(board, size, 'S', i, player, &lastRow, &lastCol);
		if((lastRow == row) && (lastCol == col)){
			*side = 'S';
			*move = i;
			return;
		}
	}

	// Try East
	for(int i = 0; i < size; i++){
		AddMoveToBoard(board, size, 'E', i, player, &lastRow, &lastCol);
		if((lastRow == row) && (lastCol == col)){
			*side = 'E';
			*move = i;
			return;
		}
	}

	// Try West
	for(int i = 0; i < size; i++){
		AddMoveToBoard(board, size, 'W', i, player, &lastRow, &lastCol);
		if((lastRow == row) && (lastCol == col)){
			*side = 'W';
			*move = i;
			return;
		}
	}

}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{

	int notValid = 1, randHeading, chosenMove, result = 0;
	char chosenHeading;
	int tempBoard[MAX_SIZE][MAX_SIZE];
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			tempBoard[i][j] = board[i][j];
		}
	}

	// Loop through the board
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			// For every place there is no token
			if(board[i][j] == 0){
				// Set that position to player
				board[i][j] = player;
				// See if that would result in a win
				result = CheckGameOver(board, size, player, i, j);
				// Reset that position back to 0
				board[i][j] = 0;
				// If it would result in a win
				if(result == player){
					// See what side and move would be needed to make that move
					GetHeadingAndMove(board, size, player, side, move, i, j);
					// Then quit the function
					return;
				}
			}
		}
	}

	// for (int k = 0; k < size; k++) {
	// 	printf("   ");
	// 	for (int l = 0; l < size; l++) {
	// 		printf("%d ", tempBoard[k][l]);
	// 	}
	// 	printf("\n");
	// }

	/* ----------- Check for winning moves --------------- */
	// 1. Loop through board
	// 2. Consider points which are 0 (no token placed)
	// 3. If placing a token there can make 4 in a row, place it
	// 4. i.e. if there are 3 in a row adjacent to it

	// for(int i = 0; i < size; i++){
	// 	for(int j = 0; j < size; j++){
	// 		if(board[i][j] == 0){
	// 			tempBoard[i][j] = player;
	// 			result = CheckGameOver(tempBoard, size, player, i, j);
	// 			// printf("result: %d\n", result);
	// 			if(result != 0){
	// 				// printf("Found 3 in a row ");
	// 				// printf("in row %d column %d\n", i, j);
	// 				// for (int k = 0; k < size; k++) {
	// 				// 	printf("   ");
	// 				// 	for (int l = 0; l < size; l++) {
	// 				// 		printf("%d ", tempBoard[k][l]);
	// 				// 	}
	// 				// 	printf("\n");
	// 				// }
	// 				GetHeadingAndMove(board, size, player, side, move, i, j);
	// 				// printf("move will go in side %c move %d\n", *side, *move);
	// 				tempBoard[i][j] = 0;
	// 				return;
	// 			}
	// 			tempBoard[i][j] = 0;
	// 		}
	// 	}
	// }

	/* ------------- Return any valid, random move ------------- */
	while(notValid){
		// Pick a move number
		chosenMove = (rand() % size);
		randHeading = (rand() % 4);

		// Pick a heading, and check validity
		if(randHeading == 0){
			chosenHeading = 'N';
			if(board[0][chosenMove] == 0){
				notValid = 0;
			}
		} else if(randHeading == 1){
			chosenHeading = 'E';
			if(board[chosenMove][size-1] == 0){
				notValid = 0;
			}
		} else if(randHeading == 2){
			chosenHeading = 'S';
			if(board[size-1][chosenMove] == 0){
				notValid = 0;
			}
		} else{
			chosenHeading = 'W';
			if(board[chosenMove][0] == 0){
				notValid = 0;
			}
		}
	}

	// Set pointers to chosen thing
	*side = chosenHeading;
	*move = chosenMove;

}

void GetMoveBot2(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{
	// 1. Pick a random heading
	// 2. Pick a random number 
	// 3. If valid, make that move
	// 4. Otherwise, keep repeating 1 & 2 until valid

	int notValid = 1, randHeading, chosenMove;
	char chosenHeading;

	while(notValid){
		// Pick a move number
		chosenMove = (rand() % size);
		randHeading = (rand() % 4);

		// Pick a heading, and check validity
		if(randHeading == 0){
			chosenHeading = 'N';
			if(board[0][chosenMove] == 0){
				notValid = 0;
			}
		} else if(randHeading == 1){
			chosenHeading = 'E';
			if(board[chosenMove][size-1] == 0){
				notValid = 0;
			}
		} else if(randHeading == 2){
			chosenHeading = 'S';
			if(board[size-1][chosenMove] == 0){
				notValid = 0;
			}
		} else{
			chosenHeading = 'W';
			if(board[chosenMove][0] == 0){
				notValid = 0;
			}
		}
	}

	*side = chosenHeading;
	*move = chosenMove;

}
