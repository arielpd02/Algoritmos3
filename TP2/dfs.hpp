#ifndef DFS_HPP
#define DFS_HPP

#include "vector"
#include "algorithm"
#include <bits/stdc++.h>

using namespace std;

namespace Red {
    int N, M;
    vector<vector<tuple<int, int, int>>> aristas;
    vector<pair<long long ,long long>> sol;
    vector<bool> visitado;

    long long D = 0;
    long long R = 0;
    int cantAristas=0;


    void solve(){

    }



    void dfs(int v, int padre,vector<pair<long long ,long long>>& sol) {
        if(cantAristas == N-1){
            sol.push_back(make_pair(D,R));
            return;
        }
        visitado[v] = true;
        for (auto [u,di,ri]: aristas[v]) {
            if (!visitado[u]){
                D+=di;R+=ri; //Cuento esta conexion
                cantAristas++;
                dfs(u,v,sol);
                visitado[u]=false;
                D=D-di;R=R-ri; //Descuento la conexion
                cantAristas--;
            }
        }
    }

    pair<long long ,long long> optimo(vector<pair<long long,long long>>& s){
        pair<long long,long long> res=s.front();
        for (auto p:s) {
            if(p.first/p.second > res.first/res.second){
                res=p;
            }
        }
        return res;
    }

}






#endif
