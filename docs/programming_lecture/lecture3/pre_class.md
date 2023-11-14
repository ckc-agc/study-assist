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

2. 关于`printf()`

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

    你能解释为什么使用%ld输出long类型的值时，也会出现错误吗？

3. 关于`scanf()`

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

4. 文件

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