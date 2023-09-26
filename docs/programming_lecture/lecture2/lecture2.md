# 类型系统与内存模型

<!-- prettier-ignore-start -->
!!! danger "施工中"

    本页面正在编辑中。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! abstract
    
    - C 类型系统的完整描述
    - 如何阅读声明
    - 程序内存空间的布局
    - 如何管理内存
<!-- prettier-ignore-end -->

## 类型系统

<!-- prettier-ignore-start -->
!!! abstract
    
    该部分在课堂上有较为详细的讲解，你应当已经了解下面这些**基本数据类型**的使用：
    
    - 整型：`int`、`long`、`short`、`char`、`unsigned`、`signed` 等。
    - 结构
<!-- prettier-ignore-end -->

### 数据是什么？

todo: 数据与类型的基本概念

### C 语言的类型系统

<!-- prettier-ignore-start -->
??? tip "字符类型解惑"

    或许你会和我同样对以下几个问题感到困惑：
    
    -   为什么**字符常量**的类型是 `int` 且长度是 4 个字节？
    -   为什么 `getchar()` 等函数返回 `int` 而不是 `char`？
    -   宽字符、多字节字符和 Unicode 究竟如何使用？
    
    这里将解释前两个问题，第三个问题不做要求，有兴趣可以参看 [杂项](misc.md) 中的相关内容。
    
    -   字符常量的类型为什么是 `int`？
    
    多字符常量（Multicharacter constants）继承于 C 语言的前身 B 语言。它们的主要用途是用于编写汇编语言，因为汇编语言中的指令通常是多字节的。例如，`'abcd'` 可以用于表示一个 32 位的指令。
    
    在 C 标准中，**多字符常量被定义为 `int` 类型**，长度是 4 个字节。在 C 语言的实际使用中，多字符常量通常是出于**调试目的**而嵌入结构中的**魔数（Magic Numbers）**，就像有些人会使用 `0xfeedbeef` 和 `0xdeadbeef` 而不是 `NULL` 来标记指针的**未初始化**和**已删除**状态。这样做的好处是，如果程序出现了错误，我们可以通过打印出这些魔数来定位错误的位置。
    
    我们使用时**应当避免将多字符常量从 `int` 类型转换为 `char` 类型，因为这一转换过程是由编译器实现决定的。**比如 `char a = 'ABCD'`，在 gcc、clang、msvc 上均为 `a = 'D'`，但是在 armcc 上为 `a = 'A'`。
    
    -   `getchar()` 为什么要返回 `int` 类型？
    
    因为它会返回 `EOF`，而 `EOF` 在标准中定义为 `int` 类型，通常为 `(int)-1`。
    
    > This macro is an integer value that is returned by a number of narrow stream functions to indicate an end-of-file condition, or some other error situation.
    
    为什么要这么定义？从逻辑上说，`EOF` 应当**与任何一个字符值都不同**。`(char)-1` 也是一个合法的字符（因为它是 `char` 类型，`char` 类型的每个值都能表示字符），所以不能用作 `EOF`，必须使用 `(int)-1`，它与前者宽度不同，因此是不同的值。
    
    还记得的在类型转换中提到的**整形提升**吗？如果我们让 `getchar()` 返回 `(char)-1`，当函数接收到 `(char)-1` 时，它会执行从无符号数到有符号数的转换（即使实现为有符号的 `char`），从而返回 `(int)255`，这与 `EOF` 的定义不符。
    
    此外，`char`、`signed char` 与 `unsigned char` 直接两两不同，尽管 `char` 具体实现为有符号数还是无符号数由实现决定。
    
    > 参考资料：
    >
    > -   [What is the purpose of multi character constants in C? - Quora](https://www.quora.com/What-is-the-purpose-of-multi-character-constants-in-C)
    > -   [Character constant - cppreference.com](https://en.cppreference.com/w/c/language/character_constant)
    > -   [int c = getchar()? Why int? : C_Programming (reddit.com)](https://www.reddit.com/r/C_Programming/comments/5a9sv1/int_c_getchar_why_int)
    > -   [Implicit conversions - cppreference.com](https://en.cppreference.com/w/c/language/conversion)

<!-- prettier-ignore-end -->




### 结构与其他数据类型

### 阅读和撰写类型声明

<!-- prettier-ignore-start -->
!!! info

    本节内容主要来自《C 专家编程》第 3 章“分析 C 语言的声明”。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! tip "在实际工作中最好使用 `typedef` 逐步合成声明。"

    One good way to synthesize declarations is in small steps with `typedef`. *K&R C, 5.12*.
<!-- prettier-ignore-end -->

《C 专家编程》和《C 陷阱与缺陷》都提出用下面这种方法理解复杂的类型声明，它们本质是一样的，分别表述为：

-   ***声明的形式与使用的形式相似***。
-   ***声明是类型+表达式***，对该表达式求值将***得到该类型***。

<!-- prettier-ignore-start -->
=== "简单的例子"
    
    看看这个声明：`int *p`
    
    -   `p` 是一个指针。我们声明它的形式与使用它的形式 `*p` （解引用 `p`）类似。
    -   `p` 是一个指针，对它求值得到一个 `int` 类型的值。
=== "复杂的例子"

    再看看这个声明：`char (*(*x[3])())[5]`
    
    -   `x` 是一个数组。我们声明它的形式与使用它的形式 `x[3]` 类似。
    -   把 `(*(*x[3])())[5]` 看作一个表达式，从内向外按照运算符和结合律对其求值，最终会得到一个 `char` 类型。求值的过程中，我们依次得到了数组、函数指针、数组指针，最后得到了 `char` 类型。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? note "K&R 对 C 语言类型声明的解读"

    Todo
<!-- prettier-ignore-end -->

对于**声明**来说，上面的方法已经足够了，因为**总是容易找到变量的名字在哪里**。但是对于**形式参数**、`typedef`、`sizeof` 和强制类型转换符等情况来说，**找不到变量的名字**，上面的方法就不够了。这时有一个更好的办法：从最内层括号开始读。

看看这个表达式：

```c
(*(void(*)())0)();
```

-   从最内层括号开始读：`void(*)()` 显然是一个函数指针，指向的函数的返回类型是 `void`，参数列表为空。
-   一层括号把 `void(*)()` 包起来，这是**强制类型转换**的用法，把 `0` 转换为 `void(*)()` 类型的指针。
-   最后就剩下 `(*fp)()` 形式的函数调用了。

综上所述，这个表达式的目的是调用首地址为 `0` 的函数。实际工作中，我们可以这样分解这个函数声明：

```c
typedef void (*funcptr)();
(*(funcptr)0)();
```

C 语言考试中还会要求你阅读代码片段，为形参等位置填写类型声明。请参考[历年卷总结](exam.md)中的例题。

---

分割线下方的内容还未整理

## 内存管理

C 的内存管理是一大痛点，因为它本身并不提供检查机制，一切都依赖于程序员自己。因此，好好掌握内存管理对于写出安全、稳定的程序是非常必要的。

### 对象和标识符

让我们来了解几个概念：对象、标识符

-   每个被存储的值都占用一定的物理内存，这样的一块内存称为**对象**。对象可以储存一个或多个值。

<!-- prettier-ignore-start -->
!!! tip "对象的其他含义"
    
    “面向对象编程”中的对象指的是“类对象”。
<!-- prettier-ignore-end -->

-   声明变量创建了一个**标识符**，标识符用于指定硬件内存中的对象。
-   **指针**与标识符不同，它是另一种指定对象的途径。

<!-- prettier-ignore-start -->
!!! note "左值"
    
    指定对象的表达式被称为**左值**。
    
    - `entity` 标识符，是左值
    - `*pt` 是表达式，也是左值
    - `2 * entity` 不是标识符，也不是左值
    - `*(pt + 2)` 是表达式，也是左值
    
    如果可以使用左值改变对象中的值，那么称为**可修改的左值**。
    
    ```c
    const char * pc = "xxxx";
    ```
    
    - `pc` 是可修改的左值
    - `*pc` 是不可修改的左值
<!-- prettier-ignore-end -->

### 存储期、作用域和链接

<!-- prettier-ignore-start -->
!!! note
    
    **存储期**描述对象，表明在内存中存储的时间。
    
    **作用域和链接**描述标识符，表明程序的哪些部分可以使用它。
<!-- prettier-ignore-end -->

#### 作用域

C 中的变量作用域有以下几种类型：

-   块作用域

大多数变量。从定义处到块末尾。

函数形参（即使它在花括号外部）。

<!-- prettier-ignore-start -->
??? note

    在 C99 之前，块作用域的变量必须在块的开头声明。
    
    也是在 C99，**块**的概念被放宽：控制语句（条件、循环）也是块（即使没有使用花括号）。比如：
    
    ```c
    for(int i = 0;;)
        function();
    ```
    
    `i` 具有块作用域，是循环的一部分。
    
    更精细的定义：循环体是整个循环的子块。你可以这样想它：
    
    ```c
    {
        for(int i;;)
        {
            int i;
        }
    }
    ```
    
    上面的两个同名变量 `i` 不在同一个块中，因此不是重复定义。

!!! tip

    同名的变量，内部覆盖外部。
<!-- prettier-ignore-end -->

-   函数作用域

`goto` 语句的标签。这意味着，即使标签在内层的块中，它的作用域也延伸至整个函数。

-   函数原型作用域

函数原型中的变量名。从定义处到函数原型结束。

只在你使用 VLA 时需要注意这一顺序：

```c
void use_VLA(int n, int m, ar[n][m]);
```

-   文件作用域

在任何函数外定义的变量。从定义处到文件末尾。

这样的变量称为全局变量。

<!-- prettier-ignore-start -->
!!! note "翻译单元"
    
    你所认为的多个文件对于编译器来说可能是一个文件。比如头文件：预处理时，头文件被插入。对于编译器来说，它看到的是单个文件。
    
    这样的单个文件称为一个翻译单元。每个翻译单元对应一个源文件和它 include 的文件。
    
    刚才我们说的**文件作用域**其实是在**整个翻译单元可见**。

<!-- prettier-ignore-end -->

#### 链接

-   外部链接

可以在多文件程序中的任何地方使用。

-   内部链接

只能在一个翻译单元中使用。由 `static` 关键字说明。

<!-- prettier-ignore-start -->
??? tip "用语"
    
    程序员们通常用**全局作用域或程序作用域**指代外部链接，用**文件作用域**指代内部链接。
<!-- prettier-ignore-end -->

-   无链接

块作用域、函数作用域、函数原型作用域。

#### 存储期

-   静态存储期

整个程序执行期间。文件作用域的变量。

块作用域的变量也能具有静态存储期，使用 `static` 限定符声明即可。

-   线程存储期

从声明处到线程结束。对文件作用域的声明使用 `_Thread_local` 限定符说明。每个线程有这个变量的私有拷贝。

-   自动存储期

程序进入块时分配，离开块时释放。块作用域的变量。

> VLA 是一个例外，它从定义处到块末尾存在。（毕竟到定义处才能知道其大小）。

-   动态分配存储期

#### 总结

不考虑并发编程，C 语言有五种存储类型。请描述它们的存储期、作用域、链接和定义方式。

-   自动
-   寄存器

寄存器变量存放在可用的最快的内存中。由于它可能存放在寄存器中，因此不能取得它的地址。其他方面与自动变量相同。

能够被声明为寄存器类型的变量类型可能受到限制。比如在某些处理器中，比 `double` 长的类型不能声明为寄存器变量。

-   静态外部链接

`extern` 声明常常是不必要的，只是能够更好地说明使用了其他地方的变量。

> 但是如果在块中，再次声明一个同名的变量，则会覆盖静态外部链接的变量。如果出现这种重名的情况，建议使用 `auto` 注明。

-   静态内部链接
-   静态无链接

仅在初始化时编译一次，若未指定值，则为 `0`。如果你用调试器调试，常常会发现好像“跳过”了这一步。

<!-- prettier-ignore-start -->
??? note
    
    - 可以使用 `auto` 显式说明自动存储期。但在 C++ 中它有不同含义，因此不要使用该限定符。
    - 
<!-- prettier-ignore-end -->

