#include<bits/stdc++.h>
/*Algorithm:
 * Step1 (Sole candidate): Check each square. If there is only 1 possible number.
 *  in the notes, add that number to that square. Loop until
 *  can't do anymore.
 * Step2 (Unique Candidate): Check all of the row, column and box possibilities
 * Step3: Place squares based on boxes to rows and rows to boxes and boxes to columns and columns to boxes
*/
using namespace std;

/* Given an integer array, create a Sudoku board and return the address.
 * WARNING: This function uses the heap for memory. Make sure to use delete after using the created board to prevent
 * memory leaks.*/
Sudoku* create_board(int arr[9][9])
{
    // make a blank board
    Sudoku *s = new Sudoku;
    // loop through the array
    for (int i = 0; i < 9; i++)
    {
        for(int j=0; j<9; j++)
        {
            // case of the integer is not 0, place the number in the board
            if(arr[i][j] != 0)
            {
                s->place(arr[i][j], i, j);
            }
        }
    }
    // return the address of s
    return s;
}

/*In the sudoku square, check if there is only\
 *  1 item in notes. If so, put that number. Helper\
 * for step 1";*/
bool fill_single(Sudoku *s, int row, int col)
{
    // call the single_num method
    int num = s->get_square(row, col)->single_num();
    bool ret;
    // if the number is not 0
    if(num)
    {
        //place the number on that square
        s->place(num, row, col);
        ret = true;
    }else
    {
        ret = false;
    }
    return ret;
}

/*See algorithm above*/
bool step1(Sudoku *s)
{
    bool cont = true, did_something = false;
    int i, j;
    while(cont)
    {
        // set cont to false
        cont = false;
        i = 0;
        // loop the 9x9 board
        while(i<9)
        {
            j = 0;
            while(j<9)
            {
                did_something = fill_single(s, i, j) || did_something;
                j++;
            }
            i++;
        }
    }
    return did_something;
}

//given a number, return true iff there is only 1 occurrence in the row/col/box
bool only_one_occurrence(int num, vector<Square*> row_col_box)
{
    int counter = 0;
    int index = 0;
    // loop through until the end of the vector or until counter exceeds 1
    while(counter < 2 && index < row_col_box.size())
    {
        // if the number is in the indicated vector, add 1 to the counter
        if(row_col_box[index]->in(num))
        {
            counter ++;
        }
        // increment
        index ++;
    }
    return counter == 1;
}

/*Returns True if this function mutated the sudoku board. Mutates the board such that if one of the numbers in\
 *the notes of the indicated square in s->board[row][col] is the only occurrence in the row/col/box, place that\
 *number in the board."*/
bool single_out(Sudoku *s, int row, int col, vector<Square*> row_col_box)
{
    bool did_something = false;
    // get the remaining numbers possible for the indicated block
    vector<int> remainder = s->get_square(row, col)->remaining();
    // loop through those numbers
    int i = 0;
    while (!did_something && i < remainder.size())
    {
    // if there is only one occurrence in the row/col/box, add that number and set did_something to true
        if(only_one_occurrence(remainder[i], row_col_box))
        {
            s->place(remainder[i], row, col);
            did_something = true;
        }
        i ++;
    }
    return did_something;
}


// See algorithm above
bool step2(Sudoku *s)
{
    bool did_something = false;
    // loop through rows
    for(int i=0; i<9; i++)
    {
        vector<Square*> rows = s->get_row(i);
        // loop through columns
        for(int j=0; j<9; j++)
        {
            // rows
            if(s->get_square(i, j)->get_number() == 0)
            {
                did_something = single_out(s, i, j, rows) || did_something;
            }
            // columns
            if(s->get_square(i, j)->get_number() == 0)
            {// get the column
                vector<Square*> cols = s->get_col(j);
                did_something = single_out(s, i, j, cols) || did_something;
            }
            // boxes
            if(s->get_square(i, j)->get_number() == 0)
            {
                vector<Square*> boxes = s->get_box(i/3*3 + j/3);
                did_something = single_out(s, i ,j , boxes)|| did_something;
            }
        }
    }
    return did_something;
}


/* Given a row number, return an array of the box_numbers that intersect with that row
 * row_ind is the row number
int* row_intersections_with_box(int row_ind)
{
    // start num is the first box number.
    int* ret;
    int start_num;
    // get the starting number
    start_num = row_ind / 3;
    // loop through
    for(int i= 0; i<3; i++)
    {
        ret[i] = start_num + i;
    }
    return ret;
}*/

/* Given the column number, return an array of box_numbers
int* col_intersections_with_box(int col_ind)
{
    int start_num;
    int* ret;
    start_num = col_ind / 3;
    // loop through
    for(int i=0; i<3; i++)
    {
        ret[i] = i*3+start_num;
    }
    return ret;
}*/


/* Find the coordinates of an empty square in the sudoku where first is the row number and second is the column.
 * If none found, return (-1, -1)*/
tuple<int, int> find_empty(Sudoku s)
{
    // loop through s
    int i, j, x, y;
    // set the default value of the function
    x = -1;
    y = -1;
    // loop through the sudoku board
    i = 0;
    while(x == -1 && i < 9)
    {
        j = 0;
        while(y == -1 && j < 9)
        {
            // when found an empty square, set the coordinates of that square in the result
            if(s.get_square(i, j)->get_number() == 0)
            {
                // set x and y to the coordinate that has an empty square
                x = i;
                y = j;
            }
            j++;
        }
        i++;
    }
    tuple<int, int> result = make_tuple(x, y);
    return result;
}


/* Given a Sudoku board 's', solves s by brute force and returns the new sudoku board. If the Sudoku board is not
 * valid, the function returns and empty Sudoku board. Uses recursion*/
Sudoku backtrack(Sudoku s)
{
    Sudoku result;
    // find an empty square
    int i, j;
    tie(i, j) = find_empty(s);
    // when sudoku is complete, return it
    if(i == -1 && j == -1)
    {
        result = s;
    }
    else
    {
        // get the remaining of the Square
        vector<int> remainder = s.get_square(i, j)->remaining();
        // case of a dead end, do nothing
        // if not dead end
        if (remainder.size() != 0)
        {
            int m = 0;
            // loop through the remainder
            while (result.isempty() && m < remainder.size())
            {
                // make a temporary Sudoku board
                Sudoku temp_s = s;
                // place a possible number in s
                temp_s.place(remainder[m], i, j);
                // Recursion;
                result = backtrack(temp_s);
                m++;
            }
        }
    }
    return result;
}
