//
// Created by mikhalinho on 13.11.2021.
//

#include "Akinator.h"


bool Akinator::contains(T item) {
    Node* result = search_(item, root);

    return result != nullptr;
}


Stack Akinator::elements() {
    elements_(root);
    Stack result = Elements;
    Elements.clear();

    return result;
}


bool Akinator::erase(T item){
    if (this->contains(item)) {
        root = erase_(item, root);
        size--;

        return true;
    }

    return false;
}


void Akinator::destroy_tree_(Node* node) {
    if(node != nullptr){
        destroy_tree_(node->left);
        destroy_tree_(node->right);
        delete node;
    }
}


void Akinator::f_round_(Node* node){
    if(node != nullptr) {
        if (node->question) node->data.string[0] = '?';

        size_t length = strlen(node->data.string);

        node->data.string[length - 1] = '.';
        //node->data.string[length - 2] = '.';

        strcat (f_round_str, node->data.string);
        strcat (f_round_str, "\n");

        f_round_(node->left);
        f_round_(node->right);
    }
}


int Akinator::get_height_(const Node *node) const{
    if (node == nullptr) return 0;

    int lHeight = get_height_(node->left);
    int rHeight = get_height_(node->right);

    if(lHeight > rHeight) return (lHeight + 1);
    else return (rHeight + 1);
}


void Akinator::elements_(Node* node){
    if(node != nullptr){
        elements_(node->left);
        Elements.push(node->data);
        elements_(node->right);
    }
}


int Akinator::do_question(Node* node) {
    char answer = 0;
    if (node->question) {
        sprintf(freebuf, "Is the object %s?\n Press y (yes) or n (no)\n", node->data.string);
        speak(freebuf);
        if (!scanf("\n%c", &answer)) {
            printf("%c\n", answer);
            return INVALID_ANSWER;
        }

        if      (answer == 'y') return do_question(node->left);
        else if (answer == 'n') return do_question(node->right);
        else {
            printf("%c\n", answer);
            return INVALID_ANSWER;
        }
    }

    sprintf(freebuf, "Is it %s?\n Press y (yes) or n (no)\n", node->data.string);
    speak(freebuf);
    if (!scanf("\n%c", &answer)) return INVALID_ANSWER;

    if      (answer == 'y') speak("Haha!!! I won the game! It was so fucking easy!\n");
    else if (answer == 'n') return Add_new_object(node);
    else                    return INVALID_ANSWER;

    return ALL_OK;
}


int Akinator::Add_new_object (Node* node) {
    speak("I'm so sorry, I don't know what did you conceive.\n Let me know, what object are you talking about?\n");

    size_t _size = LIMITED_SIZE_OF_STRING;
    char* new_object = new char[LIMITED_SIZE_OF_STRING];
    getline(&freebuf, &_size, stdin);
    if (!getline(&new_object, &_size, stdin)) return INVALID_ANSWER;
    node->left = new Node;
    node->left->data.string = new_object;

    size_t length = strlen(new_object);
    node->left->data.string[length - 1] = '\n';

    node->right = new Node;
    node->right->data = node->data;

    node->data.string = new char[LIMITED_SIZE_OF_STRING];
    char* temp_str = node->data.string;
    temp_str++;
    speak("Which fact does distinguish your object?\n");
    if (!getline(&temp_str, &_size, stdin)) return INVALID_ANSWER;
    length = strlen(node->data.string);
    node->data.string[length - 1] = '\n';
    node->question = true;

    speak("Thank you for game! See you later!\n");
    size += 2;

    if (verification()) return verification();

    return ALL_OK;
}


Akinator::Akinator() {
    root = new Node;
    root->data.string = new char[LIMITED_SIZE_OF_STRING];
    root->data.string = (char*) "Nobody\n";
    root->data.size = strlen("Nobody\n");
    f_round_str = nullptr;
}


Akinator::Akinator(const char* input) {
    root = new Node;
    FILE* database = fopen(input, "rb");
    size_t size_of_file = Size_of_file(database);
    size_t number_of_lines = 0;
    text = text_from_file(database, size_of_file, &number_of_lines);

    size = (int) number_of_lines;
    Read_in_tree(&number_of_lines, root);

    fclose(database);
}

Node* Akinator::erase_(T item, Node* node) {
    if (node == nullptr) return node;

    return nullptr;
}

void Akinator::destroy_tree() {
    f_round_str = (char*) calloc(size + 5, sizeof(LIMITED_SIZE_OF_STRING));
    f_round_(root);


    FILE* output = fopen("database.txt", "wb");
    fputs(f_round_str, output);

    fclose(output);
    destroy_tree_(root);
}


void Akinator::Read_in_tree(size_t* number_of_lines, Node* node) {
    assert(text != nullptr);

    if (*number_of_lines <= 0) return;
    (*number_of_lines)--;

    if (text[0] == '?') {
        node->question = true;
        text[0] = '\t';
    }

    node->data.string = text;
    if (!node->question) return;

    node->left = new Node;
    text = strchar(text, '\0');
    text++;

    Read_in_tree(number_of_lines, node->left);

    node->right = new Node;
    text = strchar(text, '\0');
    text++;

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

void Akinator::_dumpE (Node* node) const {
    if (node == nullptr) return;

    char* tmp_string = (char*) calloc(15, LIMITED_SIZE_OF_STRING);

    char* color = nullptr;

    if (node->question) color = (char*) GOLD;
    else                color = (char*) LIME;

    sprintf(tmp_string,
            "node%p[ style = \"filled, rounded\", fillcolor = \"%s\"]"
            "node%p [label=\"<f0> name (%s)|<f1> address (%p)|<f2> left (%p)|<f3> right (%p)\"];\n",
            node, color, node, node->data.string, node, node->left, node->right);

    strcat(f_round_str, tmp_string);

    if (node->left  != nullptr) _dumpE(node->left);
    if (node->right != nullptr) _dumpE(node->right);

    free(tmp_string);

}

void Akinator::_dumpV (Node* node) const {
    if (node != nullptr) {
        char* temp_string = (char*) calloc(15, LIMITED_SIZE_OF_STRING);
        if (node->right != nullptr) {
            sprintf(temp_string, "node%p:f3 -> node%p:f0;\n", node, node->right);
            strcat(f_round_str, temp_string);
            _dumpV(node->right);
        }

        if (node->left  != nullptr) {
            sprintf(temp_string, "node%p:f2 -> node%p:f0;\n", node, node->left);
            strcat(f_round_str, temp_string);
            _dumpV(node->left);
        }

        free(temp_string);
    }

}

int Akinator::Dump() {
    if (verification()) return verification();

    FILE* Graph = fopen("Graph.dot", "wb");
    if(Graph == nullptr) fprintf(stderr, "Error opening file!\n");

    f_round_str = (char*) calloc(size, LIMITED_SIZE_OF_STRING * LIMITED_SIZE_OF_STRING);

    const char* DEFAULT_TEXT = "digraph G{\n"
                               "edge [color = \"darkgreen\"];\n"
                               "rankdir = \"LR\";\n"
                               "node [shape = record];\n"
                               "node [color = \"#000000\", shape = record];\n";
    strcat(f_round_str, DEFAULT_TEXT);

    _dumpE(root);
    _dumpV(root);

    fputs(f_round_str, Graph);
    fputs("}\n", Graph);

    fclose(Graph);

    char*  command = (char*) calloc(2, LIMITED_SIZE_OF_STRING);
    strcpy (command, DOT);
    strcat (command, OUTPUT_FILE_NAME);

    system (command);

    char* command2 = (char*) calloc(2, LIMITED_SIZE_OF_STRING);
    strcat(command2, "eog ");
    strcat(command2, OUTPUT_FILE_NAME);
    system (command2);

    free(command);

    //free(f_round_str);
    if (verification()) return verification();

    return ALL_OK;
}

int Akinator::check (Node* node) const{
    if (node == nullptr) return ALL_OK;

    if (node->question) {
        if (node->left == nullptr || node->right == nullptr) {
            fprintf(stderr, "Invalid pointer...\n");
            return INVALID_POINTER;
        }
    }
    else {
        if (node->left != nullptr || node->right != nullptr) {
            fprintf(stderr, "Invalid pointer...\n");
            return INVALID_POINTER;
        }
    }

    int error_code = ALL_OK;
    error_code = check(node->left);
    if (error_code) return error_code;

    error_code = check(node->right);
    if (error_code) return error_code;

    return ALL_OK;
}

Stack Akinator::definition(const char* object) {
    simple_string ss;
    ss.string = (char*) object;

    char* speech = (char*) calloc(size + 1, LIMITED_SIZE_OF_STRING + 10);
    char* word   = (char*) calloc(2, LIMITED_SIZE_OF_STRING);

    strcat(speech, "espeak ");

    Node* result = search(ss);

    if (result != nullptr) {
        strcpy(word, Elements.at(0).string);
        printf("%s is\n1)", object);
        strcat(speech, word);

        for (int i = 1; i < Elements.Get_Size(); ++i) {
            sprintf(word, "%d)%s", i + 1, Elements.at(i).string);
            strcat(speech, word);
        }

        printf("%s", speech + 6);
        printf("\n");
    }
    else {
        speak("Object wasn't found!");
        return elements();
    }

    for (int i = 8; i < strlen(speech); ++i) {
        if (!std::isalpha(speech[i])) speech[i] = '_';
    }

    strcat(speech, " -s 100");

    system(speech);

    free(word);
    free(speech);
    return elements();
};


int speak(const char* string) {
    puts(string);

    char* speech = (char*) calloc(10 + strlen(string), sizeof(char));

    strcpy(speech, "espeak ");
    strcat(speech, string);
    replace_spaces(speech);

    system(speech);

    free(speech);

    return ALL_OK;
}