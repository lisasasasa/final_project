class Expression{
public:
    vector<String<25>> postfix;
    void input(char *str) {
        vector<char> operator_stack;
        String<25> key; 
        for (char c; c = *str; ++str) {
            switch (c) {
                case '|':
                    while (!operator_stack.empty() && operator_stack.back() != '(')
                        postfix.push_back(String(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '&':
                    while (!operator_stack.empty() && operator_stack.back() != '&' && operator_stack.back() != '(')
                        postfix.push_back(String(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '!':
                    while (!operator_stack.empty() && operator_stack.back() == '!')
                        postfix.push_back(String(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '(':
                    operator_stack.push_back('(');
                    break;
                case ')':
                    while (operator_stack.back() != '(')
                        postfix.push_back(String(operator_stack.back()));
                    operator_stack.pop_back();  
                    break;
                default:
                    key.input(str);
                    postfix.push_back(key);
                    break;
            }
            while (!operator_stack.empty())
                postfix.push_back(String(operator_stack.back()));
        }    
    }
};
