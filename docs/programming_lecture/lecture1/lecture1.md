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

### 解读 `gcc` 显示的详细信息

下面这些文本是 `gcc -Og -o prog main.c sum.c` 命令的输出结果。点击文本中带圆圈的 `+` 号可以展开详细信息，高亮的行是运行某个编译器组件的具体命令。

```html hl_lines="12 33 36 57 62"
<!--(1)!-->Using built-in specs. 
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/12/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none:amdgcn-amdhsa
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 12.3.0-1ubuntu1~23.04' --with-bugurl=file:///usr/share/doc/gcc-12/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-12 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-12-DAPbBt/gcc-12-12.3.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-12-DAPbBt/gcc-12-12.3.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 12.3.0 (Ubuntu 12.3.0-1ubuntu1~23.04) 
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog-'
<!--(2)!--> /usr/lib/gcc/x86_64-linux-gnu/12/cc1 -quiet -v -imultiarch x86_64-linux-gnu main.c -quiet -dumpdir prog- -dumpbase main.c -dumpbase-ext .c -mtune=generic -march=x86-64 -Og -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/ccCWi0p2.s
GNU C17 (Ubuntu 12.3.0-1ubuntu1~23.04) version 12.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 12.3.0, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/12/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/12/../../../../x86_64-linux-gnu/include"
<!--(3)!-->#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-linux-gnu/12/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
GNU C17 (Ubuntu 12.3.0-1ubuntu1~23.04) version 12.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 12.3.0, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: d9353c3f0a32d3e91a16ba312e2a9024
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog-'
<!--(4)!--> as -v --64 -o /tmp/ccAnKDEo.o /tmp/ccCWi0p2.s
GNU assembler version 2.40 (x86_64-linux-gnu) using BFD version (GNU Binutils for Ubuntu) 2.40
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog-'
<!--(5)!--> /usr/lib/gcc/x86_64-linux-gnu/12/cc1 -quiet -v -imultiarch x86_64-linux-gnu sum.c -quiet -dumpdir prog- -dumpbase sum.c -dumpbase-ext .c -mtune=generic -march=x86-64 -Og -version -fasynchronous-unwind-tables -fstack-protector-strong -Wformat -Wformat-security -fstack-clash-protection -fcf-protection -o /tmp/ccCWi0p2.s
GNU C17 (Ubuntu 12.3.0-1ubuntu1~23.04) version 12.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 12.3.0, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
ignoring nonexistent directory "/usr/local/include/x86_64-linux-gnu"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/12/include-fixed"
ignoring nonexistent directory "/usr/lib/gcc/x86_64-linux-gnu/12/../../../../x86_64-linux-gnu/include"
#include "..." search starts here:
#include <...> search starts here:
 /usr/lib/gcc/x86_64-linux-gnu/12/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
GNU C17 (Ubuntu 12.3.0-1ubuntu1~23.04) version 12.3.0 (x86_64-linux-gnu)
	compiled by GNU C version 12.3.0, GMP version 6.2.1, MPFR version 4.2.0, MPC version 1.3.1, isl version isl-0.25-GMP

GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
Compiler executable checksum: d9353c3f0a32d3e91a16ba312e2a9024
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog-'
 as -v --64 -o /tmp/ccgMFTqK.o /tmp/ccCWi0p2.s
GNU assembler version 2.40 (x86_64-linux-gnu) using BFD version (GNU Binutils for Ubuntu) 2.40
COMPILER_PATH=/usr/lib/gcc/x86_64-linux-gnu/12/:/usr/lib/gcc/x86_64-linux-gnu/12/:/usr/lib/gcc/x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/12/:/usr/lib/gcc/x86_64-linux-gnu/
LIBRARY_PATH=/usr/lib/gcc/x86_64-linux-gnu/12/:/usr/lib/gcc/x86_64-linux-gnu/12/../../../x86_64-linux-gnu/:/usr/lib/gcc/x86_64-linux-gnu/12/../../../../lib/:/lib/x86_64-linux-gnu/:/lib/../lib/:/usr/lib/x86_64-linux-gnu/:/usr/lib/../lib/:/usr/lib/gcc/x86_64-linux-gnu/12/../../../:/lib/:/usr/lib/
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog.'
<!--(6)!--> /usr/lib/gcc/x86_64-linux-gnu/12/collect2 -plugin /usr/lib/gcc/x86_64-linux-gnu/12/liblto_plugin.so -plugin-opt=/usr/lib/gcc/x86_64-linux-gnu/12/lto-wrapper -plugin-opt=-fresolution=/tmp/ccFqz8G9.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s -plugin-opt=-pass-through=-lc -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_s --build-id --eh-frame-hdr -m elf_x86_64 --hash-style=gnu --as-needed -dynamic-linker /lib64/ld-linux-x86-64.so.2 -pie -z now -z relro -o prog /usr/lib/gcc/x86_64-linux-gnu/12/../../../x86_64-linux-gnu/Scrt1.o /usr/lib/gcc/x86_64-linux-gnu/12/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/12/crtbeginS.o -L/usr/lib/gcc/x86_64-linux-gnu/12 -L/usr/lib/gcc/x86_64-linux-gnu/12/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/12/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/12/../../.. /tmp/ccAnKDEo.o /tmp/ccgMFTqK.o -lgcc --push-state --as-needed -lgcc_s --pop-state -lc -lgcc --push-state --as-needed -lgcc_s --pop-state /usr/lib/gcc/x86_64-linux-gnu/12/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/12/../../../x86_64-linux-gnu/crtn.o
COLLECT_GCC_OPTIONS='-Og' '-o' 'prog' '-v' '-mtune=generic' '-march=x86-64' '-dumpdir' 'prog.'

```

1.  最开头是 `gcc` 的相关信息，包括它运行的平台、配置的选项等。
2.  这里调用了 `cc1` 完成预处理和编译阶段，将源代码文件 `main.c` 编译成了 ASCII 编码的汇编文件 `/tmp/ccCWi0p2.s`。
3.  这里显示了头文件搜索路径，如果你编译时报错缺少头文件，可以检查一下这里有没有包含对应的路径。
4.  这里调用了 `as` 完成汇编阶段，将汇编文件 `/tmp/ccCWi0p2.s` 翻译成了机器语言文件 `/tmp/ccAnKDEo.o`。
5.  接下来又对 `sum.c` 重复预处理、编译和汇编的过程，得到了 `/tmp/ccgMFTqK.o`。
6.  最后调用 `collect2` 完成链接阶段，将两个源代码生成的目标文件 `/tmp/ccAnKDEo.o` 和 `/tmp/ccgMFTqK.o` 与其他很多目标文件链接成了可执行文件 `prog`。这就是你能在操作系统上运行的程序。


<!-- prettier-ignore-start -->
??? question "我怎么没有看见运行了 `cpp` 呢？"

    某些版本的 `gcc` 会将预处理器 `cpp` 和编译器 `cc1` 合并成一个程序，这样就不会显示预处理阶段的信息了。
<!-- prettier-ignore-end -->

### 链接

你会注意到，这参与链接的 `.o` 文件非常之多，其中很多位于 `x86_64-linux-gnu` 这样的文件夹下，这一般是操作系统提供的库文件。这些库文件包含了很多常用的函数，比如 `printf`、`malloc` 等。如果你的程序中使用了这些函数，那么链接器就会将这些库文件链接到你的程序中。




## 参考资料

<!-- prettier-ignore-start -->
!!! info "参考资料"

    - [GCC and Make - A Tutorial on how to compile, link and build C/C++ applications](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)

<!-- prettier-ignore-end -->