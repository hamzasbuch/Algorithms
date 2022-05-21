#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <math.h>

#include "sort.h"


int ivector_length(int* v, int n)
{
    int sum;
    
    sum = 0;
    for (int i = 0; i < n; i++)
        sum += (v[i] < 0) ? -v[i] : v[i];
    
    return sum;
}

/*
 * insertion sort
 */
void insertion_sort(int** A, int n, int l, int r)
{ 
    int i;
    int* key;
    
    for (int j = l+1; j <= r; j++)
    {
        key = A[j];
        i = j - 1;
        
        while ((i >= l) && (ivector_length(A[i], n) > ivector_length(key, n)))
        {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = key;
    }
}

/*
 *   TO IMPLEMENT: Improved Insertion Sort for problem 1.
 */
void insertion_sort_im(int** A, int n, int l, int r)
{
    int i;
    int* key;
    
    int keySum;
    
    int* computedLenArr;
    
    computedLenArr = new int [r+1];
    
    //Compute the length of each vector
    for(int x=0;x<r+1;x++)
    {
        computedLenArr[x] = ivector_length(A[x], n);
    }
    
    for (int j = l+1; j <= r; j++)
    {
        keySum = computedLenArr[j];
        key = A[j];
        i = j - 1;
        
        while ((i >= l) && (computedLenArr[i] > keySum))
        {
            computedLenArr[i+1] = computedLenArr[i];
            A[i+1] = A[i];
            i = i - 1;
        }
        computedLenArr[i+1] = keySum;
        A[i+1] = key;
    }
}

//Function to merge the array using the pre computed array length
void merge(int** A, int* computedLenArr, int p , int q, int r)
{
    int i,j,k;
    
    int n1 = q-p+1;
    int n2 = r-q;
    
    int L[n1];
    int R[n2];
    
    int** arrL = new int*[n1];
    int** arrR = new int*[n2];
    
    
    for(int i=0;i<n1;i++)
    {
        L[i] = computedLenArr[p+i];
        arrL[i] = A[p+i];
    }
    
    for(int j=0; j<n2;j++)
    {
        R[j] = computedLenArr[q+1+j];
        arrR[j] = A[q+1+j];
    }
    
    i = 0;
    j=0;
    k=p;
    
    while(i< n1 && j<n2)
    {
        if(L[i] <= R[j])
        {
            computedLenArr[k] = L[i];
            A[k] = arrL[i];
            i++;
        }
        else{
            computedLenArr[k] = R[j];
            A[k] = arrR[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        computedLenArr[k] = L[i];
        A[k] = arrL[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        computedLenArr[k] = R[j];
        A[k] = arrR[j];
        j++;
        k++;
    }
}

//Recursive merge sort function
void mergesort(int** A, int* computedLenArr ,int p, int r)
{
    int q;
    if(p<r)
    {
        q = p+(r-p)/2;
        mergesort(A,computedLenArr,p, q);
        mergesort(A,computedLenArr,q+1, r);
        merge(A,computedLenArr, p,q,r);
    }
}
/*
 *   TO IMPLEMENT: Improved Merge Sort for problem 2.
 */
void merge_sort(int** A, int n, int p, int r)
{
    int* computedLenArr;
    computedLenArr = new int [r+1];
    
    //Compute the length of each vector
    for(int x=0;x<r+1;x++)
    {
        computedLenArr[x] = ivector_length(A[x], n);
    }
    
    mergesort(A,computedLenArr,p,r);
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is
 *    greater than the i-th element.
 */
bool check_sorted(int** A, int n, int l, int r)
{
    for (int i = l+1; i <= r; i++)
        if (ivector_length(A[i-1], n) > ivector_length(A[i], n))
            return false;
    return true;
}


/*
 * generate sorted/reverse/random arrays of type hw1type
 */
int** create_ivector(int n, int m)
{
    int** iv_array;
    
    iv_array = new int*[m];
    for (int i = 0; i < m; i++)
        iv_array[i] = new int[n];
    
    return iv_array;
}

void remove_ivector(int** iv_array, int m)
{
    for (int i = 0; i < m; i++)
        delete[] iv_array[i];
    delete[] iv_array;
}

int** create_sorted_ivector(int n, int m)
{
    int** iv_array;
    
    iv_array = create_ivector(n, m);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            iv_array[i][j] = (i+j)/n;
    
    return iv_array;
}

int** create_reverse_sorted_ivector(int n, int m)
{
    int** iv_array;
    
    iv_array = create_ivector(n, m);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            iv_array[i][j] = ((m-i)+j)/n;
    
    return iv_array;
}

int** create_random_ivector(int n, int m, bool small)
{
    random_generator rg;
    int** iv_array;
    
    iv_array = create_ivector(n, m);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            rg >> iv_array[i][j];
            if (small)
                iv_array[i][j] %= 100;
            else
                iv_array[i][j] %= 65536;
        }
    
    return iv_array;
}

