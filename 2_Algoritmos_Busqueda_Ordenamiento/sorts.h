#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include <iostream>

template <class T>
class Sorts {
public:
    // Métodos de Ordenamiento
    void ordenaSeleccion(std::vector<T>& v);
    void ordenaBurbuja(std::vector<T>& v);
    void ordenaMerge(std::vector<T>& v);

    // Métodos de Búsqueda
    int busqSecuencial(const std::vector<T>& v, T val);
    int busqBinaria(const std::vector<T>& v, T val);

private:
    // Métodos auxiliares para Merge Sort
    void mergeSplit(std::vector<T>& v, std::vector<T>& temp, int low, int high);
    void merge(std::vector<T>& v, std::vector<T>& temp, int low, int mid, int high);
    
    // Método auxiliar para intercambiar elementos
    void swap(std::vector<T>& v, int i, int j);
};

// Función auxiliar para intercambiar valores
template <class T>
void Sorts<T>::swap(std::vector<T>& v, int i, int j) {
    T aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

// 1. Selection Sort, complejidad de O(n^2)
template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[minIndex]) {
                minIndex = j;
            }
        }
        swap(v, i, minIndex);
    }
}

// 2. Bubble Sort, complejidad de O(n^2)
template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T>& v) {
    for (int i = v.size() - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (v[j] > v[j + 1]) {
                swap(v, j, j + 1);
            }
        }
    }
}

// 3. Merge Sort, complejidad de O(n log n)

// Método público que inicializa el proceso
template <class T>
void Sorts<T>::ordenaMerge(std::vector<T>& v) {
    std::vector<T> temp(v.size());
    mergeSplit(v, temp, 0, v.size() - 1);
}

// División recursiva
template <class T>
void Sorts<T>::mergeSplit(std::vector<T>& v, std::vector<T>& temp, int low, int high) {
    if (low < high) {
        int mid = (high + low) / 2;
        mergeSplit(v, temp, low, mid);      // Ordenar mitad izquierda
        mergeSplit(v, temp, mid + 1, high); // Ordenar mitad derecha
        merge(v, temp, low, mid, high);     // Combinar ambas mitades
    }
}

// Fusión de sub-arreglos ordenados
template <class T>
void Sorts<T>::merge(std::vector<T>& v, std::vector<T>& temp, int low, int mid, int high) {
    int i = low;      // Índice para la parte izquierda
    int j = mid + 1;  // Índice para la parte derecha
    int k = low;      // Índice para el arreglo temporal

    while (i <= mid && j <= high) {
        if (v[i] < v[j]) {
            temp[k] = v[i];
            i++;
        } else {
            temp[k] = v[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes de la mitad izquierda
    while (i <= mid) {
        temp[k] = v[i];
        k++;
        i++;
    }

    // Copiar elementos restantes de la mitad derecha
    while (j <= high) {
        temp[k] = v[j];
        k++;
        j++;
    }

    // Copiar del temporal al original
    for (int m = low; m <= high; m++) {
        v[m] = temp[m];
    }
}


// 4. Búsqueda Secuencial,, complejidad de O(n)
template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T>& v, T val) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == val) {
            return i;
        }
    }
    return -1;
}

// 5. Binary Search, complejidad de O(log n)
// Requiere que el arreglo esté ordenado previamente
template <class T>
int Sorts<T>::busqBinaria(const std::vector<T>& v, T val) {
    int low = 0;
    int high = v.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (v[mid] == val) {
            return mid; // Encontrado
        } else if (val < v[mid]) {
            high = mid - 1; // Buscar en la mitad inferior
        } else {
            low = mid + 1;  // Buscar en la mitad superior
        }
    }
    return -1; // No encontrado
}

#endif