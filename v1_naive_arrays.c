/*
 * Calculadora roñosa
 * creación: 25/02/26
 * empieza a calcular: 01/03/2026
 * Calcula correctamente: 02/03/26
 * Martina Diez Pisani
 *
 * */

#include<stdio.h>
#define MAX 100
//function prototypes
int readAndStore(char operation[]);
void signManagement(char operation[]);
int numberCalculus(char operation[], int totalDigits[], double operands[]);
int signVerification(char operation[]);
int delWhiteSpaces(char operation[]);
void signOrOperator(char operation[]);
void negatives(char operation[], double operands[]);
int operators_array(char operation[], char operators[]);
int calculator(char operators[], double operands[], int *length_operands);
int arrayCompression(int iterator, int *length_operands, double operands[], char operators[]);

//Function definitions:
/* The function below is for reading characters introduced by the user and
 * store them in the operation array
 * */
int readAndStore(char operation[])
{
	char character;
	int iterator = 0;
	while((character = getchar()) != '\n')
	{
		switch (character)
		{
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
			case '+': case '*': case '-': case '/': case '.':
				operation[iterator] = character;
				character, operation[iterator];
				iterator++;
			break;
			case ' ':
			break;
			
			default:
				printf("Something went wrong :,c\n");
			break;
		}
	}
	operation[iterator] = '\0';
	return iterator;
}

/* The function below simplifies the concadenated signs
 * */
void signManagement(char operation[])
{
	int iterator, negative_signs;
	iterator = negative_signs = 0;
	while(operation[iterator] != '\0')
	{
		switch (operation[iterator])
		{
			case '+':
				operation[iterator] = ' ';
			break;

			case '-':
				operation[iterator] = ' ';
				++negative_signs;
			break;

			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				if ((iterator - 1) >= 0 && operation[iterator - 1] == ' ')
				{
					if ((negative_signs % 2) == 0)
					{
						operation[iterator - 1] = '+';
					} else
						{
							operation[iterator - 1] = '-';
						}
					negative_signs = 0;
				}
			break;
		}
		iterator++;
	}
}

//Delete the white spaces
int delWhiteSpaces(char operation[])
{
	int iterator = 0, iterator2 = 0;
	while(operation[iterator] != '\0')
	{
		if (operation[iterator] != ' ')
		{
			operation[iterator2] = operation[iterator];
			iterator2++;
		}
		iterator++;
	}
	operation[iterator2] = '\0';
	return iterator2;
}

/* The function below is for calculating the number of digits of each operand
 * at the same time it calculates the number itself
 * */
int numberCalculus(char operation[], int totalDigits[], double operands[])
{
	int iterator, iterator2, iterator3, digits, intergerdig, floatPart;
	int numbiterator, numbers_length;
	double number = 0;
	int numbers[16];
	char character;

	iterator = iterator2 = iterator3 = digits = intergerdig = floatPart = 0;
	numbiterator = numbers_length = 0;

  do
	{
		character = operation[iterator];
		switch(character)
		{
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				digits++;
				numbers[numbiterator++] = (int)character - '0';
			break;

			case '+': case '*': case '-': case '/': case '\0':
				if (digits != 0)
				{
					numbers_length = numbiterator;
					totalDigits[iterator2++] = digits;

					numbiterator = 0;
					while (numbiterator < numbers_length)
					{
						number *= 10;
						number += numbers[numbiterator++];
					}
					//printf("The number %lf has been calculated\n", number);

					if (intergerdig != 0)
					{
						floatPart = digits - intergerdig;
						while (floatPart != 0)
						{
							number /= 10;
							floatPart--;
						}
					//printf("The float %lf has been calculated\n", number);
					}
				operands[iterator3++] = number;
				numbiterator = 0;
				intergerdig = 0;
				digits = 0;
				number = 0;
			}
			break;

			case '.':
				intergerdig = digits;
			break;

			case ' ': case '\n':
			break;

			default:
			printf("Something went wrong :,c in function numberClaculus \n");
			break;
		}
	} while(operation[iterator++] != '\0');
	return iterator3;
}

/*The function below deletes +  before an operator as * or /
 * */
void signOrOperator(char operation[])
{
	int iterator = 0;
	if (operation[0] == '+') operation[0] = ' ';
	while(operation[iterator] != '\0')
	{
		if (operation[iterator] == '+')
		{
			if (operation[iterator - 1] == '*' || operation[iterator - 1] == '/')
			{
				operation[iterator] = ' ';
			}
		}
		iterator++;
	}
}

/* The function below converts to negative the numbers that should
 * */
void negatives(char operation[], double operands[])
{
	int iterator = 1, operator = 0;
	double number = 0;
	if (operation[0] == '-')
	{
		number = operands[0];
		operands[0] = (-1) * number;
		operation[0] = ' ';
	}
	while(operation[iterator] != '\0')
	{
		switch (operation[iterator])
		{
			case '-':
				if (operation[iterator - 1] == '*' || operation[iterator - 1] == '/')
				{
					number = operands[operator];
					//printf("The number %g should be negative (isn't it?)\n", number);
					operands[operator] = (-1)*number;
					operation[iterator] = ' ';
				} else operator++;
			break;
			
			case '*': case '/': case '+':
				operator++;
		 	break;
		}
		iterator++;
	}
}

/* The function below fills the operators' array with the operators of the operation
 * */
int operators_array(char operation[], char operators[])
{
	int iterator = 0, iterator2 = 0;
	char character;
	while (operation[iterator] != '\0')
	{
		character = operation[iterator];
		switch(character)
		{
			case '+': case '-': case '*': case '/': case '(': case ')':
				operators[iterator2++] = character;
			break;
		}
		iterator++;
	}
	operators[iterator2] = '\0';
	return iterator2;
}

/* The function below compress the array to the left
 * */
int arrayCompression(int iterator, int *length_operands, double operands[], char operators[])
{
	int iterator2, operandsNum, length_operators;
	iterator2 = iterator;
			while ((iterator2 + 2) <= *length_operands)
			{
		  	//printf("The operands[iterator2] = %lf is been replaced by operands[iterator2 + 1] = %lf\n", operands[iterator2], operands[iterator2]);
		  	operands[iterator2 + 1] = operands[iterator2 + 2];
				iterator2++;
			}
			*length_operands = iterator2;

			operandsNum = iterator2;

			iterator2 = iterator;
			while (operators[iterator2 + 1] != '\0')
			{
		  	//printf("The operators[iterator2] = %c is been replaced by operators[iterator2 + 1] = %c\n", operators[iterator2], operators[iterator2 + 1]);
				operators[iterator2] = operators[iterator2 + 1];
				iterator2++;
			}
	operators[iterator2] = '\0';
	length_operators = iterator2;
	return operandsNum;
}

/* The function below calculates 
 * */
int calculator(char operators[], double operands[], int *length_operands)
{
	int iterator, iterator2;
	char operator;
	double number;
	iterator = iterator2 = 0;
	while (operators[iterator] != '\0')
	{
		operator = operators[iterator];
		switch(operator)
		{
			case '*':
				number = operands[iterator] * operands[iterator + 1];
				//printf("An * has been read so operands[iterator] = %lf, operands[iterator+1] = %lf, operands[iterator] * operands[iterator + 1] = numnber = %lf \n", operands[iterator], operands[iterator + 1], number);
				operands[iterator] = number;
				arrayCompression(iterator, length_operands, operands, operators);
				iterator--;
			break;

		 	case '/':
				number = operands[iterator] / operands[iterator + 1];
				//printf("An / has been read so operands[iterator] = %lf, operands[iterator+1] = %lf, operands[iterator] / operands[iterator + 1] = numnber = %lf\n", operands[iterator], operands[iterator + 1], number);
				operands[iterator] = number;
				arrayCompression(iterator, length_operands, operands, operators);
				iterator--;
			break;
		}
		iterator++;
	}

	iterator = iterator2 = 0;
	while (operators[iterator] != '\0')
	{
		operator = operators[iterator];
		switch(operator)
		{
			case '+':
				number = operands[iterator] + operands[iterator + 1];
				//printf("An +  has been read so operands[iterator] = %lf,operands[iterator+1] = %lf, operands[iterator] + operands[iterator + 1] = numnber = %lf\n", operands[iterator], operands[iterator + 1], number);
				operands[iterator] = number;
				arrayCompression(iterator, length_operands, operands, operators);
				iterator--;
			break;

		 	case '-':
				number = operands[iterator] - operands[iterator + 1];
				//printf("An - has been read so operands[iterator] = %lf, operands[iterator+1] = %lf, operands[iterator] - operands[iterator + 1] = numnber = %lf\n", operands[iterator], operands[iterator + 1], number);
				operands[iterator] = number;
				arrayCompression(iterator, length_operands, operands, operators);
				iterator--;
			break;
		}
	iterator++;
	}
	return iterator2;
}

int main ()
{
	char operation[MAX], operators[MAX];
	int length_operation, length_operands, length_operators, iterator = 0;
	int totalDigits[MAX];
	double operands[MAX];
	printf("Introduce the operation you want to do:\n");
	length_operation = readAndStore(operation);
	signManagement(operation);
	length_operation = delWhiteSpaces(operation);
	signOrOperator(operation);
	length_operation = delWhiteSpaces(operation);
	length_operands = numberCalculus(operation, totalDigits, operands);
	negatives(operation, operands);
	length_operation = delWhiteSpaces(operation);
	length_operators = operators_array(operation, operators);

	/*printf("The operation array is: \n");
	for(iterator = 0; iterator < length_operation; iterator++)
	{
		printf("%c", operation[iterator]);
	}
	printf("\nThe operands stored are:\n");
	for(iterator = 0; iterator < length_operands; iterator++)
	{
		printf("%lf\t", operands[iterator]);
	}

	printf("\nThe operantors stored are:\n");
	for(iterator = 0; iterator < length_operators; iterator++)
	{
		printf("%c\t", operators[iterator]);
	}
	printf("\n");*/

	calculator(operators, operands, &length_operands);

	printf("The result is:\n");
	for(iterator = 0; iterator < length_operands; iterator++)
	{
		printf("%g\t", operands[iterator]);
	}
	printf("\n");
	return 0;
}
