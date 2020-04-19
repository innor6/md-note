# VIM

打开文件：`vi filename`

##### 命令行模式

- `:q`：退出
- `:w`：保存
- `:w filename`：指定文件名保存
- `:help [key]`：查看命令对应的帮助



##### 插入模式

- `i`：前插
- `a`：后插
- `o`：在下面新建一行插入
- `O`：在上面新建一行插入



##### 普通模式

- `ZZ`：存盘退出

- `ZQ`：不存盘退出

- `u`：撤销（`ctrl + R`重做）

- `y`：复制（`yy`复制整行）

- `p`：粘贴

- `x`：剪切

- `d`：删除，配合移动动作，删除经过的路径（`dd`删除整行）

  - 删除单词：`b`到达单词开头，`dw`删除单词
  - 删除括号中内容：`ci(`

- `c`：同上，删除后进入插入模式

- `r`：替换

  



##### 光标移动

- 基础：`hjkl`，左下上右
- 单词：`w`（下一单词），`b`（上一单词），`e`（下一单词结尾）
- 行：`0`（行首），`$`（行尾），`^`（非空行首）
- 屏幕：`H`（上），`M`（中），`L`（下）
- 滑动：`ctrl+u`（up），`ctrl+d`（down）
- 文件：`gg`（文件开头），`G`（文件末尾）
- 第i行：`:i`
- 括号间移动：`%`



##### 查找

- `f{char}`：查找下一个字符，如`fc`移动到下一个c（`F`反向查找）
- `/{regex}`：模式匹配
  - 回车确定
  - 按n查找下一个匹配的
  - `/\v{regex}`元字符都不需要加反斜杠



##### Visual选择

1. 按`v`进入可视模式，此时任何的移动操作都会选取经过的路径
2. 按`y`进行复制，并回到正常模式
3. 按`p`粘贴

- `V`进入行模式，整行选取
- `ctrl+V`进入块模式，按块选取







##### 多窗口

- `:sp`：分裂窗口
- `:vsp`：左右分裂
- `:sp filename`：在新窗口中打开另一文件
- `:close`：关闭窗口（`ctrl + w + c`）
- `:only`：只留下当前窗口
- `ctrl + w + h/j/k/l`：在窗口间切换（或方向键）
- `ctrl + ww`：切换到下一窗口
- `ctrl + w + x`：交换当前和下一个窗口
- 
- `:tabnew`：打开新的tab
- `:tab [cmd]`：cmd生成的新窗口将会放在新tab中
- `:tabc`：关闭tab
- `:tabo`：只留下当前tab
- `:qa`：关闭所有窗口和tab



##### 杂

数字+命令：多次执行命令

`.`：重复上次修改操作



选项：

`+`：将光标置于末尾

`+n`：光标置于第n行

`-r`：恢复崩溃的文件





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





# 插件

1. 安装vundle插件管理器

   ```
   git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim
   ```

   配置.vimrc

   ```
   sudo vim /etc/vim/vimrc
   ```

   粘贴以下内容

   ```
   set nocompatible               "去除VIM一致性，必须"
   filetype off                   "必须"
   
   "设置包括vundle和初始化相关的运行时路径"
   set rtp+=~/.vim/bundle/Vundle.vim
   call vundle#begin()
   
   "启用vundle管理插件，必须"
   Plugin 'VundleVim/Vundle.vim'
   
   "在此增加其他插件"
   "安装github上的插件格式为 Plugin '用户名/插件仓库名'"
   
   call vundle#end()              
   filetype plugin indent on      "加载vim自带和插件相应的语法和文件类型相关脚本，必须"
   ```

   将要安装的插件插在其中的这两行之间：

   ```
   call vundle#begin()
   call vundle#end()
   ```

   

2. 安装YouCompleteMe代码补全插件

   配置.vimrc

   ```
   sudo vim /etc/vim/vimrc
   ```

   在`call vundle#begin()`以及`call vundle#end() `之间加入：

   ```
   Plugin 'Valloric/YouCompleteMe'
   ```

   保存退出`:wq`

   进入vim，`:PluginInstall`进行安装插件

3. 安装Vim-go

   下载

   ```
   git clone https://github.com/fatih/vim-go.git ~/.vim/bundle/vim-go
   ```

   配置.vimrc

   ```
   sudo vim /etc/vim/vimrc
   ```

   在`call vundle#begin()`以及`call vundle#end() `之间加入：

   ```
   Plugin 'fatih/vim-go'
   ```

   保存退出`:wq`

   进入vim，`:PluginInstall`进行安装插件

   进入vim，`:GoInstallBinaries`安装依赖工具

4. 删除插件

   配置.vimrc

   ```
   sudo vim /etc/vim/vimrc
   ```

   删除插件名，保存退出。

   进入vim，`:PluginClean`清除插件。

