#ifndef CTEST_H
#define CTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

REQUIREMENTS
Simple requirements for first release

1. Test needs to be runable try enum for progress: FAILED, RUNNING, PASSED
2. Test needs red/green output on terminal Linux/MacOS only
3. Test needs assert statements - timeout settings for safety
4. Appropriate error handling for failed tests
5. Flag system to indicate test - all tests are added to a queue to be run sequentially

*/

// Test status
typedef enum {
    IDLE,       // 0 status code
    RUNNING,    // 1 status code
    PASSED,     // 2 status code
    FAILED      // 3 status code
} Status;

// Test object structure
typedef struct {
    char* id;           // ID for test
    char* description;  // User provided description
    Status testStatus;  // Status for pass/fail 0 - 3
    char* statusMessage; // Message to display on error
} Test;

// Main Test
typedef struct {
    Test tests[20];
    int elements;
} CTest;

// Initialisation functions

CTest* testSetup() {
    CTest *test = malloc(sizeof(CTest));
    test->elements = 0;
    return test;
}

Test* testInit(const char* description) {
    Test* test = malloc(sizeof(Test));
    if (!test) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    test->id = strdup("CTEST_UNIT"); 
    test->testStatus = IDLE;

    test->description = strdup(description); 
    test->statusMessage = strdup("");        

    return test;
}

// Assert equal A == B
void assertEqual(CTest* test, int a, int b) {
    // Perform out of bounds check
    if (test->elements >= 20) return;

    // Create test object
    char description[] = "TEST";
    Test *newTest = testInit(description);
    // Check value
    if (a == b) newTest->testStatus = PASSED;
    else newTest->testStatus = FAILED;

    // Add test to main test 
    test->tests[test->elements] = (*newTest);
    test->elements++;
}

// Check status
void checkStatus(Test* test) {
    if (test->testStatus == 2) {
        printf("\033[0;32m"); // green
        printf("PASSED\n");
        printf("\033[0m");
    } else if (test->testStatus == 3) {
        printf("\033[0;31m"); // red
        printf("FAILED\n");
        printf("\033[0m");
    } else {
        printf("IDLE\n");   // default
    }
}

// Test info display DEBUG function
void displayInfo(Test* test) {
    printf("Test ID:\t%s\nDescription:\t%s\nTest Status:\t%u\n", test->id, test->description, test->testStatus);
    checkStatus(test);
}

void displayTests(CTest* test) {
    printf("\nCURRENT TESTS %d\n\n", test->elements);
    for (int i = 0; i < test->elements; i++) {
        displayInfo(&test->tests[i]);
        printf("\n");
    }
}

// Free memory
void freeTest(CTest* test) {
    for (int i = 0; i < test->elements; i++) {
        free(test->tests[i].description);
    }

    free(test);
}

#endif