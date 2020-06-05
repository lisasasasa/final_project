template< size_t N >
class Heap {
    int cnt[N];
    priority_queue<int> data;
public:
    void push(int x) {
        data.push(x);
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
        while (cnt[data.top()])
            --cnt[data.top()], data.pop();
        return data.empty();
    }
};
