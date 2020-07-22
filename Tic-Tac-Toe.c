#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<stdbool.h>
                            //external variables
char board[3][3]={{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char userMark, computerMark, temp;
int values[3][3]={{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
int firstTurn, row,column, rowPoints[3], columnPoints[3], diagonalPoints[2], nextPlay,move;

void gameBoard();       //function prototypes are added here
void start();
void calculateRowPoints();
void calculateColumnPoints();
void calculateDiagonal_1Points();
void calculateDiagonal_2Points();
void positionValues();
void correctMove(int size);
bool drawGame();
bool gameWon(char ch, char board[] [3]);
void nextMove();
void moveValidation();
void next();
void getRowColumn();
void clearBoard(int size);
void boardStructure();
void win();

int main(){
    system("COLOR 2");      //green colour
    boardStructure();
    printf("\n\tTIC TAC TOE!!\n\n");
    start();
    while(true){
        if (gameWon('X', board)){           //Stops game if X wins
            system("COLOR E");
            if(userMark=='X'){
                printf("\n\tCongratulations!! You have won.\n");
            }
            else{
                printf("\n\tSorry you lost!\n");
            }
            next(3);
            if(nextPlay==0){
                break;
            }
        }
        if(firstTurn==0){
            nextMove();
            gameBoard();
        }
        if (drawGame()){
            system("COLOR E");
            printf("\n\tNo winner!! Game is drawn.\n");      //Stops game if all spaces are occupied and there is no winner
            next(3);
            if(nextPlay==1)
                continue;
            if(nextPlay==0)
                break;
        }
        calculateRowPoints();
        calculateColumnPoints();
        calculateDiagonal_1Points();
        calculateDiagonal_2Points();
        positionValues();
        correctMove(3);
        gameBoard();
        if (gameWon('O', board)){           //Stops game if O wins
            system("COLOR E");      //light yellow colour
            if(userMark=='O')
                printf("\n\tCongratulations!! You have won.\n");
            else
                printf("\n\tSorry you lost!\n");
            next(3);
            if(nextPlay==0){
                break;
            }
        }
        if(firstTurn==1){
            nextMove();
            gameBoard();
        }
    }
    return 0;
}

void boardStructure(){      //design of the board
    printf("\n\n\n");
    printf("\t -------------------- \n");
    printf("\t|      |      |      |\n");
    printf("\t|  %c   |  %c   |  %c   |\n", board[0][0], board[0][1], board[0][2]);
    printf("\t|      |      |      |\n");
    printf("\t -------------------- \n");
    printf("\t|      |      |      |\n");
    printf("\t|  %c   |  %c   |  %c   |\n", board[1][0], board[1][1], board[1][2]);
    printf("\t|      |      |      |\n");
    printf("\t -------------------- \n");
    printf("\t|      |      |      |\n");
    printf("\t|  %c   |  %c   |  %c   |\n", board[2][0], board[2][1], board[2][2]);
    printf("\t|      |      |      |\n");
    printf("\t -------------------- \n");
}
void gameBoard(){       //displays the board
    system("cls");
    printf("\n\n");
    system("COLOR A");      //light green colour
    printf("\tUser mark     : %c\n", userMark);
    printf("\tComputer Mark : %c", computerMark);
    boardStructure();
}

void start(){
    printf("Enter who will take the first turn. (1 for user, 0 for computer): ");
    scanf("%d", &firstTurn);
    if(firstTurn==-1)
        exit(0);
    if(firstTurn!=0 && firstTurn!=1){
        system("COLOR C");
        printf("\nERROR!\n\n");
        start();
    }
    clearBoard(3);
    if(firstTurn == 1 ){
        printf("\nUser will take the first turn\n");
        nextMove();
        moveValidation();
        userMark = 'X';
        computerMark='O';
        board[row][column]=userMark;
    }
    if(firstTurn==0){
        srand(time(NULL));      //a random number for row and column is generated
        row=rand()%3;
        column=rand()%3;
        computerMark='X';
        userMark='O';
        board[row][column]=computerMark;
    }
    gameBoard();
}

void nextMove(){                //asks the player to play the next move
    printf("\n\tWhat is your move : ");
    scanf("%d", &move);
    if(move==-1){
            exit(0);
        }
    moveValidation();
    getRowColumn();
    board[row][column]=userMark;
}

void moveValidation(){         //validation of the  user move
    while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 && move != 6 && move != 7 && move != 8 && move != 9){
        system("COLOR C");      //red colour
        printf("\n\tERROR!\n");
        printf("\n\tWhat is your move : ");
        scanf("%d", &move);
    }
}

void getRowColumn(){        //getting the row and column for the board array from each square number
    switch(move){
        case 1 :    row=0; column=0; break;
        case 2 :    row=0; column=1; break;
        case 3 :    row=0; column=2; break;
        case 4 :    row=1; column=0; break;
        case 5 :    row=1; column=1; break;
        case 6 :    row=1; column=2; break;
        case 7 :    row=2; column=0; break;
        case 8 :    row=2; column=1; break;
        case 9 :    row=2; column=2; break;
    }
}

void calculateRowPoints(){       //calculating the points for each row
    for (int i = 0; i < 3; i++){
        if ((board[i][0] =='X'&& board[i][1]=='X'&& board[i][2]== ' ')||(board[i][0] =='X' && board[i][2]=='X'&&board[i][1]==' ') ||(board[i][1] =='X' && board[i][2]=='X' && board[i][0]==' ')){
            if(firstTurn==0)
                rowPoints[i]=1000;          //2 X's
            else
                rowPoints[i]=100;
        }
        else if ((board[i][0] =='O'&&board[i][1]=='O'&&board[i][2]==' ')||(board[i][0] =='O' && board[i][2]=='O'&&board[i][1]==' ') ||(board[i][1] =='O' && board[i][2]=='O' && board[i][0]==' ')){
            if(firstTurn==0)
                rowPoints[i]=100;           //2 O's
            else
                rowPoints[i]=1000;
        }
        else if ((board[i] [0] =='X' && board[i] [1]=='O') || (board[i] [0] =='X' && board[i] [2]=='O') ||(board[i] [1] =='X' && board[i] [0]=='O') || (board[i] [1] =='X' && board[i] [2]=='O') ||(board[i] [2] =='X' && board[i] [0]=='O') || (board[i] [2] =='X' && board[i] [1]=='O'))
            rowPoints[i]=0;             //when blocked
        else if(board[i][0]=='X' || board[i][1]=='X' || board[i][2]=='X'){      //1 X
            if(firstTurn==0)
                rowPoints[i]=10;
            else
                rowPoints[i]=9;
        }
        else if(board[i][0]=='O' || board[i][1]=='O' || board[i][2]=='O'){      //1 O
            if(firstTurn==0)
                rowPoints[i]=9;
            else
                rowPoints[i]=10;
        }
        else            //empty
            rowPoints[i]=1;
    }
}

void calculateColumnPoints(){                               //calculating the points for each column
    for (int i = 0; i < 3; i++){
        if ((board[0][i] =='X'&& board[1][i]=='X'&& board[2][i]==' ')||(board[0][i] =='X' && board[2][i]=='X'&&board[1][i]==' ') ||(board[1][i] =='X' && board[2][i]=='X' && board[0][i]==' ')){
            if(firstTurn==0)
                columnPoints[i]=1000;           //2 X's
            else
                columnPoints[i]=100;
        }
        else if ((board[0][i] =='O'&&board[1][i]=='O'&&board[2][i]==' ')||(board[0][i] =='O' && board[2][i]=='O'&&board[1][i]==' ') ||(board[1][i] =='O' && board[2][i]=='O' && board[0][i]==' ')){
            if(firstTurn==0)
                columnPoints[i]=100;            //2 O's
            else
                columnPoints[i]=1000;
        }
        else if ((board[0] [i] =='X' && board[1] [i]=='O') || (board[0] [i] =='X' && board[2] [i]=='O') ||(board[1] [i] =='X' && board[0] [i]=='O') || (board[1] [i] =='X' && board[2] [i]=='O') ||(board[2] [i] =='X' && board[0] [i]=='O') || (board[2] [i] =='X' && board[1] [i]=='O'))
                columnPoints[i]=0;                             //when blocked
        else if(board[0][i]=='X' || board[1][i]=='X' || board[2][i]=='X'){      //1 X
            if(firstTurn==0)
                columnPoints[i]=10;
            else
                columnPoints[i]=9;
        }
        else if(board[0][i]=='O' || board[1][i]=='O' || board[2][i]=='O'){      //1 O
            if(firstTurn==0)
                columnPoints[i]=9;
            else
                columnPoints[i]=10;
        }
        else{
            columnPoints[i]=1;          //empty
        }
    }
}

void calculateDiagonal_1Points(){                                   //calculating diagonal points for squares 1,5,9
    if ((board[0][0] =='X' && board[1][1]=='X'&& board[2][2]==' ') || (board[0][0] =='X' && board[2][2]=='X'&&board[1][1]==' ') ||(board[1][1] =='X' && board[2][2]=='X' && board[0][0]==' ')){
        if(firstTurn==0)
            diagonalPoints[0]=1000;         //z X's
        else
            diagonalPoints[0]=100;
    }
    else if ((board[0][0] =='O' && board[1][1]=='O' && board[2][2]==' ') || (board[0][0] =='O' && board[2][2]=='O' &&board[1][1]==' ') ||(board[1][1] =='O' && board[2][2]=='O' && board[0][0]==' ')){
        if(firstTurn==0)
            diagonalPoints[0]=100;          //2 O's
        else
            diagonalPoints[0]=1000;
    }
    else if ((board[0] [0] =='X' && board[1] [1]=='O') || (board[0] [0] =='X' && board[2] [2]=='O') ||(board[1] [1] =='X' && board[0] [0]=='O') || (board[1] [1] =='X' && board[2] [2]=='O') ||(board[2] [2] =='X' && board[0] [0]=='O') || (board[2] [2] =='X' && board[1] [1]=='O'))
        diagonalPoints[0]=0;                             //when blocked
    else if(board[0][0]=='X' || board[1][1]=='X' || board[2][2]=='X'){        //1 X
        if(firstTurn==0)
            diagonalPoints[0]=10;
        else
            diagonalPoints[0]=9;
    }
    else if(board[0][0]=='O' || board[1][1]=='O' || board[2][2]=='O'){       //1 O
        if(firstTurn==0)
            diagonalPoints[0]=9;
        else
            diagonalPoints[0]=10;
        }
    else{
        diagonalPoints[0]=1;          //empty
    }
}

void calculateDiagonal_2Points(){          //calculating diagonal points for squares 3,5,7
    if ((board[0][2] =='X' && board[1][1]=='X' && board[2][0]==' ') || (board[0][2] =='X' && board[2][0]=='X' && board[1][1]==' ') ||(board[1][1] =='X' && board[2][0]=='X' && board[0][2]==' ')){
        if(firstTurn==0)
            diagonalPoints[1]=1000;         //2 X's
        else
            diagonalPoints[1]=100;
    }
    else if ((board[0][2] =='O' && board[1][1]=='O' && board[2][0]==' ') || (board[0][2] =='O' && board[2][0]=='O' && board[1][1]==' ') || (board[1][1] =='O' && board[2][0]=='O' && board[0][2]==' ')){
        if(firstTurn==0)
            diagonalPoints[1]=100;          //2 O's
        else
            diagonalPoints[1]=1000;
    }
    else if ((board[0] [2] =='X' && board[1] [1]=='O') || (board[0] [2] =='X' && board[2] [0]=='O') ||(board[1] [1] =='X' && board[0] [2]=='O') || (board[1] [1] =='X' && board[2] [0]=='O') ||(board[2] [0] =='X' && board[0] [2]=='O') || (board[2] [0] =='X' && board[1] [1]=='O'))
        diagonalPoints[1]=0;                             //when blocked
    else if(board[0][2]=='X' || board[1][1]=='X' || board[2][0]=='X'){       //1 X
        if(firstTurn==0)
            diagonalPoints[1]=10;
        else
            diagonalPoints[1]=9;
    }
    else if(board[0][2]=='O' || board[1][1]=='O' || board[2][0]=='O'){      //1 O
        if(firstTurn==0)
            diagonalPoints[1]=9;
        else
            diagonalPoints[1]=10;
    }
    else
        diagonalPoints[1]=1;          //empty
}

void positionValues(){
    values[0][0] = rowPoints[0]+columnPoints[0]+diagonalPoints[0];  //points for each square
    values[0][1]=rowPoints[0]+columnPoints[1];
    values[0][2]=rowPoints[0]+columnPoints[2]+diagonalPoints[1];
    values[1][0]=rowPoints[1]+columnPoints[0];
    values[1][1]=rowPoints[1]+columnPoints[1]+diagonalPoints[0]+diagonalPoints[1];
    values[1][2]=rowPoints[1]+columnPoints[2];
    values[2][0]=rowPoints[2]+columnPoints[0]+diagonalPoints[1];
    values[2][1]=rowPoints[2]+columnPoints[1];
    values[2][2]=rowPoints[2]+columnPoints[2]+diagonalPoints[0];
}

void correctMove(int size){     //finding the intelligent move according to the points
    int max = values[0][0];
    int index1=0, index2=0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if(values[i][j] > max){
                max=values[i][j];
                index1=i;
                index2=j;
            }
        }
    }
    while(board[index1][index2]=='X' || board[index1][index2]=='O'){
        values[index1][index2]=0;
        max=values[0][0];
        index1=0;
        index2=0;
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(values[i][j] > max){
                    max=values[i][j];
                    index1=i;
                    index2=j;
                }
            }
        }
    }
    board[index1][index2]=computerMark;
}

bool gameWon(char ch, char board[] [3]){        //to check whether someone won the game
    for (int x = 0; x < 3; x++){
        if (ch == board[x] [0] && ch == board[x] [1] && ch == board[x] [2])
            return true;
    }
    for (int y = 0; y < 3; y++){
        if (ch == board[0] [y] && ch == board[1] [y] && ch == board[2] [y])
            return true;
    }
    if (ch == board[0] [0] && ch == board[1] [1] && ch == board[2] [2])
        return true;
    if (ch == board[0] [2] && ch == board[1] [1] && ch == board[2] [0])
        return true;
    return false;
}

bool drawGame(){         //to check whether the game is draw
    int count=0;
    for (int x = 0; x < 3; x++){
        for (int y = 0; y < 3; y++){
            if (board[x] [y] == 'X' || board[x][y]=='O')
                continue;
            else
                count++;
        }
    }
    if(count>1)
        return false;
    return true;
}

void next(){        //decides whether the user wants to play another game
    printf("\n\tDo you want to play again?(1 of Yes, 0 for No): ");
    scanf("%d", &nextPlay);
    if(nextPlay==-1)
        exit(0);
    if(nextPlay!=0 && nextPlay!=1){
        system("COLOR C");          //red colour
        printf("\n\tERROR!\n");
        next();
    }
    if(nextPlay==1){
        temp=userMark;
        userMark=computerMark;
        computerMark=temp;
        if(firstTurn==1)
            firstTurn=0;
        else
            firstTurn=1;
        clearBoard(3);
        if(userMark=='X'){
            system("cls");
            nextMove();
        }
        else{
            srand(time(NULL));
            row=rand()%3;
            column=rand()%3;
            board[row][column]=computerMark;
        }
        gameBoard();
    }
}

void clearBoard(int size){      //clears the array board
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++)
            board[i][j]=' ';
    }
}