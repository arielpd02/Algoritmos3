#include <iostream>
#include "ejercicios/ejs_dinamica.hpp"


int main() {
    //int res= minimoNivelDeVida(0,0);
    Matriz b(3,vector<int>(3,0));
    int res= mNV_bottom_up(b,0,0);
    cout<<"El mínimo nivel de vida para comenzar es : "<< res <<endl;
    return 0;
}


/****TESTER*****/
/*Cuadrado aux={{2,7,6},
                {9,5,1},
                {4,3,8}};
  if(esCuadradoMagico(aux)){
      cout<<"Todo bien!"<<endl;
      return 0;
  }


   vector<int> s;
    Matriz m={{0,1,1,10},
              {10,0,3,15},
              {21,17,0,2},
              {3,22,30,0}};
    set<int> c;
    for (int i = 0; i < n; ++i) {
        c.insert(i);
    }
    minimaPermutacion(m,s,0,c);

   */

/*
 * 6)
    vector<int> billetes={2,3,5,10,20,20};
    int res= maxGanNeta(0,0);

     */
// 8)
/*
    vector<int> cortes={0,2,4,7,10};
    int res= minimoCosto_sorted(cortes,0,4);
    //int res= minimoCosto(0,13); */
