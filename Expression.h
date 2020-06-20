namespace Expression{
    uint postfix[STACK_SIZE], postfix_top;
    void input(char *str) {
        uint stack_top(uint_MAX);
        postfix_top = uint_MAX;
        String<25> key; 
        // !:uint_MAX-1, &:uint_MAX-2, |:uint_MAX-3, (:uint_MAX-4
        for (char c; (c = *str); ++str) {
            switch (c) {
                case '|':
                    for (; (~stack_top) && temp_stack[stack_top] != uint_MAX - 4; --stack_top)
                        postfix[++postfix_top] = temp_stack[stack_top];
                    temp_stack[++stack_top] = uint_MAX - 3;
                    break;
                case '&':
                    for (; (~stack_top) && temp_stack[stack_top] > uint_MAX - 3; --stack_top)
                        postfix[++postfix_top] = temp_stack[stack_top];
                    temp_stack[++stack_top] = uint_MAX - 2;
                    break;
                case '!':
                    for (; (~stack_top) && temp_stack[stack_top] == uint_MAX - 1; --stack_top)
                        postfix[++postfix_top] = temp_stack[stack_top];
                    temp_stack[++stack_top] = uint_MAX - 1;
                    break;
                case '(':
                    temp_stack[++stack_top] = uint_MAX - 4;
                    break;
                case ')':
                    for (; temp_stack[stack_top] != uint_MAX - 4; --stack_top)
                        postfix[++postfix_top] = temp_stack[stack_top];
                    --stack_top;  
                    break;
                default:
                    key.input(str), --str;
                    postfix[++postfix_top] = get_keyword_index(key, 0);
                    break;
            }
        }   
        for (; (~stack_top); --stack_top)
            postfix[++postfix_top] = temp_stack[stack_top];
    }
};
