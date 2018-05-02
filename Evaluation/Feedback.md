# kad144
Score: 94

## Files & Changed Files
* Only required files committed
* Proper files changed

## Build
* Successfully builds, no errors, no warnings

## Test
* Passes all user tests
* No extraneous output

## Test Oracle: code\_analysis\_t.cpp
* Passes oracle test suite with student's implementation

## Test Oracle: code\_analysis.cpp
Fails a late test in the student's test suite with oracle implementation

## Code
* Necessary code is present
* Indentation is inconsistent with final returns, inside of try block
* Not sure why exceptions were thrown and then caught. 
* Temporary strings such as ```errorType1``` and ```errorType2``` are not well named. Just put the literal string in the output.
* No need for final return when if-then-else has returns in both then and else.e
* Not easy to read. Use blank lines to separate, especially after the first if-statement in ```analysis_filename()```
* If every part is returning in a nested if, the else's are not needed
* Conditions are much more complex then they need to be

## Test Cases
* Good set of test cases
* Be consistent on use of blank lines in the test program

## Literal Values used in Testing
* Realistic values used based on the problem description

## Error Messages
* Report did not find error messages because they were not literal strings output via ```std::cerr```

## Commits
* All commit versions build successfully
* Good set of commits
* Good commit messages
* Test cases committed with implementation code

