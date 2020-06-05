struct Mail_Cmp {
    bool operator()(const Mail*& a, const Mail*& b) const { 
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
    void query(int from_id, int to_id, long long begin, long long end, Expression &exp) {
        // print here
        vector<int> ans;
        if (~from_id) {
            auto p = from[from_id].lower_bound(Mail(begin, 0));
            auto q = from[from_id].upper_bound(Mail(end, MAX_ID));
            if (~to_id)
                for (; p != q; ++p)
                    if (*p -> to == to_id && *p -> match(exp)) {
                        ans.push_back(*p -> id);
                    }
            else
                for (; p != q; ++p)
                    if (*p -> match(exp)) {
                        ans.push_back(*p -> id);
                    }
        }
        else if (~to_id) {
            auto p = to[to_id].lower_bound(Mail(begin, 0));
            auto q = to[to_id].upper_bound(Mail(end, MAX_ID));
            for (; p != q; ++p)
                if (*p -> match(exp))
                    ans.push_back(*p -> id);
        }
        else {
            auto p = all.lower_bound(Mail(begin, 0));
            auto q = all.upper_bound(Mail(end, MAX_ID));
            for (; p != q; ++p)
                if (*p -> match(exp))
                    ans.push_back(*p -> id);
        }
        sort(ans.begin(), ans.end());
        for (int i = 0; i < int(ans.size()); ++i)
            cout << ans[i] << " \n"[i + 1 == int(ans.size())];
    }
    // When id = -1, means nothing
};
