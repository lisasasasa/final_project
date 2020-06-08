template< size_t N >
class Heap {
    bitset<N> vis;
    priority_queue<pair<uint, uint>> data;
public:
    void push(uint x,uint num) {
        data.push(pair<uint, uint>(x, ~num));
        vis[num] = 1;
    }
    uint top() {
        while (!data.empty() && !vis[~data.top().second])
            data.pop();
        return ~data.top().second;
    }
    void erase(uint num) {
        vis[num] = 0;
    }
    bool empty() {
        while (!data.empty() && !vis[~data.top().second])
            data.pop();
        return data.empty();
    }
};
