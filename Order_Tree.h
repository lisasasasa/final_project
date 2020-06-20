#include "Treap.h"

struct Mail_Cmp {
    bool operator()(Mail* const &a, Mail* const &b) const { 
        if (a -> date != b -> date)
            return a -> date < b -> date;
        return a -> id < b -> id;
    }
};

class Order_Tree {
    Treap<Mail*, Mail_Cmp> from[user_range];
    Treap<Mail*, Mail_Cmp> to[user_range];
    Treap<Mail*, Mail_Cmp> all;
public:
    void query(uint from_id, uint to_id, unsigned long long begin, unsigned long long end) {
        // print here
        Mail beg(begin, 0), ed(end, MAX_ID);
        static uint ans_stack[MAX_ID];
        uint ans_top = uint_MAX;
        if (~from_id) {
            from[from_id].find(&beg, &ed, to_id, ans_stack, ans_top);
        }
        else if (~to_id) {
            to[to_id].find(&beg, &ed, -1, ans_stack, ans_top);
        }
        else {
            all.find(&beg, &ed, -1, ans_stack, ans_top);
        }
        if (!~ans_top)
            puts("-");
        else {
            sort(ans_stack, ans_stack + ans_top + 1);
            for (uint i = 0; i <= ans_top; ++i)
                printf("%u%c", ans_stack[i], " \n"[i == ans_top]);
        }
    }
    // When id = -1, means nothing
    void insert(Mail &M) {
        from[M.from].insert(&M), to[M.to].insert(&M), all.insert(&M);
    }
    void erase(Mail &M) {
        from[M.from].erase(&M), to[M.to].erase(&M), all.erase(&M);
    }
};
