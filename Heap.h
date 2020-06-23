template< size_t N, typename T >
class Heap {
    bitset<N> del;
    int Length = 0;
    pair<T, int> data[N];
    pair<T, int> tmp;
    priority_queue < pair <T , int > > pq;
    void pop_heap(int idx) {
        data[idx] = data[Length];
        --Length;
        while( 2*idx >= Length ){
            if( 2*idx  == Length ) data[idx] = tmp , tmp = data[2 * idx] , data[2 * idx] = data[idx] ;
            else{
                if( data[2*idx].first > data[ 2*idx + 1 ].first ) data[idx] = tmp , tmp = data[2 * idx] , data[2 * idx] = data[idx] ;
                else data[idx] = tmp , tmp = data[2 * idx + 1 ] , data[2 * idx + 1 ] = data[idx] ;
            }
        }
    }
public:
    void push(T x,int num) {
        del[num] = 0;
        ++Length;
        data[Length] = make_pair( x , num );
        //data.push(pair<T, int>(x, -num));
    }
    T top() {
        while ( Length > 0 && del[-data[1].second])
            pop_heap(1);
        return -data[1].second;
    }
    void erase(int num) {
        del[num] = 1;
    }
    bool empty() {
        while ( Length > 0 && del[-data[1].second])
            pop_heap(1);
        return Length == 0 ;
    }
    vector<int> kth(int k) {
        vector <int> v ;
        priority_queue < pair <T , int > > kpq;
        pq.push(make_pair(data[1].first, 1)); 
        pair<T, int> top ;
        for ( int i = 0 ; i < k ; ++i ){
            top = kpq.top(); 
            kpq.pop();
            if (del[-data[top.second].second]) {
                pop_heap(top.second);
                --i;
                continue;
            }
            v.push_back(-data[top.second].second);
            kpq.push(make_pair(data[ 2 * top.second ].first, 2 * top.second)); 
            kpq.push(make_pair(data[ 2 * top.second + 1 ].first, 2 * top.second + 1)); 
        }
        return v ;
    }
};
