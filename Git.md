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

### config

```bash
# 配置：用户名、邮箱
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com

# 别名
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
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



### gitignore

创建 `.gitignore` 文件，写入：

（子目录下也可以有自己的.gitignore文件）

```bash
# 默认会递归的应用到每个子目录中
# 以/开头表示防止递归匹配，只匹配当前目录下的TODO文件，
/TODO

# 忽略文件夹，/表示文件夹
tmp/

# 忽略所有子目录下以.o或.a结尾的文件
*.[oa]

# !取反，表示虽然忽略了*.a，但不忽略lib.a
!lib.a

doc/*.txt
doc/**/*.pdf

# 其实是一种正则表达式匹配，若文件路径file_path被匹配了则忽略
# 匹配规则：
# ?		只匹配一个任意字符
# * 	匹配零个或多个任意字符
# **	匹配零个或多个中间目录，比如 a/**/z 可以匹配 a/z 、 a/b/z 或 a/b/c/z 等。
# [abc] 匹配任何一个列在方括号中的字符
# [0-9] 0~9字 
```



### 基础

创建仓库

```bash
# 本地项目文件夹内使用
git init

# clone远程仓库，它会在当前目录下创建一个项目文件夹
git clone <url>
```



暂存修改：追踪已修改/新增/删除的文件

```bash
git add <file name>		# 将文件/目录添加到暂存区
git add .				# 添加所有改动到暂存区
git add -p				# 暂存部分修改（输入?查看交互操作的意思）
```



取消暂存

```bash
git rm --cached <file name>	# 从暂存区移除，并不再追踪
git rm <file name>			# 取消追踪并删除该文件，需要commit才会删除
```

注：取消stage、取消modify的命令可以在git status的提示中看到



修改commit

```bash
# 将暂存区的文件合并到上次提交，且可以修改commit message
git commit --amend
# 会生成新的hash值
```



移动、重命名

```bash
git mv <file src> <file dst>
```



标签

```bash
git tag			# 查看已有标签
git tag v1.3	# 添加轻量标签
git tag v1.2 <checksum>	# 给历史提交添加附注标签
git tag -a v1.4	# 添加附注标签-a
git show v1.4	# 查看标签信息

git push origin v1.4	# 将标签推送到远程
git push origin --tags	# 将所有标签推送到远程

git tag -d v1.4	# 删除本地标签
git push origin --delete v1.4	# 删除远程标签

git checkout v1.4	# 移动到标签位置，注意可能是分离HEAD状态，请创建分支
git checkout -b version1.4 v1.4
```

说明：相比轻量标签，附注标签还附带了创建者、创建时间、注释等信息。



### 分支

查看所有分支

```bash
git branch
--merged		# 查看已合并到当前分支的分支
--no-merged		# 查看尚未合并到当前分支的分支
```



创建分支

```bash
git checkout -b <newbranch> [<oldbranch>]
git branch <newbranch> [<oldbranch>]
```



切换分支

```bash
git checkout <branch>
```



合并分支

```bash
git merge hotfix	# 将hotfix合并到当前分支
```

说明：

1. 三方合并：基于两个分支及它们的最近公共祖先比较差异，并生成一个新结点。
2. 快进合并：如果hotfix是当前分支的后继，则当前分支的指针可以直接向前推进（fast-forward）
3. 如果两个分支合修改了同一个地方，则会冲突，打开文件解决冲突、删除冲突标记，然后add，commit。
4. 可以使用 `--no-commit` 选项来进行合并而不自动提交。



压缩合并

```bash
git merge --squash featA	# 将分支featA上的多次提交合为一次，合并过来
git commit		# 需要手动commit
```

说明：

1. squash合并后并不提交，因此你可以在提交之前利用squash来引入另一个分支的所有改动，并进行额外的修改。
2. 这样的合并提交后，前驱指针只会指向单个父结点。



合并分支2——变基

```bash
git checkout hotfix
git rebase master	# 将当前分支的基(base)接到master之后
# 等价于 git rebase master hotfix

git checkout master
git merge hotfix	# 由于hotfix在master之后，master可以直接快进合并
```

说明：

1. 先找到两个分支的公共祖先C，然后将当前分支从C开始的修改（patch）依次一个个接续到master之后，使得当前分支的提交链由指向公共祖先变为指向master。

2. 每次接续都可能有冲突，则需要解决冲突，add，然后继续` git rebase --continue`。

3. 合并后，原本分叉的分支提交历史会变为线性的提交历史。

4. 如果要对一个已经推送到远端的分支进行变基，则推送时添加 `-f` 参数：

   ```bash
   git push -f origin hotfix	# 将远程上的hotfix分支替换为新的hotfix
   ```

> 变基操作的实质是丢弃一些现有的提交，然后相应地新建一些内容一样但实际上不同的提交。
>
> 只对尚未推送或分享给别人的本地修改执行变基操作清理历史， 从不对已推送至别处的提交执行变基操作，这样，你才能享受到两种方式带来的便利。
>
> **如果提交存在于你的仓库之外，而别人可能基于这些提交进行开发，那么不要执行变基。**
>
> 如果你遵循这条金科玉律，就不会出差错。 否则，人民群众会仇恨你，你的朋友和家人也会嘲笑你，唾弃你。



删除分支

```bash
git branch -d hotfix			# 删除本地分支
git push origin --delete hotfix	# 删除远程分支
```



### 获取信息

查看日志

```bash
git log --graph --oneline	# 图形化的分支历史、一行显示一次提交
-p			# 显示每次提交的diff
--stat		# 显示文件的增删统计
--no-merges	# 隐藏merge的提交

# 自定义输出格式：
git log --pretty='%h: "%s" <%an> [%cr]'
# 84b1c3c: "first commit" <innor> [42 minutes ago]

# DIFF: 显示orgin/featA中有，featA中没有的提交
featA..origin/featA
# 即featA要追上origin/featA，需要合并哪些提交

-S keywords		# 只显示修改了关键字的提交
--author='innor'
--since='2020-11-18'
--before='2020-12-24'
-- <filepath>	# 在命令的最后可以选定文件或目录
```



查看差异

```bash
git diff			# 比较工作区与暂存区
git diff --stage	# 比较暂存区与上次提交的
git diff master...featA	# 显示featA相对于两者公共祖先提交的修改
```



查看状态

```bash
git status
```



帮助

```bash
git add -h		# 只查看verb的可选选项
git <verb> --help
git help <verb>
```



### 远程

查看远程仓库

```bash
git remote -v
# output: origin	https://github.com/schacon/ticgit (fetch)
```



添加远程仓库

```bash
git remote add <remote-name> <url>	# 远程名是自定义的
```



拉取数据

```bash
git fetch	# 只是拉取远程的数据
git pull	# 拉取数据后，自动合并当前分支
```



推送数据

```bash
git push <remote> <branch>	# 将分支提交到远程
```

fetch-merge-push：如果别人已经先于你推送了该分支，你必须先拉取他们的工作合并后才能推送：

```bash
# 两人都基于origin/master开发
# 若Alice提交了修改，并push到了origin/master
# 则当Bob基于原来的master修改，并push时，由于本地的master落后了，会被拒绝
# Bob必须先抓取master的上游改动，合并到本地仓库中后，才能被允许推送。
# 三步走:
→ git fetch
↓ git merge origin/master
← git push origin master
```

个人理解：当你要push一个分支到远程时，你必须保证本地分支在远程分支的上游，即远程分支是本地分支的祖先结点，使得远程分支可以通过fast-forward来到达本地分支。



推送到另一个远程分支

```bash
git push origin featB:featBee	#将本地的featB推送到origin/featBee
```

- 使用了引用规范



删除远程分支

```
git push origin --delete hotfix
```





### 引用分支

祖先引用

```bash
HEAD^^
d921970^2	# 第二父提交，即merge过来的分支
HEAD~3
HEAD~~~
HEAD~3^2	# HEAD~3的第二父提交
```



提交区间

```bash
# 两点：显示在featA分支中，而不在master分支中的提交
git log master..featA		# 也表示master需要合并哪些提交才能追上featA
git log origin/master..master	# 可以用来查看push会推送的提交

# 多点：显示在分支refA和refB中，但不在分支refC和refD中的提交
git log refA refB ^refC --not refD

# 三点：显示只属于某一侧分支的提交，但不显示同时被两侧包含的分支
git log master...featA --left-right	# 该选项可以显示提交属于哪一边
```



引用的历史记录：查看之前HEAD指向的引用

```bash
git reflog
# 734713b HEAD@{0}: commit: fixed refs handling,
# d921970 HEAD@{1}: merge phedders/rdocs
# 1c002dd HEAD@{2}: commit: added some blame
```

- 可以用类似 `HEAD@{1}` 的方式进行引用



```
可以在命令行中使用 git add -p 或 git add --patch 来启动同样的脚本。

更进一步地，可以使用 git reset --patch 命令的补丁模式来部分重置文件， 通过 git checkout --patch 命令来部分检出文件与 git stash save --patch 命令来部分暂存文件。 我们将会在接触这些命令的高级使用方法时了解更多详细信息。
```



### 贮藏 & 清理

贮藏

```bash
git stash		# 把当前工作目录的修改贮藏到栈上
git stash pop	# 弹出栈顶的贮藏，并应用到当前分支
git stash apply # 应用栈顶的贮藏（不弹出）
git stash drop  # 删除栈顶的贮藏
--index			# 应用贮藏时，不会应用到当前分支中已经stage的文件

git stash list	# 显示贮藏栈
git stash pop/apply/drop stash@{1}	# 可以应用/删除指定的贮藏

git stash -u	# 未追踪的文件也会被贮藏（但不会贮藏被忽略的文件，除非加上-a/--all）

git stash branch <new branchname> # 从贮藏时的结点处创建一个新分支，弹出并应用贮藏
```

- 贮藏可以被应用到不同分支。
- 应用贮藏时，可能会产生合并冲突。



清理

```bash
git clean		# 删除未被追踪文件（不删除被忽略的文件）
git clean -n	# 不真正执行删除，用于查看将会删除哪些文件（执行时-n改为-f）
-d		# 还会删除空的子目录
-x		# 还会删除被忽略的文件

git stash --all	# 更安全的"删除"方法
```

