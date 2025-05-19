#ifndef CTEST_H
#define CTEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/*

REQUIREMENTS
Simple requirements for first release

1. Test needs to be runable try enum for progress: FAILED, RUNNING, PASSED                  DONE
2. Test needs red/green output on terminal Linux/MacOS only                                 DONE
3. Test needs assert statements - timeout settings for safety                               DONE
4. Appropriate error handling for failed tests                                              DONE
5. Flag system to indicate test - all tests are added to a queue to be run sequentially     DONE
6. Add skipped functionality                                                                DONE

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
    char* id;               // ID for test
    char* description;      // User provided description
    Status testStatus;      // Status for pass/fail 0 - 3
    char* statusMessage;    // Message to display on error
    double timeTaken;       // Runtime of test
    clock_t start;          // Start of runtime
    clock_t end;            // End of runtime
    bool skipped;           // Check if test is to be skipped at runtime
} Test;

// Main Test
typedef struct {
    Test tests[50];         // Limit of 50 tests per parent, might change later
    int elements;           // Counter of elements
    double timeTaken;       // Runtime of test
    clock_t start;          // Start of runtime
    clock_t end;            // End of runtime
} CTest;

// Initialisation functions
CTest* testSetup() {
    CTest *test = malloc(sizeof(CTest));
    test->elements = 0;
    test->start = clock();
    test->timeTaken = 0.0;
    return test;
}

Test* testInit(const char* description, bool skip) {
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
    test->skipped = skip;                       // Run or skip test

    return test;
}

// Prints text in green
void printGreen(const char* text) {
    printf("\033[0;32m%s\033[0m", text);
}

// Prints text in red
void printRed(const char* text) {
    printf("\033[0;31m%s\033[0m", text);
}

// Prints text in yellow
void printYellow(const char* text) {
    printf("\033[0;33m%s\033[0m", text);
}

/*

Basic test structure, setup and end test

*/

Test* startTest(CTest* test, const char* description, bool skip) {
    if (test->elements >= 20) return NULL;   // Out of bounds check

    // Create test object
    Test *newTest = testInit(description, skip);

    // Start timer before code runtime
    newTest->start = clock();    // Record the start time
    return newTest;
}

void endTest(CTest* test, Test* curTest) {
    // End timer and record time
    curTest->end = clock();
    curTest->timeTaken = ((double) (curTest->end - curTest->start)) / CLOCKS_PER_SEC;

    // Add test to main test 
    test->tests[test->elements] = (*curTest);
    test->elements++;
}

void checkStatus(Test* test) {
    // Check if skipped 
    if (test->skipped == true) printYellow("SKIP");
    else {
        // Otherwise print status
        if (test->testStatus == 2) printGreen("PASS");
        else if (test->testStatus == 3) printRed("FAIL");
        else printf("IDLE"); 
    }
}

/*

Test display

*/

void testResult(Test* test) {
    // Print test info, check for error
    printf("%-40s %-40s\t", test->description, test->statusMessage);
    checkStatus(test);

}

void displayTests(CTest* test) {
    int failures = 0;
    double totalTime;

    // Grab total runtime of tests
    for (int i = 0; i < test->elements; i++) totalTime += test->tests[i].timeTaken;

    printf("\n"); // padding

    for (int i = 0; i < test->elements; i++) {
        testResult(&test->tests[i]);
        printf("\n");
        if (test->tests[i].skipped == true) continue;
        else if (test->tests[i].testStatus == 3) failures++;
    }
    
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Ran %d tests in %fs\n", test->elements, test->timeTaken);
    
    // Check failures to either pass or fail parent test
    if (failures > 0) printRed("\nTEST FAILED\n\n");
    else  printGreen("\nTEST PASSED\n\n");
    
}

// Free memory
void freeTest(CTest* test) {
    for (int i = 0; i < test->elements; i++) {
        free(test->tests[i].description);
    }

    free(test);
}

// Run tests
void run(CTest* test) {
    test->end = clock();
    test->timeTaken = ((double) (test->end - test->start)) / CLOCKS_PER_SEC;
    displayTests(test);
    freeTest(test);
}

/*

Assertions

*/

void assertEqual(CTest* test, int a, int b, const char* description, bool skip) {
    
    // Create test object
    Test *newTest = startTest(test, description, skip);
    if (!newTest) return;

    // Assert equal, if not fail
    if (a == b) newTest->testStatus = PASSED;
    else {
        newTest->testStatus = FAILED;
        asprintf(&(newTest->statusMessage), "AssertionError: %d != %d", a, b);
    }

    // End timer and record time
    endTest(test, newTest);
}

void assertNotNull(CTest* test, void *a, const char* description, bool skip) {
    
    // Create test object
    Test *newTest = startTest(test, description, skip);
    if (!newTest) return;

    // Assert not null, if not return
    if (a != NULL) newTest->testStatus = PASSED;
    else {
        newTest->testStatus = FAILED;
        newTest->statusMessage = "AssertionError: A != NULL";
    }

    // End timer and record time
    endTest(test, newTest);
}

void assertTrue(CTest* test, bool a, const char* description, bool skip) {
    
    // Create test object
    Test *newTest = startTest(test, description, skip);
    if (!newTest) return;

    // Assert true, if not return
    if (a == true) newTest->testStatus = PASSED;
    else {
        newTest->testStatus = FAILED;
        newTest->statusMessage = "AssertionError: A != true";
    }

    // End timer and record time
    endTest(test, newTest);
}

void assertFalse(CTest* test, bool a, const char* description, bool skip) {
    
    // Create test object
    Test *newTest = startTest(test, description, skip);
    if (!newTest) return;

    // Assert true, if not return
    if (a == false) newTest->testStatus = PASSED;
    else {
        newTest->testStatus = FAILED;
        newTest->statusMessage = "AssertionError: A != false";
    }

    // End timer and record time
    endTest(test, newTest);
}

#endif