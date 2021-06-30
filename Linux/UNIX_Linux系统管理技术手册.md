$ user

\# root

[] 可选

... 可重复

{} 用|隔开，表示其中一个







```
ssh root@47.97.90.53
```



# 基础

### root权限

```sh
# ubuntu设置root密码
sudo passwd root
# 账户密码都存在/etc/shadow下

# 切换用户身份，默认进入root，exit退出
su

# 以root用户执行命令
sudo <CMD>
# 可用sudo visudo配置账户的访问控制权限
# 配置格式：用户 主机 = (以...用户执行) 命令
# 配置例子：见 man sudoers
```



##### 访问控制权限

1. 每个文件都有UID/GID，表示文件的属于谁，还定义了它们的访问权限（rwx）
2. 每个进程执行时，都有 real UID 和 effective UID：
   - **real UID**：创建进程的用户，也就是父进程的PID，通常只允许创建者和root对进程进行操作。
   - **effective UID**：表示以哪个用户UID的权限访问资源和文件。通常EUID与UID相同，除非设置了setuid位。（EUID可以被重置，从而修改进程的访问权限）
3. 如果可执行文件设置了setuid、setgid位，则执行该文件时，会将进程的effective UID改为该文件的UID。



### dpkg

底层的软件包管理工具（安装、卸载、查询）

```sh
sudo dkpg --install ./xxx.deb	# 安装deb软件包
sudo dkpg --remove
dpkg -l | grep <pkgname>	# 查看某个软件是否已安装
dpkg -l <pkgname>
```



### 换源

```sh
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak # 备份
```

- 科大换源说明：https://mirrors.ustc.edu.cn/help/ubuntu.html
- sources.list 里最好用 https



### apt

上层的软件包管理工具（下载、分析依赖、更新）

```sh
sudo apt update
sudo apt instal <pkgname>
sudo apt upgrade [-y]	# 更新所有软件包到最新版[-y 自动回复yes]
# apt update & apt upgrade -y	#自动更新脚本
```

- 在 `/etc/spt/sources.list` 配置好软件仓库源后，使用 `apt update` 应用配置。





### man

简要说明命令

```
whatis <CMD>
whatis -w "loca*"		# 正则匹配
```

查找手册

```
man <title>
man [section] <title>	# 从指定的节号中查找（1用户命令, 8系统管理, 2系统调用）
man -k <keyword>		# 列出“概要”中包含keyword的命令
```



# 进程管理

### kill

向进程发送信号

```sh
kill -l				# 输出信号列表
kill [-signal] pid	# 向进程发送指定信号，默认为TERM
```



### ps

监视进程

```sh
ps aux	# 看CPU、MEN, all, user-oriented, no-must-have-tty
ps alx	# 看PPID、NI, long-format

ps aux | grep sshd	# 过滤输出
ps up "1 2"			# 查看指定的PID进程（PID列表用引号括起来）
pidof sh			# 获取sh进程的PID

# - [CMD]中括号表示内核线程
# - w、ww可以避免输出截断
```

`top` ：动态监视进程。

- 按1可以查看各个CPU核的使用情况
- 按F可以选择要显示的信息，如DATA列（数据段+堆栈段），用空格进行选择。

`/proc` ：该目录中包含更详细的进程信息（cwd, environ, df, maps, ns, root）。



### renice

友善度：进程竞争CPU时，调度的优先级。数值越低，优先级越高（越不友善）。

```sh
renice +19 PID	# 修改进程的友善值为19（最大，最慢）
```

- 友善值只能增加，除非用sudo
- 0是基准值，范围是[-20, 19]，负数都会运行的很快
- 只影响CPU的调度优先级，不影响IO优先级，高友善度的进程仍然可能霸占IO。



### strace

追踪信号和系统调用

```sh
sudo strace -p PID	# 附着到进程上
-e trace=file	# 只显示文件相关操作
```

注意那些返回错误提示的系统调用



### df

查看文件系统的磁盘使用情况

```sh
df -h	# human-readable
```



### cron

创建定时作业

```sh
crontab -e	# 编辑crontab
crontab -l	# 查看crontab
crontab -r	# 删除

# 格式: minute  hour  day-of-month  month  day-of-week  CMD
# 例子: * * * * * echo $(/bin/date) - $(/usr/bin/uptime) >> ~/uptime.log
# 实际上是将当前时间对表达式进行匹配
# - *: 任意
# - 0-6: 范围
# - 1-10/2 */10: 步进
# - 1,3,5,7-10: 列表
# - dom和dow是或的匹配，一个满足即可
```

- 时间精确到分钟
- 命令由sh执行
- 命令建议使用完整路径。命令中%表示换行，使用\%转义
- 可以在配置文件的顶部设置环境变量
- 如果是执行脚本，确保可执行权限 `chmod +x`；
- 也可以在CMD部分用sh来调：`/usr/bin/sh -c "命令、脚本"`
- 用户实际的配置文件放在 `/var/spool/cron` 目录下，以用户名命名。





# 文件系统

- “文件树”中的分支称为“文件系统”。
- 文件树的组织：见 `man hier`



- 创建：mkdir
- 删除：rm (删除目录：rm -rf )
- 移动：mv
- 复制：cp src dst (复制目录：cp -r )



### find

搜寻文件或目录

```
find ./ -name "core*"
```

- `locate filename` 可以根据数据库索引进行快速查找（更新数据库：`updatedb`）



### mount

```sh
mount	# 查看已挂载的文件系统
sudo mount /dev/sda5 /users	# 挂载文件系统到挂载点（重复挂载到同一目录会覆盖）
sudo umount /users			# 卸载文件系统
```

- 使用 `fuser -cr mountpoint` 可以查看正在使用该文件系统的所有进程PID。
- 文件 `/etc/fstab` 记录了系统正常挂载的文件系统



### file

```sh
file /usr	# 查看文件类型
```

- 也可以在 `ll` 输出中的第一个字母判断文件类型
- 7种类型：普通文件、目录、符号链接、字符设备文件、块设备文件、FIFO管道、域套接字
- `rm` ：文件都可以通过rm来删除，支持模式匹配（如 `rm -i a*` ），建议加上 `-i` 进行二次确认；删除目录需要 `rmdir` （空目录）或 `rm -r` （递归删除其中内容）。



### ln

```sh
ln oldfile newfile	# 创建硬链接
ln -s path linkfile	# 创建软链接（注意path只是字符串字面量，与当前路径无关）
```

硬链接 + 引用计数：文件本身没有名字，“目录”文件记录了要引用哪些文件，并指定它们的名字。同一个文件可以被多个目录引用，且拥有不同的名字。



### chmod

修改文件权限

```sh
chmod 711 myprog
chmod 6711 myprog	# 设置setuid和setgid位（不设置黏着位）
chmod u=rwx,g+x,o-w myscript	# 助记符的方式修改权限（属主可用ugoa表示）
```

注意：目录的执行位 x 表示能否作为路径名的一部分出现在命令中，wx 表示有权限创建删除文件。

- 可以通过 `chown` 和 `chrgp` 修改文件的uid和gid
- 可以通过 `lsattr` 和 `chattr` 查看/修改文件的属性



# Shell

##### 命令行快捷键

光标到开头：ctrl + A

光标到结尾：ctrl + E

搜索历史命令：ctrl + R（输入搜索内容，多次按 ctrl + R 进行反向搜索）



##### 重定向

文件描述符：STDIN（&0），STDOUT（&1），STDERR（&2）

- `<` 会重定向 STDIN
- `>` 和 `>>` 会重定向 STDOUT
- `2>` 会重定向 STDERR
- `&>` 同时重定向 STDOUT 和 STDERR 
- `|` 将前一个命令的 STDOUT 连接到后一个命令的 STDIN

```sh
find / -name core 2> /dev/null	# 不输出错误信息
exec 0<$1	# 将第一个参数指定的文件作为标准输入
```

- `[CMD1] && [CMD2]` 只有前一个命令执行成功（退出码为0），才执行后一个
- `[CMD1] || [CMD2]` 只有前一个命令执行失败，才执行后一个

```sh
mkdir foo && cd foo
cd foo || echo "No such directory"
ls /proc && echo  suss! || echo failed.
```



一条命令可以用 `\` 分成好几行；

多条命令可以用 `;` 写成同一行。



##### 变量

变量通过赋值创建，通过 `$` 引用变量

```sh
etcdir='/etc'
echo $etcdir
echo "This is ${rev}th version"		# 也可以用${var}来引用变量，常用于双引号的字符串
echo "There are `wc -l < /etc/passwd` lines in the passwd file."	# 反引号``中内容会被当成命令执行

# 变量其实都是字符串
# 使用$((...))进行强制数值计算
cnt=$((cnt + 1))
c=$((a + b))
```

- **赋值的等号两边不能有空格！！否则会被当成命令**
- 所有sh变量都是字符串，不会区分1和“1”！
- 变量名区分大小写，本地变量通常用小写+下划线；环境、全局变量用大写。
- 只有在双引号 `""` 中才能扩展匹配处理（*和?）以及变量扩展（${var}）



##### 环境变量

环境变量会被传递给执行的程序。

```sh
printenv	# 查看环境变量
export EDITOR=nano	# 将普通变量提升为环境变量（暂时的）
```



##### cut

把行划分成字段（默认分隔符为Tab）

```sh
cut -d<分隔符> -f<指定输出的列> filename
cut -d" " -f1,3,5-9 ./myfile	# 输出第1,3,5~9列
```



##### sort

对输入行按字典序排序

```sh
sort filepath
sort -t: -k3,3 -n /etc/group	# 对行根据冒号:分隔，以第3~3个字段作为排序键，按数值序排序
-r 逆序
-f 忽略大小写
-b 忽略前导空白
```



##### uniq

去重

```sh
cut -d: -f7 /etc/passwd | sort | uniq -c	# 去重并计数，必须先sort
```

- -d 只打印重复的行（count > 1）
- -u 只打印不重复的行（count = 1）



##### wc

统计行数（-l）、单词数（-w）、字符数（-c）

```sh
wc /etc/passwd
wc -l /etc/passwd	# 只统计行数
```



##### tee

将 标准输入 发送到 标准输出 以及指定的文件中

```sh
# 将耗时的命令输出到终端tty便于查看
find / -name core 2> /dev/null | tee /dev/tty | wc -l

# 也可以把tee放在最后，既能将输出保存到文件，又能在终端即时查看
```



##### tail

```sh
# 持续监视日志文件的最后10行（这里还使用grep进行了过滤）
tail -f /var/log/messages | grep --line-buffered <pattern>
```



##### grep

```sh
xxx | grep -v <pattern>			# 排除<pattern>
grep -l <pattern> /var/log/*	# 只打印文件名，而不打印具体匹配到的内容
```





### sh脚本

第一行指定解释器

```sh
#!/bin/sh
#!/usr/bin/env python	(在环境变量中搜索解释器，存在安全隐患，特别是sudo执行的时候)
```



脚本需要设置执行位：

```sh
chmod +x myscript
```



执行

```sh
./myscript
sh myscript
source myscript		# 等价于". myscript"
```



脚本无视缩进、空格等空白符，只是通过换行表示一条命令。



##### 输入

可以通过read命令获取输入

```sh
echo -n "Enter your name: "		#这里用-n取消了换行
read user_name
echo "Hello, ${user_name}!"
```



##### 参数

```
$0		脚本名
$1-9	参数1~9
$#		参数个数
$*		参数列表
```

文件名中又空格时，用引号包围文件名，或者用 `\` 对空格转义



##### if

```sh
if [ $# -ne 2 ]; then
    echo "Usage $0 parm1 parm2" 1>&2	#重定向了STDOUT
    exit 1
fi
```

- 使用 `[]` 做比较，**必须要留出空格**
- 数值比大小：-eq -ne -lt -gt -le -ge
- 文件存在性：-e（存在） -d（目录） -f（文件） -r（读权限）



##### case

```sh
case $level in
	0) text="Error";;
	1) text="Warning";;
	2) text="Info";;
	3) text="Debug";;
	*) text="Other"		# 其实是字符串的通配，说明支持字符串作为case号
esac
echo "${text}: ${msg}"
```

- 每个条件最后要有 `;;`



##### for

```sh
# 备份文件
suffix=BACKUP--`date +%Y-%m-%d-%H%M`
for file in *.sh; do
	newname="${file}.${suffix}"
	cp -p $file $newname
done	
```

- 如果 for 后面不写 in，则默认遍历命令行参数列表



##### while

```sh
exec 0<$1	#将参数1的文件名重定向到STDIN
cnt=1
while read line; do
	echo "${cnt}: ${line}"
	cnt=$((cnt + 1))	# 强制数值计算
done
```

