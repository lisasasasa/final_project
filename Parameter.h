const int TEMP_SIZE = 10000000;
const int MAX_ID = 10000;
const int user_range = 65536;
char temp_string[TEMP_SIZE];

char user[user_range][55];
unsigned int user_hash(char *s, int flag = 0) { // Perfect hash
    //printf("hash: %s %d\n",s,flag);
    unsigned int hash = 0;
    for (char c, *p = s; (c = *p); ++p)
        if (c != '"')
            hash = (((hash << 6) + hash) + c) & (user_range - 1);
    if (flag)
        strcpy(user[hash], s);
    else if (strcmp(user[hash], s))
        hash = 0;
    return hash;
}

bool isalphnum(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}


