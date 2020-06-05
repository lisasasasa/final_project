class Keyword{
    unordered_set<String<25>> data;
    vector <char> stack;
public:
    bool match(Expression &exp) {
        for(int i = 0 ; i < exp.postfix.size() ; ++ i ){
            if(data.count(exp.postfix[i])) exp.postfix[i]=1;
            else exp.postfix=0; // 會不小心把運算元判掉，我要所有運算元的set 之類ㄉ判斷
        }
        for(int i = 0 ; i < exp.postfix.size() ; ++ i ){
            
        }
    }
    void insert(String &s) {
        data.insert(s);
    }
};