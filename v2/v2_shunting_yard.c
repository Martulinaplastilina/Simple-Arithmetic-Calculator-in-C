/*
 * Calculadora roñosa
 * Intento de implementación del algoritmo de Shunting-Yard
 * Inicio: 5/11/2026
 * @author Martina Diez Pisani
 * @version 2.0
 **/

#include<stdio.h>
#include<stdbool.h>

//Function prototypes/declarations
long int createInteger(int number[], int length);
double createFloat(int floatPart, long int number);
double createNumber(int numbe[], int* number_length, int* integerDigits);
int precedence(char operator);
bool leftAssociative(char operator);
void operate(char operators[], int *operators_length, double operands[], int *operands_length);

//Function definitions
/**
 *	Creates a full integer from an array of separate numbers.
 *	@param number[] array of sigle digits
 *	@param length	length of the digits' array
 *	@return integer	result number
 */
long int createInteger(int number[], int length){
	long int integer = 0;
	for(int j = 0; j < length; j++){
		integer *= 10;
		integer += number[j];
	}
	return integer;
}

/**
 *	Creates a float number from a integer number and its calculated floatPart.
 *	@param	floatPart amount of digits this number has after the point
 *	@param	number 	  integer version of the number
 *	@return doubleNum the result float with double precision
 */
double createFloat(int floatPart,long int number){
	double doubleNum = number;
	for(; floatPart > 0; floatPart--){
		doubleNum /= 10.0;
	}
	return doubleNum;
}

/**
 *	Creates a full floating point number with double precision from an array of sigle digits.
 *	@param  number[]		array of sigle digits
 *	@param  *number_length	length of the digits' array
 *	@param	*integerDigits	amount of digits this number has before the point
 *	@return	floatNum		the result float with double precision
 */
double createNumber(int number[], int *number_length,int *integerDigits){
	double floatNum;
	if(*number_length > 0){
		long int integer = createInteger(number, *number_length);
		if(*integerDigits > 0){
			floatNum = createFloat(*number_length - *integerDigits, integer);
		} else{
			floatNum = integer;
		}
		*number_length = *integerDigits = 0;
		return floatNum;
	} else{
		/*Possible two operators in a row*/
	}
}

/**
 *	Function that returns the precedence value.
 *	@param operator		character that represents an arithmetic operation		
 *	@return precedence	the value of priority of an operator (from 1 to 4, being 1 the lowest priority)
 */
int precedence(char operator){
	int precedence = 0;
	switch(operator){
		case '(': case ')':
			precedence = 4;
			break;
		case '^':
			precedence = 3;
			break;
		case '*': case '/':
			precedence = 2;
			break;
		case '+': case '-':
			precedence = 1;
			break;
	}
	return precedence;
}

/**
 * Function that returns if an operator is left associative or not
 *	@param operator		 character that represents an arithmetic operation
 *	@return asociativity boolean value, whether an operator is left assosiative is true, otherwise false.
 */
bool leftAssociative(char operator){
	bool associativity;
	switch(operator){
		case '(': case ')':
		case '*': case '/':
		case '+': case '-':
			associativity = true;
			break;
		case '^':
			associativity = false;
			break;
		default:
			associativity = false;
			break;
	}
	return associativity;
}

/**
 *	Calculates the result of a binary operation.
 *	@param operators[]			array of characters that represent an arithmetic operation
 *	@param *operators_length	the length of the operators array
 *	@param operands[]			array of double precision float numbers
 *	@param *operands_length		the length of the operands array
 */
void operate(char operators[], int *operators_length, double operands[], int *operands_length){
	//The last operand in the operands' array
	double operand1 = operands[*operands_length-1];
	
	//The second last operand in the operands' array
	double operand2 = operands[*operands_length - 2];
	
	//The las character in the operators' array
	char operation = operators[*operators_length - 1];

	//The result
	double result = 0;

	//Debug printfs
	// printf("Operand 1: operands[%d] = %f\n", *operands_length-1, operand1);
	// printf("Operand 2: operands[%d] = %f\n", *operands_length-2, operand2);
	// printf("Operation: operators[%d] = %c\n", *operators_length - 1, operation);
	// printf("==OPERATE FUNCTION==\n");
	// printf("Operands:\n");
	// for(int i = 0; i < *operands_length; i++) printf("Operand[%d] = %f\n", i, operands[i]);
	// printf("Operators:\n");
	// for(int i = 0; i < *operators_length; i++) printf("Operators[%d] = %c\n", i, operators[i]);
	
	switch(operation){
		case '^':
			/*To define*/
			break;
		case '*':
			result = operand2 * operand1;
			break;
		case '/':
			if(operand1 != 0){
				result = operand2 / operand1;
			} else{
				printf("Division by 0!!\n");
				//The program shouldn't continue
			}
			break;
		case '+':
			result = operand2 + operand1;
			break;
		case '-':
			result = operand2 - operand1;
			break;
		case '~':
			/*unary '-'?*/
			break;
		default:
			/*To define*/
			break;
	}
	operands[*operands_length - 2] = result;
	// printf("Result: operands[%d] = %f\n", *operands_length - 2, result);
	*operands_length -= 1;
}


int main(){
	int number[17];				/*Array of sigle digits that make up the operand*/
	int number_length = 0;		/*the length of the number's array*/
	
	int periods = 0;			/*Amount of periods introduced by the user*/
	int integerDigits = 0;		/*Number of digits before the floating point*/
	
	double operands[20];		/*Array of the former operands in double precision*/
	int operands_length = 0;	/*The length of the operands' array*/

	char character;				/*Character entered by the user*/
	char operators[20];			/*Array of characters that represent an arithmetic operation*/
	int operators_length = 0;	/*The length of the oprerator's array*/

	
	printf("Enter an operation:\n");
	do{
		character = getchar();
		switch(character){							
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				number[number_length++] = (int)character - '0';
				break;
			case '.':
				if (periods <= 1){
					periods++;
					if(number_length > 0){
						integerDigits = number_length;		
					} else{
						number[number_length++] = 0;
						integerDigits = 1;
					}
				}
				break;
			case '+': case '-': case '*': case '/':
				if(number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits);		
					periods = 0;
				}
							
				while((operators_length > 0 && operators[operators_length - 1] != '(') && (precedence(operators[operators_length - 1]) > precedence(character) || (precedence(operators[operators_length - 1])== precedence(character)&& leftAssociative(character)))){
					operate(operators, &operators_length, operands, &operands_length);
					operators_length--;
				}								
				operators[operators_length++] = character;
				
				break;
			case '\n':
				if(number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits);		
					periods = 0;
				}
			
				for(; operators_length > 0 && operators[operators_length - 1] != '('; operators_length--){
					operate(operators, &operators_length, operands, &operands_length);
				}
				break;
			case '(':
				operators[operators_length++] = character;
				break;
			case ')':
				if(number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits);
					periods = 0;
				}
				
				for(; operators_length > 0 && operators[operators_length - 1] != '('; operators_length--){
					operate(operators, &operators_length, operands, &operands_length);
				}
				
				if(operators[operators_length - 1] == '('){
					operators_length--;
				}
				break;
			default:
				/*To define*/
				break;
		}
	}while(character != '\n' && character != EOF);
		
	printf("%lf\n", operands[0]);
}

