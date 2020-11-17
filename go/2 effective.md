### 自动格式化

gofmt或go fmt命令



### 命名

变量、函数：首字母大写表示包外可见，驼峰命名。

包名：小写的单个单词

接口名：只含一个方法的接口应该叫-er，如只含read方法叫Reader，因此可以Reader.read



### 控制语句

##### if

- 判断部分不用括号

- 以return结束的if后面不用写else

```
if err := file.Chmod(0664); err != nil {
    log.Print(err)
    return err
}

if ... {

} else if ... {

}
```





##### for

for循环

```
for i := 0; i < 10; i++ { }
```

while循环

```
for condition { }
```

无限循环

```
for { }
```

for range（返回 `index` 和 `value` ，用于array、slice、map）

```go
for key, value := range oldMap {
	newMap[key] = value
}
```

只要key / value

```
for key := range m
for _, value := range array
```

字符串

```
for pos, char := range "日本\x80語"
```

可变参数列表

```go
func Max(a ...int) int {
	max := 0
	for _, i := range a {	//a是实参列表的切片
		if i > max{
			max= i
		}
	}
	return max
}
```

多个变量时只能平行赋值（因为go中逗号不能分隔语句，i++也是语句）

```go
for i, j := 0, len(a)-1; i < j; i, j = i+1, j-1 {
```



##### switch

自上向下匹配，可代替else-if

```go
// case是t表达式时，switch后面可以不接变量t（否则应该如下面的“类型选择”那样写）
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

逗号分隔多个相同处理的条件

```go
case ' ', '?', '&', '=', '#', '+', '%':
	return true
```

类型选择

```go
var t interface{}
t = functionOfSomeType()
switch t := t.(type) {
default:
	fmt.Printf("unexpected type %T\n", t)     // %T 输出 t 是什么类型
case bool:
	fmt.Printf("boolean %t\n", t)             // t 是 bool 类型
case int:
	fmt.Printf("integer %d\n", t)             // t 是 int 类型
case *bool:
	fmt.Printf("pointer to boolean %t\n", *t) // t 是 *bool 类型
case *int:
	fmt.Printf("pointer to integer %d\n", *t) // t 是 *int 类型
}  
```



### defer

推迟调用到 “在函数返回之前” 执行。

被defer的函数的实参，在该语句出现的位置处，就已经求值决定，不会再变。

多个defer的函数按“后进先出”（栈）顺序执行。



### 数据

##### 常量

```go
type ByteSize float64
const (
    _           = iota // 通过赋予空白标识符来忽略iota的第一个值(0)
    KB ByteSize = 1 << (10 * iota)
    MB			// - 后面的常量自动应用上面的常量表达式，其中iota自增
    _			// - 下划线跳过一个枚举值，这里是跳过了GB，但iota仍然自增
    TB
    PB
)
```

- iota是常量计数器，只能用在常量表达式中。
- iota在const关键字出现时将被重置为0（const内部的第一行之前），const中每一行常量声明将使iota自增一次（iota可理解为const语句块中的**行索引**）。



##### 类型转换

```go
user, _ := c.Get("user")// 有些函数返回一个interface{}对象
user.(model.User).ID	// 使用该对象的ID字段时需要先类型转换为具体的对象
```





##### new

分配的内存置零，返回指针（0刚好是零值）

```
p := new(Obj)	//type *Obj
```



##### 初始化：复合字面

用来给对象初始化赋值

```go
return &File{fd, name, nil, 0}		//按“顺序”赋值
return &File{fd: fd, name: name}	//用“字段：值”赋值(没写的为零值)
```

构造函数写法如下：

```go
func NewFile(fd int, name string) *File {
	if fd < 0 {
		return nil
	}
	return &File{fd: fd, name: name}
}
```

注：可以返回一个**局部变量**的地址！！



##### make

只用于slice、map、channel，因为他们是引用，使用前必须初始化。

- 返回T，而不是指针*T。

```
v := make([]int, 100)	//分配100个int空间
```

如果明确是需要指针，则用new进行分配。



##### Slice

go数组不像C中是指针，数组的赋值是副本的拷贝!

- 切片底层就是数组的引用：因此传参时，可用slice作为形参类型，就可以模仿C的数组。
- [low,hign)

追加元素：

```
s = append(s, 1)
s = append(s, 2, 3, 4)	//添加任意多个元素
s2 := []int{5,6,7}
s = append(s, s2...)	//添加切片
```

追加后，可能导致底层数组扩容，因此需要把结果重新赋值给s（原数组等待gc回收）

深拷贝：

```go
s1 := []int{1,2,3}
// 深拷贝，修改s2不影响s1（好像只是单层的，如果元素是struct则可以，如果还是silce则需要递归）
s2 := make([]int, len(s1))
copy(s2, s1)
```







##### Map

- 只要类型支持相等判断，就可以做key（切片不行）

- 必须先创建，再赋值

  ```
  myMap := make(map[uint]uint, size)	//第二个参数size好像是必须的？
  ```

- 查找不存在的key时，会返回零值

  ```go
  seconds, ok = timeZone[tz]	// key不存在时ok = false
  // 用法
  if seconds, ok := timeZone[tz]; ok {
  		return seconds
  	}
  ```

- 删除某项

  ```
  delete(map, key)
  ```

  

##### 打印

有格式打印

```
fmt.Printf("Hello %d\n", 23)
```

无格式的拼接打印

```
fmt.Print("Hello ", 23)
```

自动加空格（Println系列）

```
fmt.Println("Hello", 23)
```

输出到文件（Fprint）、输出到字符串（Sprint）：

```go
fmt.Fprint(os.Stdout, "Hello ", 23, "\n")	// 或os.Stderr
str := fmt.Sprint("Hello ", 23)	// 生成字符串
```

注：

-  `%v` 可以打印任意类型，`%+v` 、`%#v` 输出更多信息。
-  `% x` 会在字节之间加空格。
-  `%T` 打印类型
- 给类实现`func (t *T) String() string`接口，即可自定义 `%v` 输出的格式



##### init函数

每个源文件都可以有一个`func init()`

- 发生在程序所有变量初始化之后、程序正式运行之前
- 可用于初始化变量
- 可用于检验、校正程序状态



##### 函数

```go
// 返回多个参数
func Apple() (ok bool, msg string) {
	ok = false
    msg = "错误信息"
    return
}
```





##### 方法

语义：带接收器的函数（类似C++中类的方法）

接收器可以为：

- 值：只能调用值方法
- 指针：可以调用指针方法和值方法



### 接口

##### 定义接口

- 可以用接口作为参数、返回类型
- 接口中可以内嵌接口，但内嵌多个接口要求不能有交叉的方法
- 结构体中可以包含一个接口的指针，则调用接口函数时，自动调用结构体中这个成员所实现的接口。

（如果只含一个方法，应该叫-er）

```go
type Abser interface {
	Abs() float64
}
```

##### 类型转换

将对象转为一个接口类型

```
接口名(实现了接口的对象)
```

##### 类型选择

```go
switch str := value.(type) {
case string:
	return str
case Stringer:
	return str.String()
}
```

##### 类型断言

检查对象能否作为某个接口来使用，可以则ok = true

```go
if str, ok := value.(string); ok {
	return str
} else if str, ok := value.(Stringer); ok {
	return str.String()
}
```


