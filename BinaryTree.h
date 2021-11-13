//
// Created by mikhalinho on 13.11.2021.
//

#ifndef AKINATOR_BINARYTREE_H
#define AKINATOR_BINARYTREE_H

#include <cstdio>
#include <cstring>
#include "Stack.h"

typedef simple_string T;

class BinaryTree{
    struct Node
    {
        T data;
        Node* left = nullptr;
        Node* right = nullptr;

        bool question = false;
    };


public:

    BinaryTree() { root = nullptr; }

    BinaryTree(T* array, int arr_size);

    ~BinaryTree() { destroy_tree(); }

    void add(T item);

    Node* search(T item) { return search_(item, root); }

    void destroy_tree() { destroy_tree_(root); }

    bool contains(T item);

    int get_height() { return get_height_(root); }

    int get_size() const { return size; }

    bool is_empty() { return !root; }

    char* f_round();

    Stack elements();

    bool erase(T item);



private:
    void destroy_tree_(Node* node);

    void add_(T item, Node* node);

    Node* search_(T item, Node *node) {
        if(node != nullptr){
            if(item == node->data) return node;
            if(item < node->data) return search_(item, node->left);
            else return search_(item, node->right);
        }
        else return nullptr;
    }

    void f_round_(Node* node);

    int get_height_(const Node *node);

    void elements_(Node* node);

    Node* minValueNode(Node* node) {
        Node* current = node;
        while(current && current->left != nullptr) current = current->left;
        return current;
    }

    Node* erase_(T item, Node* node) {
        if (node == nullptr) return node;
        if (item < node->data) node->left = erase_(item, node->left);
        else if(item > node->data) node->right = erase_(item, node->right);
        else {
            if(node->left == nullptr){
                Node* temp = node->right;
                free(node);
                return temp;
            }
            else if(node->right == nullptr){
                Node* temp = node->right;
                free(node);
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = erase_(item, node->right);
        }
        return node;
    }

    int size = 1;
    Stack Elements;
    Node* root;
    char* f_round_str;

};

#endif //AKINATOR_BINARYTREE_H
