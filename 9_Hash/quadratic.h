#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>

template <class Key, class Value>
class Quadratic {
private:
    unsigned int (*func)(const Key);
    unsigned int size, count;

    Key *keys;
    Key initialValue;
    Value *values;

    long indexOf(const Key&) const;

public:
    Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
    ~Quadratic();
    bool full() const;
    bool put(Key, Value);
    bool contains(const Key&) const;
    Value get(const Key&);
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f)(const Key)) {
    size=sze;
    func=f;
    count=0;
    initialValue=init;

    keys=new Key[size];
    values=new Value[size];

    for (unsigned int i=0; i<size; i++) keys[i]=initialValue;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
    delete[] keys;
    delete[] values;
    keys=nullptr;
    values=nullptr;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    return count>=size;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key& k) const {
    unsigned int start=func(k)%size;
    unsigned int i=start;

    for (unsigned int j=0; j<size; j++) {
        if (keys[i]==k) {
            return i;
        }
        if (keys[i]==initialValue) {
            return -1; // no está y hay espacio vacío
        }
        i=(start+j*j)%size;  // cuadrático
    }
    return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
    if (full()) return false;

    long pos=indexOf(k);
    if (pos!=-1) {
        values[pos]=v;
        return true;
    }

    unsigned int start=func(k)%size;
    unsigned int i=start;

    for (unsigned int j=0; j<size; j++) {
        if (keys[i]==initialValue) {
            keys[i]=k;
            values[i]=v;
            count++;
            return true;
        }
        i=(start+j*j)%size;
    }
    return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key &k) const {
    return indexOf(k)!=-1;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key &k) {
    long pos=indexOf(k);
    if (pos!=-1) {return values[pos];}
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
    count=0;
    for (unsigned int i=0; i<size; i++) keys[i]=initialValue;
}

// impresion clase quadratic
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
				aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}

#endif