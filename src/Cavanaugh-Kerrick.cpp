#include <iostream>
using namespace std;

// read in a new matrix
// returns the newly allocated matrix
int **readInMatrix(int r, int c)
{
    // print user prompt to enter matrix
    cout << "Please enter the values for your matrix! (" << r * c << " values)" << endl;
    //allocate some space fo the array (2d array with r rows)
    int **mat = new int *[r];
    //allocate c columns
    for (int i = 0; i < r; i++)
    {
        mat[i] = new int[c];
        //prompt user to input values
        for (int j = 0; j < c; j++)
        {
            cin >> mat[i][j];
        }
    }
    return mat;
}

//display the matrix user creates
void displayMatrix(int **mat, int r, int c)
{
    //display matrix (rows -> cols)
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << mat[i][j] << "\t";
        }
        cout << endl;

    }
    cout << endl;
}

//dealocate memory allocted from matrix
void deallocate(int **mat, int r)
{
    //delete each row
    for (int i = 0; i < r; i++)
    {
        delete mat[i];
    }
    //finally, delete row heads
    delete[] mat;
}

//transpose the matrix
//returns transposed matrix
//I chose to simply swap indexes (O(n^2) solution)
int **transpose(int **mat, int r, int c)
{
    //create new matrix (cols in mat = rows in res, vise versa)
    int **resMat = new int *[c];
    //iterate through all vals
    for (int i = 0; i < c; i++)
    {
        //allocate the mem for each col
        resMat[i] = new int[r];
        for (int j = 0; j < r; j++)
        {
            //swap vals
            resMat[i][j] = mat[j][i];
        }
    }
    return resMat;
}

//multiply matricies
//returns result of matrix multiplication
//only need col number of second matrix, as the cols of matB must be the same as rows of matA
int **multiply(int **matA, int **matB, int r1, int c1, int c2)
{
    //first, transpose the second matrix (should decrease number of cache misses, as we will accessing values in order)
    int **matBTrans = transpose(matB, r1, c2);
    //create result matrix
    int **matRes = new int *[r1];
    for (int i = 0; i < r1; i++)
    {
        matRes[i] = new int[c2];
        for (int j = 0; j < c2; j++)
        {
            //put 0 as placeholder before multiplication
            matRes[i][j] = 0;
            //perform multiplication
            for (int k = 0; k < c1; k++)
            {
                matRes[i][j] += matA[i][k] * matB[k][j];
            }
        }
    }
    return matRes;
}

// main function
int main()
{
    int userChoice;
    //while the user does NOT want to exit
    while (userChoice != 3)
    {
        //print menu and input prompt
        cout << "Welcome to the Portable Linear Algebra Library!" << endl;
        cout << "\n\t1. Transpose";
        cout << "\n\t2. Multiply";
        cout << "\n\t3. Exit\n";
        cout << "\nPlease choose an option: \n";
        // get input
        cin >> userChoice;
        int r1, c1, r2, c2;
        int **first, **second, **res;
        switch (userChoice)
        {
            case 1: {// transpose case
                // prompt for matrix dimensions
                cout << "Enter # of rows: ";
                cin >> r1;
                cout << "Enter # of columns: ";
                cin >> c1;
                cout << endl;
                // call readMatrix(...)
                first = readInMatrix(r1, c1);
                //display input matrix
                cout << "Original matrix:\n";
                displayMatrix(first, r1, c1);
                //call transpose to get result
                res = transpose(first, r1, c1);
                //print the resulting matrix
                cout << "Transposed matrix:\n";
                displayMatrix(res, c1, r1);
                //deallocate created matricies
                deallocate(first, r1);
                deallocate(res, c1);
                //break
                break;
            }

            case 2: { //multiply
                //prompt for first matrix dims
                cout << "Enter # of rows for M1: ";
                cin >> r1;
                cout << "Enter # of columns for M1: ";
                cin >> c1;
                cout << endl;
                //create matrix M1
                first = readInMatrix(r1, c1);

                //conditon for valid operation
                bool validOp = false;

                // while the operation is not valid, continue to prompt for valid response.
                while(!validOp){
                    //prompt for second matrix dims
                    cout << "Enter # of rows for M2: ";
                    cin >> r2;
                    cout << "Enter # of columns for M2: ";
                    cin >> c2;
                    cout << endl;

                    //check if multiplication is possible (row of M1 == cols of M2)
                    if(r1 == c2){ // valid
                        //create matrix M2
                        second = readInMatrix(r2, c2);
                        // set validOp to true, and continue with calculations
                        validOp = true;
                        // call multiply(...) to perform multiplication
                        res = multiply(first, second, r1, c1, c2);
                        //display input matricies
                        cout << "First matrix: \n";
                        displayMatrix(first, r1, c1);
                        cout << "Second matrix: \n";
                        displayMatrix(second, r2, c2);
                        // display resulting matrix
                        cout << "Resulting matrix:\n";
                        displayMatrix(res, r1, c2);
                        // deallocate matricies
                        deallocate(first, r1);
                        deallocate(second, r2);
                        deallocate(res, r1);
                    }else{ //not valid
                        // print invalid prompt
                        cout << "This is an invalid operation. (Hint: # of columns in first matrix MUST equal $ of rows in second matrix)\n";
                        cout << "Your first created matrix has " << c1 << " columns, please enter a second matrix that satisfies this condition.\n";
                    }
                }
                break;
            }
            case 3:{ //exit
                // print exit prompt
                cout << "Exiting Portable Linear Algebra Library\n";
                cout << "Come again.\n";
                break;
            }
            default: {//invalid entry
                // print invalid enty prompt
                cout << "Invlid entry!\n";
                break;
            }
        }
    }
}
