template< size_t N >
class String {
    char *c[N];
    int size;
public:
    String() {
        size = 0;
    }
    String(char ch) {
        c[0] = ch;
        size = 1;
        c[1] = 0;
    }
    bool operator==(const char &ch)const {
        return c[0] == ch;
    }
    void size() {
        return size;
    }
    void input(char *&s) {
        for (size = 0; (c[size] = *s) && c[size] != ' '; ++s)
            ++size;
        c[size] = 0;
    }
    size_t hash() {
        size_t rt = 0;
        for (int i = 0; i < size; ++i)
            rt = ((rt << 5) + rt + c[i]);
        return rt;
    }
};

namespace std {
    template<> struct hash<String> {
        std::size_t operator()(String const& s) const noexcept {
            return s.hash();
        }
    };
}
