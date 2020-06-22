template< size_t N, typename T >
class Heap {
    int cnt[N] ;
    int Top = 0 ;
    pair<T, int> data[N];
public:
    void push(T x,int num) {
        data.push(pair<T, int>(x, -num));
    }
    T top() {
        while (!data.empty() && cnt[-data.top().second])
            --cnt[-data.top().second], data.pop();
        return -data.top().second;
    }
    void erase(int num) {
        ++cnt[num];
    }
    bool empty() {
        while (!data.empty() && cnt[-data.top().second])
            --cnt[-data.top().second], data.pop();
        return data.empty();
    }
    void kth() {

    }
};
