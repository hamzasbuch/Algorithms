#include <cstdio>
#include <cstdlib>

#include "sort.h"

/* 
 * HW 2 part
 */
int string_compare(char* s1, char *s2)
{ 
/*
 * We assume that s1 and s2 are non-null pointers
 */
  int i;

  i = 0;
  while ((s1[i] != 0) && (s2[i] != 0) && (s1[i] == s2[i]))
    i++;

  if (s1[i] == s2[i])
    return 0;
  else
    {
      if (s1[i] < s2[i])
	return -1;
      else
	return 1;
    }
} /*>>>*/

void insertion_sort(char** A, int l, int r)
{ 
  int i;
  char* key;

  for (int j = l+1; j <= r; j++)
    {
      key = A[j];
      i = j - 1;

      while ((i >= l) && (string_compare(A[i], key) > 0))
        {
	  A[i+1] = A[i];
	  i = i - 1;
	}

      A[i+1] = key;
    }
}

void insertion_sort_digit(char** A, int* A_len, int l, int r, int d)
{
    int i;
    char* key;
    int A_len_key;

    int computeArrKey;

    int* computedArr;

    computedArr = new int [r+1];

    //Compute the ASCII representation of character at d
    for(int i=0;i<r+1;i++)
    {
        if(A_len[i]<d)
        {
            computedArr[i] = 0;
        }
        else
        {
            computedArr[i] = int(A[i][d]);
        }
    }


    for (int j = l+1; j <= r; j++)
    {
        computeArrKey = computedArr[j];
        key = A[j];
        A_len_key = A_len[j];
        i = j - 1;

        while ((i >= l) && (computedArr[i] > computeArrKey))
        {
            computedArr[i+1] = computedArr[i];
            A[i+1] = A[i];
            A_len[i+1] = A_len[i];
            i = i - 1;
        }
        computedArr[i+1] = computeArrKey;
        A[i+1] = key;
        A_len[i+1] = A_len_key;
    }
}

void counting_sort_digit(char** A, int* A_len, char** B, int* B_len, int n, int d)
{
    int max = 0;
    int min = 0;
    int C[256];
    int output[n];
    int* computedArr;

    computedArr = new int [n+1];

    //Compute the ASCII representation of character at d
    for(int i=0;i<n+1;i++)
    {
        if(A_len[i]<d)
        {
            computedArr[i] = 0;
        }
        else
        {
            computedArr[i] = int(A[i][d]);
        }
    }
    
    //Find the max element of the array
    for(int i=0; i<n+1;i++)
    {
        if(computedArr[i] > max)
        {
            max = computedArr[i];
        }
    }
    
    //Find the min element of the array
    for(int i=0; i<n+1;i++)
    {
        if(computedArr[i] < min)
        {
            min = computedArr[i];
        }
    }
    
    //Initialize count array with 0's
    for(int i=min;i<=max;i++)
    {
        C[i] = 0;
    }
    
    //Store the count of each element
    for(int i=0; i<n+1;i++)
    {
        C[computedArr[i]]++;
    }
    
    //Calculate the cumulative count
      for (int i = min+1; i <= max; i++) {
        C[i] = C[i] + C[i - 1];
      }
    
    //Find index of each element of the original array in count array, and place elements in the output array
    for (int i = n  ; i >= 0; i--) {
       output[C[computedArr[i]] - 1] = computedArr[i];
        B[C[computedArr[i]]-1] = A[i];
        B_len[C[computedArr[i]]-1] = A_len[i];
        C[computedArr[i]]--;
     }
    
    //Copy the elements into original array
    for (int i = 0; i < n+1; i++) {
        computedArr[i] = output[i];
        A[i] = B[i];
        A_len[i] = B_len[i];
     }
}


void radix_sort_is(char** A, int* A_len, int n, int m)
{
    for(int i=m-1;i>=0;i--)
    {
        insertion_sort_digit(A,A_len,0,n-1,i);
    }
}

void radix_sort_cs(char** A, int* A_len, int n, int m)
{
    char** B;
    int* B_len;
    B = new char*[n];
    B_len = new int[n];
   
    for(int i=m-1;i>=0;i--)
    {
        counting_sort_digit(A,A_len, B, B_len, n-1, i);
    }
}

/*
 * Simple function to check that our sorting algorithm did work
 * -> problem, if we find position, where the (i-1)-th element is 
 *    greater than the i-th element.
 */
bool check_sorted(char** A, int l, int r)
{
  for (int i = l+1; i < r; i++)
    if (string_compare(A[i-1],A[i]) > 0)
      return false;
  return true;
}
