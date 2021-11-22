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

inline const char* GOLD = "gold";
inline const char* LIME = "lime";


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
    get_height() const { return get_height_(root); }

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

    int
    verification() { return check(root);};

    Stack
    definition (const char* object);

private:
    int check (Node* node);

    void destroy_tree_(Node *node);

    void _dumpE (Node* node) const;

    void _dumpV (Node* node) const;

    int do_question(Node *node);

    Node *search_(T item, Node *node);

    int Add_new_object(Node *node);

    void f_round_(Node *node);

    int get_height_(const Node *node) const;

    void Read_in_tree(size_t* number_of_lines, Node* node);

    void elements_(Node *node);

    Node *erase_(T item, Node *node);

    int size = 1;
    Stack Elements = Stack(16);
    Node* root;
    char* f_round_str;
    char* freebuf = new char[LIMITED_SIZE_OF_STRING];
    char* text = nullptr;

};

inline Node* Akinator::search_(T item, Node *node) {
    if (node == nullptr) {
        Elements.pop();
        return nullptr;
    }

    if (!node->question) {
        if (str_equal(node->data.string, item.string)) return node;
        else return nullptr;
    }
    else {
        Elements.push(node->data);
        Node* new_node = search_(item, node->left);
        if (new_node != nullptr) return new_node;

        simple_string tmp_ss;
        Elements.pop(&tmp_ss);

        simple_string denial(LIMITED_SIZE_OF_STRING * 2);
        strcpy(denial.string, "\tnot");

        strcat(denial.string, tmp_ss.string);
        Elements.push(denial);

        new_node = search_(item, node->right);
        if (new_node == nullptr) Elements.pop();
        return new_node;
    }

    /*if (str_equal(node->data.string, item.string)) return node;

    Elements.push(node->data);
    Node* newNode = search_(item, node->left);

    if (newNode != nullptr) return newNode;
    else {
        //Elements.pop();
        simple_string tmp_ss;
        Elements.pop(&tmp_ss);

        simple_string denial(LIMITED_SIZE_OF_STRING * 2);
        strcpy(denial.string, "not ");

        strcat(denial.string, tmp_ss.string);
        Elements.push(denial);

        return search_(item, node->right);
    }*/
}

#endif //AKINATOR_AKINATOR_H
