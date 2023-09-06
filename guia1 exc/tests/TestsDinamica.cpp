#include "gtest-1.8.1/gtest.h"
#include "../src/operaciones.hpp"
#include "../src/dados.hpp"
/*
#include "../src/cajasnumeradas.hpp"


TEST(Cajas_Numeradas,BT){
    vector<int> peso={19, 7, 5, 6, 1};
    vector<int> soporte={15, 13, 7, 8, 2};
    int pesoSoporteMax= 0;
    for (int x: peso) {
        pesoSoporteMax+=x;
    }
    EXPECT_EQ(4, maximaCantidadCajas(peso,soporte,pesoSoporteMax,0));
}

TEST(Cajas_Numeradas,PD){
    vector<int> peso={19, 7, 5, 6, 1};
    vector<int> soporte={15, 13, 7, 8, 2};
    int pesoSoporteMax= 0;
    for (int x: peso) {
        pesoSoporteMax+=x;
    }
    EXPECT_EQ(4, maximaCCTopDown(peso,soporte,pesoSoporteMax,0));
}
*/
TEST(Operaciones,Easy_example){
    //Inicializo mi vector solución
    vector<char> v={};
    //Expected
    vector<char> res={'+','x','^','x'};
    //LLamo con el primer valor acumulado y con i = 1 , pq continuo con el 2° elem
    operaciones_BT(v,1,3);
    EXPECT_EQ(v,res);
}

TEST(Operaciones,Dinámica){

    //Inicializo mi vector solución
    vector<char> v={};
    //Expected
    vector<char> res={'+','x','^','x'};
    //LLamo con el primer valor acumulado y con i = 1 , pq continuo con el 2° elem
    v=operaciones_PD(v,1,3);
    EXPECT_EQ(v,res);
}

TEST(Operaciones,Jodido){

    //Inicializo mi vector solución
    vector<char> v={};
    //Expected
    vector<char> res={'+','x','+','^','x','+','+'};
    //LLamo con el primer valor acumulado y con i = 1 , pq continuo con el 2° elem
    operaciones_PD(v,1,1);
    EXPECT_EQ(v,res);
}

TEST(Dados,easy){
    Dados::dados=3;
    Dados::caras=4;
    Dados::sum=6;
    int res= Dados::f(Dados::dados,Dados::sum);
    EXPECT_EQ(res,10);
}

TEST(Dados,Testeo_g){
    Dados::dados=3;
    Dados::caras=3;
    Dados::sum=5;
    int res= Dados::g(Dados::dados,Dados::sum,Dados::caras);
    EXPECT_EQ(res,2);

    Dados::dados=3;
    Dados::caras=4;
    Dados::sum=6;
    res= Dados::g(Dados::dados,Dados::sum,Dados::caras);
    EXPECT_EQ(res,3);

}
