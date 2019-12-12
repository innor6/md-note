##### 下载安装

安装后打开git bash

配置用户名和Email地址：

```bash
$ git config --global user.name "innor"
$ git config --global user.email "innor@mail.ustc.edu.cn
```

##### 创建版本库

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

##### 添加文件与提交

在“learngit”目录（子目录）下创建文件“readme.txt”

随后打开bash

将文件放到暂存区（stage）

```bash
$ git add readme.txt
$ git add ... ... other files
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

##### 历史版本

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

##### 修改控制

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

# 远程仓库

##### 创建SSH Key

```bash
$ ssh-keygen rsa -C "innor@mail.ustc.edu.cn"
```

Github-Setting-SSH Keys，将公钥“id_rsa.pub”的内容填入。

在Github右上角，+ new repository，创建完毕后

##### 关联远程仓库origin

```bash
$ git remote add origin git@github.com:innorLMJ/learngit.git
```

##### 第一次推送

推送本地分支master，关联远程分支master

```bash
$ git push -u origin master
```

##### 普通推送

```bash
$ git push origin master
```

##### 克隆远程库到当前目录

```bash
$ git clone git@github.com:innorLMJ/xxx.git
```

# SourceTree

##### 添加git账号

##### 设置ssh

先按照**远程仓库**章节创建SSH Key

工具——选项——一般——SSH客户端配置——SSH客户端：选择OpenSSH

##### 添加库

建议先在本地用git建立好库，并连好远程库，再在sourcetree中添加库。