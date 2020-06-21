#include "Skip_List.h"

struct Mail_Cmp {
    bool operator()(const Mail* a, const Mail* b) const {
        if (!a) return 0;
        if (!b) return 1;
        if (a -> date != b -> date)
            return a -> date < b -> date;
        return a -> id < b -> id;
    }
};

class Order_Tree {
    skip_list<Mail*, Mail_Cmp> from[user_range];
    skip_list<Mail*, Mail_Cmp> to[user_range];
    skip_list<Mail*, Mail_Cmp> all;
public:
    void query(uint from_id, uint to_id, unsigned long long begin, unsigned long long end) {
        // pruint here
        Mail beg(begin, 0), ed(end, MAX_ID);
        static uint ans_stack[MAX_ID];
        uint ans_top = uint_MAX;
        if (~from_id) {
            auto p = from[from_id].lower_bound(&beg);
            auto q = from[from_id].upper_bound(&ed);
            if (~to_id) {
                for (; p != q; ++p)
                    if ((*p) -> to == to_id && (*p) -> keyword.match())
                        ans_stack[++ans_top] = (*p) -> id;
            }
            else
                for (; p != q; ++p)
                    if ((*p) -> keyword.match())
                        ans_stack[++ans_top] = (*p) -> id;
        }
        else if (~to_id) {
            auto p = to[to_id].lower_bound(&beg);
            auto q = to[to_id].upper_bound(&ed);
            for (; p != q; ++p)
                if ((*p) -> keyword.match())
                    ans_stack[++ans_top] = (*p) -> id;
        }
        else {
            auto p = all.lower_bound(&beg);
            auto q = all.upper_bound(&ed);
            for (; p != q; ++p)
                if (assert(*p), (*p) -> keyword.match())
                    ans_stack[++ans_top] = (*p) -> id;
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
        from[M.from].insert(&M);
        to[M.to].insert(&M);
        all.insert(&M);
    }
    void erase(Mail &M) {
        from[M.from].erase(&M);
        to[M.to].erase(&M);
        all.erase(&M);
    }
};
