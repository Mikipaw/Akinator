/*!
 * @mainpage
 *  @brief     Akinator
 *  @author    Michael Pavlov
 *  @author    Mikhail Pavlov
 *  @version   C++23
 *  @date      11.2021
 *  @pre       First initialize the system.
 *  @bug       No
 *  @warning   Be careful! Limited size of string is 31 chars on default.
 *  @copyright GNU Public License.
 */

#include "Akinator.h"

int main() {
    const char* input = "database.txt";
    Akinator akinator = Akinator(input);
    akinator.start();
    akinator.Dump();
    return akinator.start();
    //akinator.definition("Dimas");

    return 0;
}
