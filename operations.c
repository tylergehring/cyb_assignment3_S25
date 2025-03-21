//Tyler Gehring CYB 220.
//Purpose: functions for performing operations on either two ints or an int and a string
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <limits.h>

#define INT_MAX_VALUE INT_MAX


int add_int(int operand1, int operand2);
void add_int_char(char* operand1, char* operand2, char* result);
int subtract_int(int operand1, int operand2);
void subtract_int_char(char* operand_num, char* operand_char, char* result);
int divide_int(int operand1, int operand2);
void divide_int_char(char* operand_num, char* operand_char, char* result);
int multiply_int(int operand1, int operand2);
void multiply_int_char(char* operand_num, char* operand_char, char* result);

void parse_expression(char expression[], char** operands);
int is_operator(char op);
int valid_chars(char operation[]);
int get_length(char arr[]);
int is_digits(char* arg);
int is_alphas(char* arg);
int convert_char_dig(char* arr);

void dig_to_dig_op(char** expression, char* result);
void dig_to_char_op(char** expression, char* result, int operand2_char);

int add_int(int operand1, int operand2){
    //Check for int overflow, add operands together, return int
    return operand1 + operand2;
}

void add_int_char(char* operand_num, char* operand_str, char* result){
    //shift right. if op2 is abc and op1 is 1 the result will be bcd.
    //operand2 is already a-z or A-Z, shifts operand2 over operand1 amount, returns char*
    //convert chars in operand2 to askii vals and add the operand1 val
    int op1_int = convert_char_dig(operand_num);
    int op2_size = get_length(operand_str);
    int idx = 0;
    for (int i =0; i < op2_size; i++){
        int askii_val = (operand_str[i] - 0);
        askii_val += op1_int;
        result[i] = (char)askii_val;
        idx = i;
    }
    result[idx+1] = '\0';
}

int subtract_int(int operand1, int operand2){
    //Check for int overflow, add operands together, return int
    return operand1 - operand2;
}

void subtract_int_char(char* operand_num, char* operand_char, char* result){
    //shift right. if op2 is abc and op1 is 1 the result will be bcd.
    //operand2 is already a-z or A-Z, shifts operand2 over operand1 amount, returns char*
    //convert chars in operand2 to askii vals and add the operand1 val
    int op1 = convert_char_dig(operand_num);
    int idx;
    for (int i =0; i < get_length(operand_char); i++){
        int askii_val = (operand_char[i] - 0);
        askii_val -= op1;
        result[i] = (char)askii_val;
        idx = i;
    }
    result[idx+1] = '\0';

}

int divide_int(int operand1, int operand2){
    if(operand2 != 0){
        return operand1/operand2;
    }
    else{
        printf("You can not divide by zero!!\n");
        return -1;
    }
}

void divide_int_char(char* operand_num, char* operand_char, char* result){
    //remove operand1 amount of chars from the end of operand2 char array
    int op1 = convert_char_dig(operand_num);
    int idx = 0;
    for(int i= 0; i<((get_length(operand_char))-op1); i++){
        result[i] = operand_char[i];
        idx = i;
    }
    result[idx+1] = '\0';
}

int multiply_int(int operand1, int operand2){
    return operand1*operand2;
}

void multiply_int_char(char* operand_num, char* operand_char, char* result){
    //copy operand2 char array operand1 amount of times into a new array and return its pointer
    int op1 = convert_char_dig(operand_num);
    int idx = 0;
    int size = get_length(operand_char);
    if((op1*size)<1023){
        for (int i = 0; i < op1; i++){
            for(int j = 0; j < (size); j++){
                result[idx] = operand_char[j];
                idx++;
            }
        }
        result[idx] ='\0';
    } else {
        printf("I cannot return a string of that length...\n");
        for (int i = 0; (i < (1000/size)); i++){
            for(int j = 0; j < (size); j++){
                result[idx] = operand_char[j];
                idx++;
            }
        }
        result[idx] ='\0';
    }
}

int remainder_int(int operand1, int operand2){
    return operand1%operand2;
}

void parse_expression(char expression[], char** operands){
    //returns a 2 dimensional array of arg1, arg2, operation
    //char** operands = (char**)malloc(sizeof(char*) * 3);
    //operands[0] = (char*)malloc(sizeof(char) * 150); //operand1
    //operands[2] = (char*)malloc(sizeof(char) * 150); //operand2
    //operands[1] = (char*)malloc(sizeof(char) * 2);  //operation
    int size = get_length(expression);
    int op1_found = 0;
    int op1_idx=0; 
    int op2_idx=0;

    for(int i = 0; i<size; i++){
        if(is_operator(expression[i])){
            operands[1][0] = expression[i];
            operands[1][1] = '\0';
            op1_found = 1;
        }
        else if (op1_found){
            operands[2][op2_idx] = expression[i];
            op2_idx++;
        }
        else if (!op1_found) {
            operands[0][op1_idx] = expression[i];
            op1_idx++;
        }
    }

    operands[0][op1_idx] = '\0';
    operands[2][op2_idx] = '\0';

}

int is_operator(char op){
    //return 1 if char is operator in operators list
    char operators[5] = {'+','-','/','*','%'};
    for(int j=0; j < 5; j++){
        if (op == operators[j]){
            return 1;
        }
        else{
            continue;
        }
    }
    return 0;
}

int valid_chars(char operation[]){
    //checks the validity of the operation. returns 1 if valid
    int size = get_length(operation);
    int found_operator = 0;
    for (int i = 0; i<size-1; i++){
        if (isspace(operation[i]-0)){
            printf("No Spaces Allowed..\n");
            return 0;  
        }
        else if(isdigit(operation[i])){
            continue;
        }
        else if (isalpha(operation[i])){
            continue;
        }
        else if ((operation[i] == '+' || operation[i] == '-' || operation[i] == '/'
        || operation[i] == '*' || operation[i] == '%') && (found_operator ==0)){
            found_operator++;
            continue;
        }
        else{
            printf("ERROR.. Invalid Input\n");
            return 0;
        }
    }
    return 1;
}

int get_length(char arr[]){
    int idx = 0;
    while(arr[idx] != '\0'){
        idx++;
    }
    return idx;
}

int is_digits(char* arg){
    // returns 1 if char arr is all digits
    int size = get_length(arg);
    int arg_len = 0; //should be the same a size once we are done
    int max_askii = 57; //num 9
    int min_askii = 48; // num 0


    for (int i= 0; i<(size-1); i++){
        int askii = (arg[i]-0);
        if(askii == 45){ //'-' char
            arg_len++;
        }
        else if (askii <= max_askii && askii >= min_askii){ //dig
            arg_len++;
        }
        else{
            return 0;
        }
    
    }
    if (arg_len == (size-1)){
        return 1;
    }
    else{
        printf("ERROR:Operations.c::is_digit: {arg_len size: %d | size of char arr:%d}\n",arg_len, size);
        return 0;
    }
}

int is_alphas(char* arg){
    // returns 1 if char arr is all alpha
    int size = get_length(arg);
    int arg_len = 0; //should be the same a size once we are done

    for (int i= 0; i<(size-1); i++){
        if(isalpha(arg[i])){
            arg_len++;
        }
        else{
            return 0;
        }
    }

    if (arg_len == (size-1)){
        return 1;
    }
    else{
        printf("ERROR:Operations.c::is_digit: {arg_len size: %d | size of char arr:%d}\n",arg_len, size);
        return 0;
    }
}

int convert_char_dig(char* arr){
    /*-1 is error term for int being out of range*/
    long long int val;
    sscanf(arr, "%lld", &val);
    if ((val < INT_MAX)&& val>=0){
        return (int)val;
    }
    else{
        printf("Int is too big...\n");
        return -1;
    }
}

void convert_dig_char(char* arr, int num){
    sprintf(arr, "%d\0", num);
}

int perform_operation(char** expression, char* result){
    //returns 1 if all checks pass; performs operation and changes result char* if deemed valid
    //expression[0] = operand1
    //expression[2] = operand2
    
    int operand1_digit = is_digits(expression[0]);
    int operand2_digit = is_digits(expression[2]);
    int operand1_char = is_alphas(expression[0]);
    int operand2_char = is_alphas(expression[2]);
    int success;
    
    /*check size of digit*/
    if(operand1_digit>0){
        success = convert_char_dig(expression[0]);
        if(success == -1){
            return 0;
        }
    }
    if(operand2_digit>0){
        success = convert_char_dig(expression[2]);
        if(success == -1){
            return 0;
        }
    }

    /*check size of chars*/
    if(operand1_char>0){
        if(get_length(expression[0])>100){
            printf("String is too long...");
            return 0;
        }
    }
    if(operand2_char>0){
        if(get_length(expression[2])>100){
            printf("String is too long...");
            return 0;
        }
    }


    /*perform operations*/
    if(operand1_digit && operand2_digit){
        dig_to_dig_op(expression, result); 
        return 1;

    }
    else if ((operand1_digit && operand2_char) && (*expression[1] != '%')){
        dig_to_char_op(expression, result, 1); //1 because operand 2 is char
        return 1;
    }
    else if ((operand1_char && operand2_digit) && (*expression[1] != '%')){
        dig_to_char_op(expression, result, 0); //0 because operand 1 is char
        return 1;
    }
    else{
        return 0;
    }

}

void dig_to_dig_op(char** expression, char* result){
    int op1 = convert_char_dig(expression[0]);
    int op2 = convert_char_dig(expression[2]);
    int res_int = 0;

    if(expression[1][0] == '+'){
        res_int = add_int(op1, op2);
        convert_dig_char(result, res_int);
    }
    else if(expression[1][0] == '-'){
        res_int = subtract_int(op1, op2);
        convert_dig_char(result, res_int);
    }
    else if(expression[1][0] == '/'){
        res_int = divide_int(op1, op2);
        convert_dig_char(result, res_int);
    }
    else if(expression[1][0] == '*'){
        res_int = multiply_int(op1, op2);
        convert_dig_char(result, res_int);
    }
    else if(expression[1][0] == '%'){
        res_int = remainder_int(op1, op2);
        convert_dig_char(result, res_int);
    }
    else{
        printf("ERROR:Operations.c::dig_to_dig_op()\n");
    }
    
}

void dig_to_char_op(char** expression, char* result, int operand2_char){
    // params: parsed expression, results, bool of if operand2 is a char
    int idx_char;
    int idx_num;
    if(operand2_char){
        idx_char = 2; 
        idx_num = 0;
    }
    else{
        idx_char = 0;
        idx_num = 2;
    }
    
    if(expression[1][0] == '+'){
        add_int_char(expression[idx_num], expression[idx_char], result);
    }
    else if(expression[1][0] == '-'){
        subtract_int_char(expression[idx_num], expression[idx_char], result);
    }
    else if(expression[1][0] == '/'){
        divide_int_char(expression[idx_num], expression[idx_char], result);
    }
    else if(expression[1][0] == '*'){
        multiply_int_char(expression[idx_num], expression[idx_char], result);
    }
    else{
        printf("ERROR:Operations.c::dig_to_char_op()\n");
    }
    
}


void clear_str(char* char_arr){
    for(int i = 0; i < (get_length(char_arr)); i++){
        char_arr[i] = '\0'; //clearing data
    }
}

void clear_operands(char** operands){
    /*very specific use case on operands sturcture defined in main*/
    for(int i =0; i<3;i++){
        clear_str(operands[i]);
    }
}




