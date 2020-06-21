#include <bits/stdc++.h>

using namespace std;

template<class Key, class Compare = less<Key>>
class skip_list{ 
    class node{
        Key data;
        node* above;
        node* below;
        node* before;
        node* after;
        node(const Key &_data = Key(), const node* &_after = NULL):
            data(_data), above(NULL), below(NULL), before(NULL), after(_after){};  
    };
    Compare comp;
    node* s;
    int height;
    node* skip_search(Key &M){
        node *p = s;
        while (p -> below != NULL){
            p = p -> below;
            while (!comp(M, p -> after)){
                p -> p.after;
            }
        }
        return p;
    }
public:
    skip_list():height(0), s(new node()){};
    void insert(const Key &M){
        node* k = skip_search(M);
        node* node_M = new node(M, k -> after);
        k -> after = node_M;
        int i = -1;
        while(rand() & 1){
            i++;
            if(i >= height){
                height++;
                node *new_s = new node();
                s -> above = new_s;
                new_s.below = s;
                s = new_s;
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
    void remove(const Key &M){
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
    iterator(const node* pNode = s) noexcept: 
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
        bool operator!=(const iterator& iterator){ 
            return m_pCurrentNode != iterator.m_pCurrentNode; 
        } 
  
        Key operator*() { 
            return m_pCurrentNode -> data; 
        }
    private: 
        const node* m_pCurrentNode; 
    };
    iterator lower_bound(const Key &M){
        return iterator(skip_search(M));
    }
    iterator upper_bound(const Key &M){
        return ++iterator(skip_search(M));
    }
};