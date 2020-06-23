#ifndef run
#include <bits/stdc++.h>
using namespace std;
#include "Parameter.h"
#include "String.h"
#include "Expression.h"
#include "Keyword.h"
#include "Mail.h"
#include "Heap.h"
#include "Order_Tree.h"
#endif
class Priority{
    vector <string> people ;
    vector <string> password ;
    double People , Password , Date ;
    Heap<MAX_MAIL, double> list;
public:
    void init(){
        string line , split , query , query_index ;
	    ios::sync_with_stdio(0);
	    cin.tie(0);
	    ifstream file(".priority_conf") ;

        getline ( file , line ) ;
        istringstream is( line ) ; 
        while( is >> split ) people.push_back(split) ; 

        getline ( file , line ) ;
        istringstream is2( line ) ; 
		while( is2 >> split ) password.push_back(split) ;

		getline ( file , line ) ;
        for(int i = 0 ; i < 3 ; ++i ){
            double x;
            istringstream is3( line ) ;
            is3 >> x;
            if( i == 0 ) People = x ;
            else if ( i == 1 ) Password = x ;
            else Date = x ;
        }
		file.close() ;
	};

    /*void build(){

    #}*/
    void insert(Mail &M) {
        double value , PEOPLE = 0 , PASSWD = 0  , DATE = 0 ;
        for (int  i = 0 ; i < int(people.size()) ; ++i ) {
            if( M.keyword.match(people[i])) PEOPLE = 110/(i+1) - 100 ;
        }
        for (int  i = 0 ; i < int(password.size()) ; ++i ) {
            if( M.keyword.match(password[i])) PASSWD += 110/(i+1) - 100 ;
        }
        DATE = M.date/20000000 ;
        value = People * PEOPLE + Password * PASSWD + Date * DATE ;
        list.push( value , M.id );
    }
    void erase(int id) {
        list.erase(id) ;
    }
    vector<int> query(int k) {
        return list.kth(k);
    }
};
