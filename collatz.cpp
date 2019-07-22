// Name:   collatz
// Author: Paul Nadolny
// Date:   2019-Jul-17
//
// Purpose: Show two ways of computing the Collatz or hailstone function.
//          One way is recursive with memoization, the other is iterative.
// Note:    I'm showing the overall algorithms without necessarily
//          optimizing the running time or space management.
// TODO:    Wrap the functions and static variables in a class.
// TODO:    Also could do iterative with memoization.
// TODO:    Add statements to time the function calls.
//
// To compile: g++ -std=c++17 -o collatz collatz.cpp

#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <string>

int DEBUG = 0;

static int calls_recursive_memo = 0;
static int count_loop = 0;

// hash table for memoization, a value of zero indicates
// that a value needs to be calculated for this key
static std::unordered_map<int, int> memo;


// ---------------------------------------------------------------------------
// Takes one argument: the initial value
// Returns an int: the number of steps to go from the initial value to 1
// Uses recursion and memoization
int hailstone_recursive_memo(int a) {

  ++calls_recursive_memo; // keep track of the total count of function calls

  // Base cases, no need to memoize these
  if (a < 1) {
    // function is not defined for values less than 1
    return 0;
  }
  if (a == 1) {
    // f(1) takes 0 steps
    if (DEBUG==1) std::cout << "At " << a << " Base case: 0" << std::endl;
    return 0;
  }

  if (memo[a] == 0) {
    if (a % 2 == 0) {
      if (DEBUG==1) std::cout << "At " << a << " Calling hailstone_memo(" << a << "/2)" << std::endl;
      memo[a] = 1 + hailstone_recursive_memo( a/2 );
    } else {
      if (DEBUG==1) std::cout << "At " << a << " Calling hailstone_memo(3*" << a << "+1)" << std::endl;
      memo[a] = 1 + hailstone_recursive_memo( 3*a + 1 );
    }
  } else {
    if (DEBUG==1) std::cout << "At " << a << " Found memo[" << a << "]=" << memo[a] << std::endl;
  }

  return memo[a];
} // end hailstone()


// ---------------------------------------------------------------------------
// Takes one argument: the initial value
// Returns an int: the number of steps to go from the initial value to 1
// Uses iteration
int hailstone_loop(int a) {
  int steps;
  bool done;

  if (a < 1) {
    return 0;
  }
  if (a == 1) {
    return 0;
  }

  steps = 0;
  done = false;
  while (!done) {
    ++count_loop; // keep track of the total count of times through the loop
    ++steps;
    if (a % 2 == 0) {
      a = a/2;
    } else {
      a = 3*a + 1;
    }
    if (a == 1) {
      done = true;
    }
  }

  return steps;
} // end hailstone()


// ---------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  int table_rows = 10;  // default number of table rows to compute
  int total_calls_recursive_memo = 0;
  int total_count_loop = 0;
  int col1 = 3;  // column width
  int col2 = 5;  // column width

  // Display a table showing how many resursive calls or loops it takes
  // to compute the collatz/hailstone steps using each algorithm.
  // The recursive memoized algorithm gets more efficient as more rows
  // are computed.

  // Check for an optional command line argument
  // It is the number of table rows to compute
  if (argc == 2) {
    std::string s(argv[1]);
    table_rows = std::stoi(s);
  }

  std::cout << "Will compute the first " << table_rows <<
    " Collatz/hailstone numbers" << std::endl;
  std::cout << std::endl;

  std::cout << std::setw(col1) << " " << "   "
            << std::setw(col2) << "recur" << " "
            << std::setw(col2) << "recur" << "   "
            << std::setw(col2) << "loop" << " "
            << std::setw(col2) << "loop" << std::endl;
  std::cout << std::setw(col1) << "n" << "   "
            << std::setw(col2) << "steps" << " "
            << std::setw(col2) << "calls" << "   "
            << std::setw(col2) << "steps" << " "
            << std::setw(col2) << "count" << std::endl;

  for (int i=1; i<=table_rows; ++i) {
    calls_recursive_memo = 0;
    count_loop = 0;
    int steps_recursive_memo = hailstone_recursive_memo(i);
    int steps_loop = hailstone_loop(i);
    std::cout << std::setw(col1) << i << "   "
              << std::setw(col2) << steps_recursive_memo << " "
              << std::setw(col2) << calls_recursive_memo << "   "
              << std::setw(col2) << steps_loop << " "
              << std::setw(col2) << count_loop << std::endl;
    total_calls_recursive_memo += calls_recursive_memo;
    total_count_loop += count_loop;
  }

  std::cout << std::endl;
  std::cout << "Total recursive memoized function calls: "
            << total_calls_recursive_memo << " " << std::endl;
  std::cout << "Total iterative loop count:              "
            << total_count_loop << std::endl;

  // Show the memoization hash table.
  std::cout << std::endl;
  std::cout << "Memoization:  hash table entries: " << memo.size() << std::endl;
  for (auto const& i : memo) {
    std::cout << "(" << i.first << "->" << i.second << ") " ;
  }
  std::cout << std::endl;

  return 0;
}
