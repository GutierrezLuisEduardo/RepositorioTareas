#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

template <typename T>
struct NODE {
    T data;
    NODE<T>* left;
    NODE<T>* right;
    NODE(const T& v): data(v), left(nullptr), right(nullptr) {};
};

template <typename T>
class BST {
private:
    NODE<T>* root;

    /* funciones de apoyo */
    void preorder(NODE<T>* node, std::string &out, bool &first) {
        if (!node) return;
        if (!first) out += " ";
        out += toString(node->data);
        first = false;
        preorder(node->left, out, first);
        preorder(node->right, out, first);
    }

    void inorder(NODE<T>* node, std::string &out, bool &first) {
        if (!node) return;
        inorder(node->left, out, first);
        if (!first) out += " ";
        out += toString(node->data);
        first = false;
        inorder(node->right, out, first);
    }

    void postorder(NODE<T>* node, std::string &out, bool &first) {
        if (!node) return;
        postorder(node->left, out, first);
        postorder(node->right, out, first);
        if (!first) out += " ";
        out += toString(node->data);
        first = false;
    }

    int alturaRec(NODE<T>* node) {
        if (!node) return 0;
        int hl = alturaRec(node->left);
        int hr = alturaRec(node->right);
        return 1 + (hl > hr ? hl : hr);
    }

    int countNodes(NODE<T>* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void destroy(NODE<T>* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    std::string toString(const T& val) {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    }

public:
    BST(): root(nullptr) {}
    ~BST() { destroy(root); }

    /* add */
    void add(const T& val) {
        if (!root) {
            root = new NODE<T>(val);
            return;
        }
        NODE<T>* act = root;
        while (true) {
            if (val == act->data) {
                // ignora duplicados
                return;
            } else if (val < act->data) {
                if (!act->left) {
                    act->left = new NODE<T>(val);
                    return;
                } else act = act->left;
            } else {
                if (!act->right) {
                    act->right = new NODE<T>(val);
                    return;
                } else act = act->right;
            }
        }
    }

    /* visit
    Descripción: Despliega c/uno de los datos almacenados en el BST:
    1. Preorder
    2. Inorder
    3. Postorder
    4. Level by level
    """
    [11 8 12 110 17 112]
    [8 11 12 17 110 112]
    [8 17 112 110 12 11]
    [11 8 12 110 17 112]
    """
    Entrada: Nada
    Salida:	String con los 4 recorridos, seperados por un salto de
    línea entre cada uno.
    Precondición: Un BST válido
    Postcondición: No se modica la estructura */
    std::string visit() {
        std::string sp = "", sio = "", spo = "", sl = "";
        bool first;

        // preorder
        first = true;
        preorder(root, sp, first);
        sp = "["+sp+"]";

        // inorder
        first = true;
        inorder(root, sio, first);
        sio = "["+sio+"]";

        // postorder
        first = true;
        postorder(root, spo, first);
        spo = "["+spo+"]";

        // level order
        int n = countNodes(root);
        if (n == 0) {
            sl = "[]";
        } else {
            /* q apunta a un arreglo dinámico de punteros a node */
            NODE<T>** q = new NODE<T>*[n];
            int head = 0, tail = 0;
            /* puntero en la posición tail dentro del arreglo */
            q[tail++] = root; 
            bool firstLevel = true;
            while (head < tail) {
                NODE<T>* node = q[head++];
                if (!firstLevel) sl += " ";
                sl += toString(node->data);
                firstLevel = false;
                if (node->left) q[tail++] = node->left;
                if (node->right) q[tail++] = node->right;
            }
            delete [] q;
            sl = "["+sl+"]";
        }
        return sp+"\n"+sio+"\n"+spo+"\n"+sl;
    }

    /*height
    Descripción: Obtiene la altura del BST (el número del nivel más
    profundo). Un árbol con solo la raíz tiene altura 1
    Entrada: Nada
    Salida: Un entero con el cual indicará la altura del BST
    Precondición:	Un BST válido
    Postcondición: No se modica la estructura*/
    int height() {
        return alturaRec(root);
    }

    /*ancestors
    Descripción: Obtiene los ancestros de un dato (todos los nodos
    arribas de n en línea directa hasta llegar a la raiz)
    "[10 12 110]"
    Entrada: El dato (valor del nodo) del cual se desea conocer los
    ancestros.
    Salida:	Un string con los valores de los nodos ancentros
    Precondición: Un BST válido
    Postcondición: No se modica la estructura*/
    std::string ancestors(const T& val) {
        if (!root) return "[]";
        int n = countNodes(root);
        T* path = new T[n];
        int idx = 0;
        NODE<T>* cur = root;

        while (cur && cur->data != val) {
            path[idx++] = cur->data;
            if (val < cur->data) cur = cur->left;
            else cur = cur->right;
        }

        if (!cur) { // no encontrado
            delete [] path;
            return "[]";
        }

        if (idx == 0) { // el valor es la raíz
            delete [] path;
            return "[]";
        }

        std::ostringstream oss;
        oss << "[";
        for (int i = 0; i < idx; ++i) {
            if (i > 0) oss << " ";
            oss << path[i];
        }
        oss << "]";
        delete [] path;
        return oss.str();
    }

    /*whatlevelamI
    Descripción: Obtiene el valor del nivel del nodo actual
    Entrada: El dato (valor del nodo) del cual se desea conocer su
    nivel.
    Salida:	El entero con el valor de nivel
    Precondición:	Un BST válido
    Postcondición: No se modica la estructura*/
    int whatlevelamI(const T& val) {
        NODE<T>* cur = root;
        int lvl = 1;
        while (cur) {
            if (cur->data == val) return lvl;
            if (val < cur->data) cur = cur->left;
            else cur = cur->right;
            ++lvl;
        }
        return 0; // no encontrado
    }
};

#endif
