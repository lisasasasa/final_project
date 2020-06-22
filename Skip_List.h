template<class Key, class Compare = less<Key>>
class skip_list{ 
    class node{
        public:
            Key data;
            node* above;
            node* below;
            node* before;
            node* after;
            node(const Key &_data = Key(), node* _after = NULL):
                data(_data), above(NULL), below(NULL), before(NULL), after(_after){};  
    };
    static const uint C = 3000000;
    static node mem[C];
    static uint mem_stack[C], mem_top, mem_stack_top;
    node* newnode(const Key &_data = Key(), node* _after = NULL) {
        node *p;
        if (mem_top == C)
            p = &(mem[mem_stack[--mem_stack_top]]);
        p = &mem[mem_top++];
        p -> data = _data;
        p -> above = NULL;
        p -> below = NULL;
        p -> before = NULL;
        p -> after = _after;
        return p;
    }
    void delnode(node *&p) {
        mem_stack[mem_stack_top++] = p - mem;
    }
    Compare comp;
    uint height;
    node* s;
    node* skip_search(const Key &M){
        node *p = s;
        while (p -> below != NULL){
            p = p -> below;
            while (!comp(M, p -> after -> data)){
                p = p -> after;
            }
        }
        return p;
    }
    public:
    skip_list():height(0){
        s = new node();
        s -> after = new node();
        s -> after -> before = s;
        s -> above = new node();
        s -> above -> below = s;
        s = s -> above;
        s -> after = new node();
        s -> after -> before = s;
        s -> after -> below = s -> below -> after;
        s -> below -> after -> above = s -> after;
    };
    void insert(const Key &M){
        node* k = skip_search(M);
        node* node_M = newnode(M, k -> after);
        k -> after -> before = node_M;
        k -> after = node_M;
        node_M -> before = k;
        uint i = uint_MAX;
        while(rand() & 1){
            i++;
            if(i >= height){
                height++;
                node *new_s = newnode();
                s -> above = new_s;
                new_s -> below = s;
                s = new_s;
                s -> after = newnode();
                s -> after -> before = s;
                s -> after -> below = s -> below -> after;
                s -> below -> after -> above = s -> after;
            }
            while (k -> above == NULL){
                k = k -> before;
            }
            k = k -> above;
            node *insert_M = newnode(M, k -> after);

            k -> after -> before = insert_M;

            k -> after = insert_M;
            insert_M -> before = k;

            insert_M -> below = node_M;
            node_M -> above = insert_M;

            node_M = insert_M;
        }
    }
    void erase(const Key &M){
        node* k = skip_search(M);
        while(k != NULL){
            k -> before -> after = k -> after;
            k -> after -> before = k -> before;
            node *tmp = k;
            k = k -> above;
            delnode(tmp);
        }
    }
    void find(const Key &left, const Key &right, uint to_id, uint *ans_stack, uint &ans_top) {
        node *p = s;
        while (p -> below != NULL){
            p = p -> below;
            while (comp(p -> after -> data, left)){
                p = p -> after;
            }
        }
        for (p = p -> after; !comp(right, p -> data); p = p -> after)
            if ((!~to_id || p -> data -> to == to_id) && p -> data -> keyword.match())
                ans_stack[++ans_top] = p -> data -> id;
    }
};

template<typename T, class Compare>
typename skip_list<T, Compare>::node skip_list<T, Compare>::mem[C];
template<typename T, class Compare>
uint skip_list<T, Compare>::mem_stack[C];
template<typename T, class Compare>
uint skip_list<T, Compare>::mem_stack_top = 0;
template<typename T, class Compare>
uint skip_list<T, Compare>::mem_top = 0;
