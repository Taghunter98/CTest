#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"

int main() {
    CTest *test = testSetup();
    assertEqual(test, 5, 5);
    assertEqual(test, 2, 5);
    displayTests(test);
    freeTest(test);
}