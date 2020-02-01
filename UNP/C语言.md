`strlen(buff)`：字符串长度

`strcpy(* dest, * src)`：拷贝字符串

`strcat(* str1, * str2)`：连接字符串

`atoi(* str)`：字符串 to 整型



从字符串`str[]`中读取变量（返回成功赋值的变量个数）：

```
sscanf(* str, "%d...", * v1, ...)
```

向字符串`str[]`写入（自动检查写入溢出；之后可调用`n = strlen(str)`来获取写入文本的大小）：

```
snprintf(* str, sizeof(str), "%d...", var1, ...)
```



从输入流（stdin）读一行，输出一行到输出流（stdout）：

```
char *fgets(char *str, int n, FILE *stream)
int fputs(const char *str, FILE *stream)
```

