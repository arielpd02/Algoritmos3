//
// Created by Ariel on 28/08/2023.
//
#ifndef EJS_DINAMICA.HPP
#define EJS_DINAMICA.HPP
#include "vector"
#include "math.h"


using namespace std;
typedef std::vector<std::vector<int>> Matriz;

// VARIABLES GLOBALES
int inf= 89898;
int costo=14;
int n=3,m=n;
/***********************************DINAMICA***************************************/
// EJERCICIO 6
vector<vector<pair<int,int>>> mem(6,vector<pair<int,int>>(costo, make_pair(-1,-1)));
vector<int> billetes={2,3,5,10,20,20};

pair<int,int> minima_perdida_bt(vector<int>& b, int i , int j){
    if( i<0 && j>0){
        return make_pair(inf,inf);
    }else if( j<=0){
        return make_pair(abs(j),0);
    }else{
        //Calculo el resultado de agregar el billete
        pair<int,int> res= minima_perdida_bt(b,i-1,j-b[i]);
        //Cuento el billete que gaste
        res.second++;
        // Devuelvo el mínimo entre ambas ramas
        return min(res, minima_perdida_bt(b,i-1,j));
    }
}

pair<int,int> minima_perdidaTP(int i , int j){
    if( i<0 && j>0){
        return make_pair(inf,inf);
    }else if( j<=0){
        return make_pair(abs(j),0);
    }else{
        if(mem[i][j].first =! -1) {
            return mem[i][j];
        }
        //Calculo el resultado de agregar el billete
        pair<int, int> res = minima_perdidaTP(i - 1, j - billetes[i]);
        //Cuento el billete que gaste
        res.second++;
        //Guardo lo calculado en memoria para el i-esimo billete actual y gasto
        mem[i][j] = min(res, minima_perdidaTP(i - 1, j));


        return mem[i][j];
    }
}

//EJERCICIO 7

Matriz memo(n,vector<int>(n,-1));
vector<int> precios={3,6,10};

int maxGanNeta(int dia,int cantAster){
    // Si tengo + aster. que dias o vendí sin haer comprado...
    if(cantAster > (n-dia) || cantAster < 0){
        return -inf;
    }else if(dia == n){
        return 0;
    }else{
        if(memo[dia][cantAster] == -1) {
            int comprarHoy = maxGanNeta(dia + 1, cantAster + 1) - precios[dia];
            int venderHoy = maxGanNeta(dia + 1, cantAster - 1) + precios[dia];
            int noHacerNada = maxGanNeta(dia + 1, cantAster);
            //Guardemos en memoria el res de m.g.n para dado estado
            memo[dia][cantAster]= max(comprarHoy, max(venderHoy, noHacerNada));
        }
        // Devuelvo el res
        return memo[dia][cantAster];
    }
}

int mgnBottomUP(int dia ,int cantAster){

}

//EJERCICIO 8
vector<int> c={2,4,7};
Matriz memory(3   ,vector<int>(3,inf));

bool noHayCortes(vector<int>& c,int i ,int j){
    for (int k = 0; k < c.size(); ++k) {
        if(c[k] > i && c[k] < j)
            return false;
    }
    return true;
}


int minimoCosto(int i,int j){
    if(noHayCortes(c,i,j)){
        return 0;
    }else{
        if(memory[i][j] == inf) { //NO estaba guardado el estado
            int res = (j - i);
            int minimoCortes = inf;
            for (int k = 0; k < c.size(); ++k) {
                if (c[k] > i && c[k] < j) {
                    minimoCortes = min(minimoCortes, minimoCosto(i, c[k]) + minimoCosto(c[k], j));
                }
            }
            res += minimoCortes;
            memory[i][j]=res;
        }
        return  memory[i][j];
    }
}

int minimoCosto_sorted(vector<int>& cortes,int i,int j){
    //Si no hay cortes entre los puntos parámetros
    if( j == i+1){
        return 0;
    }else{
        if(memory[i][j] == inf) {
            //Calculo el mínimo costo de de cortar entre i y j
            int res = (cortes[j] - cortes[i]);
            int minCortes = inf;
            for (int k = i + 1; k < j; ++k) {
                minCortes = min(minCortes, minimoCosto_sorted(cortes, i, k) + minimoCosto_sorted(cortes, k, j));
            }
            res += minCortes;
            memory[i][j]=res;
        }
        return memory[i][j];
    }
}


//EJERCICIO 9
Matriz a={{-2,-3,3},
          {-5,-10,1},
          {10,30,-5}};

int minimoNivelDeVida(int fila,int col){
    //Caso base : llegue a A_nm -> devuellvo 1 si > 0 , ó la m.n.v tq sea 1
    if(fila==n-1 && col==m-1){
        return max(1,1-a[fila][col]);
    }else if(fila==n-1){ //LLegue a extremo fila
        return max(1, minimoNivelDeVida(fila,col+1) - a[fila][col]);
    }else if(col==m-1){ //Llegue a extremo columna
        return max(1, minimoNivelDeVida(fila+1,col) - a[fila][col]);
    }else{
        if(memory[fila][col]== inf) { //No guarde el valor
            int minimo = min(minimoNivelDeVida(fila + 1, col), minimoNivelDeVida(fila, col + 1)) - a[fila][col];
            memory[fila][col]=max(1, minimo);
        }
        return memory[fila][col];
    }
}

int mNV_bottom_up(Matriz& b, int fila,int col){
    b[n-1][m-1]=max(1,1-a[n-1][m-1]);
    // Cargo los valores de ultima columna
    for (int i = n-2; i >= 0 ; --i) {
        b[i][m-1]=max(1,b[i+1][m-1] - a[i][m-1]);
    }
    // Cargo los valores de ultima fila
    for (int j = m-2; j >= 0 ; --j) {
        b[n-1][j]=max(1,b[n-1][j+1] - a[n-1][j]);
    }
    for (int i = n-2; i >=0 ; --i) {
        for (int j = m-2; j >=0 ; --j) {
            b[i][j]=max(1,min(b[i+1][j],b[i][j+1]) - a[i][j]);
        }
    }
    return b[fila][col];
}



#endif