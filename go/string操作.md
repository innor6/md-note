[TOC]



### 基础

1. 底层：**指针 + 长度**的只读字符（byte）数组。
2. 由于只读：因此字符串的复制、切片都是高效安全的（复制的是指针 + 长度）。
3. 采用UTF8编码，但 `len(s)` 是字节数，不是rune数。
4. 原生字符串：使用`号包围；所有内容都不会转义，适合编写正则表达式；可以跨行，会自动删除换行符。



##### ascii -> char

```Go
string(65)	// "A"
```

##### for遍历rune

```GO
for pos, char := range "日本\x80語" {
    // 隐式UTF8解码，这里的char取出来的是rune
}	
```

##### string <--> []byte 类型转换

```
b := []byte(s)
s := string(b)
```

##### bytes.Buffer缓存

利用 []byte缓存 高效拼接字符串

```go
// 打印列表中数字，并用逗号分隔
func intsToString(values []int) string {
    var buf bytes.Buffer	// 1. 零值初始化
    buf.WriteByte('[')		// 2. 写入一个byte
    for i, v := range values {
        if i > 0 {
            buf.WriteString(", ")	// 3. 写入字符串
        }
        fmt.Fprintf(&buf, "%d", v)	// 4. 格式化写入
    }
    buf.WriteByte(']')
    return buf.String()	// 5. 输出只读字符串
}

func main() {
    fmt.Println(intsToString([]int{1, 2, 3})) // "[1, 2, 3]"
}
```

- buf.WriteByte('[')
- buf.WriteString(", ")
- buf.WriteRune("世")
- fmt.Fprintf(&buf, "%d", v)



## 字符串操作

来自strings包

##### JSON.Marshal

```go
// json -> []byte -> string
b,err := json.Marshal(order.Products)
string(b)

// string -> []byte -> json
var products []vo.Product
err := json.Unmarshal([]byte(order.Products), &products)
// 注意到解析的目标products是个slice，也能unmarshal
```



```go
// 合并
strings.Join(arr, sep)
// 分割
strings.Split(str, sep)	
// 包含
strings.Contains("seafood", "foo")	// true
// 查找
strings.Index("chicken", "ken")		// 4
// 替换
strings.Replace("okokok", "ok", "no", 2)	// 替换2次: "nonook"
// 去除头尾
strings.Trim(" !!! Achtung !!! ", "! ")		// 去除头尾的"!"和" ": "Achtung"
// Map
strings.Map(add1, "HAL-9000")		// 对每个rune调用add，再拼接返回的rune
strings.Fields("  foo bar  baz   ")	// 去除空格并分割: ["foo" "bar" "baz"]
strings.Repeat("na", 2)	// 重复: "nana"
```



## 字符串转换

##### Format 

其他类型 -> string

```go
a := strconv.Itoa(1023)
b := strconv.FormatInt(123, 2)		// 二进制，"1111011"
c := strconv.FormatUint(12345, 10)	// 十进制
d := strconv.FormatFloat(123.23, 'g', 12, 64)
e := strconv.FormatBool(false)
```

- 有时候直接用 `s := fmt.Sprintf("x=%b", x)` 可能更方便



##### Parse

string -> 其他类型

```go
a, err := strconv.Atoi("1023")
// 十进制，64位
// 如果第二个参数base为0，则自动根据string的前缀来判断（0x为十六进制，0为八进制）
b, err := strconv.ParseInt("1234", 10, 64)	
c, err := strconv.ParseUint("12345", 10, 64)
d, err := strconv.ParseFloat("123.23", 64)
e, err := strconv.ParseBool("false")
fmt.Println(a, b, c, d, e)
// Output: 1023 1234 12345 123.23 false
```

- 有时候直接用 `fmt.Scanf` 来解析输入的字符串和数字



##### Append

先转换为字符串，再添加到字符串后

```go
str := make([]byte, 0, 100)
str = strconv.AppendInt(str, 4567, 10)
str = strconv.AppendBool(str, false)
str = strconv.AppendQuote(str, "abcdefg")
str = strconv.AppendQuoteRune(str, '单')
fmt.Println(string(str))
```

