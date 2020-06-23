#include <bits/stdc++.h>
using namespace std;
#include "Parameter.h"
#include "String.h"
#include "Expression.h"
#include "Keyword.h"
#include "Mail.h"
#include "Heap.h"
#include "priority.h"
#include "Order_Tree.h"

Mail mail[MAX_MAIL];
Heap<MAX_MAIL, int> longest;
Priority priority;
Order_Tree order_tree;
int mail_cnt = 0, mail_place[MAX_MAIL];
String<50> mail_file[MAX_MAIL];
unordered_map<String<50>, int> record; // record the file named for escaping adding a file repeatly

int main() {
    memset(mail_place, -1, sizeof mail_place);
    String<50> file_string;
    unordered_set<String<50>> file;
    int from_id, to_id;
    long long datel, dater;
    char c, *p;
    priority.init();
    while (scanf("%s", temp_string) != EOF) {
        switch (temp_string[0]) { // switch is more faster
            case 'a':
                assert(scanf("%s", temp_string) != EOF);
                file_string.input_temp(temp_string);
                if (file.find(file_string) == file.end()) {
                    if (record.find(file_string) != record.end()) {
                        int x = record[file_string];
                        mail_place[mail[x].id] = x;
                        longest.push(mail[x].length, mail[x].id);
                        file.insert(mail_file[mail[x].id]);
                        order_tree.insert(mail[x]);
                        priority.insert(mail[x]);
                    }
                    else {
                        file.insert(file_string);
                        FILE *f = fopen(temp_string, "r");
                        mail[mail_cnt].input(f);
                        mail_place[mail[mail_cnt].id] = mail_cnt;
                        mail_file[mail[mail_cnt].id] = file_string;
                        longest.push(mail[mail_cnt].length, mail[mail_cnt].id);
                        fclose(f);
                        order_tree.insert(mail[mail_cnt]);
                        priority.insert(mail[mail_cnt]);
                        record[file_string] = mail_cnt++;
                    }
                    printf("%d\n", int(file.size()));
                }
                else
                    puts("-");
                break;
            case 'r':
                int x;
                assert(scanf("%d", &x));
                if (!~mail_place[x])
                    puts("-");
                else {
                    order_tree.erase(mail[mail_place[x]]);
                    priority.erase(x);
                    longest.erase(x);
                    mail_place[x] = -1;
                    file.erase(mail_file[x]);
                    printf("%d\n", int(file.size()));
                }
                break;
            case 'l':
                if (file.empty())
                    puts("-");
                else
                    printf("%d %d\n", longest.top(), mail[mail_place[longest.top()]].length);
                break;
            case 'q':
                from_id = to_id = -1;
                datel = 0, dater = 1e18;
                while (scanf("%s", temp_string) && temp_string[0] == '-') {
                    switch (temp_string[1]) {
                        case 'f':
                            for (int i = 3; temp_string[i]; ++i)
                                if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                                    temp_string[i] ^= 'a' ^ 'A';
                                else if (temp_string[i] == '"')
                                    temp_string[i] = 0;
                            from_id = user_hash(temp_string + 3); 
                            break;
                        case 't':
                            for (int i = 3; temp_string[i]; ++i)
                                if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                                    temp_string[i] ^= 'a' ^ 'A';
                                else if (temp_string[i] == '"')
                                    temp_string[i] = 0;
                            to_id = user_hash(temp_string + 3); 
                            break;
                        case 'd':
                            p = temp_string + 2;
                            while ((c = *p++) != '~')
                                datel *= 10, datel += c ^ '0';
                            if (*p)
                                for (dater = 0; (c = *p++);)
                                    dater *= 10, dater += c ^ '0';
                            break;
                    }
                }
                {
                    for (int i = 0; temp_string[i]; ++i)
                        if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                            temp_string[i] ^= 'a' ^ 'A';
                    Expression exp;
                    exp.input(temp_string);
                    order_tree.query(from_id, to_id, datel, dater, exp);
                }
                break;
            case 'p':
                if (temp_string[1] == 'r') {
                    int k;
                    scanf("%d", &k);
                    auto v = priority.query(k);
                    if (v.empty())
                        puts("-");
                    else
                        for (int i = 0; i < int(v.size()); ++i)
                            printf("%d%c", v[i], " \n"[i + 1 == int(v.size())]);
                    if (int(v.size()) < k)
                        printf("The number of mail is less than %d...\n", k);
                }
                else {
                    /* code */
                }
                
        }
    }
}
