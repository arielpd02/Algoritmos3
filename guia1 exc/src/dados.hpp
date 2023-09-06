#include "operaciones.hpp"

#ifndef DADOS_HPP
#define DADOS_HPP

namespace Dados {
    int caras = 4;
    int dados = 3;
    int sum = 6;


    vector<vector<int>> memory(dados + 1, vector<int>(sum + 1, -1));

    int f(int n, int s) {
        if (n == 0) {
            return (s == 0 ? 1 : 0);
        } else if (s <= 0) {
            return 0;
        } else {
            if (memory[n][s] == -1) {
                int res = 0;
                for (int i = 1; i <= caras; ++i) {
                    res = res + f(n - 1, s - i);
                }
                memory[n][s] = res;
            }
            return memory[n][s];
        }
    }

    vector<vector<vector<int>>> memory_g(dados+1,vector<vector<int>>(sum+1,vector<int>(caras+1,-1)));

    int g(int i, int s, int cara) {
        if(i == 0){
            return (s==0 ? 1: 0);
        }else if(s <= 0){
            return 0;
        }else{
            if(memory_g[i][s][cara] == -1) {
                int res = 0;
                for (int j = 1; j <= min(cara, s); ++j) {
                    res += g(i - 1, s - j, j);
                }

                memory_g[i][s][cara]=res;
            }
            return memory_g[i][s][cara];
        }
    }


}




#endif
