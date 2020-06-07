const int TEMP_SIZE = 1000000;
const int STACK_SIZE = 100;
const int MAX_ID = 10000;
const int user_range = 65536;
char temp_string[TEMP_SIZE];
int temp_stack[STACK_SIZE];
int postfix[STACK_SIZE], postfix_top;

static constexpr const char month_table[] = {12, 5, 0, 8, 0, 0, 0, 1, 7, 4, 6, 3, 11, 9, 0, 10, 2};

static constexpr inline unsigned int get_month(const char *str) {
  return month_table[((str[1] & ~0x20) + (str[2] & ~0x20)) % sizeof (month_table) / sizeof (month_table[0])];
}

char user[user_range][55];
unsigned int user_hash(char *s, int flag = 0) { // Perfect hash
    unsigned int hash = 0;
    for (char c, *p = s; (c = *p); ++p)
        hash = (((hash << 6) + hash) + c) & (user_range - 1);
    if (flag) {
        if (!user[hash][0])
            strcpy(user[hash], s);
    }
    else if (strcmp(user[hash], s))
        hash = 0;
    return hash;
}

bool isalphnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}


