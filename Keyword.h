class Keyword{
    gp_hash_table<int, bool> data;
public:
    bool match() {
        int num_top = -1;
        for(int i = 0; i <= postfix_top ; ++i ) {
            switch (postfix[i]) {
                case -3:
                    temp_stack[num_top - 1] |= temp_stack[num_top];
                    --num_top;
                    break;
                case -2:
                    temp_stack[num_top - 1] &= temp_stack[num_top];
                    --num_top;
                    break;
                case -1:
                    temp_stack[num_top] = !temp_stack[num_top];
                    break;
                default:
                    temp_stack[++num_top] = (data.find(postfix[i]) != data.end());
                    break;
            }
        }
        return temp_stack[0];
    }
    void insert(int x) {
        data[x] = 1;
    }
};

