Author: Daniel Cheung

ITSC: dcheungaa

# Classwork

## 1. Modifying hello world

Copy this code into your `main.c` in your IDE:

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

#### Instructions

- Change the program so that it outputs your name.

## 2. Swapping contents

```c
#include <stdio.h>

int main() {
    float cup_x = 3.4f;
    float cup_y = 2.7f;
    //Your code starts here
    
    //Your code ends here
    printf("Cup X now contains %fml.", cup_x);
    return 0;
}
```

#### Instructions

- Use an additional container to swap the contents of `cup_x` and `cup_y` **without** typing out any literals in your code.

## 3. Discount Eligibility

 ```c
#include <stdio.h>
#include <stdbool.h>

int main() {
    //Change the code below
    int age = 45;
    bool has_card = false;
    
    printf("You are young enough to have the discount.");
    printf("You are old enough to have the discount.");
    printf("You are not eligible for the discount!");
    return 0;
}
 ```

#### Instructions

- **First part**

  Children with age 12- and elderlies with age 65+ are eligible for a discount. Create a program that can output different messages depending on the `age` variable. Change the code so that it displays different messages depending on the initialized `age` value.
  
- **Second part**

  When a person has "the card" and that they are elderly, give them a discount, otherwise, they are not eligible. Use logical operators to construct a condition to check this situation.

##  4. Clap-7

```c
#include <stdio.h>
#include <stdbool.h>

int main() {
    //Change the code below
    printf("*clap*\n");
    printf("%d\n", 1);
    return 0;
}
```

#### Instruction

- **First part**
  Make a program using for loop that counts from 1-100, then it outputs the number if it is indivisible by 7, and outputs "\*clap\*" when divisible by 7. Expected output:

  ```
  1
  2
  3
  4
  5
  6
  *clap*
  8
  ...
  ```

- **Second part**

  Update the code so that it `*stomp*` when the number is a multiple of `5`, and `*click*` when a multiple of `3`.

## 5. Area of circle

#### Instruction

- **First part**

  Prompt the user to input a radius of a circle by **asking them to do so**. Then read a floating point number as the radius, then print the area of the circle with the formula. Expected output:

  ```
  Please enter r: 3
  Area of circle = 3.141593 * 3.000000 = 9.424779
  ```

- **Second part**

  Construct a function called `circleArea()` to calculate the area of circle in floating point number such that the following code can work. Modify the following code:

  ```c
  #include <stdio.h>
  #include <stdbool.h>
  
  int main() {
      printf("%f", circleArea(5.0f));
      return 0;
  }
  ```

## 6. Fibonacci sequence

#### Instruction

- Generate the first 100 items of the Fibonacci sequence and store them in an array. It starts with 1, 1, 2, 3, 5, 8, ...

  The pattern is pretty simple:

  ```
  1
  1
  1 + 1 = 2
  1 + 2 = 3
  2 + 3 = 5
  3 + 5 = 8
  ...
  ```

  Then output: `"Select an item from the array: "` to prompt the user for an integer input for the index, then retrieve that item with that index from your generated array and output that to the user. Repeat this interaction forever. Expected output:

  ```
  Select an item from the array: 4
  5
  Select an item from the array: 5
  8
  Select an item from the array: 0
  1
  ...
  ```

## 7. Triangle

#### Instruction

- Initialize an integer `height` and initialize that to some integer. Generate a triangle made with asterisks using loops. The triangle grows 1 outwards on both sides horizontally after each level.

#### Expected output

When `height` is `5`, the following is the console output.

```
    *
   ***
  *****
 *******
*********

```

