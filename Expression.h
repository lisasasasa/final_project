class Expression{
public:
    vector<String<25>> postfix;
    void input(char *str) {
        int stack_top = -1;
        String<25> key; 
        for (char c; (c = *str); ++str) {
            switch (c) {
                case '|':
                    for (; (~stack_top) && temp_char_stack[stack_top] != '('; --stack_top)
                        postfix.push_back(String<25>(temp_char_stack[stack_top]));
                    temp_char_stack[++stack_top] = c;
                    break;
                case '&':
                    for (; (~stack_top) && temp_char_stack[stack_top] != '|' && temp_char_stack[stack_top] != '('; --stack_top)
                        postfix.push_back(String<25>(temp_char_stack[stack_top]));
                    temp_char_stack[++stack_top] = c;
                    break;
                case '!':
                    for (; (~stack_top) && temp_char_stack[stack_top] == '!'; --stack_top)
                        postfix.push_back(String<25>(temp_char_stack[stack_top]));
                    temp_char_stack[++stack_top] = c;
                    break;
                case '(':
                    temp_char_stack[++stack_top] = c;
                    break;
                case ')':
                    for (; temp_char_stack[stack_top] != '('; --stack_top)
                        postfix.push_back(String<25>(temp_char_stack[stack_top]));
                    --stack_top;  
                    break;
                default:
                    key.input(str), --str;
                    postfix.push_back(key);
                    break;
            }
        }   
        for (; (~stack_top); --stack_top)
            postfix.push_back(String<25>(temp_char_stack[stack_top]));
    }
};
