#include "iostream"
#include "vector"
#include "algorithm"
#include <bits/stdc++.h>


using namespace std;
using ll= long long;


struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }

    int find(int v){
        while(padre[v] != v) v = padre[v];
        return v;
    }

    void unite(int u, int v){
        u = find(u); v = find(v);
        if(tamano[u] < tamano[v]) swap(u,v);
        //ahora u es al menos tan grande como v
        padre[v] = u;
        tamano[u] += tamano[v];
    }

    vector<int> padre;
    vector<int> tamano;

    //tamano[v] <= n
    //INV: si padre[v] != v entonces tamano[padre[v]] >= 2*tamano[v]
};

void kruskalAux(vector<tuple<int,int,int,int>>& aristas, int n){
    long long D = 0;
    long long R = 0;

    // Ordenamos por distancia mayor y que ri"1 standarizado a di"2 sea <= que ri"2 - en O(M log(N))
    sort(
            aristas.begin(), aristas.end(),
            [](tuple<int,int,int,int> t1, tuple<int,int,int,int> t2)
            { return get<2>(t1)>=get<2>(t2) && (get<3>(t1)/(get<2>(t1)/get<2>(t2)))<=get<3>(t2) ; }
    );

    DSU dsu(n);

    int aristasCount = 0;
    for(auto [u,v,di,ri] : aristas){ //O(N)
        //u y v estan en distinta cc?
        if(dsu.find(u) != dsu.find(v)){ //O(N)
            dsu.unite(u,v);
            D+= di;
            R+=ri;
            aristasCount++;
        }
        if(aristasCount == n-1) break;
    }
    //if(aristasCount == n-1) cout<<D<<" "<<R<<'\n';
    //else cout<<"IMPOSSIBLE\n";
}



void leerFile(){
    ifstream archivoIn;
    archivoIn.open("entrada.in",ios::in);
    int n;
    while(archivoIn>>n) {
        cout << n <<" ";
    }
    archivoIn.close();
}
void leerFileAux() {
    std::ifstream archivoIn("entrada.in");
    std::string line;
    while (std::getline(archivoIn, line)) {
        std::istringstream iss(line);
        int n;
        while (iss >> n) {
            std::cout << n << " ";
        }
    }
    archivoIn.close();
}

int main() {

    int c,N,M;
    cin>>c;
    for (int i = 0; i < c; ++i) { //Cant. test cases do
        cin>>N>>M;
        vector<tuple<int,int,int,int>> aristas(N); // e = <v,di,ri>

        //Inicializo la lista de adyacencias
        int u,v,di,ri;
        for (int j = 0; j < M; ++j) {
            cin>>u>>v>>di>>ri;
            u--;v--; //Para que indexe en 0
            aristas.push_back({v,u,di,ri});
        }
    /*
        //Llamo a DFS
        Red::aristas=aristas;
        Red::N=N;
        Red::M=M;
        Red::visitado = vector<bool>(N, false);
        Red::dfs(0,0,Red::sol);
        auto res=Red::optimo(Red::sol);
        cout<<res.first<<" "<<res.second<<endl;
    */

        kruskalAux(aristas,N);
    }

    return 0;
}
