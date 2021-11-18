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

/*
char* BinaryTree::f_round() {
    f_round_(root);
    char* result = f_round_str;
    f_round_str = nullptr;

    return result;
}
*/

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
    if(node != nullptr) {
        if (node->question) strcat (f_round_str, "?");
        strcat (f_round_str, node->data.string);
        strcat (f_round_str, ".");

        f_round_(node->left);
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
        if (!scanf("%c\n", &answer)) return INVALID_ANSWER;

        if (answer == 'y') return do_question(node->left);
        else if (answer == 'n') return do_question(node->right);
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

    size_t _size = LIMITED_SIZE_OF_STRING;
    char* new_object = new char[LIMITED_SIZE_OF_STRING];
    getline(&freebuf, &_size, stdin);
    if (!getline(&new_object, &_size, stdin)) return INVALID_ANSWER;
    node->right = new Node;
    node->right->data.string = new_object;
    node->right->data.string[LIMITED_SIZE_OF_STRING - 2] = '\n';
    node->right->data.string[LIMITED_SIZE_OF_STRING - 3] = '.';

    node->left = new Node;
    node->left->data = node->data;

    node->data.string = new char[LIMITED_SIZE_OF_STRING];
    printf("Which fact does distinguish your object?\n");
    if (!getline(&node->data.string, &_size, stdin)) return INVALID_ANSWER;
    node->data.string[LIMITED_SIZE_OF_STRING - 2] = '\n';
    node->data.string[LIMITED_SIZE_OF_STRING - 3] = '.';
    node->question = true;

    printf("Thank you for game! See you later!\n");
    size += 2;

    return ALL_OK;
}

BinaryTree::BinaryTree() {
    root = new Node;
    root->data.string = new char[LIMITED_SIZE_OF_STRING];
    root->data.string = (char*) "Nobody\n";
    root->data.size = strlen("Nobody\n");
    f_round_str = nullptr;
}

BinaryTree::BinaryTree(const char* input) {
    root = new Node;
    FILE* database = fopen(input, "rb");
    size_t size_of_file = Size_of_file(database);
    size_t number_of_lines = 0;
    text = text_from_file(database, size_of_file, &number_of_lines);
    //auto pointers = (simple_string *) calloc(number_of_lines + 1, sizeof(simple_string));
    //Arrange_str_ptrs(pointers, number_of_lines, text);
    Read_in_tree(&number_of_lines, root);

    fclose(database);
}

Node* BinaryTree::erase_(T item, Node* node) {
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

void BinaryTree::destroy_tree() {
    f_round_str = (char*) calloc(size + 1, sizeof(LIMITED_SIZE_OF_STRING));
    f_round_(root);

    FILE* output = fopen("database.txt", "wb");
    fputs(f_round_str, output);

    //TODO:node->right read function
    fclose(output);
    destroy_tree_(root);
}

char* get_line(char* buffer, int max_size) {
    fgets(buffer, max_size, stdin);

    size_t new_size = strlen(buffer);
    char* result = new char[new_size + 1];
    strcpy(result, buffer);
    result[new_size - 1] = '\0';

    return result;
}

void BinaryTree::add_from_file (Node* node, simple_string* pointers, size_t* limit) {
    if (index >= *limit) return;

    node->data = pointers[index + 1];
    if (pointers[index].string[0] == '?') node->question = true;

    node->left = new Node;
    add_from_file(node->left, pointers, limit);

    node->right = new Node;
    add_from_file(node->right, pointers, limit);
}

void BinaryTree::Read_in_tree(size_t* number_of_lines, Node* node) {
    assert(text != nullptr);

    if (*number_of_lines <= 0) return;
    (*number_of_lines)--;

    if (text[0] == '?') {
        node->question = true;
        text++;
    }

    node->data.string = text;
    if (!node->question) return;

    node->left = new Node;
    text = strchar(text, '\0');
    if (text == nullptr) fprintf(stderr, "Houya!\n");
    text++;
    //node->left->data.string = text;
    //node->data.size = (int) (node->left->data.string - node->data.string);

    Read_in_tree(number_of_lines, node->left);

    node->right = new Node;
    text = strchar(text, '\0');
    text++;
    //node->right->data.string = text;
    //node->data.size = (int) (node->left->data.string - node->data.string);
    Read_in_tree(number_of_lines, node->right);

}

char* strchar(char* buffer, char sym) {
    char* c = buffer;
    while (*c != sym) {
        c++;
        if (c == nullptr || *c == '\0') return c;
    }

    return c;
}