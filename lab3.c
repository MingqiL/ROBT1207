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

//----------------------------------------------------------------------------------------------------------------
// standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned int cabbage;
//----------------------------------------------------------------------------------------------------------------
// Global Constants
#define MAX_DIVISORS 1000        // for sizing the div1 and div2 array statically
const int CONSOLE_WIDTH = 120;   // used to determine the number of divisor values per line to print out

//----------------------------------------------------------------------------------------------------------------
// local functions
void displayProgramInfo();       // prints information about the program
bool flushInputBuffer();         // flushes any characters left in the standard input buffer
void waitForEnterKey();          // waits for the Enter key to be pressed
void printErrorMessageAndCloseProgram(const char* message); // prints an message and closes program
void getProgramInputData(cabbage* n1, cabbage* n2);
cabbage getWholeNumber(char[]);
void getAllDivisors(cabbage n1, cabbage n2, size_t* numDiv1, size_t* numDiv2, cabbage* divsors1, cabbage* divsors2);
void getDivisors(cabbage n, cabbage* divisorArray, size_t* numCount);
cabbage getGCD(cabbage gcdPlaceHolder, cabbage* div1, cabbage* div2, size_t* numDiv1, size_t* numDiv2);
void printAllDivisors(cabbage* div1, cabbage* div2, cabbage* n1, cabbage* n2);
//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION:  Program to demonstrate standard input, branches, and loops. The program asks the user for two
//               positive whole numbers and determines their greatest common divisor (gcd).
// ARGUMENTS:    none
// RETURN VALUE: an int that tells the O/S how the program ended.  0 = EXIT_SUCCESS = normal termination
int main()
{
	cabbage n1 = 0, n2 = 0;                                // numbers used to determine the gcd. Got from user.
	size_t numDivisors1 = 0, numDivisors2 = 0;                  // number of divisors for n1 and n2
	cabbage gcd = 0;                                       // the greatest common divisior of n1 and n2
	cabbage divisors1[MAX_DIVISORS] = { 0 }, divisors2[MAX_DIVISORS] = { 0 };  // arrays to hold gcd divisors

	displayProgramInfo();  // prints out displayProgramInformation about the program

	getProgramInputData(&n1, &n2);    //getProgramInputData

	//getAllDivisors
	getAllDivisors(n1, n2, &numDivisors1, &numDivisors2, &divisors1, &divisors2);

	//getGCD
	gcd = getGCD(gcd, &divisors1, &divisors2, &numDivisors1, &numDivisors2);

	//printAllDivisors
	printAllDivisors(&divisors1, &divisors2, &n1, &n2);

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
// DESCRIPTION   Closes the program.  Outputs a message to the console and asks the user to press ENTER before closing.
// INPUTS:       message:  the message string
// RETURN:       none
void printErrorMessageAndCloseProgram(const char* message)
{
	printf("\n%s\n", message);
	printf("Press ENTER to end this program...");
	waitForEnterKey();
	exit(0);  // exit terminates a console program immediately
}

//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION: Gets main's n1 and n2 values from the user
// INPUTS:      pn1: holds main's n1 memory address
//              pn2: holds main's n2 memory address
// RETURN:      none
void getProgramInputData(cabbage* n1, cabbage* n2)
{
	char firstN[] = "first number n1";
	char secondN[] = "second number n2";

	*n1 = getWholeNumber(firstN);
	*n2 = getWholeNumber(secondN);
}


//----------------------------------------------------------------------------------------------------------------
// DESCRIPTION: Gets the whole number from the user for n1 and n2
// INPUTS:      none
// RETURN:      the whole number from the user
cabbage getWholeNumber(char n_count[])
{
	cabbage n;
	int ret;
	bool b;
	long double decTest;
	signed long long int longTest;

	printf("Please enter the %s (>0 and <=4294967295): ", n_count);
	do {
		ret = scanf_s("%lf", &decTest);
		longTest = decTest;
		//printf("decTest is %lf\n", decTest);
		//printf("longTest is %lld\n", longTest);
		//printf("ref is :%d \n", ret);
		b = flushInputBuffer();
		if (ret == false) {                            // clean up input with leading garbage
			printf("Input has leading garbage!\n");
			printf("Please enter a whole number > 0: ");
		}
		else if (b) {                                  // clean up input with trailing garbage
			printf("Input has trailing garbage!\n");
			printf("Please enter a whole number > 0: ");
		}
		else if (longTest < 0) {                        // clean up negative input
			printf("Nagative number is not accepted!\n");
			printf("Please enter a whole number > 0: ");
		}
		else if ((long long int)decTest != decTest) {  // clean up decimal input
			printf("Decimal number is not accepted!\n");
			printf("Please enter a whole number > 0: ");
		}
		else if (longTest > UINT_MAX) {                   // clean up out-of-range input
			printf("Input is outside range!\n");
			printf("Please enter a whole number > 0: ");
		}
		else if (longTest == 0) {                         // clean up zero input
			printf("Zero is not accepted!\n");
			printf("Please enter a whole number > 0: ");
		}
		else {                                         // record the input with right form
			n = (cabbage)longTest;
			printf("You have entered %u\n\n", n);
			break;

		}

	} while (true);


	return n;
}

void getAllDivisors(cabbage n1, cabbage n2, size_t* numDiv1, size_t* numDiv2, cabbage* divisors11, cabbage* divisors22)
{
	printf("Getting divisors of %u. Pleases be patient...", n1);
	getDivisors(n1, divisors11, numDiv1);
	printf("done!\n\n");
	printf("Getting divisors of %u. Pleases be patient...", n2);
	getDivisors(n2, divisors22, numDiv2);
	printf("done!\n\n");
	// Get and return the size of both n1's and n2's divisors
	//printf("Size of Div1 = %zu, and of Div2 = %zu\n", *numDiv1, *numDiv2);

}

void getDivisors(cabbage n, cabbage* divisorArray, size_t* divCount)
{
	cabbage testDiv, divisorIndex = 0;
	int pointerOffset;
	double midPoint;
	midPoint = sqrt(n);
	for (testDiv = 1; testDiv <= midPoint; testDiv++) {
		//printf("test divisor %d\n", testDiv);
		if (n % testDiv == 0) {
			*divisorArray = testDiv;
			//printf("Divisors are %u, address is %p.\n", *divisorArray, divisorArray);
			divisorArray++;
			*divCount = *divCount + 1;
		}

	}


	// determine whether the input is equal to any number raise by power of 2,
	// and give a corresponding offset value to distinguish both cases
	if (midPoint == *(divisorArray - 1))
		pointerOffset = 2;
	else
		pointerOffset = 1;

	while (divisorIndex < *divCount - pointerOffset + 1)
	{
		*(divisorArray + divisorIndex) = n / *(divisorArray - divisorIndex - pointerOffset);
		//printf("Divisors are %u, address is %p.\n", *(divisorArray + divisorIndex), divisorArray + divisorIndex);
		divisorIndex++;
	}

	*divCount = 2 * (*divCount) - pointerOffset + 1; // finalize and return size of divisors



	//else {
	//    while (divisorIndex <= *divCount)
	//    {
	//        *(divisorArray + divisorIndex) = n / *(divisorArray - divisorIndex - pointerOffset);
	//        printf("Divisors are %u, address is %p.\n", *(divisorArray + divisorIndex), divisorArray + divisorIndex);
	//        divisorIndex++;
	//    }
	//}

}

cabbage getGCD(cabbage gcdPlaceHolder, cabbage* div1, cabbage* div2, size_t* numDiv1, size_t* numDiv2)
{
	cabbage* n1_end, * n2_end, switchHandle, indexMin, indexMax, divLenMin, divLenMax;
	n1_end = div1 + *numDiv1 - 1;
	n2_end = div2 + *numDiv2 - 1;

	if (*numDiv1 <= *numDiv2) {
		switchHandle = 0;
	}
	else {
		switchHandle = 1;
	}


	switch (switchHandle)
	{
	case 0:    // case which there are less divisors for n1
		divLenMin = *numDiv1;
		divLenMax = *numDiv2;

		for (indexMin = 0; indexMin < divLenMin; indexMin++)
		{
			//printf("Checking divisor = %u:\n", *(n1_end-indexMin));
			for (indexMax = 0; indexMax < divLenMax; indexMax++) {
				if (*(n1_end - indexMin) == *(n2_end - indexMax))
				{
					gcdPlaceHolder = *(n1_end - indexMin);
					//printf("Recorded gcd %u.\n", gcdPlaceHolder);
					return gcdPlaceHolder;
				}


			}
		}
		break;


	case 1:    // case which there are less divisors for n2
		divLenMin = *numDiv2;
		divLenMax = *numDiv1;

		for (indexMin = 0; indexMin < divLenMin; indexMin++)
		{
			//printf("Checking divisor = %u:\n", *(n2_end - indexMin));
			for (indexMax = 0; indexMax < divLenMax; indexMax++) {
				if (*(n2_end - indexMin) == *(n1_end - indexMax))
				{
					gcdPlaceHolder = *(n2_end - indexMin);
					//printf("Recorded gcd %u.\n", gcdPlaceHolder);
					return gcdPlaceHolder;
				}


			}
		}

	default:
		printf("Something goes wrong!!\n");
	}


}

void printAllDivisors(cabbage* div1, cabbage* div2, cabbage* n1, cabbage* n2)
{
	cabbage numPerLine = 12, fieldWidth, divCount;
	fieldWidth = CONSOLE_WIDTH / numPerLine -2;

	printf("The divisors of %u are:\n", *n1);
	for (divCount = 0; *(div1 + divCount + 1) != 0; divCount++)
	{
		printf("%*u, ", fieldWidth, *(div1 + divCount));

	}
	printf("%*u\n\n", fieldWidth, *n1);

	printf("The divisors of %u are:\n", *n2);
	for (divCount = 0; *(div2 + divCount + 1) != 0; divCount++)
	{
		printf("%*u, ", fieldWidth, *(div2 + divCount));

	}
	printf("%*u\n", fieldWidth, *n2);
}
