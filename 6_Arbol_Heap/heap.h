#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>

template <class T>
class Heap {
private:
	T *data; // arreglo dinámico
	unsigned int size_heap; // capacidad máxima
	unsigned int count; // número de elementos actuales

	unsigned int parent(unsigned int i) {return (i - 1) / 2;}
	unsigned int left(unsigned int i) {return (2 * i) + 1;}
	unsigned int right(unsigned int i) {return (2 * i) + 2;}

	void swap(unsigned int i, unsigned int j) {
		T aux = data[i];
		data[i] = data[j];	
		data[j] = aux;
	}

	void heapifyDown(unsigned int i) {
		unsigned int l = left(i);
		unsigned int r = right(i);
		unsigned int largest = i;

		// Prioridad mayor heap máximo
		if (l<count && data[l]<data[largest]) largest = l;
		if (r<count && data[r]<data[largest]) largest = r;
		if (largest != i) {
			swap(i, largest);
			heapifyDown(largest);
		}
	}

	void heapifyUp(unsigned int i) {
		while (i > 0 && data[parent(i)] > data[i]) {
			swap(i, parent(i));
			i = parent(i);
		}
	}

public:
	Heap(unsigned int sze) {
		data = new T[sze];
		count = 0;
	}

	~Heap() {delete[] data;}

	/*

	push

	Descripción: Agregue un dato a la fila priorizada.

	Entrada: El dato n tipo entero (int) que se desea agregar a la fila priorizada.

	Salida:	Nada.

	Precondición: n es un entero.

	Postcondición: La fila priorizada contiene un nuevo dato.
	*/

	void push(T val) {
		if (count < size_heap){
		data[count] = val;
		count++;
		heapifyUp(count - 1);
		}
	}

	/*

	pop

	Descripción: Saca de la fila priorizada el dato que tiene mayor prioridad.

	Entrada: Nada.

	Salida:	Nada.

	Precondición: Que la fila priorizada contenga al menos 1 dato.

	Postcondición: La fila priorizada queda sin el dato con mayor prioridad.
	*/

	void pop() {
		if (count>0) {
		data[0] = data[count - 1];
		count--;
		if (count > 0) heapifyDown(0);
		}
	}

	T top() const {
		if (count != 0) return data[0];
	}

	/*

	empty

	Descripción: Regresa un valor boleando diciendo si la fila priorizada esta vacía o tiene datos.

	Entrada: Nada.

	Salida:	Un valor boleano que sea verdadero si la fila priorizada esta vacía o flase si tiene datos.

	Precondición: Nada.

	Postcondición: La estructura no se modifica.

	*/

	bool empty() const {return (count == 0);}


	/*size

	Descripción: Regresa la cantidad de datos que tiene la fila priorizada.

	Entrada: Nada.

	Salida:	Un valor entero con la cantidad de datos en la fila priorizada.

	Precondición: Nada.
	
	Postcondición: La estructura no se modifica.
	*/

	unsigned int size() const {return count;}

	std::string toString() const {
		std::stringstream aux;
		aux << "[";	for (unsigned int i = 0; i < count; i++) {
			if (i != 0) {
				aux << " ";
			} aux << data[i];
		} aux << "]";
		return aux.str();
	}

};

#endif
