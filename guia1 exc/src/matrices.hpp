//
// Created by Ariel on 22/08/2023.
//
#include "vector"
#include "set"

using namespace std;
using Matriz=vector<vector<int>>;

set<int> empty;
pair<set<int>,int> solMax = {empty,0};
int n=4;

int sumaElementos(set<int>& s,Matriz& m){
    int res=0;
    for (int i:s) {
        for (int j:s) {
            res+=m[i][j];
        }
    }
    return res;
}

int sumaElemRestantes(int i, Matriz& m){ //Genera el subconjunto restante desde el i+1-esimo elemento y luego sumaElementos
    set<int> res;
    for (int j = i ; j < n; ++j) {
        res.insert(j);
    }
    return sumaElementos(res,m);
}

//Se invocara con (m,k,0,1,vacio)
void maxSubset(Matriz& m,int k,int sum,int i,set<int>& s){

    if( k==0 || i==n){
        if(sum > solMax.second){
            solMax.first=s;
            solMax.second= sumaElementos(s,m);
        }
        //Poda por optimalidad ; si aun llegando al final , no maximizo
    }else if(solMax.second < sumaElemRestantes(i+1,m) + sum){

        s.insert(i);
        maxSubset(m,k-1, sumaElementos(s,m),i+1,s);
        s.erase(i);
        maxSubset(m,k,sum,i+1,s);

    }
}


