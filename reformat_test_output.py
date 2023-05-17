import sys
import re

# run ./build/tests/server_tests > test_output.txt to get the output the text file
# and then run python3 reformat_test_output.py test_output.txt

# ANSI escape codes for colorizing output.
RED = "\033[1;31m"
GREEN = "\033[1;32m"
BLUE = "\033[1;34m"
RESET = "\033[0;0m"


def parse_test_output(file):
    test_suite = None
    total_tests = 0
    passed_tests = 0
    failed_tests = []

    print("Running tests from:")

    with open(file, 'r') as f:
        for line in f:
            line = line.strip()
            m = re.match(r'\[\----------\] (\d+) tests? from (\w+)', line)
            n = re.match(r'\[ RUN      \] (\w+)\.(\w+)', line)
            o = re.match(r'\[       OK \] (\w+)\.(\w+) \((\d+) ms\)', line)
            p = re.match(r'\[  FAILED  \] (\w+)\.(\w+) \((\d+) ms\)', line)

            if m:
                if test_suite is not None:
                    print(
                        f'{BLUE}----------------------{test_suite}----------------------{RESET}\n')
                test_suite = m.group(2)
                print(f' - {test_suite}.cpp')
                print(
                    f'{BLUE}----------------------{test_suite}----------------------{RESET}')
                total_tests += int(m.group(1))

            elif n:
                print(f'\nTest {n.group(2)}: ', end="")

            elif o:
                print(f'{GREEN}PASS{RESET}')
                passed_tests += 1

            elif p:
                print(f'{RED}FAIL{RESET}')
                failed_tests.append((test_suite, p.group(2)))

    print(f'{BLUE}----------------------{test_suite}----------------------{RESET}\n')
    print("\nGlobal summary:")

    if len(failed_tests) > 0:
        print(f'{RED}{passed_tests}/{total_tests} tests PASSED{RESET}')
        print("Tests that failed were:")
        for suite, test in failed_tests:
            print(f'{RED}Test {test} from {suite}{RESET}')
    else:
        print(f'{GREEN}{passed_tests}/{total_tests} tests PASSED{RESET}')


if __name__ == "__main__":
    parse_test_output(sys.argv[1])
