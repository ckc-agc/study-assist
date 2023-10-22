# 常见问题

<!-- prettier-ignore-start -->
!!! danger "施工中"
<!-- prettier-ignore-end -->

## 指针、声明

### 怎么读声明？

-   详见：[Reading C type declarations (unixwiz.net)](https://unixwiz.net/techtips/reading-cdecl.html)

### 函数与函数指针

> Author：45gfg9、Anston Sun

首先，让我介绍一下两个惹人喜爱的小家伙。

```c
int function(int arg)
{
    return 2 * arg;
}
```

一般通过函数，**类型是 `int (int)`**。

```c
int (*func_ptr)(int);
```

芝士什么？芝士函数指针，**类型是 `int (*)(int)`**。

那么，这两个小家伙能干什么呢？

```c
func_ptr = &function;
func_ptr = function;
```

前者是什么？指针。没错，平平无奇的取地址操作，洒洒水啦。
后者是什么？我们知道指针的值实际上是某块内存地址，不考虑奇技淫巧的话，将所指对象的值赋值给指针是没有意义的。但是，将函数指代器 `function` 赋值给函数指针 `func_ptr`，却没有产生任何问题。

坏了，自动播放妈妈生的，大脑要打高端局了。不过你先别急，这个看起来不知所云的赋值语句，其实与前者完全等效。C 标准是仁慈的，它不忍心看到被函数绕晕的初学者面对错误的解引用不知所措，于是规定了函数到指针的*隐式转换*。

> #### 函数到指针转换
>
> 任何函数指代器表达式，在用于**异于下列语境**时
>
> -   作为取址运算符的操作数
> -   作为 `sizeof` 的操作数
>
> 会经历到指向<u>表达式所指代函数</u>的指针的转换。

这里 `function` 经过一次隐式转换变成 `&function`。这一步转换并不改变值，而**类型从 `int (int)` 变成 `int (*)(int) `** 了。也就是实际上在编译器看来，第二行就是第一行。

现在你已经对函数和函数指针有了一定了解，就让我们看一看下面这个简单的例子，把我们已经学到的知识运用到实践中吧。

请解释以下代码的作用：

```c
// 试试看！
(*(void(*)())0)();
```

好吧，这样的表达式或许对你来说为时尚早。我们换一个简单点的例子。

```c
function(20);
(function)(20);
(*&function)(20);
(&function)(20);
(*function)(20);
(***********function)(20); // 不用数了，11 个
```

先不管第六个是什么东西。我们看看前五个。

第一个不能再熟悉了，一个人畜无害的函数调用。

第二个看着和第一个差不多……没错，相信自己，它们完全一样。

第三个呢？没错，取地址再解引用，除了出题没有用。连编译器都会毫不犹豫地优化掉。

第四个开始奇怪了起来。缺失的解引用并非粗心大意，它象征着我们玩转指针的自信与惬意，以及捍卫指针地位的决心。鉴于 **C 标准允许通过函数指针调用函数**，编译器对此也没什么意见。

第五个换了种折磨方式。聪明如你早已料到最后的结果。但是为什么？引言定真，鉴定为隐式转换惯的。回忆一下**函数到指针的隐式转换**，`*function` 等效于 `*&function`，这下看懂了。

现在第六个你应该也能理解了。每次尝试对 `function` 解引用，都会迫使编译器将它转换为函数指针，以满足你对代码风格的奇怪癖好。

还是看看远处的 `func_ptr` 吧家人们。

```c
(*func_ptr)(20);
func_ptr(20);
(****func_ptr)(20);
(&func_ptr)(20);
```

第一个，简单易懂的指针解引用，相当于上面的第二个。

第二个，人畜无害的函数指针调用函数，相当于上面的第四个。

第三个，函数到指针的隐式转换发生了整整三回啊三回，类似上面的第六个。

**第四个，编译器跟你爆了**。怎么会是呢？我们不妨拆开看看：

```c
int (*func_ptr)(int) = &function;    // 这是之前的
int (**second_ptr)(int) = &func_ptr; // 这是我们正在做的
second_ptr(20);                      // 我们想这样
```

在这里，`second_ptr` 已经是个二级指针了。**函数到函数指针（它是个一级指针）的变化，地址值是不会改变的，就是这个函数的可执行代码所在的位置**。问题在于，二级指针的值不是 `function` 的地址，而是 `func_ptr` 这个变量的地址。这还得了，骗自己可以，骗兄弟也就算了，编译器可不吃你这套。

接下来，我们再看点不太一样的：

```c
int func_two(int a, int f(int arg))
{
    return 3 * f(a);
}
```

这是什么？函数，调用一下：

```c
// function 如上文定义
int function(int arg);

int a = 1;
int b = func_two(a, function);
```

相信聪明的你已经猜到了，`b` 的值就是 6。桥豆麻袋，好像有哪里不太对劲。`func_two` 的两个参数类型分别是 `int` 和 `int (int)`，但是调用时却传入了一个函数指针（还记得隐式转换吗？），这却没有产生任何问题。这又是什么操作？

又是隐式转换？Bingo！不过需要注意发生隐式转换的位置。`func_two` 的第二个形参实际上是 `int (*)(int)` ，而非字面上的 `int (int)`。这就和 `void f(int a[])` 实际上就是 `void f(int *a)` 一样，同样是出于节约资源的考虑。也就是说，编译器眼中的 `func_two` 是 `int func_two(int a, int (*f)(int)`。搞清楚这一点，其余部分也就顺理成章了。

经过练习，你应该已经可以看出，从**函数到指针的隐式转换**规定出发，理解上述情景并非难事。对函数指针的畏惧，往往是因为不熟悉转换规则，或受复杂的声明语法干扰。因此，提高识别类型的熟练度，足以让你自信运用函数指针。

## 图形库

简要整理一下 `libgraphics` 用法：

### 必备函数

图形与文字

> 值得注意的一点是：`libgraphics` 的坐标系统与 `ACLLib` 不同。前者以左下角为原点，符合我们常用的数学表达；后者以左上角为顶点，使用窗口坐标系统。
>
>   <img src="https://cdn.bowling233.top/images/2023/06/202306232338094.png" style="zoom:50%;" />

-   `void InitGraphics(void)`：使用图形库中的函数前调用
-   `void MovePen(double x, double y)`：将笔移动到某点（注意不是相对移动）
-   `void DrawLine(double dx, double dy)`：从当前点 $(x,y)$ 画到 $(x+dx, y+dy)$ 的线，画笔随之移动
-   `void DrawArc(double r, double start, double sweep)`：以当前点为圆心，从 $\phi=start$ 角开始，画半径为 $r$，圆心角为 $\Delta\phi=sweep$ 的圆弧。<img src="https://cdn.bowling233.top/images/2023/06/202306232336927.png" style="zoom: 50%;float:right" />
-   `double GetWindowWidth(void)`：获取窗口宽度
-   `double GetWindowHeight(void)`
-   `double GetCurrentX(void)`：获取当前画笔的位置
-   `double GetCurrentY(void)`
-   `void DrawTextString(string text)`：在当前位置打印字符串
-   `double TextStringWidth(string text)`：获取该字符串打印时的宽度

关于 `SetEraseMode()` 和 `GetEraseMode()` 我直接把注释贴在这了，直接读吧：

```c
/*
 * Function: SetEraseMode
 * Usage: SetEraseMode(TRUE);
 *        SetEraseMode(FALSE);
 * ---------------------------
 * The SetEraseMode function sets the value of the internal
 * erasing flag.  Setting this flag is similar to setting the
 * color to "White" in its effect but does not affect the
 * current color setting.  When erase mode is set to FALSE,
 * normal drawing is restored, using the current color.
 */

void SetEraseMode(bool mode);

/*
 * Function: GetEraseMode
 * Usage: mode = GetEraseMode();
 * -----------------------------
 * This function returns the current state of the erase mode flag.
 */

bool GetEraseMode(void);
```

> 还是附个翻译吧：SetEraseMode 函数设置内部擦除标志的值。设置这个值的效果就像把颜色设置为“白色”，但不会影响当前的颜色设置。当擦除模式设置为 FALSE 时，恢复到正常的绘画状态，使用当前的颜色。

控制台交互：这些源代码在 `simpio.h` 中

-   `void InitConsole(void)`：打开一个新的控制台，要使用 `stdio.h` 中的标准输入输出函数前记得写上这个。

-   `int GetInteger(void)`：从标准输入中读入一行，并尝试读取一个整数。如果遇到意外情况，会要求用户重新输入。源码如下：

    ```c
    int GetInteger(void)
    {
        string line;
        int value;
        char termch;

        while (TRUE) {
            line = GetLine();
            if (line == NULL) Error("GetInteger: unexpected end of file");
            switch (sscanf(line, " %d %c", &value, &termch)) {
              case 1:
                FreeBlock(line);
                return (value);
              case 2:
                printf("Unexpected character: '%c'\n", termch);
                break;
              default:
                printf("Please enter an integer\n");
                break;
            }
            FreeBlock(line);
            printf("Retry: ");
        }
    }
    ```

-   `double GetReal(void)`：读取一个实数，具体同上。

-   `string GetLine(void)`

-   `string ReadLine(FILE *infile)`：从指定的文件中读入一行。

### 定时启动——计时器回调

计时器用于延时或重复执行同类任务。相比钟表等纯粹的计时工具，计时器更接近于日程安排。计时器的核心功能如下：每经过*预先设定的时长*，计时器便会*通过某种机制*，执行*特定的指令*。

`libgraphics` 库通过*事件回调机制*实现定时触发的功能。回调机制此处不再赘述。

### 计时器

与计时器相关的函数如下：

-   `void startTimer(int timerID, int interval)`
-   `void cancelTimer(int timerID)`

顾名思义，两个函数分别用于启动与终止定时器。`interval` 是*预先设定的时长*，即每两次触发的时间间隔。`timerID` 为计时器的标识符，可理解为计时器的专用名称。

为了完成多项定时任务，往往需要分别启动多个间隔不同的定时器。由于所有计时器均会触发 `TimerEvent`，在回调函数内需要使用 `timerID` 区分不同的定时器。

#### 回调注册函数

-   `void registerTimerEvent(TimerEventCallback)`：注册计时器事件。 `TimerEventCallback` 类型见下。

#### 回调函数

-   `typedef void (*TimerEventCallback)(int timerID)`

`TimerEventCallback` 是一个函数指针类型，该类型变量指向函数（假设名称为 `func`）的类型为 `void func(int timerID)`。通过回调机制，每当任一计时器到达设定时间时，均会通过该类型函数指针调用 `func` 函数。通过传入的 `timerID`，回调函数内可以区分不同计时器的触发事件，并执行特定操作。

#### 补充思考

以上介绍均集中于重复执行，但是前面提到计时器也可用于延时执行，即在*预先设定的时长*后执行*特定次数*的*特定操作*。结合 `cancelTimer` 函数，想想怎样实现这一目标。

### 回调函数

```c
typedef void (*KeyboardEventCallback) (int key,int event);
typedef void (*CharEventCallback) (char c);
typedef void (*MouseEventCallback) (int x, int y, int button, int event);
typedef void (*TimerEventCallback) (int timerID);

void registerKeyboardEvent(KeyboardEventCallback callback);
void registerCharEvent(CharEventCallback callback);
void registerMouseEvent(MouseEventCallback callback);
void registerTimerEvent(TimerEventCallback callback);
void startTimer(int id,int timeinterval);
```

因为这些回调函数在 `graphics` 库中都没有注释，我就不作解释了，课上都讲过回调函数怎么用。

-   计时器：以 20 年程序填空第 3 题为例：

    ```c
    void Main()
    {
        InitGraphics();
        registerTimerEvent(TimerEventProcess);
        //...
        startTimer(TIMER_CURSOR, 500);/*start 500ms cursor blinking timer*/
    }
    void TimerEventProcess(int timerID)
    {
        bool erasemode;
        if(TIMER_CURSOR == timerID)
        {
            //...
        }
    }
    ```

    从这段例程中可以了解到几个重要的点：

    -   使用 `void registerTimerEvent(TimerEventCallback callback)` 注册回调函数 `callback` 后，还需要用 `void startTimer(int id,int timeinterval)` 设定并启动一个计时器，设定这个计时器的 `id` 和 `timeinterval`。
    -   每当计时器到达指定时间后，计时器就会调用所有的回调函数，回调函数会接收这个计时器的 `id` 并检查是不是自己需要进行动作的那个计时器。这就是 `TimerEventProcess` 函数中 `if` 语句的作用。

### 使用方法

-   主函数是 `void Main()` 别写错了
-   下面是一个最简单的例程：

```c
#include <stdio.h>
#include "graphics.h"

void Main(void)
{
    InitGraphics();
    MovePen(1.5, 1.0);
    DrawArc(0.5, 0, 360);
}
```

### `New()` 函数

向下翻，找到 2019 年程序填空第 3 题，使用方法在那里。

## 算法复杂度分析

-   记住：排序算法的时间复杂度与两项操作的次数有关：**比较**和**交换**。

    -   你可以这样想：创建一个全局变量作为计数器，在所有涉及比较和交换的地方让它 `++`，运行完的结果就是其时间复杂度。比如：

        ```c
        int count = 0;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < n; ++j) {
            for (int k = 0; k < m; ++k) {
                count++;
            }
          }
        }
        ```

        运行完这段代码，`count = n*n*m`，则其时间复杂度为 $O(n^2m)$。

-   记住并理解一些常见的算法的平均时间复杂度、最优、最差情况复杂度：![image-20230623223659304](https://cdn.bowling233.top/images/2023/06/202306232248681.png)

    来源：[常用排序算法总结对比 | 数据结构与算法 系列教程（笔记） (zq99299.github.io)](https://zq99299.github.io/dsalg-tutorial/dsalg-java-hsp/07/10.html)

## 后缀表达式

这东西前两三年都考了，需要了解一下。关于表达式树的相关内容请参见：

-   [表达式求值 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/misc/expression/)
-   [树基础 - OI Wiki (oi-wiki.org)](https://oi-wiki.org/graph/tree-basic/#树的遍历)

在前缀、中缀、后缀表达式之间进行转换的最好方法是将其想象成一个树状结构。

![](https://cdn.bowling233.top/images/2023/06/202306232250141.png)

-   中缀表达式：对这棵树进行中序遍历，即**左、根、右**
    -   a+b\*(c-d)-(e/f)
-   前缀表达式：对这棵树进行先序遍历，即**根、左、右**
    -   -+a\*b-cd/ef
-   后缀表达式：对这棵树进行后序遍历，即**左、右、根**。注意到左右子节点都比根先遍历，所以可以一路往下找到最深的子节点，然后向上解析。
    -   abcd-\*+ef/-

值得一提的是后缀表达式具有几个方便的性质：

-   计算后缀表达式，只需要维护一个数字栈，每次遇到一个运算符，就取出两个栈顶元素，将运算结果重新压入栈中。
-   后缀表达式与表达式树一一对应。后缀表达式不需要括号表示，它的运算顺序是唯一确定的。