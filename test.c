#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"
#include <time.h>

void test1() {
    CTest *test = testSetup();
    int sum = (5 + 5) * 2;
    assertEqual(test, sum, 20, "Check if sum is equal to 20");
    assertEqual(test, 5, 10, "Check A == B");
    assertEqual(test, 400, 400, "Obvious easy test");
    run(test);
}

int main() {
    test1();
}