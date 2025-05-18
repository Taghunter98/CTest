#ifndef CTEST_H
#define CTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*

REQUIREMENTS
Simple requirements for first release

1. Test needs to be runable try enum for progress: FAILED, RUNNING, PASSED                  DONE
2. Test needs red/green output on terminal Linux/MacOS only                                 DONE
3. Test needs assert statements - timeout settings for safety                               TODO
4. Appropriate error handling for failed tests                                              TODO
5. Flag system to indicate test - all tests are added to a queue to be run sequentially     TODO
6. Add skipped functionality                                                                TODO

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
    double timeTaken;   // Runtime of test
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
    Test* test = malloc(sizeof(Test));          // Allocate memory for test size
    if (!test) {                       
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    test->id = strdup("CTEST_UNIT");            // Hardcoded ID for tests - may be useful later
    test->testStatus = IDLE;                    // Test is in IDLE state, not running

    test->description = strdup(description);    // Description - "Test if A is not equal to B" 
    test->statusMessage = strdup("");           // Status message - "A != B"
    test->timeTaken = 0.0;                      // Measure of time taken on execution

    return test;
}

/*

Assertions

*/

void assertEqual(CTest* test, int a, int b, char* description) {
    if (test->elements >= 20) return;   // Out of bounds check

    // Create test object
    Test *newTest = testInit(description);

    // Start timer before code runtime
    clock_t start;      
    clock_t end;        
    double runtime;     // Test runtime 
    start = clock();    // Record the start time

    // Check value
    if (a == b) {
        newTest->testStatus = PASSED;
        asprintf(&(newTest->statusMessage), "%d = %d", a, b);
    } else {
        newTest->testStatus = FAILED;
        asprintf(&(newTest->statusMessage), "%d != %d", a, b);
    }

    // End timer and record time
    end = clock();
    runtime = ((double) (end - start)) / CLOCKS_PER_SEC;
    newTest->timeTaken = runtime;

    // Add test to main test 
    test->tests[test->elements] = (*newTest);
    test->elements++;
}

// Check status
void checkStatus(Test* test) {
    if (test->testStatus == 2) {
        printf("\033[0;32m"); // green
        printf("PASS");
        printf("\033[0m");
    } else if (test->testStatus == 3) {
        printf("\033[0;31m"); // red
        printf("FAIL");
        printf("\033[0m");
    } else {
        printf("IDLE");   // default
    }
}

// Display tests
void testResult(Test* test) {
    checkStatus(test);
    // 40 is the width for the description field, adjust as needed
    printf("\t%-50s (%fs)", test->description, test->timeTaken);
}

void displayTests(CTest* test) {
    int failures;
    double totalTime;

    // Grab total runtime of tests
    for (int i = 0; i < test->elements; i++) totalTime += test->tests[i].timeTaken;

    printf("\n======================================================================\n");
    printf("Ran %d tests in %.3f seconds\n", test->elements, totalTime);
    printf("======================================================================\n\n");

    for (int i = 0; i < test->elements; i++) {
        testResult(&test->tests[i]);
        printf("\n\n");
        if (test->tests[i].testStatus == 3) failures++;
    }
    printf("\n----------------------------------------------------------------------\n");
    if (failures > 0) {
        printf("\033[0;31m"); // red
        printf("TEST FAILED\n\n");
        printf("\033[0m");
    } else  {
        printf("\033[0;32m"); // green
        printf("TEST PASSED\n\n");
        printf("\033[0m");
    }
}

// Free memory
void freeTest(CTest* test) {
    for (int i = 0; i < test->elements; i++) {
        free(test->tests[i].description);
        free(test->tests[i].statusMessage);
    }

    free(test);
}

// Run tests
void run(CTest* test) {
    displayTests(test);
    freeTest(test);
}

#endif