# I/O 与文件

<!-- prettier-ignore-start -->
!!! danger "施工中"

    本页面正在编辑中。
<!-- prettier-ignore-end -->

<!-- prettier-ignore-start -->
!!! abstract "内容提要"

    - C 的输入输出模型：缓冲与流的概念
    - C 标准 I/O 函数
    - 文件编码
<!-- prettier-ignore-end -->

## C 的输入输出模型

### 缓冲

<!-- prettier-ignore-start -->
!!! note "缓冲输入"
    
    用户输入的字符被收集并储存在缓冲区（buffer）中，**按下 ++enter++ 键后**程序才能使用用户输入的字符。

    - 完全缓冲：仅缓冲区填满时才发送内容、刷新缓冲区，通常用于**文件输入**。
    - 行缓冲：出现换行符时刷新缓冲区，通常用于**键盘输入**。
<!-- prettier-ignore-end -->

与之对应地，无缓冲输入的程序能够立即使用用户输入的内容。

C 标准规定：**输入是缓冲的**。

<!-- prettier-ignore-start -->
??? info "我可以更改输入方式吗？"
    
    UNIX 库中有 `ioctl()` 函数用于指定待输入的类型，但这不属于 C 标准。

    ANSI C 中，可以使用 `setbuf()` 和 `setvbuf()` 控制缓冲，但受限于系统的设置。
<!-- prettier-ignore-end -->

### 流

C 库提供的输入输出方式称为**标准 I/O**，它们是建立在操作系统提供的**底层 I/O** 上的。底层 I/O 之间常常会有一些差异：

<!-- prettier-ignore-start -->
!!! note "各个系统的文件差异"

    | 差异 | UNIX | Windows | MacOS |
    | - | - | - | - |
    | 换行符 | `\n`<br /> LF | `\r\n` <br />CRLF | `\n` (较早的 MacOS 使用 `\r`)<br />LF |
    | 文件结束符 | `^D` | `^Z` | `^D` |

    注：如 `^Z` 代表 `Ctrl+Z`，你可以使用该组合键结束键盘输入。

    文件结尾也不一定由文件结束符标记。事实上，UNIX 系统储存文件大小信息，依据文件大小信息决定文件末尾。
<!-- prettier-ignore-end -->

从概念上看，C 处理的是**流**而不是文件。不同属性和不同种类的输入，由属性更统一的**流**来表示。

<!-- prettier-ignore-start -->
!!! note "流"
    
    流就是一系列连续的字节。

    打开文件的过程就是把**流与文件相关联**，读写都通过流来完成。
<!-- prettier-ignore-end -->

`getchar()` 和 `scanf()` 等函数读取到文件结尾时会返回一个特殊的值 `EOF`，在 `stdio.h` 中定义了：

```C
#define EOF (-1)
```

你能解释为什么要把它定为 `-1` 吗？

## 字符输入输出

<!-- prettier-ignore-start -->
!!! note "函数和它们的功能"
    
    | 功能 | 函数 | 失败返回值 |
    | - | - | - |
    | `int getchar(void)`<br /> `int getc(FILE *stream)` <br /> `int fgetc(FILE *stream)` | 单字符输入 | EOF |
    | `char *fgets(char *s, int size, FILE *stream)` | 字符串输入 | NULL |
    | `int ungetc(int c, FILE *stream)` | 放回缓冲输入 | EOF |

    注意：以上函数都将字符从缓冲区中的 `unsigned char` 类型转换为 `int` 类型。

    那么这是否会造成 EOF 不能被识别，而是被看作字符呢？
<!-- prettier-ignore-end -->


<!-- prettier-ignore-start -->
!!! note "关于 `getchar()` 函数"
    
    它的返回值是 `int` 类型而非 `char` 类型，值得注意。
<!-- prettier-ignore-end -->

### 换行符问题

这是一个典型的问题：`scanf()` 函数，除了 `%c` 以外的转换说明，都不会读取空白字符（空格、制表符和回车）。

<!-- prettier-ignore-start -->
!!! note "写一个安全的输入函数"
    
    ```C
    char * s_gets(char* st, int n)
    {
        char * ret_val;
        int i = 0;

        ret_val = fgets(st, n, stdin);
        if (ret_val)
        {
            while (st[i] != '\n' && st[i] != '\0)
                i++;
            if (st[i] == '\n')
                st[i] = '\0';
            else //must have words[i] == '\0'
                while (getchar() != '\n')
                    continue;
        }
        return ret_val;
    }
    ```

    这个函数来自《C Primer Plus》，也是书中 13 章以后一直使用的输入函数。这个函数示范了如何使用安全的 `fgets()` 函数，并**将输入统一**，并处理剩余的字符。

    在涉及行的输入时，一定要注意统一行结尾的形式。这对于换行符，特别是**文件结尾处薛定谔的换行符**，有很大作用。
<!-- prettier-ignore-end -->

### 检查输入

可以用于检查输入的方式有以下几种：

1. `scanf()` 的返回值。


## 文件输入输出

## 标准库


## C standard library

### History of I/O model

- Before the UNIX system, 

- UNIX system designed I/O method isolated about devices. It treats all text stream using standard internal format.
    - `ioctl` is used to edit text stream for output.
    -


## 字符串的艺术

## 文件

本节结合 `<stdio.h>` 库和 C 标准内容。

### 基础概念

C 把文件看作连续的字节，每个字节都能被单独读取。C 提供两种文件模式，已经在开头介绍。

### 类型和宏

在 `<stdio.h>` 中有如下与文件相关的类型和宏：

- `FILE` 对象类型，记录控制**流**所需要的所有信息，包括：文件定位符、指向相关缓冲的指针、错误指示符和文件结束符。
    - 不要试图探索 `FILE *` 数据对象的内部，即使实现给出了某些可见域。不要修改对象、不要拷贝对象并代替使用，因为**实现假定知道流数据对象的所有地址**。
- `fpos_t` 对象类型，含有唯一指定文件中每个位置所需的所有信息。
- `stderr`, `stdin`, `stdout` 都是 `FILE*` 类型的表达式。
- `EOF` 展开为一个负的整值常量。
- `NULL`
- `SEEK_CUR` 文件当前位置
- `SEEK_END` 文件结束位置
- `SEEK_SET` 文件开始位置

### 函数

文件操作：

- `int remove (const char *filename)`
- `int rename (const char *old, const char *new)`
- `FILE *tmpfile(void)`
- `char * tmpnam(char *s)`

文件访问：

- `int fclose(FILE *stream)` 
    - 关闭文件，清空流（清空流就是传递缓冲数据），释放缓冲。
- `int fflush(FILE *stream)`
    - 立即写入（要求上一次操作是输出）。
- `FILE *fopen(const char *filename, const char *mode)`
- `FILE *freopen(const char *filename, const char *mode, FILE *stream)`
- `void setbuf(FILE *stream, char *buf)`
- `int setvbuf(FILE *stream, char *buf, int mode, size_t size)`

mode 字符串的含义：

| flag | meaning |
| - | - |
| r | read |
| w | write (new or cut) |
| a | append (new or append) |
| b | binary |
| + | update |

注意一下上面词语的含义，update 和 append 能写入的范围应该是不同的。

- append 模式下**所有写操作**强制加到文件结束处。
- update 模式下，若不调用文件定位函数，输入输出不一定相互紧跟。

对于 UNIX 这种只有一种文件类型的系统，带 `b` 与否的模式是相同的。

C11 中新增了 `x`，带该字母的写模式打开存在文件会失败（相当于加了保护），且允许独占。

格式化输入输出：

- `fprintf`
- `fscanf`
- `vfprintf`
- `vprintf`
- `vsprintf`

字符输入输出：

- `fgetc`
- `fgets`
- `fputc`
- `fputs`
- `getc`
- `getchar`
- [DECPRATED] `gets`
- `putc`
- `putchar`
- `puts`
- `ungetc`

其中，`fgetc()` 与 `getc()` 这类函数的不同是后者可能被实现为宏。

直接 I/O：

- `size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)`
- `size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)`

文件定位：

- `int fseek(FILE *stream, long int offset, int whence)`
- `long int ftell(FILE *stream)`
- `void rewind(FILE *stream)`

以下两个函数用于处理更大型的文件（`long` 无法表示的偏移值）

- `int fgetpos(FILE *stream, fpos_t *pos)`
- `int fsetpos(FILE *stream, const fpos_t *pos)`

错误处理：略


### 流和文件

C 标准是这样描述两种流的：

- 文本流：组成文本行的有序字符序列，每一行由零个或多个字符加上标志结束的换行符组成。
    - 实现定义：最后一行是否需要换行符、换行符正前面的空格是否在读取时出现等。
- 二进制流：字符的有序序列。



关于文件动作：

- 打开文件：流打开一个文件，就是与该文件**关联**。
    - 创建文件会丢弃内容。
    - 和流相关的文件定位符定位在文件起始位置。
    - 附加模式下定位位置由实现决定。
- 


### 在文件中移动

- offset 应该由 ftell 来决定。

### 二进制文件

