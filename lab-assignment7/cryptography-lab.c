// Haoyang (Hendrick) Chen
// chen.haoyang4@northeastern.edu

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* function to encrypt the data*/
void encrypt(char text[], int key)
// Using the XOR cipher to encrypt
{
    for(int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;
    }
}

/* function to decrypt the data*/
void decrypt(char text[], int key)
{
    for(int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;
    }
}

/*----------- Main program---------------*/
int main()
{
    char text[20];
    int keyvalue = 3;

    /* Input string */
    printf("Enter the message:  ");
    scanf("%s", text);
    printf("text input = %s\n", text);
    
    /* Call function to encrypt the data */
    encrypt(text, keyvalue);
    printf("Encrypted value = %s\n", text);
    
    /* Call function to decrypt the data */
    decrypt(text, keyvalue);
    printf("Decrypted value = %s\n", text);
    
    return 0;
}
