# 讲义：C 语言的类型系统与内存模型

<!-- prettier-ignore-start -->
!!! danger "施工中"

    本页面正在施工：

    - 将较难内容迁移到课后模块。就程序设计这门课来说，需要讲述的内容抽象程度较高，如大端法、小端法等具体内容则无需讲解。与计算机系统有关的内容应当迁移到扩展模块
    - 优化讲义结构

!!! abstract
    - 程序内存空间的布局
    - C 类型系统的描述
    - 如何阅读声明
    - 如何管理内存

!!! tip
    在本节讲义中，若无特别说明，我们默认采用 C99 标准。
<!-- prettier-ignore-end -->

## 前置：数、进制与数据

- 十进制：`20231029`
- 二进制：`[0b] 1001101001011001101110101`
- 八进制：`[0o] 115131565`
- 十六进制：`[0x] 134b375`

你可以通过 `%x` 格式化字符串来打印十六进制数。

```c
printf("%x\n", 20231029);
printf("%d\n", 0x20231029);
```

### 如何阅读它们？

这些都是“十”：`0b1010`，`0o12`，`0xa`，`10`。

- `0x18`
    - ❌ *零埃克斯十八*，*零叉十八*，*零乘十八*
    - ✅ *零埃克斯一八*，*零叉一八*
- `0o23`
    - ❌ *零欧二十三*
    - ✅ *零欧二三*
- `0b1010`
    - ❌ *零币一千零一十*
    - ✅ *零币一零一零*
- `0x10000`
    - ❌ *零埃克斯一万*，*零叉一万*，*零乘一万*
    - ✅ *零埃克斯一零零零零*，*零叉一零零零零*

### ASCII

每个字符对应一个数字，即其 ASCII 码。如 `A` 的 ASCII 码为 `65`，`a` 的 ASCII 码为 `97`。

## 类型系统

类型是与数据相关的属性，它决定了数据的**存储方式**和**可进行的操作**。

变量是数据的**载体**，它是**存储在内存中的一块空间**，有**类型**和**值**。

### 计算机如何存储数据？

在一台 s390x 架构的计算机上：

```c
MAGIC_R(0x20231029);
// =====
// 0x20231029: 4 (0x4) byte(s)
// 0000  20 23 10 29
```

### 大端序与小端序

<!-- prettier-ignore-start -->
??? info "大端和小端名称的来源"

    来源于《格列佛游记》中的大小端之争：

    > 我下面要告诉你的是，Lilliput 和 Blefuscu 这两大强国在过去 36 个月里一直在苦战。战争开始是由于以下的原因：我们大家都认为，吃鸡蛋前，原始的方法是打破鸡蛋较大的一端，可是当今皇帝的祖父小时候吃鸡蛋，一次按古法打鸡蛋时碰巧将一个手指弄破了。因此他的父亲，当时的皇帝，就下了一道敕令，命令全体臣民吃鸡蛋时打破鸡蛋较小的一端，违令者重罚。老百姓们对这项命令极其反感。历史告诉我们，由此曾经发生过6次叛乱，其中一个皇帝送了命，另一个丢了王位。这些叛乱大多都是由 Blefuscu 的国王大臣们煽动起来的。叛乱平息后，流亡的人总是逃到那个帝国去寻求避难。据估计，先后几次有 11000 人情愿受死也不肯去打破鸡蛋较小的一端。关于这一争端，曾出版过几百本大部著作，不过大端派的书一直是受禁的，法律也规定该派任何人不得做官。”

<!-- prettier-ignore-end -->



主流架构（如 x86、AMD64、ARM）使用**小端序**。一些不常见的架构（如 SPARC）使用**大端序**。网络协议使用**大端序**。

### 先来练练手！

你应当已经知道，不同类型的变量一般占据不同的字节数。

```c
int i = 0x12345678;
MAGIC(i);

long long ll = 0xfedcba9876543210LL;
MAGIC(ll);

double d = 3.14159265358979323;
MAGIC(d);

float f = d;
MAGIC(f);

char c = 'A';
MAGIC(c);

MAGIC_R('A');

MAGIC_R((short)ll);

MAGIC("Hello world! I am a l" "ong string.");
```

<!-- prettier-ignore-start -->
??? info "在小端序计算机上可能的运行结果"
    ```html
    =====
    i: 4 (0x4) byte
    0000  78 56 34 12
    =====
    ll: 8 (0x8) byte
    0000  10 32 54 76 98 ba dc fe
    =====
    d: 8 (0x8) byte
    0000  18 2d 44 54 fb 21 09 40
    =====
    f: 4 (0x4) byte
    0000  db 0f 49 40
    =====
    c: 1 (0x1) bytes
    0000  41
    =====
    'A': 4 (0x4) byte <!--(1)!-->
    0000  41 00 00 00
    =====
    (short)ll: 2 (0x2) byte
    0000  10 32
    =====
    "Hello world! I am a l" "ong string.": 33 (0x21) byte
    0000  48 65 6c 6c 6f 20 77 6f 72 6c 64 21 20 49 20 61
    0010  6d 20 61 20 6c 6f 6e 67 20 73 74 72 69 6e 67 2e
    0020  00
    ```

    1. 其类型为 `#!c int`，故占用 4 字节。
<!-- prettier-ignore-end -->

### 基本类型

[类型 - cppreference.com](https://zh.cppreference.com/w/c/language/types)

整数类型：`#!c char` `#!c short` `#!c int` `#!c long` `#!c long long`

其中，除了 `#!c char` 以外的类型默认为 `#!c signed`，即有符号数。也就是说，`#!c int` 就是 `#!c signed int`。将 `#!c signed` 换为 `#!c unsigned`，就得到了无符号数。

<!-- prettier-ignore-start -->
!!! tip "那么 `#!c char` 呢？"

    `#!c char` `#!c signed char` `#!c unsigned char` 是**三个不同的类型**，尽管在大多数实现中，`#!c char` 表现为有符号数。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? tip "字符类型解惑"

    或许你会和我同样对以下几个问题感到困惑：

    -   为什么**字符常量**的类型是 `#!c int` 且长度是 4 个字节？
    -   为什么 `#!c getchar()` 等函数返回 `#!c int` 而不是 `#!c char`？
    -   宽字符、多字节字符和 Unicode 究竟如何使用？

    这里将解释前两个问题，第三个问题不做要求，有兴趣可以参看中的相关内容。

    -   字符常量的类型为什么是 `#!c int`？

    多字符常量（Multicharacter constants）继承于 C 语言的前身 B 语言。它们的主要用途是用于编写汇编语言，因为汇编语言中的指令通常是多字节的。例如，`#!c 'abcd'` 可以用于表示一个 32 位的指令。

    在 C 标准中，**多字符常量被定义为 `#!c int` 类型**，长度是 4 个字节。在 C 语言的实际使用中，多字符常量通常是出于**调试目的**而嵌入结构中的**魔数（Magic Numbers）**，就像有些人会使用 `#!c 0xfeedbeef` 和 `#!c 0xdeadbeef` 而不是 `#!c NULL` 来标记指针的**未初始化**和**已删除**状态。这样做的好处是，如果程序出现了错误，我们可以通过打印出这些魔数来定位错误的位置。

    我们使用时**应当避免将多字符常量从 `#!c int` 类型转换为 `#!c char` 类型，因为这一转换过程是由编译器实现决定的。**比如 `#!c char a = 'ABCD'`，在 gcc、clang、msvc 上均为 `#!c a = 'D'`，但是在 armcc 上为 `#!c a = 'A'`。

    -   `#!c getchar()` 为什么要返回 `#!c int` 类型？

    因为它会返回 `EOF`，而 `EOF` 在标准中定义为 `#!c int` 类型，通常为 `#!c (int)-1`。

    > This macro is an integer value that is returned by a number of narrow stream functions to indicate an end-of-file condition, or some other error situation.

    为什么要这么定义？从逻辑上说，`EOF` 应当**与任何一个字符值都不同**。`#!c (char)-1` 也是一个合法的字符（因为它是 `#!c char` 类型，根据 Latin-1 编码，`#!c char` 类型的每个可能值都表示一个字符），所以不能用作 `EOF`，必须使用 `#!c (int)-1`，它与前者宽度不同，因此是不同的值。

    还记得的在类型转换中提到的**整形提升**吗？如果我们让 `#!c getchar()` 返回 `#!c (char)-1`，当函数接收到 `#!c (char)-1` 时，它会执行从无符号数到有符号数的转换（即使实现为有符号的 `#!c char`），从而返回 `#!c (int)255`，这与 `EOF` 的定义不符。

    > 参考资料：
    >
    > - [What is the purpose of multi character constants in C? - Quora](https://www.quora.com/What-is-the-purpose-of-multi-character-constants-in-C)
    > - [字符常量 - cppreference.com](https://zh.cppreference.com/w/c/language/character_constant)
    > - [`#!c int c = getchar()`? Why `#!c int`? : C_Programming (reddit.com)](https://www.reddit.com/r/C_Programming/comments/5a9sv1/int_c_getchar_why_int)
    > - [隐式转换 - cppreference.com](https://zh.cppreference.com/w/c/language/conversion)
<!-- prettier-ignore-end -->

浮点类型：`#!c float` `#!c double` `#!c long double`

!!! tip "复数类型"
    在其后加上 `#!c _Complex` 即为复数类型，如 `#!c double _Complex`。相同的，有 `#!c _Imaginary`。

    是的，C 在语言层面上支持复数和虚数，但并不是所有的编译器都支持这一特性。例如，gcc 和 clang 目前均不支持 `#!c _Imaginary`。

### 定长整数类型与其他整数类型

在 `stdint.h` 中定义，如 `#!c int8_t` `#!c uint8_t` `#!c int16_t` `#!c uint16_t` `#!c int32_t` `#!c uint32_t` `#!c int64_t` `#!c uint64_t`。

`#!c sizeof` 运算符与 `#!c offsetof` 宏的结果：`#!c size_t`，足够表示任何对象的**大小**。常被定义为 `#!c unsigned long`。

在 `stddef.h` 中定义，`#!c ptrdiff_t` 表示两个指针相减的结果。常被定义为 `#!c long`。

<!-- prettier-ignore-start -->
??? tip "如何输出这些整数类型？"

    在 `inttypes.h` 中定义了一系列格式化字符串，如 `PRId32` 一般展开为 `#!c "d"`，而 `PRIu64` 可能展开为 `#!c "llu"`。

    这些定义在不同的平台上可能有所不同。使用这些格式化字符串可以保证在不同平台上输出正确的结果（且不会引发编译器警告）。

    ```c
    uint64_t i = 0xdeadbeefcafebabe;
    printf("%" PRIu64 "\n", i); // 应当包含 inttypes.h
    ```

    对于 `#!c size_t` 和 `#!c ptrdiff_t`，可以使用 `#!c %zu` 和 `#!c %td`。
<!-- prettier-ignore-end -->

### 结构体、联合体、枚举类型

枚举类型实质上是整数类型。它的值是由编译器自动分配的（一般从 0 开始），也可手动指定。

结构体的大小是其成员大小的总和，加上**对齐**所需的填充字节。

```c
struct point {
  int x;
  long y;
};
struct point p = {1234, -5678};
MAGIC(p);

union un_t {
  long l;
  double d;
};
union un_t un;
un.d = 3.14159265358979323;
MAGIC(un);

enum en_t { ENA, ENB, ENC = 114514 };
MAGIC_R(ENA);
MAGIC_R(ENC);

MAGIC_PTR(&p.x);
MAGIC_PTR(&p.y);
MAGIC_PTR(&un.l);
MAGIC_PTR(&un.d);
```

<!-- prettier-ignore-start -->
??? info "在小端序计算机上可能的运行结果"
    ```text
    =====
    p: 16 (0x10) byte
    0000  d2 04 00 00 00 00 00 00 d2 e9 ff ff ff ff ff ff
    =====
    un: 8 (0x8) byte
    0000  18 2d 44 54 fb 21 09 40
    =====
    ENA: 4 (0x4) bytes
    0000  00 00 00 00
    =====
    ENC: 4 (0x4) bytes
    0000  52 bf 01 00
    &p.x: 0x16d3cee18
    &p.y: 0x16d3cee20
    &un.l: 0x16d3cee10
    &un.d: 0x16d3cee10
    ```
<!-- prettier-ignore-end -->

### 字符串，数组，函数，指针类型

数组是一系列相同类型的对象的集合。数组的大小是其元素大小的总和。

```c
int arr[] = { 0xbeef, 0xcafe, 0xdead, 0xface, 0xfeed };
MAGIC(arr);

char str1[] = "Hello world!";
const char *str2 = "Hello world!";
MAGIC(str1);
MAGIC(str2);
```

以 `main` 函数为例，其有两种（标准规定的）形式：
```c
int main(void);                   // 类型为 int(void)
int main(int argc, char *argv[]); // 类型为 int(int, char *[])
```

C 标准不允许对函数类型应用 `sizeof` 运算符。

所有的指针类型都拥有相同的大小。我们将在后面的章节中讨论指针类型。

!!! note "数组到指针退化"

### `#!c void` 类型

`#!c void` 是一个**不完整类型**，即不存在 `#!c void` 类型的变量。它作为函数的返回类型，表示函数没有返回值。它作为函数的参数类型，表示函数不接受参数。

```c
void f(void) { /* 实现略去 */ }
void g(void) {
  return f(); // 仅当 f 的返回类型为 void 时才能这样写
}
```

<!-- prettier-ignore-start -->
??? info "那么 `#!c void *` 呢？"

    `#!c void *` 是一个**完整类型**，它表示一个指针，指向未知类型的对象（即，“舍弃”了类型信息的指针）。

    任何类型的指针均可隐式转换为 `#!c void *` 类型，但是反过来不行。这是因为 `#!c void *` 类型的指针不知道指向的对象的大小，因此不能进行解引用操作。

    ```c
    int i = 0x12345678;
    void *p = &i;
    printf("%p\n", p);
    printf("%d\n", *(int *)p);
    ```
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? tip "什么是不完整类型？"

    **不完整类型**是指**只知道其存在，但无法知道其大小**的类型。比如：

    ```c
    struct incomp;
    ```

    我们只知道 `#!c struct incomp` 存在，但是不知道它的大小（因为没有给出其定义）。因此，`#!c struct incomp` 是一个**不完整类型**。但是可以声明指向 `#!c struct incomp` 类型的指针。

    **`#!c void` 类型是唯一可作为函数返回类型的不完整类型。**这是 C 语法的一条特殊规定，其意义就是标定“函数没有返回值”。
<!-- prettier-ignore-end -->

### 使用 `#!c typedef` 为现有的类型定义别名

```c
int a;
```

你已经很熟悉这样的声明了，对吧？`a` 是一个 `#!c int` 类型的变量。

```c
typedef int a;
```

这就是说，`a` 现在就是 `#!c int` 的别名。你可以这样使用它：

```c
a b; // 等价于 int b;
```

我们之前提到过的 `#!c size_t`、`#!c ptrdiff_t`、`#!c int8_t` 等类型，就是通过 `#!c typedef` 定义的。

考试中还会要求你阅读代码片段，为形参等位置填写类型声明。请参考历年卷总结中的例题。

<!-- prettier-ignore-start -->
!!! info "C 与 C++ 的 `#!c struct` 并不完全一致"
    对于结构体

    ```c
    struct point {
      int x;
      int y;
    }
    ```

    在 C++ 中，此声明引入的新类型名为 `point`，而在 C 中，此声明引入的新类型名为 `#!c struct point`。`point` 本身不是一个类型名。

    下面的写法是常见的：

    ```c
    typedef struct point point;
    ```

    此即定义了一个类型名 `point`，其为 `#!c struct point` 的别名。
<!-- prettier-ignore-end -->

## 内存模型

在 C 语言的内存模型中，**字节**（byte）是最小的可寻址的内存单元，其被定义为一系列连续的**位**（bit）。**可寻址**意味着每个字节都拥有其编号，即**地址**。

```
MAGIC_PTR(&i);
MAGIC_PTR(&ll);
MAGIC_PTR(&d);
MAGIC_PTR(&f);

MAGIC_SIZED(f, 0x20);
```

### 地址和指针

**地址**是一个**无符号整数**，它表示内存中的一个字节。**指针**是一个**变量**，其存储了一个地址。由于这个原因，所有指针类型的大小都是相同的。

```c
MAGIC_R(&i);
MAGIC_PTR(&i);
```

### 对象和标识符

每个被存储的值都占用一定的物理内存，这样的一块内存称为**对象**。对象可以储存一个或多个值。声明变量时，创建了一个**标识符**（identifier），其与对象相关联。

所以，定义一个变量时实际上做了两件事：
- 为对象分配内存
- 将标识符与对象关联

<!-- prettier-ignore-start -->
!!! tip "对象的其他含义"

    “面向对象编程”中的对象指的是“类对象”。C 语言中没有“类对象”这一概念。
<!-- prettier-ignore-end -->

思维训练：

```c
int *psi = &i;

MAGIC(i);
MAGIC_R(*psi);
MAGIC(psi);
MAGIC_PTR(&i);
MAGIC_PTR(&psi);
```
<!-- prettier-ignore-start -->
??? info "在小端序计算机上可能的运行结果"
    ```text hl_lines="3 6 8-10"
    =====
    i: 4 (0x4) bytes
    0000  78 56 34 12
    =====
    *psi: 4 (0x4) bytes
    0000  78 56 34 12
    =====
    psi: 8 (0x8) bytes
    0000  4c ae db 6f 01 00 00 00
    &i: 0x16fdbae4c
    &psi: 0x16fdbae08
    ```
<!-- prettier-ignore-end -->

我们可以观察到什么？

- `psi` 变量的值就是 `i` 关联的对象的地址（`0x16fdbae4c`）
- 通过 `psi` 可以访问 `i` 关联的对象（`*psi`）
- `psi` 本身作为一个变量，也有自己的地址（`0x16fdbae08`）

<!-- prettier-ignore-start -->
!!! note "左值与右值"

    指代对象的表达式被称为**左值**。这个术语来自于赋值语句，因为赋值语句的左边必须是一个对象。

    如果可以使用左值改变对象中的值，那么称为**可修改的左值**。

    - `i` 是标识符，是可修改的左值
    - `*psi` 或 `arr[3]` 是表达式，是可修改的左值
    - `2 * i` 或 `&i` 或 `&psi`，不是标识符，是右值

    ```c
    const char *pc = "Good morning my neighbors";
    ```

    - `pc` 是可修改的左值
    - `*pc` 是不可修改的左值

    参考：[值类别 - cppreference.com](https://zh.cppreference.com/w/c/language/value_category)
<!-- prettier-ignore-end -->

### 内存管理

C 的内存管理是一大痛点，因为它本身并不提供检查机制，一切都依赖于程序员自己。因此，好好掌握内存管理对于写出安全、稳定的程序是非常必要的。

```c
int *dangling() {
  int i = 0xdeadbeef;
  int *p = &i;
  return p;
}

int main() {
  int *pfi = dangling();
  MAGIC(pfi);
  MAGIC(*pfi);
}
```

在这里 `pfi` 称为**悬垂指针**（dangling pointer），它指向了一个已经被销毁的对象。使用悬垂指针是未定义行为，可能会导致程序崩溃。

<!-- prettier-ignore-start -->
!!! note "常见变式"

    ```c hl_lines="2"
    char *get_a_string() {
      char str[] = "Hello world!";
      return str;
    }
    int main() {
      char *str = get_a_string();
      printf("%s\n", str);
    }
    ```

    问题出在哪？

    `str` 作为一个数组，其生命周期在 `get_a_string` 函数返回时结束。

    它与下面的程序有什么区别？

    ```c hl_lines="2"
    char *get_a_string() {
      char *str = "Hello world!";
      return str;
    }
    int main() {
      char *str = get_a_string();
      printf("%s\n", str);
    }
    ```
<!-- prettier-ignore-end -->

---

### 存储期、作用域和链接

**存储期**描述对象，表明在内存中存储的时间。

**作用域和链接性**描述标识符，表明程序的哪些部分可以使用它。

#### 存储期

- 静态存储期（static）
  在程序开始时创建，在程序结束时销毁。如全局变量和静态变量。
- 自动存储期（automatic）
  在程序进入作用域时创建，在程序离开作用域时销毁。如局部变量。
- 动态分配存储期（allocated）
  在程序显式地分配内存时创建，在程序显式地释放内存时销毁。如 `#!c malloc()` 分配的内存。

```c
#include <stdlib.h>
int global;
int main() {
  int automatic;
  int *allocated = malloc(sizeof(int));

  MAGIC_PTR(&global);
  MAGIC_PTR(&automatic);
  MAGIC_PTR(allocated);
}
```

#### 作用域

[作用域 - cppreference.com](https://zh.cppreference.com/w/c/language/scope)

##### 块作用域

<!-- prettier-ignore-start -->
??? note

    在 C99 之前，块作用域的变量必须在块的开头声明。

    在 C99，**块**的概念被放宽：控制语句（条件、循环）也是块（即使没有使用花括号）。比如：

    ```c
    for(int i = 0;;)
      function();
    ```

    `i` 具有块作用域，是循环的一部分。

    更精细的定义：循环体是整个循环的子块。你可以这样想它：

    ```c
    {
      for(int i;;) {
        int i;
      }
    }
    ```

    上面的两个同名变量 `i` 不在同一个块中，因此不是重复定义。

!!! tip

    同名的变量，内部覆盖外部。
<!-- prettier-ignore-end -->

##### 函数作用域

`goto` 语句的标签。这意味着，即使标签在内层的块中，它的作用域也延伸至整个函数。

##### 函数原型作用域

函数原型中的变量名。从定义处到函数原型结束。

只在你使用 VLA 时需要注意这一顺序：

```c
void use_VLA(int n, int m, ar[n][m]);
```

##### 文件作用域

在任何函数外定义的变量。从定义处到文件末尾。

这样的变量称为全局变量。

<!-- prettier-ignore-start -->
!!! note "翻译单元"

    你所认为的多个文件对于编译器来说可能是一个文件。比如头文件：预处理时，头文件被插入。对于编译器来说，它看到的是单个文件。

    这样的单个文件称为一个翻译单元。每个翻译单元对应一个源文件和它 include 的文件。

    刚才我们说的**文件作用域**其实是在**整个翻译单元可见**。

<!-- prettier-ignore-end -->

---

由于讲义中涉及到的内容较多，无法在一节课内全部讲解。后续的讲义将会随回放链接更新而更新。

#### 链接

### 阅读和撰写类型声明
