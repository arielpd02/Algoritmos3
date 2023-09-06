#include "vector"
#include "string"
#include "algorithm"


using namespace std;
typedef vector<vector<int>> Matriz;

int n=4,soporteMax=38;
Matriz memo(n,vector<int>(38+1,-1));

int maximaCantidadCajas(vector<int>& peso,vector<int>& soporte,int restante,int i){
    //CB: Si no tengo mas cajas por ver
    if(i == peso.size())
        return 0;
    //CB: Si no me queda mas peso por colocar
    if( restante == 0)
        return 0;
    //Sino -> paso recursivo. Tomo el máximo entre colocar y no colocar la caja
    int res=0;
    if( peso[i] <= restante){
        int apilo_caja= 1+ maximaCantidadCajas(peso,soporte, min(restante-peso[i],soporte[i]),i+1);
        int no_apilo= maximaCantidadCajas(peso,soporte,restante,i+1);
        res = max(apilo_caja,no_apilo);
    }else{
        res= maximaCantidadCajas(peso,soporte,restante,i+1);
    }
    return res;
}

int maximaCCTopDown(vector<int>& peso,vector<int>& soporte,int restante,int i){
    if(i==peso.size())
        return 0;
    if(restante==0)
        return 0;

    if(memo[i][restante] != -1){
        return memo[i][restante];
    }else{
        int res=0;
        if( peso[i] <= restante){
            int apilo_caja= 1+ maximaCantidadCajas(peso,soporte, min(restante-peso[i],soporte[i]),i+1);
            int no_apilo= maximaCantidadCajas(peso,soporte,restante,i+1);
            res = max(apilo_caja,no_apilo);
        }else{
            res= maximaCantidadCajas(peso,soporte,restante,i+1);
        }
        //Guardo el estado en la matriz
        memo[i][restante]=res;

        return memo[i][restante];
    }
}