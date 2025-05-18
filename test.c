#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"
#include <time.h>

void test1() {
    CTest *test = testSetup();
    int sum = (5 + 5) * 2;
    assertEqual(test, sum, 20, "Check if sum is equal to 20");
    assertEqual(test, 10, 10, "Check A == B");
    run(test);
}

int main() {
    test1();
}