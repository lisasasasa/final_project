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
        String<25> word;
        assert(fgets(temp_string, TEMP_SIZE, file));
        for (int i = 6; temp_string[i]; ++i)
            if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                temp_string[i] ^= 'a' ^ 'A';
            else if (!isalphnum(temp_string[i]))
                temp_string[i] = 0;
        from = user_hash(temp_string + 6, 1);

        assert(fgets(temp_string, TEMP_SIZE, file)); 
        int x = 0;
        char *tp = temp_string + 6, c;
        for (date = 0; (c = *tp++) != ' ';)
            date *= 10, date += c ^ '0';
        date *= 10000;
        date += get_month(tp) * 1000000;
        for (; (*tp++) != ' ';);
        for (x = 0; (c = *tp++) != ' ';)
            x *= 10, x += c ^ '0'; 
        date += (long long)x * 100000000;
        for (x = 0, tp += 3; (c = *tp++) != ':';)
            x *= 10, x += c ^ '0'; 
        date += x * 100;
        for (x = 0; (c = *tp++) >= '0';)
            x *= 10, x += c ^ '0'; 
        date += x;
       
        assert(fgets(temp_string, TEMP_SIZE, file));
        for (id = 0, tp = temp_string + 12; (c = *tp++) >= '0';)
            id *= 10, id += c ^ '0';

        assert(fgets(temp_string, TEMP_SIZE, file));
        for (int i = 9; temp_string[i]; ++i ) {
            if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                temp_string[i] ^= 'a' ^ 'A';
            if (!isalphnum(temp_string[i])) 
                temp_string[i] = ' ';
        }
        for (char *p = temp_string + 9; word.input(p);)
            keyword.insert(get_keyword_index(word));

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
                keyword.insert(get_keyword_index(word));
        }
    }
};
