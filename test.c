#include <stdio.h>
#include <stdlib.h>
#include "CTest.h"
#include <stdbool.h>

void test1(CTest *test) {
    int sum = (5 + 5) * 2;
    assertEqual(test, sum, 20, "Check if sum is equal to 20", false);
}

void test2(CTest *test) {
    bool value = true;
    assertTrue(test, value, "Check A is true", false);
}

void test3(CTest *test) {
    bool value = true;
    assertFalse(test, value, "Check A is false", true);
}

void test4(CTest *test) {
    int sum = 2 * 200;
    assertNotNull(test, &sum, "Check if sum is not null", true);
}

void test5(CTest *test) {
    bool val = 1 != 0;
    assertTrue(test, val, "Check if val is true", false);
}

int main() {
    CTest *test = createCTest();

    test1(test);
    test2(test);
    test3(test);
    test4(test);
    test5(test);

    run(test);
}