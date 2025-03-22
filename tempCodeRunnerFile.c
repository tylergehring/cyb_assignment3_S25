

int main(){
    int valid_op = 0;
    char expression[300];

    char** operands = (char**)malloc(sizeof(char*) * 3);
    operands[0] = (char*)malloc(sizeof(char) * 250); //operand1
    operands[2] = (char*)malloc(sizeof(char) * 250); //operand2
    operands[1] = (char*)malloc(sizeof(char) * 2);  //operation
    
    char* result = (char*)malloc(sizeof(char)*1024);
    for(int i = 0; i<1024; i++){
        result[i] = '\0';
    }


    while(1){ 
        for(int i =0; i<300; i++){
            expression[i] = '\0';
        }
        printf("Enter Your Expression: ");
        fgets(expression, 200, stdin);
        if((valid_chars(expression)) > 0){
            /*Check Exit*/
            if (expression[0] == 'e' && expression[1] == 'x' && expression[2] == 'i' && expression[3] == 't'){
                break;
            }
            /*Continue Operation*/
            parse_expression(expression, operands);
            int val = perform_operation(operands, result);
            if(val){