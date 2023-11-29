# C Programming Daily Problem

<style>
h1:before {content: unset;}
h2:before {content: unset;}
h3:before {content: unset;}
h4:before {content: unset;}
h5:before {content: unset;}
</style>

为了让同学们适应期末考试，每日一题的题面都将使用英文描述。

## November

### 「29」Soyo Size

On a 64-bit machine, the output of the following code fragment is **\_\_**.

```c
void print_soyo(char soyo[]) {
    printf("%lu\n", sizeof(soyo));
}

int main() {
    char soyo[] = "Soyosan\0Love";
    print_soyo(soyo);
    return 0;
}
```

<div style="display: flex">
    <div style="width: 100%">A. 13</div>
    <div style="width: 100%">B. 7</div>
    <div style="width: 100%">C. 8</div>
    <div style="width: 100%">D. 4</div>
</div>


<!-- prettier-ignore-start -->
??? note "Answer"
    C.

    When an array type is used in a function parameter list, it is transformed to the corresponding pointer type: `int f(int a[])` and `int f(int *a)` declare the same function. See [cppreference-Array to pointer conversion](https://en.cppreference.com/w/c/language/array#Array_to_pointer_conversion) for more information.

    So the parameter `soyo` in function `print_soyo` is actually a pointer, and the size of a pointer is variable depending on the architecture. On a 64-bit machine, the size of a pointer is 8 bytes, and on a 32-bit machine, the size of a pointer is 4 bytes. Therefore, the output of this program is `8`.
<!-- prettier-ignore-end -->

> 供题人：苏煜程

### 「28」 Naughty Pointer

The following code fragment prints out **\_\_**.

```c
int a[2][3] = {1, 2, 3, 4, 5, 6};
int(*p)[3] = *a + 1;
printf("%d", *(*(p + 1) + 1));
```

<!-- prettier-ignore-start -->
??? note "Answer"

    `6`.

    Obviously, the type of `p` is declared as `int (*)[3]`, which is a pointer to an array of 3 integers. We know that in the initializer, `a` will be converted to a pointer to its first element, so `*a` is equivalent to `a[0]`, which is an array of 3 integers. Then, the type of `*a` will be converted from `int [3]` to `int *` again. Therefore, adding 1 to `*a` will make it point to the next integer, which is `a[0][1]`.

    You may notice that the type of `*a + 1` is not the same as pointer `p`. In fact, its type is casted to `int (*)[3]` when assigned to `p`. Trying to figure out the "meaning" of `p` now may become more difficult. Instead, just remember the value of pointer `p` is the address of `a[0][1]`.

    Now consider the expression `*(*(p + 1) + 1)`. First, since the type of `p` is `int (*)[3]`, adding 1 to `p` will make it point to the next array of 3 integers; that is to say, the value of `p` will be the address of the third integer after `a[0][1]`, which is `a[1][1]`. So `*(p + 1)` is just equivalent to `&a[1][1]`. Then, adding 1 to `*(p + 1)` will make it point to the next integer, which is `a[1][2]`. Thus, the value of `*(*(p + 1) + 1)` is `a[1][2]`, which is 6.
<!-- prettier-ignore-end -->

> 供题人：孙兆江

### 「27」 I Love `scanf`!

After entering the following inputs, does the program operate normally? If it does, what should be the output?

```c
int a;
char c1, c2;
char s[7];
scanf("%d%c %c%s\n", &a, &c1, &c2, s);
printf("%d#%c#%c#%s", a, c1, c2, s);
```

```bash
#input: there is no space after the last character
20231127
 ckc-agc
daily_problem
```
<!-- prettier-ignore-start -->
??? note "Answer"

    The program operates normally and the output is:

    ```text
    20231127#
    #c#kc-agc
    ```

    The `scanf` function reads input from the standard input stream, which is usually the keyboard. The format string of `scanf` is `"%d%c %c%s\n"`. The first `%d` matches the integer `20231127`, the second `%c` matches the character `'\n'` because `%c` won't miss any character including `' '` and `'\n'`. The space in formatting string will ignore every blank character, so the third `%c` matches the character `'c'`, and the fourth `%s` matches the string `"kc-agc"`, whose length is 7. When you print `\n` after line2,  `scanf` will not stop, because `'\n'` in formatting string will ignore every blank character. So until you enter a non-blank character and use enter to send it to the program from buffer, `scanf` will stop.
<!-- prettier-ignore-end -->

> 供题人：胡育玮

### 「26」 Broken `strcpy()`

Does this `strcpy()` implementation do its job?

```c
void my_strcpy(char *s, const char *t) {
    do {
        *s++ = *t++;
    } while (*t);
}
```

<!-- prettier-ignore-start -->
??? note "Answer"

    No, it's broken. This implementation does not terminate the string pointed to by `s`. To correctly copy a string, the character used in assignment must be the same character used in loop condition.

    What does that mean? Suppose `t = "Hello"`, then:

    - `*t` is `'H'`, and is assigned to `*s`.
    - `s` and `t` increment.
    - `*t`, now being `'e'`, is used to evaluate the `while` condition.
    - ... this process repeats until `t` points to `'o'` and is assigned to `*s`.
    - `s` and `t` increment.
    - `*t`, now being `'\0'`, is used to evaluate the `while` condition. The loop ends.

    See the problem? The null byte `'\0'` is not copied to `s`, therefore it's left unterminated. Any attempt to use `s` as a string will result in undefined behavior.

    Worse still, what happens if `t` is an empty string i.e. `t = ""`?

    - `'\0'` is assigned to `*s`.
    - `s` and `t` increment. `t` gets past its end.
    - Now we have a memory out-of-bounds. Accessing `*t` is undefined behavior.
    - And it keeps copying garbage values until some arbitrary `'\0'`, or it goes too far and causes a segmentation fault.
<!-- prettier-ignore-end -->

> 供题人：李英琦

### 「25」 I Love Strcat!

The following code fragment prints out **\_\_**.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_strcat(char *s1, char *s2, char *s3) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    s3 = malloc(len1 + len2 + 1);
    memcpy(s3, s1, len1);
    memcpy(s3 + len1, s2, len2);
    s3[len1 + len2] = 0;
    printf("%s\n", s3);
}

int main() {
    char s1[] = "I love ";
    char s2[] = "cats!";
    char s3[] = "";
    my_strcat(s1, s2, s3);
    printf("%s\n", s3);
}
```

A. `I love cats!\n\n`

B. `\n\n`

C. `\nI love cats!\n`

D. `I love cats!\nI love cats!\n`

<!-- prettier-ignore-start -->
??? note "Answer"

    `A`.

    The function `my_strcat` is supposed to concatenate `s1` and `s2` and store the result in `s3`. However, the function does not work as expected. The problem lies in the line `s3 = malloc(len1 + len2 + 1);`. The function `my_strcat` takes `s3` as a parameter, which is a pointer to a `char` array. When the function is called, the value of `s3` is copied to the function's local variable `s3`. Therefore, the `malloc` function allocates memory for the local variable `s3`, not the original `s3` in `main`. The memory allocated for the local variable `s3` is not used after the function returns, so it is a memory leak. The original `s3` in `main` is not modified, so it is still an empty string.

    You may think that the problem can be solved by simply deleting the line `s3 = malloc(len1 + len2 + 1);`. However, this will cause another problem. `s3` is initialized as an empty string, which means that it is a pointer to a `char` array with only one element, the null character `\0`. The memory allocated for `s3` is not enough to store the concatenated string. Therefore, this will cause a buffer overflow.

<!-- prettier-ignore-end -->

> 供题人：梅敏炫

### 「24」 Pointer Array

The output of the following code fragment is **\_\_**.

```c
#include <stdio.h>
int main()
{
	char* a[] = { "the","one","is","unknown" };
	char** pa = a;
	pa++;
	printf("%c%s\n", *(*pa + 1), *pa);
	return 0;
}
```

<div style="display: flex">
    <div style="width: 100%">A. none</div>
    <div style="width: 100%">B. tone</div>
    <div style="width: 100%">C. tthe</div>
    <div style="width: 100%">D. nis</div>
</div>

<!-- prettier-ignore-start -->
??? note "Answer"

    A.

    `a[]` is an array of pointers, which stores the addresses of three strings, and `pa` points to the address of the first element of `a`, as shown below:

    ![](24daily_nov24.jpg)

    Pointer operations take precedence over addition, so `*(*pa + 1)` equals to `n`.

    In summary, the code fragment prints out `none`.
<!-- prettier-ignore-end -->

> 供题人：华展辉

### 「23」 `typedef` and String

The preprocessing of this program is as follows：

```c
#define MAX_SIZE 10000

typedef struct Bookcase{
    char* book[10];
} *PtrToBookcase;

typedef PtrToBookcase Lib_data_base[MAX_SIZE];
```

After executing the following code fragment, the output should be **\_\_**.

```c
Lib_data_base library;
*(library) = (PtrToBookcase)malloc(sizeof(struct Bookcase));
(*library)->book[0] = "C Programming Book";
for(int i = 0; i < 3; i++)
    printf("%.2s\n", library[0]->book[0] + strlen(library[0]->book[0]) - i - 1));
free(library[0]);
```

<!-- prettier-ignore-start -->
??? note "Answer"

    Output is:

    ```text
    k
    ok
    oo
    ```

    The address pointed to by `library[0]->book[0]` plus `(strlen(library[0]->book[0])-i-1) * sizeof(char)` will be eventually passed to `%.2s` and placed into the output stream. 
    
    Thus, when `i=0`, `i=1`, and `i=2`, the strings passed to `%.2s` are "k\0", "ok\0", and "ook\0", respectively. Among these, the length of the third string "ook\0" exceeds 2, so only the first two characters "oo" will be output. 

    This question involves multiple concepts, primarily focusing on both the proper usage of `typedef` and issues related to pointer output with `char*` in C. The analysis will be divided into two parts: `typedef` and `char*`. If you are already familiar with `typedef`, you can directly skip this section.

    ??? note "`typedef`"
    
        In the C language, `typedef` is used to create new names for existing data types.
        
        When using `typedef`, errors can occur in the specification of its usage. One common misunderstanding is to interpret `typedef (type_name) (new_name)`, which is correct only in a few cases, such as `typedef int Integer`.

        However, the correct understanding should be: if you need to redefine a type, first write the declaration statement of that type: `type variable_name`, then replace `variable_name` with the alias you want, and finally add `typedef` in front of the entire statement. 
        
        For example, after `int array[10]`, where the type of the variable `array` is `int [10]`, you can rename `array` to the alias `IntegerList` and add `typedef` at the front, resulting in `typedef int IntegerList[10]`.

        After this, you can directly use the alias `IntegerList` to define variables of type `int [10]`, such as `IntegerList a;`, which is equivalent to decelaration: `int a[10]`.

        Returning to the question, let's analyze the two `typedef` statements in the question. 

        The first one creates an alias for a structure variable. If we initially want to declare a variable of type `struct Bookcase*`, we would write it like this:

        ```c
        struct Bookcase {
            char* book[10];
        } *Bookcase1;
        ```

        Following the rules of `typedef`, replace the variable name `Bookcase1` with the alias `PtrToBookcase` and add `typedef` at the beginning of the entire statement, resulting in the form seen in the question:

        ```c
        typedef struct Bookcase {
            char* book[10];
        } *PtrToBookcase;
        ```

        This statement means giving an alias, `PtrToBookcase`, to the type `struct Bookcase*`.

        The second `typedef` is very similar to the example we mentioned earlier, `typedef int IntegerList[10];`. 
        It first declares `PtrToBookcase Ptr1[MAX_SIZE]`, then replaces the variable name `Ptr1` with the alias `Lib_data_base`, and adds `typedef` at the front.
        Therefore, its meaning is to give an alias, `Lib_data_base`, to the type `PtrToBookcase [MAX_SIZE]`. 
        Consequently, the subsequent `Lib_data_base library` actually creates an array of `PtrToBookcase`, named `library`, with `MAX_SIZE` elements.

    ??? note "`char*`"

        After understanding `typedef`, let's now explore the issue related to string output in this program. 
        There are two potentially confusing elements in this code: `%.2s` and `library[0]->book[0]+strlen(library[0]->book[0])-i-1`.

        `%.2s` is relatively straightforward: It is used to control the output of strings. `%s` would directly output the characters stored at the memory location pointed to by a `char*` type pointer and all characters in consecutive memory until encountering the '\0' character. 
        The additional `.2` in `%.2s` is used to limit the length of the output string. If the string length is less than or equal to 2, it will be output normally. If it exceeds 2, only the first two characters will be output.

        `library[0]->book[0]+strlen(library[0]->book[0])-i-1` involves operations on a `char*` type pointer. 
        `library[0]->book[0]` is a `char*` type pointer. Adding `n` to it effectively shifts the pointer to a position `n * sizeof(char)` bytes forward from the current address. Subtracting `n` from it shifts the pointer to a position `n * sizeof(char)` bytes backward from the current address. 

<!-- prettier-ignore-end -->

> 供题人：姚雪涛

## October

### 「29」 Precedence

The output of the following code fragment is **\_\_**.

```c
int x = 1, y = 2;
printf("%d\n", y << 1 - 1 > 2 || !(x++ > --y) ? x : y);
```

<!-- prettier-ignore-start -->
??? note "Answer"

    The answer is 2.

    Several operators appear in this problem, listed in order of operation precedence from top to bottom:

    * *Suffix increacement and decreacement:* `a++`
    * *Logical NOT:* `!`
    * *Prefix increacement and decreacement:* `--a`
    * *Subtraction:* `-`
    * *Bitwise left shift:* `<<`
    * *Comparison:* `<`, `>`
    * *Logical OR:* `||`
    * *Ternary conditional:* `a ? b : c`
    
    See more about operator precedence at [cppreference.com](https://en.cppreference.com/w/cpp/language/operator_precedence).
    
    Knowing this, let's break down the expression from the innermost to the outermost parts.
    
    1. `1 - 1` evaluates to 0, and `y << 0` has the value 2.
    2. `2 > 2` is false, thus the value of the Logical OR depends on the right part.
    3. `x++` assigns the value of `x` (1) to the expression and then increments `x` by 1, making `x` equal to 2.
    4. `--y` decreases the value of `y` (2) by 1, so `y` becomes 1.
    5. `x++ > --y` is equivalent to 1 > 1, which is false, so this part equals 0.
    6. `!(x++ > --y)` negates false, so this part equals 1, making the condition of the Ternary conditional true.
    7. Since `x` has the value of 2 and `y` has the value of 1, the output will be 2.
<!-- prettier-ignore-end -->

> 供题人：徐若禺

### 「27」 Or in `switch`

What will happen when compiling and executing the following code fragment with input `5`?

```c
char ch;
scanf("%c", &ch);
switch (ch) {
    case 0 || 2 || 4 || 6 || 8:
        printf("even digit ");
    case 1 || 3 || 5 || 7 || 9:
        printf("odd digit ");
    default:
        printf("not a digit ");
}
```

A. It will print `odd digit `.

B. It will print `odd digit not a digit`.

C. It will print `not a digit`.

D. It cannot be compiled.

<!-- prettier-ignore-start -->
??? note "Answer"

    `D`.

    The compiler will tell you that `case label value has already appeared in this switch`.  
    There are many problems in this code fragment, and the most important one is that `0 || 2 || 4 || 6 || 8` will not behave as expected in `case` statement. It will be evaluated as `1` because `0 || 2 || 4 || 6 || 8` is equivalent to `((((0 || 2) || 4) || 6) || 8)`. The result of `0 || 2` is `1`, so the result of `0 || 2 || 4` is `1`, and so on. Therefore, the `case` statement will be evaluated as `case 1`. The same problem exists in `case 1 || 3 || 5 || 7 || 9`, which will also be evaluated as `case 1`.  
    The correct way to write this code fragment is:

    ```c
    char ch;
    scanf("%c", &ch);
    switch (ch) {
        case '0': case '2': case '4': case '6': case '8':
            printf("even digit "); break;
        case '1': case '3': case '5': case '7': case '9':
            printf("odd digit "); break;
        default:
            printf("not a digit ");
    }
    ```

    For more information about `switch` statement, see [cppreference-Switch statement](https://en.cppreference.com/w/c/language/switch).
<!-- prettier-ignore-end -->

> 供题人：郑俊达

### 「26」 Bitwize Operator

Which of the following options can achieve a swapping effect for `pair(*,*)`?
Note that `^` represents `XOR` operation. For binary numbers, `0 XOR 0 = 0`, `0 XOR 1 = 1`, `1 XOR 0 = 1`, `1 XOR 1 = 0`.

A. `(x, y)`: `x ^= y ^= x ^= y;`

B. `(a[x], a[y])`: `a[x] ^= a[y] ^= a[x] ^= a[y];`

C. `(x, y)`: `x -= y += x -= y;`

D. `(a[x], a[y])`: `a[x] -= a[y] += a[x] -= a[y];`

<!-- prettier-ignore-start -->
??? note "Answer"

    `A`.

    - `B` will always be `0` when `x==y`. 
    - `C` and `D` is not logically correct.

<!-- prettier-ignore-end -->

> 供题人：程昕宇

### 「25」 Eternal Binary-Search

After executing the following code fragment, the output should be **\_\_**.

```c
int ok[50000];
for (int i = 0; i <= 19268; ++i) ok[i] = 1;
for (int i = 19269; i <= 49999; ++i) ok[i] = 0;
int l = 0, r = 49999;
while (l < r){
    int mid = (l + r) / 2;
    if (ok[mid]) l = mid;
    else r = mid - 1;
}
printf ("the ok_maximum is %d", l);
```

<!-- prettier-ignore-start -->
??? note "Answer"

    In fact, this code fragment has no output because it is stuck in an endless loop. Let's see what happens: At first the code executes perfectly, `l` increasing and `r` decreasing constantly. However, when the value of `r-l` reduce to `1`, the value of `l` and `r` will never change again. That's because `mid` equals to `l` and `ok[mid]` is `true` (Think about it. why?), so `l = mid` will be execute, again and again with no value change.

    Binary Search is a very simple, common and useful algorithm that you will learn soon. However, when using Binary Search, it is easy to write a wrong code. It is said that only 10% of the programmers can write a exactly correct code. Hence, you need to pay special attention to this algorithm. A small change can possibly change the code correctness. For example, modifying the `int mid = (l + r) / 2;` to `int mid = (l + r + 1) / 2;` makes the code correct.

<!-- prettier-ignore-end -->

> 供题人：郑涵文

### 「24」 Nested `switch`, Confusing `default` and `break`

After executing the following code fragment, the output should be **\_\_**.

```c
int x = 1, y = 1;
switch (x) {
    case 1:
        switch (y) {
            default:
                printf("three ");
            case 1:
                printf("one ");
            case 2:
                printf("two ");
                break;
        }
    case 2: case 3:
        printf("four ");
        break;
    default:
        printf("five ");
}
```

<!-- prettier-ignore-start -->
??? note "Answer"

    `one two four`

    The syntax of `switch` statement is:

    ```c
    switch (expression) {
        case constant-expression:
            statements
        case constant-expression:
            statements
        default:
            statements
    }
    ```

    The `expression` must have an integral or enumerated type, or be of a class type in which the class has a single conversion function to an integral or enumerated type. The `constant-expression` for each `case` must be a constant expression of the same type as the expression, and no two of the constant expressions associated with the same `switch` statement shall have the same value after conversion.

    The `switch` statement evaluates `expression`, then looks for the `case` constant-expression whose value is equal to the value of `expression` (after conversion). If such a `case` is found, the statements following that `case` are executed **until a `break` statement is encountered**. If no `case` is found whose value is equal to the value of the expression, and if there is a `default` label, the statements following the `default` label are executed. Otherwise, the statements of the `switch` statement are skipped.

    If some `case` labels are not followed by `break` statements, the execution of the `switch` statement falls through to the next `case` label. You can use this behavior to execute multiple statements for a particular `case` label or to execute statements for more than one `case` label.

<!-- prettier-ignore-end -->

> 供题人：朱宝林

### 「23」 Prefix OR Postfix

After executing the following code fragment, the value of variable `x` is **\_\_**.

```c
int x;
for (x = 0; x-- < 9 || ++x < 10; ++x) {
    x++;
}
```

<!-- prettier-ignore-start -->
??? note "Answer"
    `11`

    1. The result of the increment and decrement operators

        Increment and decrement operators have postfix form `x++` (or `x--`), and prefix form `++x` (or `--x`).

        * The result of the postfix forms is the value of `x`.
        * The result of the prefix forms is the value of `x + 1` for `++x` (or `x - 1` for `--x`).

        For more information, see [cppreference-Increment/decrement operators](https://en.cppreference.com/w/c/language/operator_incdec)

    2. Logical OR `||`

        The logical OR expression has the form `lhs || rhs`, in which `rhs` is only evaluated if `lhs` compares equal to `​0`​.
        
        For more information, see [cppreference-Logical operators](https://en.cppreference.com/w/c/language/operator_logical)

    When `x < 9`, each loop will cause `x` to increase by `1`. Note that only `x-- < 9` is evaluated in each loop now.
    
    Now `x` is equal to `9` before the cond-expression of the for loop. First, `x-- < 9` is evaluated, which compares equal to `0`, and causes `x` to decrease by `1`. Then `x` is equal to `8` and `++x < 10` is evaluated, which compares equal to `1` and causes `x` to increase by `1`. Loop continues.

    Then, `x` is equal to `11` before the cond-expression of the for loop. Now `x-- < 9` and `++x < 10` both compare equal to `0`, so the loop ends. `x` firstly decreases by `1` and then increases by `1`, so the final value of `x` is `11`.
<!-- prettier-ignore-end -->

> 供题人：苏煜程

### 「22」 String Comparison

What's wrong with this code snippet?

```c
char a[] = {"abcd"};
char b[] = {"abcd"};
char c[] = {"ABCD"};

if(a > b) printf("[1] YES\n");
else printf("[1] NO\n");
if(a > c) printf("[2] YES\n");
else printf("[2] NO\n");
```

<!-- prettier-ignore-start -->
??? note "Answer"

    Actually, the output of this program is unpredictable.

    1. To compare two strings, you should use `strcmp` function in `<string.h>` header file. Learn how to use the function by yourself.
    2. In the code snippet above, `a`, `b` and `c` are all arrays of `char`, so `a > b` and `a > c` are actually comparing the addresses of these arrays. You may think that the array declared later has a larger address, but this is not always true. It depends on the design of the architecture that the stack grows towards higher memory addresses or towards lower memory addresses. So the output of this program is unpredictable. For more information on this, see [StackOverflow: Is the order of memory addresses of successively declared variables always descending?](https://stackoverflow.com/questions/12438216/is-the-order-of-memory-addresses-of-successively-declared-variables-always-desce)

> 供题人：杨琳玥

### 「21」 Addition

After executing the following code fragment, the output should be **\_\_**.

```c
double a = 0.1, b = 0.2;
if (a + b == 0.3)
    printf("Equal.\n");
else
    printf("Not equal.\n");
```

<!-- prettier-ignore-start -->
??? note "Answer"

    `Not equal.`

    In C (and many other programming languages), [floating-point](https://zh.wikipedia.org/wiki/%E6%B5%AE%E7%82%B9%E6%95%B0) arithmetic is not always exact due to the way numbers are represented in binary. This means that sometimes, tiny errors can be introduced and accumulated when performing mathematical operations on floating-point numbers.

    In this case, when adding 0.1 and 0.2 together, the result is not precisely 0.3 due to these inaccuracies. Thus, directly comparing floating-point numbers with `==` can lead to unexpected results.
    
    To deal with such issues in real programs, check if the difference between two floating-point numbers is smaller than a tiny threshold.

    For more information about floating-point numbers, search for [IEEE 754](https://zh.wikipedia.org/wiki/IEEE_754).
<!-- prettier-ignore-end -->

> 供题人：孙兆江

### 「20」 Bad for

After executing the following code fragment, the output should be **\_\_**.

```c
unsigned int x , y; // 'int' occupies 4 bytes
for (x = 2, y = 1; x = y; y++)
    ;
printf("%d", x-1);
```

<!-- prettier-ignore-start -->
???+ note "Hint"

    Review Oct.「18」 & 「16」 may help you get right answer.

<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "Answer"

    `-1`.

    Notice that the condition of `for` is `x = y`, not `x == y`. So `for` loop will terminate until `y = 0`. You should consider [overflow](https://zh.cppreference.com/w/c/language/operator_arithmetic#Overflows) in `unsigned int` variable.

    When we execute `++` for `unsigned int y` in `for` loop, we will get `0x111...1`($2^{32}-1$) as the max `unsigned int`, and then we will get `0x00...0` as `0` because of overflow. So `x` gets the value of `y(0)` and terminates `for`. In `printf`, `x-1` is `0x11...1`. When you use `%d` to print, it will be considered as a signed interger, so the answer is `-1`, not $2^{32}-1$.
<!-- prettier-ignore-end -->

> 供题人：胡育玮

### 「19」 IsPrime?

What's wrong with this code snippet?

```c
int d;
scanf("%d", &d);

// determine if d is a prime number
for (int i = 2; i <= d; i++) {
  if (d % i == 0) {
    printf("%d is a composite\n", d);
    exit(0);
  }
}
printf("%d is a prime\n", d);
```

<!-- prettier-ignore-start -->
??? note "Answer"

    Notice the *condition* of the `for` loop: `i <= d`, which means `i` will eventually be equal to `d`.
    Therefore `d % i == 0` evaluates to 1, reporting composite for every input greater than 1.
<!-- prettier-ignore-end -->

> 供题人：李英琦

### 「18」 Bad `if`-`else`

After executing the following code fragment, the output is **\_\_**.

```c
int x = 0;
int y = -2;
if(x > 0) y = 1;
else if(x < 0) y = -1;
else if(x = 0) y = 0;
printf("%d", y);
```

<div style="display: flex">
    <div style="width: 100%">A. 1</div>
    <div style="width: 100%">B. 0</div>
    <div style="width: 100%">C. -1</div>
    <div style="width: 100%">D. -2</div>
</div>

<!-- prettier-ignore-start -->
??? note "Answer"

    `D`.

    Notice that the condition of `if` in line 5 is `x = 0`, not `x == 0`. The former means "0 is assigned to x", and then the if sentence won't be executed since it is equivalent to `if(0)`. Thus the value of `y` is its initial value, -2.
<!-- prettier-ignore-end -->

> 供题人：梅敏炫

### 「17」 Character

Given: `char c = '@';`, the value of expression `'A' <= c <= 'Z'` is **\_\_**.

<!-- prettier-ignore-start -->
??? note "Answer"

    `1`.

    To solve this problem you do not need to remember ASCII code. This problem is about operator precedence. The expression `'A' <= c <= 'Z'` is equivalent to `(('A' <= c) <= 'Z')`. No matter what the value of `c` is, the expression `('A' <= c)` will be evaluated to `1` or `0`, which is less than `'Z'`. Therefore, the value of the expression `'A' <= c <= 'Z'` is `1`.

    But in other problems you may need to remember some key ASCII codes:

    | Character | ASCII Code |
    | --------- | ---------- |
    | `'0'`     | `48`       |
    | `'A'`     | `65`       |
    | `'a'`     | `97`       |

    Upper case is prior to lower case. The difference between `'A'` and `'a'` is `32`. So if you want to convert a lowercase letter to uppercase, you can use `c - 32`. Or an easier way: `c - 'a' + 'A'`.
<!-- prettier-ignore-end -->

> 来自：C 大 13 年期末

### 「16」 Overflow

For code below:

```c
unsigned short sht = 0;
sht--;
```

What will be the value of `sht` after the execution?

<div style="display: flex">
    <div style="width: 100%">A. -1</div>
    <div style="width: 100%">B. 65535</div>
    <div style="width: 100%">C. 32767</div>
    <div style="width: 100%">D. 65536</div>
</div>

<!-- prettier-ignore-start -->
??? note "Answer"

    B.

    Remember that `unsigned short` is an unsigned integer type, so it will not be negative. Instead, it will be the largest value of `unsigned short` type. The largest value of `unsigned short` type is `65535`, because `unsigned short` is 16-bit long.
<!-- prettier-ignore-end -->

> 来自：C 大 13 年期末
