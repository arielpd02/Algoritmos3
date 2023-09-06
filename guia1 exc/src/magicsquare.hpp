//
// Created by Ariel on 21/08/2023.
//
#include "vector"
#include "set"

using namespace std;
using Cuadrado = vector<vector<int>>;

int n=3;
int cantSoluciones = 0;

bool esCuadradoMagico(Cuadrado& c){
    int magico=0;
    for (int i = 0; i < c.size(); ++i) { // Busco el nro. magico
        magico+= c[0][i];
    }
    for (int i = 0; i < n; ++i) { //Chequeo filas
        int actual=0;
        for (int j = 0; j < n; ++j) {
            actual+=c[i][j];
        }
        if (actual!=magico)
            return false;
    }
    for (int j = 0; j < n; ++j) { //Chequeo columnas
        int actual=0;
        for (int i = 0; i < n; ++i) {
            actual+=c[i][j];
        }
        if (actual!=magico)
            return false;
    }
    int actual1=0,actual2=0;
    for (int i = 0,j=0,k=n-1; i < n ; ++i,j++,k--) { //Chequeo diagonales
        actual1+=c[i][j];
        actual2+=c[i][k];
    }

    if(actual2!=magico || actual1!=magico)
        return false;

    return true;

}
bool notYetMagicSquare(Cuadrado& c , int i, int j){
    //Todavia no se formo el magico
    if(i==0)
        return false;

    // Busco el nro. magico
    int magico=0;
    for (int q = 0; q < c.size(); ++q) {
        magico+= c[0][q];
    }
    //Verifico suma parcial fila
    int actual=0;
    for (int k = 0; k < j; ++k) {
        actual+=c[i][k];
    }
    if(actual>magico)
        return true;
    //Verifico suma parcial columnas
    for (int k = 0; k <j; ++k) {
        actual=0;
        for (int l = 0; l <= i; ++l) {
            actual+=c[l][k];
        }
        if(actual>magico)
            return true;
    }
    return false;
}

void cuadradoMagicoAux(Cuadrado& c,int i,int j,set<int>& restantes){

    if(i==n){

        if(esCuadradoMagico(c))
            cantSoluciones++;

    }else{

        int sig_j= j+1;
        int sig_i=i;
        if(sig_j == n){         //Si me pase del size, actualizo fila y col
            sig_i= i+1;
            sig_j=0;
        }

        set<int> disp = restantes;    //Copio los restantes de acuerdo al nivel del llamado
        for (auto x: disp) {
            if(notYetMagicSquare(c,i,j)){
                return;
            }
            c[i][j] = x;
            //Borro el elemento de restantes
            restantes.erase(x);
            cuadradoMagicoAux(c, sig_i, sig_j, restantes);
            //Restauro el elemento luego del llamado
            restantes.insert(x);
            }

    }
}

