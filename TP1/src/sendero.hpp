//
// Created by Ariel on 30/08/2023.
//
#include "vector"
#include "string"
#include "set"
using namespace std;
typedef vector<string> Matriz;

//Globales

Matriz tablero={{'L','I','+','L'},
                {'+','+','I','L'},
                {'I','#','+','#'},
                {'L','I','+','+'}};

int n=4,m=4,inf=999999;
int minCamino=inf , maxCamino=-inf;
vector<vector<bool>> vistas(4,vector<bool>(4,false));




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