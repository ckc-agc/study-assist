# 课前：MAGIC 函数

请复制此份程序到你的编辑器中。我们将会直接在这份程序的基础上进行授课。

不需要读懂并理解这段程序的意义。感兴趣的同学可自行研究。

```c
#define _STR0(x) #x
#define _STR(x) _STR0(x)
#define _MAGIC0(name, val, size) _magic_print((name), (const uint8_t *)(val), (size))
#define MAGIC(v) _MAGIC0(_STR(v), (&v), sizeof(v));
#define MAGIC_R(v)                      \
  ({                                    \
    __typeof__(v) _v = v;               \
    _MAGIC0(_STR(v), (&_v), sizeof(v)); \
  });
#define MAGIC_SIZED(v, size) _MAGIC0(_STR(v), (&v), (size));
#define MAGIC_PTR(v) fprintf(stderr, "%s: %p\n", _STR(v), (void *)(v));

static void _magic_print(const char *name, const uint8_t *ptr, size_t size) {
  fprintf(stderr, "=====\n%s: %zu (%#zx) byte%s", name, size, size, ("s") + (size == 1));
  for (size_t i = 0; i < size; i++) {
    if (i % 16 == 0)
      fprintf(stderr, "\n%0*zx ", 4, i);
    fprintf(stderr, " %02hhx", ptr[i]);
  }
  fprintf(stderr, "\n");
}

int main() {
  // start our journey here...
  MAGIC_R(0x12345678);

}
```
