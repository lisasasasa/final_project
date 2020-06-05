#include <bits/stdc++.h>
using namespace std;
#include "Parameter.h"
#include "String.h"
#include "Expression.h"
#include "Keyword.h"
#include "Mail.h"
#include "Heap.h"
#include "Order_Tree.h"

Mail mail[10005];
Heap<5000000> longest;
Order_Tree order_tree;
int mail_cnt = 0, mail_place[10005];
String<50> mail_file[10005];
unordered_map<String, int> record; // record the file named for escaping adding a file repeatly

int main() {
    memset(mail_place, -1, sizeof mail_place);
    String<50> file_string;
    unordered_set<String<50>> file;
    while (scanf("%s", temp_string) != EOF) {
        switch (temp_string[0]) { // switch is more faster
            case 'a':
                file_string.input(stdin);
                if (file.find(file_string) == file.end()) {
                    file.insert(file_string);
                    FILE *f = fopen(temp_string, "w");
                    mail[mail_cnt].input(f);
                    mail_place[mail[mail_cnt].id] = mail_cnt;
                    mail_file[mail[mail_cnt].id] = file_string;
                    longest.push(mail[mail_cnt].length);
                    fclose(f);
                    record[file_string] = mail_cnt++;
                    printf("%d\n", file.size());
                }
                else if (record.find(file_string) != record.end()) {
                    int x = record[file_string];
                    mail_place[mail[x].id] = x;
                    longest.push(mail[x].length);
                    file.insert(mail_file[x]);
                    printf("%d\n", file.size());
                }
                else
                    puts("-");
                break;
            case 'r':
                int x;
                fread(&x, sizeof(int), 1, stdin);
                if (~mail[x])
                    puts("-");
                else {
                    mail_place[x] = -1;
                    file.erase(mail_file[x]);
                    printf("%d\n", file.size());
                }
                break;
            case 'l':
                if (file.empty())
                    puts("-");
                else
                    printf("%d\n", longest.top());
                break;
            case 'q':
                int from_id, to_id;
                long long datel = 0, dater = 1e18;
                Expression exp;
                while (scanf("%s", temp_string) && temp_string[0] == '-') {
                    switch (temp_string[1]):
                        case 'f':
                            from_id = user_hash(temp_string + 2); 
                            break;
                        case 't':
                            to_id = user_hash(temp_string + 2); 
                            break;
                        case 'd'
                            char c, *p = temp_string + 2;
                            while ((c = *p++) != '~')
                                datel *= 10, datel += c ^ '0';
                            if (*p)
                                for (dater = 0; c = *p++;)
                                    dater *= 10, dater += c ^ '0';
                            break;
                }
                exp.input(temp_string);
                order_tree.query(from_id, to_id, datel, dater, exp);
                break;
        }
    }
}
