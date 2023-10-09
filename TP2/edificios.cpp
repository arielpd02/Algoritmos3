#include <bits/stdc++.h>
#include "cmath"

using namespace std;

struct Solucion {
    long  s;
    long  d_sum;
    long  r_sum;

    Solucion(): s(0), d_sum(0), r_sum(0) {}
};

struct Ady {
    int hasta;
    int di;
    int ri;

    Ady(int h, int di, int ri): hasta(h), di(di), ri(ri) {}

    bool operator<(const Ady& rhs) const {
        return hasta < rhs.hasta;
    }
};

vector<vector<Ady>> graph;
int T, N, M, ui, vi, di, ri;

int costo(int dst, int r, float C) {
    float df=dst, rf=r;
    return df-C*rf;
}

//Prim con peso de e = costo
Solucion prim(float C) {
    Solucion sol = Solucion();
    priority_queue<pair<long , Ady>> q;
    vector<bool> visited(N, false);

    for (Ady ady : graph[0]) {
        int c = costo(ady.di, ady.ri, C);
        q.push({c, ady});
    }

    int edges = 0;
    visited[0] = true;
    while (!q.empty()) {
        pair<long , Ady> item = q.top(); q.pop();
        int costo_arista = item.first;
        Ady arista = item.second;

        if (!visited[arista.hasta]) {
            visited[arista.hasta] = true;
            for (Ady ady : graph[arista.hasta]) {
                int c = costo(ady.di, ady.ri, C);
                q.push({c, ady});
            }
            edges++;
            sol.s += costo_arista;
            sol.d_sum += arista.di;
            sol.r_sum += arista.ri;
        }
        if (edges == N - 1) break;
    }
    return sol;
}

//Binary search del C optimo
void solve(int cota) {
    int low = 0;
    int high = cota;
    Solucion sol;

    while (low + 1 < high) {
        int mid = (low + high) / 2;
        sol = prim(mid);

        if (int(sol.s)> 0) {
            low = mid;
        } else if (int(sol.s) < 0) {
            high = mid;
        } else {
            break;
        }
    }
    if (sol.s != 0) { //El C no es entero , busco entre intervalos de 0,10 entre low/high son consecutivos
        //sol=prim(high);
        //cout<<lowF<<endl;
        //cout<<"LLegue"<<endl;
        float part=1.0/100.0;
        float lowF=low;
        for (int i = 0; i < 100; ++i) { //Cuando low == high dejo de iterar
            lowF+=part;
            sol= prim(lowF);
            if(sol.s==0) break;
        }
    }
    printf("%ld %ld\n", sol.d_sum, sol.r_sum);
}


int main() {
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N >> M;
        graph = vector<vector<Ady>>(N, vector<Ady>());

        int cota = 0;
        //Inicializa el grafo
        for (int m = 0; m < M; m++) {
            cin >> ui >> vi >> di >> ri;
            cota += di;
            graph[ui - 1].push_back(Ady(vi - 1, di, ri));
            graph[vi - 1].push_back(Ady(ui - 1, di, ri));
        }
        cota=cota/M;
        //Redondeo para arriba
        cota++;
        solve(cota);
    }
    return 0;
}