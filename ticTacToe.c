#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char board[3][3];//global variable for a 3x3 board
int choice; //variable to determine the game mode
int playerOneWins = 0, playerTwoWins = 0, computerWins = 0;//win tracker for each player type


void resetBoard(); //resets the board to an empty board
void printBoard(); //prints the game board
void player1Move(); //function that lets player 1 pick their spot
void player2Move(); //function that lets player 2 pick their spot
void computerMove();//function that lets the computer pick its spot
char checkWinner(); //function that checks to see if there is a winner
void printWinner(char winner); //prints the winner 
int freeSpaces(); //function to check how many free spaces are left on the board


int main()
{
    char winner = ' '; //winner gets reset to an empty character
    char repeat;//variable used for repeating the game

    do{
        printf("Enter 1 to face another player or 2 to verse the computer: ");
        scanf("%d",&choice);

        winner = ' '; //winner gets reset to an empty character
        resetBoard(); //board gets reset
        while (winner == ' ' && freeSpaces() != 0){ //while there's no winner and there isn't any free spaces

            // PLAYER VS PLAYER //

            if (choice == 1){
                printf("Player One Turn\n");

            }
            else {
                printf("User's Turn\n");
            }
            printBoard();

            player1Move();

            winner = checkWinner(); //checkWinner function gets called to see if player 1 won

            if (winner != ' ' || freeSpaces() == 0){ //if there is a winner or there is no more free spaces the game ends
                break;
            }

            if (choice == 1){
                printf("Player Two Turn\n");
                printBoard();
                player2Move();//player 2 chooses a spot on the board

                winner = checkWinner(); //the checkWinner function gets called to see if player 2 won
                if (winner != ' ' || freeSpaces() == 0){//if there is a winner or there is no more free spaces the game ends
                    break;
                }
            }

            // USER VS COMPUTER // 
            

            else if (choice == 2) {
                computerMove();

                winner = checkWinner();

                if (winner != ' ' || freeSpaces() == 0){
                    break;
                }
            }

        }

        //  THE GAME ENDS   //
        printBoard(); 
        printWinner(winner); //prints the winner if there is a winner
        printf("Would you like to play again? (y/n): ");//prompts the user to play again
        getchar();
        scanf("%c",&repeat);


    }while(repeat == 'y');

    //  OPENS A FILE THAT CONTAINS THE LEADERBOARD  //

    FILE * file = fopen("ticTacToe.txt","w"); //opens a file in write mode

    //    GETS PRINTED TO THE FILE    //

    fprintf(file,"*****LEADERBOARD*****\n");

    fprintf(file,"Player One Wins = %d\n",playerOneWins);
    fprintf(file,"Player Two Wins = %d\n",playerTwoWins);
    fprintf(file,"Computer Wins = %d\n",computerWins);

    //print statements that display how many wins have been accumulated 
    printf("Player One Wins: %d\n",playerOneWins);
    printf("Player Two Wins: %d\n",playerTwoWins);
    printf("Computer Wins: %3d\n",computerWins);
    

    return 0;
}

void resetBoard(){ //resets the board so every index contains an empty character
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 3;j++){
            board[i][j] = ' ';
        }
    }

}
void printBoard(){//prints whatever value is stored at that index
    for (int i = 0; i < 3;i++){
        printf(" %c | %c | %c\n",board[i][0],board[i][1],board[i][2]);
        printf("---|---|---\n");
    }


}
void player1Move(){
    int x, y;
    if (freeSpaces() != 0){//if there is a space on the board available
        do {//do-while loop that continues until the player has selected a valid spot
            //prompts the user to enter a row and column
            printf("Enter a row(1-3): ");
            scanf("%d",&x);
            printf("Enter a column(1-3): ");
            scanf("%d",&y);

            // checks to see if the input is within the range
            if ((x > 3 || x < 1) || (y > 3 || y < 0)){
                printf("Invalid move\n");
                break;
            }

            x--;
            y--;

            if (board[x][y] != ' '){ //if the spot on the array is not an open character, that spot is already taken
                printf("That spot is taken\n");
            }
            else if (board[x][y] == ' '){ //if the spot is open, an X is placed and the loop breaks
                board[x][y] = 'X';
                break;
            }


        }while (board[x][y] == ' ');
    }
}

void player2Move(){ //SAME CONCEPT AS player1Move but places an 'O' instead of an 'X'
    int x, y;
    if (freeSpaces() != 0){
        do {
            printf("Enter a row(1-3): ");
            scanf("%d",&x);
            printf("Enter a column(1-3): ");
            scanf("%d",&y);

            if ((x > 3 || x < 1) || (y > 3 || y < 0)){
                printf("Invalid move\n");
                break;
            }

            x--;
            y--;

            if (board[x][y] != ' '){
                printf("That spot is taken\n");
            }
            else if (board[x][y] == ' '){
                board[x][y] = 'O';
                break;
            }


        }while (board[x][y] == ' ');
    }
}

void computerMove(){
    int x,y;
    srand(time(0)); 

    if (freeSpaces() != 0){//if there is space available on the board the computer generates a random number
        do {//generates a random x and y from 0-2 while the space isn't occupied 
            x = rand() % 3;
            y = rand() % 3;
        }while(board[x][y] != ' ');

        board[x][y] = 'O'; //the board gets marked with an O
    }
    else {
        printWinner(' ');
    }

}


char checkWinner(){
    for (int i = 0; i < 3;i++){
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]){ //if there are 3 elements that contain the same value horizontally, there is a winner
            return board[i][0];
        }
    }

    for (int i = 0; i < 3;i++){
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]){//if there are 3 elements that contain the same value vertically, there is a winner
            return board[0][i];
        }
    }

    //      CHECKING THE HORIZONTALS FOR A WINNER     //
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }

    if (board[2][0] == board[1][1] && board[2][0] == board[0][2]){
        return board[2][0];
    }
    //else return an empty character symbolizing there is no winner
    return ' ';

}
void printWinner(char winner){
    if (choice == 1){//if it is Player vs Player
        if (winner == 'X'){
            printf("Player One Wins\n");
            playerOneWins++;//playerOneWins gets incremented
        }
        else if (winner == 'O'){
            printf("Player Two Wins!\n");
            playerTwoWins++;//playerTwoWins gets incremented
        }
        else {
            printf("The game is a draw\n");
        }
    }
    else if (choice == 2){//if it's User vs Computer
        if (winner == 'X'){
            printf("\nYOU WIN!!\n");
            playerOneWins++;
        }
        else if (winner == 'O'){
            printf("COMPUTER WINS!!\n");
            computerWins++;
        }
        else {
            printf("The game is a draw\n");
        }
    }

}

int freeSpaces(){
    int freeSpace = 9;//there are 9 free spaces on the board so freeSpace is initialized with a value of 9
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 3;j++){
            if (board[i][j] != ' '){//if the board at that index isn't an empty space, freeSpace gets decremented
                freeSpace--;
            }
        }
    }
    return freeSpace;//returns the number of free spaces left
}