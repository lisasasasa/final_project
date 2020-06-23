#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <utility>
#include "Mail.h"
const int user_range = 65536;
using namespace std;
#ifndef run
#include<bits/stdc++.h>
using namespace std;
#include "String.h"
#endif

class statistics{
    class user_stat{
        public:
        unordered_map<int, int> time_interval; 
        multiset<pair<int, int>> time_times;
        unordered_map<String<25>, int> keywords;
        multiset<pair<int, String<25>>, greater<pair<int, String<25>>>> keyword_times;
    };
    user_stat users[user_range];
    int m, n;
    unordered_set<String<25>> filter;
    statistics(Mail mail, int _m, int _n):m(_m), n(_n){};
    public:
    void add_statistics(Mail mail){
        //time
        int user = mail.from, time = (mail.date / 100) % 10000;
        if(users[user].time_interval.find(time) == users[user].time_interval.end()){
            users[user].time_interval[time] = 1;
        }
        else{
            users[user].time_times.erase(make_pair(users[user].time_interval[time],time));
            users[user].time_interval[time]++;
        }
        users[user].time_times.insert(make_pair(users[user].time_interval[time],time));
        //keywords
        for (auto it = mail.keyword.data.begin(); it != mail.keyword.data.end(); ++it){
            if(users[user].keywords.find(it) == users[user].keywords.end()){
                users[user].keywords[it] = 1;
            }
            else{
                users[user].keyword_times.erase(make_pair(users[user].keywords[it], it));
                users[user].keywords[it]++;
            }
            users[user].keyword_times.insert(make_pair(users[user].keywords[it], it));
        }
    }
    void peek(int user){
        int count = 0;
        printf("time interval :\n");
        for (auto it = users[user].time_times.begin(); it != users[user].time_times.end(); ++it){
            printf("%d:00 to %d:00 : %d times", it -> second, it -> second + 1, it->first);
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