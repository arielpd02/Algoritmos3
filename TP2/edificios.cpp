#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

struct Solucion {
    long long s;
    int d_sum;
    int r_sum;

    Solucion(): s(0), d_sum(0), r_sum(0) {}
};

struct SolucionF{
    double s;
    int d_sum;
    int r_sum;

    SolucionF(): s(0), d_sum(0), r_sum(0) {}
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

int costo(int dst, int r,int C) {
    return dst-C*r;
}

//Prim con peso de e = costo
Solucion prim(int C) {
    Solucion sol = Solucion();
    priority_queue<pair<int, Ady>> q;
    vector<bool> visited(N, false);

    for (Ady ady : graph[0]) {
        int c = costo(ady.di, ady.ri, C);
        q.push({c, ady});
    }

    int edges = 0;
    visited[0] = true;
    while (!q.empty()) {
        pair<int, Ady> item = q.top(); q.pop();
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

long long costoAux(int dst, int r, long long C) {
    return 1e9*dst-C*r;
}

Solucion primaux(long long C){
    Solucion sol = Solucion();
    priority_queue<pair<long long, Ady>> q;
    vector<bool> visited(N, false);

    for (Ady ady : graph[0]) {
        long long c = costoAux(ady.di, ady.ri, C);
        q.push({c, ady});
    }

    int edges = 0;
    visited[0] = true;
    while (!q.empty()) {
        pair<long long , Ady> item = q.top(); q.pop();
        long long costo_arista = item.first;
        Ady arista = item.second;

        if (!visited[arista.hasta]) {
            visited[arista.hasta] = true;
            for (Ady ady : graph[arista.hasta]) {
                long long c = costoAux(ady.di, ady.ri, C);
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

double costoF(int dst, int r,double C) {
    return dst-C*r;
}

SolucionF primFloat(double C){
    SolucionF sol = SolucionF();
    priority_queue<pair<double, Ady>> q;
    vector<bool> visited(N, false);

    for (Ady ady : graph[0]) {
        double c = costoF(ady.di, ady.ri, C);
        q.push({c, ady});
    }

    int edges = 0;
    visited[0] = true;
    while (!q.empty()) {
        pair<double, Ady> item = q.top(); q.pop();
        double costo_arista = item.first;
        Ady arista = item.second;

        if (!visited[arista.hasta]) {
            visited[arista.hasta] = true;
            for (Ady ady : graph[arista.hasta]) {
                double c = costoF(ady.di, ady.ri, C);
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
        if (sol.s> 0) {
            low = mid;
        } else if (sol.s < 0) {
            high = mid;
        } else {
            break;
        }
    }
    if (sol.s != 0) { //El C no es entero , busco entre low/high tq son consecutivos, con reales normalizados
        //sol=prim(high);

        /*
        long long sActual=0;
        long long highL=1e9*high;
        long long lowL=1e9*low;

        while (sol.s!=0 && lowL+1<highL){ //Itera O(log(10^9)) veces
            long long mid=(lowL+highL)/2;
            sol= primaux(mid);
            if(sol.s>0){
                lowL=mid;
            }else if(sol.s<0){
                highL=mid;
            }
        }
        */

        //Busqueda entre reales de low-high
        float lowF=low,highF=high;
        float sActual=0;
        SolucionF solF=SolucionF();
        solF.s=sol.s;
        solF.r_sum=sol.r_sum;
        solF.d_sum=sol.d_sum;

        //|| int(sActual+solF.s)!=0
        while(int(solF.s)!=0){
            double midF=(lowF+highF)/2.0;
            sActual=solF.s;
            //cout<<sActual<<endl;
            solF = primFloat(midF);
            if(solF.s>0){
                lowF=midF;
            }else if(solF.s<0){
                highF=midF;
            }
        }

        sol.s=solF.s;
        sol.d_sum=solF.d_sum;
        sol.r_sum=solF.r_sum;

        /*
        // Recorrido lineal de a milesimos
         float part=1.0/10000.0;
        float lowF=low,highF=high;
        for (int i = 0; i < 10000; ++i) { //Cuando low == high dejo de iterar
            sActual=sol.s;
            lowF+=part;
            sol= prim(lowF);
            if(sol.s==0 || sActual+sol.s==0) break;
        }
        */
    }
    //cout<<sol.s<<endl;
    printf("%d %d\n", sol.d_sum, sol.r_sum);
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