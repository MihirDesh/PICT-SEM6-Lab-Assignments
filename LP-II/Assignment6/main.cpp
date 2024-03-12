#include <bits/stdc++.h>
using namespace std;

int N;//number of queens

int board[100][100];//initializing the chess board

bool isPossible(int row, int col)
{
    for(int i = 0; i < col; i++)
        if(board[row][i])
            return false;
    
    for(int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if(board[i][j])
            return false;

    for(int i = row, j = col; i < N && j >= 0; i++, j--)
        if(board[i][j])
            return false;

    return true;
}

bool solveNQueen(int col)
{
    if(col >= N)
        return true;

    for(int i = 0; i < N; i++)
    {
        if(isPossible(i, col))
        {
            board[i][col] = 1;

            if(solveNQueen(col + 1))
                return true;

            board[i][col] = 0;//backtrack
        }
    }

    return false;
}

int main()
{
    cout<<"Enter the number of Queens:"<<endl;
    cin>>N;
    memset(board, 0, sizeof(board));

    if(solveNQueen(0) == false)
    {
        cout<<"Solution does not `exist"<<endl;
        return 0;
    }

    //print the resulting chess board
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            cout<<board[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}