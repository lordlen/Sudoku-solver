#include <bits/stdc++.h>
#include "sudokuclass.h"
#include "sudokufunctions.h"
using namespace std;


int main(){
    // pointer to a sudoku board
    Sudoku *sp;
    /*
    // easy sudoku board
    int arr[9][9] = {
            {0,9,0,8,7,3,0,2,0},
            {0,0,5,0,0,0,7,0,0},
            {4,0,3,0,0,0,0,0,0},
            {0,4,0,7,0,0,2,8,0},
            {0,0,0,3,0,8,0,0,0},
            {0,3,8,0,0,6,0,5,0},
            {0,0,0,0,0,0,6,0,2},
            {0,0,7,0,0,0,5,0,0},
            {0,6,0,5,2,1,0,4,0}
    };*/
    //Hard sudoku board
    int arr[9][9] =
     {
            {5,0,0,0,0,0,0,9,0},
            {0,7,0,6,0,5,0,0,8},
            {0,0,0,0,9,0,1,0,4},
            {0,0,9,0,2,0,0,0,0},
            {8,0,0,7,0,0,0,0,9},
            {0,0,5,8,0,0,0,6,0},
            {4,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,4,0,0,5},
            {0,0,0,0,3,0,0,2,1}
    };
    /*
    int arr[9][9] =
    {
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0}
    };*/
    sp = create_board(arr);
    // print the beginning board
    sp->print_board();
    // do the easy moves
    bool did_something = true;
    // loop ends when step1 and step2 does nothing
    while(did_something)
    {
        did_something = false;
        // sole candidate: looks at each square and places number on squares in which there is only one possibility
        did_something = step1(sp)||did_something;
        // unique candidate:Looks at rows, columns, box and places number if
        // it is the only possible number in that group
        did_something = step2(sp)||did_something;
    }
    cout << endl;
    // brute force: use backtracking to fill the rest
    Sudoku s = backtrack(*sp);
    // print the final board
    s.print_board();
    // deallocate memory
    delete sp;
return 0;
}
