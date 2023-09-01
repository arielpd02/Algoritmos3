//
// Created by Ariel on 01/09/2023.
//
#include "vector"
#include "algorithm"

using namespace std;
typedef pair<int,int> alumno;
typedef pair<alumno,float> infoAlumno;



namespace Correciones{
    vector<int> tiempos;
    vector<int> coef;
    vector<infoAlumno> infoAlumnos;
    int cota=10^9+7;

    int minimoDescontento(int t){
        long long desc=0;
        for (infoAlumno i: infoAlumnos) {
            int tAlumno=i.first.first + t;
            int coef=i.first.second;
            desc = (desc + (tAlumno * coef)%cota) % cota;
            t+=tAlumno;
        }
        return  desc;
    }
}