# Collatz Conjecture / Hailstone Sequence
by Paul Nadolny, 2019-Jul-21, https://github.com/pjnadolny
## Description
Given the following function on positive integers:  

f(n) = n/2, <i>if n is even</i>  
f(n) = 3*n+1, <i>if n is odd</i>  

Apply this function repeatedly to get a sequence:

 a<sub>i</sub> = n <i>for i=0</i>  
 a<sub>i</sub> = f(a<sub>i-1</sub>) <i>for i>0</i>  

An example sequence starting at 3 is:  
3, 10 5, 16, 8, 4, 2, 1, 4, 2, 1  
which takes 7 steps to reach 1 (at which point it cycles 1, 4, 2, 1, ...)

The sequence starting at 27 takes 111 steps to reach 1.

The Collatz conjecture is that the sequence will eventually go to 1 for every initial positive integer.  It's still a conjecture because:
1. It hasn't been proven.
2. No counter examples have been found.

Much more information can be found at Wikipedia: https://en.wikipedia.org/wiki/Collatz_conjecture, or Wolfram MathWorld: http://mathworld.wolfram.com/CollatzProblem.html, or many other webpages and videos.  Try searching for "Collatz conjecture" in your favorite search engine.

## Algorithms
I've created two C++ functions which each implement a different algorithm to compute the number of steps it takes to go from an initial value to 1. In addition, there are two others that I should implement.

### Recursion with Memoization
One implemented C++ function algorithm is recursive, because the nature of the sequence is recursive: each successive value is the output of applying the function to the previous value, and the base case is when the value is 1.  (When the value is 1, it takes 0 steps to get there, because you're already there!)

To this recursive function I've added memoization.  Every time I compute the number of steps for a value, I insert it into a hash table, so that the next time I don't need to recompute it.

### Iteration
The second implemented C++ function is interative - instead of using recursion, I use a loop to compute successive values in the sequence.  When the value becomes 1, I stop the loop and the number of steps to reach 1 is the number of times through the loop.

Often iteration is preferable to recursion, because the stack doesn't grow, using up memory.

### Iteration with Memoization
I haven't done this yet, but the next logical step is to create a function that uses iteration with memoization.  This would have the advantage of using minimal stack space, while using memoization to decrease computation time.

### Recursion
To be complete, I should implement a purely recursive function.

## Analysis
My only analysis so far is running it on the first N positive integers to count the iterative loops, recursive function call, and the hash table size.

For example, after the first 100 positive integers, the iterative function took 3142 loops, while the memoized recursive function made only 350 calls, but ended with 250 hash table entries.

| First N Values  | Iterative Loops   | Recursive Calls | Memoized Hash Table Size|
|--------: |-------:| -----:| ---------:|
| 100     |  3142   |  350  |  250  |
| 200     |  8418   |  630  |  430  |
| 300     | 14167   |  909  |  609  |
| 400     | 20141   | 1208  |  808  |
| 500     | 26143   | 1565  | 1065  |

You can see that Recursive Calls and Memoized Hash Table Size seem to grow as O(N) - roughly 3N and 2N respectively.  However, Iterative Loops is growing more quickly.

## Future steps
I plan to implement all four functions above, then keep track of time spent in each function, memory used in the hash table, etc.  This would enable me to compare the functions more thoroughly and see what advantages and disadvantages each one has.

## Notes
I wrote these functions just to demonstrate different ways to approach a problem, and show how memoization can help reduce the amount of computation time.

Real research into the Collatz Conjecture uses far more advanced techniques to get to values in the billions or trillions.
