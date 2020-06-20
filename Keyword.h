class Keyword{
    gp_hash_table<uint, bool> data;
public:
    bool match() {
        uint num_top(uint_MAX);
        for(uint i = 0; i <= Expression::postfix_top ; ++i ) {
            switch (Expression::postfix[i]) {
                case uint_MAX - 3:
                    temp_stack[num_top - 1] |= temp_stack[num_top];
                    --num_top;
                    break;
                case uint_MAX - 2:
                    temp_stack[num_top - 1] &= temp_stack[num_top];
                    --num_top;
                    break;
                case uint_MAX - 1:
                    temp_stack[num_top] = !temp_stack[num_top];
                    break;
                default:
                    temp_stack[++num_top] = (data.find(Expression::postfix[i]) != data.end());
                    break;
            }
        }
        return temp_stack[0];
    }
    void insert(uint x) {
        data[x] = 1;
    }
};

