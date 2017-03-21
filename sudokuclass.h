using namespace std;


class Square{
    // Represents a Sudoku square
    private:
        // number stores a number. 0 means empty
        int number = 0;
        // notes are possible numbers
        int notes[9] = {1,2,3,4,5,6,7,8,9};
    public:
        /* REQ: 0 < num <= 9

        Places the num in the square. Clears notes ie sets the numbers in the notes to 0
        */
        void place(int num)
        {
            // set the number to the indicated number
            number = num;
            // clear the notes
            for(int i=0; i < 9; i++)
            {
                notes[i] = 0;
            }
        }


        /* REQ: 0 < num <= 9
         * Removes a particular number
         * from the notes*/
        void eliminate(int num)
        {
            // remove the number from the ordered list
            notes[num-1] = 0;
        }


        /*REQ: 0 < num <= 9
        Checks if a particular number is in the notes of the square*/
        bool in(int num)
        {
            // check if the number is in the notes
            return num == notes[num-1];
        }


        /*If there is only 1 number left, return that number, otherwise return 0*/
        int single_num()
        {
            int ret;
            // counts the number of non-zero items
            short int counter = 0;
            // track the index
            short int index = 0;
            // loop through the notes. See if there is only 1 number left in the notes
            while(counter < 2 && index < 9)
            {
                // condition of square non-empty
                if(notes[index] != 0)
                {
                    ret = notes[index];
                    counter++;
                }
                index++;
            }
            if(counter != 1)
            {
                ret = 0;
            }
            return ret;
        }


        /* Returns the number held by the square*/
        int get_number()
        {
            return number;
        }


        /*Gets the possible numbers to place on the square*/
        vector<int> remaining()
        {
            // make an empty vector to return as a result later
            vector<int> res;
            // loop through the square
            for(int i=0; i<9; i++)
            {
                // when the value is possible to place in the square
                if(notes[i] != 0)
                {
                    // put that number in the resulting vector
                    res.push_back(notes[i]);
                }
            }
            return res;
        }
};

/* This class represents the Sudoku object
 *
 * variables:
 * the 'board' is a 9x9 array of squares.
 * 'empty' indicates whether the Sudoku board is empty or not
 *
 * warning: there is no method to reverse Sudoku board processes*/
class Sudoku{
private:
    Square board[9][9];
    bool empty;


public:
    /* Constructor for the Sudoku object. This board will be empty, filled with 0's*/
    Sudoku()
    {
        // When sudoku is constructed, empty is always true.
        empty = true;
    }


    /* Get the square in the coordinates, i, j where i is the row number and j is the column number
     * i and j must be at least 1 and at most 8
     * Return the address of the square*/
    Square* get_square(int i, int j)
    {
        return &board[i][j];
    }


    /* Prints the board visually where 0's are empty squares*/
    void print_board()
    {
        // loop through the board
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                // prints out the number
                cout<<board[i][j].get_number()<<' ';
            }
            cout<<endl;
        }
    }

    /* Places a number on the Sudoku board*/
    void place(int num, int row, int col)
    {
        // make empty be FALSE
        this->empty = false;
        // call the place method of the indicated square
        board[row][col].place(num);
        // get the starting place of the box
        int m = row/3*3;
        int n = col/3*3;
        // remove from notes row column and box
        for(int i=0; i<9; i++)
        {
            // eliminate num from row, column, and boxes
            // row
            board[row][i].eliminate(num);
            // column
            board[i][col].eliminate(num);
            // box
            board[m+(i/3)][n+(i%3)].eliminate(num);
        }
    }


    /* Return true iff this sudoku board is empty*/
    bool isempty()
    {
        return this->empty;
    }

    /* REQ: 0 <= ind < 9;
     * Returns a vector of pointers of a particular row*/
    vector<Square*> get_row(int ind)
    {
        // empty vector
        vector<Square*> ret;
        // loop through the row
        for(int i=0; i<9; i++)
        {
            ret.push_back(&board[ind][i]);
        }
        return ret;
    }

    /*REQ: 0 <= ind < 9
    Return a vector pointer of the column*/
    vector<Square*> get_col(int ind)
    {
        // empty vector
        vector<Square*> ret;
        // loop through the indicated column and add the address
        for(int i=0; i<9; i++)
        {
            ret.push_back(&board[i][ind]);
        }
        // return
        return ret;
    }

    /* REQ: 0 <= ind < 9
     *Return a vector of pointers of the indicated box*/
    vector<Square*> get_box(int ind)
    {
        // calculate the starting point
        int i = ind / 3 * 3;
        int j = ind % 3 * 3;
        vector<Square*> ret;
        for(int m=0; m<3; m++)
        {
            for(int n=0; n<3; n++)
            {
                // add the addresses of the squares to the return value
                ret.push_back(&board[m+i][j+n]);
            }
        }
        return ret;
    }
};
