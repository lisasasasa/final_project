const int MAX_ID = 10000;
const int user_range = 262144;
char *temp_string[10000000];

unsigned int user_hash(char *s) { // Perfect hash
    unsigned int hash = 0;
    for (char c; c = *str; ++str)
        if (c != '"')
            hash = (((hash << 6) + hash) + c) & (user_range - 1);
    return hash;
}
