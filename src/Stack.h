//
// Created by mikhalinho on 13.11.2021.
//

#ifndef AKINATOR_STACK_H
#define AKINATOR_STACK_H

#include <cassert>
#include <cstdio>
#include <stdexcept>
#include <cmath>


#define STACK_CONSTRUCT(stack, capacity, type) Stack<type> stack(5, #stack);
#define NAME(var) #var

const long long STRANGE_NUMBER = 0xDEADBEEF;
const size_t LIMITED_SIZE_OF_STRING = 31;

struct simple_string{
    simple_string() = default;
    explicit simple_string(size_t capacity) {
        string = new char[capacity];
    }

    explicit simple_string(const char* word) {
        string = strcpy(string, word);
    }

    char* string = new char[LIMITED_SIZE_OF_STRING];
    size_t size = 0;
};

enum ERRORS{
    SUCCESS,                            //0
    INVALID_POINTER,                    //1
    INVALID_SIZE,                       //2
    CANARY_SCREAM,                      //3
    UNAVAILABLE_ELEMENTS_WAS_CHANGED,   //4
    UNACCEPTABLE_HASH,                  //5
    UNKNOWN_ERROR,                      //6
};

/*!@function charsum(const char* string)
 * @brief This function finds sum of chars of the string
 * @param string
 * @return an integer - sum of chars
 */
inline int charsum(const char* string);


/*! \class Stack
 *  \brief This is a stack of memory for storage various elements.
 *  \param data - pointer to block of memory with elements.
 *  \param size - number of elements in Stack.
 *  \param capacity - number of maximum elements can be located in current block of memory.
 *  Some details about the Stack class.
 */
class Stack{
private:
    const long long canary1 = STRANGE_NUMBER;

public:
    Stack() = default;

    explicit
    Stack(size_t new_capacity):
            capacity (new_capacity),
            size     (0),
            data     (new simple_string[new_capacity]) {
        fill();
    }

    explicit
    Stack(size_t new_capacity, const char* new_name):
            capacity (new_capacity),
            size     (0),
            data     (new simple_string[new_capacity]),
            name     (new_name) {
        fill();
    }


    int
    inline StackError(int error_number);

    /*!
    *  @method bool push(const char*& item).
    *  @brief  Adds element in the end of the stack.
    *  It expands the Stack by one.
    *
    *  @return a bool - true if operation was successful, false - if not
    */
    inline bool
    push(simple_string item);

    inline void
    copy(const Stack& stk);


    /*!
     *  @method bool pop(T* element).
     *  @brief  Removes last element.
     *  @param element - char**
     *  It shrinks the Stack by one. Deleted item are in element after.
     *
     *  @return a bool - true if success, false if not
     */
    inline bool
    pop(simple_string* element);

    bool
    pop();


    /*!
     *  @method void clear().
     *  @brief  Clearing data.
     *  @return nothing.
     */
    inline void clear();

    [[nodiscard]]
    inline simple_string&
    at(int index) const;

    /*!
     *  @method void Destruct().
     *  @brief  Destroys the class.
     *
     *  @return nothing
     */
    inline void
    Destruct();

    ~Stack() {
        size = -1;
        capacity = -1;
        //free(data);
        //*data = 13;
    }


    [[nodiscard]] inline size_t          Get_Size()      const;
    [[nodiscard]] inline size_t          Get_Capacity()  const;
    [[nodiscard]] inline simple_string*  Get_Data()      const;
    [[nodiscard]] inline const char*     Get_Name()      const;

private:

/*!
    *  @method void fill(size_t new_capacity).
    *  @brief  This method fills Stack after constructor call.
    *  @param new_capacity a size_t.
    *
    *  @return nothing
    */
    inline
    void fill();

    /*!
    *  @brief  Access to the data contained in the Stack.
    *  @param index The index of the element for which data should be
    *  accessed.
    *  @return  Reference to data.
    */
    inline
    simple_string&
    operator[](size_t index);

    /*!
    *  @method void Expand(bool* success).
    *  @brief  This method expands block of memory.
    *  @param success a bool* - true if all is ok, false if expand was unsuccessful.
    *
    *  @return nothing
    */
    inline void
    Expand(bool* success);

    /*!
    *  @method void Decrease().
    *  @brief  This method decreases block of memory.
    *
    *  @return nothing
    */
    inline void
    Decrease();

    /*!
    *  @method bool Stack_OK().
    *  @brief  This method checks if stack is OK.
    *
    *  @return bool - true if stack is ok, false if it is not ok.
    */
    inline bool
    Stack_OK();



private:
    simple_string* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    const char* name = "Nameless stack";
    size_t HASH = 0;

    const long long canary2 = STRANGE_NUMBER;
};

/*!
 * @function str_equal(const char* str1, const char* str2)
 * @brief Function checks if 2 strings are equal
 * @param str1 - const char*
 * @param str2 - const char*
 * @return true if strings are equal, false if not
 */
inline
int str_equal(const char* str1, const char* str2);

/*!
 * @function str_cmp(const char* str1, const char* str2)
 * @brief Function compares 2 strings
 * @param str1 - const char*
 * @param str2 - const char*
 * @return -1 if <, 0 if ==, 1 if >.
 */
inline
int str_cmp (const char* str1, const char* str2);

inline
void Stack_info(const Stack& stack);

inline
void Stack_info(const Stack& stack, FILE* log_file);


inline
void Stack::Destruct(){
    this->Stack_OK();
    free(data);
    size = -1;
    capacity = -1;
}

inline
bool Stack::pop(simple_string* element){
    if(!this->Stack_OK()) return false;

    if(size == 0) {
        fprintf(stderr, "Logic error at line %d:\n"
                        "It is impossible to delete an element from empty stack\n", __LINE__);
        return false;
    }


    if(size - 1 < capacity/4 && capacity > 16) Decrease();
    size--;

    *element = data[size];

    data[size].string = nullptr;

    this->Stack_OK();
    return true;
}

inline
bool Stack::pop(){
    if(!this->Stack_OK()) return false;

    if(size == 0) {
        fprintf(stderr, "Logic error at line %d:\n"
                        "It is impossible to delete an element from empty stack\n", __LINE__);
        return false;
    }

    if(size - 1 < capacity/4 && capacity > 16) Decrease();
    size--;

    data[size].string = nullptr;
    this->Stack_OK();
    return true;
}


inline
bool Stack::push(simple_string item){
    if(!this->Stack_OK()) return false;

    bool push_success = true;

    if (size == capacity)
        Expand(&push_success);
    if(!push_success)
        return push_success;

    data[size++] = item;
    this->Stack_OK();
    return push_success;
}

inline
int Stack::StackError(int error_number){
    FILE* Log_file = fopen("Logs.txt", "wb");
    switch (error_number) {
        case 1:
            fprintf(Log_file, "Invalid pointer!\n");
            break;

        case 2:
            fprintf(Log_file, "Invalid size!\n");
            break;

        case 3:
            fprintf(Log_file, "Canary was hit!\nCanary1 = %lld\nCanary2 = %lld\n", canary1, canary2);
            break;

        case 4:
            fprintf(Log_file, "Unavailable elements was changed!\n");
            break;

        case 5:
            fprintf(Log_file, "Unacceptable hash!\n");
            break;


        default:
            fprintf(Log_file, "Unknown error!\n");
            Stack_info(*this, Log_file);
            Stack_info(*this);
            Destruct();
            return error_number;
    }
    fprintf(Log_file, "\n");
    Stack_info(*this, Log_file);
    Stack_info(*this);
    fclose(Log_file);
    return 1;
}


inline
simple_string& Stack::operator[](size_t index){
    if(index < 0 || index >= size) {
        fprintf(stderr, "Out of range error at line %d:\n"
                        "Index %ld is out of range!\n", __LINE__, index);
        simple_string result;

        return result;
    }

    return data[index];
}

inline
void Stack::Expand(bool* success) {
    (capacity*=2)++;
    data = (simple_string*) realloc(data, capacity*sizeof(simple_string));
    if (data == nullptr) *success = false;

}

inline
void Stack::Decrease() {
    capacity/=2;
    data = (simple_string*) realloc(data, capacity*sizeof(simple_string));
}

inline
bool Stack::Stack_OK() {

    if(this == nullptr) {   //NULL POINTER
        StackError(INVALID_POINTER);
        return false;
    }

    if(size > capacity) {   // BAD SIZE
        StackError(INVALID_SIZE);
        return false;
    }

    if(this->data == nullptr) { //NULL POINTER
        StackError(INVALID_POINTER);
        return false;
    }

    if(canary1 != STRANGE_NUMBER || canary2 != STRANGE_NUMBER) { //CANARY WAS HIT
        StackError(CANARY_SCREAM);
        return false;
    }

    for (int i = size; i < capacity; ++i) {
        if(str_equal(data[i].string, nullptr)) break;
        StackError(UNAVAILABLE_ELEMENTS_WAS_CHANGED);
        return false;
    }

    return true;
}

inline
size_t Stack::Get_Size() const { return size; }

inline
size_t Stack::Get_Capacity() const { return capacity; }

inline
simple_string* Stack::Get_Data() const { return data; }

inline
const char* Stack::Get_Name() const { return name; }

inline
simple_string& Stack::at(int index) const {
    return *(data + index);
}

inline
void Stack::fill(){
    for (int i = 0; i < capacity; ++i) {
        data[i].string = nullptr;
        //data[i].size = 0;
    }
}

inline
void Stack_info(const Stack& stack){
    printf("Stack = [%p], \"%s\"\n", &stack, stack.Get_Name());
    printf("{\n");
    printf("\tsize = %ld\n",     stack.Get_Size());
    printf("\tcapacity = %ld\n", stack.Get_Capacity());
    printf("\tdata [%p]\n",      stack.Get_Data());
    printf("\t{\n");

    for(int i = 0; i < stack.Get_Capacity(); ++i){
        printf("\t\t[%d] = ", i);
        //printf("%s, size = %ld\n",stack.at(i).string, stack.at(i).size);
    }
    printf("\t}\n");
}

inline
void Stack_info(const Stack& stack, FILE* log_file){
    fprintf(log_file, "Stack = [%p], \"%s\"\n", &stack, stack.Get_Name());
    fprintf(log_file, "{\n");
    fprintf(log_file, "\tsize = %ld\n",     stack.Get_Size());
    fprintf(log_file, "\tcapacity = %ld\n", stack.Get_Capacity());
    fprintf(log_file, "\tdata [%p]\n",      stack.Get_Data());
    fprintf(log_file, "\t{\n");

    for(int i = 0; i < stack.Get_Capacity(); ++i){
        fprintf(log_file, "\t\t[%d] = ", i);
        //fprintf(log_file, "%s, size = %ld\n", stack.at(i).string, stack.at(i).size);
    }
    fprintf(log_file, "\t}\n");
}

inline void Stack::clear() {
    while (size != 0) pop();
}

inline int str_cmp (const char* str1, const char* str2) {
    if (str1 == nullptr || str2 == nullptr) return 0;
    int i = 0, j = 0;
    while(true){
        while(!(isalpha(str1[i]) || str1[i] == '\0')) i++;
        while(!(isalpha(str2[j]) || str2[j] == '\0')) j++;

        if (str1[i] == '\0' &&
            str2[j] == '\0')
            return 0;

        if (str1[i] == str2[j]){
            i++;
            j++;
        }

        else
            return str1[i] - str2[j];
    }
}

inline bool operator==(const simple_string& ss1, const simple_string& ss2) {
    if (!str_cmp(ss1.string, ss2.string)) return true;
    else return false;
}


inline bool operator>(const simple_string& ss1, const simple_string& ss2) {
    return str_cmp(ss1.string, ss2.string) > 0;
}

inline bool operator>=(const simple_string& ss1, const simple_string& ss2) {
    return str_cmp(ss1.string, ss2.string) >= 0;
}

inline bool operator<(const simple_string& ss1, const simple_string& ss2) {
    return str_cmp(ss1.string, ss2.string) < 0;
}

inline bool operator<=(const simple_string& ss1, const simple_string& ss2) {
    return str_cmp(ss1.string, ss2.string) <= 0;
}

inline int str_equal(const char* str1, const char* str2){
    int i = 0;
    if (str1 == nullptr && str2 == nullptr) return true;
    if (str1 == nullptr || str2 == nullptr) return false;

    while(true){
        if ((str1[i] == '\n' || str1[i] == '\0') && (str2[i] == '\n' || str2[i] == '\0')) return true;
        if(str1[i] == str2[i]){
            ++i;
            continue;
        }
        return false;
    }
}

inline int Arrange_str_ptrs(simple_string* pointers, size_t number_of_lines, char* text) {
    assert(pointers != nullptr);
    assert(text != nullptr);
    int number_of_empty_lines = 0;
    pointers[0].string = text;
    for (int i = 1; i < number_of_lines; ++i) {
        text = strchr(text, '\0');
        text++;
        pointers[i].string = text;
        pointers[i - 1].size = (int) (pointers[i].string - pointers[i - 1].string);
    }

    return number_of_empty_lines;
}

inline void
Stack::copy(const Stack& stk) {
    size_t size1 = stk.Get_Size();

    for (int i = 0; i < size1; ++i) push(stk.at(i));
}

//TODO:compare 2 obj

#endif //AKINATOR_STACK_H
