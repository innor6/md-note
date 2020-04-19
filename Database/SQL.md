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
FROM mytable
    JOIN another_table
      ON mytable.column = another_table.column
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

```
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
2. IN 的列表可以来自于子查询

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



### JOIN

连接多个表，通常连接后再使用WHERE条件

**INNER JOIN**

交集，通过不同的表具有相同的**主码**来进行连接

如果两个表中的主码名字不同，则`A.key1 = B.key2`可以写成`key1 = key2`

```sql
SELECT column, another_table_column
FROM A
INNER JOIN another_table 
    ON A.key = B.key
WHERE condition(s)
```

**LEFT/RIGHT/FULL JOIN**

通常不同表的数据非对称（主码不能全部一一对应）

用法同 `INNER JOIN` 

`LEFT JOIN`：保留表A中的全部行，并连接B中的行

`FULL JOIN`：保留表A和表B中的所有行，能连接则连接，不能则对应列留空值。



### 表达式和别名

在 SELECT 和 WHERE 中使用表达式：

```sql
SELECT particle_speed / 2.0 AS 
	half_particle_speed
FROM physics_data
WHERE ABS(particle_position) * 10.0 > 500;
```

**别名 AS**

```sql
SELECT column AS better_column_name
FROM a_long_widgets_table_name AS mywidgets
INNER JOIN widget_sales
  ON mywidgets.id = widget_sales.widget_id;
```

在`SELECT ... FROM ...`对列名、表名使用别名，在后续使用时（`WHERE`、`JOIN`等），可以直接用别名 替代原名



### 聚集函数

- 选择一个数值属性列，遍历其中元素进行计算，返回单一值
- 配合别名**AS**便于阅读
- **WHERE**进行第一次过滤
- 配合**GROUP BY**可先将某列中值相同的元素合为一组，再分别对每组调用聚集函数
- **HAVING**对打组后的返回值进行过滤

**注意**：使用打组后，一个组只会返回一行结果

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

SELECT column, another_column
FROM mytable
**UNION / UNION ALL / INTERSECT / EXCEPT
	SELECT other_column, yet_another_column
	FROM another_table**
ORDER BY column DESC
LIMIT *n*;

将两个查询结果（行）取并集/交集/去除，要求具有相同的列数。

集合操作发生于**ORDER BY**和**LIMIT**之前。

**UNION ALL**在合并行时不去重复的行，其余操作都会去重。



# DML

### INSERT INTO

插入行（可使用表达式）

```
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
    year INTEGER, 
    …
);
```

**数据类型**

- INTEGER, BOOLEAN
- FLOAT, DOUBLE, REAL
- CHARACTER(num_chars), VARCHAR(num_chars), TEXT
- DATE, DATETIME
- BLOB

**限制条件**

- PRIMARY KEY
- AUTOINCREMENT
- UNIQUE
- CHECK (expression)
- FOREIGN KEY



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

```
DROP TABLE IF EXISTS mytable;
```

如果有其他表依赖于待删除表，则应在删除之前，修改其他的表。