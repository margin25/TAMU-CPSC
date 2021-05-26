/*  QUESTION
 Array Comparison
Write a function that takes as input two arrays of integers -- array A of length size_A and
array B of length size_B -- and compares the two arrays and returns the Boolean value
true if and only if A < B, i.e. there exists some i such that A[i] < B[i] and 0 ≤ i <
size_A and 0 ≤ i < size_B and A[j] = B[j] for all 0 ≤ j < i. If all elements
at indices within bounds for both arrays are equal and the arrays have different lengths, then
the shorter array is the “smaller” array (see example 2 below). Note that an array may be
empty.
The function declaration is:
bool array_compare(int A[], unsigned int size_A, int B[],
unsigned int size_B);
Examples
1. [1,2,3,4] < [1,2,4,3] → true
2. [1,2,3] < [1,2,3,4] → true
3. [] < [1] → true
4. [1,2,4] < [1,2,3,4] → false
5. [1,2,4,2,1] < [1,2,3] → false
6. [8,6,7,5] < [8,6,7,5] → false
*/

bool array_compare(int A[], unsigned int size_A, int B[], unsigned int size_B)
{
    /* // TODO(student): write your answer (i.e. comments, code) here
    //obtain smaller array size
    int min_size = 0;
    if (size_A > size_B)
    {
        min_size = size_B;
    }
    if (size_B > size_A)
    {
        min_size = size_A;
    }

    if (size_A == size_B)
    {
        min_size = size_B;
    }
    //compares the two arrays and returns the Boolean value
    //true if and only if A < B, i.e. there exists some i such that A[i] < B[i] and 0 ≤ i <
    //size_A and 0 ≤ i < size_B and A[j] = B[j] for all 0 ≤ j < i.
    for (int i = 0; i < min_size; i++)
    {
        if ((A[i] < B[i]))
        {
            if (i < size_A)
                return true;
        }

        else if (A[i] == B[j])
        {
            if (i < size_B)
                return true;
        }
    } */
    return false;
}
