/*
 * Calculadora roñosa
 * Intento de implementación del algoritmo de Shunting-Yard
 * Inicio: 5/11/2026
 * @author Martina Diez Pisani
 * @version 2.2
 **/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>	//In order to compare with version 1.0


//Function prototypes/declarations
long long int createInteger(int number[], int length);
double createFloat(int floatPart, long int number);
double createNumber(int number[], int *number_length,int *integerDigits, int *periods);
int precedence(char operator);
bool leftAssociative(char operator);
double BinaryOperation(char operation, double operand1, double operand2);
double UnaryOperation(char operation, double operand);
void operate(char operation, double operands[], int *operands_length);
bool isBinary(char operation);
bool isOperator(char operators[], int index);

//Function definitions
/**
 *	Creates a full integer from an array of separate numbers.
 *	@param number[] array of sigle digits
 *	@param length	length of the digits' array
 *	@return integer	result number
 */
long long int createInteger(int number[], int length){
	long long int integer = 0;
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
 *  @param	*periods		amount of points entered by the user
 *	@return	floatNum		the result float with double precision
 */
double createNumber(int number[], int *number_length,int *integerDigits, int *periods){
	double floatNum;
	long long int integer = createInteger(number, *number_length);
	if(*integerDigits > 0){
		floatNum = createFloat(*number_length - *integerDigits, integer);
	} else{
		floatNum = integer;
	}
	*number_length = *integerDigits = *periods = 0; //reset of the variables after the number creation
	return floatNum;
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
		case '~': case '`':
			precedence = 2;
			break;
		case '*': case '/':
			precedence = 1;
			break;
		case '+': case '-':
			precedence = 0;
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
		case '^': case '~': case '`':
			associativity = false;
			break;
		default:
			associativity = false;
			break;
	}
	return associativity;
}

/**
 *	Calculates the result of an binary operation.
 *	@param operation			the last operator in the operatiors' array
 *	@param operand1			 	the last operand in the operands' array
  *	@param operand2			 	the second last operand in the operands' array
 *	@return result				the result of the operation between the operands
 */
double BinaryOperation(char operation, double operand1, double operand2){
	double result = 0; 			/* The result */
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
				fprintf(stderr, "Division by 0!!\n");
				//The program shouldn't continue
			}
			break;
		case '+':
			result = operand2 + operand1;
			break;
		case '-':
			result = operand2 - operand1;
			break;
		default:
			/*To define*/
			break;
	}
	return result;
}


/**
 *	Calculates the result of an unary operation.
 * 	@param operation			the last operator in the operatiors' array
 *	@param operand  		 	the last operand in the operands' array
 *	@return result				the result of the operation on the operand
 */
double UnaryOperation(char operation, double operand){
	double result = 0; 			//The result
	switch(operation){
		case '~':
			result = -1 * operand;
			break;
		case '`':
			result = operand;
			break;
		default:
			/*To define*/
			break;
	}
	return result;
	
}

/**
 *	Calculates the result of an operation.
 *	@param operation		    the last operator in the operatiors' array
 *	@param operands[]			array of double precision float numbers
 *	@param *operands_length		the length of the operands array
 */
void operate(char operation, double operands[], int *operands_length){
	if(isBinary(operation)){ 
		operands[*operands_length - 2] = BinaryOperation(operation, operands[*operands_length - 1], operands[*operands_length - 2]);
		*operands_length -= 1;
	} else {
		operands[*operands_length - 1] = UnaryOperation(operation, operands[*operands_length - 1]);
	}
}

/**
 * Function that returns whether an operation is binaryr or not
 *	@param operation			character that represents an arithmetic operation
 *	@return true if it's binaryr, otherwise false.
 */
bool isBinary(char operation){
	switch(operation){
	case '^':
	case '*':
	case '/':
	case '+':
	case '-':
		return true;
	case '~':
	case '`':
		return false;
	default:
		return false;
		break;
	}
}

/**
 * Function that returns whether a character is an operator or not
 *	@param operators[]			array of characters
 *	@param index			    index of the characters' array
 *	@return true if a character is an operator, otherwise false.
 */
bool isOperator(char operators[], int index){
	switch(operators[index]){
		case '^':
		case '*':
		case '/':
		case '+':
		case '-':
		case '~':
		case '`':
			return true;
		default:
			return false;
	}
}

int main(){
	int number_size, operands_size, operators_size;
	number_size = operands_size = operators_size = 20;
	int *number = malloc(number_size * sizeof(int));			/*Array of sigle digits that make up the operand*/
	int number_length = 0;										/*the length of the number's array*/

	int periods = 0;											/*Amount of periods introduced by the user*/
	int integerDigits = 0;										/*Number of digits before the floating point*/

	double *operands = malloc(operands_size * sizeof(double));	/*Array of the former operands in double precision*/
	int operands_length = 0;									/*The length of the operands' array*/

	char character;												/*Character entered by the user*/
	char *operators = malloc(operators_size * sizeof(char));			/*Array of characters that represent an arithmetic operation*/
	int operators_length = 0;				/*The length of the oprerator's array*/


	//printf("Enter an operation:\n");
	do{
		character = getchar();
		// printf("Read a character: %c\n", character);
		// printf("So far we have:\n");
		// printf("operands array:\n");
		// for(int i = 0; i < operands_length; i++) printf("\toperands[%d] = %lf\n", i, operands[i]);
		// printf("operators array:\n");
		// for(int i = 0; i < operators_length; i++) printf("\toperators[%d] = %c\n", i, operators[i]);
		switch(character){
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				number[number_length++] = (int)character - '0';
				break;
			case '.':
				if (periods < 1){ 	//Verifies if the user hasn't entered more than one point
					periods++;
					if(number_length > 0){ //If there are digits before the point, they'll be the integer part of the calculated number
						integerDigits = number_length;
					} else {
						number[number_length++] = 0;
						integerDigits++;
					}
				} else {
					fprintf(stderr, "Several floating point detected - Only the first one will be considered\n");
				}
				break;

			case '-':case '+': 
			case '*': case '/':
				
				// printf("For the operators[%d] = %c ---Not yet stored just representation\n", operators_length, character);
				// printf("\tHas this situation:\n");
				// printf("\t operators_length > 0 -> %d\n", operators_length > 0);
				// if(operators_length > 0)
				// printf("\t isOperator(operators, operators_length - 1) -> %d\n", isOperator(operators, operators_length - 1));
				// printf("\t number_length == 0 -> %d\n", number_length == 0);
				// printf("\t operands_length == 0 -> %d\n", operands_length == 0);
				// printf("\t operators_length == 0 -> %d\n", operators_length == 0);
				 if (number_length == 0 && operands_length == 0){
					// printf("CHANGE CHARACTER TO UNARY 1\n");
					 if(character == '+'){
						character = '`';
					} else if (character == '-'){
						character = '~';
					}
				}  else if(operators_length > 0 && isOperator(operators, operators_length - 1) && number_length == 0){
					// printf("CHANGE CHARACTER TO UNARY 2\n");
					if(character == '+'){
						character = '`';
					} else if (character == '-'){
						character = '~';
					}
				}
				if(operators_length > 0 && operators[operators_length - 1] == ')'){
					operators_length--;
				}
			
				if (number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits, &periods);
					// printf("number created: operands[%d] = %lf\n", operands_length - 1, operands[operands_length - 1]);
					if(operands_length == operands_size){
						operands = realloc(operands, ++operands_size);
					}
				} 
				while((operators_length > 0 && operators[operators_length - 1] != '(' ) && (precedence(operators[operators_length - 1]) > precedence(character) || (precedence(operators[operators_length - 1])== precedence(character)&& leftAssociative(character)))){
					// printf("Operation to be done: operators[%d] = %c\n", operators_length -1, operators[operators_length - 1]);
					operate(operators[operators_length - 1], operands, &operands_length);
					operators_length--;
				}
				operators = realloc(operators, operators_length + 1);
				operators[operators_length++] = character;
				if(operators_length == operators_size){
					operators = realloc(operators, ++operators_size);
				}
				break;
			case '\n': case EOF: case ')':
				if(number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits, &periods);
					// printf("number created: operands[%d] = %lf\n", operands_length - 1, operands[operands_length - 1]);
					if(operands_length == operands_size){
						operands = realloc(operands, ++operands_size);
					}
				}
				if(operators_length > 0 && operators[operators_length - 1] == ')'){
					operators_length--;
				}
				for(; operators_length > 0 && operators[operators_length - 1] != '(';operators_length--){
					// printf("Operation to be done: operators[%d] = %c\n", operators_length -1, operators[operators_length - 1]);
					operate(operators[operators_length - 1], operands, &operands_length);
				}
				
				if(operators_length > 0 && operators[operators_length - 1] == '('){ //If the for has calculated what's between parethesis the las operator would be a closing parenthesis, finally we delete it
					if(character == ')') operators[operators_length - 1] = character;
				}
				operators = realloc(operators, operators_length);
				break;
			case '(':
				operators[operators_length++] = character;
				break;
			default:
				/*To define*/
				break;
		}
	}while(character != '\n' && character != EOF);

	printf("%lf\n", operands[0]);
	free(number);
	free(operands);
	free(operators);
}

