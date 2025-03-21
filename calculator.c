//Tyler Gehring CYB 220. Assignment 3;
//Purpose: Calculator that can perform operations on chars. 
//Program watches for potential overflows.

#include<stdio.h>
#include "operations.c"


int main(){
    int valid_op = 0;
    char expression[500];

    char** operands = (char**)malloc(sizeof(char*) * 3);
    operands[0] = (char*)malloc(sizeof(char) * 250); //operand1
    operands[2] = (char*)malloc(sizeof(char) * 250); //operand2
    operands[1] = (char*)malloc(sizeof(char) * 2);  //operation
    
    char* result = (char*)malloc(sizeof(char)*100);
    for(int i = 0; i<100; i++){
        result[i] = '\0';
    }

    
    while(1){ 
        for(int i =0; i<500; i++){
            expression[i] = '\0';
        }
        printf("Enter Your Expression: ");
        scanf("%s", expression);
        if(valid_chars(expression)){
            /*Check Exit*/
            if (expression[0] == 'e' && expression[1] == 'x' && expression[2] == 'i' && expression[3] == 't'){
                break;
            }
            /*Continue Operation*/
            parse_expression(expression, operands);
            int val = perform_operation(operands, result);
            if(val){
                printf("RESULT: %s\n", result);
            }
            else{
                printf("Invalid Expression... Please Try Again. [digit,digit or digit,char]\n");
            }
        }
        clear_operands(operands);
        clear_str(result);
    }

    return 0;
    }




//TO DO:
// In valid_chars... create a check for multiple operators... 
// We are not worried about negative ints
//percent int % operation

/*
RECQUIREMENTS:
- string operand can only be 100 chars
- If the integer is > INT_MAX or <0, reject it
- in expression No whitespace allowed
- check for potential integer overflow/underflow and divide by zero.
- for * of strings  If after the expansion, the string is longer than 1024 characters (abc*500), print a message
    about it (“result string is too long” or something similar) and only keep 1024 characters
    and ignore the later characters
-Make your calculator run multiple times until the user enters “exit” to terminate the program.
-For all of the numbers, use signed int as their data type
- Your program should provide meaning messages




if (expression[0] == 'e' && expression[1] == 'x' && expression[2] == 'i' && expression[3] == 't'){
                exit_lp = 1;
                break;
            }
*/