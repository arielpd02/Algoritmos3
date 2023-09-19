#include "gtest-1.8.1/gtest.h"
#include "../src/particionesMellizos.hpp"
#include "../src/ciclosDigrafo.hpp"
#include "iostream"

using namespace std;

TEST(Ejercicio_13,Diamong_Graph){
    Mellizos::g={{0,1,2,3},{0,1,2},{0,1,2,3},{0,2,3}};
    Mellizos::N=4;
    Mellizos::particiones={{0,1,2,3}};
    Mellizos::findMellizos();

    set<set<int>> res={{1},{3},{0,2},{}};
    EXPECT_EQ(Mellizos::particiones,res);
}

TEST(Ejercicio_13,Garra){
    Mellizos::g={{0,1,2,3},{0,1},{0,2},{0,3}};
    Mellizos::N=4;
    Mellizos::particiones={{0,1,2,3}}; //P0= V(G)
    Mellizos::findMellizos();

    set<set<int>> res={{3},{2},{1},{0},{}};
    EXPECT_EQ(Mellizos::particiones,res);
}

TEST(Ejercicio_14,CumplenPre){
    Digrafos::d={{{4},{1}},
                 {{0},{2}},
                 {{1},{3,4}},
                 {{2},{4}},
                 {{2,3},{0}}};
    Digrafos::N=Digrafos::d.size();
    vector<bool> v(Digrafos::N,false);
    Digrafos::visitados=v;

    list<int> c={};
    list<int> res={0,1,2,3,4,0};

    Digrafos::findCiclo(c,0);

    EXPECT_EQ(c,res);
}

TEST(Ejercicio_14,NoCumplenPre){
    Digrafos::d={{{4},{1}},
                 {{0},{2}},
                 {{1},{3,4}},
                 {{2},{4}},
                 {{2,3},{0}}};
    Digrafos::N=Digrafos::d.size();
    vector<bool> v(Digrafos::N,false);
    Digrafos::visitados=v;
    Digrafos::salidaNulo={};

    list<int> c={};
    list<int> exp={0,1,2,3,4,0};

    bool res= Digrafos::hayCiclo(c);
    ASSERT_TRUE(res);
    EXPECT_EQ(exp,c);

    Digrafos::d={{{},{1,5}},
                 {{0},{2,4}},
                 {{1},{3}},
                 {{2,4},{}},
                 {{1,5},{3}},
                 {{0},{4}}};
    Digrafos::N=Digrafos::d.size();
    Digrafos::visitados=v;
    Digrafos::salidaNulo={};

    res= Digrafos::hayCiclo(c);
    exp={3};
    ASSERT_FALSE(res);
    EXPECT_EQ(exp,Digrafos::salidaNulo);
}

TEST(Ejercicio_14,SinCiclo){
    Digrafos::d={{{},{1,5}},
                 {{0},{2,4}},
                 {{1},{3}},
                 {{2,4},{}},
                 {{1,5},{3}},
                 {{0},{4}}};
    Digrafos::N=Digrafos::d.size();
    vector<bool> v(Digrafos::N,false);
    Digrafos::visitados=v;
    Digrafos::salidaNulo={};

    list<int> c={};
    list<int> exp={0,1,2,3,4,0};

    bool res= Digrafos::hayCiclo(c);
    exp={3};
    ASSERT_FALSE(res);
    EXPECT_EQ(exp,Digrafos::salidaNulo);
}