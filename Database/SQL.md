[TOC]

说明：

- 大小写不敏感，通常关键字使用大写
- 空格、换行随便用
- 每条SQL语句末端建议使用分号
- 使用单引号`''`环绕文本值
- SELECT查询语句可以嵌套使用，对其返回结果进一步操作



# DQL

### [总]语句执行顺序

```sql
SELECT DISTINCT column, AGG_FUNC(column_or_expression), …
FROM mytable a
    JOIN another_table b
      ON a.column = b.column
    WHERE constraint_expression
    GROUP BY column
    HAVING constraint_expression
ORDER BY column ASC/DESC
LIMIT count OFFSET COUNT;
```

1. **FROM & JOIN**：提取表格得到总的工作数据集
2. **WHERE**：依次对每一行进行过滤
3. **GROUP BY & HAVING**：打组和过滤
4. **SELECT**：执行其中的表达式，此后可以使用<u>别名</u>
5. **DISTINCT**：去重
6. **ORDER BY**：排序
7. **LIMIT / OFFSET**：限制返回条数



### **SELECT**

```sql
SELECT column,column2 FROM mytable;
SELECT * FROM table_name;
```

**SELECT DISTINCT**

去掉重复的行

```sql
SELECT DISTINCT column FROM mytable;
```



### **WHERE过滤**

条件从句

```sql
SELECT column, another_column, …
FROM mytable
WHERE condition
    AND/OR another_condition
    AND/OR …;
```

**空值**

```sql
WHERE column IS/IS NOT NULL
```

**数值运算符**

| Operator           | Condition   | SQL Example                           |
| ------------------ | ----------- | ------------------------------------- |
| =, !=, < <=, >, >= | 数值比较    | col_name **!=** 4                     |
| BETWEEN … AND …    | 闭区间[a,b] | col_name **BETWEEN** 1.5 **AND** 10.5 |
| IN (…)             | 在列表中    | col_name **IN** (2, 4, 6)             |

注：

1. 反向操作：NOT BETWEEN、NOT IN

2. IN 的集合可以来自于子查询，常用于嵌套查询

3. ANY / ALL可表示任意 / 且：

   ```sql
   WHERE score > any(...) //score大于集合中任意一个元素，即大于最小值
   WHERE score > all(...) //score大于集合中所有元素，即大于最大值
   ```

**字符串运算符**

| Operator  | Condition | Example                         |
| --------- | --------- | ------------------------------- |
| =, !=, <> | 相等/不等 | col_name **=** "abc"            |
| LIKE      | 模式匹配  | col_name **LIKE** "CA_"         |
| IN (…)    | 在列表中  | col_name **IN** ("A", "B", "C") |

注：

1. 字符串需要用引号`''`包围
2. 反向操作：NOT LIKE、NOT IN
3.  **LIKE**的模式匹配可使用通配符（ `%` ：0个或多个任意字；`_` ：单个任意字符）

**日期**

`datediff(w1.Date, w2.Date) = 1` ：日期作差，1表示左边比右边晚一天



### ORDER BY/LIMIT OFFSET

ORDER BY ... ASC/DESC：排序

LIMIT ... OFFSET ...：指定返回结果的行数（该从句通常写在最后）

```sql
SELECT column, another_column, …
FROM mytable
WHERE condition(s)
ORDER BY column [ASC/DESC]
LIMIT num_limit [OFFSET num_offset];
```

多字段排序：

```sql
ORDER BY col1 ASC, col2 DESC
```

从下标0开始取2条记录：

```sql
LIMIT 0,2
```

**下标偏移从0开始！！**



### JOIN

连接多个表，通常连接后再使用WHERE条件

**多表查询**

用where进行连接（交集）

```sql
SELECT column, another_column, …
FROM table1, table2
WHERE table1.id = table2.id;
```

**INNER JOIN**

交集，通过不同的表具有相同的**主码**来进行连接

如果两个表中的主码名字不同，则`A.key1 = B.key2`可以写成`key1 = key2`

```sql
SELECT column, another_table_column
FROM A
INNER JOIN B
    ON A.key = B.key
WHERE condition(s)
```

**LEFT/RIGHT/FULL JOIN**

通常不同表的数据非对称（主码不能全部一一对应）

用法同 `INNER JOIN` 

`LEFT JOIN`：保留表A中的全部行，并连接B中的行。A中的key若不能在B中找到对应的key，则B部分字段为NULL。

`FULL JOIN`：保留表A和表B中的所有行，能连接则连接，不能则对应列留空值。



### 表达式和别名

**别名 AS**

```sql
SELECT a AS alias, b AS blias from ...
```

在 SELECT 和 WHERE 中使用表达式：

```sql
SELECT particle_speed / 2.0 AS 
	half_particle_speed
FROM physics_data
WHERE ABS(particle_position) * 10.0 > 500;
```

在`SELECT ... FROM ...`创建的别名，在后续使用时（`WHERE`、`JOIN`等），可以直接用别名 替代原名

```sql
SELECT column AS better_column_name
FROM a_long_widgets_table_name AS mywidgets
INNER JOIN widget_sales
  ON mywidgets.id = widget_sales.widget_id;
```



### 聚集函数

- 选择一个数值属性列，遍历其中元素进行计算，返回单一值
- 配合别名**AS**便于阅读
- **WHERE**进行第一次过滤
- **GROUP BY**对记录按指定列的值进行分组，随后可分别对每组调用聚集函数
- **HAVING**对打组后的返回值进行二次过滤

**注意**：

使用打组后，一个组只会返回一行结果

having和where后面一样都是写条件表达式，只是having针对组内元素，因此having的条件表达式还可以用聚合函数。

```sql
SELECT FUNC(column_or_expression) AS alias, column2, ...
FROM mytable
WHERE constraint_expression
GROUP BY column
HAVING group_condition;
```

- COUNT(*), COUNT(column)
- MIN(column)
- MAX(column)
- AVG(column)
- SUM(column)

### 集合操作

将两个查询结果（行）取并集/交集/去除（**UNION / UNION ALL / INTERSECT / EXCEPT**），要求具有相同的列数。

将含相同列的记录合并：

```
查询子句1 UNION 查询子句2
```

执行顺序：

```
SELECT column, another_column
FROM mytable
**UNION / UNION ALL / INTERSECT / EXCEPT
	SELECT other_column, yet_another_column
	FROM another_table**
ORDER BY column DESC
LIMIT n;
```

- 集合操作发生于**ORDER BY**和**LIMIT**之前。

- **UNION ALL**在合并行时不去重复的行，其余操作都会去重。



### 一些函数

`datediff(w1.Date, w2.Date) = 1` ：日期作差，1表示左边比右边晚一天

`if(expr1, expr2, expr3)`：三目运算，如果 `expr1` 为真（非0非null），返回 `expr2` ，否则返回 `expr3`

`round(col, decimals)`：舍入，第二个参数decimals决定保留的小数位数。





# 笔记

### 别名

如果是连接两个表，则两个表建议取别名，使用字段时，相同名字的字段必须使用 `别名.xxx` 来避免歧义；

但是如果是嵌条表达式，则不必用别名：

```SQL
--获取不在dept_manager表中的employees
--虽然两个表都有emp_no字段，但是由于是嵌条查询，因此可以不用别名
SELECT emp_no FROM employees
WHERE emp_no NOT IN (
    SELECT emp_no FROM dept_manager
)
```

SELECT ... FROM ... 中定义的别名，在having中也可以使用，甚至可以给函数表达式做别名

```SQL
--统计出现次数超过15次的人
SELECT emp_no, COUNT() t FROM salaries
GROUP BY emp_no
HAVING t > 15	--可以使用COUNT()的别名t
```



### GROUP BY

易错：使用 `GROUP BY` 时， SELECT子句中只能有聚合键（即被GROUP BY的字段）、聚合函数、常数，而不能出现非聚合字段。

1. 一个聚合的某一个分组里，一个聚合字段值对应了多个非聚合字段值，因此，如果在 SELECT 中使用非聚合字段，则不知道应该选择哪一个非聚合字段值。如果希望 SELECT 中出现非聚合字段，可以考虑看能否把字段放到聚合函数中。
2. 当有一个聚合中，一个分组中满足HAVING条件的有多条记录时，只能得到其中的一条记录，则其他满足条件的记录就无法查出了。
3. HAVING 筛选的是分组，而不是记录，因此应该使用聚合函数来构造条件表达式



# DML

### INSERT INTO

插入行（可使用表达式）

```sql
INSERT INTO mytable
VALUES (val1, val2, ...),
       (val3, expr, ...), ...
```

指定属性列（要求其他列有默认值）

```sql
INSERT INTO mytable
	(col1, col2)
VALUES (val1, val2),
       (val3, expr), ...
```



### UPDATE

修改（通过**WHERE**选择修改的行）

```sql
UPDATE mytable
SET column1 = value1, 
    column2 = expr, 
    …
WHERE condition;
```

常见错误：

修改了一个指针，或忘写**WHERE**而修改了整列。



### DELETE FROM

```sql
DELETE FROM mytable
WHERE condition;
```

同样不要忘记**WHERE**。



# DDL

### CREATE

创建表

```sql
CREATE TABLE IF NOT EXISTS mytable (
    //列名 数据类型 表限制 DEFAULT 默认值,
    id INTEGER PRIMARY KEY,
    title TEXT,
    director TEXT,
    year INTEGER DEFAULT 1990, 
    …,
    //约束条件也可以写在最后，如
    primary key(id,name)
    
);
```

**数据类型**

- INTEGER, BOOLEAN
- FLOAT, DOUBLE, REAL
- CHARACTER(num_chars), VARCHAR(num_chars), TEXT
- DATE, DATETIME
- BLOB

函数year(column_date)可以获取datetime的年。

**约束条件**

- PRIMARY KEY
- AUTOINCREMENT
- UNIQUE
- NOT NULL
- CHECK (expression)
- FOREIGN KEY

添加主码约束：ALTER TABLE mytable ADD primary key(id);
删除主码约束：ALTER TABLE mytable DROP primary key;
通过修改字段来修改约束：ALTER TABLE mytable MODIFY id int primary key;

删除唯一约束：ALTER TABLE mytable DROP index col_name;
修改唯一约束：modify

关于外码：

```
FORIGN KEY(本表中的字段) references 另一表名(另一表的字段) 
```

- 外码所引用的字段在主表中必须为主码
- 副表插入记录时，外码的值必须在主表中已存在
- 主表的记录被副表引用时，不能被删除



### ALTER

修改表

**添加列**

```sql
ALTER TABLE mytable
ADD column DataType Constraint DEFAULT default_value;
```

**删除列**

```sql
ALTER TABLE mytable
DROP column_name;
```

**重命名表名**

```sql
ALTER TABLE mytable
RENAME TO new_table_name;
```



### DROP

删除表

```sql
DROP TABLE IF EXISTS mytable;
```

如果有其他表依赖于待删除表，则应在删除之前，修改其他的表。