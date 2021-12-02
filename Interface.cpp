//
// Created by mikhalinho on 02.12.2021.
//

#include "Interface.h"

int Interface() {

    const char* input = "database.txt";
    Akinator akinator = Akinator(input);

    const char* name = Get_name();

    Intro(name);

    char answer = 0;
    char* object = (char*) calloc(LIMITED_SIZE_OF_STRING, sizeof(char));

    while (answer != 'e') {
        speak("What do you want?");
        puts(R"(
        s - start the game
        d - get the definition of the object
        e - exit)");

        scanf("\n%c", &answer);

        switch (answer) {
            case 's':
                akinator.start();
                break;

            case 'e':
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
    char speech[1000];

    sprintf(speech, "espeak Hello, %s, and welcome to the Akinator game!\n"
                    "My name is Oracle and I am the smartest intellect in world ever!\n", name);

    printf("%s\n", speech + 7);

    replace_spaces(speech);
    system(speech);

    return ALL_OK;
}

const char* Get_name() {
    char* name = (char*) calloc(LIMITED_SIZE_OF_STRING, sizeof(char));
    printf("Firstly, enter your name!\n");
    scanf("%s", name);

    return name;
}