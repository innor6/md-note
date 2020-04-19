# 脚本

#### 使用脚本

1. `vim mcd.sh` 创建如下脚本：

   ```
   mcd () {
       mkdir -p "$1"
       cd "$1"
   }
   ```

2. `source mcd.sh` 将脚本加载到shell中
3. `mcd xxx`调用脚本



#### 定义变量

```bash
foo=bar
echo "$foo" #输出变量的值
echo '$foo' #输出字符串
```

注意：

1. 空格，`foo = bar` 是错误的，=和bar会解析为foo命令的参数。
2. 双引号`""`才是引用变量



#### 特殊变量

- `$0` 脚本名称
- `$1`~`$9` 脚本的参数。`$1`是第一个参数，依此类推。
- `$@` 所有的参数
- `$#` 参数数量
- `$$` 当前脚本的进程标识号
- `$?` 上一条命令的返回值（`echo $?`查看错误代码）
- `!!` 上一个命令及其参数（用法：`sudo !!`）
- `$_` 上一个命令的最后一个参数（shell中可用`ESC .`输入一个`$_`）

- 每个命令都有一个返回值，可通过返回值进行短路执行：

```shell
true || echo "Will not be printed"
true && echo "Things went well"
false ; echo "This will always run"
```

- `[[]]` ：逻辑表达式

```shell
if [[ $? -ne 0 ]]; then #if上一个命令返回值不等于0
fi
```



- `$(CMD)` ：替换为命令的输出

```shell
echo "We are in $(pwd)" #替换为命令的输出
echo "Now is $(date)"	#替换为命令的输出
for file in $(ls)		#对ls的输出迭代
```

- `<(CMD)` ：将命令的输出输出到临时文件，再替换为文件名

```shell
diff <(ls foo) <(ls bar) #将ls结果输出到临时文件，再以文件名的形式传参给diff。这里的执行结果显示的foo和bar文件夹的差异
```



- `{}` ：扩展

```shell
touch foo{,1,2,10}
#touch foo foo1 foo2 foo10
touch foo{a..c}
#touch fooa foob fooc
#含有多个{}将做笛卡尔积
```



- `#!` ：设定文件的打开方式，在文件的第一行写

```
#!/usr/bin/env python
```



- `shellcheck a.sh` ：用于检查shell脚本错误









# 工具

1. `tldr CMD`：命令使用说明，“太长不读”版的`man`

2. `find`：查找文件（`-type d`查找目录，`-type f`查找文件）

   ```shell
   find . -path '**/lib/**/*.sh' #从当前目录查找匹配路径名
   find . -name '*.sh' #只匹配文件名
   find . -mtime -7	#最近7天修改过的文件
   find . -name '*.tmp' -exec rm {}\; #查找并执行命令，{}对应文件名
   #-type d查找目录
   #-type f查找文件
   # fd: 简单版find(没下到)
   ```

   ```shell
   #另一种查找方式：建立数据库索引
   `locate` uses a database that is updated using cmd `updatedb`. In most systems updatedb is updated daily via `cron`. 
   ```

3. `grep` / `rg (ripgrep)`

   ```shell
   grep 'PATTERN' FILE
   grep -E --color 'PATTERN' filename #（-E使用扩展的regexp，--color高亮匹配的字串，注意color前面是两横！，-n显示行号）
    
   rg 'PATTERN' [DIR/FILE] #在指定的目录下/文件中查找
   xxx | rg 'PATTERN' #在命令的输出中查找
   
   -t txt 	#指定查找文件类型
   -v 		#反向查找
   -C 5 	#显示上下五行 -B -A 
   -e 'PATTERN' #后跟查找的模式
   --files-with-matches #只打印文件名
   
   --files-without-match #找出所有不含
   -u 		#包括查找隐藏文件
   --stats #显示统计信息
   ```

4. `history 3` 查看最近三条历史命令

   `ctrl + R`：输入查找模式，多次按下快捷键，反向搜索历史命令

5. `fzf` ：模糊查找（逆向的）

   ```
   cat a.sh | fzf
   ```

6. 目录查看

   ```shell
   tree . -L 3 #打印从当前目录开始的3层tree
   -P 'PATTERN' #只显示匹配的文件名
   -s -h #显示文件大小
   ```