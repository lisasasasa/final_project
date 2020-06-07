class Expression{
public:
    vector<int> postfix;
    void input(char *str) {
        int stack_top = -1;
        String<25> key; 
        // !:-1, &:-2, |:-3, (:-4
        for (char c; (c = *str); ++str) {
            switch (c) {
                case '|':
                    for (; (~stack_top) && temp_stack[stack_top] != -4; --stack_top)
                        postfix.push_back(temp_stack[stack_top]);
                    temp_stack[++stack_top] = -3;
                    break;
                case '&':
                    for (; (~stack_top) && temp_stack[stack_top] > -3; --stack_top)
                        postfix.push_back(temp_stack[stack_top]);
                    temp_stack[++stack_top] = -2;
                    break;
                case '!':
                    for (; (~stack_top) && temp_stack[stack_top] == -1; --stack_top)
                        postfix.push_back(temp_stack[stack_top]);
                    temp_stack[++stack_top] = -1;
                    break;
                case '(':
                    temp_stack[++stack_top] = -4;
                    break;
                case ')':
                    for (; temp_stack[stack_top] != -4; --stack_top)
                        postfix.push_back(temp_stack[stack_top]);
                    --stack_top;  
                    break;
                default:
                    key.input(str), --str;
                    postfix.push_back(get_keyword_index(key, 0));
                    break;
            }
        }   
        for (; (~stack_top); --stack_top)
            postfix.push_back(temp_stack[stack_top]);
    }
};
