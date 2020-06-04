class Mail{
public:
    String<55> from;
    String<55> to;
    long long date;
    int id;
    int length;
    Keyword keyword;
    void input(FILE *file) {
        char month[15];
        fgets(temp_string , 57 , file);
        from.input(temp_string + 6);

        fgets(temp_string , 40 , file); 
        int date , year , hour , min ;
        sscanf(temp_string,"%d %s %d at %d:%d", &date , month ,&year , &hour , &min);
        date = year*100000000 + date*10000 + hour*100 + min ;
        switch(month) {
            case strcpy(start,"January") == 0 :
                date += 1000000;
                break;
            case strcpy(start,"February") == 0 :
                date += 2000000;
                break;
            case strcpy(start,"March") == 0 :
                date += 3000000;
                break;
            case strcpy(start,"April") == 0 :
                date += 4000000;
                break;
            case strcpy(start,"May") == 0 :
                date += 5000000;
                break;
            case strcpy(start,"June") == 0 :
                date += 6000000;
                break;
            case strcpy(start,"July") == 0 :
                date += 7000000;
                break;
            case strcpy(start,"August") == 0 :
                date += 8000000;
                break;
            case strcpy(start,"September") == 0 :
                date += 9000000;
                break;
            case strcpy(start,"October") == 0 :
                date += 10000000;
                break;
            case strcpy(start,"November") == 0 :
                date += 11000000;
                break;
            case strcpy(start,"December") == 0 :
                date += 12000000;
                break;
            default:
                printf("Wrong!");
                break;
        }
        
        fgets(temp_string , 20 , file);
        sscanf(temp_string,"Message-ID: %d", &id);

        char subject[22];
        fgets(temp_string , 30 , file);
        sscanf(temp_string,"Subject: %s", subject);
        keyword.insert(subject);

        fgets(temp_string , 55 , file);
        to.input(temp_string + 4);
        
        fscanf(file,"%s",temp_string);
        for(int i = 0 ; i < temp_string.size() ; ++ i ){
            if(!((temp_string[i] >= 'A' && temp_string[i] <= 'Z') || (temp_string[i] >= 'a' && temp_string[i] <= 'z') 
            || (temp_string[i] >= '0' && temp_string[i] <= '9') ) ) temp_
        }
    }
}
