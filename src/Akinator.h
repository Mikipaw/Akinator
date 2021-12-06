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
inline const char* DATABASE_TREE    = "Database_tree.jpg";
inline const char* DOT              = R"(dot Graph.dot -Tjpg -o )";
inline const char* UDOT             = R"(dot UserGraph.dot -Tjpg -o )";


inline const char* GOLD = "gold";
inline const char* LIME = "lime";

inline const int RESERVE_MEM = 10;
inline const int ESPEAK_SIZE = 7;


/*!
 * @struct Node
 * @brief classical node of binary tree with bool param
 * @param data - data
 * @param left - pointer to the left childnode
 * @param right - pointer to the right childnode
 * @param question - question (true) or object (false)
 */
struct Node {
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    bool question = false;
};


/*!
 * @function strchar(char* buffer, char sym)
 * @brief Function finds the first symbol 'sym' in string 'buffer' and returns pointer to it (or nullptr if wasn't found)
 * @param buffer - char* (source string)
 * @param sym - char (symbol user wants to find)
 * @return char* - pointer to the first symbol 'sym' in 'buffer'
 */
char* strchar(char* buffer, char sym);


/*!
 * @class Akinator
 * @brief classical Akinator game with database contains English words no longer then 31 symbol.
 * @param size          - number of elements in database.
 * @param Elements      - stack which helps to show the objects features.
 * @param root          - pointer to the root of binary tree (first question in the game).
 * @param f_round_str   - string needs to tree traversal.
 * @param freebuf       - string needs to save in strings for short time.
 * @param text          - string needs to save the text from file in buffer.
 */
class Akinator {

public:

    //!Classical constructor
    Akinator();

    //!The constructor creates the tree using the text file database.
    explicit Akinator(const char* input);

    //!Classical destructor
    ~Akinator() { destroy_tree(); }

    /*!
     * @method search(T item)
     * @brief This method searches object 'item' in binary tree.
     * @param item - object user wants to find.
     * @return Node* - pointer to the node contains 'item' or nullptr if 'item' doesn't exist in tree.
     */
    Node*
    search(T item) { return search_(item, root); }


    /*!
     * @method destroy_tree()
     * @brief This method destroys the binary tree.
     * @return Nothing.
     */
    void
    destroy_tree();

    /*!
     * @method contains(T item)
     * @brief The method answers the question if the tree contains 'item'.
     * @param item - object user wants to find.
     * @return true (if 'item' in tree) or false (in other cases)
     */
    bool
    contains(T item);

    /*!
     * @method get_height()
     * @brief function recursively finds the height of tree (radius of graph).
     * @return int - height of tree.
     */
    [[nodiscard]] int
    get_height() const { return get_height_(root); }

    [[nodiscard]] int
    get_size() const { return size; }

    bool
    is_empty() { return !root; }

    /*!
     * @method elements()
     * @brief returns all elements of tree.
     * @warning function wasn't tested in new version of Akinator tree. Don't use it before it will be fixed.
     * @return Stack with elements of binary tree.
     */
    Stack
    elements();

    /*!
     * @method erase (T item)
     * @brief Finds the object 'item' in tree and deletes it.
     * @warning function wasn't tested in new version of Akinator tree. Don't use it before it will be fixed.
     * @param item - item user wants to delete from tree.
     * @return true if operation was successful, false if item wasn't found.
     */
    bool
    erase(T item);

    /*!
     * @method Dump()
     * @brief creates the jpg picture of three using 'Graphviz'
     * @warning don't use the function if you don't have Graphviz.
     * @return int - error code
     */
    int
    Dump();

    /*!
     * @method start()
     * @brief Starts the Akinator game.
     * @return int - error code.
     */
    int
    start() { return do_question(root); };

    /*!
     * @method verification()
     * @brief  tests the Akinator. Recommend to use it before starting game.
     * @return error code (0 if all ok).
     */
    int
    verification() const;

    /*!
     * @method definition (const char* object)
     * @brief prints the definition of object in console.
     * @param object - object user wants to know a definition.
     * @return Stack with characteristics of the object.
     */
    Stack
    definition (const char* object);

    /*!
     * @method Show_database()
     * @brief Creates a picture of database for user.
     * @return error code
     */
    int
    Show_database() const;

    /*!
     * @method Compare(const char* lhs, const char* rhs)
     * @param lhs - first object
     * @param rhs - second object
     * @return error code
     */
    int Compare(const char* lhs, const char* rhs);

private:
    int check (Node* node) const;

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

    void _udumpE(Node* node, char* uf_round_str) const;

    void _udumpV(Node* node, char* uf_round_str) const;


    int size = 1;
    Stack Elements = Stack(16);
    Node* root;
    char* f_round_str;
    char* freebuf = new char[LIMITED_SIZE_OF_STRING * 10];
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
}

int speak(const char* string);

#endif //AKINATOR_AKINATOR_H
