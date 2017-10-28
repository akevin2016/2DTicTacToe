#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void pVp();
void pVc();
void initializeBoard(char [3][3]);
void displayBoard(char [3][3]);
void doTurn(char [3][3], int);
int checkWin(char [3][3]);
int checkTie(char [3][3]);
void printPvPWinner(int);
void printPvCWinner(int);
void input(char [3][3], int);
void waldo(char [3][3]);
int checkAvailable(char [3][3], int, int);
int checkThrees(char [3][3], char);
void doThrees(char [3][3], int);

int main()
{
    int gamemode;
    char repeat;
    int counter = 0;

    srand((unsigned)time(0));

    do
    {
        puts("Choose a gamemode:");
        puts("1) Player vs Player");
        puts("2) Player vs Computer");

        do
        {
            scanf("%i", &gamemode);
            switch(gamemode)
            {
                case 1:
                    pVp();
                    repeat = 'N';
                    break;

                case 2:
                    if(counter == 0)
                    {
                        puts("Waking up Waldo, the not-so-friendly neighborhood bot...");
                        puts("And I'm awake!");
                        counter++;
                    }
                    pVc();
                    repeat = 'N';
                    break;

                default:
                    puts("Choose a valid option!");
                    repeat = 'Y';
                    break;
            }
        }while(repeat == 'Y');

        puts("Play again?");
        getchar();
        repeat = getchar();

    }while(repeat == 'Y' || repeat == 'y');

    return 0;
}

void pVp()
{
    char board[3][3];
    int playerWin = 0;
    int turn = 1;

    initializeBoard(board);
    displayBoard(board);

    do
    {
        if(turn == 1)
        {
            puts("Player 1:");
            doTurn(board, turn);
            turn = 2;
        }
        else if(turn == 2)
        {
            puts("Player 2:");
            doTurn(board, turn);
            turn = 1;
        }

        playerWin = checkWin(board);

        if(playerWin == 0)
        {
            playerWin = checkTie(board);
        }

    }
    while(playerWin == 0);

    printPvPWinner(playerWin);
}

void pVc()
{
    char board[3][3];
    int turnNum = 1;
    int playerWin = 0;

    initializeBoard(board);
    displayBoard(board);

    do
    {
        if(turnNum % 2 == 1)
        {
            puts("You:");
            doTurn(board, turnNum % 2);
            turnNum++;
        }
        else if(turnNum % 2 == 0)
        {
            puts("Me:");
            waldo(board);
            turnNum++;
        }
        playerWin = checkWin(board);

        if(!playerWin)
        {
            playerWin = checkTie(board);
        }
    }
    while(!playerWin);

    printPvCWinner(playerWin);
}

void initializeBoard(char myBoard[3][3])
{
    int row;
    int column;
    for(row = 0; row < 3; row++)
    {
        for(column = 0; column < 3; column++)
        {
            myBoard[row][column] = ' ';
        }
    }
}

void displayBoard(char myBoard[3][3])
{
    int row;
    int column;
    puts("+---+");
    for(row = 0; row < 3; row++)
    {
        printf("|");
        for(column = 0; column < 3; column++)
        {
            printf("%c", myBoard[row][column]);
        }
        puts("|");
    }
    puts("+---+");
}

void doTurn(char myBoard[3][3], int player)
{
    input(myBoard, player);

    displayBoard(myBoard);
}

int checkWin(char myBoard[3][3])
{
    int row;
    int column;

    for(row = 0; row < 3; row++)
    {
        if(myBoard[row][0] == myBoard[row][1] && myBoard[row][1] == myBoard[row][2] && myBoard[row][0] != ' ')
        {
            if(myBoard[row][0] == 'X')
            {
                return 1;
            }
            else if(myBoard[row][0] == 'O')
            {
                return 2;
            }
        }
    }

    for(column = 0; column < 3; column++)
    {
        if(myBoard[0][column]== myBoard[1][column] && myBoard[1][column] == myBoard[2][column] && myBoard[0][column] != ' ')
        {
            if(myBoard[0][column] == 'X')
            {
                return 1;
            }
            else if(myBoard[0][column] == 'O')
            {
                return 2;
            }
        }
    }

    if(myBoard[0][0] == myBoard[1][1] && myBoard[1][1] == myBoard[2][2] && myBoard[0][0] != ' ')
    {
        if(myBoard[1][1] == 'X')
        {
            return 1;
        }
        else if(myBoard[1][1] == 'O')
        {
            return 2;
        }
    }

    if(myBoard[0][2] == myBoard[1][1] && myBoard[1][1] == myBoard[2][0] && myBoard[0][2] != ' ')
    {
        if(myBoard[1][1] == 'X')
        {
            return 1;
        }
        else if(myBoard[1][1] == 'O')
        {
            return 2;
        }
    }

    return 0;
}

int checkTie(char myBoard[3][3])
{
    int row;
    int column;
    int tie = -1;

    for(row = 0; row < 3; row++)
    {
        for(column = 0; column < 3; column++)
        {
            if(myBoard[row][column] == ' ')
            {
                tie = 0;
            }
        }
    }
    return tie;
}

void printPvPWinner(int winner)
{
    if(winner == 1 || winner == 2)
    {
        printf("\nPlayer %i won!\n", winner);
    }
    else
    {
        printf("\nIt's a tie!\n");
    }
}

void printPvCWinner(int winner)
{
    if(winner == 1)
    {
        puts("\nI call hacks!!... Oh, wait...");
    }
    else if(winner == 2)
    {
        puts("Hah! Take that, slimy human!");
    }
    else
    {
        puts("Hey, at least I didn't lose and you didn't win, so I'm good.");
        puts("Even though it's a tie.");
    }
}

void input(char myBoard[3][3], int player)
{
    int row;
    int column;
    char repeat;
    do
    {
        do
        {
            printf("Row (from 1 to 3): ");
            scanf("%i", &row);
            row--;
            if(row < 0 || row > 2)
            {
                repeat = 'Y';
                puts("Choose a possible row number!");
            }
            else
            {
                repeat = 'N';
            }
        }while(repeat == 'Y');

        do
        {
            printf("Column (from 1 to 3): ");
            scanf("%i", &column);
            column--;
            if(column < 0 || column > 2)
            {
                repeat = 'Y';
                puts("Choose a possible column number!");
            }
            else
            {
                repeat = 'N';
            }
        }while(repeat == 'Y');

        if(myBoard[row][column] == 'X' || myBoard[row][column] == 'O')
        {
            repeat = 'Y';
            puts("You need to choose a free space!");
        }

    }while(repeat == 'Y');

    puts("\n\n");

    if(player == 1)
    {
        myBoard[row][column] = 'X';
    }

    else if(player == 2)
    {
        myBoard[row][column] = 'O';
    }

}

void waldo(char myBoard[3][3])
{
    int moveDone = 0;
    int row = 0;
    int column = 0;
    int choice;
    char repeat = 'N';
    int winPlay = checkThrees(myBoard, 'O');
    int risk = checkThrees(myBoard, 'X');
    /*--------------------------------------------------------------------------------------------------------*/

    if(winPlay % 10 != 0)
    {                                                                                               // WIN
        doThrees(myBoard, winPlay);
        moveDone = 1;
    }

    /*--------------------------------------------------------------------------------------------------------*/

    if(risk % 10 != 0 && moveDone == 0)
    {
        doThrees(myBoard, risk);                                                                    // RISK
        if(rand() % 2 == 0 && checkThrees(myBoard, 'X') % 10 == 0)
        {
            puts("Thought you could win?");
        }
        else if(checkThrees(myBoard, 'X') % 10 == 0)
        {
            puts("You aren't that smart, are you? At least compared to me.");
        }
        else
        {
            puts("How?!");
        }
        moveDone = 1;
    }

    /*--------------------------------------------------------------------------------------------------------*/

    if(myBoard[1][1] == ' ' && moveDone == 0)
    {
        myBoard[1][1] = 'O';                                                                        // CENTER
        puts("Do you even tic-tac-toe, bro?");
        moveDone = 1;
    }
    /*--------------------------------------------------------------------------------------------------------*/
    if(moveDone == 0)
    {
        if(myBoard[0][1] == 'X' && myBoard[1][2] == 'X' && checkAvailable(myBoard, 0, 2) == 1 && moveDone == 0)
        {
            if(checkAvailable(myBoard, 0, 0) == 1 && checkAvailable(myBoard, 2, 2) == 1)
            {
                myBoard[0][2] = 'O';
                moveDone = 1;
            }
        }
        if(myBoard[1][2] == 'X' && myBoard[2][1] == 'X' && checkAvailable(myBoard, 2, 2) == 1 && moveDone == 0)
        {
            if(checkAvailable(myBoard, 0, 2) == 1 && checkAvailable(myBoard, 2, 0) == 1)
            {
                myBoard[2][2] = 'O';
                moveDone = 1;
            }
        }
        if(myBoard[2][1] == 'X' && myBoard[1][0] == 'X' && checkAvailable(myBoard, 2, 0) == 1 && moveDone == 0)
        {
            if(checkAvailable(myBoard, 2, 2) == 1 && checkAvailable(myBoard, 0, 0) == 1)
            {
                myBoard[2][0] = 'O';
                moveDone = 1;
            }
        }
        if(myBoard[1][0] == 'X' && myBoard[0][1] == 'X' && checkAvailable(myBoard, 0, 0) == 1 && moveDone == 0)
        {
            if(checkAvailable(myBoard, 2, 0) == 1 && checkAvailable(myBoard, 0, 2) == 1)
            {
                myBoard[0][0] = 'O';
                moveDone = 1;
            }
        }
    }
    /*--------------------------------------------------------------------------------------------------------*/
    if((myBoard[0][0] == ' ' || myBoard[0][2] == ' ' || myBoard[2][0] == ' ' || myBoard[2][2] == ' ') && moveDone == 0)
    {
        int available[4] = {1, 1, 1, 1};
        available[0] = checkAvailable(myBoard, 0, 0);
        available[1] = checkAvailable(myBoard, 0, 2);
        available[2] = checkAvailable(myBoard, 2, 0);
        available[3] = checkAvailable(myBoard, 2, 2);
        do
        {
            choice = rand() % 4;
            if(available[choice] == 1)
            {
                switch(choice)
                {
                    case 0:
                        myBoard[0][0] = 'O';
                        break;
                    case 1:
                        myBoard[0][2] = 'O';                                                        // CORNERS
                        break;
                    case 2:
                        myBoard[2][0] = 'O';
                        break;
                    case 3:
                        myBoard[2][2] = 'O';
                        break;
                    default:
                        puts("It's Stuart's fault I don't work well, not mine.");
                }
                repeat = 'N';
            }
            else
            {
                repeat = 'Y';
            }
        }while(repeat == 'Y');
        moveDone = 1;
        if(rand() % 2 == 0)
        {
            puts("Corners are cooler. Cooler than you.");
        }
        else
        {
            puts("Why should you stand in a corner if you're cold? Press enter for the answer.");
            getchar();
            getchar();
            puts("Because no one wants to look at your ugly face.");
        }
    }

    /*--------------------------------------------------------------------------------------------------------*/
    if(moveDone == 0)
    {
        int success = 0;
        while(success == 0)
        {
            row = rand() % 3;
            column = rand() % 3;
            if(checkAvailable(myBoard, row, column) == 1)                                           // RANDOM
            {
                myBoard[row][column] = 'O';
                success = 1;
            }
        }
    }
    /*--------------------------------------------------------------------------------------------------------*/
    displayBoard(myBoard);
}

int checkAvailable(char myBoard[3][3], int r, int c)
{
    if(myBoard[r][c] == ' ' && r < 3 && c < 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkThrees(char myBoard[3][3], char check)
{
    int itemNum = 0;
    int row = 0;
    int column = 0;
    for(row = 0; row < 3; row++)
    {
        for(column = 0; column < 3; column++)
        {
            if(myBoard[row][column] == check)
            {
                if(myBoard[row][column + 1] == check && column + 1 < 3)
                {

                    itemNum = 1;
                    if(checkAvailable(myBoard, row, column + 2) == 1)
                    {
                        break;
                    }
                    else if(checkAvailable(myBoard, row, column - 1) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                if(myBoard[row + 1][column] == check && itemNum == 0 && row + 1 < 3)
                {
                    itemNum = 2;
                    if(checkAvailable(myBoard, row + 2, column) == 1)
                    {
                        break;
                    }
                    else if(checkAvailable(myBoard, row - 1, column) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                if(myBoard[row][column + 2] == check && itemNum == 0 && column + 2 < 3)
                {
                    itemNum = 3;
                    if(checkAvailable(myBoard, row, column + 1) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                if(myBoard[row + 2][column] == check && itemNum == 0 && row + 2 < 3)
                {
                    itemNum = 4;
                    if(checkAvailable(myBoard, row + 1, column) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                if(myBoard[row + 1][column + 1] == check && itemNum == 0 && row + 1 < 3 && column + 1 < 3)
                {
                    itemNum = 5;
                    if(checkAvailable(myBoard, row + 2, column + 2) == 1)
                    {
                        break;
                    }
                    else if(checkAvailable(myBoard, row - 1, column - 1) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                if(myBoard[row + 1][column - 1] == check && itemNum == 0 && row + 1 < 3 && column - 1 >= 0)
                {
                    itemNum = 6;
                    if(checkAvailable(myBoard, row + 2, column - 2) == 1)
                    {
                        break;
                    }
                    else if(checkAvailable(myBoard, row - 1, column + 1) == 1)
                    {
                        break;
                    }
                    else
                        itemNum = 0;
                }
                //don't need mid diagonal because of center priority

            }
            if(itemNum != 0)
            {
                break;
            }
        }
        if(itemNum != 0)
        {
            break;
        }
    }
    itemNum = itemNum + (10*row) + (100*column);  //condense column, row, itemNum

    return itemNum;
}

void doThrees(char myBoard[3][3], int itemNum)
{
    int row = 0;
    int column = 0;

    while(itemNum > 99)
    {
        itemNum = itemNum - 100;  //split itemNum into column, row, actual itemNum
        column += 1;
    }
    while(itemNum > 9)
    {
        itemNum = itemNum - 10;
        row += 1;
    }

    switch(itemNum)
    {
        case 1:
            if(checkAvailable(myBoard, row, column + 2) == 1)
            {
                myBoard[row][column + 2] = 'O';
                break;
            }
            else if(checkAvailable(myBoard, row, column - 1) == 1)
            {
                myBoard[row][column - 1] = 'O';
                break;
            }
        case 2:
            if(checkAvailable(myBoard, row + 2, column) == 1)
            {
                myBoard[row + 2][column] = 'O';
                break;
            }
            else if(checkAvailable(myBoard, row - 1, column) == 1)
            {
                myBoard[row - 1][column] = 'O';
                break;
            }
        case 3:
            myBoard[row][column + 1] = 'O';
            break;
        case 4:
            myBoard[row + 1][column] = 'O';
            break;
        case 5:
            if(checkAvailable(myBoard, row + 2, column + 2))
            {
                myBoard[row + 2][column + 2] = 'O';
                break;
            }
            else if(checkAvailable(myBoard, row - 1, column - 1))
            {
                myBoard[row - 1][column - 1] = 'O';
                break;
            }
        case 6:
            if(checkAvailable(myBoard, row + 2, column - 2))
            {
                myBoard[row + 2][column - 2] = 'O';
                break;
            }
            else if(checkAvailable(myBoard, row - 1, column + 1))
            {
                myBoard[row - 1][column + 1] = 'O';
                break;
            }
        default:
            puts("Stu, learn to code!");
    }
}


/*

 1st priority center   DONE
 2nd priority corner if no threat  DONE
 after (center and corner) or (corner and corner), basically two turns, block player DONE (alternate version)
 fill in spaces or if space is filled choose a different corner   DONE
 talk smack if possible (do this last in coding process)





 */











