GET

```go
// 用code向微信请求openid
url := fmt.Sprintf("https://api.weixin.qq.com/sns/jscode2session?appid=%s&secret=%s&js_code=%s&grant_type=authorization_code", appid, secret, code)
res, err := http.Get(url)
if err != nil {
    response.FailServer(c, "code2session请求失败", err, nil)
    return ""
}

// 读取响应body
body, err := ioutil.ReadAll(res.Body)
defer res.Body.Close()
if err != nil {
    response.FailServer(c, "code2session获取失败", err, nil)
    return ""
}

// 解析json
var wxsession WXSession	//解析为自己定义的json格式
if err := json.Unmarshal(body, &wxsession); err != nil {
    response.FailServer(c, "code2session解析失败", err, nil)
    return ""
}
```



POST

```go
// 请求微信发送一次订阅消息
url := fmt.Sprintf("https://api.weixin.qq.com/cgi-bin/message/subscribe/send?access_token=%s", accessToken.AccessToken)
data := gin.H{
    "touser": order.User.Openid,
    "template_id": "Nlw54VKoh9qXeQFst3hAo_ofFeXDgAdhYa5OZAdwfds",
    "data": gin.H{
        "date3": gin.H{ "value": model.Time(order.CreatedAt)	},
        "amount2": gin.H{"value": strconv.FormatUint(uint64(order.FeeTotal/100), 10)},
        "thing8": gin.H{"value": "您的商品已发货，可在小程序中获取快递单号。"},
    },
}
b, _ := json.Marshal(data)
res, err := http.Post(url,"application/json", bytes.NewBuffer(b))
if err != nil {
    response.FailServer(c, "发送订阅消息失败", err, nil)
	return
}
defer res.Body.Close()
body, _ := ioutil.ReadAll(resp.Body)

response.Success(c, "发送订阅消息成功"+string(body), nil)
```





对于`r *http.Request`



# 表单Form

`r.Form`是一个map，里面包含了所有请求的参数：

- URL中query-string
- POST的数据
- PUT的数据

```go
r.ParseForm()		//必须先解析url，或POST的body
r.Form.Get("id")	//获取的id的值
r.Form["username"]	//获取username的值（这种方法返回slice）

for k, v := range r.Form {
    fmt.Println("key:", k)
    fmt.Println("val:", strings.Join(v, ""))
}
```



`r.Form`是url.Values类型，一些操作：

```go
// 写入
v := url.Values{}
v.Set("name", "Ava")
v.Add("friend", "Jess")
v.Add("friend", "Sarah")
v.Add("friend", "Zoe")
// 取值
// v.Encode() == "name=Ava&friend=Jess&friend=Sarah&friend=Zoe"
fmt.Println(v.Get("name"))
fmt.Println(v.Get("friend"))
fmt.Println(v["friend"])
```



## 验证表单输入

**必填字段**

```go
if len(r.Form["username"][0])==0{
    //为空的处理
}
```

对于单选框、复选框，如果没有选择，则在提交的form中不会有对应字段，如果用了上述方法会报错。应使用`r.Form.Get()`取值（对于不存在的字段，取到的是空值），但是该方法只能取单个值，如果是map，必须用上面的方法。

**数字**

先将str转换为int，再判断数字范围合法性。

```go
getint,err:=strconv.Atoi(r.Form.Get("age"))
if err!=nil{
    //数字转化出错了，那么可能就不是数字
}

//接下来就可以判断这个数字的大小范围了
if getint >100 {
    //太大了
}
```

正则表达式（性能可能略差）

```go
if m, _ := regexp.MatchString("^[0-9]+$", r.Form.Get("age")); !m {
    return false
}
```

**其他输入**

```go
// 中文
regexp.MatchString("^\\p{Han}+$", r.Form.Get("realname"))
// 英文
regexp.MatchString("^[a-zA-Z]+$", r.Form.Get("engname"))
// 电子邮件地址
regexp.MatchString(`^([\w\.\_]{2,10})@(\w{1,}).([a-z]{2,4})$`, r.Form.Get("email"))
// 手机号码
regexp.MatchString(`^(1[3|4|5|8][0-9]\d{4,8})$`, r.Form.Get("mobile"))
// 身份证（15位和18位都要验证）
regexp.MatchString(`^(\d{15})$`, r.Form.Get("usercard")
regexp.MatchString(`^(\d{17})([0-9]|X)$`, r.Form.Get("usercard"))
```

**下拉菜单、单选**

检查提交的值是否属于下拉菜单、选项中的值：

```go
slice:=[]string{"apple","pear","banane"}

for _, v := range slice {
    if v == r.Form.Get("fruit") {
        return true
    }
}
return false
```

复选框需要做一些更多的判断。

**日期**

利用time包，将用户输入的年月日转化为时间，然后逻辑判断。



## 防止跨站攻击XSS

主要是防止注入脚本在浏览器端运行，好像主要是因为可以伪造标签，因此要把`<`、`>`都转义掉。

`html/template`包：

```go
func HTMLEscape(w io.Writer, b []byte) //把b进行转义之后写到w
func HTMLEscapeString(s string) string //转义s之后返回结果字符串
```

用法：

```go
// 服务端读取用户提交的form时，进行转义
template.HTMLEscapeString(r.Form.Get("username"))
// 服务器将应答写入w时进行转义
template.HTMLEscape(w, []byte(r.Form.Get("username")))
// 其实也可以用Fprint系列函数，配合第一个函数，写入w
fmt.Fprintln(w, "username:", template.HTMLEscapeString(r.Form.Get("username")))
```



## 防止表单多次提交

表单中添加一个隐藏字段token，通过MD5(时间戳)来获取惟一值，存储到服务器端(session来控制)，以方便表单提交时比对判定。

每次刷新（GET）页面的时候，服务端都生成一个新的token值：

```go
crutime := time.Now().Unix()
h := md5.New()
io.WriteString(h, strconv.FormatInt(crutime, 10))
token := fmt.Sprintf("%x", h.Sum(nil))
```

服务端解析提交的r.form后，先检查token字段的合法性：

```go
r.ParseForm()
token := r.Form.Get("token")
if token != "" {
	//验证token的合法性
} else {
	//token为空值，报错
}
// 后续对表单的真正操作
```



## 上传文件

1. 前端设置的编码类型（enctype）：

   ```
   application/x-www-form-urlencoded   表示在发送前将表单编码为URI的query string（默认）
   multipart/form-data   不编码。在使用包含文件上传控件的表单时，必须使用该值。
   text/plain    空格转换为 "+" 加号，但不对特殊字符编码。
   ```

   要上传文件，编码类型选择`form-data`。

   

2. 服务端调用`r.ParseMultipartForm()`来解析请求，而不再是`r.ParseForm()`：

   ```go
   r.ParseMultipartForm(32 << 20)
   ```

   参数表示分配多大的内存，用来存储上传的文件，超出部分存储在系统的临时文件。

   

3. 使用`r.FormFile`获取文件句柄，然后对文件进行存储等处理。

   ```go
   // 获取文件句柄
   file, handler, err := r.FormFile("uploadfile")	//uploadfile是表单里的文件字段
   if err != nil {
   	fmt.Println(err)
   	return
   }
   defer file.Close()
   
   //handler包含了文件名等信息
   fmt.Fprintf(w, "%v", handler.Header)
   
   // 将file的数据存储到新文件f
   f, err := os.OpenFile("./test/"+handler.Filename, os.O_WRONLY|os.O_CREATE, 0666)
   if err != nil {
   	fmt.Println(err)
   	return
   }
   defer f.Close()
   io.Copy(f, file)
   ```

   







