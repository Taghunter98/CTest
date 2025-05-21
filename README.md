![image](https://i.imgur.com/Bw6RGz4.png)

# CTest
A user friendly lightweight testing framework I built for my C projects. 

## Features
- Set up a global test with up to 50 internal tests
- Run tests and see detailed coloured output on terminal with error handling
- Minimal boilerplate and simple interface for test management
- Multiple assertion functions with plans for expansion
- Test runtime tracking

## Example use
1. Set up test parent object, with `testSetup()`. Then add all test functions below, making sure to pass the parent test to each function. Finally run the test with run, passing the global test object.

    ```c
    int main() {
        CTest *test = testSetup();  // Init the test
    
        // Add test functions to test scope
        test1(test);                
        test2(test);
        test3(test);
        test4(test);
        test5(test);                

        run(test);                  // Run the test
    }
    ```
2. Then write your test functions, I have used some simple assertion statements here.
    ```c
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
        assertNotNull(test, &sum, "Check sum us not null", true);
    }

    void test5(CTest *test) {
        bool val = 1 != 0;
        assertTrue(test, val, "Check val is true", false);
    }
    ```

    A sample output will look like this:

    ```
    Check if sum is equal to 20                                                      	PASS
    Check A is true                                                                  	PASS
    Check A is false                         AssertionError: A != false              	SKIP
    Check if A is not null                                                         	    SKIP
    Check val is true                                                                   PASS

    ----------------------------------------------------------------------------------------
    Ran 5 tests in 0.000161s

    TEST PASSED
    
    ```
## Planned features
I am planning on contributing more features to build out the test suite over time with the next lot of features detailed below:

- More assertion statements with array comparison
- Better error handling
- Assumption checking
- Greater user control over the tests
- Improve the CLI UI

## Contribution
I am really happy for anyone to contribute, this is currently a personal tool however if you would like to contribute please fork the repo and make a pull request!

## Licence
This project is licenced under the MIT licence.