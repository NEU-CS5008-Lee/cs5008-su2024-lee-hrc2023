// name: Haoyang (Hendrick) Chen
// email: chen.haoyang4@northeastern.edu


// please start with a copy of your hw7.c, rename it to hw.8
// and then complete the assignment

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLESIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// Hash table entry structure
typedef struct Entry {
    char cityStr[MAXSTRING];
    int popInt;
    struct Entry* next;  // For chaining in case of collisions
} Entry;

// Hash table structure
typedef struct HashTable {
    Entry* slots[TABLESIZE];
} HashTable;

// check if a character c is a digit
bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2];           // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0';          // put NUL to terminate string of one character
    strcat(s, charToStr);
}

// Initialize hash table
void initHashTable(HashTable* table) {
    for (int i = 0; i < TABLESIZE; i++) {
        table->slots[i] = NULL;
    }
}

// Create a new hash table entry
Entry* createEntry(const char* cityStr, int popInt) {
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    if (newEntry) {
        strcpy(newEntry->cityStr, cityStr);
        newEntry->popInt = popInt;
        newEntry->next = NULL;
    }
    return newEntry;
}

// Hash function 1: length of the city/state string (modulo size of table)
int hashFunc1(const char* str) {
    return strlen(str) % TABLESIZE;
}

// Hash function 2: sum of the character codes of the city/state string (modulo size of table)
int hashFunc2(const char* str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += (unsigned char)str[i];
    }
    return sum % TABLESIZE;
}

// Hash function 3: product of the first 2 character codes in city/state string (modulo size of table)
int hashFunc3(const char* str) {
    if (strlen(str) < 2) {
        return 0;
    }
    int product = (unsigned char)str[0] * (unsigned char)str[1];
    return product % TABLESIZE;
}

// Insert into hash table
void insertToTable(HashTable* table, int (*hashFunc)(const char*), const char* cityStr, int popInt) {
    int index = hashFunc(cityStr);
    Entry* newEntry = createEntry(cityStr, popInt);
    if (newEntry) {
        newEntry->next = table->slots[index];
        table->slots[index] = newEntry;
    }
}

// Print hash table contents
void printTable(HashTable* table, const char* tableName) {
    printf("Contents of %s:\n", tableName);
    for (int i = 0; i < TABLESIZE; i++) {
        if (table->slots[i] != NULL) {
            Entry* entry = table->slots[i];
            while (entry != NULL) {
                printf("Slot %d: [%s] -> Population: %d\n", i, entry->cityStr, entry->popInt);
                entry = entry->next;
            }
        }
    }
    printf("\n");
}

int main() {
    char inputLine[MAXSTRING];   // temporary string to hold input line
    char cityStr[MAXSTRING];     // city name
    int  lineNum;                // line number (city rank)
    int  popInt;                 // population
    int  state;                  // FSM state
    int  nextChar;               // index of next character in input string
    char temp[MAXSTRING];        // temp string to build up extracted strings from input characters

    FILE* fp;
    fp = fopen("pop.csv", "r");

    HashTable table1, table2, table3;
    initHashTable(&table1);
    initHashTable(&table2);
    initHashTable(&table3);

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        // ***** BEGIN FINITE STATE MACHINE *****

        // STARTSTATE: digit -> S1
        // S1: digit -> S1; , -> S2
        // S2: " -> S3
        // S3: !" -> S3; " -> S4
        // S4: , -> S5
        // S5: " -> S6; ( -> ACCEPTSTATE
        // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE;
        // ACCEPTSTATE: done!
        // else go to ERRORSTATE
        //
        while (feof(fp) == 0) {

            nextChar = 0;
            state = STARTSTATE;
            strcpy(temp, "");       // temp = ""
            strcpy(cityStr, "");    // cityStr = ""
            popInt = 0;            // initialize population to 0

            if (nextChar >= strlen(inputLine)) {
                // if no input string then go to ERRORSTATE
                state = ERRORSTATE;
            }

            while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
                switch (state) {
                    case STARTSTATE:
                        // look for a digit to confirm a valid line
                        if (isDigit(inputLine[nextChar])) {
                            state = S1;
                            appendChar(temp, inputLine[nextChar]);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S1:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            state = S2;
                            lineNum = atoi(temp);  // convert temp string to integer
                            strcpy(temp, "");  // reset temp for next use
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S2:
                        if (inputLine[nextChar] == '"') {
                            state = S3;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S3:
                        if (inputLine[nextChar] != '"') {
                            appendChar(cityStr, inputLine[nextChar]);
                        } else {
                            state = S4;
                        }
                        break;

                    case S4:
                        if (inputLine[nextChar] == ',') {
                            state = S5;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S5:
                        if (inputLine[nextChar] == '"') {
                            state = S6;
                        } else if (inputLine[nextChar] == '(') {
                            state = ACCEPTSTATE;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S6:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',' || inputLine[nextChar] == '"') {
                            if (inputLine[nextChar] == '"') {
                                char* ptr;
                                popInt = strtol(temp, &ptr, 10);  // convert temp string to integer, handle commas
                                state = ACCEPTSTATE;
                            }
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case ACCEPTSTATE:
                        // nothing to do - we are done!
                        break;

                    default:
                        state = ERRORSTATE;
                        break;
                } // end switch

                // advance input
                nextChar++;

            } // end while state machine loop

            // ***** END FINITE STATE MACHINE *****

            // Insert into hash tables
            insertToTable(&table1, hashFunc1, cityStr, popInt);
            insertToTable(&table2, hashFunc2, cityStr, popInt);
            insertToTable(&table3, hashFunc3, cityStr, popInt);

            // get next line
            fgets(inputLine, MAXSTRING, fp);

        } // end while file input loop

        fclose(fp);

    } else {
        printf("File not found!\n");
    }

    // Print hash table contents
    printTable(&table1, "Hash Table 1");
    printTable(&table2, "Hash Table 2");
    printTable(&table3, "Hash Table 3");

    return 0;
}
