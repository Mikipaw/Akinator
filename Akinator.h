//
// Created by mikhalinho on 13.11.2021.
//

#ifndef AKINATOR_AKINATOR_H
#define AKINATOR_AKINATOR_H

#include <string.h>
#include "Stack.h"
#include "ErrorList.h"
#include "mystr.h"

typedef simple_string T;

inline const char* OUTPUT_FILE_NAME = "Dump_file0.jpg";
inline const char* DOT              = R"(dot Graph.dot -Tjpg -o )";


struct Node {
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    bool question = false;
};

char* strchar(char* buffer, char sym);

class Akinator {

public:

    Akinator();

    explicit Akinator(const char* input);

    ~Akinator() { destroy_tree(); }

    Node*
    search(T item) { return search_(item, root); }

    void
    destroy_tree();

    bool
    contains(T item);

    [[nodiscard]] int
    get_height() { return get_height_(root); }

    [[nodiscard]] int
    get_size() const { return size; }

    bool
    is_empty() { return !root; }

    Stack
    elements();

    bool
    erase(T item);

    int
    Dump();

    void
    start() { do_question(root); };

private:
    void destroy_tree_(Node *node);

    void _dumpE (Node* node) const;

    void _dumpV (Node* node) const;

    int do_question(Node *node);

    Node *search_(T item, Node *node) {
        if (node != nullptr) {
            if (item == node->data) return node;
            if (item < node->data)  return search_(item, node->left);
            else                    return search_(item, node->right);
        }
        else return nullptr;
    }

    int Add_new_object(Node *node);

    void f_round_(Node *node);

    int get_height_(const Node *node);

    void Read_in_tree(size_t* number_of_lines, Node* node);

    void elements_(Node *node);

    Node *erase_(T item, Node *node);

    int size = 1;
    //int index = 0;
    Stack Elements;
    Node* root;
    char* f_round_str;
    char* freebuf = new char[LIMITED_SIZE_OF_STRING];
    char* text = nullptr;

};

#endif //AKINATOR_AKINATOR_H
