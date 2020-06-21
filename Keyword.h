class Keyword{
    unordered_set<String<25>> data;
public:
    bool match(Expression &exp) {
        int num_top = -1;
        for(int i = 0; i < int(exp.postfix.size()) ; ++i ) {
            switch (exp.postfix[i][0]) {
                case '|':
                    temp_stack[num_top - 1] |= temp_stack[num_top];
                    --num_top;
                    break;
                case '&':
                    temp_stack[num_top - 1] &= temp_stack[num_top];
                    --num_top;
                    break;
                case '!':
                    temp_stack[num_top] = !temp_stack[num_top];
                    break;
                default:
                    temp_stack[++num_top] = data.count(exp.postfix[i]);
                    break;
            }
        }
        return temp_stack[0];
    }
    bool match(string &s) {
        return data.count(String<25>(s));
    }
    void insert(String<25> &s) {
        data.insert(s);
    }
};
