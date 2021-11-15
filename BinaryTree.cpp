//
// Created by mikhalinho on 13.11.2021.
//

#include "BinaryTree.h"

void BinaryTree::add(T item){
    if(this->contains(item)) return;

    if(root != nullptr){
        add_(item, root);
        size++;
    }
    else{
        root = new Node;
        root->data = item;
        root->left = nullptr;
        root->right = nullptr;
    }
}


BinaryTree::BinaryTree(T* array, int arr_size) {
    root = nullptr;
    for (int i = 0; i < arr_size; ++ i) add(array[i]);
}


bool BinaryTree::contains(T item) {
    Node* result = search_(item, root);

    return result != nullptr;
}


char* BinaryTree::f_round() {
    f_round_(root);
    char* result = f_round_str;
    f_round_str = nullptr;

    return result;
}


Stack BinaryTree::elements() {
    elements_(root);
    Stack result = Elements;
    Elements.clear();

    return result;
}


bool BinaryTree::erase(T item){
    if (this->contains(item)) {
        root = erase_(item, root);
        size--;

        return true;
    }

    return false;
}


void BinaryTree::destroy_tree_(Node* node) {
    if(node != nullptr){
        destroy_tree_(node->left);
        destroy_tree_(node->right);
        delete node;
    }
}


void BinaryTree::add_(T item, Node* node){
    if(item < node->data){
        if(node->left != nullptr) add_(item, node->left);
        else{
            node->left = new Node;
            node->left->data = item;
            node->left->left = nullptr;
            node->left->right = nullptr;
        }
    }
    else if(item >= node->data){
        if(node->right != nullptr) add_(item, node->right);
        else{
            node->right = new Node;
            node->right->data = item;
            node->right->left = nullptr;
            node->right->right = nullptr;
        }
    }
}


void BinaryTree::f_round_(Node* node){
    if(node != nullptr){
        f_round_(node->left);
        strcat (f_round_str, node->data.string);
        f_round_(node->right);
    }
}


int BinaryTree::get_height_(const Node *node) {
    if (node == nullptr) return 0;

    int lHeight = get_height_(node->left);
    int rHeight = get_height_(node->right);

    if(lHeight > rHeight) return (lHeight + 1);
    else return (rHeight + 1);
}

void BinaryTree::elements_(Node* node){
    if(node != nullptr){
        elements_(node->left);
        Elements.push(node->data);
        elements_(node->right);
    }
}

int BinaryTree::do_question(Node* node) {
    char answer = 0;
    if (node->question) {
        printf("Is the object %s?\n Press y (yes) or n (no)\n", node->data.string);
        if (!scanf("%c", &answer)) return INVALID_ANSWER;

        if (answer == 'y') return do_question(node->right);
        else if (answer == 'n') return do_question(node->left);
        else return INVALID_ANSWER;
    }
    printf("Is it %s?\n Press y (yes) or n (no)\n", node->data.string);
    if (!scanf("%c", &answer)) return INVALID_ANSWER;

    if      (answer == 'y') printf("Haha! I won the game! It was so easy!\n");
    else if (answer == 'n') return Add_new_object(node);
    else                    return INVALID_ANSWER;

    return ALL_OK;
}

int BinaryTree::Add_new_object (Node* node) {
    printf("I'm so sorry, I don't know what did you conceive.\n Let me know, what object are you talking about?\n");

    char* new_object = new char[LIMITED_SIZE_OF_STRING];
    if (!scanf("%s", new_object)) return INVALID_ANSWER;
    node->right = new Node;
    node->right->data.string = new_object;

    node->left = new Node;
    node->left->data = node->data;

    printf("Which fact does distinguish your object?\n");
    if (!scanf("%s", node->data.string)) return INVALID_ANSWER;
    node->question = true;

    printf("Thank you for game! See you later!\n");
    size++;

    return ALL_OK;
}