class Keyword{
    unordered_set<String<25>> data;
    vector <char> stack;
    vector <int> num;
public:
    bool match(Expression &exp) {
        for(int i = 0 ; i < exp.postfix.size() ; ++ i ){
            if(data.count(exp.postfix[i])) exp.postfix[i]=1;
            else if (exp.postfix[i] != "|" && exp.postfix[i] != "&" && exp.postfix[i] != "!") exp.postfix[i]=0; 
        }
        for(int i = 0 ; i < exp.postfix.size() ; ++ i ){
            if(exp.postfix[i] != "|" && exp.postfix[i] != "&" && exp.postfix[i] != "!") num.push_back(exp.postfix[i][0]-'0');
            else if(exp.postfix[i] != "!") num.back() = !num.back() ;
            else{
                int second = num.back() ;
                num.pop_back();
                if(exp.postfix[i] != "&") num.back() = num.back() & second ;
                else num.back() = num.back() | second ;
            }
        }
        return num[0] ;
    }
    void insert(String &s) {
        data.insert(s);
    }
};