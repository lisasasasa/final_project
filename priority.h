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
const double first = 0.87;
const double second = 0.58;
const double third = 0.32;
class Priority{
    vector <string> people ;
    vector <string> password ;
    int People , Password , Date ;
    Heap<MAX_MAIL, double> list;
public:
    void init(){
        string line , split , query , query_index ;
	    ios::sync_with_stdio(0);
	    cin.tie(0);
	    int index = 0 , line_index = 0 ;
	    ifstream file(argv[1]) ;

        getline ( file , line ) ;
        istringstream is( line ) ; 
        while( getline( is , split , '\t' ) ) people.push_back(split) ; 

        getline ( file , line ) ;
		istringstream is( line ) ; 
		while( getline( is , split , '\t' ) ) password.push_back(split) ;

		getline ( file , line ) ;
        for(int i = 0 ; i < 3 ; ++i ){
            istringstream is( line ) ;
            getline( is , split , '\t' ) ;
            if( i == 0 ) People = stoi(split) ;
            else if ( i == 1 ) Password = stoi(split) ;
            else Date = stoi(split) ;
        }
		file.close() ;
	};

    /*void build(){

    #}*/
    void insert(Mail &M) {
        double value , PEOPLE = 0 , PASSWD = 0  , DATE = 0 ;
        for (int  i = 0 ; i < people.size() ; ++i ) {
            if( M.keyword().match(people[i])) PEOPLE = 110/(i+1) - 100 ;
        }
        for (int  i = 0 ; i < password.size() ; ++i ) {
            if( M.keyword().match(password[i])) PASSWD += 110/(i+1) - 100 ;
        DATE = M.date/20000000 ;
        value = People * PEOPLE + Password * PASSWD + Date * DATE ;
        list.push( value , M.id );
    }
    void erase(Mail &M) {
        list.erase(M.id) ;
    };
};
