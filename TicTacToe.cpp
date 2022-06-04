/*
    * All board games uses the minimax algorithm, so I wanted to try this using that algorithm.
    * Examples of edge cases: enter outside the boundries, enter numbers other than 1/2 in the beginning, or enter taken coordinates.
    * Hope you have fun playing!
*/

#include <iostream>
#include <cstdlib>
using namespace std;

#define PRINTBOX(s) ( (char)( (s == 'E') ? ' ' : s))

void printBoard(unsigned char [][3]);
void printWin(int);
int checkWin(unsigned char [][3], int);
void RegularDifficulty(unsigned char [][3], int *, int *);
void miniMaxAlgorithm(unsigned char [][3], int *, int *, int);
int miniMax(unsigned char [][3], int, bool);

int main() 
{
    unsigned int ans, i = 2, order, win;
    cout << "Welcome to the TicTacToe menu." << endl;
    cout << "Would you like to play difficulty level:" << endl;
    cout << "1) Regular (Computer Guesses At Random)" << endl;
    cout << "2) Impossible (Minimax Algorithm Does Not Allow You To Win (: )" << endl;
    cout << "I would like to play... ";
    cin >> ans;

    cin.clear();
    fflush(stdin);

    while ((ans != 1) && (ans != 2))
    {
        cout << "Invalid answer. Enter '1' or '2'." << endl;
        cout << "I would like to play... ";
        cin >> ans;

        cin.clear();
        fflush(stdin);
    }
    cout << "I would like to play 1st(X, enter 1) or 2nd(O, enter 2)... ";
    cin >> order;

    cin.clear();
    fflush(stdin);

    while ((order != 1) && (order != 2))
    {
        cout << "Invalid answer. Enter '1' or '2'." << endl;
        cout << "I would like to play... ";
        cin >> order;

        cin.clear();
        fflush(stdin);
    }
    
    
    cout << "Great!! Hope I win (:" << endl;
    int x, y;
    // 'E' stands for Empty Slot.
    unsigned char gameBoard[3][3] = { 
        {'E', 'E', 'E'},
        {'E', 'E', 'E'},
        {'E', 'E', 'E'}
    };

    cout << "Hello, user! Welcome to Tic-Tac-Toe!!!" << endl;
    cout << endl;
    cout << "How to make a move: The top left square is '0 0', moving to the right and down increments the right and left number by 1, respectively. Enter a coordinate in the form of the 2 numbers seperated by 1 space." << endl;
    cout << endl;
    srand(time(NULL));
    if (order == 1)
    {
        cout << "You are X. Your Computer is O. Let's see who shall win." << endl;
        printBoard(gameBoard);
        for (int i = 1; i <= 9; i = i + 2)
        {
            cout << "If you are requested to enter your move again, the previous one was out of bounds or in a filled space." << endl;
            do
            {
                do
                {
                    cout << "What move would you like to make? ";
                    cin >> x >> y;

                    cin.clear();
                    fflush(stdin);
                }
                while ((x < 0) || (x > 2) || (y < 0) || (y > 2));
            }
            while(gameBoard[x][y] != 'E');

            gameBoard[x][y] = 'X';
            printBoard(gameBoard);
            win = checkWin(gameBoard, order);
            printWin(win);
            if (i == 9)
            {
                cout << "You tied!" << endl;
                exit(0);
            }
            switch (ans)
            {
            case 1:
                RegularDifficulty(gameBoard, & x, & y);
                break;
            case 2:
                miniMaxAlgorithm(gameBoard, & x, & y, order);
                break;
            default:
                break;
            }
            gameBoard[x][y] = 'O';
            cout << "Computer is thinking... computer has moved!" << endl;
            printBoard(gameBoard);
            win = checkWin(gameBoard, order);
            printWin(win);
        }
    }
    if (order == 2)
    {
        cout << "Your computer is X. You are O. Let's see who shall win." << endl;
        for (int i = 1; i <= 9; i = i + 2)
        {
            switch (ans)
            {
            case 1:
                RegularDifficulty(gameBoard, & x, & y);
                break;
            case 2:
                miniMaxAlgorithm(gameBoard, & x, & y, order);
                break;
            default:
                break;
            }
            gameBoard[x][y] = 'X';
            cout << "Computer is thinking... computer has moved!" << endl;
            printBoard(gameBoard);
            win = checkWin(gameBoard, order);
            printWin(win);

            if (i == 9)
            {
                cout << "You tied!" << endl;
                exit(0);
            }

            cout << "If you are requested to enter your move again, the previous one was out of bounds or in a filled space." << endl;
            do
            {
                do
                {
                    cout << "What move would you like to make? ";
                    cin >> x >> y;

                    cin.clear();
                    fflush(stdin);
                }
                while ((x < 0) || (x > 2) || (y < 0) || (y > 2));
            }
            while(gameBoard[x][y] != 'E');

            gameBoard[x][y] = 'O';
            printBoard(gameBoard);
            win = checkWin(gameBoard, order);
            printWin(win);
        }

    }
    return 0;
}

void printBoard(unsigned char board[][3])
{
    cout << " -----------------" << endl;
    cout << "|  " << PRINTBOX(board[0][0]) << "  |  " << PRINTBOX(board[0][1]) << "  |  " << PRINTBOX(board[0][2]) << "  |" << endl;
    cout << " -----------------" << endl;
    cout << "|  " << PRINTBOX(board[1][0]) << "  |  " << PRINTBOX(board[1][1]) << "  |  " << PRINTBOX(board[1][2]) << "  |" << endl;
    cout << " -----------------" << endl;
    cout << "|  " << PRINTBOX(board[2][0]) << "  |  " << PRINTBOX(board[2][1]) << "  |  " << PRINTBOX(board[2][2]) << "  |" << endl;
    cout << " -----------------" << endl;
}

int checkWin(unsigned char winner[][3], int order)
{
    for (int i = 0; i <= 2; i++)
    {
        if ((winner[i][0] == 'E') || (winner[i][1] == 'E') || (winner[i][2] == 'E'))
        {
            continue;
        }

        else if ((winner[i][0] == winner[i][1]) && (winner[i][1] == winner[i][2]))
        {
            if (((winner[i][0] == 'X') && (order == 1)) || ((winner[i][0] == 'O') && (order == 2)))
            {
                return -1;
            }
            if (((winner[i][0] == 'X') && (order == 2)) || ((winner[i][0] == 'O') && (order == 1)))
            {
                return 1;
            }
        }
    }

    for (int j = 0; j <= 2; j++)
    {
        if ((winner[0][j] == 'E') || (winner[1][j] == 'E') || (winner[2][j] == 'E'))
        {
            continue;
        }

        else if ((winner[0][j] == winner[1][j]) && (winner[1][j] == winner[2][j]))
        {
            if (((winner[0][j] == 'X') && (order == 1)) || ((winner[0][j] == 'O') && (order == 2)))
            {
                return -1;
            }
            if (((winner[0][j] == 'X') && (order == 2)) || ((winner[0][j] == 'O') && (order == 1)))
            {
                return 1;
            }
        }
    }

    if ((winner[0][0] != 'E') && (winner[1][1] != 'E') && (winner[2][2] != 'E'))
    {
        if ((winner[0][0] == winner[1][1]) && (winner[1][1] == winner[2][2]))
        {
            if (((winner[0][0] == 'X') && (order == 1)) || ((winner[0][0] == 'O') && (order == 2))) 
            {
                return -1;
            }
            if (((winner[0][0] == 'X') && (order == 2)) || ((winner[0][0] == 'O') && (order == 1))) 
            {
                return 1;
            }

        }
    }

    if ((winner[0][2] != 'E') && (winner[1][1] != 'E') && (winner[2][0] != 'E'))
    {
        if ((winner[0][2] == winner[1][1]) && (winner[1][1] == winner[2][0]))
        {
            if (((winner[0][2] == 'X') && (order == 1)) || ((winner[0][2] == 'O') && (order == 2)))
            {
                return -1;
            }
            if (((winner[0][2] == 'X') && (order == 2)) || ((winner[0][2] == 'O') && (order == 1)))
            {
                return 1;
            }
        
        }

    }

    return 0;

}    

void RegularDifficulty(unsigned char gameBoard[][3], int * x, int * y)
{
    do
    {
        do
        {
            *x = rand() % 4;
            *y = rand() % 4;
        }
        while ((*x < 0) || (*x > 2) || (*y < 0) || (*y > 2));
    }
    while(gameBoard[*x][*y] != 'E');
}

void miniMaxAlgorithm(unsigned char gameBoard[][3], int * x, int * y, int order)
{
    int score = 0, bestScore = -10;

    for (int i = 0; i <= 2; i++)
    {
        for (int j = 0; j <= 2; j++)
        {
            if (gameBoard[i][j] == 'E')
            {
                if (order == 1)
                {
                    gameBoard[i][j] = 'O';
                }
                if (order == 2)
                {
                    gameBoard[i][j] = 'X';
                }
                score = miniMax(gameBoard, order, false);
                gameBoard[i][j] = 'E';

                if (score > bestScore)
                {
                    bestScore = score;
                    * x = i;
                    * y = j;
                }
            }
        }
    }

}

int miniMax(unsigned char gameBoard[][3], int order, bool isMaximizing)
{
    int result = checkWin(gameBoard, order), bestScore = -10, score;
    if ((result == 1) || (result == -1))
    {
        return result;
    }

    if (isMaximizing == true)
    {
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (gameBoard[i][j] == 'E')
                {
                    if (order == 1)
                    {
                        gameBoard[i][j] = 'O';
                    }
                    if (order == 2)
                    {
                        gameBoard[i][j] = 'X';
                    }
                    score = miniMax(gameBoard, order, false);
                    gameBoard[i][j] = 'E';

                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    else 
    {
        bestScore = 10;
        for (int i = 0; i <= 2; i++)
        {
            for (int j = 0; j <= 2; j++)
            {
                if (gameBoard[i][j] == 'E')
                {
                    if (order == 1)
                    {
                        gameBoard[i][j] = 'X';
                    }
                    if (order == 2)
                    {
                        gameBoard[i][j] = 'O';
                    }
                    score = miniMax(gameBoard, order, true);
                    gameBoard[i][j] = 'E';

                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
    return bestScore;
    }

}

void printWin(int win)
{
    if (win == -1)
    {
        cout << "You won!" << endl;
        exit(0);
    }
    if (win == 1)
    {
        cout << "The computer won!" << endl;
        exit(0);
    }
}