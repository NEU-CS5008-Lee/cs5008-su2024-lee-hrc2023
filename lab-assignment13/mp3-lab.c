// chen.haoyang4@northeastern.edu
// Haoyang (Hendrick) Chen

#include <stdio.h>
#include <string.h>

int compression(char arr[], int n, char res[]){
    int IndexR = 0; // index for the result array
    int IndexI = 0; // index for the input array

    while (IndexI < n) {
        // Start of a new character sequence
        char currentChar = arr[IndexI];
        int count = 0;

        // Count the number of occurrences of the current character
        while (IndexI < n && arr[IndexI] == currentChar) {
            count++;
            IndexI++;
        }

        // Append the character to the result array
        res[IndexR++] = currentChar;

        // Append the count if it's more than 1
        if (count > 1) {
            int numChars = sprintf(&res[IndexR], "%d", count);
            IndexR += numChars;
        }
    }

    // Null-terminate the result string
    res[IndexR] = '\0';

    // Return the length of the compressed string
    return IndexR;
}
 
int main()
{
    char a[]="aaaaaaaaaaaaaabbbbcccd";
    char res[50];
    int r, n = strlen(a); // n is the size of input array
    r = compression(a, n, res);
    printf("Compressed string: %s\n", res);
    printf("Length of the compressed string: %d\n", r);
    return 0;
}
