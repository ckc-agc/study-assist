# C Programming Daily Problem

<style>
h1:before {content: unset;}
h2:before {content: unset;}
h3:before {content: unset;}
h4:before {content: unset;}
h5:before {content: unset;}
</style>

为了让同学们适应期末考试，每日一题的题面都将使用英文描述。

## October

### 「29」 Precedence

The output of the following code fragment is __.

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


### 「27」 Or in Switch

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

### 「24」 Nested Switch, Confusing Default and Break

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

### 「18」 Bad if-else

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
