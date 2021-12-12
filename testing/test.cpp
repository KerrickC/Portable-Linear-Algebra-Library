//for testing, I will be using the Catch2 framework
#define CATCH_CONFIG_MAIN // tells Catch to provide a main
#include "./catch.hpp"
// #include "../src/Cavanaugh-Kerrick.cpp"


int** generateArray(int r, int c)
{
    //allocate some space fo the array (2d array with r rows)
    int **mat = new int *[r];
    //allocate c columns
    for (int i = 0; i < r; i++)
    {
        mat[i] = new int[c];
    }
    return mat;
}

//copy of transpose function from Cavanaugh-Kerrick.cpp (for testing)
//this is not optimal but I did not have enough time to come up with an alternate solution
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

//copy of multiply function from Cavanaugh-Kerrick.cpp (for testing)
//this is not optimal but I did not have enough time to come up with an alternate solution
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

//NOTE: Do to the nature of my implementation, I created array comparison for each size of array. This could most likely be optimized if I had more time.

//testing function to equate two 1x1 2-d arrays (matricies)
bool is_equal1x1(int** mat1, int mat2[][1])
{
    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 1; ++j)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//testing function to equate two 2x2 2-d arrays (matricies)
bool is_equal2x2(int** mat1, int mat2[][2])
{
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//testing function to equate two 3x3 2-d arrays (matricies)
bool is_equal3x3(int** mat1, int mat2[][3])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//testing function to equate two 2x1 2-d arrays (matricies)
bool is_equal2x1(int** mat1, int mat2[][2])
{
    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//testing function to equate two 3x4 2-d arrays (matricies)
bool is_equal3x4(int** mat1, int mat2[][3])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

//test transpose function
TEST_CASE("Test transpose", "[transpose]")
{
    SECTION("Test different sizes of matricies") {
        //tests

        //test 1 (1x1 array)
        int** arr1 = generateArray(1,1); //candidate
        arr1[0][0] = 5;
        int ttest1correct[1][1] = {{5}}; //correct solution

        //test 2 (2x2 array)
        int** arr2 = generateArray(2,2); //candidate
        arr2[0][0] = 1;
        arr2[0][1] = 2;
        arr2[1][0] = 3;
        arr2[1][1] = 4;
        int ttest2correct[2][2] = {{1,3},{2,4}}; //correct solution

        //test 3 (3x4 array)
        int** arr3 = generateArray(3,4); //candidate
        arr3[0][0] = 1;
        arr3[0][1] = 2;
        arr3[0][2] = 3;
        arr3[0][3] = 4;
        arr3[1][0] = 5;
        arr3[1][1] = 6;
        arr3[1][2] = 7;
        arr3[1][3] = 8;
        arr3[2][0] = 9;
        arr3[2][1] = 5;
        arr3[2][2] = 4;
        arr3[2][3] = 6;
        int ttest3correct[4][3] = {{1,5,9},{2,6,5},{3,7,4}, {4,8,6}}; //correct solution


        //tests
        REQUIRE(is_equal1x1(transpose(arr1, 1, 1), ttest1correct) == true);
        REQUIRE(is_equal2x2(transpose(arr2, 2, 2), ttest2correct) == true);
        REQUIRE(is_equal3x4(transpose(arr3, 3, 4), ttest3correct) == true);

    }
}

// test multiplication function
TEST_CASE("Test multiplication", "[multiplication]")
{
    SECTION("Test different multiplication cases") {
        //test matricies

        //test 1, two 1x1 matricies
        int** arr11 = generateArray(1,1); //candidate1
        arr11[0][0] = 2;
        int** arr12 = generateArray(1,1); //candidate2
        arr12[0][0] = 3;
        int mtest1correct[1][1] = {{6}}; //correctr solution

        //test 2, two 3x3 matricies
        int** arr21 = generateArray(3,3); //candidate1
        arr21[0][0] = 1;
        arr21[0][1] = 2;
        arr21[0][2] = 4;
        arr21[1][0] = 6;
        arr21[1][1] = 2;
        arr21[1][2] = 2;
        arr21[2][0] = 1;
        arr21[2][1] = 1;
        arr21[2][2] = 6;
        int** arr22 = generateArray(3,3); //candidate2
        arr22[0][0] = 7;
        arr22[0][1] = 3;
        arr22[0][2] = 2;
        arr22[1][0] = 1;
        arr22[1][1] = 2;
        arr22[1][2] = 5;
        arr22[2][0] = 6;
        arr22[2][1] = 3;
        arr22[2][2] = 1;
        int mtest2correct[3][3] = {{33,19,16}, {56,28,24}, {44,23,13}}; //correct solution

        //test 3, 2x3 matrix * 3x1 matrix
        int** arr31 = generateArray(2,3); //candidate1
        arr31[0][0] = 3;
        arr31[0][1] = 2;
        arr31[0][2] = 5;
        arr31[1][0] = 1;
        arr31[1][1] = 3;
        arr31[1][2] = 7;
        int** arr32 = generateArray(3,2); //candidate2
        arr32[0][0] = 4;
        arr32[0][1] = 2;
        arr32[1][0] = 1;
        arr32[1][1] = 8;
        arr32[2][0] = 9;
        arr32[2][1] = 2;
        int mtest3correct[2][2] = {{59, 32},{70, 40}}; //correct solution


        //tests
        REQUIRE(is_equal1x1(multiply(arr11, arr12, 1, 1, 1), mtest1correct) == true);
        REQUIRE(is_equal3x3(multiply(arr21, arr22, 3, 3, 3), mtest2correct) == true);
        REQUIRE(is_equal2x2(multiply(arr31, arr32, 2, 3, 2), mtest3correct) == true);

    }
}
