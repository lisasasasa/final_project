struct SAM{
    static const int END = 38;
    int root, lst;
    vector<int> mom, mx, acc;
    vector<unordered_map<int, int>> nxt;
    int chtonum(char c) {
        if ('a' <= c && c <= 'z')
            return c - 'a' + 1;
        if ('0' <= c && c <= '9')
            return c - '0' + 27;
        return END;
    }
    int newNode() {
        mom.push_back(0), mx.push_back(0), acc.push_back(0);
        nxt.push_back(unordered_map<int, int>());
        return int(mom.size()) - 1;
    }
    void init() {
        mom.clear(), mx.clear(), acc.clear(), nxt.clear();
        mom.push_back(0), mx.push_back(0), acc.push_back(0);
        nxt.push_back(unordered_map<int, int>());
        root = newNode();
        lst = root;
    }
    void push(int c) {
        int p = lst;
        int np = newNode();
        mx[np] = mx[p] + 1;
        for (; p && nxt[p][c] == 0; p = mom[p])
            nxt[p][c] = np;
        if (p == 0) 
            mom[np] = root;
        else {
            int q = nxt[p][c];
            if (mx[p]+1 == mx[q]) mom[np] = q;
            else{
                int nq = newNode();
                mx[nq] = mx[p]+1;
                for (int i = 0; i <= END; ++i)
                    nxt[nq][i] = nxt[q][i];
                mom[nq] = mom[q];
                mom[q] = nq;
                mom[np] = nq;
                for (; p && nxt[p][c] == q; p = mom[p])
                    nxt[p][c] = nq;
            }
        }
        lst = np;
    }
    void push(const char *str) {
        for (int i = 0; str[i]; ++i)
            push(chtonum(str[i]));
        push(END);
    }
    bool match(const char *str) {
        int p = root;
        for (int i = 0; str[i]; ++i)
            if (!nxt[p][chtonum(str[i])])
                return 0;
            else
                p = nxt[p][chtonum(str[i])];
        return 1;
    }
} ;
