#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"

int main() {
    char description[] = "TEST";
    Test *test = setup(description);
    displayInfo(test);
    assertEqual(test, 5, 5);
    displayInfo(test);
    freeTest(test);
}