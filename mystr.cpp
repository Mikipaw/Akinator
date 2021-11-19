//
// Created by mikhalinho on 17.11.2021.
//

#include "mystr.h"

char* text_from_file(FILE* file_name, size_t size_of_file, size_t* number_of_lines){
    char* result_string = (char*) calloc(size_of_file + 5, sizeof(char));
    fread(result_string, sizeof(char), size_of_file + 5, file_name);

    for(int i = 0; i < size_of_file; ++i){
        if(result_string[i] == '\n'){
            result_string[i - 1] = '\n';
            result_string[i]     = '\0';
            (*number_of_lines)++;
        }
    }
    return result_string;
}

size_t Size_of_file(FILE* name_of_file) {
    fseek(name_of_file, 0, SEEK_END);
    size_t size_of_file = ftell(name_of_file);
    fseek(name_of_file, 0, SEEK_SET);

    return size_of_file;
}

