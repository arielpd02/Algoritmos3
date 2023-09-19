#include "vector"
#include "set"
#include "list"
#include "algorithm"

using namespace std;
using Grafo = vector<list<int>>;

namespace Mellizos{
    Grafo g;
    int N=g.size();
    set<set<int>> particiones;

    set<int> interseccion(set<int>& w,const list<int>& adyacencias){
        set<int> res={};
        for (int v : w ) {
            if(std::binary_search(adyacencias.begin(), adyacencias.end(),v)){
                res.insert(v);
            }
        }
        return res;
    }
    set<int> diferencia(set<int>&w, const list<int>& adyacencias){
        for (int v: adyacencias ) {
            if(w.count(v)){
                w.erase(v);
            }
        }
        return w;
    }

    void findMellizos(){

        for (int i = 0; i < N; ++i) {
            set<set<int>> pi = particiones;
            auto it=pi.begin();
            particiones.clear();
            while(it != pi.end()){
                set<int> w=it.operator*();

                //Calculo las intersecciones con el N[v]
                set<int> inter= interseccion(w,g[i]);

                //Calculo las diferencias con el N[v]
                set<int> dif= diferencia(w,g[i]);
                particiones.insert(inter);
                particiones.insert(dif);

                // Avanzo al proximo W de Pi
                it++;
            }
        }
    }

}