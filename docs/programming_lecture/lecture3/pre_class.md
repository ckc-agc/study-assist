# 课前

把讲义里的小程序和命令行跑一跑，思考一下留下的问题～

1. 重定向运算符

    ```C title="echo_eof.c"
    /* echo_eof.c -- repeats input to end of file */
    #include <stdio.h>
    int main(void)
    {
        int ch;

        while ((ch = getchar()) != EOF)
        putchar(ch);

         return 0;
    }
    ```

    ```bash
    $ echo_eof < echo_eof.c
    $ echo_eof < echo_eof.c > echo_eof.txt
    $ echo_eof < echo_eof.c | cat
    ```

2. 关于*格式化字符串*

    ```C title="printf.c"
    #include <stdio.h>

    int main()
    {
        // 类型
        printf("%5d\n", 1000);  // 默认右对齐,左边补空格
        printf("%-5d\n", 1000); // 左对齐,右边补空格
        printf("%+d %+d\n", 1000, -1000); // 输出正负号
        printf("% d % d\n", 1000, -1000); // 正号用空格替代，负号输出
        printf("%x %#x\n", 1000, 1000); // 输出0x
        printf("%.0f %#.0f\n", 1000.0, 1000.0); // 当小数点后不输出值时依然输出小数点
        printf("%g %#g\n", 1000.0, 1000.0); // 保留小数点后后的0
        printf("%05d\n", 1000); // 前面补0

        // 宽度
        double a = 3.141592653589;
        int x = 5;
        printf("%.*f", x, a);

        // 精度
        printf("%.8d\n", 1000);           // 不足指定宽度补前导0，效果等同于%06d
        printf("%.8f\n", 1000.123456789); // 超过精度，截断
        printf("%.8f\n", 1000.123456);    // 不足精度，补后置0
        printf("%.8g\n", 1000.123456);    // 最大有效数字为8位
        printf("%.8s\n", "abcdefghij");   // 超过指定长度截断

        // 类型长度
        printf("%hhd\n", 'A');               // 输出有符号char
        printf("%hhu\n", 'A' + 128);         // 输出无符号char
        printf("%hd\n", 32767);              // 输出有符号短整型short int
        printf("%hu\n", 65535);              // 输出无符号短整型unsigned short int
        printf("%ld\n", 0x7fffffffffffffff); // 输出有符号长整型long int
        printf("%lu\n", 0xffffffffffffffff); // 输出有符号长整型unsigned long int
    }

    ```

3. 关于`printf()`

    ```C title="wrong_cnv.c"
    #include <stdio.h>
    #define num 336
    #define b 65618
    int main(void)
    {
        printf("num as short and unsigned short:  %hd %hu\n", num,num);
        printf("-num as short and unsigned short: %hd %hu\n", -mnum,-mnum);
        printf("num as int and char: %d %c\n", num, num);
        printf("b as int, short, and char: %d %hd %c\n",b, b, b);

        float n1 = 3.0;
        double n2 = 3.0;
        long n3 = 2000000000;
        long n4 = 1234567890;
        printf("%.1e %.1e %.1e %.1e\n", n1, n2, n3, n4);
        printf("%ld %ld\n", n3, n4);
        printf("%ld %ld %ld %ld\n", n1, n2, n3, n4);
        return 0;
    }
    ```

    该程序的输出结果为(**由于实现是未定义的，部分结果因系统和编译器而异**)：

    ```bash
    num as short and unsigned short:  336 336
    -num as short and unsigned short: -336 65200
    num as int and char: 336 P
    b as int, short, and char: 65618 336 R
    3.0e+00 3.0e+00 2.0e+09 1.2e+09
    2000000000 1234567890
    0 1074266112 0 1074266112
    ```

    你能解释为什么使用%ld 输出 long 类型的值时，也会出现错误吗？

4. 关于`scanf()`

    ```C title="confusing_scanf.c"
    #include <stdio.h>
    int main(void)
    {
        char c[100] = {0};
        scanf("%s\n",&c);
        printf("%s",c);
    }
    ```

    这个程序为什么这么奇怪？

5. 文件

    ```C title="c_file.c"
    #include<stdio.h>
    #include<string.h>

    int main(int argc, char *argv[]){
        const char *str = "ckc-agc programming lec3";

        FILE *fp1 = fopen("test1.txt", "wb+");
        FILE *fp2 = fopen("test2.txt", "w+");
        fprintf(fp1, "%s\n%s\n", str, argv[0]);
        fprintf(fp2, "%s\n%s\n", str, argv[0]);
        fwrite(str, sizeof(char), strlen(str), fp1);

        // fseek(fp1, 0, SEEK_SET);
        // fprintf(fp1, "%s\n", "SEEK_SET");
        fseek(fp1, 0, SEEK_END);
        fprintf(fp1, "%s\n", "SEEK_END");

        rewind(fp1);
        fprintf(fp1, "%s\n", "rewind");

        fclose(fp1);
        fclose(fp2);
    }
    ```

    ```bash
    $ file c_file.c
    $ file c_file.o
    $ file c_file
    $ objdump -h -s -d c_file.o
    $ objdump -h -s c_file
    ```
