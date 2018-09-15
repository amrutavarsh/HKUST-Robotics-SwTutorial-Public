Author: Daniel Cheung

ITSC: dcheungaa@connect.ust.hk

Submit the homework in separate .c files to dcheungaa@connect.ust.hk

# Homework

This homework aims to check your understanding in the syntax of C programming, as well as to test the flexibility of your mind, to see whether you can come up with ingenious solutions to the problems. Simpler and faster code is always better.

For the following problems, there are no code skeletons. As long as your code is clear, it will be marked fine. You may ask seniors for any queries and Google if you need to. Have fun doing the homework!

## Simple Calculator

Implement a simple calculator program that:

1. Ask for the mode of operation by reading a character input.
2. Ask for the first int.
3. Ask for the second int.
4. Display the result in form of `<first_number> <operator> <second_number> = <result>`
5. Ask whether they want to try again by reading a character. If they reply `'y'`, repeat the program. Otherwise, end the program.

Assume all inputs are correct.

| Operations     | Character |
| -------------- | --------- |
| Addition       |     `'+'` |
| Subtraction    |     `'-'` |
| Multiplication |     `'*'` |
| Division       |     `'/'` |
| Modulus        |     `'%'` |

#### Expected combined console inputs and outputs

```
Select a mode of operation (+, -, *, /, %): -
First number: 1
Second number: 2
1 - 2 = -1
Again? y
Select a mode of operation (+, -, *, /, %): +
First number:  1
Second number:  2
1 + 2 = 3
Again? n
```

When writing the format string for `scanf() ` to read a character, use this: `" %c"`. Because pressing the Enter key counts as inputing a newline character (`'\n'`). Entering a trivial character as well as the Enter key will count as 2 characters. Since this format string `"%c"` only consumes 1 character, the Enter key would be put in a buffer for until the next time `scanf()` is needed. In other words, the `'\n'` would be queued for the next time when `scanf()` reads a character, and would be consumed immediately, so the console will not pause and ask for an input. The space in the correct format string will consume the Enter keys, effectively ignoring them.

## Mesmerizing Sin Curve

In this problem, you have to draw out a vertical version of the mathematical sin curve in the console with spaces and asterisks using loops. The following required facts are provided to you.

- To use mathematical functions like `sin()`, include the header `<math.h>`.

- The `sin()` function has the following prototype, from [cppreference](https://en.cppreference.com/w/c/numeric/math/sin):

  ```c
  double sin( double arg );
  ```

  `arg` is a double storing the angle in radian units.

- `M_PI` stores the pi value in radian units. Can be accessed directly after inclusion of `<math.h>`

You must initialize variables to store the following. The program should work as intended when these values are changed, compiled and run again.

- `periods` - How many periods of the sin curve are drawn;
- `x_size` - How wide the sin curve is printed be;
- `y_size` - How tall a period of the curve is drawn.

#### Expected parameters and outputs

When:

- `periods` is 3
- `x_size` is 20
- `y_size` is 15

The console shows:

```
          *
              *
                 *
                   *
                   *
                  *
               *
            *
        *
     *
  *
 *
 *
   *
      *
          *
              *
                 *
                   *
                   *
                  *
               *
            *
        *
     *
  *
 *
 *
   *
      *
          *
              *
                 *
                   *
                   *
                  *
               *
            *
        *
     *
  *
 *
 *
   *
      *

```

Notice at the smallest output of the sin function, the x-position of the `*` is at 0, and at the largest output, the x-position is at 20.

## A and B

Initialized with an array of `'a'`s and `'b'`s like so `{'a', 'b', 'b', 'a', 'a'}`. Whenever you find 2 adjacent  `'a'` and `'b'`, remove them. Repeat that until you cannot find pairs anymore, then print out the array to the console.

#### Sample inputs and outputs

- **Sample 1**

  Input

  ```c
  {'a', 'b', 'a'}
  ```

  Console output

  ```
  a
  ```

- **Sample 2**

  Input

  ```c
  {'a', 'b', 'b', 'a'}
  ```

  Console output

  ```
  
  ```
