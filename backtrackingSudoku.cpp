#include <iostream>

using namespace std;

class Sudoku {
int sudoku[9][9];

public:
    void createBoard();
    int isComplete();
    void fillPositions();
    void printBoard();
    void printHorizontal();
    bool checkRow(int, int);
    bool checkColumn(int, int);
    bool checkBlock(int, int, int);
    bool check(int, int, int);
    bool solve();
};

void Sudoku :: createBoard() {
    cout<<"Enter the values for the sudoku board (0 for blank):"<<endl;
    int a;
    for(int i = 0; i < 9; i ++) {
        cout<<"Row #"<<i+1<<":"<<endl;
        for(int j = 0; j < 9; j++) {
            cin>>sudoku[i][j];
        }
    }
}

void Sudoku :: printBoard() {
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0)
            printHorizontal();
        for(int j = 0; j < 9; j++) {
            if(j % 3 == 0) {
                cout<<"|";
            }
            cout<<sudoku[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    printHorizontal();
}

void Sudoku :: printHorizontal() {      // Just for display purposes
    for(int i = 1; i < 10; i++) {
        if(i % 3 == 1) {
            cout<<"+";
        }
        cout<<"--";
    }
    cout<<"+"<<endl;
}

int Sudoku :: isComplete() {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(sudoku[i][j] == 0) {
                return i*10 + j;        // Just a trick to return i and j together
            }
        }
    }
    return -1;
}

bool Sudoku :: checkRow(int m, int element) {
    for(int i = 0; i < 9; i++) {
        if(sudoku[m][i] == element) {
            return false;
        }
    }
    return true;
}

bool Sudoku :: checkColumn(int m, int element) {
    for(int i = 0; i < 9; i++) {
        if(sudoku[i][m] == element) {
            return false;
        }
    }
    return true;
}

bool Sudoku :: checkBlock(int m, int n, int element) {
    if(m >= 0 && m <= 2) 
        m = 0;
    else if(m >= 3 && m <= 5)
        m = 3;
    else
        m = 6;
    if(n >= 0 && n <= 2) 
        n = 0;
    else if(n >= 3 && n <= 5)
        n = 3;
    else
        n = 6;
    for(int i = m; i < m + 3; i++) {
        for(int j = n; j < n + 3; j++) {
            if(sudoku[i][j] == element)
                return false;
        }
    }
    return true;
}

bool Sudoku :: check(int m, int n, int element) {
        if(checkRow(m, element)) 
            if(checkColumn(n, element))
                if(checkBlock(m, n, element))
                    return true;
    return false;
}

bool Sudoku :: solve() {
    int m, n, r;
    if((m = isComplete()) == -1) {
        return true;
    } else {
        n = m % 10;
        m = m / 10;
    }
    for(int i = 1; i < 10; i++) {
        if(check(m, n, i)) {
            sudoku[m][n] = i;
            if(solve()) {
                return true;
            } 
            sudoku[m][n] = 0;   
        }
    }
    return false;
}

int main() {
    Sudoku s;
    s.createBoard();
    s.solve();
    s.printBoard();

    return 0;
}


/*

Medium:

0 3 0 2 8 0 1 0 0
0 5 0 3 0 0 0 6 0
1 0 0 0 0 0 8 0 2
0 0 0 8 0 0 0 1 3
0 0 7 0 2 0 5 0 0
3 2 0 0 0 5 0 0 0
7 0 3 0 0 0 0 0 1
0 8 0 0 0 1 0 4 0
0 0 9 0 4 2 0 7 0

Hard:

0 0 7 0 0 0 0 0 8
0 0 0 0 9 0 5 0 0
0 0 3 1 0 5 9 7 0
0 8 0 0 1 6 0 3 0
0 0 0 0 0 0 0 0 0
0 6 0 8 3 0 0 2 0
0 3 8 7 0 1 4 0 0
0 0 9 0 6 0 0 0 0
1 0 0 0 0 0 8 0 0


*/