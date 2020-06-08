#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef uint32_t uint;
#include "Parameter.h"
#include "String.h"
#include "Expression.h"
#include "Keyword.h"
#include "Mail.h"
#include "Heap.h"
#include "Order_Tree.h"

Mail mail[10005];
Heap<10005> longest;
Order_Tree order_tree;
uint mail_cnt = 0, mail_place[10005];
String<35> mail_file[10005];
gp_hash_table<String<35>, uint, hash<String<35>>> record; // record the file named for escaping adding a file repeatly

int main() {
    memset(mail_place, -1, sizeof mail_place);
    String<35> file_string;
    gp_hash_table<String<35>, bool, hash<String<35>>> file;
    uint from_id, to_id;
    unsigned long long datel, dater;
    char c, *p;
    while (scanf("%s", temp_string) != EOF) {
        switch (temp_string[0]) { // switch is more faster
            case 'a':
                assert(scanf("%s", temp_string) != EOF);
                file_string.input_temp(temp_string);
                if (file.find(file_string) == file.end()) {
                    if (record.find(file_string) != record.end()) {
                        uint x = record[file_string];
                        mail_place[mail[x].id] = x;
                        longest.push(mail[x].length, mail[x].id);
                        file[mail_file[mail[x].id]] = 1;
                        order_tree.insert(mail[x]);
                    }
                    else {
                        file[file_string] = 1;
                        FILE *f = fopen(temp_string, "r");
                        mail[mail_cnt].input(f);
                        mail_place[mail[mail_cnt].id] = mail_cnt;
                        mail_file[mail[mail_cnt].id] = file_string;
                        longest.push(mail[mail_cnt].length, mail[mail_cnt].id);
                        fclose(f);
                        order_tree.insert(mail[mail_cnt]);
                        record[file_string] = mail_cnt++;
                    }
                    printf("%u\n", uint(file.size()));
                }
                else
                    puts("-");
                break;
            case 'r':
                uint x;
                assert(scanf("%u", &x));
                if (!~mail_place[x])
                    puts("-");
                else {
                    order_tree.erase(mail[mail_place[x]]);
                    longest.erase(x);
                    mail_place[x] = uint_MAX;
                    file.erase(mail_file[x]);
                    printf("%u\n", uint(file.size()));
                }
                break;
            case 'l':
                if (file.empty())
                    puts("-");
                else
                    printf("%u %u\n", longest.top(), mail[mail_place[longest.top()]].length);
                break;
            case 'q':
                from_id = to_id = uint_MAX;
                datel = 0, dater = 1e18;
                while (scanf("%s", temp_string) && temp_string[0] == '-') {
                    switch (temp_string[1]) {
                        case 'f':
                            for (uint i = 3; temp_string[i]; ++i)
                                if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                                    temp_string[i] ^= 'a' ^ 'A';
                                else if (temp_string[i] == '"')
                                    temp_string[i] = 0;
                            from_id = user_hash(temp_string + 3); 
                            break;
                        case 't':
                            for (uint i = 3; temp_string[i]; ++i)
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
                for (uint i = 0; temp_string[i]; ++i)
                    if (temp_string[i] >= 'A' && temp_string[i] <= 'Z')
                        temp_string[i] ^= 'a' ^ 'A';
                Expression::input(temp_string);
                order_tree.query(from_id, to_id, datel, dater);
                break;
        }
    }
}
