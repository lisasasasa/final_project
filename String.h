template< size_t N >
class String {
    char c[N];
    uint the_size;
public:
    bool operator==(const String<N> &s) const{
        return strcmp(c, s.c) == 0;
    }
    String(): the_size(0) {}
    String(char ch): the_size(1) {
        c[0] = ch, c[1] = 0;
    }
    char& operator[](uint idx) {
        return c[idx];
    }
    uint size() {
        return the_size;
    }
    uint input(char *&s) {
        while (*s == ' ')
            ++s;
        if (*s == 0)
            return 0;
        for (the_size = 0; (c[the_size] = *s) && isalphnum(c[the_size]); ++s)
            if (the_size < 25)
                ++the_size;
        c[the_size] = 0;
        return 1;
    }
    uint input_temp(char *s) {
        while (*s == ' ')
            ++s;
        if (*s == 0)
            return 0;
        for (the_size = 0; (c[the_size] = *s); ++s)
            ++the_size;
        c[the_size] = 0;
        return 1;
    }
    size_t hash() const{
        size_t rt = 0;
        for (uint i = 0; i < the_size; ++i)
            rt = ((rt << 5) + rt + c[i]);
        return rt;
    }
    void print() {
        printf("%s", c);
    }
};

namespace std {
    template<size_t N>
    struct hash<String<N>> {
      size_t operator()(const String<N> &s) const {
        return hash<uint>()(s.hash());
      }
    };
}

gp_hash_table<String<25>, uint, hash<String<25>>> keyword_table;
uint keyword_cnt = 0;

uint get_keyword_index(String<25> &s, uint flag = 1) {
    auto p = keyword_table.find(s);
    if (p == keyword_table.end()) {
        if (flag)
            return keyword_table[s] = ++keyword_cnt;
        else
            return 0;
    }
    return p -> second;
}
