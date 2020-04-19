[effective-modern-cpp](https://downdemo.gitbook.io/effective-modern-cpp/)



- [ ] unique_ptr
- [ ] 命名空间
- [ ] lambda
- [ ] thread
- [ ] RAII
- [ ] move



虚函数，虚函数表？

四种类型转换？

红黑树、跳表、hash表？



`typedef typename Base::pointer pointer`？

typedef int T[100]：声明类型int[100]的别名为T

using xxx = typename aaa：声明类型aaa的别名xxx



运算符重载

```c++
T& operator++()		//前置++i
T operator++(int)	//后置i++，一般会调用前置++
T* operator->() const	{ return &(operator*()); }	//->返回一个指针，然后编译器会再次对这个内置指针执行一次->
```





拷贝构造：参数类型必须为&或const &，绝对不能为自己的类类型的值传递（循环调用）。



sizeof(数组)：整个数组的大小

sizeof(指针)：指针的大小4/8 byte（32/64位）（而不是数组大小）

当数组作为函数的参数传递后，数组自动退化为指针！



new

```c++
vector* vec = new vector();		
char* str = new char;
char* str = new char[len+1];	//长度别忘了\0
```



cstring操作

```c++
const char *	//cstr的类型

ch != '\0'		//判结尾
strlen(cstr)	//\0不计入长度
strcpy
Sprintf
```

string

```c++
s.data()		//返回cstr，包含\n
```



##### 栈

```c++
stack<int> stk;    //创建栈
stk.push(item);
int item = stk.top(); //返回栈顶元素，但不弹出
stk.pop();         //弹出栈顶元素，但不返回它的值
```



##### 内存空间



Static

1. 生存期：局部变量vs静态变量。静态变量，分配在静态存储区，在数据段中。函数退出之后，变量值不变。
2. 全局变量vs全局静态变量：作用域。全局的静态变量、静态函数只能在本文件中使用。而非静态全局变量的作用域是整个源程序。