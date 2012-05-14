/**
*		Simple Unix Terminal Tic Tac Toe Game
*			using Minimax Algorithm for A.I
*
*		@author Mark Lacomber
*/										

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define EMPTY_CHAR ' '
#define WIN 1
#define DRAW 0
#define LOSE -1
#define UNFINISHED 2
#define N 3

#define VALID_SQUARE(square) (square >= 1 && square <= 9 ? TRUE : FALSE)
#define VALID_COORD(x,y) ((x < 0 || x > N-1 || y < 0 || y > N-1) ? FALSE : TRUE)
#define IS_EMPTY(square) (square == ' ' ? TRUE : FALSE)
#define OTHER(player) (player == PLAYER_X ? PLAYER_O : PLAYER_X)

void init_board(char board[N][N]);
void print_title();
int player_move(char board[N][N], char player);
int comp_move(char board[N][N], char player);
int enter_grid_move(char board[N][N], char player, int grid_num);
int enter_coord_move(char board[N][N], char player, int x, int y);
void print_board(char board[N][N]);
int check_winner(char board[N][N], char player);
int my_max(char board[N][N], char player);
int my_min(char board[N][N], char player);
void minimax(char board[N][N], char player);

int main()
{
	char board[N][N];

	char choice;
	// Choose X or O   (X goes first)
	print_title();

	while(TRUE)
	{
		printf("Would you like to play as X and go first? (y/n): ");
		scanf("%c", &choice);
		choice = tolower(choice);
		if(choice == 'y' || choice == 'n')
		{
			choice = (choice == 'y' ? PLAYER_X : PLAYER_O);
			break;
		}
		printf("Incorrect choice, Please Try Again\n");
	}

	// Initialize Board to empty chars
	init_board(board);

	print_board(board);

	// Main Loop
	while(TRUE)
	{
		if(choice == PLAYER_X)
		{
			if(player_move(board, PLAYER_X) == TRUE)
				break;
			if(comp_move(board, PLAYER_O) == TRUE)
				break;
		}else{
			if(comp_move(board, PLAYER_X) == TRUE)
				break;		
			if(player_move(board, PLAYER_O) == TRUE)
				break;
		}
	}

	return 0;
}

void init_board(char board[N][N])
{
	int i, j;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++ j){
			board[i][j] = EMPTY_CHAR;
		}
	}
}

void print_title()
{
	printf("\n***\t\tTicTacToe  (X's and O's)\t\t***\n\n");
}

int player_move(char board[N][N], char player)
{
	int grid_num;
	while(TRUE)
	{
		printf("Enter Square Number according to diagram: ");
		scanf("%d", &grid_num);
		printf("\t\t\tYOUR TURN\n");	
		if(enter_grid_move(board, player, grid_num) == 0)
			break;
		
		// Invalid move location
		printf("Incorrect choice, Try Again\n");
	}
		
	print_board(board);

	int play = check_winner(board, player);
	if(play == WIN){
		printf("\nCongratulations, you are the winner\n");
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

int comp_move(char board[N][N], char player)
{
	printf("\t\t\tCOMPUTER'S TURN\n");

	minimax(board, player);
	print_board(board);

	int play = check_winner(board, player);
	if(play == WIN)
	{
		printf("\nUnlucky, the computer wins\n");
		return TRUE;
	}else if(play == DRAW){
		printf("\nIt's a Draw\n");
		return TRUE;
	}
	return FALSE;
}

int enter_grid_move(char board[N][N], char player, int grid_num)
{
	if(VALID_SQUARE(grid_num) == FALSE)
		return TRUE;
	//Calculates corresponding i,j coordinates from grid number
	int i,j;
	if(grid_num < 4){
		j = 0;
	}else if(grid_num < 7){
		j = 1;
	}else{
		j = 2;
	}
	i = grid_num-1-(j*N);
	if(IS_EMPTY(board[i][j]) == FALSE)
		return TRUE;
	board[i][j] = player;

	return FALSE;
}

int enter_coord_move(char board[N][N], char player, int x, int y)
{
	// Check that coordinates are valid
	if(VALID_COORD(x,y) == FALSE)
		return TRUE;
	//if(board[x][y] != ' ')
	if(IS_EMPTY(board[x][y]) == FALSE)
		return TRUE;
	board[x][y] = player;

	return FALSE;
}

void print_board(char board[N][N])
{
	printf("\n");
	int i;
	for(i = 0; i < N; ++i)
	{
		printf("| %d | %d | %d |\t\t",1+(N*i),2+(N*i),3+(N*i));
		printf("| %c | %c | %c |\n",board[0][i], board[1][i], board[2][i]);
	}
	printf("\n");
}

int check_winner(char board[N][N], char player)
{
	int i, j;
	//Row and Column Checks
	for(i = 0; i < N; ++i)
	{
		//Row
		if(board[0][i] != EMPTY_CHAR)
		{
			if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
				return board[0][i] == player ? WIN : LOSE;
		}
		//Column
		if(board[i][0] != EMPTY_CHAR)
		{
			if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
				return board[i][0] == player ? WIN : LOSE;
		}
	}

	//Left Diagonal
	if(board[0][0] != EMPTY_CHAR && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
		return board[0][0] == player ? WIN : LOSE;
	}

	//Right Diagonal
	if(board[2][0] != EMPTY_CHAR && board[2][0] == board[1][1] && board[1][1] == board[0][2]){
		return board[2][0] == player ? WIN : LOSE;
	}

	//Check for draw
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] == EMPTY_CHAR)
				break;
		}
		if(board[i][j] == EMPTY_CHAR)
			break;
	}
	//Draw
	if(i*j==9)
		return DRAW;

	// Incomplete board
	return UNFINISHED;
}

int my_max(char board[N][N], char player)
{
	int result = check_winner(board, player);
	if(result != UNFINISHED)
		return result;

	int i, j, max;
	max = -10; // Only actually needs to be less than -1
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x, y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if(new_board[i][j] != ' '){
				printf("MY_MAX overlap\n");
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			if(temp > max)
				max = temp;
		}
	}
	return max;
}

int my_min(char board[N][N], char player)
{
	int result = check_winner(board, OTHER(player));
	if(result != UNFINISHED)
		return result;
	
	int i, j, min;
	min = 10; //Only actually has to be greater than 1
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x, y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if(new_board[i][j] != ' '){
				printf("MY_MIN overlap\n"); //Debug
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_max(new_board, OTHER(player));
			if(temp < min)
				min = temp;
		}
	}
	return min;
}

void minimax(char board[N][N], char player)
{
	int i, j, max, max_i, max_j;
	max = -10;
	for(i = 0; i < N; ++i)
	{
		for(j = 0; j < N; ++j)
		{
			if(board[i][j] != ' ')
				continue;
			char new_board[N][N];
			int x,y;
			for(x = 0; x < N; ++x)
			{
				for(y = 0; y < N; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			// Max(Computer) is always the top of minimax tree
			// Finish with max result of my_min() recursive loop
			if(temp > max)
			{
				max = temp;
				max_i = i;
				max_j = j;
			}
		}
	}	
	if(enter_coord_move(board, player, max_i, max_j) == TRUE){
		printf("Minimax - Error entering move\n"); //Debug
		exit(0);
	}
}
