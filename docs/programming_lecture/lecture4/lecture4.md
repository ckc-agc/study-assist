# C 标准库

<!-- prettier-ignore-start -->
!!! danger "施工中"

    本页面正在编辑中。

!!! abstract "摘要"

    -   前半：C 标准库的使用（简单）
        
        前半部分的内容要求仅限于考试。从历年卷中看，考察内容仅限于：

        -   `ctype.h`：在第二讲「类型系统与内存模型」提及
        -   `stdio.h`：已在第三讲「I/O与文件」介绍其中部分
        -   `string.h`：字符串相关操作
        -   `stdlib.h`：常用工具库
        -   `math.h`：数学库

        前半节课我们将对考试必备的标准库函数作介绍，用一个个案例展示它们的用法。

    -   后半：C 标准库的实现（较难）
        
        后半部分我们将认识一下 C 标准库这类应用于生产环境的代码的组织方式，挑选一些经典的函数看看它的实现。这部分内容不会出现在考试中，但是对于理解 C 语言的底层实现有很大的帮助。或许它是你从未了解过的 C 语言的另一面。
<!-- prettier-ignore-end -->

## 前半：C 标准库的使用

「内容」 模块中代码段内被注释掉的内容，表示不作要求。

### `ctype.h`

<!-- prettier-ignore-start -->
!!! info "背景知识"

    ASCII 中：

    - 打印字符：`0x20` ~ `0x7E`
    - 控制字符：`0x00` ~ `0x1F` 和 `0x7F`
<!-- prettier-ignore-end -->

头文件 `<ctype.h>` 声明了几个可以用于**识别和转换字符**的函数。

#### 内容

-   字符判断函数
    ```c
    int isalnum(int c);
    int isalpha(int c);
    // int iscntrl(int c);
    int isdigit(int c);
    // int isgraph(int c);
    int islower(int c);
    // int isprint(int c);
    // int ispunct(int c);
    int isspace(int c);
    int isupper(int c);
    // int isxdigit(int c);
    ```
-   字符转换函数
    ```c
    int tolower(int c);
    int toupper(int c);
    ```

#### 使用

`<ctype.h>` 中的函数对 ASCII 字符大致作了如下划分：

![](graph/character_types.png)

## 后半：C 标准库的实现

<!-- prettier-ignore-start -->
!!! info "杂谈：为什么要学习 C 标准库？"

    理论上，学习完任何编程语言的基本语法后，我们就可以用它来编程解决任何实际问题了。但是，语言所衍生出的任何能提高生产力的库，其重要性往往会远远超过该语言本身。学习一门语言并学习其库的实现，这样才能熟练地驾驭语言工具，了解库所提供的功能和局限性，进而在特定的应用要求下扩展库。

    尽管 C 语言及其所附带的标准库中隐藏着太多的晦涩陷阱，但我们不得不花大力气“过分钻研”它。学习 C 标准库本身的实现，就是学习 C 语言最好的教材，因为其实现过程将会把使用 C 语言编写具有工业强度的健壮代码所需的技巧展现得淋漓尽致。

    C 标准库可以分为 3 组。如何正确和熟练地使用它们，可以相应地区分出 3 种层次的 C 程序员：

    -   合格程序员：
        ```text
        <ctype.h> <stdio.h> <stdlib.h> <string.h>
        ```
    -   熟练程序员：
        ```text
        <assert.h> <limits.h> <stddef.h> <time.h>
        ```
    -   优秀程序员：
        ```text
        <float.h> <math.h> <error.h> <locale.h> <setjmp.h> <signal.h> <stdarg.h>
        ```
    
    可以看到，C 程序设计这门课程对大家的要求就是「合格程序员」。我们在课程中的极少部分代码会看见 `<assert.h>` 和 `<time.h>`，这两个库也会对你的编程有所帮助，优秀的同学可以以「熟练程序员」来要求自己。今后大多数同学或许都会转向学习 C++，大概只有做安全、系统、嵌入式之类的同学会需要做到「优秀程序员」的地步。

!!! tip "学习 C 标准库前你应该具备的知识"

    -   字符串、数组、指针等操作
    -   命名空间：库中定义了 200 个以上的名字，你应当知道 C 中各种名字会如何被解析。

    ![](graph/namespace.png)
<!-- prettier-ignore-end -->

学习 C 标准库时，我们会接触到很多 C 标准中的规范性的严谨地语句，初读时可能让你觉得非常拗口和难以理解，让我们来读几条。

### 杂项：C 标准对库的实现要求

标准库中的一些函数，可能同时提供了宏和函数的版本。

-   一个实现必须为每一个库函数提供一个实际的函数，即使它已经为该函数提供了一个宏。
-   一个函数的任何宏定义都可以通过用括号把函数的名字括住来局部地抑制它。因为这个名字后面没有跟着指示一个宏函数名展开地左括号。
-   用来移除任何宏定义的 `#undef` 预处理指令的使用也可以保证实际函数的引用。

<!-- prettier-ignore-start -->
!!! example "`atoi()` 的使用方式"

    1.  可能生成一个宏函数：
        ```c
        #include <stdlib.h>
        const char *str;
        i = atoi(str);
        ```
    2.  生成一个实际函数引用：
        ```c
        #include <stdlib.h>
        #undef atoi
        const char *str;
        i = atoi(str);
        ```
        或者
        ```c
        #include <stdlib.h>
        const char *str;
        i = (atoi)(str);
        ```
<!-- prettier-ignore-end -->

### `<ctype.h>` 的实现：宏与位运算

<!-- prettier-ignore-start -->
!!! question "🤚停一停，先别看下面的内容。思考一下，你会怎么实现上面的那些函数？"

    你会不会在想这样的代码：

    ```c
    int isalnum(int c)
        { /* test for alphanumeric character */
        return (('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z'));
        }
    ```
<!-- prettier-ignore-end -->

`<ctype.h>` 中的函数通常使用宏来实现。使用宏实现时需要注意以下因素：

-   虽然宏可能比函数快，但是它们通常会产生更大的代码。如果在很多地方扩展，这个程序可能大到让你无法想象。
-   宏的参数可能会被求值多次，具有副作用的宏参数会导致意外。
    <!-- prettier-ignore-start -->

    !!! warning "会产生不安全行为的宏"

        标准库中，只有 `getc` 和 `putc` 可能会产生这种不安全行为。

    <!-- prettier-ignore-end -->

`<ctype.h>` 中定义了一个查找表 `_Ctype`，两个映射表 `_Tolower` 和 `_Toupper`。每个字符都被编入查找表中，使用位运算就能判断出字符的类型。

```c title="ctype.h"
#define _DI 0x20 /* '0'-'9' */
#define _LO 0x10 /* 'a'-'z' */
#define _UP 0x02 /* 'A'-'Z' */
#define _XA 0x200 /* 'a'-'z', 'A'-'Z' */
extern const short *_Ctype, *_Tolower, *_Toupper;
#define isalnum(c) (_Ctype[(int)(c)] & (_DI|_LO|_UP|_XA))
#define tolower(c) _ToLower[(int)(c)]
```

<!-- prettier-ignore-start -->
!!! question "读一下上面的代码，想象一下 `_Ctype` 这个查找表的样子。"
!!! question "考考你，对于 ASCII 字符集，这个查找表有多大？"
!!! question "你能想一想映射表的实现吗？"
<!-- prettier-ignore-end -->

同样，给出函数版本的实现：

```c title="isalnum.c"
#include <ctype.h>

int isalnum(int c)
    { /* test for alphanumeric character */
    return (_Ctype[c] & (_DI|_LO|_UP|_XA));
    }
```

下面两幅图分别展示了 `_Ctype` 和 `_Toupper` 的样子：

<!-- prettier-ignore-start -->
::cards:: cols=2

[
  {
    "title": "`_Ctype`",
    "image": "graph/ctype.png"
  },
  {
    "title": "`_Toupper`",
    "image": "graph/toupper.png"
  }
]

::/cards::
<!-- prettier-ignore-end -->

非常地简单，对吧？这可比 `'a' <= c && c <= 'z'` 这样的判断要快得多。于是我们学完了 `<ctype.h>` 的实现。

### `<stdio.h>` 的实现：系统调用与内核编程

在我个人看来，`<stdio.h>` 的实现最具挑战性。你需要对实现对应的操作系统有一定的了解，才能编写出完善的代码。

<!-- prettier-ignore-start -->
!!! tip "本节以 UNIX 和 POSIX 规范的系统调用为准。"
??? info "一些历史的背景：文件、设备和 `ioctl`"

    1. 混乱的磁盘文件系统

    或许你很难想象，UNIX 之前的磁盘文件系统为文件赋予了很多类型上的概念和、作了很多区分，而不是我们现在所广泛接受的「文件就是一系列连续的字节」的概念。这边有一段描述，你可以看看：

    > Typically source code was a distinguished type, different from data. Compilers could read source, compiled programs could read and write 'data.' Thus the creation and inspection of Fortran programs was often walled off from the creation and inspection of other files, with completely different ways to edit and print them. This ruled out the use of programs to generate (or even simply copy) Fortran programs.

    2. 不统一的文本表示和设备交互

    早期程序的输入输出无法独立于设备。比如，在上个世纪 60 年代的 FORTRAN IV 中，在磁带机上需要用 `READ INPUT TAPE 5`，读取磁盘上需要用 `READ INPUT DISK 1`。这样的代码在不同的设备上需要修改，非常不方便。UNIX 将这些混乱的设备交互封装在**设备处理程序**中。在 UNIX 系统看来，外围设备有三种类型：字符设备（Character devices）、块设备（Block devices）和网络设备（Network devices）。这三种设备都被抽象为文件，使用统一的文件操作接口。

    在 Ken Thompson 为 UNIX 设计统一的内部文本形式前，文本表示也是十分混乱的。结束一行是使用回车还是回车加换行，还是换行符，还是更神奇的字符？终端能不能识别和展开制表符？怎样用键盘标志文件结束？这些问题的答案和终端的生产厂商一样多。UNIX 使用系统调用 `ioctl` 来设置一个设备的各种参数，负责对内部换行约定和各种终端之间的需要转换的字符进行处理。


<!-- prettier-ignore-end -->

