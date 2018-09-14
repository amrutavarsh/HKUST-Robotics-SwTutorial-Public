Author: Daniel Cheung
ITSC: dcheungaa@connect.ust.hk

# Tutorial 0 - C Programming

*Courtesy to Peter for letting me refer to his C++ notes.*

## Introduction to C, a procedural language

C is an old language. It was very popular then, and is still popular now, because of how robust it can run. It is a **low level** language, meaning there is little between it and machine code (0s and 1s). It also means that we often have to manage the memory (RAM) by ourselves, the programmer.

C is also a procedural language, the type of program where we have to say a list of instructions to the computer one by one and it follows line by line. A specific way to write the list of instructions to do something, is what we call an **algorithm**.

## Where do I write my code? (Tutorial Preparation)

Since some of you may not have installed an **IDE** (integrated development environment) on your computer yet, you may use an online version to write your programs in. [Repl.it C Language](https://repl.it/languages/c) is a good choice.

##### Instructions

1. Simply go onto [Repl.it C Language](https://repl.it/languages/c), you will see the URL change to `https://repl.it/repls/SomeRandomWords`. This is the unique link to your code. You can give this link to other people to share your code.
2. In the middle section, you will see a sample code already in place, under the file name `main.c`. You can also see all the files on the left column associated with this setup. Do not worry about other files right now, editing `main.c` in the middle column is sufficient for now.
3. After you have completed some code, click "Run" to compile and run the program. The program is then run in the **console** on the right, where you can do inputs and it can display outputs.  If there are any errors in the code, the program will fail to run and display its error message in the console as well. Follow its prompt or maybe search online  to find out how to fix the problem.

For now, to familiarize yourself to C, try editing the sample program so that instead of displaying "Hello World", it displays your name.

In a later tutorial, we will show you how to install and use Keil,  the IDE we use for the CPU onboard.

## Hello world

Let us write the most basic program to illustrate the language that is C, a "hello world program" that outputs simply: "Hello world!".

```c
//main.c

#include <stdio.h>

int main() {
    // This is a comment.
    
    /* This is a multi-lined comment.
     * These gray lines are ignored by the program.
     * It is only for the developer, to remember something,
     * or to tell their peers how the program works.
     */
    
    printf("Hello, World!\n"); // \n means newline
    return 0;
    
    // Console:
    // Hello, World!
    // 
}
```

The program can be dissected as follows:

- `#include <stdio.h>`
  This line tells the program we are using features within a **library** named `stdio.h`, `printf()` to be exact, as it is defined within the library.

- `int main() {}`
  This is a **function definition**. It is the entry-point of the program, that means, the program will start right inside it. **It must exist in every C program.** We write the main code inside this function.
  
- `printf("Hello, World!\n");`
  This is a **function call**, like using a mathematics function, we pass parameters within the parenthesis. This function can output whatever parameter we put in to the **console**, so we want it to write out `Hello, World!`. The function is defined within the library we have included earlier.  **`'\n'` represents a "newline" character**, since we cannot actually store an Enter key in a single line.
  
- `return 0;`
  When we run a C program, it ends with giving us an **exit code** to indicate whether or not there is a problem. By *returning* `0`, we indicate what the program ended successfully.
Some things to take note of:

- C is case-sensitive. Different case are different letters. Do not confuse them.
- End each statement with a `;` like how you would end a sentence with a full stop in English.
- Close as many `{`/`(`/`"` as there are with `}`/`)`/`"` and do not mess up the order. It is just like maths.

## File types

C programs are stored as plain text in, often, 2 file types, with their conventional usages. Do follow the conventions, as there are practical and real differences you will see later on.

- `.h` **Header files** - These files contain function, structure, global variable and macro declarations. *Basically anything declared that can be accessed globally.*

  For example: `stdio.h` is an actual header file stored in your computer, and is installed along with your choice of **C toolchain**. I personally use "MinGW 64-bit" and my file is at `D:\TDM-GCC-64\x86_64-w64-mingw32\include\stdio.h` but your path would likely be different than mine.
  
  *The reason your **IDE (integrated development environment)** is able to detect where the libraries are, is because the installation of the toolchain also appended the source directories within your `PATH` (system environment variable), or the installation path is manually selected in your IDE settings.*
  
- `.c` **Source files** - These files contain function implementations.

  For example: the hello world program is stored within `main.c` in my case in some arbitrary project folder that I have created for the tutorial.
  
## Variables

### Data types

#### Primitive types

Variables are containers for values. We use different typed variables to store different typed values, e.g. integer, decimal, text.

These are the **primitive types** in C, the most basic variable types:

| Type | Description | Example Literal |
|------|-------------|------|
| `char` | 8-bit integer* for storing an ASCII character | `'a'` |
| `int` | 16-bit/32-bit signed integer** | `1` |
| `float` | 32-bit, single-precision floating point value | `3.0f` |
| `double` | 64-bit, double-precision floating point value | `5.0` |

- \*Whether `char` is signed or unsigned is machine-dependent.
- \*\*Size is compiler-dependent and machine-dependent.

There is actually one more common, non-primitive type.

| Type | Description |
|------|-------------|
| `void` | The absence of type |

#### Signs and modifiers

Signed integer will use half of the distinct bit combinations for negative numbers and the other for positive. The ranges are as follows:

![Signed range equation](https://latex.codecogs.com/svg.latex?%5Ctext%7BSigned%20Range%7D%20%3D%20%5B-2%5E%7B%5Ctext%7Bbit%7D-1%7D%2C2%5E%7B%5Ctext%7Bbit%7D-1%7D-1%5D)

![Unsigned range equation](http://latex.codecogs.com/svg.latex?%5Ctext%7BUnsigned%20Range%7D%20%3D%20%5B0%2C2%5E%7B%5Ctext%7Bbit%7D%7D-1%5D)

We can add the `signed` and `unsigned` modifiers to `char` and `int` to set the range the variable can hold. Read other modifiers on [C Language](http://c-language.com/c-tutorial/c-type-modifiers/).

To test for the bit size for different types on the machines, we can use the `sizeof()` operator. For example: `sizeof(int)` will tell us how big `int` really is on the machine that runs the program. You must include `<stdlib.h>` in order to use it.

#### The boolean type

C has since added another type, the boolean type in the C99 standard version of C, as `_Bool`. It has also added the useful alias `bool`, (another name for `_Bool`,) as well as macros `true` and `false` to represent the values for convenience, but these **require the inclusion of `<stdbool.h>`**.

| Type | Description |
|------|-------------|
| `_Bool` | A boolean value represented in a 1-bit integer. Assigning anything non-`0` to it is set to `1`, considered true. |
| `bool` | `true` evaluates to `1`; `false` evaluates to `0` |

#### Standard integer types

It is not convenient that `int` is sometimes 2 byte and sometimes 4. It is more useful if we can control exactly how long `int` is, so we do not have to cater to different machine settings. With `<stdint.h>`, we have just that, more type definitions!

| Type | Description |
|------|-------------|
| `int8_t` | signed 8-bit integer |
| `int16_t` | signed 16-bit integer |
| `int32_t` | signed 32-bit integer |
| `int64_t` | signed 64-bit integer |
| `uint8_t` | unsigned 8-bit integer |
| `uint16_t` | unsigned 16-bit integer |
| `uint32_t` | unsigned 32-bit integer |
| `uint64_t` | unsigned 64-bit integer |
| ... | *other less common types* |

Remember we said, **we had to manage the memory by ourselves**? Since C is low level, we get to have more choices regarding the memory of our variables. The reason we **must not use `int64_t` for every integer** we have, is because we have to **manage the performance as well as memory** use of our program, especially **for micro-controllers, that have little computational resources.**

Smaller variables are always faster and they consume less space than larger ones.

#### `const` type qualifier

According to [cppreference](https://en.cppreference.com/w/c/language/const), `const` is a type of qualifier in C, adding a "quality" of being constant to the "variable". A variable with such a qualifier in front is not allowed to be reassigned.

```c
const double PI = 3.141592654;
```

Typically, we name constants using the **UPPER_SNAKE_CASE** convention, which is discussed below.

Superficially, this protects unchangeable variables from changing, by emitting an error during compilation, making it safer. *But in a deeper level, this qualifier can change the program in a lower, more technical level in the compiler, possibly altering performance and space efficiency.*

### Variable declaration

We must tell the computer that we are about to use a variable with some name before we use it. This action is called **declaration**. And we can only declare a variable with the same name once per scope, (we'll talk about that later). We can declare one with this syntax: `<type> <variable_name>;`. For example:

```c
int16_t some_integer; // Declaring some_integer as a 16-bit integer
char c; //Declaring c as a character
char d;
```

### Variable assignment

When a variable is declared, we can assign a value to the variable using the `=` (assignment operator). The first assignment to a variable is called the **initialization**. We should **always initialize any variable we declare before reading them**, as this is an "undefined behavior", the compiler may or may not crash from the consequences if you do so. We assign values like so:

```c
some_integer = 42;
c = 'A';
d = c;
```

In the above example, we set the value `42` to `some_integer`, which we assume is declared before. We also assigned a character, which **must be quoted with single quotes**, to `c`. `42` and `'A'` are called **literals**, because they are basically the value.

Then, we assigned the value stored in `c`, to `d`, so `d` is now having the value `'A'`. **Be careful, the `=` is not the mathematical "equal", it means "assign the RHS to the LHS"**.

#### Casting

Assigning a variable or literal in another type to a variable is possible through **casting**. Saving a lower-bit value to a higher-bit container is often safe, but the converse is always unsafe, because information is lost by losing bits. Below are some examples:

```c
int main(){
    bool b = true;
    int n = b; // compiler casts a boolean to an integer, n would be 1 because true -> 1; false -> 0

    char c = 'c';
    n = c; // compiler casts a character to an integer, by using ASCII conversion, n is now 99

    float f = 0.55f;
    n = f; // compiler casts a float to an integer, by truncating the floating point value, n is now 0, same goes with double

    uint8_t p = 6;
    uint16_t q = p; // compiler casts a 8-bit to a 16-bit, since 16-bit can hold larger values, q is also 6

    q = 678;
    p = q; // compiler casts a 16-bit to a 8-bit, since 8-bit cannot store a number this large, it overflows and goes back to 166 (678 in binary with only last 8 bits)

    int16_t j = -5;
    uint16_t k = j; // compiler casts a signed to unsigned, since it cannot store a negative number, it underflows and goes to 65531 (-5 in binary's two's compliment and converts to unsigned)
  
    return 0;
}
```

The type conversion above is an **implicit** casting, i.e. the compiler itself figures out the converted type. Usually, instead, we would prefer a safer approach, that we specify the converted type in our codes.

```c
float f = 2.5f;
int n = (int)f; //n is now 2
```

### Combined declaration and initialization

We may also combine the initialization to the declaration. The safest way to declare is always to first initialize to some default value.

```c
int16_t some_integer = 42;
char c = 'A';
char d = c;
```

Here is a working program:

```c
//variable.c

#include <stdio.h>
#include <stdint.h>

int main() {
    int16_t some_integer = 42;
    printf("The number is ");
    printf("%d", some_integer); //The left is used for formatting
    return 0;
    
    // Console:
    // The number is 42
}
```

### Naming convention and rules

There are several ways people name their variables, as illustrated in the names:

- `PascalCase`
- `camelCase`
- `snake_case`
- `UPPER_SNAKE_CASE`
- `kebab-case` (Cannot be used in C)

Depending on the organization or the project, you may be asked to use a certain naming convention. They are always used to differentiate between variables, functions, macros and constants, but different people use different styles.

Secondly, in C and in many other languages, these are some points you must follow in naming a variable, otherwise, you may cause an error during compilation.

- Name should begin with a letter or underscore.
- After the first character, you may include numbers.
- Names are case sensitive.
- No reserved keywords. E.g. You can't use `int` or `return` as a name.

**Do make meaning names, do not name a variable a letter**. As your code becomes longer, you will forget about what they are. It is also clearer to your peer developers if the names are clear. When you are naming a Boolean variable, name it a logical statement, like `is_repeat`,  `found_path`, `has_changed`, etc.

## Operators

Operators help us to perform the most fundamental mathematical or logical operations on variables.

**Operators** can accept different numbers of **operands**. Their names are as follows:

- **U**nary operators:
  
  Positions: `-x` (UB), `x++` (UA)
  
- **B**inary operators:

  Position: `x + y`
  
- Ternary operator:

  Position: `x ? y : z`
  
**Beware that different operators carry different precedences**, meaning values are evaluated from the operator with highest precedence down to the lowest, like how multiplication comes first before addition in maths. 

### Assignment operators

- `=` assignment (B)
- ...

The `=` is the most fundamental assignment operator. There are other assignment operators that simplifies **statements**, (such as `+=`, `|=`, ...), but `=` is sufficient for now.

### Arithmetic operators

- `+` addition (B)
- `+` unary plus (UB. no effect, just for symmetry)
- `-` subtraction (B)
- `-` unary minus (UB)
- `*` multiplication (B)
- `/` division (B)
- `%` modulo (B)
- ...

These are your typical mathematical operators.

### Relational operators

A relational operator compares the value of two expressions, most of which are self explanatory.

- `==` equal to (B)
- `!=` not equal to (B)
- `>` greater than (B)
- `>=` greater than or equal to (B)
- `<` less than (B)
- `<=` less than or equal to (B)

**Do not mix up `=` and `==`**. One is used for value assignment, the other used to compare whether the values are the same.

### Logical operators

- `||` logical or (B)
- `&&` logical and (B)
- `!` logical not (UB)

These operators accept **boolean represented** values on both sides, and perform logical operations on them to return a boolean value.

`!` has a higher precedence than `||` and `&&`.

#### Truth Table

| P | Q | P or Q | P and Q | not P |
|:---:|:---:|:------:|:------:|:----:|
|`false`|`false`|`false`|`false`|`true`|
|`false`|`true`|`true`|`false`|`true`|
|`true`|`false`|`true`|`false`|`false`|
|`true`|`true`|`true`|`true`|`false`|

Read [Operators in C and C++ on Wikipedia](https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B) for more information, including **Bitwise operators**, **compound assignment operators**, **Member and pointer operators**, etc.

## Statements

A statement is a fragment of code in C. All statement types are on [cppreference](https://en.cppreference.com/w/c/language/statements).

### Expression statements

Expression statements are the lines of code that ends in `;`. Or in other words: an expression statement is **a line of code**. Most statements are expression statements.

### Compound statements (Code Block)

Compound statements consists of one or more lines of code. It defines a **scope**. They are also called **code blocks**.

One in a scope can access variables declared in itself, as well as variables in larger scopes, but not those in smaller scopes inside itself nor neighboring scopes nor any of its parents. Essentially, the access right to a variable is only at its level upwards.

#### Selection statements

Selection statements modifies the **control flow** of the program. It uses different sets of code depending on the condition at **runtime**.

##### If statements

Code blocks are bounded by a set of `{}`, which you have already seen, surrounds the `main()` function.

The if statements takes the following formats:

- `if (<expression>) <statement_true>`
- `if (<expression>) <statement_true> else <statement_false>`

When the `expression` is not `0`, `statement_true` is evaluated, otherwise, `statement_false` is evaluated if the `else` keyword exists.

Often, `statement_false` is itself another if statement, chaining into an (if, else if, else) structure.

The following is an example:

```c
if (x > 1) {
    //when x > 1 evaluates to true, i.e. 1, this part is run.
    //when it evaluates to false, i.e. 0, this part is skipped.
} else if (x == 0) {
    //some other code
} else {
    //some other code
}
```

#### Switch statements

Switch statements contains **jump statements** and **labels**, which we do not recommend using outside of switch statements. They act simply as alternatives to if statements on the superficial level. The format is as follows:

- `switch (<expression>) <statement>`

  The "expression" here must evaluate to some integral value. And the "statement" here is typically a block with case labels.

- `case <integer_constant_expression>: <statement>`
- `default: <statement>`

```c
switch (x) {//value to compare against with the cases
    case 1:
        //code for when x == 1
        break; //jumps the the end of the switch statement
    case 2:
        //code for when x == 2
    case 3:
        //code carries on from line above and for when x == 3
        break;
    default:
        //code when none of the cases match. The default label is optional
}
```

Each case is compared against the expression in the switch parenthesis, if a match is found, the program **jumps** to that case and start executing line by line, and only exits when encountering `break;` or when the code block ends.

Basically, switch-statements are just if-statements when all their conditions are `x == case`.

### Iteration statements

Iteration statements are used to repeat a section of code.

#### While loop

This statement will execute repeatedly as long as the condition is met. The format is as follows:

- `while (<expression>) <statement>`

The following is an example:

```c
while (!done) {
    //do something
}
```

#### Do-while loop

This statement will execute, then repeatedly execute as long as the condition is met. The format is as follows:

- `do <statement> while (<expression>);`

```c
do {
    //do something
} while (is_repeat);
```

#### For loop

Often, developers use while loops to execute code while counting. For loops were introduced to simplify this situation, while encasing the **iterator** (the counting number) within the scope. The following example illustrates this.

```c
//This program prints from 0 to 9
int i = 0;
while (i < 10) {
    printf("%d\n", i);
    i++;
}
```

The for loop format is as follows:

- `for (<init_clause>; <expression (optional)>; <expression (optional)>) <statement>`

The 3 clauses in the parenthesis are usually called:

- **initialization expression**

  This expression is run before the statement. Usually, an iterator variable is declared and initialized here.
  
- **condition**

  This expression is run before every iteration of the loop to determine whether the body of the loop would be run, or whether the loop ends here. Same as before, the body is run when this expression is a non-zero value.
  
- **final expression**

  This expression is run after every iteration of the loop. Usually, the iterator is incremented or decremented here.
  
This is the for loop version of the number printing program above:

```c
for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
}
```

Of course, because the body is only a single line, the curly braces are not required. So it can become as so:

```c
for (int i = 0; i < 10; i++)
    printf("%d\n", i);
```

### Jump statements

Jump statements alter the flow of the program by literally jumping to a different section of code to execute.

- `break;`

  This statement is only valid in loops and switch statements. It is used to exit the statement, *breaking* the execution.

- `continue;`

  This statement is only valid in loops. It breaks from the current iteration and executes the final expression if the loop is a for loop, then it will move to the condition for comparision immediately, *continuing* the loop.

- `return <expression (optional)>;`

  This statement is only valid in functions. It terminates the function, then *returns* a resulting value to the caller. It is seen in the `main()` function, returning a program termination code to the operating system.
  
  `return;` is treated as returning `void`.

- `goto <identifier>;`

  This statement is used to jump to a certain label to continue program execution. **This statement is highly unrecommended, since it may create an erratic control flow as it can jump from scope to scope, and is harmful to debugging as it is difficult to follow the execution path of the program.**

## Standard input/output

A program communicates with the outside using standard input and standard output. The most common ways to input and output in C, are reading and writing to and from the console and files.

### Console output

We can use the function `printf()` from `<stdio.h>` to print to the console, as shown in the hello world example. According to [cppreference][cppref_printf] (referencing a C++ site here because C99 reference is not publicly available, you have to pay ISO to get a copy), the **signature** of the function is:

```c
int printf ( const char * format, ... );
```

The function returns the number of characters written.

The first parameter is the **format string**. Ordinary characters can be directly printed, but the **`%` character followed by flag characters** is used to specify a substitute with a value when the string is printed. To specifically print out one `%` character, one must **escape** it using `"%%"`.

The remaining `...` means one or more parameters, specifically the value to be printed, ordered accordingly to the **specifiers** in the format string.

Below is a table for the common used ones:

| Specifier | Explanation |
|-----------|-------------|
| `%%` | Writes one `%` character |
| `%c` | Writes a character |
| `%d` | Writes an integer |
| `%x` | Writes an integer in base 16 |
| `%f` | Writes a floating point number |

The above table is very crude, so please refer to [cppreference][cppref_printf] for the complete explanation.

The following is an example:

```c
printf("No specifiers.\n");
printf("%d specifier.\n", 1);
printf("%d specifiers for %c%c%c.\n", 4, 'i', 'n', 't');

//Console
/*
No specifiers.
1 specifier.
4 specifiers for int.
*/
```

### Console input

```c
int scanf( const char* format, ... );
```

Reading console input is similar to writing the output. It is just that instead of writing the values in parameter 2+, we now store to them. The function documentation is on [cppreference](https://en.cppreference.com/w/cpp/io/c/scanf).

The `...` parameters must be a type of **address**, (which we will discuss later). For now, we will see the following example:

```c
int main() {
    int number;
    scanf("%d", &number); //&<variable_name> will get you the address to the variable.
    return 0;
}
```

The above program simply reads an integer, then store that in `number`. *Be aware that during the reading of the variable, the program is at a pause, until an input is submitted.*

## Functions

`printf()` and `scanf()` are examples of functions. Functions provide **abstraction**, i.e. providing a simpler interface to hide complex implementations. We have already defined one before, it is `main()`, the entry point to our program.

### Function call

A function call takes form of: `<function_name>(<parameters...>)`

A C function call/invocation is same as those of mathematical functions, for which they accept parameters as inputs and returns an output as a response, although C functions can also perform simple actions without any response. The parameters provided to a function call can be variables or literals, just anything that carries a value.

### Function definition

Functions can be used by simply defining one. Declaration is not compulsory.

The most commonly used function definition syntax is as follows: `<return_type> <function_name>(<parameters...>) {<function_body>}`

In `<parameters...>`, parameters are separated by a `,` (comma operator). Each parameter consist of `<type_specifier> <parameter_name>`. The type specifier specifies the type of parameter the function accepts, and the parameter name is some arbitrary name, used and only meaningful inside the function.

For example:

```c
int square(int x) {
    return x*x;
}
```

Then we can call it by `square(3)` for example, it would return `9` at the calling place.

### Function declaration (Prototype)

Being like variables, functions can only be accessed after the compiler knows about it, reading from the top. So to use a function in `main()` for example, it either has to be defined above, or declared above and defined elsewhere.

If a function is declared before, then the compiler knows about its existence, and expect it to be defined some time in the future as it reads from file to file. The definition can be in any place in any file, as long as it is in some place the compiler expects.

If the function is declared, used, but not defined, then the compiler will generate a `reference to function not found` error.

The declaration/prototype is like so: `<return_type> <function_name>(<parameters...>);`

In `<parameters...>`, each parameter can be simply `<type_specifier>` without a parameter name, since they are not used immediately, though leaving a name may provide more details to how the function can be used.

## Arrays

Array is another type of variable. It is a container for multiple values of the same type. Arrays carries type information and can only carry one type of values in one array. Think arrays as cabinets, and each value belong in one drawer in a cabinet.

An array must have a **constant length**, specified either at declaration, or interpreted at initialization.

Refer to [cppreference](https://en.cppreference.com/w/c/language/array) for more details.

### Array declaration

The following is the syntax for declaration: `<element_type> <array_name>[<length (optional)>];`

The `[]`(square brackets) specifies an array.

The following is an example of declaring a float array with length 10;

```c
float numbers[10];
```

### Array initialization

An array can be initialized alongside declaration with values, by using the initializer expression, like so:

```c
int natural_numberes[20] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //remaining spaces are filled with 0s
```

If you initialize using the initializer expression, you are not required to specify the array length. It will count the number of elements and set the length as that.

Uninitialized arrays in functions store **garbage values** as initial values. If you want to initialize them as all `0`s, do the following:

```c
int blank[20] = {0};
```

**Arrays cannot be re-assigned**, so you cannot use the initializer expression after the declaration statement, nor assign them to another array variable.

### Array access

Array items do not have a name we can call, but they are arranged in an orderly fashion within an array. We can access items using an **index**. We count from 0 in programming, so we can call, e.g. the 0th item in array x. The index can be a variable containing an integer, or simply an integer literal. The following is the syntax of array access: `<array_name>[<index>]`

For example:

```c
int numbers[10];
numbers[0] = 3;
int y = numbers [0]; //y is 3
```

**Accessing outside the array region is an undefined behavior but may not generate any error when used.** Values are retrieved at other memory addresses that do not belong to the array and the values are not guaranteed as the same across machines. Accessing outside of program memory will produce a "SIGSEGV Signal Segmentation Fault" runtime error.

Arrays are usually used with for loops, to iterate over the length of the array for data manipulation.

This example populates the array with natural numbers:

```c
int n[100];

for (int i = 0; i < 100; i++) {
    n[i] = i+1;
}
```

### Multidimensional arrays

Arrays can have multiple dimensions. The arrays we have explored above are called 1D arrays.

To declare arrays with additional dimensions, just do as follows:

```c
int map[5][10];
```

The above declares a 5-by-10 array.

To access a cell, it can be done as:

```c
map[4][8] = 2;
```

## Program time

There are mainly 3 time periods of a compiled program:

- Compile time

  During compilation. Compiler catches syntax errors and other compile time errors here. If there is an error, the program will not be built.

- Link time

  The compiler links different bits of compiled code after compilation. In future compilations, the compiler will only compile changed files and run the linker again. Linking error may occur if references to objects are not found, or when compiling for embedded systems, memory allocations exceeded maximum memory allowance.

- Runtime

  This is when the program is running. Unless the program is in **debug mode**, errors here may result in the program crashing without any messages. During debugging, fatal runtime errors will trigger a **breakpoint** and an error message and the erroneous line is displayed.

## Reference materials

https://www-s.acm.illinois.edu/webmonkeys/book/c_guide/


[cppref_printf]: https://en.cppreference.com/w/cpp/io/c/printf
