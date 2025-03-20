//Tyler Gehring CYB 220. Assignment 3;
//Purpose: Calculator that can perform operations on chars. 
//Program watches for potential overflows.

#include<stdio.h>
#include "operations.c"




int main(){
    int valid_op = 0;
    char expression[100];

    char** operands = (char**)malloc(sizeof(char*) * 3);
    operands[0] = (char*)malloc(sizeof(char) * 150); //operand1
    operands[2] = (char*)malloc(sizeof(char) * 150); //operand2
    operands[1] = (char*)malloc(sizeof(char) * 2);  //operation
    
    char* result = (char*)malloc(sizeof(char)*100);
    for(int i = 0; i<100; i++){
        result[i] = '\0';
    }


    do{
        for(int i = 0; i<100; i++){
            expression[i] = '\0';
        }
        printf("Enter Your Expression: ");
        scanf("%s", expression);
        if(valid_chars(expression)){
            parse_expression(expression, operands);
            if(perform_operation(operands, result)){
                valid_op = 1;
            }
            else{
                printf("Invalid Expression... Please Try Again. [digit,digit or digit,char]\n");
                for(int i =0; i<3;i++){
                    for(int j = 0; j < (get_length(operands[i])); j++){
                        operands[i][j] = '\0'; //clearing data
                    }
                }
            }
        }
    } while (!valid_op);

    printf("RESULT: %s\n", result);

    // 
    // if(operands[1][0] == '+'){
    //     add_int_char(operands[0], operands[2]);
    //     printf("result: %s\n", operands[2]);
    //}



    //based on operator, convert types and call operator function
    return 0;

    
}


//TO DO:
// In valid_chars... create a check for multiple operators... 
// We are not worried about negative ints
//percent int % operation