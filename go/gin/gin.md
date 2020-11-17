### 安装配置Go

1. 官方下载

2. 安装后，bash中命令 go version 查看版本

3. go env 查看环境变量

   ```
   go env -w GO111MODULE=on #开启module
   go env -w GOPROXY=https://goproxy.cn,direct #开启代理
   ```

4. 安装Goland：https://www.jianshu.com/p/ab855dfc5312

   

### 创建项目

- 编译单个文件

  ```
  go run main.go
  ```

  编译全部文件

  ```
  go build
  ```

  （他会在目录下生成一个可执行文件，在bash中运行）

  goland中运行：编辑配置时，设置 Run kind 为 Directory

- 创建mod（说明这个项目属于这个module）

  ```
  go mod init github.com/innor6/ginessential
  ```

- 启用Go Module（用于自动引入包）

  设置——Go——Go Module——勾选Enable Go Modules integration

- 安装各种包

  ```bash
  go get -u github.com/gin-gonic/gin	#gin
  go get -u github.com/jinzhu/gorm	#gorm
  go get -u github.com/go-sql-driver/mysql	#mysql
  #在import中加入_ "github.com/go-sql-driver/mysql"
  go get -u golang.org/x/crypto/bcrypt	#bcrypt
  go get github.com/gin-contrib/sessions #gin-session
  go get github.com/spf13/viper	#viper-配置文件
  go get github.com/satori/go.uuid	#uuid
  
  go get github.com/iGoogle-ink/gopay #gopay
  ```

- **GIT**

  先创建 .gitignore 文件，填入

  ```
  .idea
  ```

  创建git仓库，并提交一个版本

  ```bash
  git init
  git add --all
  git commit -v #出现vim界面，i,输入comment，:wq
  git status
  git log
  ```

- 数据库设置允许时间类型的为零

  ```sql
  -- 找到sql_mode
  show variables like 'sql_mode' ; 
  
  -- 去掉其中的：NO_ZERO_IN_DATE,NO_ZERO_DATE
  set global sql_mode = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION';
  ```

  




目录结构

- 主目录：main、config.yml（配置文件）、routes.go（注册路由）

- config：配置文件信息

- middleware：创建session、token鉴权

- response：封装返回响应的统一格式

- controller：router调用的api，操作model

- model：数据库模型

- serializer：将model转换成返回给前端的json

- util：一些工具函数

  



请求处理过程：

- 获取参数
- 数据验证
- 处理
- 返回结构



常用

- 状态码：

  - 400：http.StatusBadRequest，请求数据有语法错误
  - 401：http.StatusUnauthorized，权限不足
  - 422：http.StatusUnprocessableEntity，请求数据不符合格式规范
  - 500：http.StatusInternalServerError，服务器内部错误
  
- 上下文中取数据：interface -> object

  ```go
  user,_ := c.Get("user")	//返回指针 *interface
  user.(*model.User).ID
  ```
  
- [gin-session](https://blog.csdn.net/qq_16763983/article/details/105049118)

- 路由

  ```go
  //参数路由
  //:name表示该字段非空，*action则允许该字段为空值
  router.GET("/user/:name/*action", func(c *gin.Context))
  
  //获取参数
  name := c.Param("name")
  action := c.Param("action")
  ```

- 返回JSON

  ```go
  //gin.H的类型是map[string]interface{}）
  c.JSON(http.StatusOK, gin.H{
      "code": 200,
      "data": gin.H{"token":token},
      "msg": "注册成功",
  })
  ```

- 解析请求：

  ```go
  // 方法〇：gin.c.bind自动抓取
  var requestUser = model.User{}	//定义在model中的结构体User
  c.Bind(&requestUser)
  
  // 方法一：map
  var requestMap = make(map[string]string)
  json.NewDecoder(c.Request.Body).Decode(&requestMap)
  
  // 方法二：结构体
  var requestUser = model.User{}
  json.NewDecoder(c.Request.Body).Decode(&requestUser)
  ```
  
- 授权校验middleware将user信息写入上下文，可以在后续被提取

- 数据库的外码：

  - model里用目标关系+id命名
  
  - 查数据库时，先 Preload
  
    ```go
    // 有外码，先 Preload("Category")
    if p.DB.Preload("Category").Where("id = ?", postId).First(&post).RecordNotFound()
    ```

- bcrypt加密

  - 原理：密码+随机盐，重复 hash 10次，输出：bcrypt+加密次数+盐+哈希结果
  - 验证：从哈希结果取出盐，加上明文密码，重新计算，检查结果是否相同。
  - 破解：属于单向加密，破解需要构建彩虹表。但是由于hash次数过多，计算一个密码的哈希结果的代价就很大，构建彩虹表的时间代价大；而且加随机盐，密码长度增加，构建彩虹表的空间代价、时间代价大。
  - [彩虹表](https://www.jianshu.com/p/732d9d960411)，一种hash碰撞的破解方法，对短密码计算哈希值，覆盖整个密码空间；
    - 相比普通的hash碰撞，彩虹表不是保存所有的哈希结果，而是利用哈希链，只保留哈希链的头尾，降低空间代价为1/k；（对明文密码最多hash、reduce k 次，若出现在哈希链头尾，则明文在该链中）
    - 如果reduce函数不能把hash结果均匀的散列，则两条哈希链很可能会有重叠，因此在一条哈希链中使用多个不同reduce函数，以避免哈希链重叠，提高空间利用率；但是破解明文的计算时间代价变为k^2。

  加密：

  ```go
  hashPassword, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.DefaultCost)	//参数2为加密次数
  if err != nil {
      response.Response(c, http.StatusInternalServerError, 500, "加密错误", nil)
      return
  }
  mypassword := string(hashPassword) //转换为string
  ```

  解密：

  ```go
  if err := bcrypt.CompareHashAndPassword([]byte(user.Password),[]byte(password)); err != nil {
      response.Fail(c, "密码错误", nil)
      return
  }
  ```

- UUID（时间戳+版本号+时钟序列号+结点ID）

  算法：

  1. 获取系统级的锁
  2. 从系统级的持久化文件中读UUID生成器的状态：上一次生成的UUID的timestamp, clock sequence, and node ID
  3. 获取当前时间戳、结点ID。如果时间回退，则时钟序列号+1；如果结点改变，则生成随机时钟序列号。
  4. 保存当前状态
  5. 释放锁
  6. 生成UUID

  性能优化：

  1. 每次读状态效率低：实际上只要在启动时从持久化文件中读取一次状态就够了，之后可以一直放在内存修改，直到持久化文件更新了才更新。
  2. 系统时钟精度不够：可以使用自增计数器填充时间戳的最低位来代替，如果短时间请求生成UUID过多，则要么推迟时间，要么返回错误。
  3. 每次写回状态效率低：不用每次生成完都写回，可以写回一个更晚的时间戳，当真实时间超过该值才触发下一次写回。或者是当时钟序列号、结点ID改变也触发写回。
  4. 在进程间共享状态开销大：可以让系统级的生成器每次一次性分配一个块的时间戳；而每个进程自己的生成器则从分配给自己的块中取时间戳，直到用尽。



### 获取参数

create（POST）、update（PUT）用json

show（GET）、delete（DELETE）用query-string



获取路由中参数：

```
router.GET("/users/:id", controller.user)

id := c.Param("id")
```

获取**GET**参数：query-string

```go
id := c.Query("id")
page := c.DefaultQuery("page", "0")	//如果参数不存在则赋默认值
if id == "" || page == "" {
    response.Fail(c, "参数错误", nil, nil)
    return
}
```

获取**POST**参数：Content-Type: application/x-www-form-urlencoded

```go
message := c.PostForm("message")
nick := c.DefaultPostForm("nick", "anonymous")	//设置默认值
```

绑定到结构体：

```go
type Login struct {
    User     string `form:"user" json:"user" binding:"required"`
    Password string `form:"password" json:"password" binding:"required"`
}


if err := c.ShouldBind(&Login); err != nil {
    c.JSON(http.StatusBadRequest, gin.H{"error": err.Error()})
    return
}
```







[https://www.jianshu.com/p/732d9d960411]: 





### 快递

您在丰桥自助API的

顾客编码为：SLLLFr，

校验码为：IfYSF79fm70EcpBXFAUTLHF49yvh4ym2