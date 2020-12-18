[TOC]



### 下载安装

安装后打开git bash

配置用户名和Email地址：

```bash
$ git config --global user.name "innor"
$ git config --global user.email "innor@mail.ustc.edu.cn
```



### 创建版本库

打开bash

使用cd移动到目标目录

创建“learngit”文件夹作为仓库，以后的代码都放这里

```bash
$ mkdir learngit
$ cd learngit
$ pwd
$ git init

Initialized empty Git repository in C:/Users/64589/Documents/git/learngit/.git/
```



### 添加文件与提交

在“learngit”目录（子目录）下创建文件“readme.txt”

随后打开bash

将文件放到暂存区（stage）

```bash
$ git add readme.txt
$ git add ... ... other files
$ git add -A	#添加所有新增、修改、删除的文件
```

提交修改及说明到当前仓库分支（master）

```bash
$ git commit -m "wrote a readme file"
[master (root-commit) a154811] wrote a readme file
 1 file changed, 2 insertions(+)
 create mode 100644 readme.txt
```

查看未添加、提交的修改

```bash
$ git status
```

查看被修改的内容

```bash
$ git diff readme.txt #工作区和暂存区中文件内容的差异
$ git diff -cached readme.txt #暂存区和仓库的差异
$ git diff HEAD -- readme.txt #目标版本与工作区的差异
```



### 查看历史版本

查看版本日志

```bash
$ git log
```

回档

HEAD表示当前版本，后面加`^`表示上一版本，上上版本为`HEAD^^`，上100个版本为`HEAD~100`

```bash
$ git reset --hard HEAD^
```

回档后，想要跳到更后的版本，需要记住目标版本的commit id，如id为`a068f016aa142d5edbf880e04802a4dc2179f673`

```bash
$ git reset --hard a068
```

查看历史操作，以获取之前的commit id

```bash
$ git reflog
```



### 修改控制

撤销对工作区文档的修改/删除（回退到仓库中的版本）

```bash
$ git restore readme.txt
# git checkout -- readme.txt
```

撤销暂存区中添加的项目

```bash
$ git restore --staged readme.txt
# git reset HEAD readme.txt
```



### 远程仓库

**创建SSH Key**

```bash
$ ssh-keygen rsa -C "innor@mail.ustc.edu.cn"
```

Github-Setting-SSH Keys，将公钥“id_rsa.pub”的内容填入。

在Github右上角，+ new repository，创建完毕后

**关联远程仓库origin**

```bash
$ git remote add origin git@github.com:innorLMJ/learngit.git
```

##### 修改远程仓库地址

```bash
$ git remote set-url origin git@github.com:innor6/md-note.git
#也可以先删再加
git remote rm origin
git remote add origin [url]
```

**第一次推送**

推送本地分支master，关联远程分支master

```bash
$ git push -u origin master
```

**普通推送**

```bash
$ git push origin master
```

**克隆远程库到当前目录**

```bash
$ git clone git@github.com:innorLMJ/xxx.git
```







# Git scm

[git-scm](https://git-scm.com/book/zh/v2)

### 配置config

```bash
# 配置：用户名、邮箱
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com
```

查看配置

```bash
git config --list		# 列出所有配置，有同名的配置则选择最后一个
git config user.name	# 查看某个变量的值
git config --show-origin rerere.autoUpdate	# 查看某个变量来自哪个配置文件
```

说明：

- 配置文件有三个地方：

  （局部配置覆盖全局配置）

  - 系统级：`/etc/gitconfig`（git config --system）
  - 当前用户： `~/.gitconfig`（git config --global） 
  - 当前仓库（默认）：`.git/config`



### 忽略

创建 `.gitignore` 文件，写入：

```bash
# 其实是一种正则表达式匹配，若文件路径file_path被匹配了则忽略
# 默认会递归的应用到每个子目录中

# 匹配规则：
# * 	匹配零个或多个任意字符
# **	匹配零个或多个中间目录，比如 a/**/z 可以匹配 a/z 、 a/b/z 或 a/b/c/z 等。
# ?		只匹配一个任意字符
# [abc] 匹配任何一个列在方括号中的字符
# [0-9] 匹配所有 0 到 9 的数字

# 忽略所有子目录下以.o或.a结尾的文件
*.[oa]

# !取反，表示虽然忽略了*.a，但不忽略lib.a
!lib.a

# 忽略文件夹，/表示文件夹
tmp/

# /在开头表示防止递归匹配，只匹配当前目录下的TODO文件，
/TODO

doc/*.txt
doc/**/*.pdf
```



### 帮助

```bash
git add -h		# 只查看verb的可选选项
git <verb> --help
git help <verb>
```



### 开始

创建仓库

```bash
# 本地项目文件夹内使用
git init		
git add .
git commit -m "first commit"

# clone远程仓库，它会在当前目录下创建一个项目文件夹
git clone <url>
```



加入到暂存区

```bash
git add <file name>		# 将新文件/已修改的文件添加到暂存区
git add .				# 添加所有改动到暂存区
```



删除

```bash
git rm <file name>			# 取消追踪并删除该文件，等待下次提交
git rm --cached <file name>	# 从暂存区删除
git rm \*~					# 删除所有以`~`结尾的文件
```



移动、重命名

```
git mv <file src> <file dst>
```





查看差异

```bash
git diff			# 比较工作区与暂存区
git diff --stage	# 比较暂存区与commit区
```

