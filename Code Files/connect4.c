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
 	double prizes[3];
	prizes[0] = prize1;
	prizes[1] = prize2;
	prizes[2] = prize3;
	return (int) MedianAbility(prizes, 3);
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

int DoPropogation(int board[MAX_SIZE][MAX_SIZE], int player, int row, int col, int size, int changeInX, int changeInY)
{
	int counter = 0;
	int i = row;
	int j = col;

	while(board[i][j] == player){
		if(board[i][j] == player){
			counter++;
		}
		i += changeInX;
		j += changeInY;
	}

	return counter;
}
	
int CheckGameOver(int board[MAX_SIZE][MAX_SIZE], int size, int player, int row, int col)
{
	int counter = 0;
	int rightCounter;
	int leftCounter;

	/* -------- HORIZONTALLY ------- */
	// Propogate horizontally to the right
	rightCounter = DoPropogation(board, player, row, col, size, 0, 1);
	// Propogate horizontally to the left
	leftCounter = DoPropogation(board, player, row, col, size, 0, -1);
	counter = rightCounter + leftCounter;

	if(counter >= 5){
		return player;
	} else{
		counter = 0;
		rightCounter = 0;
		leftCounter = 0;
	}

	/* -------- VERTICAL ---------- */
	// Propogate verically to the bottom
	rightCounter = DoPropogation(board, player, row, col, size, 1, 0);
	// Propogate horizontally to the top
	leftCounter = DoPropogation(board, player, row, col, size, -1, 0);
	counter = rightCounter + leftCounter;

	if(counter >= 5){
		return player;
	} else{
		counter = 0;
		rightCounter = 0;
		leftCounter = 0;
	}

	/* -------- POSITIVE DIAGONAL ---------- */
	// Propogate diagonal to the upper-right
	rightCounter = DoPropogation(board, player, row, col, size, -1, 1);
	// Propogate digonally to the bottom-left
	leftCounter = DoPropogation(board, player, row, col, size, 1, -1);
	counter = rightCounter + leftCounter;

	if(counter >= 5){
		return player;
	} else{
		counter = 0;
		rightCounter = 0;
		leftCounter = 0;
	}

	/* -------- NEGTAIVE DIAGONAL ---------- */
	// Propogate diagonal to the upper-left
	rightCounter = DoPropogation(board, player, row, col, size, -1, -1);
	// Propogate digonally to the bottom-right
	leftCounter = DoPropogation(board, player, row, col, size, 1, 1);
	counter = rightCounter + leftCounter;

	if(counter >= 5){
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

	*move = -1;

}

void GetFinalPosition(int board[MAX_SIZE][MAX_SIZE], int size, char side, int move, int *lastRow, int *lastCol){
	if(side == 'N'){
		for(int i = 0; i < size; i++){
			if(board[i][move] != 0){
				if(i == 0){
					*lastRow = -1;
					*lastCol = -1;
					break;
				} else{
					*lastRow = (i-1);
					*lastCol = move;
					break;
				}
			} else if(i == (size-1)){
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
					*lastRow = (i+1);
					*lastCol = move;
					break;
				}
			} else if(i == 0){
				// printf("Reached end of grid\n");
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
					*lastRow = move;
					*lastCol = (i+1);
					break;
				}
			} else if(i == 0){
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
					*lastRow = move;
					*lastCol = (i-1);
					break;
				}
			} else if(i == (size-1)){
				*lastRow = move;
				*lastCol = i;
				break;
			}
		}
	}
}

void GetMoveBot1(int board[MAX_SIZE][MAX_SIZE], int size, int player, char *side, int *move)
{

	int notValid = 1, randHeading, chosenMove, result = 0;
	char chosenHeading;
	int lastRow = 0;
	int lastCol = 0;
	int checkWin = 0;

	// Consider all North moves
	for(int i = 0; i < size; i++){
		GetFinalPosition(board, size, 'N', i, &lastRow, &lastCol);
		if((lastRow != -1) && (lastCol != -1)){
			board[lastRow][lastCol] = player;
			checkWin = CheckGameOver(board, size, player, lastRow, lastCol);
			board[lastRow][lastCol] = 0;
			if(checkWin == player){
				*side = 'N';
				*move = i;
				printf("a move in side: 'N' and move: %d will win\n", i);
				return;
			}
		}
	}

	// Consider all South moves
	for(int i = 0; i < size; i++){
		GetFinalPosition(board, size, 'S', i, &lastRow, &lastCol);
		if((lastRow != -1) && (lastCol != -1)){
			board[lastRow][lastCol] = player;
			checkWin = CheckGameOver(board, size, player, lastRow, lastCol);
			board[lastRow][lastCol] = 0;
			if(checkWin == player){
				*side = 'S';
				*move = i;
				printf("a move in side: 'S' and move: %d will win\n", i);
				return;
			}
		}
	}

	// Consider all East moves
	for(int i = 0; i < size; i++){
		GetFinalPosition(board, size, 'E', i, &lastRow, &lastCol);
		if((lastRow != -1) && (lastCol != -1)){
			board[lastRow][lastCol] = player;
			checkWin = CheckGameOver(board, size, player, lastRow, lastCol);
			board[lastRow][lastCol] = 0;
			if(checkWin == player){
				*side = 'E';
				*move = i;
				printf("a move in side: 'E' and move: %d will win\n", i);
				return;
			}
		}
	}

	// Consider all West moves
	for(int i = 0; i < size; i++){
		GetFinalPosition(board, size, 'W', i, &lastRow, &lastCol);
		if((lastRow != -1) && (lastCol != -1)){
			board[lastRow][lastCol] = player;
			checkWin = CheckGameOver(board, size, player, lastRow, lastCol);
			board[lastRow][lastCol] = 0;
			if(checkWin == player){
				*side = 'W';
				*move = i;
				printf("a move in side: 'W' and move: %d will win\n", i);
				return;
			}
		}
	}


	// int tempBoard[MAX_SIZE][MAX_SIZE];
	// for(int i = 0; i < size; i++){
	// 	for(int j = 0; j < size; j++){
	// 		tempBoard[i][j] = board[i][j];
	// 	}
	// }

	// Loop through the board

	
	// for(int i = 0; i < size; i++){
	// 	for(int j = 0; j < size; j++){
	// 		// For every place there is no token
	// 		if(board[i][j] == 0){
	// 			// Set that position to player
	// 			board[i][j] = player;
	// 			// See if that would result in a win
	// 			result = CheckGameOver(board, size, player, i, j);
	// 			// Reset that position back to 0
	// 			board[i][j] = 0;
	// 			// If it would result in a win
	// 			if(result == player){
	// 				// See what side and move would be needed to make that move
	// 				GetHeadingAndMove(board, size, player, side, move, i, j);
	// 				printf("move: %d", *move);
	// 				// Check to see if that move was available
	// 				if(*move != -1){
	// 					// Then quit the function
	// 					return;
	// 				}
	// 			}
	// 		}
	// 	}
	// }


	// for (int k = 0; k < size; k++) {
	// 	printf("   ");~
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
