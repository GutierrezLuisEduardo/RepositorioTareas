#ifndef FUNCIONES_H
#define FUNCIONES_H

class Funciones {
public:
    /* Suma iterativa */
    int sumaIterativa(int n) {
        int suma=0;
        for (int i=1; i<=n; ++i) {
            suma+=i;
        }
        return suma;
    }

    /* Suma recursiva */
    int sumaRecursiva(int n) {
        if (n<=1) return n;
        return n + sumaRecursiva(n - 1);
    }

    /* Suma directa */
    int sumaDirecta(int n) {
        return (n * (n + 1)) / 2; // aún si n es 0, srve
    }
};

#endif // FUNCIONES_H
