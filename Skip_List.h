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
    Compare comp;
    int height;
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
        node* node_M = new node(M, k -> after);
        k -> after -> before = node_M;
        k -> after = node_M;
        node_M -> before = k;
        int i = -1;
        while(rand() & 1){
            i++;
            if(i >= height){
                height++;
                node *new_s = new node();
                s -> above = new_s;
                new_s -> below = s;
                s = new_s;
                s -> after = new node();
                s -> after -> before = s;
                s -> after -> below = s -> below -> after;
                s -> below -> after -> above = s -> after;
            }
            while (k -> above == NULL){
                k = k -> before;
            }
            k = k -> above;
            node *insert_M = new node(M, k -> after);

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
            delete tmp;
        }
    }
    class iterator{ 
        public: 
            iterator(node* pNode = NULL) noexcept: 
                m_pCurrentNode (pNode){}

            iterator& operator=(node* pNode){ 
                this -> m_pCurrentNode = pNode; 
                return *this;
            } 

            // Prefix ++ overload 
            iterator& operator++(){ 
                if (m_pCurrentNode) 
                    m_pCurrentNode = m_pCurrentNode -> after; 
                return *this;
            } 
            bool operator!=(const iterator& it){ 
                return m_pCurrentNode != it.m_pCurrentNode; 
            } 

            Key& operator*() { 
                return m_pCurrentNode -> data; 
            }
        private: 
            node* m_pCurrentNode; 
    };
    iterator lower_bound(const Key &M){
        node *p = s;
        while (p -> below != NULL){
            p = p -> below;
            while (comp(p -> after -> data, M)){
                p = p -> after;
            }
        }
        return iterator(p -> after);
    }
    iterator upper_bound(const Key &M){
        node* p = skip_search(M);
        if (!p -> after)
            return iterator(p);
        return iterator(p -> after);
    }
};
