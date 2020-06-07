template< size_t N >
class Heap {
    bitset<N> vis;
    priority_queue<pair<int, int>> data;
public:
    void push(int x,int num) {
        data.push(pair<int, int>(x, -num));
        vis[num] = 1;
    }
    int top() {
        while (!data.empty() && !vis[-data.top().second])
            data.pop();
        return -data.top().second;
    }
    void erase(int num) {
        vis[num] = 0;
    }
    bool empty() {
        while (!data.empty() && !vis[-data.top().second])
            data.pop();
        return data.empty();
    }
};
