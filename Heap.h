template< size_t N >
class Heap {
    int cnt[N];
    priority_queue<pair<int, int>> data;
public:
    void push(int x,int num) {
        data.push(pair<int, int>(x, -num));
    }
    int top() {
        while (!data.empty() && cnt[-data.top().second])
            --cnt[data.top().second], data.pop();
        return -data.top().second;
    }
    void erase(int num) {
        ++cnt[num];
    }
    bool empty() {
        while (!data.empty() && cnt[-data.top().second])
            --cnt[data.top().second], data.pop();
        return data.empty();
    }
};
