#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 1
#define O 2

int playerDidWin(int player, int board[6][7], int winningMoves[8]){
	// Check rows
	int i,j;
	for (i = 0; i < 6; i++){
		for (j = 0; j < 4; j++){
			if (board[i][j] == player && board[i][j+1] == player && board[i][j+2] == player && board[i][j+3] == player){
				winningMoves[0] = i;
				winningMoves[1] = j;
				winningMoves[2] = i;
				winningMoves[3] = j+1;
				winningMoves[4] = i;
				winningMoves[5] = j+2;
				winningMoves[6] = i;
				winningMoves[7] = j+3;
				return 1;
			}
		}
	}

	// Check cols
	for (j = 0; j < 7; j++){
		for (i = 0; i < 3; i++){
			if (board[i][j] == player && board[i+1][j] == player && board[i+2][j] == player && board[i+3][j] == player){
				winningMoves[0] = i;
				winningMoves[1] = j;
				winningMoves[2] = i+1;
				winningMoves[3] = j;
				winningMoves[4] = i+2;
				winningMoves[5] = j;
				winningMoves[6] = i+3;
				winningMoves[7] = j;
				return 1;
			}
		}
	}

	// Check diags
	for (i = 0; i < 3; i++){
		for (j = 0; j < 4; j++){
			if (board[i][j] == player && board[i+1][j+1] == player && board[i+2][j+2] == player && board[i+3][j+3] == player){
				winningMoves[0] = i;
				winningMoves[1] = j;
				winningMoves[2] = i+1;
				winningMoves[3] = j+1;
				winningMoves[4] = i+2;
				winningMoves[5] = j+2;
				winningMoves[6] = i+3;
				winningMoves[7] = j+3;
				return 1;
			}
		}
	}
	for (i = 5; i >= 3; i--){
		for (j = 6; j >= 3; j--){
			if (board[i][j] == player && board[i-1][j-1] == player && board[i-2][j-2] == player && board[i-3][j-3] == player){
				winningMoves[0] = i;
				winningMoves[1] = j;
				winningMoves[2] = i-1;
				winningMoves[3] = j-1;
				winningMoves[4] = i-2;
				winningMoves[5] = j-2;
				winningMoves[6] = i-3;
				winningMoves[7] = j-3;
				return 1;
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[]){
	int bufferSize = 256;
	char buffer[bufferSize];
	char* lines = (char*)malloc(1);
	int lineCount = 0;
	while (fgets(buffer, bufferSize, stdin) != NULL){
        if (*(buffer+strlen(buffer)-1) == '\n'){
            *(buffer+strlen(buffer)-1) = '\0';
        }
        lineCount++;
        lines = (char*)realloc(lines, bufferSize*lineCount*sizeof(char));
        strcpy(lines + (lineCount-1)*bufferSize, buffer);
    }

    int board[6][7];
    int columnHeights[7] = {};
    int winningMoves[8] = {};

    int movesX[lineCount];
    int movesO[lineCount];
    int i,j;

    for (i = 0; i < 6; i++){
    	for (j = 0; j < 7; j++){
    		board[i][j] = 0;
    	}
    }

    for (i = 0; i < lineCount; i++){

    	int xmove = *(lines + bufferSize*i)-'A';
    	movesX[i] = xmove;

    	int h = columnHeights[xmove];
    	board[ h ][ xmove ] = X;


    	columnHeights[xmove]++;
    	int Xwon = playerDidWin(X, board, winningMoves);

    	if (Xwon){
    		printf("X won at move %d (with %c%d %c%d %c%d %c%d)\n", i+1, winningMoves[1]+'A', winningMoves[0]+1, winningMoves[3]+'A', winningMoves[2]+1, winningMoves[5]+'A', winningMoves[4]+1, winningMoves[7]+'A', winningMoves[6]+1);
    		return 0;
    	}

    	int omove = *(lines + bufferSize*i + 3)-'a';
    	movesO[i] = omove;
    	h = columnHeights[omove];
    	board[ h ][ omove ] = O;
    	columnHeights[omove]++;
    	int Owon = playerDidWin(O, board, winningMoves);

    	if (Owon){
    		printf("O won at move %d (with %c%d %c%d %c%d %c%d)\n", i+1, winningMoves[1]+'a', winningMoves[0]+1, winningMoves[3]+'a', winningMoves[2]+1, winningMoves[5]+'a', winningMoves[4]+1, winningMoves[7]+'a', winningMoves[6]+1);
    		return 0;
    	}
    }

	return 0;
}