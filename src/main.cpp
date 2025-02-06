#include "Grafo.h"

#define INF 1e9

using namespace std::chrono;
//----------------------------------------------------------------------------//
//Los tiempos estaran comentados ASI
//----------------------------------------------------------------------------//
int main()
{
    srand(time(NULL) + rand());
    Grafo< string > g;
    // Grafo< int > g; // para archivos con NUMEROS es mas eficiente

    // g.leerArchivoNumeros("PRUEBA_Min_Cut.txt");
    // g.leerArchivoNumeros("MinCut.txt");

    // g.leerArchivo("Min_Cut_NOMBRES Prueba.txt");
    g.leerArchivo("MIN_CUT_CON_NOMBRES.txt");


    int minimo = INF;
    int karger;
    long long limite = static_cast<long long>(g.hash.size() * g.hash.size() * log10(g.hash.size()));
    auto start = high_resolution_clock::now();


    form(i,0,limite)
    {
        karger = g.kargerToMinCut(g);

        minimo = min(minimo ,karger );
        cout << karger << endl;// si no se imprime solo se considera el tiempo del algoritmo y asi no se le suma el output
    }


    auto stop = high_resolution_clock::now(); // Fin del cronómetro
    cout << "-----------------------------------" << endl;
    cout <<"minimo de cortes: " << minimo << endl;
    cout << "-----------------------------------" << endl;

    g.mostrar(&g);


    // Calcular la duración
    auto duration = duration_cast<minutes>(stop - start);
    cout << "Tiempo de ejecucion: " << duration.count() << " minutos" << endl; // Imprimir el tiempo

    return 0;
}