template<typename T, class Compare = less<T>>
class Treap {
    Compare comp;
    class Node {
    public:
        T data;
        uint pri;
        Node *l, *r;
        Node(){}
        Node(const T &k):data(k), pri(rand()), l(0), r(0){}
    };
    static const uint C = 100000;
    static Node mem[C];
    static uint mem_stack[C], mem_top, mem_stack_top;
    Node* newNode(const T &k) {
        if (mem_top == C)
            return &(mem[mem_stack[--mem_stack_top]] = Node(k));
        return &(mem[mem_top++] = Node(k));
    }
    void delNode(Node *&p) {
        mem_stack[mem_stack_top++] = p - mem;
    }
    Node* root;
    Node *merge(Node *a, Node *b) {
        if (!a || !b)
            return a ? a : b;
        if (a -> pri < b -> pri)
            return a -> r = merge(a -> r, b), a;
        return b -> l = merge(a, b -> l), b;
    }
    void split(Node *o, Node *&a, Node *&b, const T &k) {
        if (!o)
            return a = b = 0, void();
        if (comp(o -> data, k))
            a = o, split(o -> r, a -> r, b, k);
        else
            b = o, split(o -> l, a, b -> l, k);
    }
    void remove(Node *&o, const T &k) {
        if (o -> data == k) {
            Node *p = o;
            o = merge(o -> l, o -> r);
            delNode(p);
        }
        else if (comp(k, o -> data))
            remove(o -> l, k);
        else
            remove(o -> r, k);
    }
    void find_data(const T &left, const T &right, uint to_id, uint* ans_stack, uint &ans_top, Node *o) {
        if (!o) return;
        if ((comp(left, o -> data) || !comp(o -> data, left)) && (comp(o -> data, right) || !comp(right, o -> data))) {
            if ((!~to_id || o -> data -> to == to_id) && o -> data -> keyword.match())
                ans_stack[++ans_top] = o -> data -> id;
        }
        find_data(left, right, to_id, ans_stack, ans_top, o -> l);
        find_data(left, right, to_id, ans_stack, ans_top, o -> r);
    }
public:
    Treap():root(0){} 
    void insert(const T &k) {
        Node *a, *b;
        split(root, a, b, k);
        root = merge(a, merge(newNode(k), b));
    }
    void erase(const T &k) {
        remove(root, k);
    }
    void find(const T &left, const T &right, uint to_id, uint* ans_stack, uint &ans_top) {
        find_data(left, right, to_id, ans_stack, ans_top, root);
    }
};

template<typename T, class Compare>
typename Treap<T, Compare>::Node Treap<T, Compare>::mem[C];
template<typename T, class Compare>
uint Treap<T, Compare>::mem_stack[C];
template<typename T, class Compare>
uint Treap<T, Compare>::mem_stack_top = 0;
template<typename T, class Compare>
uint Treap<T, Compare>::mem_top = 0;
