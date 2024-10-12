// conversion.c
#include <stdio.h>

int main(void)
{
    // 转换说明的各种用法

    // 1. 最小字段宽度
    printf("%%d: %d|\n", 123); // %d: 123
    printf("%%5d: %5d|\n", 123); // %5d:   123
    // 2. 标志
    printf("%%+5d: %+5d|\n", 123); // %+5d:  +123
    printf("%%-5d: %-5d|\n", 123); // %-5d: 123
    printf("%%05d: %05d|\n", 123); // %05d: 00123
    printf("%% 5d: % 5d|\n", 123); // % 5d:   123
    // 3. 精度
    printf("%%.2f: %.2f|\n", 123.456); // %.2f: 123.46
    printf("%%.2s: %.2s|\n", "hello"); // %.2s: he
    // 4. h/l/L
    printf("%%hd: %hd|\n", 123456); // %hd: -7616
    printf("%%ld: %ld|\n", 123456); // %ld: 123456
    // 5. *
    printf("%%*d: %*d|\n", 5, 123); // %*d:   123
    printf("%%*.*f: %*.*f|\n", 5, 2, 123.456); // %*.*f: 123.46
    return 0;
}