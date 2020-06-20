const uint uint_MAX = 4294967295;
const uint TEMP_SIZE = 100000;
const uint STACK_SIZE = 100;
const uint MAX_ID = 10000;
const uint user_range = 65536;
char temp_string[TEMP_SIZE];
uint temp_stack[STACK_SIZE];

static constexpr const char month_table[] = {12, 5, 0, 8, 0, 0, 0, 1, 7, 4, 6, 3, 11, 9, 0, 10, 2};

static constexpr inline uint get_month(const char *str) {
  return month_table[((str[1] & ~0x20) + (str[2] & ~0x20)) % sizeof (month_table) / sizeof (month_table[0])];
}

char user[user_range][55];
inline uint user_hash(char *s, uint flag = 0) { // Perfect hash
    uint hash(0);
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

inline bool isalphnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

