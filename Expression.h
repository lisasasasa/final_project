class Expression{
public:
    vector<String<25>> postfix;
    void input(char *str) {
        vector<char> operator_stack;
        String<25> key; 
        for (char c; (c = *str); ++str) {
            switch (c) {
                case '|':
                    for (; !operator_stack.empty() && operator_stack.back() != '('; operator_stack.pop_back())
                        postfix.push_back(String<25>(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '&':
                    for (; !operator_stack.empty() && operator_stack.back() != '|' && operator_stack.back() != '('; operator_stack.pop_back())
                        postfix.push_back(String<25>(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '!':
                    for (; !operator_stack.empty() && operator_stack.back() == '!'; operator_stack.pop_back())
                        postfix.push_back(String<25>(operator_stack.back()));
                    operator_stack.push_back(c);
                    break;
                case '(':
                    operator_stack.push_back('(');
                    break;
                case ')':
                    for (; operator_stack.back() != '('; operator_stack.pop_back())
                        postfix.push_back(String<25>(operator_stack.back()));
                    operator_stack.pop_back();  
                    break;
                case '[':
                    key.input_ex(str);
                    postfix.push_back(key);
                    break;
                default:
                    key.input(str), --str;
                    postfix.push_back(key);
                    break;
            }
        }   
        for (; !operator_stack.empty(); operator_stack.pop_back())
            postfix.push_back(String<25>(operator_stack.back()));
    }
};
