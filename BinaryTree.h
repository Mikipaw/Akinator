//
// Created by mikhalinho on 13.11.2021.
//

#ifndef AKINATOR_BINARYTREE_H
#define AKINATOR_BINARYTREE_H

#include <cstdio>
#include <cstring>
#include "Stack.h"
#include "ErrorList.h"
#include "mystr.h"

typedef simple_string T;

struct Node {
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    bool question = false;
};

char* get_line(char* buffer, int max_size);

char* strchar(char* buffer, char sym);

class BinaryTree {

public:

    BinaryTree();

    explicit BinaryTree(const char* input);

    BinaryTree(T *array, int arr_size);

    ~BinaryTree() { destroy_tree(); }

    void
    add(T item);

    Node*
    search(T item) { return search_(item, root); }

    void
    destroy_tree();

    bool
    contains(T item);

    int
    get_height() { return get_height_(root); }

    int
    get_size() const { return size; }

    bool
    is_empty() { return !root; }

    //char* f_round();

    Stack
    elements();

    bool
    erase(T item);

    void
    start() { do_question(root); }

private:
    void destroy_tree_(Node *node);

    void add_from_file (Node* node, simple_string* pointers, size_t* limit);

    void add_(T item, Node *node);

    int do_question(Node *node);

    Node *search_(T item, Node *node) {
        if (node != nullptr) {
            if (item == node->data) return node;
            if (item < node->data) return search_(item, node->left);
            else return search_(item, node->right);
        } else return nullptr;
    }

    int Add_new_object(Node *node);

    void f_round_(Node *node);

    int get_height_(const Node *node);

    void Read_in_tree(size_t* number_of_lines, Node* node);

    void elements_(Node *node);

    Node *minValueNode(Node *node) {
        Node *current = node;
        while (current && current->left != nullptr) current = current->left;
        return current;
    }

    Node *erase_(T item, Node *node);

    int size = 1;
    int index = 0;
    Stack Elements;
    Node* root;
    char* f_round_str;
    char* freebuf = new char[LIMITED_SIZE_OF_STRING];
    char* text = nullptr;

};

//TODO: problems in output and shit with scanf

#endif //AKINATOR_BINARYTREE_H
