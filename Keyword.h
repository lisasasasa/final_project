struct String_Cmp {
    bool operator()(const char *a, const char *b) const{
        return strcmp(a, b) < 0;
    }
};

class Keyword{
    set<char*, String_Cmp> suffix_set;
    String<25> pool[4000];
    int pool_top = -1;
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
                    {
                        auto p = suffix_set.lower_bound(exp.postfix[i].c_str(1));
                        int res = 0;
                        if (p != suffix_set.end()) {
                            res = 1;
                            for (int j = 1; j < exp.postfix[i].size(); ++j)
                                if ((*p)[j - 1] != exp.postfix[i][j]) {
                                    res = 0;
                                    break;
                                }

                        }
                        temp_stack[++num_top] = res;
                    }
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
            pool[++pool_top] = s;
            data[s] = 1;
            for (int i = 0; i < s.size(); ++i)
                suffix_set.insert(pool[pool_top].c_str(i));
        }
        else {
            ++data[s];
        }
    }
};
