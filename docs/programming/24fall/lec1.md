# 第一讲：编程入门

本次课程定位为编程入门，希望主要向大家介绍一些基本的编程思想，并通过例题与讲解的形式加以渗透。例题参考自去年的 PTA 习题。

## 计算机基础知识

冯诺依曼架构：输入、储存、计算、输出

计算机如何储存数据？

计算机如何运算数据？

## 编程思路

编程的过程可以是一种直观思考的抽象化，对于一般的编程问题，我一般把它分为两类，即：

- 可以直接想出来的
- 不知道算法做不出来的（或者想不到最优解）

对于前者，我们还是可以有一定的思路去解决的，比如下面这个经典的例子：

!!! note "例子"
    公鸡 5 元一只、母鸡 3 元一只、小鸡 1 元 3 只；100 元买了 100 只鸡，问各多少只？

对于后者，比如：

!!! note "例子"
    给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数。

    用户可以对一个单词进行如下三种操作：插入一个字符、删除一个字符、替换一个字符。

跳出做题的框架，我们一般把编程范式分为以下几种：

- 面向过程
- 面向对象
- 函数式
***

## 基础知识复习

- 变量
- 语句
- 数组
- 指针
- 栈
- 队列
- 递归

## 基本输入输出
可能这一节内容有些基础，但作为每道编程题必不可少的部分（有时甚至是通过的关键所在），我希望能为大家稍微总结一下怎样读数据，怎样输出数据。

目前，我们一般使用 `scanf()` 读入数据，`printf()` 输出数据。其中的 `'f'` 意为 "format"，即格式化输入输出。

!!! note "scanf"
    `scanf()` 的定义如下：
    ```c
    int scanf(const char *format, ...)
    ```

参数由两部分组成：格式化字符串、读入参数。简单来说，前面一半是告诉计算机怎么读，后面一半是告诉计算机读完了存在哪里。

|                  类型                  |      合格的输入      |  参数的类型   |            备注            |
| :------------------------------------: | :------------------: | :-----------: | :------------------------: |
|                  `%c`                  |       单个字符       |   `char *`    |    可以使其读取多个字符    |
|                  `%d`                  |      十进制整数      |    `int *`    |         32 位整型          |
|                  `%l`                  |      十进制整数      |   `long *`    |         32 位整型          |
|                 `%ll`                  |      十进制整数      | `long long *` |         64 位整型          |
| `%e`、`%E`、`%f` <br> `%F`、`%g`、`%G` |     单精度浮点数     |   `float *`   |  注意不能用来读 `double`   |
|                 `%lf`                  |     双精度浮点数     |  `double *`   |        64 位浮点型         |
|                  `%i`                  | 十、八、十六进制整数 |    `int *`    |    有的时候可以用来偷懒    |
|                  `%o`                  |      八进制整数      |    `int *`    |            同上            |
|               `%x`、`%X`               |     十六进制整数     |    `int *`    |           同上上           |
|                  `%s`                  |        字符串        |   `char *`    | 读取直到遇到第一个空白字符 |
|                  `%p`                  |         指针         |               |                            |
|                  `%%`                  |    读入 `%` 字符     |               |                            |

一个很容易犯的错误：`scanf(%d, &var)`写成`scanf(%d, var)`。此处使用`&`运算符是因为我们要告诉计算机储存数据的位置 `&var` 而不是 `var` 这个变量的值。

而日常被忽略的 `scanf()` 返回值会告诉我们它成功读到了几个参数（可用于判定有没有读完）。

!!! note "试试看!（只需要写出读取输入的语句）"
    1. 输入仅有一行，共 7 个用空格隔开的整数.
    2. 第一行一个整数 $N$（$N$ 是偶数且 $1<N<100000$）;
        第二行 $N-1$ 个用空格隔开的正整数 $A_i (0<A_i<100000)$.
    3. 输入的第一行是整数 $L$（$1< L < 10000$）；
        第二行是整数 $M$（$0 < M < 100$）；
        接下来的 $M$ 行，每行包含两个不同的整数，用一个空格隔开.
    4. 输入由空格隔开的正数（可以是小数），直到输入 -1.
    5. 输入是 1~5 个正整数.

!!! info "printf"
    `printf()` 的定义如下：
    ```c
    int printf(const char *format, ...)
    ```

相对于 `scanf()` 的格式化字符串，`printf()` 更加复杂：`printf()` 的格式化参数可以表达为以下形式：

```C
%[flags][width][.precision][length]specifier

```
其中，`specifier` 即格式字符，与 `scanf()` 一致；其他参数如下所示：（来自 [菜鸟教程](https://www.runoob.com/cprogramming/c-function-printf.html)）

| flag  | 描述                                                                                                                                                                                                                                                                                                                         |
| :---: | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|  `-`  | 在给定的字段宽度内左对齐，默认是右对齐                                                                                                                                                                                                                                                                                       |
|  `+`  | 强制在结果之前显示加号或减号（`+` 或 `-`），即正数前面会显示 `+` 号。默认情况下，只有负数前面会显示一个 `-` 号                                                                                                                                                                                                               |
| 空格  | 如果没有写入任何符号，则在该值前面插入一个空格。                                                                                                                                                                                                                                                                             |
|  `#`  | 与 `o`、`x` 或 `X` 说明符一起使用时，非零值前面会分别显示 `0`、`0x` 或 `0X`。<br>与 `e`、`E` 和 `f` 一起使用时，会强制输出包含一个小数点（即使后边没有数字时也会显示小数点）。<br>默认情况下，如果后边没有数字时候，不会显示显示小数点。<br>与 `g` 或 `G` 一起使用时，结果与使用 `e` 或 `E` 时相同，但是尾部的零不会被移除。 |
|  `0`  | 在指定填充 padding 的数字左边放置零（`0`），而不是空格                                                                                                                                                                                                                                                                       |

|  width   | 描述                                                                                                   |
| :------: | :----------------------------------------------------------------------------------------------------- |
| (number) | 要输出的字符的最小数目。如果输出的值短于该数，结果会用空格填充。如果输出的值长于该数，结果不会被截断。 |
|   `*`    | 宽度在 format 字符串中未指定，但是会作为附加整数值参数放置于要被格式化的参数之前。                     |

| .precision | 描述                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| :--------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|  .number   | 对于整数说明符（`d`、`i`、`o`、`u`、`x`、`X`）：precision 指定了要写入的数字的最小位数。如果写入的值短于该数，结果会用前导零来填充。如果写入的值长于该数，结果不会被截断。精度为 0 意味着不写入任何字符。<br>对于 `e`、`E` 和 `f` 说明符：要在小数点后输出的小数位数。<br>对于 `g` 和 `G` 说明符：要输出的最大有效位数。<br>对于 `s`: 要输出的最大字符数。默认情况下，所有字符都会被输出，直到遇到末尾的空字符。<br>对于 `c` 类型：没有任何影响。<br>当未指定任何精度时，默认为 1。如果指定时不带有一个显式值，则假定为 0。 |


而日常被忽略的 `printf()` 返回值会告诉我们写入的字符总数（如果有输出），否则会是一个负数（可用于判定有没有输出）。
***
## 一些题目

!!! info "水仙花数"
    找出 0~999 间所有的水仙花数。水仙花数是指一个三位数，它的各位数字的三次幂之和是其本身。

!!! info "完美数"
    实现一个计算整数因子和的简单函数，并利用其实现另一个函数，输出两正整数 $m$ 和 $n$（$0<m<n<10000$）之间的所有完数。所谓完数就是该数恰好等于除自身外的因子之和。例如：$6=1+2+3$，其中 1、2、3 为 6 的因子。

!!! info "Gram-Schmidt Algorithm"
    （ 题目省略 ）