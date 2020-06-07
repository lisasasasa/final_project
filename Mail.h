class Mail{
public:
    int from;
    int to;
    long long date;
    int id;
    int length;
    Keyword keyword;
    Mail(long long _date = 0, int _id = 0){
        date = _date;
        id = _id;
        length = 0;
    }
    void print() {
        printf("From: %d\n", from);
        printf("To: %d\n", to);
        printf("Date: %lld\n", date);
        printf("ID: %d\n", id);
        printf("Length: %d\n", length);
    }
    void input(FILE *file) {
        char month[15];
        String<25> word;
        assert(fgets(temp_string, TEMP_SIZE, file));
        for (int i = 6; temp_string[i]; ++i)
            if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                temp_string[i] ^= 'a' ^ 'A';
            else if (!isalphnum(temp_string[i]))
                temp_string[i] = 0;
        from = user_hash(temp_string + 6, 1);

        assert(fgets(temp_string, TEMP_SIZE, file)); 
        int dt , year , hour , min ;
        sscanf(temp_string,"Date: %d %s %d at %d:%d", &dt , month ,&year , &hour , &min);
        date = (long long)year * 100000000 + dt * 10000 + hour * 100 + min ;
        date += get_month(month) * 1000000;
        
        assert(fgets(temp_string, TEMP_SIZE, file));
        sscanf(temp_string,"Message-ID: %d", &id);

        assert(fgets(temp_string, TEMP_SIZE, file));
        for (int i = 9; temp_string[i]; ++i ) {
            if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                temp_string[i] ^= 'a' ^ 'A';
            if (!isalphnum(temp_string[i])) 
                temp_string[i] = ' ';
        }
        for (char *p = temp_string + 9; word.input(p);)
            keyword.insert(word);

        assert(fgets(temp_string, TEMP_SIZE, file));
        for (int i = 4; temp_string[i]; ++i)
            if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                temp_string[i] ^= 'a' ^ 'A';
            else if (!isalphnum(temp_string[i]))
                temp_string[i] = 0;
        to = user_hash(temp_string + 4, 1);
        
        assert(fgets(temp_string, TEMP_SIZE, file));
        length = 0;
        while (fgets(temp_string, TEMP_SIZE, file)) {
            for (int i = 0; temp_string[i]; ++i ) {
                if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                    temp_string[i] ^= 'a' ^ 'A';
                if(!isalphnum(temp_string[i])) temp_string[i] = ' ';
                else ++length;
            }
            for (char *p = temp_string; word.input(p); )
                keyword.insert(word);
        }
    }
};
