import sys
import re

# run ""./build/tests/server_tests > test_output.txt" to get the output the text file
# and then run "python3 reformat_test_output.py test_output.txt"

# ANSI escape codes for colorizing output.
RED = "\033[1;31m"
GREEN = "\033[1;32m"
BLUE = "\033[1;34m"
YELLOW = "\033[33m"
CYAN = "\033[36m"
UNDERLINE = '\033[4m'
BOLD = '\033[1m'
RESET = "\033[0;0m"


def parse_test_output(file):
    test_suite = None
    total_tests = 0
    passed_tests = 0
    failed_tests = []
    test_files = {}
    test_num = 0

    print(
        f'{YELLOW}═════════════════════════════════{"TESTS"}═════════════════════════════════════{RESET}\n')

    with open(file, 'r') as f:
        f.readline()
        f.readline()
        for line in f:
            line = line.strip()

            if line.endswith('(0 ms total)'):
                continue

            m = re.match(r'\[\----------\] (\d+) tests? from (\w+)', line)
            n = re.match(r'\[ RUN      \] (\w+)\.(\w+)', line)
            o = re.match(r'\[       OK \] (\w+)\.(\w+) \((\d+) ms\)', line)
            p = re.match(r'\[  FAILED  \] (\w+)\.(\w+) \((\d+) ms\)', line)

            if m:
                if test_suite is not None:
                    print()  # Adding an empty line between the last test and the closing header
                    print(
                        f'{BLUE}------------------------{test_suite}------------------------{RESET}\n')

                test_suite = m.group(2)
                test_files[test_suite] = True  # initialize as all tests pass
                print(
                    f'{BLUE}------------------------{test_suite}------------------------{RESET}')
                test_num = 0

            elif n:
                total_tests += 1
                test_num += 1
                print(f'\nTest {test_num:02} {n.group(2)}: ', end="")

            elif o:
                print(f'{GREEN}PASS{RESET}')
                passed_tests += 1

            elif p:
                print(f'{RED}FAIL{RESET}')
                failed_tests.append((test_num, test_suite, p.group(2)))
                # if a test fails, mark as false
                test_files[test_suite] = False

    print(
        f'{BLUE}------------------------{test_suite}------------------------{RESET}\n')
    print(f'\n{CYAN}{BOLD}{UNDERLINE}Global summary:{RESET}\n')
    print("Running tests from:")

    for file, passed in test_files.items():
        if passed:
            print(f'{GREEN}{file}{RESET}')
        else:
            print(f'{RED}{file}{RESET}')

    print("\nTest Results:")
    if len(failed_tests) > 0:
        print(f'{RED}{passed_tests}/{total_tests} tests PASSED{RESET}')
        print("Tests that failed were:")
        for num, suite, test in failed_tests:
            print(f'{RED}Test {num:02} {test} from {suite}{RESET}')
    else:
        print(f'{GREEN}{passed_tests}/{total_tests} tests PASSED{RESET}')


if __name__ == "__main__":
    parse_test_output(sys.argv[1])
