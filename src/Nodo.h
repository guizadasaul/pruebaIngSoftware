#pragma once

#include "stdlib.h"
#include "time.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <cstdlib>
#include <ctime>

#define form(i,s,e)     for(int i = s; i < e ; i++)
#define endl            '\n'
#define DBG(x) cerr<<#x<<' = '<<(x)<<endl

using namespace std;

template <class T>
class Nodo
{
public:
    vector< T > adyacencias;



    Nodo();
    ~Nodo();

    int eliminarAdyacenteUnaVez(T eliminado);
};

template <class T>
inline Nodo<T>::Nodo()
{
}

template <class T>
inline Nodo<T>::~Nodo()
{
}

template <class T>
inline int Nodo<T>::eliminarAdyacenteUnaVez(T eliminado)
{
    int res = 0;
    for(int i = 0; i < adyacencias.size(); i++)
    {
        if (adyacencias[i] == eliminado)
        {
            swap(adyacencias[i], adyacencias.back());
            adyacencias.pop_back();
            i--;
            res++;
        }
    } 
    return res;
}