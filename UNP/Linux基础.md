来自——[看完这篇Linux基本的操作就会了](https://zhuanlan.zhihu.com/p/36801617)

## 系统级快捷键

切换工作区：`ctrl + alt + 左/右方向键`

复制粘贴：`ctrl + shift + c/v`

EOF：`ctrl + D`

中断：`ctrl + C/?`（向进程发送 `SIGINT` 信号）

清屏：`ctrl + L`

## 目录结构

- **bin 存放二进制可执行文件(ls,cat,mkdir等)**
- boot 存放用于系统引导时使用的各种文件
- dev 用于存放设备文件
- **etc 存放系统配置文件**
- home 存放所有用户文件的根目录
- lib 存放跟文件系统中的程序运行所需要的共享库及内核模块
- mnt 系统管理员安装临时文件系统的安装点
- **opt 额外安装的可选应用程序包所放置的位置**
- proc 虚拟文件系统，存放当前内存的映射
- **root 超级用户目录**
- sbin 存放二进制可执行文件，只有root才能访问
- tmp 用于存放各种临时文件
- usr 用于存放系统应用程序，比较重要的目录/usr/local 本地管理员软件安装目录
- var 用于存放运行时需要改变数据的文件



## 基础命令

基本命令格式：

`cmd [options] [arguments]`（区分大小写）

通配符：

- *：匹配任何字符和任何数目的字符
- ?：匹配单一数目的任何字符
- [ ]：匹配[ ]之内的任意一个字符
- [! ]：匹配除了[! ]之外的任意一个字符，!表示非的意思

### 目录说明

- pwd：查看当前目录
- cd：切换目录
- 绝对路径：以斜线（/）开头
- 相对路径：不以斜线（/）开头
- `.`：当前目录
- `..` ：上一级目录
- `-`：用 cd 命令切换目录**前**的目录
- `~` 表示**用户主目录**的绝对路径名（/home/innor）

### 常用命令

##### 目录操作

- `ls`：显示文件或目录信息（显示详细信息`-l`，显示隐藏文件`-a`）
- `mkdir`：当前目录下创建一个空目录
- `rmdir`：删除一个空目录
- `touch`：生成一个空文件或更改文件的时间
- `cp`：复制文件或目录（复制目录需要`-r`递归复制，`-T`修改复制后的文件名）
- `mv`：移动文件或目录、文件或目录改名
- `rm`：删除文件或目录（`-r`递归删除目录）
- `ln`：建立文件硬链接（`-s`软链接）
- `find`：查找文件（`-inum`查找inode号）
- `file/stat`：查看文件类型/文件详情inode

##### 查看文本

- `cat`：查看文本文件内容
- `more`：可以分页看
- `less`：不仅可以分页，还可以搜索，回翻等操作
  - 退出：`q`
  - 翻页：
    - 前进/后退一行：`e/y`
    - 前进半窗口：`d`
    - 前进一窗口：f
    - 回退一窗口：w
    - 跳到开头/结尾：`g/G`
  - 查找：
    - 查找模式：`/pattern`
    - 前向查找：`n`
    - 后向查找：`N`
    - 只显示匹配的行：`&pattern`
    - 取消匹配高亮：`ESC-u`
- `tail`：查看文件的尾部的10行（指定行数：`-n NUM`，显示文件名：`-v`）
- `head`：查看文件的头部10行（指定行数：`-n NUM`）
- `echo`：配合重定向（覆盖模式：`>`，追加模式：`>>`）把内容重定向到指定的文件中 ，有则打开，无则创建，如`echo "nihao" >> newfile`
- `管道命令 |` ：将前面的结果给后面的命令，例如：`ls -la | wc`，将ls的结果加油wc命令来统计字数；又如`ls -l | less`可以在ls结果过多时分屏浏览。



##### 文件压缩

- 压缩：`tar -czvf filename.tar.gz a ./mydir`（压缩：文件a、目录mydir）

- 解压缩：`tar -xzvf filname.tar.gz -C ./somedir`（解压到路径：./somedir）

参数说明：

​	-z：调用gzip进一步处理归档文件
​	-c：压缩
​	-x：解压缩
​	-f：必选，后跟指定归档文件名，最后一个参数

​	-v：生成详细输出
​	-r：将文件追加到tar中
​	-u：更新tar中的某个文件，若不存在则追加
​	-C：指定解压到的目录

[linux中tar命令用法](https://www.cnblogs.com/newcaoguo/p/5896975.html)

### 别名

`alias`：查看已经定义的别名。

`alias ll='ls -l'`：定义别名。

别名的持久化：

1. 用`vi`打开`~/.bashrc`（针对所有用户：`/etc/.bashrc`）
2. 添加别名定义：`alias ll='ls -l'`
3. 保存回到shell后，执行`source ~/.bashrc`

### Shell变量

分类：内部变量、环境变量、用户变量

局部变量：其命令行所在的Shell或Shell脚本文件中；

全局变量：作用本Shell进程及其所有子进程。

- 定义变量：`NAME=value`
- 使用变量：`$NAME`
- 查看变量：`echo $NAME`
- 删除变量：`unset NAME`

其他的命令：

- 环境变量：`env`
- 所有变量、函数：`set`
- 全局变量：`export`
- 定义全局变量：`export NAME=value`
- 提升为全局变量：`export NAME`
- 降低为局部变量：`export -n NAME`

## 正则表达式

grep命令：

`grep -E --color 'PATTERN' filename`

`grep -v '^#' filename`：反向查找，过滤掉开头是`#`的行。

（-E使用扩展的regexp，--color高亮匹配的字串，注意color前面是两横！，-n显示行号）

[30分钟掌握正则表达式](https://www.bilibili.com/video/av66949177)

```
.       - Any Character Except New Line
\d      - Digit (0-9)
\D      - Not a Digit (0-9)
\w      - Word Character (a-z, A-Z, 0-9, _)
\W      - Not a Word Character
\s      - Whitespace (space, tab, newline)
\S      - Not Whitespace

\a      - Alphabet (a-z, A-Z)
\l      - Lower Case (a-z)
\u      - Upper Case (A-Z)
\x      - Hex (0-9, A-F, a-f)


\b      - Word Boundary (beginning, end, space)
\B      - Not a Word Boundary
^       - Beginning of a String
$       - End of a String

[]      - Matches Characters in brackets
[^ ]    - Matches Characters NOT in brackets
|       - Either Or
( )     - Group

Quantifiers:(数目)
*       - 0 or More
+       - 1 or More
?       - 0 or One
{3}     - Exact Number
{3,4}   - Range of Numbers (Minimum, Maximum)


#### Sample Regexs ####

[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+
```

注意：

- 元字符需要用`\`转义：`.[{()}]\^$|?*+`
- `[a-zA-Z0-9_.+-]`：表示匹配括号中的其中一个字符，这里的`a-z`表示范围。
- `[^a-z]`：表示匹配的字符不是括号中的任意一个字符。

##### 示例一

匹配下面的人名

```
Mr. Schafer
Mr Smith
Ms Davis
Mrs. Robinson
Mr. T
```

`M(r|s|rs)\.?\s[A-Z]\w*`：

- `M(r|s|rs)`：以`Mr`、`Ms`、`Mrs`开头
- `\.?`：一个或0个`\.`
- `\s`：空白符
- `[A-Z]`：一个大写字母
- `\w*`：后跟0~任意个英文字母

##### 示例二

匹配下面的邮箱

```
CoreyMSchafer@gmail.com
corey.schafer@university.edu
corey-321-schafer@my-work.net
```

`[a-zA-Z0-9.-]+@[a-zA-Z-]+\.(com|edu|net)'`：

- `[a-zA-Z0-9.-]+`：字母、数字、`.`、`-`
- `+`：表示前面这些字符在一个或以上
- `@`
- `[a-zA-Z-]+`：同上
- `\.`
- `(com|edu|net)`：以`com`、`edu`或`net`结尾。

##### 示例三

提取下面URL的域名（打组）

```
https://www.google.com
http://coreyms.com
https://youtube.com
https://www.nasa.gov
```

`https?://(www\.)?(\w+)(\.\w+)`：

- `https?`：http或https
- `://`
- `(www\.)?`：可能有`www.`开头
- `(\w+)`：域名由多个字母、数组、下划线构成
- `(\.\w+)`：以`.com`、`.net`、`.gov`等结尾

**打组：**

上面的表达式将域名分成了三个group（用了三个括号），

每个group都有自己的序号，从1开始，

提取第二组和第三组，即`$2$3`，可得：

```
google.com
coreyms.com
youtube.com
nasa.gov
```

## VI编辑器

打开文件：`vi filename`

选项：

`+`：将光标置于末尾

`+n`：光标置于第n行

`-r`：恢复崩溃的文件

进入插入模式：`i`、`a`、`o`（按`ESC`返回）

进入命令行模式：`:`、`/`、`?`、`!`。

##### 命令行模式

- `:w filename`：以指定文件名保存
- `:wq`：存盘退出
- `:q!`：不存盘退出

##### 普通模式

- **`ZZ`：存盘退出**
- `ZQ`：不存盘退出
- **`u`：撤销**
- `x`：后向删除del（前向删除用大写`X`）
- **`dd`：删除一行**
- **`dw`：删除到单词末尾**
- **`yy`：复制一行（只能配合p使用）**
- **`yw`：复制到单词末尾**
- **`p`：粘贴**
- `r`：替换（`R`：进入替换模式）

##### 匹配

- `/`：进入匹配模式（`?`好像也可以）
- `/\v`：very magic，任何正则表达式的元字符都不需要加反斜杠
- `n`：继续查找下一个

##### 移动光标

- `h`、`j`、`k`、`l`：上下左右
- `ctrl+d/u`：向前/后跳半页
- `ctrl+f/b`：向前/后跳一页
- `w`：跳到下一个单词
- `b`：跳到上一个单词
- `^`：跳到行首
- `$`：跳到行尾
- `0`：跳到开头
- `G`：跳到末尾

##### 设置Vi环境

- :set autoindent 缩进,常用于程序的编写
- :set noautoindent 取消缩进
- :set number 在编辑文件时显示行号
- :set nonumber 不显示行号
- :set tabstop=value 设置显示制表符的空格字符个数
- :set 显示设置的所有选项
- :set all 显示所有可以设置的选项

##### 永久设置

编辑VIM的配置文件：

```
sudo vim /etc/vim/vimrc
```

末尾加上（语法高亮显示，自动缩进，显示行号，缩进4格）：

```
syntax on
set autoindent
set cindent
set nu
set tabstop=4
```

