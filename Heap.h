template< size_t N >
class Heap {
    int cnt[N];
    priority_queue<int> data;
public:
    int push(int x) {
        data.insert(x);
    }
    int top() {
        while (cnt[data.top()])
            --cnt[data.top()], data.pop();
        return data.top();
    }
    void erase(int x) {
        ++cnt[x];
    }
    bool empty() {
        return data.empty();
    }
};
