template< size_t N >
class String {
    char c[N];
    int the_size;
public:
    bool operator==(const String<N> &s) const{
        return strcmp(c, s.c) == 0;
    }
    String() {
        the_size = 0;
    }
    String(char ch) {
        c[0] = ch;
        the_size = 1;
        c[1] = 0;
    }
    char& operator[](int idx) {
        return c[idx];
    }
    int size() {
        return the_size;
    }
    int input(char *&s) {
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
    int input_temp(char *s) {
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
        for (int i = 0; i < the_size; ++i)
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
        return hash<int>()(s.hash());
      }
    };
}
