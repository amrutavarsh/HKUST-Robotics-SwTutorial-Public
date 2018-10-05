# Advanced Tutorial #1 Advance Program Structure and Library
Author: Jason Ieong

Contact: zljieong@connect.ust.hk

[TOC]

```C 
//main.c
#include "uart.h"
main(){
    uart_init(COM1, 115200);
}
``` 
You have been using the functions that are not defined in main.c. You can use them without writing your own one because you are using our library.

Simply speaking, a library consists of source files and header files. Generally, we declare functions and global variables in the header file (.h) and define them in a source file(.c). 

**Right click on the text uart.h and select Open document "uart.h" to open the header.**

### header
```C
//uart.h
#ifndef __UART_H
#define __UART_H

#include "gpio.h"
#include "stm32f10x_usart.h"

extern UARTPort UARTPort1, UARTPort3;
#define COM1 &UARTPort1
#define COM3 &UARTPort3

/**
 * @brief      Initialize the given UART Port
 *
 * @param      uart      The UART Port Handle
 * @param[in]  baudrate  The Baudrate
 */
void uart_init(UARTPort* uart, u32 baudrate);
.
.
.
#endif
```
Header declares function prototype and global variables for the compiler. It is also the common practice to explain what the function does and what arguments it takes.
To modularize and increase readability, similar functions should also be grouped together, but each header should not be too long as well.

When the IDE tries to **compile**, it tries to compiles each **.c(source files)** to **.o(object files)**(which contain object code, e.g.machine code) and the linker will try to link each **".o"** to one executable file. 

A **.h** file is not compiled by itself, but it could be **included** by a source file.

**Including** a header file is equal to **copying the content of the header file** to the corresponding place. 

### declare vs define
Say you defined a variable in a source file you want to use:
```C
//year.c
int year=2018;
```
```C
//main.c
int main(){
    printf("year=%d",year);
}
```
When the **compiler** tries to generate the object file, it treats main.c and year.c separately. In this case, the compiler cannot do its job as it cannot find the variable "year". 
The compiler needs at least needs declaration for it to do its job. Declaring a variable basically tells the compiler that this variable exists somewhere and is not a typo:
```C
//year.c
int year=2018;
```
```C
//main.c
extern int year;
int main(){
    printf("year=%d",year);
}
```
However, it is hard to keep track of these things when you have more variables and many source files, which is why we use header to contain all the declarations:
```C
//year.h
#ifndef __YEAR_H
#define __YEAR_H
extern int year;
#endif
```
```C
//year.c
#include "year.h"
int year=2018;
```
```C
//main.c
#include "year.h"
int main(){
    printf("year=%d",year);
}
```

A **declaration** introduces an identifier and describes its type, be it a type, object, or function. A declaration is **what the compiler needs** to accept references to that identifier. **Memory** is **not** allocated after **declaration**.
A **definition** actually instantiates/implements this identifier. It's what the **linker** needs in order to link references to those entities. **Memory** **is** allocated after **definition**.

A global identifier can be **declared** **as often as you want**, but it must be **defined exactly once** outside a function body. 

When you write a **.h(header file)**, try to keep it minimal and place only the **declaration** in the header file.

**Declaration** in these **.h** can help compiler compile successfully. However, if you **define** something in **.h**, and the header is included in different source files, you may be **defining** the same identifier (as the headers are copied to each source file) and the **linker** will be confused what to do. Sometimes your program can still work even if you **define** something in **.h**, but the behavior may be undefined. 

keep scrolling to see what you should and should not do.

#### The #include guards
```C
#ifndef __UART_H
#define __UART_H
    
#endif
```
Once the header is included, it checks if the token (in this case UART_H ) is defined. Then if it's not defined, it defines it and continues to the rest of the file.

When the code is included again, the first ifndef fails, resulting in a blank file.

That prevents a double declaration of any identifiers such as types, enums, and static variables.

### variable in header and source file
#### defining variable
```C
int x=20;
```
Typing out something like the above one defines x, and a memory will be allocated to the variable "x".
The action of "defining" always "declare" the variable, but "declaring" variable may not be "defining" a variable.

#### Declaring variable and The "extern" keyword
```C
extern int x;
```
"Extern" means *External Linkage*.
Adding the "extern" keyword means that this variable need to be shared between modules. This hint the compiler **not** to allocate memory to the identifier as this action will be done in somewhere else, which means that it is a variable **declaration**. 
You should also **define** this variable in **one and only one .c** file. 
Generally, if there is a variable that you want to share among modules, declare it in the header filer using keyword "extern" and define it in the source file of the same module. 
Otherwise, if the variable is only used in one module, define and use it in the source file and do not declare it in the header.
Working Example:
```C
//room.h
#ifndef INC_ROOM_H_
#define INC_ROOM_H_
//declare these variable in header
extern int smart_car;
extern int robocon;
extern int rov;
#endif /* INC_ROOM_H_ */
```
```C
//room.c
//include its own header
#include "room.h"

//declare the variables
int smart_car=3211;
int robocon=3211;
int rov=3007;
```
```C
//main.c
#include <stdio.h>
#include "room.h"
int main(){
    printf("Smart Car's lab =%d\n",smart_car);
    printf("Robocon's lab =%d\n",robocon);
    printf("Rov's lab =%d\n",rov);
    return 0;
}
```
**Not compiling** example(1):
```C
//year.h
#ifndef INC_YEAR_H_
#define INC_YEAR_H_
int year=2018;
#endif /* INC_YEAR_H_ */
```
```C
//year.c
#include "room.h"
//error(1):First defined here
```
```C
//year.c
#include <stdio.h>
#include "room.h"
int main(){
    printf("%d",year);
    return 0;
}
//error(2):Multiple definition of 'year'
```
"Year" is defined in header, but the header is included in two source file. Therefore, "year" is defined twice.

**Not compiling** example(2):
```C
#include <stdio.h>
extern int year;
int main(){
printf("%d",year);
}
```
"year" is declared but not defined.

**exceptional** case:
```C
int x;
```
By the C standard, This is actually a variable **definition** and an address will be given to it. However, most of the compiler will do us a favor and treat it as a declaration if there is other **definition**. However, try to avoid using this in a header as the compiler or linker have the right to perform an undefined behavior.

### The "Static" keyword
**Don't use static in header unless you know why you are using it!**
"Static" means internal linkage.

"Static" and "Extern" are mutually exclusive (As one mean internal linkage and one mean external linkage).

As "Static" and "Extern" are mutually exclusive, using the static has to be a **definition**.

#### Static variable in a function
Static defined local variables do not lose their value between function calls. In other words, they are global variables but scoped to the local function they are defined in.
```C
void foo(){
    int a = 10;
    //initialised in first funcyion call,bypass afterwords
    static int sa = 10;
    a += 5;
    sa += 5;
    printf("a = %d, sa = %d\n", a, sa);
}
//after the end of function, 
//local variable sa is terminated,
//but static variable retained in memory(for this variable only)

void fun(){
    static int sa=4086;
    printf("sa = %d\n", sa++);
}
//with the same name "sa" but 
//they are local variable of different function;
//so they are using different memory and different value

int main(){
    int i;
    for (i = 0; i < 5; ++i){
        foo();
        fun();
    }
}
```
prints:
```C
a = 15, sa = 15
sa = 4086
a = 15, sa = 20
sa = 4087
a = 15, sa = 25
sa = 4088
a = 15, sa = 30
sa = 4089
a = 15, sa = 35
sa = 4090
```
#### Static variable outside a function
Static variable outside a function is **only visible to the same compiling unit(basically source file)**(internal linkage allowed), and the linker will not link this with other variable with the same name in other file (no external linkage).

Do not mix up **static** and **extern**! If you use **"static"** and **define** a variable in the header, an executable file **can** be generated, **but you will have more then one copy of that variable!**

Bad Example:
```C
//room.h
#ifndef INC_ROOM_H_
#define INC_ROOM_H_
//static definition
static int smart_car=1;
static int robocon=2;
static int rov=3;
void foo1();
void foo2();
#endif /* INC_ROOM_H_ */
```
```C
//room.c
#include "room.h"
void foo1(){
smart_car=3211;
robocon=3211;
rov=3007;
}
void foo2(){
    printf("Smart Car's lab =%d \n",smart_car);
    printf("Robocon's lab =%d \n",robocon);
    printf("Rov's lab =%d \n",rov);
}
```
```C
//main.c
#include <stdio.h>
#include "room.h"
int main(){
    foo1();
    foo2();
    printf("Smart Car's lab =%d \n",smart_car);
    printf("Robocon's lab =%d \n",robocon);
    printf("Rov's lab =%d \n",rov);
    return 0;
}
```
```C
//result:
Smart Car's lab = 3211
Robocon's lab = 3211
Rov's lab = 3007
Smart Car's lab = 1
Robocon's lab = 2
Rov's lab = 3
```
As the header is included,the three variables are **defined** two times, but the "static" keyword tell the linker not to link these variable between object files, so your program **can execute without error**.

However, **two set of separate identity is created**, one for main.c and one for room.c, and even more copies if you include the header in another source file. Changing one will not change the other ones, so this is probably not what you want to do.

**TL;DR: Static is to limit the scope of a variable (to hide this variable from other functions) but a header is used to extend one (to share the variable with other modules). Use static only in the source file on the variable you don't want to share with other modules, and avoid using static variables in the header!** 



### User-defined data type
#### enum
Enumeration (or enum) is a user-defined data type in C. It is mainly used to **assign names to integral constants**, the names make a program easy to read and maintain.
```C
enum flag{constant1, constant2, constant3, ....... };
```
example of defining the data type:
```C
enum room{Smart_Car, Robocon, ROV}; 
```
Where "room" is the name of this data type. If we do not explicitly assign values to enum names, the compiler by default assigns values starting from 0. For example, in the following C program, Smart_Car=0, Robocon=1, ROV=2.
After defining the data type, you can define varlable with this given type.
```C
//main.c
#include <stdio.h>
enum team{Smart_Car, Robocon, Rov};
int main(){
    enum team jason_ieong=Smart_Car;
    enum team joseph_lam=Robocon;
    //print 0
    printf("%d\n",jason_ieong);
    //print 1
    printf("%d\n",joseph_lam);
    enum team daniel_cheung=2;
    if(daniel_cheung==Rov){
    //the word Smart_Car,Robocon and Rov are perserved to be 0,1,2
        daniel_cheung=0;
        //print 0
        printf("%d\n",daniel_cheung);
    }
    return 0;
}
```
**To C++ users: Note that you need to add "enum" before "team".** If you want to skip it, Go to "typedef" to check how to do so.

Two enum names can have same value. For example, in the following C program both ‘Oop’ and ‘Multivariable_Calculus’ have same value 2011. We can also assign values to some name in any order. All unassigned names get value as value of previous name plus one. 
```C
enum courses{Calculus_1=1013, Calculus_2, H_Calculus_1=1023
,H_Calculus_2,Oop=2011,
Wetland_Conservation=2011,Multivariable_Calculus=2011};
//1013,1014,1023,1024,2011,2011,2011
```

#### typedef
typedef is a keyword used in C language to assign alternative names to existing datatypes. Its mostly used with user defined datatypes, when names of the datatypes become slightly complicated to use in programs. 
```C 
typedef <existing_name> <alias_name> 
```
Example:
```C
//stdint.h
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

// stm32f10x.h
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
```
As you can see, both uint32_t and u32 are not standard c type name, and the reason that you can use them is you have included these headers.
```C
//all lines mean the same thing if you included our library
unsigned short int x;
uint16_t  x;
u16 x;
```
In practice, we often use it to shorten some name, such as enum.
```C
//Too long(for c++ users)
enum teamname{Smart_Car, Robocon, Rov};
int main(){
    enum teamname jason_ieong=Smart_Car;
}

//now "team" means the same as "enum teamname"
//in orther word, "team" is the alias of type "enum teamname"
enum teamname{Smart_Car, Robocon, Rov};
typedef enum teamname team;
int main(){
    //note that you don't have to type "enum"
    team jason_ieong=Smart_Car;
}

//even lazier
//"team" means the same as "enum teamname"
//in orther word, "team" is the alias of type "enum teamname"
typedef enum teamname{Smart_Car, Robocon, Rov}team;
int main(){
    //note that you don't have to type "enum"
    team jason_ieong=Smart_Car;
}

//When you are too lazy to type the original name
//"team" is the alias of this anonymous type "enum {Smart_Car, Robocon, Rov}"
typedef enum {Smart_Car, Robocon, Rov}team;
int main(){
    //note that you don't have to type "enum"
    team jason_ieong=Smart_Car;
}
```
#### example of enum in our code
```C
//button.h

//defines Button
typedef enum {
    BUTTON1,
    BUTTON2,
    BUTTON3,
} Button;

//declare the function prototype to take an enum button as the argument and return u8.
u8 button_pressed(Button button);
```
"Button" is now the type name, so the following are equivalent:
```C
    Button x=BUTTON1;
    button_pressed(x);
    
    button_pressed(BUTTON1);

    button_pressed(0);
```

#### struct
group items of possibly different types into a single type.
```C
struct tag_name {
   type member1;
   type member2;
   /** 
    * declare as many members as desired, but the 
    * entire structure size must be known to the compiler. 
    */
};
```
example:
```C
struct point{
int x;
int y;
int z;
}
int main(){
    struct point p1;
}
```
Initializing values while declaring data type is not legal:
```C
//this is not c++11, so not allowed
struct point{
int x=233;
int y=244;
int z=234;
}
```
However, Initializing values while defining data type with "{}" is allowed, but this can only be used while Initializing. 
```C
struct point{
int x;
int y;
int z;
}
int main(){
    struct point p1={23,42,-244};//allowed
    struct point p2={42,-42,-31};//allowed
    p1={23,42,-244};//not allowed
}
```
access or assign the values by using "."

```C
struct point{
int x;
int y;
int z;
}
int main(){
    struct point p1={23,42,-244};
    struct point p2={42,-42,-31};
    struct point p3=p1;
    //23,42,-244
    printf("%d,%d,%d\n",p1.x,p1.y,p1.z);
    p1.x=p2.x-42;
    p1.y=p2.y+42;
    p1.z=(p2.z/31)+1;
    //0,0,0
    printf("%d,%d,%d\n",p1.x,p1.y,p1.z);
    p1=p3;
    //23,42,-244
    printf("%d,%d,%d\n",p1.x,p1.y,p1.z);
}
```

As enum, we often shorten stuff by using typedef.
```C
typedef struct {
int x;
int y;
int z;
}point;
int main(){
    point p1;
}
```
### pointer of the variable
** **important** **
**Pointer is not as easy for beginners so we tried to alter the library so that in most cases you don't have to use the pointer directly. Approach a senior if you face any problem.** 

**This part is just for your reference and you do not have to understand all of this part.**

**Whenever our provided function in library wants you to pass a pointer, we should have defined some identifier for you to pass it into it.**

In C, everything has a memory location. A pointer is a variable whose **value** is the **address** of **another variable**, i.e., direct address of the memory location. When you see **\*** or **&** that is not used as a logic or a multiplication operator, a pointer is most likely involved.

One of the usages of the pointer is to avoid passing the real variable around and declare global variables. In C, all function calls are "pass by value", which means a new copy of the variable is passed as the argument which will be terminated after the function return. Editing this copy will not apply to the original one, and creating a copy may sometime be time-consuming. On the other hand, if we pass the memory location, a copy of the pointer(which should be smaller in memory size) 


The type of a pointer is base on the type of variable it points to. For example, a pointer that point to an integer is an integer pointer. The notation is given by the original type plus a "*" after it. Adding "&" before a variable gives the address of the variable.
```C
int* x_pointer;//a integer pointer
int x=23;
x_pointer=&x;//x_pointer now stores the address of x
```
#### passing struct into function
It is perfectly fine to pass and return a struct **if the struct does not contain a pointer**. However, you have to return the struct variable or changes may be thrown away as c passes by value.
```C
#include <stdio.h>
//#include "../inc/header.h"
typedef struct{
    int x;
    int y;
}point;
point fun1(point p){
    p.x++;
    p.y++;
    return p;
}
int main(){
    point p1={0,0};
    //changes are applied to a local copy of p1,
    //local copy thrown away after the end of fun1 
    fun1(p1);
    printf("%d, %d \n",p1.x,p1.y);
    //changes are applied to a local copy of p1,
    //local copy assigned to original before being thrown away 
    p1=fun1(p1);
    printf("%d, %d \n",p1.x,p1.y);
}
```
On the other hand, **struct that has pointers as the member is not as safe to pass directly**. Passing the pointer to that struct is the safer way, but the details are a bit too complicated to be covered here.
**There are some functions we defined that you need to pass in a struct pointer (as an address is most likely needed when the hardware is involved), but we should have defined some identifier for you to skip use as their argument.**
#### example of struct and pointer in our code
```C
//gpio.h
typedef struct {
    GPIO_TypeDef* port;
    u16 pin;
} GPIOPin;

static const GPIOPin
    /*** GPIOA ***/
    PC1 = {GPIOC, GPIO_Pin_1},
    PC2 = {GPIOC, GPIO_Pin_2};
    
typedef const GPIOPin* LED;
    
#define LED1 &PC1
#define LED2 &PC2

/**
 * @brief      Turn on the LED
 *
 * @param[in]  led   The LED
 */
void led_on(LED led);
```
**GPIOPin** is a type of struct which contains a **GPIO_TypeDef\*** and a **u16** pin, where both of them refer to some hardware memory.
**PC1,PC2** are some const **GPIOPin**.
**LED** is a alternative name for **const GPIOPin\***
**void led_on(LED led)** is a function that take a variable with type **LED** as argument and have no return.
We defined LED1 and LED2 so that you don't have to use pointer by yourself.

So all the above equivalent:
```C
led_on(LED1);
led_on(&PC1);

const GPIOPin A={GPIOC, GPIO_Pin_1};
led_on(&A);
LED B=&A;
led_on(B);
```
### function in header and source file
The declaration and definition of a function could also be separated. Declaring all function before defining one is the common practice.

This is a working program:
```C
#include <stdio.h>
const char * fun2(void){
    return "gg";
}
void fun1(void){
    printf(fun2());
}
int main(void) {
    fun1();
    return 0;
}
//output "gg"
```
This is a **not** working program
```C
#include <stdio.h>
//const char * fun2();
void fun1(void){
    printf(fun2());
}
const char * fun2(void){
    return "gg";
}
int main(void) {
    fun1();
    return 0;
}
/** 
 * prog.c: In function ‘fun1’:
 *prog.c:5:9: warning: implicit declaration of function ‘fun2’ [-Wimplicit-function-declaration]
 *  printf(fun2());
         ^~~~
 *prog.c:5:9: warning: passing argument 1 of ‘printf’ makes pointer from integer without a cast [-Wint-conversion]
 *I n file included from prog.c:2:0:
 * /usr/include/stdio.h:364:12: note: expected ‘const char * restrict’ but argument is of type ‘int’
 *extern int printf (const char *__restrict __format, ...);
 *            ^~~~~~
 *prog.c: At top level:
 *prog.c:7:14: error: conflicting types for ‘fun2’
 const char * fun2(void){
 *              ^~~~
 *prog.c:5:9: note: previous implicit declaration of ‘fun2’ was here
 *  printf(fun2());
 *         ^~~~
 */
```
In the second program, the prototype of fun2() is not declared. C++ language forbids any attempt of using non-declared function, C may sometimes allows you to compile, but the behavior may be undefined. 
The following program will compile in old c version but not after c99:
```C
int main() {
  int i = fun1(5); 
  // work in C89/90
  return 0;
}

int fun1(int i) {
  return i;
}
```
The above program could work if you place the function fun1() above main(), but sometime it is not possible, such as fun1() calling fun2() but fun2() is also calling fun1():
```C
#include <stdio.h>
int fun1(int i) {
  return i?fun2(0):0;
}
int fun2(int i) {
  return i?fun1(0):1;
}
int main() {
  printf("%d",fun1(1)); 
  return 0;
}
```
In the above case, placing either function first will not be compiling. This is one of the reason why we need to seperate declaring and defining a function.
```C
#include <stdio.h>
int fun1(int);
int fun2(int);
int fun1(int i) {
  return i?fun2(0):0;
}
int fun2(int i) {
  return i?fun1(0):1;
}
int main() {
  printf("%d",fun1(1)); 
  return 0;
}
```
So basically typing out the same function without its body will declare this function and assign an address location to the function such that the correct function address will be accessed when it is called.

When a function is declared, the **prototype** is needed, which is the function return type and the data types of parameters.

function are built in external linkage, so you do **not** have to add **"extern"**
```C
void uart_init(UARTPort*, u32);
```
It is also possible to add some name for the variable to increase readability.
```C
void uart_init(UARTPort* uart, u32 baudrate);
```
In practice, we declare the function in the header and define them in one and only one source file with in the same module. 
```C
//fun.h
int fun1(int);
int fun2(int);
```
```C
//fun.c
#include "fun.h"
int fun1(int i) {
  return i?fun2(0):0;
}
int fun2(int i) {
  return i?fun1(0):1;
}
```
```C
#include <stdio.h>
#include "fun.h"
int main() {
  printf("%d",fun1(1)); 
  return 0;
}
```

Same as declaring a variable, this allows the compiler to know that the function will be defined somewhere. As the prototype is given, the compiler can also throw an error if you are using a wrong type. 

## keywords
### "extern" function
function declartion is built in "extern", so adding it or not does not make a different.

### "static" function
The original usage of the static function is to limit the scope of a function in a compiling unit, which is mostly a good idea, so consider using it in when defining a function in a source file which is not expected to be called by other modules. 
As defining "static" variable in the header, the compiler will allower you to defining static functions in a header. However, many copies of such function will be created(for each source file that included the header). So avoid doing so or only use in on small function if necessary. 

### "inline" function
**Behavior of inline in GCC is different from what the standard C99 suggested. As it is often just used a small performance boost, avoid using it.** (as we have done most hardware related functions that need "inline" for you.)

"Inline" may sometimes be used to reduce the execution time of a program. This hit compiler to make the function inline and replace those function definition wherever those are being called.
The compiler replaces the definition of inline functions at compile time instead of referring function definition at runtime. 
This is just a suggestion to the compiler to make the function inline. If the function is big (in term of executable instruction etc) then, the compiler can ignore the “inline” request and treat the function as a normal function.
```C
#include <stdio.h>
inline void foo() 
{
  printf(" In foo\n"); 
}
void main()
{
  foo();
}
```
may be compiled(deceided by compiler) as:
```C
#include <stdio.h>
vint main()
{
  printf(" In foo\n");
}
```
Yous should be able to define an "inline" function in the header according to C standard. However, if the GCC compiler decides not to inline your function, a definition of the function will not be given, and the linker will not be able to find a definition of the function.
So in practice, either use "static inline" (The "inline" action will apply to each source file, but you will also have a copy of the definition of this function is each object file, so don't do it when the function is large) or "extern inline" to declare it in header and define it in one source file (The "inline" action will only apply to the same source file and there will still be a global function definition for another module to call).

### function pointer
Everything has a memory location in C, so as a function, therefore function can also have a pointer. In our case, it will be useful to set up an interrupt. I will just provide the syntax here or it will go too deep, and normally you don't have to use it so try to avoid except setting up the interrupt.

```C
//A normal funtion declartion named foo
int foo (double,double,double);
```
```C
//A funtion pointer named foo, can store the address of function with the same prototype as foo
int(* foo_ptr) (double,double,double);
    
//define function_ptr the be type of function pointer with int return and three double as arguments
typedef int (*function_ptr)(double,double,double);

```
example:
```C
double vector_length(double x, double y) {
    return sqrt(x * x + y * y);
}

int main() {
    //A funtion pointer named foo, can store the address of function with the same prototype as foo
    double(* vector_length_ptr) (double,double);
    typedef double (*function_ptr)(double,double);

    //store the address of foo
    vector_length_ptr = &vector_length;
    function_ptr fun1 = vector_length_ptr;
    //call, old syntax
    printf("%f\n",(*vector_length_ptr)(3, 4));
    //call, new syntax
    printf("%f\n",vector_length_ptr(3, 4));

   //cal, old syntax
    printf("%f\n",(*fun1)(3, 4));
    //call, new syntax
    printf("%f\n",fun1(3, 4));
}
```
However, as the only usage of function pointer for you is to set up the interupt, all you need to do is:
1. define a function
```C
void foo(const u8 received){
    return;
}
```
2. add a "&" before the function and pass it to the given function
```C
uart_rx_init(COM1,&foo);
```
3. The function will be called once the signal triggered the board.

### **basic principle of writing header and source file**
>try to follow these rules or *@Daniel* will be mad at you 

**Rule #1. Each module with its .h and .c file should correspond to a clear piece of functionality.**

**Rule #2. Always use “include guards” in a header file.**

**Rule #3. All of the declarations needed to use a module must appear in its header file, and this file is always used to access the module.**

**Rule #4. The header file contains only declarations, and is included by the .c file for the module.**

**Rule #5. Set up program-wide global variables with an extern declaration in the header file, and a defining declaration in the .c file.**

**Rule #6. Keep a module’s internal declarations out of the header file.**

**Rule #7. Every header file A.h should #include every other header file that A.h requires to compile correctly, but no more.**

**Rule #8. If an incomplete declaration of a structure type X will do, use it instead of #including its header X.h.**

**Rule #9. The content of a header file should compile correctly by itself.**

Most of the already rules are already covered above. check http://umich.edu/~eecs381/handouts/CHeaderFileGuidelines.pdf
for more details.







