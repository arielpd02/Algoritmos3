#include <iostream>
#include "vector"
#include "string"
#include "set"

using namespace std;
typedef vector<string> Matriz;

namespace Sendero{
    //Inicializo globales
    Matriz tablero;
    int N,M,inf=999;
    int minCamino=inf,
        maxCamino=-inf;
    vector<vector<bool>> vistas;

    set<string> accPosibles(char pieza, const string& ultAccion){
        if(pieza == 'I'){
            return {ultAccion};
        }else if(pieza == '+'){
            if( ultAccion== "der")
                return {"up","down","der"};
            else if(ultAccion == "izq")
                return {"up","down","izq"};
            else if(ultAccion == "up")
                return {"izq","der","up"};
            return {"izq","der","down"};

        }else if(pieza == 'L'){
            if(ultAccion =="der" || ultAccion =="izq")
                return {"up","down"};
            return {"izq","der"};
        }
        return {};
    }

    pair<int,int> coordenadas(int i,int j, const string& accion){
        if(accion == "izq")
            return make_pair(i,j-1);
        if(accion == "der")
            return make_pair(i,j+1);
        if(accion == "up")
            return make_pair(i-1,j);
        if(accion == "down")
            return make_pair(i+1,j);
    }

    bool enTablero(int fila , int columna){
        if ( fila < 0 || fila >= N)
            return false;
        if( columna < 0 || columna >= M)
            return false;
        return true;
    }



    void resolver(int i,int j,int piezasVistas,const string& ultAccion){
        //Casos base
        if(i==N-1 && j==M-1){
            if(piezasVistas > maxCamino){
                maxCamino=piezasVistas;
            }
            if(piezasVistas < minCamino){
                minCamino=piezasVistas;
            }
        }else if(enTablero(i,j) && !vistas[i][j]) { // En rango i,j y no pase ya por ahi
            // Si la casilla actual es vacía
            if (tablero[i][j] == '#') {
                vistas[i][j] = true;
                return;
            } else {
                piezasVistas++;
                char piezaActual = tablero[i][j];
                set<string> posibles= accPosibles(piezaActual,ultAccion);
                for(const string& accion : posibles){
                    vistas[i][j]=true;
                    pair<int,int> nuevasCoord= coordenadas(i,j,accion);
                    resolver(nuevasCoord.first,nuevasCoord.second,piezasVistas,accion);
                    vistas[i][j]=false;
                }

            }
        }
    }


}

int main() {
    int tests,N,M;
    cin>>tests;
    for (int i = 0; i < tests; ++i) {
        cin>>N>>M;
        string fila;
        Sendero:: tablero={};
        Sendero:: N = N;
        Sendero::M = M;
        vector<vector<bool>> v(N,vector<bool>(M,false));
        Sendero::vistas = v;

        //Leo e inicializo el tablero
        for (int j = 0; j < N; ++j) {
            cin>>fila;
            Sendero::tablero.push_back(fila);
        }
        Sendero::resolver(0,0,0,"down");
        Sendero::resolver(0,0,0,"der");
        int minSol=Sendero::minCamino;
        int maxSol=Sendero::maxCamino;
        if(maxSol > 0 && minSol < Sendero::inf){
            printf("POSIBLE %d %d\n", minSol, maxSol);
        }else{
            printf("IMPOSIBLE\n");
        }
    }
    return 0;
}
