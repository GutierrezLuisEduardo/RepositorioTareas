#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

template <typename T>
struct Link {
    T dato; // Dato que almacena el nodo
    Link* siguiente; // Puntero al nodosiguiente

    Link(T d) : dato(d), siguiente(nullptr) {} // Constructor
};

template <typename T>
class List {
private:
    Link<T>* cabeza; // Puntero al primer nodo

public:
    List() : cabeza(nullptr) {} // Constructor

    // Método para insertar un nuevo nodo al final
    void insertion(T dato) {
        Link<T>* nuevoNodo = new Link<T>(dato);
        /*Lista vacía, nuevo nodo es la cabeza y el siguiente aún
        apunta a null*/
        if (!cabeza) cabeza = nuevoNodo;
        else {
            Link<T>* temp = cabeza; // Empieza recorrido desde cabeza
            /* Mientras el valor temporal apunte a un siguiente, apun
            ta a ese siguiente y así llega al último nodo*/
            while (temp->siguiente) temp = temp->siguiente;
            temp->siguiente = nuevoNodo; // Enlaza el nuevo nodo
        }
    }

    // Buscar un valor para devolver su índice, o si no -1
    int search(T valor) const {
        Link<T>* p = cabeza;
        int index = 0;

        while (p != nullptr) {
            if (p->dato == valor) {
                return index;
            }
            p = p->siguiente;
            index++;
        }
        return -1; 
    }

    // Dada una posición, elimina un nodo de la lista
    void deleteAt(int pos) {
        // Si la lista está vacía, no hay nada que eliminar
        if (!cabeza) return; 

        Link<T>* actual = cabeza;

        // Si se quiere eliminar el primer nodo
        if (pos == 0) {
            cabeza = cabeza->siguiente;
            delete actual;
            return;
        }

        // Contador para la posición
        int cnt = 0;
        // Nodo anterior para mantener la referencia
        Link<T>* anterior = nullptr;

        while (actual && cnt < pos) {
            anterior = actual;
            actual = actual->siguiente;
            cnt++;
        }

        // Si se encontró el nodo en la posición deseada
        if (actual) {
            anterior->siguiente = actual->siguiente; // Reenlazando
            delete actual; // Eliminar el nodo
        }
    }

    // Actualizar el valor en la posición dada si existe
    void update(int pos, T nuevoValor) {
        Link<T>* p = cabeza;
        int index = 0;

        while (p != nullptr) {
            if (index == pos) {
                p->dato = nuevoValor;
                return;
            }
            p = p->siguiente;
            index++;
        }
    }

    std::string toString() const {
        std::stringstream aux;
        Link<T> *p;

        p = cabeza;
        aux << "[";
        while (p != 0) {
            aux << p->dato;
            if (p->siguiente != 0) {
                aux << ", ";
            }
            p = p->siguiente;
        }
        aux << "]";
        return aux.str();
    }

    // Destructor para liberar la memoria
    ~List() {
        Link<T>* actual = cabeza;
        while (actual != nullptr) {
            Link<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};
#endif