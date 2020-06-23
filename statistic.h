class Statistics{
    class user_stat{
        public:
        unordered_map<int, int> time_interval; 
        multiset<pair<int, int>> time_times;
        unordered_map<String<25>, int> keywords;
        multiset<pair<int, String<25>>, greater<pair<int, String<25>>>> keyword_times;
    };
    user_stat users[user_range];
    unordered_set<String<25>> filter;
    public:
    void add_statistics(Mail &mail){
        //time
        int user = mail.from, time = (mail.date / 100) % 100;
        if(users[user].time_interval.find(time) == users[user].time_interval.end()){
            users[user].time_interval[time] = 1;
        }
        else{
            users[user].time_times.erase(make_pair(users[user].time_interval[time],time));
            users[user].time_interval[time]++;
        }
        users[user].time_times.insert(make_pair(users[user].time_interval[time],time));
        //keywords
        auto dt = mail.keyword.get_data();
        for (auto it = dt.begin(); it != dt.end(); ++it){
            if(users[user].keywords.find(it -> first) == users[user].keywords.end()){
                users[user].keywords[it -> first] = it -> second;
            }
            else{
                users[user].keyword_times.erase(make_pair(users[user].keywords[it -> first], it -> first));
                users[user].keywords[it -> first] += it -> second;
            }
            users[user].keyword_times.insert(make_pair(users[user].keywords[it -> first], it -> first));
        }
    }
    void remove_statistics(Mail &mail){
        //time
        int user = mail.from, time = (mail.date / 100 % 100);
        users[user].time_times.erase(make_pair(users[user].time_interval[time],time));
        users[user].time_interval[time]--;
        if (users[user].time_interval[time] == 0)
            users[user].time_interval.erase(time);
        else
            users[user].time_times.insert(make_pair(users[user].time_interval[time],time));
        //keywords
        auto dt = mail.keyword.get_data();
        for (auto it = dt.begin(); it != dt.end(); ++it){
            users[user].keyword_times.erase(make_pair(users[user].keywords[it -> first], it -> first));
            users[user].keywords[it -> first] -= it -> second;
            if (users[user].keywords[it -> first] == 0)
                users[user].keywords.erase(it -> first);
            else
                users[user].keyword_times.insert(make_pair(users[user].keywords[it -> first], it -> first));
        }
    }
    void peek(int user, int m, int n){
        int count = 0;
        printf("time interval :\n");
        for (auto it = users[user].time_times.begin(); it != users[user].time_times.end(); ++it){
            printf("%d:00 to %d:00 : %d times\n", it -> second, it -> second + 1, it->first);
            count++;
            if(count >= m)break;
        }
        printf("keywords :\n");
        count = 0;
        for (auto it = users[user].keyword_times.begin(); it != users[user].keyword_times.end(); ++it){
            printf("%s : %d times\n", (it->second).c_str(), it->first);
            count++;
            if(count >= n)break;
        }
    }
};
