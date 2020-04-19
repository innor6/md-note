##### 环境变量

`echo $PATH` 显示在shell中输入command时会查找的所有路径

`which echo` 输出echo命令对应调用的文件路径

`man ls` 查看命令ls的使用手册



#### 路径

- `pwd` ：查看当前目录
- `cd` ：切换目录
- 绝对路径：以斜线（/）开头
- 相对路径：不以斜线（/）开头
- `.` ：当前目录
- `..` ：上一级目录
- `-`：用 cd 命令切换目录**前**的目录
- `~` 表示**用户主目录**的绝对路径名（/home/innor）

#### 文件

- `ls *.sh` ：显示所有`.sh`格式的文件（-l查看详细信息）
- `mv a b` ：重命名
- `cp a ../b` ：复制
- `rm ../b` ：删除（-r递归删除目录）
- `mkdir “My Photos”` ：创建目录
- `xdg-open a` ：使用默认程序打开文件a

目录文件的rwx：查看目录中包含的文件、添加删除目录中文件、查找目录中文件



##### 重定向io

`>`, `<`, `>>`, `<<` 输出输入到流

```shell
echo hello > hello.txt
cat hello.txt
cat < hello.txt > hello2.txt #从一个文件输入到另一个文件
cat < hello.txt >> hello2.txt #用>>表示append
```

`|` 将左边的输出作为右边命令的输入

```shell
ping baidu.com | tee ping.log #将左边输出输入到tee的参数对象中，tee同时会在屏幕上打印出来
```

 

##### 权限

`sudo su` 令终端进入root模式

`exit` 退出root模式

##### 终端快捷键

`ctrl + L` 清屏

`ESC .` 输入一个`$_`