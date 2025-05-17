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
typedef struct CTest{
    char* id;           // ID for test
    char* description;  // User provided description
    Status testStatus;  // Status for pass/fail 0 - 3
    char* statusMessage; // Message to display on error
} Test;

// Initialisation function
Test* setup(const char* description) {
    Test* test = malloc(sizeof(Test));
    if (!test) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    test->id = "CTEST_UNIT";    // Set test ID
    test->testStatus = IDLE;    // Set to IDLE as default

    // Allocate memory for description, just uses length of string + 1 for null ter
    test->description = malloc(strlen(description) + 1);
    if (!test->description) {
        fprintf(stderr, "Memory allocation failed\n");
        free(test);
        exit(EXIT_FAILURE);
    }
    strcpy(test->description, description); // Copy description     
    return test;
}

// Assert equal A == B
void assertEqual(Test* test, int a, int b) {
    // Check value
    if (a == b) test->testStatus = PASSED;
    else test->testStatus = FAILED;
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

// Free memory
void freeTest(Test* test) {
    if (test) {
        free(test->description);
        free(test);
    }
}

#endif