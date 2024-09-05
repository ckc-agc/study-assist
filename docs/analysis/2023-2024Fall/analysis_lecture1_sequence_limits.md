# 第一讲 数列极限

- [PDF 版](analysis_lecture1_sequence_limits.pdf)

## 实数完备性定理

### 要求

1. 给出概念、定理的名字可以使用数学语言准确叙述。

2. 掌握基本的定理证明链（详细参考1.4.1 1.4.2）：

    * 确界原理$\rightarrow$单调有界定理$\rightarrow$致密性定理$\rightarrow$Cauchy准则

    * 单调有界定理$\rightarrow$闭区间套定理$\rightarrow$有限覆盖定理（聚点原理和Dedekind分割定理不要求）

    * 确界原理$\rightarrow$各个定理

3. 期末考试会在这几个定理里出叙述题和证明题；小测会考各个定理的数学叙述细节。

### 概念叙述

1. 有界，无界

    $$
    \begin{align}
    数列有界: &\quad\forall n>0,\exists M\in \text{R},使|x_n|<M恒成立\\
    数列无界: &\quad\forall M\in \text{R},\exists n>0,使|x_n|>M \\
    错误(?): &\quad\exists n>0,\forall M\in \text{R},使x_n>M
    \end{align}
    $$

    数学语言的否定：转换全称量词和存在量词，**注意量词顺序**，改变符号

2. 最大数，最小数
   
    $$
    \begin{align}
    \max\{S\}=a &\iff a\in S且\forall x\in S,a\ge x\\
    \min\{S\}=b &\iff b\in S且\forall x\in S,b\le x
    \end{align}
    $$

3. 上确界，下确界
    
    $$
    \begin{align}
    M=\sup\{S\}\iff& \forall x\in S,x\le M且\forall\epsilon>0,\exists x'\in S有x'>M-\epsilon\\
    m=\inf\{S\}\iff& \forall x\in S,x\ge m且\forall\epsilon>0,\exists x'\in S有x'<M+\epsilon
    \end{align}
    $$

### 定理叙述

1. 确界原理

    **非空有界**集必有上下确界

1. 单调有界定理

    单调有界数列必收敛

1. 致密性定理

    任何有界数列必有收敛子列

1. Cauchy准则
    
    $$
    a_n收敛\iff\forall \epsilon>0,\exists N>0,\forall m,n>N,均有|a_m-a_n|<\epsilon \\
    \iff \forall \epsilon>0,\exists N>0,\forall n>N,p>0,均有|a_{n+p}-a_n|<\epsilon
    $$

1. 区间套定理
    
    $$
    \begin{align}
    & 设闭区间列\{[a_n,b_n]\}满足:\\
    & 1.[a_{n+1},b_{n+1}]\subset[a_n,b_n],n=1,2,3..\\
    & 2.\lim_{n\to\infty}(b_n-a_n)=0 \\
    & 则存在唯一实数\xi，满足\xi\in[a_n,b_n],n=1,2..
    \end{align}
    $$

1. 有限覆盖定理
    
    $$
    \begin{align}
    & 设[a,b]是一个闭区间，\{E_\lambda\}_{\lambda\in\Lambda}是[a,b]的任意一个开覆盖，\\
    & 则必存在\{E_\lambda\}_{\lambda\in\Lambda}的一个子集构成[a,b]的一个有限覆盖。 \\
    \iff & 在\{E_\lambda\}_{\lambda\in\Lambda}必有有限个开区间E_1,E_2..E_N使[a,b]\subset\cup_{j=1}^NE_j
    \end{align}
    $$

### 常用技巧

1. 证明集合相等的常用方法：相互包含

    !!! example "例题：确界的关系式"
    
        设 $A,B$ 是两个由非负数组成的任意数集,试证明 $\sup_{x\in A}\{x\}\cdot \sup_{y\in B}\{y\}=\sup_{x\in A,y\in B}\{xy\}$


2. 对于实数完备性定理的证明题，首先将给的条件和证明内容均翻译成数学语言（方便骗分），再观察条件和证明内容的联系。

### 例题&习题

1. 用确界原理证明单调有界原理、致密性定理、Cauchy准则、闭区间套定理、有限覆盖定理。
2. 用单调有界定理证明闭区间套定理，用闭区间套定理证明有限覆盖定理；用致密性定理证明Cauchy收敛准则。
3. $f,g为D上有界函数,\text{pf:}\inf\{f(x)+g(x)\}\le\inf{f(x)}+\sup{g(x)}$
4. 设$f(x)在[0,1]上递增,f(0)>0,f(1)<1,求证:\exists x_0\in(0,1),使得f(x_0)=x_0^2$ (Hint:确界原理or区间套定理)
5. 设$f(x)$在$[a,b]$上有定义且在每一点处函数的极限存在，求证$f(x)$在$[a,b]$上有界 (Hint:有限覆盖)
6. $设f(x)在(a,b)内有定义，\forall\xi\in(a,b),\exists\delta>0,当x\in(\xi-\delta,\xi+\delta)\cap(a,b)时,$有当$x<\xi$时,$f(x)<f(\xi), 当x>\xi$时,$f(x)>f(\xi)$.请证明:$f(x)在(a,b)$内严格递增 (Hint:有限覆盖)

## 数列极限

### 要求

1. 从小测的角度来说，概念，定理以及判断题是比较重要（搞脑子）的，当然也会有计算题
2. 期末考试可能会出1-2道求极限，1道非常简单的极限证明题（附在定理叙述上）
3. 计算也需要掌握，但是技巧性强的可以不掌握
4. 学好数列极限对函数极限和级数都很有帮助，而学好了函数极限就可以学好导数和积分，然后你就学会了数分1

### 概念叙述

1. 数列极限（$\epsilon-N$语言）

$$
\forall\epsilon>0,\exists N>0,\forall n>N,|x_n-A|<\epsilon称\lim_{x\rightarrow\infty}x_n=A\\
  *:|x_n-A|<f(\epsilon),f(x)满足\lim _{x\rightarrow0}f(x)=0即可
$$

2. 数列发散

$$
\forall A\in R,\exists\epsilon_0>0,\forall N>0,\exists n_N>N,|x_n-A|\ge\epsilon_0
$$

1. 子列
    
    $$
    \{a_n\}收敛\iff \{a_n\}的任意子列都收敛于A(请注意减弱命题)
    $$

2. 无穷小量和无穷大量
    
    $$
    \begin{align}
    & 无穷小量 : \lim_{x\rightarrow\infty}= 0 \\
    & 无穷大量 : \forall M>0,\exists N,\forall n>N,|x_n|>M
    \end{align}
    $$

### 定理叙述

1. Stolz定理

    常用于计算形式需要洛必达的极限

2. Cauchy收敛准则、等价形式及否定

$$
\begin{align}
  a_n收敛& \iff\forall \epsilon>0,\exists N>0,\forall m,n>N,均有|a_m-a_n|<\epsilon \\
  & \iff \forall \epsilon>0,\exists N>0,\forall n>N,p>0,均有|a_{n+p}-a_n|<\epsilon \\
  否定形式:a_n发散& \iff\exists\epsilon_0>0,\forall N,\exists n_0>N,p>0,|x_{n_0+p}-x_{n_0}|\ge\epsilon_0
  \end{align}
$$

### 常用技巧

1. 一些关系链：
    1. $n\rightarrow\infty时$
    
    $$
      \log\log n\ll \log n \ll n^a\ll b^n\ll n!\ll n^n\quad(a,b>0)
    $$

    2. $x\rightarrow0时$
    
    $$
    \begin{align}
      x  \sim &\sin x\sim \tan x \sim \arcsin x\sim \arctan x \\
         \sim &\ln{(1+x)} \sim \text{e}^x-1 \sim \frac{a^x-1}{\ln a}\sim \frac{(1+x)^b-1}b \quad(a>0,b\neq0)\\
        & 1-\cos x \sim \frac12 x^2
      \end{align}
    $$

2. 证明数列极限存在：

    1. 定义（$\epsilon-N$方法）

    技巧：放大法(常用)/分步法/构造形式类似的项/拟合法(技巧性较强)

    2. Cauchy准则：不需要知道极限值

    3. Cauchy准则的推论：常用于判断数项级数是否收敛($a_n=\sum_{n=1}^{\infty}f(n)$)

    4. 单调有界原理：不动点，递推式考虑

    5. 极限的运算性质：本身存在极限 有限项运算

2. 证明数列极限不存在：

    1. Cauchy命题的否定形式
    2. 子列不收敛或收敛于不同的数

3. 求数列(函数)极限：

    1. 极限的运算性质

    一些重要极限：$\lim\limits_{n\rightarrow\infty}n^\frac1n=1$，$\lim\limits_{n\rightarrow\infty}(1+\frac1n)^n=e$

    2. Stolz定理

    3. 夹逼定理

    4. 等价代换与初等变形

    5. 递推形式的极限：单调有界原理+证明/压缩映像(略难)/Stolz公式的应用

    6. Taylor/L'Hospital/积分定义/数项级数/级数的连续性...：
    很重要，但这是后事了

### 例题&习题

1. 判断下列关于子列的命题

    1. 设$\{a_n\}$是一个数列，若在任一子列$\{a_{n_k}\}$中均存在收敛子列$$\{a_{n_{k_r}}\}$$,则$$\{a_n\}$$必收敛
    2. $\{a_n\}单调递增，\{a_{n_k}\}为其中一个子列，\lim\limits_{k\rightarrow\infty}a_{n_k}=a,则\lim\limits_{n\rightarrow\infty}{a_n}=a$
    3. $\{a_{2k}\}\{a_{2p+1}\}\{a_{2023t+2024}\}均收敛，则\{a_n\}收敛$
    4. $\{a_{2k}\}\{a_{2t+1}\}\{a_{6p+5}\}均收敛，则\{a_n\}收敛$

2. 判断下列关于无穷小量的命题

    1. 无穷多个无穷小量之和是无穷小量
    2. 无穷多个无穷小量之积是无穷小量
    3. 无穷小量与有界量之积为无穷小量

3. 判断下列关于数列极限的命题

    1. 数列$a_n$收敛$\iff \forall p\in N,\lim\limits_{n\rightarrow+\infty}{|a_{n+p}-a_n|=0}$
    2. $\lim\limits_{n\rightarrow\infty}x_n=A\iff\forall k\in \text{N},\exists N>0,\forall n>N,|x_n-A|<\frac1k$
    3. $a_n收敛 \iff \exists N>0,\forall \epsilon>0,\forall m,n>N,均有|a_m-a_n|<\epsilon$

4. 重要的二级结论：

$$
Cauchy定理:\lim_{n\rightarrow\infty}x_n=A,则\lim_{n\rightarrow\infty}\frac{x_1+x_2+...+x_n}{n}=A
$$

5. $x_n=\sum_{i=1}^n\sin(\frac{2i-1}{n^2}a),\text{pf:}\lim\limits_{n\rightarrow\infty}x_n=a$ (Hint:拟合法)

6. 求极限$\lim\limits_{n\rightarrow\infty}x_n$：

    1. $x_n=\cos\frac x2\cos\frac x{2^2}\cdots\cos\frac x{2^n}$
    2. $x_n=(\frac{\sqrt[n]a+\sqrt[n]b}{2})^n$
    3. $x_n=\frac 1{\sqrt[n]{n!}}$
    4. $x_n={(n!)}^{\frac1{n^2}}$
    5. $x_n=\sqrt[6]{x^6+x^5}-\sqrt[6]{x^6-x^5}$

7. (2019(?)年数分1期末)

$$
\begin{align}
  & 对于数列x_0=a,0<a<\frac\pi2,x_n=\sin x_{n-1}(n=1,2,\cdots). \\ &\text{pf:}(1)\lim\limits_{n\rightarrow\infty}x_n=0;(2)\lim\limits_{n\rightarrow\infty}{\sqrt\frac n3}x_n=1
  \end{align}
$$
