

##### **cat、echo、less：打印文本**

保存数据到文件

```
xxx > a.log
```





##### **grep：筛选包含正则表达式的行**

```
xxx | grep abc | grep "an apple"
```



##### **sed：表达式替换**

对每行<u>第一个</u>匹配的表达式进行替换

```shell
xxx | sed 's/{{regex}}/{{替换值}}/'	#用/分隔
xxx | sed -E 's/{{regex}}/{{替换值}}/' #使用扩展的regex
```

替换为空（删去）

```shell
xxx | sed 's/{{regex}}//'
```

对<u>所有</u>匹配的进行替换

```shell
xxx | sed 's/{{regex}}/{{replace}}/g'
```

打组：

```shell
echo 'ip 1.1.1.1' | sed -E 's/^(.*) ([0-9.]+)$/\2/'
#分为了两组，\2表示输出第二组，即提取出ip地址
#通常为了精确匹配，需要用头^尾$定位
#.*?：惰性匹配，使表达式成立的最短匹配
```





##### **head：显示头五行**

```shell
cat file | head -n5
```

##### **tail:显示尾十行**

```shell
cat file | tail -n10
```



##### **wc：字数统计**

```shell
xxx | wc	#输出行数、单词数、字数
xxx | wc -l	#统计行数
```



##### **sort | uniq：对行排序、去重**

```shell
xxx | sort | uniq -c	#-c输出每行重复的数目
```

对第3列按数字序(n)排列，多列用逗号表示区间

```shell
sort -k 3n
```



##### **awk：打印列**

打印第一列

```shell
xxx | awk '{print $1}'
```

查找“第一列值为1，第二列任意，包含regex”的所有行，打印所有列

```shell
xxx | awk '$1 == 1 && $2 ~ /^c.*e$/ {print $0}'
```



##### **paste：连接每一行**

```shell
xxx | paste -sd+	#每一行用+连接
```

##### **bc：计算算术表达式**

```shell
xxx | paste -sd+ | bc -l
```



**xargs：转换为参数**

```shell
一列参数 | xargs CMD	#将数据作为CMD的参数
```

