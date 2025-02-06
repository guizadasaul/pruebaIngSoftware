#pragma once

#include "Nodo.h"
#include <unordered_map>

template <class T>
class Grafo
{
public:
    unordered_map<T, Nodo<T>> hash;

	vector< T > llaves;
    /*Gracias a nuestro vector de llaves tendremos en kargerToMinCut 
    acceso aleatorio en O(1),y asi no usamos la funcion ADVANCE que 
    es orden O(n)*/



    Grafo<T>();
    ~Grafo<T>();

    //insertar para contraer
    void insertarArista(T origen, T destino);

    //insertar para leer el archivo
    void insertar(T origen, T destino);
    int eliminarAristaUnaVez(T origen, T destino);

    int kargerToMinCut(Grafo<T> g);
    void contraer(T contractor, T contraido);

    //compara con "-1" string
    void leerArchivo(string nombreArchivo);
    //comapra con -1 int
    void leerArchivoNumeros(string nombreArchivo);


    void mostrar(Grafo<T>* g);
};

template <class T>
Grafo<T>::Grafo()
{
}

template <class T>
Grafo<T>::~Grafo()
{
}

template <class T>
inline void Grafo<T>::insertarArista(T origen, T destino)
{
    hash[origen].adyacencias.push_back(destino);
	hash[destino].adyacencias.push_back(origen);
}

template <class T>
inline void Grafo<T>::insertar(T origen, T destino)
{
    hash[origen].adyacencias.push_back(destino);
}

template <class T>
inline int Grafo<T>::eliminarAristaUnaVez(T origen, T destino)
{
    //----------------------------------------------------------------------------//
    //IMPORTANTE : Tiempto 1 = O(n - (n - posicion dato a eliminar)) done n = hash[origen].adyacentes.size()
    int res = hash[origen].eliminarAdyacenteUnaVez(destino);
    //IMPORTANTE : Tiempo 2 = O(n - (n - posicion dato a eliminar)) done n = hash[destino].adyacentes.size()
    hash[destino].eliminarAdyacenteUnaVez(origen);    
    //----------------------------------------------------------------------------//
    // if ( res1 == res2) cout << "jajajajjaj" << endl;
    // else cout << "--------------------------" << endl;
    
    return res;
}

template <class T>
inline int Grafo<T>::kargerToMinCut(Grafo<T> g)
{
    while (g.hash.size() > 2)
    {
        //ELEGIR UNIFORMEMENTE UNA ARISTA ALEATORIA
		int random = rand() % g.hash.size();
        //----------------------------------------------------------------------------//
		T vertice1 = g.llaves[random];//IMPORTANTE : Tiempo encontrar primer vertice aleatorio = O(1)
        //----------------------------------------------------------------------------//
		swap(g.llaves[random], g.llaves[g.llaves.size() - 1]);
		g.llaves.pop_back();
		vector<T>& vectorV1 = g.hash[vertice1].adyacencias;
		T vertice2 = vectorV1[rand() % vectorV1.size()];
        //FIN


        //CONTRAER Y ELIMINAR AUTOCICLOS
        //----------------------------------------------------------------------------//
        //IMPORTANTE : Tiempo contraer= O(t * Tiempo eliminar) donde t = adyacentes de vertice1
        g.contraer(vertice1,vertice2);//contraer tambien elimina autociclos 
        //----------------------------------------------------------------------------//
        g.hash.erase(vertice1);//O(1) vertice1 se contrae hacia vertice2 por eso es eliminado vertice1
        //FIN

    }

    //solo quedaran dos vertices con igual numero de adyacente, se puede tomar cualquiera
    auto salida = g.hash.begin();
    return g.hash[salida->first].adyacencias.size();
}

template <class T>
inline void Grafo<T>::contraer(T v1, T v2)
{
    vector<T>& vec = hash[v1].adyacencias;
    while(!vec.empty())
    { 
        T aux = vec.operator[](0);
        
        int eliminados = eliminarAristaUnaVez(v1, vec.operator[](0));
        //----------------------------------------------------------------------------//
        /*IMPORTANTE : Tiempo eliminar= O((T eliminar v1 de v2) + (T eliminar v2 de v1))*/
        //----------------------------------------------------------------------------//
        /*ACLARACION: al eliminar se hace un swap con el ultimo elemento que aun no ha sido comparado,
        y como el eliminar se hace siempre, el swap se hara siempre, entonces debemos evaluar
        cada vez el ese elemento, por eso siempre comparamos if(v2 != vec.operator[](0))*/

        if(v2 != aux)
        {
            form(i,0,eliminados)
            {
                insertarArista(aux,v2);
            }
        }
    }

}

template <class T>
inline void Grafo<T>::leerArchivo(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
	if (!archivo.is_open()) 
    {
		cout << "No se pudo abrir el archivo." << endl;
	}
	else
	{
		T origen; // Nodo origen
		while (archivo >> origen) 
        {
			T destino; // Nodo destino
			llaves.push_back(origen);

			while (archivo >> destino && destino != "-1") 
            {
				// Inserta solo vertice y sus adyacentes
				insertar(origen, destino);
			}
		}
		archivo.close(); 
	}
    cout << "----------------------------------" << endl;
	cout << "unordore_map cantidad llaves(vertices): " << hash.size() << endl;
	cout << "vector llaves cantidad elementos(verices): " << llaves.size() << endl;
    cout << "----------------------------------" << endl;

	
}

template <class T>
inline void Grafo<T>::leerArchivoNumeros(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
	if (!archivo.is_open()) 
    {
		cout << "No se pudo abrir el archivo." << endl;
	}
	else
	{
		T origen; // Nodo origen
		while (archivo >> origen) 
        {
			T destino; // Nodo destino
			llaves.push_back(origen);

			while (archivo >> destino && destino != -1) 
            {
				// Inserta solo vertice y sus adyacentes
				insertar(origen, destino);
			}
		}
		archivo.close(); 
	}
    cout << "----------------------------------" << endl;
	cout << "hash llaves: " << hash.size() << endl;
	cout << "vector llaves: " << llaves.size() << endl;
    cout << "----------------------------------" << endl;
	
}

template <class T>
inline void Grafo<T>::mostrar(Grafo<T> *g)
{
    cout << "------------------------------------------------------------------------" << endl;
    
    for (auto &i : g->hash)
    {
        cout << "Llave: "<< i.first << endl;
        cout << "Adyacencias = [ ";
        for (auto &j : i.second.adyacencias)
        {
            cout <<j<< " | ";
        }
        cout <<" ]"<< endl;
    }
    cout << "--------------------------------------------------------------------------" << endl;

}