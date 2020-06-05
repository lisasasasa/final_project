class Keyword{
    unordered_set<String<25>> data;
public:
    bool match(Expression &exp) {
        vector<char> stack;
        vector<int> num;
        //for (auto i:exp.postfix)
        //    i.print(),printf(" ");
       // puts("");
        for(int i = 0, second; i < int(exp.postfix.size()) ; ++i ) {
            switch (exp.postfix[i][0]) {
                case '|':
                    second = num.back();
                    num.pop_back();
                    num.back() = num.back() | second;
                    break;
                case '&':
                    second = num.back();
                    num.pop_back();
                    num.back() = num.back() & second;
                    break;
                case '!':
                    num.back() = !num.back();
                    break;
                default:
                    //exp.postfix[i].print();
                    //printf(" %d\n",int(data.count(exp.postfix[i])));
                    num.push_back(data.count(exp.postfix[i]));
                    break;
            }
        }
        return num[0];
    }
    void insert(String<25> &s) {
        data.insert(s);
    }
};
