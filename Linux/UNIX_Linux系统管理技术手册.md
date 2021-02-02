$ user

\# root

[] 可选

... 可重复

{} 用|隔开，表示其中一个



```
ssh root@47.97.90.53
```



# 安装后基础

##### 换源

```bash
sudo cp /etc/apt/sources.list /etc/apt/sources.list.bak # 备份
```

https://mirrors.ustc.edu.cn/help/ubuntu.html

（如果用gui换源了，记得把 /etc/apt/sources.list 里的 http 改为 https）

```bash
sudo apt-get update  # 更新索引
sudo apt-get upgrade # 更新软件
```



##### root账户管理

```bash
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
   - real UID：创建进程的用户，也就是父进程的PID，通常只允许创建者和root对进程进行操作
   - effective UID：表示以哪个用户UID的权限访问资源和文件。通常EUID与UID相同，除非设置了setuid位。（EUID可以被重置，从而修改进程的访问
   - 权限）
3. 如果可执行文件设置了setuid、setgid位，则执行该文件时，会将进程的effective UID改为该文件的UID。



### man

```
man <title>
man [section] <title>	# 从指定的节号中查找（1用户命令, 8系统管理, 2系统调用）
man -k <keyword>		# 列出“概要”中包含keyword的命令
```





# 进程管理

### kill

向进程发送信号

```bash
kill -l				# 输出信号列表
kill [-signal] pid	# 向进程发送指定信号，默认为TERM
```



### ps

监视进程

```bash
ps aux	# 看CPU、MEN, all, user-oriented, no-must-have-tty
ps alx	# 看PPID、NI, long-format

ps aux | grep sshd	# 过滤输出
pidof bash			# 获取PID

# - [CMD]中括号表示内核线程
# - w、ww可以避免输出截断
```

`top` ：动态监视进程。

- 按1可以查看各个CPU核的使用情况
- 按F可以选择要显示的信息，如DATA列（数据段+堆栈段），用空格进行选择。

`/proc` ：该目录中包含更详细的进程信息（cwd, environ, df, maps, ns, root）。



### renice

友善度：进程竞争CPU时，调度的优先级。数值越低，优先级越高（越不友善）。

```bash
renice +19 PID	# 修改进程的友善值为19（最大，最慢）
```

- 友善值只能增加，除非用sudo
- 0是基准值，范围是[-20, 19]，负数都会运行的很快
- 只影响CPU的调度优先级，不影响IO优先级，高友善度的进程仍然可能霸占IO。



### strace

追踪信号和系统调用

```bash
sudo strace -p PID	# 附着到进程上
-e trace=file	# 只显示文件相关操作
```

注意那些返回错误提示的系统调用



### df

查看文件系统的磁盘使用情况

```bash
df -h	# human-readable
```



### cron

创建定时作业

```bash
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