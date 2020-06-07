class Keyword{
    unordered_set<String<25>> data;
public:
    bool match(Expression &exp) {
        int num_top = -1;
        //for (auto i:exp.postfix)
        //    i.print(),printf(" ");
       // puts("");
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
                    //exp.postfix[i].print();
                    //printf(" %d\n",int(data.count(exp.postfix[i])));
                    temp_stack[++num_top] = data.count(exp.postfix[i]);
                    break;
            }
        }
        return temp_stack[0];
    }
    void insert(String<25> &s) {
        if (s.size() < 25)
            data.insert(s);
    }
};
