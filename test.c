#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"
#include <time.h>

void test1(CTest *test) {
    int sum = (5 + 5) * 2;
    assertEqual(test, sum, 20, "Check if sum is equal to 20");
}

void test2(CTest *test) {
    assertEqual(test, 10, 10, "Check A == B");
}

void test3(CTest *test) {
    assertEqual(test, 41, 400, "Obvious easy test");
}

int main() {
    CTest *test = testSetup();
    test1(test);
    test2(test);
    test3(test);
    run(test);
}