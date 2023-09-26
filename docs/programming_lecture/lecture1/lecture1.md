# 程序编译过程与调试技术

<!-- prettier-ignore-start -->
!!! danger "施工中"

    本页面正在编辑中。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! abstract "内容提要"

    - 编译过程：从源代码到可执行文件
    - 编译器和开发套件：`gcc`、`clang` 和 `llvm` 究竟是什么？
    - 调试器：如何使用 `gdb` 或 `lldb` 设置断点、找到段错误的根源？
<!-- prettier-ignore-end -->

## 课程导言

Hi，欢迎各位同学来到竺院程设辅学线下授课的第一节课。

在前几周的程序设计课程中，老师们应该已经为同学们讲解了 C 语言的基础语法等知识。但是同学们或许会有下面这些疑问：

-  计算机是如何读懂我写的代码的？
-  现在我在终端中运行程序，终端到底是什么？什么时候我的程序能具有图形界面？
-  我的程序总是出问题，我该如何快速找到错误的根源？

辅学课程的目的就是帮助同学们解决这些“为什么”的问题。实质上C语言是一门很难的编程语言，不懂编译原理、操作系统和计算机体系结构无法获得深入的理解。我们希望通过线下授课，为具有 C 语言基础或愿意深入学习 C 语言的同学提供进一步的知识扩展，让同学们在计算机（而非算法题）的语境下理解 C 语言、理解程序设计。

那么在本节课，我们将为大家系统讲解程序编译过程与调试技术，为后续的课程做铺垫。接下来，让我们一起进入计算机的世界吧！

## 基础知识

首先，我们来了解一下计算机的基本知识。

### 计算机能做什么？

现代计算机由多种部件构成，比如中央处理单元（Central Processing Unit，CPU）、随机存取内存（Random Access Memory，RAM）、硬盘（Hard Disk）等。其中 CPU 负责处理程序。

<!-- prettier-ignore-start -->
::cards:: cols=2

[
  {
    "title": "RISC CPU",
    "content": "这是一个非常简单的 CPU 的电路，它能够执行你用 0 和 1 编写的机器指令。",
    "image": "graph/risc_cpu.png"
  },
  {
    "title": "CPU 基本结构",
    "content": "CPU 主要由控制单元、算术逻辑单元和寄存器组成。控制单元中有程序计数器和指令寄存器。",
    "image": "graph/cpu.png"
  },

]

::/cards::
<!-- prettier-ignore-end -->

- CPU 能读懂什么？

CPU 无法直接读懂你写的 C 语言代码，它是由数字电路构成的。**数字电路只能处理 0 和 1，因此计算机中的任何数据都必须使用二进制表示，程序也是如此。**

在计算机刚刚诞生的阶段，工程师们不得不使用 0 和 1 构成的指令序列和计算机打交道，这就是**机器语言**。因为具体电路设计不同，每种 CPU 所能理解的指令有限，这些指令的集合叫做**指令集**。

- CPU 都做些什么？

CPU 的工作非常简单：从内存中读取并执行一条指令，再从内存中读取并执行下一条指令……1 GHz 的 CPU 每秒能重复这一操作约十亿次。

这些指令都相当具体，比如把一个数字从一个位置移动到另一个位置，把两个数字相加并把结果存储再某个地方。是的，你的 CPU 也在疯狂做着这些事情。但是通过精巧的设计，这些简单的指令就能构建起程序的控制逻辑，实现复杂的功能。

CPU 还有自己的小工作区——由若干寄存器（Register）组成的寄存器组。每个寄存器能存储一个数字。

### 高级计算机语言和编译器

现代计算机的结构与 70 年前并没有本质上的不同，但是程序设计语言取得了很大的发展，产生了汇编语言和高级语言。我们仍然不能直接对 CPU 说：为我计算 $1 + 1$，但我们可以用高级语言简洁的表达它，让**编译器（compiler）和汇编器（assembler）**将其翻译成 `0101`` 的机器语言。下图展示了程序设计语言的发展历史，编译过程其实就是这一历史的反向。

<!-- prettier-ignore-start -->
::cards::

[
  {
    "title": "机器语言 <br> Machine Code",
    "content": "这是第一代编程语言，也是计算机唯一能识别的语言。上图展示了世界上第一个计算机程序，它用来找出一个数最大的因数。",
    "image": "graph/machine_code.png"
  },
  {
    "title": "汇编语言 <br> Assembly Language",
    "content": "这是第二代编程语言，其实就是机器语言的助记符。它使得程序员不用再直接与 0 和 1 打交道，程序的可读性也更强了。上图显示了将两个整数相加的汇编代码。",
    "image": "graph/assembly.png"
  },
  {
    "title": "高级语言 <br> High-level Language",
    "content": "这是第三代编程语言，它让程序员们不用再关注计算机结构上的细节，而是将注意力转移到要解决的问题上来。",
    "image": "graph/high_level_language.png"
  },

]

::/cards::
<!-- prettier-ignore-end -->

下面三行代码分别是用 C 语言、汇编语言和机器语言（十六进制）描述的同一件事：

<!-- prettier-ignore-start -->
=== "简单的例子"
    
    ```c
    c = a + b;
    ```

    ```asm
    add $t0, $t1, $t2
    ```

    ```
    01 2a 40 20
    ```
=== "复杂的例子"

    ```c
    void multstore(long x, long y, long *dest) {
        long t = mult2(x, y);
        *dest = t;
    }
    ```

    ```asm
    multstore:
        pushq   %rbx
        movq    %rdx, %rbx
        call    mult2
        movq    %rax, (%rbx)
        popq    %rbx
        ret
    ```

    ```
    53 48 89 d3 48 83 ec 08 e8 00 00 00 00 48 89 03 5b c3
    ```
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! question "为什么需要高级语言？"

    1. 机器语言和汇编语言都是非常底层的语言，程序员需要关注计算机的细节，这使得程序的**可读性很差**。使用高级语言，程序员能**将注意力转移到要解决的问题上来**。
    2. 机器语言和汇编语言都是与具体 CPU 相关的，程序员需要为不同的 CPU 编写不同的程序，**可移植性差**。使用高级语言，程序员只需要写一次程序，再使用编译器就能将其翻译成能在特定 CPU 的机器语言。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
??? info "对机器语言有兴趣？"

    [这里](https://eng.libretexts.org/Bookshelves/Computer_Science/Programming_Languages/Introduction_To_MIPS_Assembly_Language_Programming_(Kann)/04%3A_Translating_Assembly_Language_into_Machine_Code)提供了一些将汇编语言转换为 MIPS 指令集机器语言的基础例子，有兴趣可以了解一下。
<!-- prettier-ignore-end -->

## 程序的编译过程

接下来，我们将了解编译器和汇编器是如何一步步把你的程序编译成机器码的。

GCC 是最经典的 C 语言编译器。当我们使用命令 `gcc -o test test.c` 编译一个 C 语言程序时，GCC 会调用一系列的程序将源代码翻译成汇编语言、再翻译成机器语言，最后经过链接产生可执行文件。下图展示了这个过程。

![](https://cdn.bowling233.top/images/2023/07/202307142109343.png)

1. 预处理：由 C 预处理器（C Preprocessor）完成，它将源代码中的宏定义展开，将头文件中的内容插入到源代码中，删除注释等。预处理后的代码文件以 `.i` 为后缀。
2. 编译：由 C 编译器（C Compiler）完成，它将预处理后的文件翻译成汇编语言。编译后得到的汇编代码文件以 `.s` 为后缀。
3. 汇编：由汇编器（Assembler）完成，它将汇编代码翻译成机器语言。汇编后得到的机器代码文件以 `.o` 为后缀。
4. 链接：由链接器（Linker）完成，它将多个目标文件链接成一个可执行文件。链接后得到的可执行文件以 `.exe` 为后缀。

你可以添加 `-v` 选项看到各个编译阶段的详细信息。



## 参考资料

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [GCC and Make - A Tutorial on how to compile, link and build C/C++ applications](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)

<!-- prettier-ignore-end -->