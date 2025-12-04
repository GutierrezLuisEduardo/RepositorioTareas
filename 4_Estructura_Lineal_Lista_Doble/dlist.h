#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <sstream>

template <typename T>
class DList {
private:
    struct DLink {
        T value;
        DLink* next;
        DLink* previous;
        DLink(T val) : value(val), next(nullptr), previous(nullptr) {}
    };

    DLink* head;
    DLink* tail;
    int size;

public:
    DList() : head(nullptr), tail(nullptr), size(0) {}

    // Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
    // en formatos compatibles con el main

    std::string toStringForward() const {
        std::stringstream aux;
        DLink *p;

        p = head;
        aux << "[";
        while (p != 0) {
            aux << p->value;
            if (p->next != 0) {
                aux << ", ";
            }
            p = p->next;
        }
        aux << "]";
        return aux.str();
    }

    std::string toStringBackward() const {
        std::stringstream aux;
        DLink *p;

        p = tail;
        aux << "[";
        while (p != 0) {
            aux << p->value;
            if (p->previous != 0) {
                aux << ", ";
            }
            p = p->previous;
        }
        aux << "]";
        return aux.str();
    }

    /*
    insertion
    Descripción: Insertar un elemento en la estructura de datos (create) de acuerdo a la política de acceso de la estructura
    Entrada: Estructura de datos y elemento a insertar
    Salida: Nada
    Precondición: Una estructura válida
    Postcondición: Estructura modificada
    */
    void insertion(T value) {
        DLink* newNode = new DLink(value);
        if (size == 0) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->previous = tail;
            tail = newNode;
        }
        size++;
    }

    /*
    search
    Descripción: Encuentra el elemento en la estructura y devuelve su posición.
    Entrada: El elemento a buscar (un entero)
    Salida: La posición del elemento a buscar o -1 ( si no existe un elemento con esas características)
    Precondición: Estructura de datos válida
    Postcondición: Estructura de datos válida
    */
    // busca elemento y devuelve su posición (índice) o si no -1
    int search(T value) const {
        DLink* current = head;
        int index = 0;
        while (current != nullptr) {
            if (current->value == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1; // No encontrado
    }

    /*
    update
    Descripción:Actualizar un elemento dentro de la estructura de datos (update)
    de acuerdo a la estructura de datos específica.
    Entrada: posición del elemento a actualizar, valor nuevo.
    Salida:	Nada
    Precondición: Estructura de datos válida
    Postcondición: Estructura de datos válida con el cambio
    */
    void update(int position, T newValue) {
        if (position >= 0 && position < size) { // Sólo si está dentr del rango
        DLink* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }
        current->value = newValue;
        }
    }

    /*
    deleteAt
    Descripción: Borrar (eliminar) un elemento dentro de la estructura de datos segun
    su posición.
    Entrada: La posición del elemento a eliminar.
    Salida: El valor del elemento eliminado.
    Precondición: Estructura de datos válida
    Postcondición: Estructura de datos válida con el cambio
    */
    T deleteAt(int position) {
        DLink* current = head;
        for (int i = 0; i < position; i++) {current = current->next;}

        T value = current->value;

        if (current->previous != nullptr) {
            current->previous->next = current->next;}
        else {
            head = current->next;
        }

        if (current->next != nullptr) {
            current->next->previous = current->previous;
        }
        else {
            tail = current->previous;
        }

        delete current;
        size--;
        return value;
    }

    ~DList() {
        DLink* current = head;
        while (current != nullptr) {
            DLink* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
};

#endif
