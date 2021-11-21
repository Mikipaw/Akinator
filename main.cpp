#include "Akinator.h"

int main() {
    const char* input = "database.txt";
    Akinator bt = Akinator(input);
    //bt.start();
    bt.Dump();

    return 0;
}
