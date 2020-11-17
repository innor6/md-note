# SQL语法说明

- 使用 `;` 结束SQL语句
- SQL语句不区分大小写（建议关键字大写，表名小写）
- 所有空格、换行都被忽略
- 行与行之间不存在特定的前后顺序
- `''` 表示字符串（可以用字符串查询数值类型的字段）
- `NULL` 表示未知，而不是0
- 
- **别名**：
  - 表别名可以用在WHERE、SELECT、ORDER BY子句中
  - WHERE和GROUP BY不能使用列别名，而从HAVING之后都可以使用列别名了



执行顺序

```sql
SELECT DISTINCT column, AGG_FUNC(column_or_expression) AS , …	-- 要返回的行
FROM mytable a						-- 选择要检索的表
    JOIN another_table b
      ON a.column = b.column
    WHERE constraint_expression		-- 过滤行
    GROUP BY column					-- 分组
    HAVING constraint_expression	-- 过滤分组 (从HAVING开始可以使用列别名)
ORDER BY column ASC/DESC			-- 排序
LIMIT count OFFSET COUNT;			-- 限制结果行数
```





# 基本概念



- 数据库：保存表的容器
- 表：存储记录的结构化文件
- 模式：全体数据（数据库和表）的<u>逻辑结构和特征的描述</u>
- 列：表中的一个字段
- 行：表中 的一条记录

**主键**：能够唯一区分表中每一行的字段。

1. 主键用来查找特定的行
2. 可以用多个列作为主键
3. 每个行必须有主键（即主键的值不允许为NULL）
4. 任意两行的主键都不相同

主键使用建议：

1. 不更新主键列
2. 不重用主键列
3. 不在主键列使用可能会更改的值

**外键**：是某个表中的一列，它对应于另一个表的主键。从而这两个表之间具有了关系。

1. 引用完整性：插入数据时，外键的值必须是在另一个表的主键列中出现的合法值。（值集的包含）



# 查看数据库模式

选择数据库

```
USE crashcours;
```



显示所有数据库名

```
SHOW DATABASES;	-- 注意复数
```

显示当前数据库中的所有表

```
SHOW TABLES;	-- 注意复数
```

显示 `customers` 表中的列、相关信息

```sql
DESCRIBE customers;	-- 另一种写法
SHOW COLUMNS FROM customers;
```



其他的SHOW：

```
SHOW STATUS;	-- 服务器状态
SHOW GRANTS;	-- 用户安全权限
SHOW ERRORS;	-- 服务器错误
SHOW WARNINGS;	-- 服务器警告
```





# SELECT 检索数据

检索前五条数据：

```SQL
SELECT prod_id, prod_name, prod_price
FROM products
LIMIT 0, 5;
```

- 多个列之间用逗号 `,` 分隔

- 使用 `*` 检索全部的列

- **DISTINCT**：去除重复的行

- **LIMIT**： 限制结果的数目

  - 行号从0开始：`LIMIT 0, 5` 表示从第0行开始的<u>最多</u>5条记录
  - 当行数不够时：只返回小于最大行数的记录数目

- 完全限定的表名

  ```sql
  SELECT products.prod_name	-- 完全限定的列名
  FROM crashcourse.products	-- 完全限定的表名
  ```



# ORDER BY 排序

记录的顺序一开始是添加到表的顺序，但随着更新和删除，记录的顺序会随着MySQL重用回收存储空间的影响。——如果不明规定排序顺序，则认为检索出的数据的顺序是无意义的。

按多个列排序：

```SQL
SELECT prod_id, prod_price, prod_name
FROM products
ORDER BY prod_price DESC, prod_name;	-- 先按价格降序，再按名字升序排序
```

- 排序的字段 不一定要出现在结果中
- 默认按升序 `ASC` 排序，使用 `DESC` 降序排序
- 多个列排序时，`DESC` 只作用于它前面的一个列
- MySQL的默认字典序认为 `A` 和 `a` 相同



获取最高价格：

```sql
SELECT prod_price
FROM products
ORDER BY prod_price DESC
LIMIT 1;
```



# WHERE 过滤数据

虽然在软件应用层中也可以进行过滤，但这样

1. 需要检索出超出实际需要的数据
2. 通过网络传输多余的数据
3. 应用层需要进行额外的筛选工作，应用不具备可伸缩性。



**WHERE**：检查一个列是否包含特定的值

```sql
SELECT prod_name
FROM products
WHERE prod_name = 'FUSES';	-- 不区分大小写，返回的记录是'Fuses' 
```

- MySQL支持的条件操作符：`=` , `<>`, `!=` , `<`, `<=`, `>`, `>=` , `BETWEEN` , `IS NULL`
- 执行匹配时默认不区分大小写！！



##### **BETWEEN**：范围查询

```SQL
SELECT prod_name, prod_price
FROM products
WHERE prod_price BETWEEN 5 AND 10;	-- 查询价格在5~10的商品
```



##### **IS NULL**：查询空值

```SQL
SELECT prod_name, prod_price
FROM products
WHERE prod_price IS NULL;
```

- **NULL 不等于 0** ：NULL 具有特殊的含义，表示未知



##### **AND/OR**：组合子句

```sql
SELECT vend_id, prod_name, prod_price
FROM products
WHERE vend_id = 1002 OR vend_id = 1003 AND prod_price >= 10;
-- 这是错误的写法，它执行的是：
-- (vend_id = 1002) 或 (vend_id = 1003 且 prod_price >= 10)
-- 因为 OR 比 AND 后执行。
-- 正确写法，使用括号：
WHERE (vend_id = 1002 OR vend_id = 1003) AND prod_price >= 10;
```

- 注意优先级：AND 的优先级大于 OR（即 OR 比 AND 后执行）
- 建议任何使用AND和OR的地方都使用圆括号 `()` 消除歧义



##### **IN**：集合中查找

```sql
SELECT vend_id, prod_name, prod_price
FROM products
WHERE vend_id IN (1002,1003);
```

- 集合用圆括号`()`



##### **NOT**：反向查找

```sql
SELECT vend_id, prod_name, prod_price
FROM products
WHERE vend_id NOT IN (1002,1003);
```

- NOT 可以对 IN、BETWEEN、EXISTS 子句取反



##### **LIKE**：模式匹配

```sql
SELECT prod_id, prod_name
FROM products
WHERE prod_name LIKE '%anvil%';	-- 名字中任何位置包含anvil的商品
```

- % ：任意字符出现0次或多次
- _ ：任意字符出现1次

通配符使用技巧：

1. 通配符搜索代价大，尽量用其他操作符代替
2. 尽量不要把通配符置于搜索模式的开始处，否则搜索起来是最慢的





# **REGEXP** 正则表达式

```sql
SELECT prod_id, prod_name
FROM products
WHERE prod_name REGEXP '1000';	-- 只要名字中某处出现了1000就会被返回
-- 注意，如果使用LIKE，则必须整个名字 = '1000'才会被返回
```

元字符

| 符号                   | 含义                            | 用例                              |
| ---------------------- | ------------------------------- | --------------------------------- |
| `.`                    | 匹配任意一个字符                | `.000 kg`                         |
| `|`                    | 或                              | `1000 | 2000`                     |
| `[]`                   | 匹配字符集合中的任意一个字符    | `[123] kg`、`[0-9a-zA-Z]`         |
| `^`                    | 在[]中表示否定                  | `[^123]`                          |
| `\\`                   | 转义（escaping）                | `\\.`、`\\\`、`\\r`、`\\n`、`\\(` |
| `*`                    | 0个或多个                       |                                   |
| `+`                    | 1个或多个                       |                                   |
| `?`                    | 0个或1个                        | `[0-9] apples?`                   |
| `{n}`、`{n,}`、`{n,m}` | n个、至少n个、n~m个（m <= 255） | `[0-9]{4}`                        |
| `^`、`$`               | 文本的开始、结尾                |                                   |
| `[[:<:]]`、`[[:>:]]`   | 词语的开始、结尾                |                                   |

- 预定义的字符集：`[:blank:]` 空格和制表，`[:space:]` 空格换行等空白字符
- 转义：MySQL使用两个反斜杠 `\\` 进行转义（即MySQL解释一个，正则表达式库解释另一个）
- `[]`内的字符好像不需要转义？



REGEXP 和 LIKE 的区别：

- LIKE 匹配的是整个列
- REGEXP 则对列之内的子串进行匹配，如果匹配模式在列中出现，这一行就会被返回
  - `LIKE '1000'` 表示列值必须是 `1000`
  - `REGEXP '1000'` 只要求含有1000，因此可以匹配到 `1000 kg` 的列



简单测试表达式的正确性：

```sql
-- 'hello'中不含数字，返回0，表示0条记录能成功匹配
SELECT 'hello' REGEXP '[0-9]';
```





# 计算字段

字段（field）与列（column）含义相同。

有时我们需要 SELECT 返回一些不存在于数据表、但能通过已有列计算得到的字段。如计算平均值、总价、大小写转换、字符串拼接，通常这些操作直接在DBMS中完成会比较快。



拼接字段

```sql
SELECT Concat(vend_name , ' -- ', vend_country) AS vend_title	-- 使用了别名
FROM vendors;
-- 结果类似：'Furball Inc. -- USA'
```

- **Concat()** ：拼接多个字段，concatenat
- **使用别名** ：计算字段都建议赋予一个别名
  - AS 是可以省略的
  - 当列名、表名包含不符合规定的字符（如空格）时，也可以用别名来重命名
  - 还可以用来消除歧义



算术计算

```sql
SELECT
	prod_id,
	quantity,
	item_price,
    quantity * item_price AS expanded_price	-- 计算字段：数量 * 单价 = 总价
FROM orderitems;
```

- 算术操作符：`+`、`-`、`*`、`/`，注意优先级，可用括号。



测试计算结果

```
SELECT 3*2;
SELECT Trim('  abc ');
SELECT Now();
```



# 函数

函数的可移植性差，不同的DMBS的实现的函数不同。

tradeoff：如果不使用特殊实现的函数，性能变差、编写有些代码会很艰难。



### 文本处理

注意：字符串的下标从1开始。

- `SubString(str, pos, len)`：从pos开始的len个字符。不含len则表示到结尾。
- `Length(str)`：长度
- `Trim(str)`：去除左右的空格。还有 `Ltrim()`、`Rtrim()`
- `Upper(str)`：转换为大写。还有 `Lower(str)`
- `Left(str, len)`：取左边的len个字符。还有 `Right(str, len)`
- `Locate(substr, str)`：substr在str中第一次出现的位置，找不到返回0。还有可以有第三个参数pos，表示从pos开始查找substr。

- `Soundex(str)`：转换为发音，如`WHERE Soundex(name) = Soundex('Y Lie')` 可以匹配到 `Y.Lie`



### 日期和时间

注意：日期格式必须为`yyyy-mm-dd`

- `Now()`：返回当前的时间、日期
- `Date()`：提取日期部分
- `Time()`：提取时间部分
- `Year()`、`Month()`、`Day()`：提取年、月、日
- `Hour()`、`Minute()`、`Second()`：提取时、分、秒
- `DayOfWeek()`：星期几。（星期天 = 1，星期六 = 7）
- `Date_Format(order_date, '%Y.%m.%d. %H.%i.%s')`：格式化，[具体用法](https://www.w3school.com.cn/sql/func_date_format.asp)。

计算：

- `DateDiff(datetime, '2005-9-01')`：日期部分做差，返回日期数，可能为负。
- `AddDate(datetime, uint)`：日期部分加uint天
- `AddTime(datetime, time)`：时间部分加`'hh-mm--ss'`时间
- `Date_Add(datetime, INTERVAL -3 SECOND)`：日期增减一个时间间隔INTERVAL ，时间间隔可以是负数



常见错误：用 date 去匹配 datetime

```sql
SELECT order_num, order_date
FROM orders
WHERE order_date = '2005-09-01';
-- 错误：'2005-09-01'转换为datetime类型后，时间部分是零值，因此只能匹配到 '2005-09-01 00:00:00'，无法匹配到 '2005-09-01 11:30:05'
-- 正确做法：先提取日期部分
WHERE Date(order_date) = '2005-09-01';
```

- **如果要的是日期，请使用Date()**：养成习惯，即使知道列中只包含日期，也建议使用 `Date()` 提取日期部分。同理，需要时间时使用 `Time()`。



检索2005年9月份的所有订单

```sql
SELECT order_num, order_date
FROM orders
-- 方法1：提取日期，范围查询
WHERE Date(order_date) BETWEEN '2005-09-01' AND '2005-09-30';
-- 写法2：提取年和月份，等值查询
WHERE Year(order_date) = 2005 AND Month(order_date) = 9;
```



### 数值处理

- `Abs()`：绝对值
- `Rand()`：随机数
- `Sqrt()`：算术平方根
- `Mod(n, m)`：n % m
- `Exp(x)`：e^x
- `Pi()`
- `Sin()`、`Cos()`、`Tan()`





# 聚集函数

汇总数据：运行在一组行上，返回单个值。

- `AVG()`：某列的平均值
- `COUNT()`：某列的行数（指定的列为NULL时不进行计数）
- `MAX()`：某列的最大值（同样会忽略列值为NULL的行）
- `MIN()`：某列的最小值
- `SUM()`：某列之和

说明：

- 值为**NULL**的行不被计算
- 默认对所有行执行计算，即ALL
- **DISTINCT**：可以先对行去重，再执行聚集函数（见下一个例子）。



获取1003销售商的产品平均价格：

```sql
SELECT AVG(DISTINCT prod_price) AS avg_price	-- 2.去重，再计算平均值
FROM products
WHERE vend_id = 1003;	-- 1.先过滤，再调用聚集函数
```



统计电子邮件非空的客户数目：

```sql
SELECT COUNT(cust_email) AS num_cust	-- cust_email IS NULL的不被计数
FROM customers;
```



计算总价：

```sql
SELECT SUM(item_price * quantity) AS total_price	-- 对计算字段求和
FROM orderitems;
```





# GROUP BY 分组数据

GROUP BY 把数据分为多个逻辑组，然后就可以对每个组调用聚集函数：

```sql
SELECT vend_id, COUNT(*)	-- 根据vend_id分组，统计每个分组的记录数
FROM products
GROUP BY vend_id WITH ROLLUP;	
-- 使用WITH ROLLUP，结果中会多返回一行，其中COUNT(*)字段的值为所有记录的总数
```

- **WITH ROLLUP**：总计。使用该关键字，则会在结果中多返回一行，这一行中只有聚集字段是有值的，<u>它的值：相当于对未分组的原始行调用此聚集函数/计算表达式</u>。如有 `COUNT(*)` 字段，则该字段的值就是各个分组计数的总和；如有 `MAX(col)` 字段，则该字段就是各个分组最大值之中的最大值。

注意：

- GROUP BY中**不能使用<u>列别名</u>**。
- GROUP BY中每个列：要么是表中已有的列，要么是计算表达式（但不能是聚集函数）。
- **SELECT中每个列：要么是出现在GROUP BY子句中的列，要么是聚集计算表达式。**
- 如果要分组的列中有NULL值，则这些为NULL值的行都会被分到一个分组。
- 分组必须在WHERE之后，ORDER BY之前。
- 分组时可以指定多个字段。



过滤分组：

```sql
SELECT vend_id, COUNT(*) AS cnt	-- 列别名
FROM products
WHERE prod_price >= 10	-- 1.过滤行：价格大于10的
GROUP BY vend_id		-- 2.再分组
HAVING cnt >= 2			-- 3.过滤分组：总数大于2的 (注意：从这以后都可以用列别名了)
ORDER BY cnt;			-- 4.最后排序
```

- HAVING 支持 WHERE 所有的操作符。
- WHERE 过滤的是行，HAVING 过滤的是分组。
- WHERE 发生在分组之前，HAVING 发生在分组之后。
- 别名：从 HAVING 之后都可以使用列别名了
- 分组是无序的，想要有顺序请配合使用 ORDER BY。





# 子查询

构建方法：通常先编写内层的查询，测试通过后再写外层的查询。



### 用于过滤条件

获取购买了TNT2商品的客户名单

```sql
SELECT cust_id 
FROM orders
WHERE order_num IN (SELECT order_num as onum	-- 子查询返回一列
					FROM orderitems
					WHERE prod_id = 'TNT2');
```

- 先进行子查询（获取购买了TNT2商品的订单号），然后根据返回结果执行外部的查询（通过订单号找出下单的客户）
- **列数匹配**：如果外部查询的 WHERE 使用了 `IN` ，则子查询 SELECT 只能返回一列（列的名字无无所谓）；如果外部查询的 WHERE 使用的是 `=`、`>` 等，则子查询只能返回一个行。



### 用于计算字段

获取每个客户的订单总数

```sql
SELECT cust_name,
		cust_state,
        (SELECT COUNT(*)
        FROM orders
        WHERE orders.cust_id = customers.cust_id) AS orders  -- 这个别名没有冲突哦
FROM customers
ORDER BY cust_name;
-- 该语句其实可以用 左外连接+分组 等价实现（见下）
```

- 用途：为了得到计算字段，**对每一行调用子查询**。
- **歧义性**：注意到这里子查询使用了完全限定列名 `表名.列名` 来消除歧义。





# JOIN 连接

查询20005号订单的所有商品，及其对应的供货商：

```sql
SELECT vend_name, prod_name, quantity
FROM vendors v, products p, orderitems o		-- 等值连接三个表
WHERE v.vend_id = p.vend_id
	AND o.prod_id = p.prod_id
	AND order_num = 20005;
```

- 实际执行的是：将表1中的每一行与表2中的每一行进行配对，并通过 WHERE 过滤。
- **歧义性**：WHERE 中使用完全限定列名 `表名.列名` 以区分主键和外键。
- **表别名**：连接时常使用表别名
  - 以缩短SQL语句。
  - 可以使用同一个表的副本进行自连接（见下）。
- 若没有 WHERE 条件，就变成了笛卡尔积（表1中的每一行与表2中的每一行配对）。



自连接

获取 DTNTR 商品的供应商所生成的其他商品：

```sql
SELECT p1.prod_id, p1.prod_name	-- 易错点：要使用完全限定列名
FROM products p1, products p2	-- 同一个表使用两个别名
WHERE p1.vend_id = p2.vend_id
	AND p2.prod_id = 'DTNTR';
```

- **表别名**：使用同一个表的两个别名以进行自连接。
- **歧义性**：易错，查询列要用完全限定列名 `表名.列名` 消除歧义。



内部连接

```sql
SELECT vend_name, prod_name
FROM vendors INNER JOIN products
	ON vendors.vend_id = products.vend_id;	-- 这里的条件也可以是非等值连接，如 >
```



外部连接

```sql
SELECT customers.cust_name,
		customers.cust_id,
        COUNT(orders.order_num)	-- 左外连接时，右表的字段值可能为NULL，则COUNT()返回0
FROM customers LEFT OUTER JOIN orders
ON customers.cust_id = orders.cust_id
GROUP BY customers.cust_id;
```

- 使用外连接时，必须指定 `LEFT` 还是 `RIGHT`
- 左外连接：选择左边表的所有行，去关联右边的表，如果关联不到，则右边表的字段填充 NULL
- 右外连接：选择右边表的所有行，...





# UNION 组合查询

UNION：将多个SQL查询的结果按行合并。

语法：

```sql
SELECT查询
UNION			-- 使用UNION连接多个查询
SELECT查询
UNION
SELECT查询
ORDER BY ...;	-- 最后对合并的结果进行排序
```

- 每个查询必须包含相同的列数
- 列的名字由第一个查询决定
- 对应列的数据类型必须兼容（支持隐式类型转换）
- 合并时，默认会去除重复的行。若不想去重，使用 `UNION ALL`。
- ORDER BY 只能用在最后，用于对合并的结果进行排序。





# 全文搜索

MySQL中，只有MyISAM支持全文搜索，InnoDB是不支持的。

1. 相比与 LIKE 和 REGEXP，全文搜索可以控制必须匹配的词、不匹配的词等。
2. 可以按照匹配程度进行排序



**启用全文本搜索**

```sql
CREATE TABLE productnotes
(
	note_id		int			NOT NULL AUTO_INCREMENT,
	prod_id		char(10)	NOT NULL,
	note_data	datetime	NOT NULL,
	note_text	text		NULL,
	PRIMARY KEY(note_id),
	FULLTEXT(note_text)		-- 对note_text字段建立索引（也可以指定多个列）
)	ENGINE = MyISAM;		-- 注意引擎
```

- 全文搜索需要事先对数据建立索引。
- 建表时先不启用FULLTEXT索引，导入数据之后，再修改表为FULLTEXT，一次性对全部数据建立索引。（若一开始就启用了FULLTEXT索引，每次插入数据都要更新索引，导入数据慢）



**全文本搜索**

```sql
SELECT note_text, Match(note_text) Against('rabbit') 	-- 第二列是rank值
FROM productnotes
WHERE Match(note_text) Against('rabbit');	-- 指定搜索列note_text和搜索文本rabbit
```

- 返回结果按匹配程度rank排序。
- rank：`Match(note_text) Against('rabbit')` 实际上是对每一行计算该行对文本 `rabbit` 的匹配程度，称为rank值，不匹配时rank为0。
- 匹配时忽略词中的单引号，如 `don't` 索引为 `dont`。
- 若一个词出现在50%及以上的行中，则这个词被忽略（若总共只有两行，则全文本搜索一定不反悔结果）。



**查询扩展**

搜索与查询结果可能有关的行

```sql
SELECT note_text
FROM productnotes
WHERE Match(note_text) Against('anvils' WITH QUERY EXPANSION);	-- 使用查询扩展
```

执行过程：

1. 先对搜索词进行一次全文本搜索
2. 提取返回的行中的其他单词
3. 对这些单词再进行一次全文本搜索



**布尔文本搜索**

可以更灵活的指定匹配词、排斥、优先级。

```sql
SELECT note_text
FROM productnotes
WHERE Match(note_text) Against('>rabbit <carrot +bait -rope*' IN BOOLEAN MODE);	-- 布尔模式
-- 匹配rabbit或carrot，增大前者优先级，减小后者优先级，必须有bait，不含以rope开头的词
```

- **它不是全文本搜索**：不需要建立FULLTEXT索引，但因此也非常缓慢。
- 结果不按rank排序。





# INSERT INTO 插入数据

- 插入行
- 插入行的一部分呢
- 插入多行
- 插入某些查询的结果



简单写法：

```sql
INSERT INTO Customers
VALUES (NULL,			-- 自增列填NULL
	'Pep E. LaPew',
	'100 Main Street',
	'Los Angeles',
	'CA',
	'90046'
	'USA',
	NULL,				-- 必须允许该列为空时，才能填NULL
	NULL);
```

- INSERT语句没有输出
- 自增字段可以使用NULL，表示忽略，由MySQL自动填入正确值
- 缺点：必须按照表中列定义的顺序填入值，不能有省略的字段；一旦表结构发生改变，即列顺序改变，则SQL语句出错。



**推荐：指定列名的写法**

```sql
INSERT LOW_PRIORITY INTO Customers(cust_name,	-- LOW_PRIORITY降低插入语句的优先级
	cust_address,
	cust_city,
	cust_state,
	cust_zip,
	cust_country,
	cust_contact,
	cust_email)
VALUES ('Pep E. LaPew',
	'100 Main Street',
	'Los Angeles',
	'CA',
	'90046'
	'USA',
	NULL,
	NULL), (...), (...);	-- 可以一次性插入多行（比分开插入要快）
```

- 优点：不用按表中列定义顺序来填写值，即使表的结构发生改变，该SQL语句仍能正常工作。
- 可以省略的列：
  - 自增字段
  - 允许为空值NULL的列
  - 定义了默认值的列
- LOW_PRIORITY：降低INSERT插入语句的优先级。INSERT语句可能很耗时，如需要更新索引。通过该关键字可以让SELECT查询语句更优先的执行。



**插入查询结果**

```sql
INSERT INTO Customers(...列名)
SELECT ... FROM ...;			-- 使用SELECT子句替代VALUES子句
```

- SELECT查询结果的列次序要与指定的列次序一一对应，而列名字无所谓。





# UPDATE 更新数据

```sql
UPDATE IGNORE customers				-- 指定表名，IGNORE更新错误
SET cust_name = 'The Fudds',		-- 给列赋值
	cust_email = 'elmer@fudd.com'
WHERE cust_id = 10005;				-- 指定更新的行
```

- 使用UPDATE语句**一定要记得WHERE**
- IGNORE：若UPDATE更新多行，一旦更新到某一行时发生错误，则全部回滚；若不想回滚，而是忽略发生错误的这一行，并继续执行，使用IGNORE关键字。



# DELETE FROM 删除数据

```sql
DELETE FROM customers			-- 指定表名
WHERE cust_id = 10005;			-- 指定删除的行
```

- 使用DELETE语句**一定要记得WHERE**
- 若想要快速删除全部数据，使用 `TRUNCATE TABLE`，可以删除原来的表并重新创建一个新表。





# 创建表



```sql
CREATE TABLE customers IF NOT EXISTS		-- 表名
(
	cust_id			int			NOT NULL AUTO_INCREMENT,	-- 列名、定义
	cust_name		char(50)	NOT NULL,
	cust_address	char(50)	NULL,
	cust_city		char(50)	NULL,
	cust_state		char(5)		NULL,
	cust_zip		char(10)	NULL,
	cust_country	char(50)	NULL,
	cust_contact	char(50)	NULL,
	cust_email		char(255)	NULL,
	PRIMARY KEY (cust_id)
) ENGINE=InnoDB;


	cust_id			int			NOT NULL AUTO_INCREMENT,	-- 自增
	cust_state		char(5)		NULL,						-- 可以为空值
	quantity		int			NOT NULL DEFAULT 1,		-- 数量默认值为1（常量）
	PRIMARY KEY (order_num, order_item)					-- 主键可以指定多个列
```

- IF NOT EXISTS：创建新表时，指定的表名必须不存在，否则将出错；可以使用该关键字检查是否已有相同的表名。
- NULL：每个列或者是NULL列，或者是NOT NULL列。默认为NULL，而NOT NULL将会阻止空值被插入。
- PRIMARY KEY：
  - 主键可以是多个列组合定义的 `PRIMARY KEY (order_num, order_item)`。
  - 主键可以在创建表时定义，也可以在创建表之后定义。
- AUTO_INCREMENT：
  - 每个表只允许有一个自增列，且它必须被索引（如指定为主键/UNIQUE）。
  - 本列每当INSERT一行时，MySQL自动对该列增量，给该列赋值下一个可用值。
  - INSERT时，也可以对自增列指定一个未使用过的值，后序的增量将从该值开始增加。
  - `SELECT last_insert_id()`：获取最后一个AUTO_INCREMENT值，然后可以用于后续MySQL语句，作为另一个表的外键值。
    - 注意该语句中不需要指定表，因为它是基于connection的
    - 它返回的实际上是在当前用户与MySQL连接中，上一次插入（或其他操作）时生成的AUTO_INCREMENT值。
    - 由于它是基于连接的，从而多线程情况下，即使其他用户也进行了插入，此函数返回的还是本用户上一次生成的AUTO_INCREMENT值。
- DEFAULT：指定默认值
  - MySQL中默认值必须为常量。
  - 对于计算或数据分组的列，使用默认值而不是NULL。
- ENGINE：
  - 注意：一个库中不同表可以使用不同的引擎，但外键不能跨引擎（因为强制引用完整性）。
  - InnoDB：可靠的事务处理引擎，但不支持全文搜索。
  - MyISAM：性能极高，支持全文搜索，但不支持事务处理。
  - MEMORY：功能等同于MyISAM，但数据存储在内存中，速度很快，特别适合于临时表。





# 更改表

更改表的结构。

```sql
ALTER TABLE vendors
ADD vend_phone CHAR(20),		-- 添加vend_phone列
DROP COLUMN vend_address;		-- 删除vend_address列
```

- 对同一个表的多个更改通过逗号分隔



定义外键：

```sql
-- 给orderitems表定义两个外键
ALTER TABLE orderitems
ADD CONSTRAINT fk_orderitems_orders		-- 这里好像是两个表的名字？
FOREIGN KEY (order_num) REFERENCE orders (order_num);

ALTER TABLE orderitems
ADD CONSTRAINT fk_orderitems_products
FOREGIN KEY (prod_id) REFERENCE products (prod_id);
```



对于复杂的表结构更改，可能会使用 `INSERT ... SELECT ...` 将数据从旧表复制到新表；然后依次重命名旧表、新表；然后重新创建触发器、存储过程、索引、外键。



小心的使用ALTER TABLE：尽量先做备份。如果增加了不需要的列，可能不能删除他们；删除了不应删除的列，则可能会丢失该列的所有数据。





# 删除表

```sql
DROP TABLE customer2;	-- 如果存在表customer2，则删除
```



# 重命名表

```sql
RENAME TABLE backup_customers TO customers
             backup_vendors TO vendors
             backup_products TO products;
```





# 视图

视图是虚拟的表，只包含使用时动态检索数据的查询，例：

```sql
-- 这是一个涉及多表连接的查询
SELECT cust_name, cust_contact
FROM customers c, orders o, orderitems i
WHERE c.cust_id = o.cust_id
  AND o.order_num = i.order_num
  AND prod_id = 'TNT2';

-- productcustomers是一个视图，它其实是一个SQL查询，本身不包含任何列或数据
SELECT cust_name, cust_contact
FROM productcustomers
WHERE prod_id = 'TNT2';
```

- 视图本身不包含数据，它返回的数据是从其他表中检索出来的。
- 视图可以像表一样使用，如SELECT、过滤、排序、连接，甚至添加更新。
- 更改了底层表中的数据，视图将返回改变过的数据。



为什么用视图：

- 重用SQL语句。
- 简化复杂的SQL操作。
- 使用表的一部分，而不是整个表。
- 保护数据。给用户授予表的特定部分的访问权限，而不是整个表的访问权限。
- 更改数据格式和表示。视图可返回与底层表的表示和格式不同的数据。



视图的规则和限制

- 视图命名必须唯一，视图与表也不能重名。
- 创建视图需要有足够的访问权限。
- 视图可以嵌套创建。
- 在查询视图时使用ORDER BY，会覆盖视图内部的ORDER BY。
- 视图不能索引，也没有触发器、默认值。
- 视图可以和表一起使用，如连接视图和表。



### 创建视图

用法1：简化连接

```sql
CREATE VIEW productcustomers AS
SELECT cust_name, cust_contact, prod_id
FROM customers c, orders o, orderitems i
WHERE c.cust_id = o.cust_id
  AND o.order_num = i.order_num;

SELECT cust_name, cust_contact
FROM productcustomers			-- 使用视图
WHERE prod_id = 'TNT2';
```

- MySQL处理此查询时，将指定的WHERE子句添加到视图查询中已有的WHERE子句中，以便正确过滤数据。
- 创建可重用的视图，使用视图极大地简化了复杂SQL语句的使用。



用法2：格式化

```sql
CREAT VIEW vendorlocations AS
SELECT Concat(vend_name , ' -- ', vend_country) AS vend_title
FROM vendors
ORDER BY vend_name;

SELECT *						-- 使用视图
FROM vendorlocations;
```



用法3：过滤不想要的数据

```sql
CREATE VIEW customeremaillist AS
SELECT cust_id, cust_name, cust_email
FROM customers
WHERE cust_email IS NOT NULL;	-- 过滤掉没有邮箱的用户
```



用法4：使用计算字段

```sql
CREATE VIEW orderitemexpanded AS
SELECT order_num,
       prod_id,
       quantity,
       item_price,
       quantity * item_price AS expanded_price
FROM orderitems;

SELECT *
FROM orderitemsexpanded			-- 使用视图
WHERE order_num = 20005;
```



### 更新视图

视图主要用于数据检索，但视图可以有条件的更新底层基表的数据。

如果不能正确的确定被更新的基数据，则不允许更新（INSERT、UPDATE、DELETE），如果视图中 包含一下操作，就不能更新：

- 分组 GROUP BY
- 连接
- 子查询
- 并
- 聚集函数
- DISTINCT
- 导出（计算）列





# 存储过程

有点类似批处理，是多条MySQL语句的集合，其中某个查询结果是否满足条件，可能会影响其中另一些语句是否被执行。



为什么使用存储过程：

pdf: page177