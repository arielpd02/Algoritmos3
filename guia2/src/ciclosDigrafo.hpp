#include "vector"
#include "list"
#include "stack"
#include "algorithm"

using namespace std;

//Represento el digrafo en lista de adyacencias solo con vecindario de salida (para este problema)
using vecindario=list<int>;
using Digrafo=vector<pair<vecindario,vecindario>>;

namespace Digrafos{
    Digrafo d;
    int N;
    vector<bool> visitados;
    list<int> salidaNulo;

    void findCiclo(list<int>& ciclo,int padre){
        visitados[padre]=true;
        ciclo.push_back(padre);

        int vecino=d[padre].second.front();

        if(!visitados[vecino]){
            findCiclo(ciclo,vecino);
        }else{
            //Encontre un ciclo!
            ciclo.push_back(vecino);
            return ;
        }
    }

    bool hayCiclo(list<int>& ciclo){

        //Construyo el vector de grados de salida
        vector<int> grados(N,-1);
        for (int i = 0; i < N; ++i) { //O(N)
            grados[i]=d[i].second.size();
        }
        //Coloca en la pila todo nodo con dout=0
        stack<int> s;
        for (int i = 0; i < grados.size(); ++i) { //O(N)
            if (grados[i] == 0){
                s.push(i);
                salidaNulo.push_back(i);
            }
        }
        while(!s.empty()){ //O(m) pq c/nodo cuesta O(d(v)) y la suma de grados es O(m)
            int v=s.top();
            s.pop();
            // Para todo vecino incidente a v , le disminuyo su dout al borrar v
            for (int u : d[v].first) { //O(d(v))
                grados[u]--;
                if(grados[u] == 0)
                    s.push(u);
            }
        }
        list<int> r;
        for (int i = 0; i < grados.size(); ++i) { //O(N)
            if(grados[i] > 0)
                r.push_back(i);
        }
        if(r.size() == 0){
            return false;
        }else{
            ciclo=r;
            ciclo.push_back(r.front());
        }
    }

}