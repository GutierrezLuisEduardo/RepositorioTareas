#ifndef SPLAY_H_
#define SPLAY_H_

#include <iostream>
#include <sstream>
#include <string>

template <class T>
class SplayTree {
private:
    struct Node {
        T value;
        Node *left, *right, *parent;

        Node(T val) : value(val), left(NULL), right(NULL), parent(NULL) {}
    };

    Node* root;
    

    // Helper para imprimir Inorder
    void inorder(Node* p, std::stringstream& ss, bool& first) {
        if (!p) return;
        inorder(p->left, ss, first);
        if (!first) ss << " ";
        ss << p->value;
        first = false;
        inorder(p->right, ss, first);
    }

    // Helper para imprimir Preorder
    void preorder(Node* p, std::stringstream& ss, bool& first) {
        if (!p) return;
        if (!first) ss << " ";
        ss << p->value;
        first = false;
        preorder(p->left, ss, first);
        preorder(p->right, ss, first);
    }

    // Rotación derecha (Zig)
    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right) y->right->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    // Rotación izquierda (Zag)
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        if (!x->parent) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    // Mover nodo x a la raíz
    void splay(Node* x) {
        while (x->parent) {
            if (!x->parent->parent) {
                if (x == x->parent->left)
                    rightRotate(x->parent);
                else
                    leftRotate(x->parent);
            } else {
                Node* p = x->parent;
                Node* g = p->parent;
                if (x == p->left && p == g->left) {
                    rightRotate(g);
                    rightRotate(p);
                } else if (x == p->right && p == g->right) {
                    leftRotate(g);
                    leftRotate(p);
                } else if (x == p->right && p == g->left) {
                    leftRotate(p);
                    rightRotate(g);
                } else {
                    rightRotate(p);
                    leftRotate(g);
                }
            }
        }
    }

    // Helper para reemplazar nodos en eliminación
    void replace(Node* u, Node* v) {
        if (!u->parent) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v) v->parent = u->parent;
    }

    // Buscar nodo min en subárbol (para sucesor)
    Node* subtreeMin(Node* u) {
        while (u->left) u = u->left;
        return u;
    }

    // Liberar memoria
    void clear(Node* p) {
        if (!p) return;
        clear(p->left);
        clear(p->right);
        delete p;
    }

public:
    SplayTree() : root(NULL) {}
    ~SplayTree() { clear(root); }

    void add(T val) {
        Node* node = new Node(val);
        if (!root) {
            root = node;
            return;
        }

        Node* curr = root;
        Node* prev = NULL;
        while (curr) {
            prev = curr;
            if (val < curr->value) curr = curr->left;
            else if (val > curr->value) curr = curr->right;
            else {
                // Duplicado, solo splay al nodo existente y borrar el nuevo
                splay(curr);
                delete node;
                return;
            }
        }

        node->parent = prev;
        if (val < prev->value) prev->left = node;
        else prev->right = node;

        splay(node);
    }

    bool find(T val) {
        Node* curr = root;
        Node* prev = NULL;
        while (curr) {
            if (val == curr->value) {
                splay(curr);
                return true;
            }
            prev = curr;
            if (val < curr->value) curr = curr->left;
            else curr = curr->right;
        }
        if (prev) splay(prev); // Splay al último visitado si no se encuentra
        return false;
    }

    void remove(T val) {
        if (!root) return;
        
        // 1. Encontrar el nodo (Estilo BST estándar, sin splay durante la búsqueda)
        Node* curr = root;
        while (curr && curr->value != val) {
            if (val < curr->value) curr = curr->left;
            else curr = curr->right;
        }

        if (!curr) return; // No encontrado

        Node* splayTarget = curr->parent; // Por defecto haremos splay al padre

        // 2. Eliminación BST Estándar
        if (!curr->left) {
            replace(curr, curr->right);
        } else if (!curr->right) {
            replace(curr, curr->left);
        } else {
            // Caso 2 hijos: encontrar sucesor
            Node* successor = subtreeMin(curr->right);
            if (successor->parent != curr) {
                splayTarget = successor->parent; // El punto de splay será el padre original del sucesor
                replace(successor, successor->right);
                successor->right = curr->right;
                successor->right->parent = successor;
            } else {
                 splayTarget = successor; // Si el sucesor es hijo directo, splay el sucesor
            }
            replace(curr, successor);
            successor->left = curr->left;
            successor->left->parent = successor;
        }
        
        delete curr;

        // 3. Splay Bottom-Up (al padre del nodo físicamente eliminado/movido)
        if (splayTarget) {
            splay(splayTarget);
        }
    }

    std::string inorder() {
        std::stringstream ss;
        ss << "[";
        bool first = true;
        inorder(root, ss, first);
        ss << "]";
        return ss.str();
    }

    std::string preorder() {
        std::stringstream ss;
        ss << "[";
        bool first = true;
        preorder(root, ss, first);
        ss << "]";
        return ss.str();
    }
};

#endif