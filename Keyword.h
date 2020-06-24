#include "SAM.h"

struct String_Cmp {
    bool operator()(const char *a, const char *b) const{
        return strcmp(a, b) < 0;
    }
};

class Keyword{
    SAM sam;
    unordered_map<String<25>, int> data;
public:
    unordered_map<String<25>, int>& get_data() {
        return data;
    }
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
                case '[':
                    temp_stack[++num_top] = sam.match(exp.postfix[i].c_str(1));
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
        auto p = data.find(s);
        if (p == data.end()) {
            data[s] = 1;
            sam.push(s.c_str());
        }
        else {
            ++data[s];
        }
    }
    void init() {
        sam.init();
    }
};
