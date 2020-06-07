struct Mail_Cmp {
    bool operator()(const Mail* a, const Mail* b) const { 
        if (a -> date != b -> date)
            return a -> date < b -> date;
        return a -> id < b -> id;
    }
};

class Order_Tree {
    set<Mail*, Mail_Cmp> all;
    set<Mail*, Mail_Cmp> from[user_range];
    set<Mail*, Mail_Cmp> to[user_range];
public:
    void query(int from_id, int to_id, long long begin, long long end) {
        // print here
        Mail beg(begin, 0), ed(end, MAX_ID);
        vector<int> ans;
        if (~from_id) {
            auto p = from[from_id].lower_bound(&beg);
            auto q = from[from_id].upper_bound(&ed);
            if (~to_id) {
                for (; p != q; ++p)
                    if ((*p) -> to == to_id && (*p) -> keyword.match())
                        ans.push_back((*p) -> id);
            }
            else
                for (; p != q; ++p)
                    if ((*p) -> keyword.match()) {
                        ans.push_back((*p) -> id);
                    }
        }
        else if (~to_id) {
            auto p = to[to_id].lower_bound(&beg);
            auto q = to[to_id].upper_bound(&ed);
            for (; p != q; ++p)
                if ((*p) -> keyword.match())
                    ans.push_back((*p) -> id);
        }
        else {
            auto p = all.lower_bound(&beg);
            auto q = all.upper_bound(&ed);
            for (; p != q; ++p)
                if ((*p) -> keyword.match())
                    ans.push_back((*p) -> id);
        }
        if (ans.empty())
            puts("-");
        else {
            sort(ans.begin(), ans.end());
            for (int i = 0; i < int(ans.size()); ++i)
                printf("%d%c", ans[i], " \n"[i + 1 == int(ans.size())]);
        }
    }
    // When id = -1, means nothing
    void insert(Mail &M) {
        all.insert(&M);
        from[M.from].insert(&M);
        to[M.to].insert(&M);
    }
    void erase(Mail &M) {
        all.erase(&M);
        from[M.from].erase(&M);
        to[M.to].erase(&M);
    }
};
