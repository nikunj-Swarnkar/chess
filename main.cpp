#include <iostream>
using namespace std;

char board[8][8];

void setupBoard() 
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            board[i][j] ='.';
        }
    }

    board[0][0] = 'R';
    board[0][1] = 'N';
    board[1][0] = 'P';
}

void printBoard()
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() 
{
    setupBoard();
    printBoard();
}