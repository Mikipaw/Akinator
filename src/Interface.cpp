//
// Created by mikhalinho on 02.12.2021.
//

#include "Interface.h"

int Interface() {

    const char* input = "database.txt";
    Akinator akinator = Akinator(input);

    printf("Firstly, enter your name!\n");
    const char* name = Get_name();

    Intro(name);

    char answer = 0;
    char* object = nullptr;

    const char* first  = nullptr;
    const char* second = nullptr;

    while (answer != 'e') {
        speak("What do you want?");
        puts(R"(
        s - start the game
        d - get the definition of the object
        t - watch the picture of database
        c - compare 2 objects
        e - save and exit)");

        scanf("\n%c", &answer);

        switch (answer) {
            case 's':
                akinator.start();
                break;

            case 'e':
                break;

            case 't':
                akinator.Show_database();
                break;

            case 'c':
                printf("Please, enter first object name:\n");
                first = Get_name();

                printf("Please, enter second object name:\n");
                second = Get_name();

                akinator.Compare(first, second);
                break;

            case 'd':
                speak("Please, enter the name");
                object = (char*) Get_name();
                akinator.definition(object);
                break;

            default:
                speak("Invalid input! Please try again!");
        }
    }

    //akinator.start();
    //akinator.Dump();
    //return akinator.start();
    //akinator.definition("Den");

    return ALL_OK;
}

int Intro(const char* name) {
    char speech[TEMP_BUFFER_SIZE];
    const int ESPEAK_SIZE = 7;

    sprintf(speech, "espeak Hello, %s, and welcome to the Akinator game!\n"
                    "My name is Oracle and I am the smartest intellect in world ever!\n", name);

    printf("%s\n", speech + ESPEAK_SIZE);

    replace_spaces(speech);
    system(speech);

    return ALL_OK;
}

//TODO:change it
const char* Get_name() {
    char* name = (char*) calloc(LIMITED_SIZE_OF_STRING, sizeof(char));
    assert(name != nullptr);
    scanf("%s", name);

    return name;
}