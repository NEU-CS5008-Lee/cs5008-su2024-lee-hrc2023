// name: <your name here>
// email: <your email here>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIMIT 50
#define RAND_RANGE 100

void print_array(int* arr, int num){
  //print out source array in rows of num elements
  for (int i=0; i < ((LIMIT/num)+1); i++) {
    for (int j=0; j<num; j++) {
      if (i*num+j < LIMIT) {
	printf("%.2d ",arr[i*num+j]);
      }
    }
    printf("\n");
  }
  printf("\n");
}

void generate_num(int* arr){
  //seed random numbers
  srand((unsigned)time(NULL));

  //initialize array with random numbers from 0..RAND_RANGE
  for (int i=0; i<LIMIT; i++) {
    arr[i] = rand() % RAND_RANGE;
  }
}

void selection_sort_2arr(int* source, int* dest, bool* valid){
  int smallest;      // current smallest element
  int smallest_index;

  for (int i=0; i<LIMIT; i++) {

  // INSERT YOUR CODE HERE
        smallest = RAND_RANGE + 1; // Initialize to a value larger than any possible element
        smallest_index = -1;

        for (int j = 0; j < LIMIT; j++) {
            if (valid[j] && source[j] < smallest) {
                smallest = source[j];
                smallest_index = j;
            }
        }

        if (smallest_index != -1) {
            dest[i] = source[smallest_index];
            valid[smallest_index] = false;

    }
  }
}

void selection_sort_1arr(int* source) {
    int smallest; // current smallest element
    int temp; // temporary for swap
    int smallest_index;

    for (int i = 0; i < LIMIT - 1; i++) {
        smallest_index = i;

        for (int j = i + 1; j < LIMIT; j++) {
            if (source[j] < source[smallest_index]) {
                smallest_index = j;
            }
        }

        temp = source[smallest_index];
        source[smallest_index] = source[i];
        source[i] = temp;
    }
}



int main(){

  int source[LIMIT]; // array to hold input data values
  int dest[LIMIT];   // array to hold sorted data values
                     // use dest only if you are using two arrays
  bool valid[LIMIT]; // array that indicates which input values are valid

  //initialize valid array - at begining the full array is valid
  for (int i=0; i<LIMIT; i++) {
    valid[i] = true;
  }
 
  //initialize source array with random numbers from 0..RAND_RANGE
  generate_num(source);

  //print out source array in rows of 20 elements
  printf("Source array:\n");
  print_array(source, 20);

  //Selection sort with 2 array
  //print out sorted array by 2 array in rows of 10
  selection_sort_2arr(source, dest, valid);
  printf("Sorted array by 2 array:\n");
  print_array(dest, 10);

  //Selection sort with 1 array
  //print out sorted array by 1 array in rows of 10
  selection_sort_1arr(source);
  printf("Sorted array by 1 array:\n");
  print_array(source, 10);
 
  return 0;
}
