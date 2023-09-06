//
// Created by Ariel on 24/08/2023.
//

#ifndef PERMUTACION_HPP
#define PERMUTACION_HPP

#include "vector"
#include "set"

using namespace std;
using Matriz=std::vector<std::vector<int>>;

const int inf=19191;
vector<int> minActual;
int n=4;
int costo=14;

int calculoRaro(vector<int>& pi,Matriz& m){
    if(pi.empty())
        return 189089;
    int res=m[pi.back()][pi.front()];
    for (int i = 0; i < n-1; ++i) {
        res+=m[pi[i]][pi[i+1]];
    }
    return res;
}
//Se llama con s = < >, i=0, c={1...n}
void minimaPermutacion(Matriz& m, vector<int>& s,int i,set<int>& c){

    if(i==n && calculoRaro(s,m)< calculoRaro(minActual,m)){
        minActual=s;
    }else{
        for(int x : c){
            c.erase(x);
            s.push_back(x);
            minimaPermutacion(m,s,i+1,c);
            s.pop_back();
            c.insert(x);
        }
    }
}

















#endif
