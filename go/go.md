##### 变量

```go
var i, j int

//赋初值：类型自动推导
var c, python, java = true, false, "no!" 
//函数体内初始化，可不写var
k := 3 

//常量，不能用:=
const con = 42

//指针，没有指针运算
var p *int
p = &i
*p = 3

//结构体
type Vertex struct {
	X int
	Y int
}
v  := Vertex{1, 2}  //初始化
v2 := Vertex{X: 1}  // Y:0 被隐式地赋予
v3 := Vertex{}      // X:0 Y:0
p  := &Vertex{1, 2} // 指针
v.X = 4 //访问成员
p.X = 4 //指针访问成员


```

声明变量是可用`var (a1 T, a2 T, a3 T)`声明多个变量。

容器一般都可用`{}`初始化内容。



**零值**（变量默认值）

```
0 false "" 
nil//切片、映射
```



##### slice

**数组** 不可变长

```
var a [10]int
primes := [6]int{2, 3, 5, 7, 11, 13}
```

**切片** 动态数组

切片类型为[]int，范围为`[low,high)`，下标从0开始。

数组的切片

```
//修改切片，会修改底层的数组/切片
var s []int = primes[1:4]
q := []int{2, 3, 5, 7, 11, 13}
```

创建切片

```go
a := make([]int,5)		//len(a)=5
b := make([]int,0,5)	//len(b)=0, cap(b)=5
```

获取切片的属性

```
len(s)		//长度
cap(s)		//容量
```

追加元素

```
var s []int
s = append(s, 1)
s = append(s, 2, 3, 4)
//容量按需增长，可一次性追加多个
```

遍历切片/映射

```
//每次迭代返回两个值，下标和对应元素的副本
for i, v := range s {}
//可用_忽略i或v
for _, v := range s {}
//若只需要索引，可写成
for i := range s
```

切

```
a[:10]
a[0:]
a[:]
b = b[:cap(b)] //扩展到最大
```

切片可以切自己，但每次切的low、high都是相对于当前切片的范围

1. low值会导致切片前low的元素被舍弃，即cap减少
2. high值会扩展其长度len，但是不能超过cap



##### map

```go
//创建string到int的映射
var m map[string]int		//声明变量（不能添加键）
m := make(map[string]int)	//初始化
m := map[string]int{"Bell":40} //列表初始化，类似json
//修改
m[key] = elem	//添加
delete(m,key)	//删除
elem, ok := m[key] //检测key是否存在，存在则ok为true
```





##### defer

函数的参数立即求值，但函数本身推迟到外层函数返回之后调用。

多个defer会把函数压入栈中，最后逆序调用。

```go
func main() {
	defer fmt.Println("world")
	fmt.Println("hello")
}
```



##### strings

```go
//返回一个字符串
fmt.Sprintf("%v.%v.%v.%v",ip[0],ip[1],ip[2],ip[3])

//合并，将[]string合并为string，并添加" "分隔
strings.Join(list, " ")

//切割，将s string分割为[]string，按照空格分割
list := strings.Fields(s)
```



### 并发

##### Go roution

```go
go f(x,y,z) //参数的值在当前线程中计算出
```

##### 信道

```go
ch :=make(chan int) //创建信道
ch := make(chan int, 100) //指定缓冲大小

//发送者&接收者 线程间通过等待信道的数据，实现同步
ch <- v    // 将 v 发送至信道 ch。
v := <-ch  // 从 ch 接收值并赋予 v。

//信道关闭
close(ch) //发送者关闭信道
v, ok := <-ch //接收者可以检查信道关闭
for i := range ch //接收者不断接收，直到信道关闭
```

##### select

```go
//等待多个信道，直到某个信道可用
select {
case c <- x: 	//信道c可写
	...
case <-quit:	//信道quit可读
	fmt.Println("quit")
	return
default:		//其他信道都阻塞
    time.Sleep(50 * time.Millisecond)
}
```

##### mutex

```go
import (
	"sync"
)

// 让结构体自带一个mutex锁，用于实现安全的并发访问
type SafeCounter struct {
	v   map[string]int
	mux sync.Mutex
}

// 增加计数值。
// 使用lock和unlock包围
func (c *SafeCounter) Inc(key string) {
	c.mux.Lock()
	c.v[key]++
	c.mux.Unlock()
}

// 返回计数器的值。
// 返回值为互斥资源时，使用defer进行unlock
func (c *SafeCounter) Value(key string) int {
	c.mux.Lock()
	defer c.mux.Unlock()
	return c.v[key]
}

func main() {
	c := SafeCounter{v: make(map[string]int)} //互斥量使用默认初始化
```





### 函数

函数对象

```
//声明一个函数对象
sum := func(x, y int) int {
	return math.Sqrt(x*x + y*y)
}

//函数作为参数（形参的类型为函数签名）
func compute(fn func(int, int) int) int {
	return fn(3, 4)
}
```

闭包

```go
//函数内保存了静态变量cnt
//返回一个函数，赋值给pos
//每次调用pos()，都会导致cnt++
func adder() func() int {
	cnt := 0
	return func() int {
		cnt += 1
		return cnt
	}
}

pos := adder()
```

方法

```go
//定义函数Abs()，使其“接收”一个结构体Vertex
func (v Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

//则可把结构体当做class，调用其方法
func main() {
	v := Vertex{3, 4}
    fmt.Println(v.Abs()) //调用Abs()
}
```

注：

1. 接收者不能为内建类型
2. 接收者可以为指针`(v *Vertex)`，则可用于修改v对象的内容
3. 不论方法的接收者为值或指针接收者，结构体调用方法时，会自动根据方法的声明，将结构体转换为指针或值。

### 接口

```go
//抽象基类，只定义了方法
type Abser interface {
	Abs() float64
}

//&v指针对象实现了接口a定义的方法
func (v *Vertex) Abs() float64 {
	return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

//抽象基类a:所有实现了接口中函数的对象都可以当成它
var a Abser
a = &v
a = v //错误，v对象没有实现对应的方法
```

查看接口变量保存的具体子类

```
fmt.Printf("(%v, %T)\n", i, i)
```

类型断言

```
s := i.(string)		//接口i保存的具体类型如果为string，则赋值给s；若断言为假，则s为零值
s, ok := i.(string) //ok用于查看断言是否为真
```

类型选择

```
switch v := i.(type) { //这里的type就是“type”四个字
case T:
    // v 的类型为 T
case S:
    // v 的类型为 S
default:
    // 没有匹配，v 与 i 的类型相同
}
```

##### stringer接口

```
type Stringer interface {
    String() string
}
```

用于fmt包的函数

```go
type Person struct {
	Name string
	Age  int
}

//实现stringer接口
func (p Person) String() string {
	return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

//调用fmt.Println
func main() {
	a := Person{"Arthur Dent", 42}
	z := Person{"Zaphod Beeblebrox", 9001}
	fmt.Println(a, z)
}
```

##### error接口

```
type error interface {
    Error() string
}
```

错误

```go
//error的子类，保存错误信息
type MyError struct {
	When time.Time
	What string
}

//实现接口，用于指定错误信息格式
func (e *MyError) Error() string {
	return fmt.Sprintf("at %v, %s",
		e.When, e.What)
}


func run() error {
    //出错时，返回error对象
		...
        return &MyError{
            time.Now(),
            "it didn't work",
        }
    //不出错，返回nil
    return nil
}

func main() {
    //err不为nil，则表示出错，fmt.Println(err)打印错误
	if err := run(); err != nil {
		fmt.Println(err)
	}
}
```

##### io.reader接口

包含一个Read方法，用于将字节写入b，并返回读入的字节数

```
func (T) Read(b []byte) (n int, err error)
```



```go
import (
	"fmt";"io";"strings"
)

func main() {
	//io流
	r := strings.NewReader("Hello, Reader!")
	
    //缓冲区
	b := make([]byte, 8)
	
    //每次读8个字节，返回读入的字节数，直到读到EOF
	for {
		n, err := r.Read(b)
		fmt.Printf("n = %v err = %v\n", n, err)
		fmt.Printf("b[:n] = %q\n", b[:n])
		if err == io.EOF {
			break
		}
	}
}
```





### 其他

##### 类型

```go
bool
string
int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr
byte // uint8 的别名
rune // int32 的别名
    // 表示一个 Unicode 码点
float32 float64
complex64 complex128


func main() {
    ToBe	bool	= false
    fmt.Printf("Type: %T Value: %v\n", ToBe, ToBe)
}
//输出
//Type: bool Value: false
```



##### 控制流

**循环**

（无括号）

```go
for i := 0; i < 10; i++ {
	sum += i
}

//while循环
for sum < 1000 {
	sum += sum
}

//无限循环
for {
}
```



**if条件**

（无括号，可多条语句）

```go
if i := 1; x < 0 {
	...
} else {
	...
}
```



**switch**

(从上到下匹配，每个case不用写break)

```go
switch ...; i {
case 0:
    ...
case f():
    ...
default:
    ...
}

//switch可以不写条件，当成if-else
t := time.Now()
switch {
case t.Hour() < 12:
	fmt.Println("Good morning!")
case t.Hour() < 17:
	fmt.Println("Good afternoon.")
default:
	fmt.Println("Good evening.")
}
```



