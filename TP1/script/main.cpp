#include <iostream>
#include "vector"
#include "string"
#include "set"
#include "algorithm"
using namespace std;
typedef vector<string> Matriz;

namespace Sendero{
    //Inicializo globales
    Matriz tablero;
    int N,M,inf=999;
    int minCamino=inf,
        maxCamino=-inf;
    vector<vector<bool>> vistas;

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


}
/*
  cin>>N>>M;
  string fila;
  Sendero:: tablero={};
  Sendero:: N = N;
  Sendero::M = M;
  vector<vector<bool>> v(N,vector<bool>(M,false));
  Sendero::vistas = v;

  //Leo e inicializo el tablero
  for (int j = 0; j < N; ++j) {
      cin>>fila;
      Sendero::tablero.push_back(fila);
  }
  Sendero::resolver(0,0,0,"down");
  Sendero::resolver(0,0,0,"der");
  int minSol=Sendero::minCamino;
  int maxSol=Sendero::maxCamino;
  if(maxSol > 0 && minSol < Sendero::inf){
      printf("POSIBLE %d %d\n", minSol, maxSol);
  }else{
      printf("IMPOSIBLE\n");
  }
   */

namespace Libro {
    vector<int> libro;
    int N;
    int saldo;
    vector<char> solucion;

    bool noConsiderados(int i,int j){
        return solucion[i]!='?' && solucion[j]!='?';
    }
    void reajustarSolucion(){
        for (int i = 0; i < solucion.size(); ++i) {
            for (int j = i+1; j < solucion.size(); ++j) {
                char& valorI = solucion[i];
                char& valorJ = solucion[j];
                if (libro[i] == libro[j] && valorI != valorJ && noConsiderados(i,j)){
                    valorJ = '?';
                    valorI = '?';
                    break; //Ya cambiamos un par
                }
            }
        }
    }

    void limpiaCuentas(vector<char> &b, int i, int saldoActual) {
        if (i == N && saldoActual == saldo && solucion.empty()) {
            solucion = b;
            reajustarSolucion(); //O(n"2)
        } else if(i < N ) {
            b.push_back('+');
            limpiaCuentas(b, i + 1, saldoActual + libro[i]);
            b.pop_back();
            b.push_back('-');
            limpiaCuentas(b, i + 1, saldoActual - libro[i]);
            b.pop_back();
        }
    }
}

typedef pair<int,float> alumno;
typedef pair<pair<int,int>,float> infoAlumno;


namespace Correciones{
    vector<int> tiempos;
    vector<int> coef;
    vector<infoAlumno> infoAlumnos;
    int cota=1e9+7;

    long long minimoDescontento(int t){
        long long desc=0;
        for (infoAlumno i: infoAlumnos) {
            int tAlumno=i.first.first + t;
            int coef=i.first.second;
            desc = (desc + (tAlumno * 1LL * coef) % cota )% cota;
            t=tAlumno;
        }
        return  desc;
    }
}

int main() {
    int tests,N;
    cin>>tests;

    for (int i = 0; i < tests; ++i) {
        cin>>N;
        Correciones::tiempos={};
        Correciones::coef={};
        int m,c;
        for (int j = 0; j < N; ++j) {
            cin>>m;
            Correciones::tiempos.push_back(m);
        }
        for (int j = 0; j < N; ++j) {
            cin>>c;
            Correciones::coef.push_back(c);
        }
        for (int j = 0; j < N; ++j) {
            alumno a= make_pair(Correciones::tiempos[j],Correciones::coef[j]);
            float d= a.first/a.second;
            infoAlumno i= make_pair(a,d);
            Correciones::infoAlumnos.push_back(i);
        }
        sort(Correciones::infoAlumnos.begin(),Correciones::infoAlumnos.end(),
             [](pair<alumno , float> b1, pair<alumno , float> b2) { return b1.second < b2.second; });


        printf("%lld\n",Correciones::minimoDescontento(0));

    }

    /*
    for (int j = 0; j < N; ++j) {
        alumno a= make_pair(Correciones::tiempos[j],Correciones::coef[j]);
        float d= a.first /a.second;
        infoAlumno i= make_pair(a,d);
        Correciones::infoAlumnos.push_back(i);
    }
    sort(Correciones::infoAlumnos.begin(),Correciones::infoAlumnos.end(),
         [](pair<alumno , float> b1, pair<alumno , float> b2) { return b1.second < b2.second; });
    printf("%d\n", Correciones::minimoDescontento(0,Correciones::infoAlumnos));
    */ //Interfaz prueba : Correciones

    /*
    cin>>N>>saldo;
    Libro:: libro={};
    Libro:: N=N;
    Libro:: saldo = saldo;
    Libro::solucion={};
    int valor;
    for (int j = 0; j < N; ++j) {
        cin>>valor;
        Libro::libro.push_back(valor);
    }
    vector<char> call={};

    Libro::limpiaCuentas(call,0,0);

    for (int j = 0; j < Libro::solucion.size(); ++j) {
        cout<<Libro::solucion[j];
    } */ //Interfaz para el judge :Saldo

    /*
    Libro::libro={700,1000,100,500,200,1000,200,200,1000};
    Libro::N=Libro::libro.size();
    Libro::saldo=1300;
    vector<char> b={};
    Libro::limpiaCuentas(b,0,0);
    for (int i = 0; i < Libro::solucion.size(); ++i) {
        cout<<Libro::solucion[i];
    }*/ //Interfaz de prueba :Saldo
    return 0;
}
