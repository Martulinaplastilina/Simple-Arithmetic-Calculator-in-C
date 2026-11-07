/*
 * Calculadora roñosa
 * version: 2.0
 * Intento de implementación del algoritmo de Shunting-Yard
 * Inicio: 5/11/2026
 *
 **/
#include<stdio.h>
#include<stdbool.h>

long int createInteger(int number[], int length);
double createFloat(int floatPart, long int number);
double createNumber(int numbe[], int* number_length, int* intergerDigits);
int precedence(char operator);
bool leftAssociative(char operator);
void operate(char operators[], int *operators_length, double operands[], int *operands_length);

long int createInteger(int number[], int length){
	int integer = 0;
	for(int j = 0; j < length; j++){
		integer *= 10;
		integer += number[j];
	}
	return integer;
}

double createFloat(int floatPart,long int number){
	double floatNum = number;
	for(; floatPart > 0; floatPart--){
		floatNum /= 10.0;
	}
	return floatNum;
}

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

bool leftAssociative(char operator){
	bool associativity;
	switch(operator){
		case '(': case ')':
			associativity = true;
			break;
		case '^':
			associativity = false;
			break;
		case '*': case '/':
			associativity = true;
			break;
		case '+': case '-':
			associativity = true;
			break;
		default:
			associativity = false;
			break;
	}
	return associativity;
}

void operate(char operators[], int *operators_length, double operands[], int *operands_length){
	double operand1 = operands[*operands_length-1];
	double operand2 = operands[*operands_length - 2];
	char operation = operators[*operators_length - 1];
	printf("Operand 1: operands[%d] = %f\n", *operands_length-1, operand1);
	printf("Operand 2: operands[%d] = %f\n", *operands_length-2, operand2);
	printf("Operation: operators[%d] = %c\n", *operators_length - 1, operation);
	
	double result = 0;
	printf("==OPERATE FUNCTION==\n");
	printf("Operands:\n");
	for(int i = 0; i < *operands_length; i++) printf("Operand[%d] = %f\n", i, operands[i]);
	printf("Operators:\n");
	for(int i = 0; i < *operators_length; i++) printf("Operators[%d] = %c\n", i, operators[i]);
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
	operands[*operands_length - 2] = result;
	printf("Result: operands[%d] = %f\n", *operands_length - 2, result);
	*operands_length -= 1;
}


int main(){
	int number_length = 0;
	int periods = 0;
	int integerDigits = 0;
	char character;
	int number[17];
	double operands[20];
	int operands_length = 0;
	char operators[20];
	int operators_length = 0;

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
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits);		periods = 0;
				}
							
				while((operators_length > 0 && operators[operators_length - 1] != '(') && (precedence(operators[operators_length - 1]) > precedence(character) || (precedence(operators[operators_length - 1])== precedence(character)&& leftAssociative(character)))){
					operate(operators, &operators_length, operands, &operands_length);
					operators_length--;
				}								
				operators[operators_length++] = character;
				
				break;
			case '\n':
				if(number_length > 0){
					operands[operands_length++] = createNumber(number, &number_length, &integerDigits);		periods = 0;
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
		
	for(; operators_length > 0 && operators[operators_length - 1] != '('; operators_length--){
		operate(operators, &operators_length, operands, &operands_length);
	}
	printf("%lf\n", operands[0]);
}

