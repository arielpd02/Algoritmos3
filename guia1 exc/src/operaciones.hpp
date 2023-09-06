#ifndef OPERACIONES_HPP
#define OPERACIONES_HPP
#include "vector"
#include "math.h"
#include "set"

using namespace std;
typedef vector<vector<vector<char>>> Matriz;


/***Globales***/
int w=95;
set<char> symbols={'+','x','^'};
vector<int> num={1,2,3,4,0,9,84,2};
int N=num.size();
const  vector<char> vNulo={'-'};
const long cota=1e4;



int doesSymbol(int acum,char symbol,int value){
    if(symbol == '+')
        return acum+value;
    if(symbol == 'x')
        return acum*value;
    if(symbol== '^')
        return pow(acum,value);
    //safe case
    return 0;
}

vector<char> operaciones_BT(vector<char>& v,int i , int acum){
    if(i == N ){
        if(acum == w){
            return v;
        }else{
            return {};
        }
    }else if( acum > w){
        return {'-'};
    }else {
        vector<char> res;
        int actual=0;

        //Pruebo con la suma
        v.push_back('+');
        actual=acum+num[i];
        res= operaciones_BT(v,i+1,actual);
        if(res.empty() || res==vNulo){
            //Pruebo con el producto
            v.pop_back();
            v.push_back('x');
            actual=acum*num[i];
            res= operaciones_BT(v,i+1,actual);
        }
        if(res.empty() || res==vNulo){
            //Pruebo con la potencia
            v.pop_back();
            v.push_back('^');
            actual=pow(acum,num[i]);
            res= operaciones_BT(v,i+1,actual);
        }
        if(res.empty() || res == vNulo)
            //Si tampoco sirvió , limpiemos pasos
            v.pop_back();
        return res;
    }
}


/**Memoización**/
vector<char> ini={};
Matriz memo(N,vector<vector<char>>(cota,ini));

vector<char> operaciones_PD(vector<char>& v,int i , int acum){
    if(i == N ){
        if(acum == w){
            return v;
        }else{
            return {};
        }
    }else if( acum > w){
        return {'-'};
    }else {
        //Si para i nros.vistos y cierto acum ya calcule esta solución ,devuelvo tal .Sino , la gurado y devuelvo
        if(memo[i][acum] == ini){
            vector<char> res;
            int actual = 0;

            //Pruebo con la suma
            v.push_back('+');
            actual = acum + num[i];
            res = operaciones_BT(v, i + 1, actual);
            if (res.empty() || res == vNulo) {
                //Pruebo con el producto
                v.pop_back();
                v.push_back('x');
                actual = acum * num[i];
                res = operaciones_BT(v, i + 1, actual);
            }
            if (res.empty() || res == vNulo) {
                //Pruebo con la potencia
                v.pop_back();
                v.push_back('^');
                actual = pow(acum, num[i]);
                res = operaciones_BT(v, i + 1, actual);
            }
            if (res.empty() || res == vNulo)
                //Si tampoco sirvió , limpiemos pasos
                v.pop_back();
            memo[i][acum]=res;
        }

        return memo[i][acum];
    }
}
#endif