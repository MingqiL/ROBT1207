/*****************************************************************************************************************
ROBT1270 - C Programming
Lab3 - Functions

Purpose: Learn, in more detail, how to functions to reduce program complexity.  Learn to declare function
        prototypes, and define the associated function (i.e., write the source code for the function).
        Learn to pass information to/from functions using arguments that hold values (regular variables) and
        memory addresses (pointers).   Learn to return a value from a function using the return keyword.

Author: <Firstname, Lastname>

Declaration: I, <Firstname, Lastname>, declare that the following program was written by me.

Date Created: <Give Date>
*****************************************************************************************************************/

//------------------------------------------- ---------------------------------------------------------------------
// standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

//----------------------------------------------------------------------------------------------------------------
// Global Constants
#define MAX_DIVISORS 1000        // for sizing the div1 and div2 array statically
const int CONSOLE_WIDTH = 120;   // used to determine the number of divisor values per line to print out
typedef unsigned int uint;
size_t numDivisors1 = 0, numDivisors2 = 0;
uint divisors1[MAX_DIVISORS] = { 0 }, divisors2[MAX_DIVISORS] = { 0 };
//----------------------------------------------------------------------------------------------------------------
// local functions
void displayProgramInfo();       // prints information about the program
bool flushInputBuffer();         // flushes any characters left in the standard input buffer
void waitForEnterKey();          // waits for the Enter key to be pressed
void printErrorMessageAndCloseProgram(const char* message); // prints an message and closes program

void getProgramInputData(uint* pN1, uint* pN2);
uint getwholenumber(int);

uint getdivisor(uint n, uint a[]) {
    uint countdivi = 1;
    long long count = 0;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            a[countdivi] = i;
            countdivi++;
            count = count + 1;
        }
    }
    return count;
}

int getGCD(uint n1, uint n2) {
    uint maxx = 1;
    for (int i = 1; i <= n1; i++) {
        if (n1 % i == 0 && n2 % i == 0) maxx = fmax(maxx, i);
    }
    return maxx;
}

int get_num_size(int n) {
    int size = 0;
    while (n > 0) {
        size++;
        n /= 10;
    }
    return size;
}

void printAllDivisors(uint a[], uint x, uint n) {
    printf("\n");
    printf("The divisors of %u are:\n", n);
    int max_size = get_num_size(a[x]) + 2;
    for (uint i = 1; i <= x; i++) {
        if (i < x) printf("%d, ", a[i]);
        else printf("%d", a[i]);
    }
}

// 16777216
// 67108864

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Program to demonstrate standard input, branches, and loops. The program asks the user for two
//               positive whole numbers and determines their greatest common divisor (gcd).
// ARGUMENTS:    none
// RETURN VALUE: an int that tells the O/S how the program ended.  0 = EXIT_SUCCESS = normal termination
int main()
{
    uint n1 = 0, n2 = 0;                                // numbers used to determine the gcd. Got from user.
    // number of divisors for n1 and n2
    uint gcd = 0;                                       // the greatest common divisior of n1 and n2
    //uint divisors2[MAX_DIVISORS] = { 0 };  // arrays to hold gcd divisors

    displayProgramInfo();  // prints out displayProgramInformation about the program

    getProgramInputData(&n1, &n2);

    //getAllDivisors
    numDivisors1 = getdivisor(n1, divisors1);
    numDivisors2 = getdivisor(n2, divisors2);
    //for(int i = 1;i <= )
    printf("\nGetting divisors of %u.   Please be patient...done!\n", n1);
    printf("Getting divisors of %u.   Please be patient...done!\n", n2);
    //getGCD
    gcd = getGCD(n1, n2);
    //printAllDivisors
    printAllDivisors(divisors1, numDivisors1, n1);
    printAllDivisors(divisors2, numDivisors2, n2);
    printf("\nThe GCD of %u and %u is %u", n1, n2, gcd);

    // end the program
    printf("\n\nPress ENTER to end this program.");
    waitForEnterKey();
    return EXIT_SUCCESS;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  This function prints out infomation about the program
// ARGUMENTS:    none
// RETURN VALUE: none
void displayProgramInfo()
{
    printf("This program will compute the greatest common divisor (gcd) between two positive whole numbers.\n");
    printf("You will be asked to enter two whole numbers.  The program will compute and display the list\n");
    printf("of divisors for each number, and then display the greatest common divisor of the two numbers.\n\n");
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  This function flushes the input buffer to avoid scanf issues
//               ***** CALL THIS FUNCTION AFTER EVERY CALL TO scanf!!! *****
// ARGUMENTS:    none
// RETURN VALUE: false if nothing or only '\n' is in the input buffer
//               true if extra keystrokes precede the '\n'.  Good for detecting left 
//               over garbage from scanf_s in the input buffer
bool flushInputBuffer()
{
    int ch; // temp character variable
    bool bHasGarbage = false;

    // exit loop when all characters are flushed
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (!bHasGarbage) bHasGarbage = true;
    }
    return bHasGarbage;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Waits for user to press enter.  flushes stdin if keystrokes precede enter
// ARGUMENTS:    none
// RETURN VALUE: none
void waitForEnterKey()
{
    int ch;
    if ((ch = getchar()) != EOF && ch != '\n') flushInputBuffer();
}

//----------------------------------------------------------------------------------------------------------------
// Closes the program.  Outputs a message to the console and asks the user to press ENTER before closing.
// INPUTS:  message:  the message string
// RETURN:  none
void printErrorMessageAndCloseProgram(const char* message)
{
    printf("\n%s\n", message);
    printf("Press ENTER to end this program...");
    waitForEnterKey();
    exit(0);  // exit terminates a console program immediately
}
//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Get n1 and n2 from the user and store them in main's n1 and n2
// ARGUMENTS:   PN1
// RETURN VALUE: none
void getProgramInputData(uint* pN1, uint* pN2)
{
    *pN1 = getwholenumber(1);
    *pN2 = getwholenumber(2);
}

long long int change2int(char s[]) {
    long long int num = 0;
    for (int i = 0; i < strlen(s); i++) num = num * 10 + (s[i] - 48);
    return num;
}

int check_number(char s[]) {
    if (s[0] == '-') return 0;
    int cnt_char = 0, cnt_num = 0;
    for (uint i = 0; i < strlen(s); i++) {
        if (s[i] >= '0' && s[i] <= '9') cnt_num++;
        else cnt_char++;
    }
    if (cnt_char > 0 && cnt_num > 0) return 1;
    else if (cnt_char > 0 && cnt_num == 0) return 2;
    else if (change2int(s) > 4294967295) return 0;
    return 3;
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Get a whole number from the user for n1 and and n2
// ARGUMENTS:   none
// RETURN VALUE: the whole number that we got from users 
uint getwholenumber(int count)
{
    //stand for n1 and n2 
    char x[150] = "";
    int step = 0;
    do {
        if (step == 0) printf("Please enter n%d (>0 and <= 4294967295) : ", count);
        else printf("Please enter a whole number > 0: ");
        gets(x);
        flushInputBuffer();
        if (check_number(x) == 0) printf("ERROR!!! That integer is NOT >0 and <= 4294967295\n");
        else if (check_number(x) == 1) printf("ERROR!!! Please don't include trailing garbage in your input!\n");
        else if (check_number(x) == 2) printf("ERROR!!! That is NOT a number!\n");
        step++;
    } while (check_number(x) != 3);
    if (count == 1) printf("You have entered the first number ");
    else printf("You have entered the second number ");
    printf("n%d = %lld \n", count, change2int(x));

    return change2int(x);
}