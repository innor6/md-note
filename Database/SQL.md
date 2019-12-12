# SQL

Structured Query Language

结构化查询语言，是关系数据库的标准语言

SQL是一个通用的、功能极强的关系数据库语言

## 概述

### 基本概念

关系数据库三级模式结构：

![](C:\Users\64589\Documents\Tepora\Database\3-TierSchema.png)

存储文件：它的逻辑结构组成了关系数据库内模式。

基本表：对应SQL中一个关系。

视图：从多个基本表、视图上导出的虚表，只存放视图的定义而没有对应的数据，其中的数据会随基本表动态变化。

### 特点

**综合统一**

ANSI SQL语句分成以下六类（按使用频率排列）：

- 数据查询语言（DQL）：其语句，也称为“数据检索语句”，用以从表中获得数据，确定数据怎样在应用程序给出。保留字SELECT是DQL（也是所有SQL）用得最多的动词，其他DQL常用的保留字有WHERE，ORDER BY，GROUP BY和HAVING。这些DQL保留字常与其他类型的SQL语句一起使用。
- 数据操作语言（DML）:其语句包括动词INSERT，UPDATE和DELETE。它们分别用于添加，修改和删除表中的行。也称为动作查询语言。
- 事务处理语言（TPL）：它的语句能确保被DML语句影响的表的所有行及时得以更新。TPL语句包括BEGIN TRANSACTION，COMMIT和ROLLBACK。
- 数据控制语言（DCL）：它的语句通过GRANT或REVOKE获得许可，确定单个用户和用户组对数据库对象的访问。某些RDBMS可用GRANT或REVOKE控制对表单个列的访问。
- 数据定义语言（DDL）:其语句可在数据库中创建新表（CREAT TABLE）；为表加入索引等。DDL包括许多与人数据库目录中获得数据有关的保留字。它也是动作查询的一部分。
- 指针控制语言（CCL）：它的语句，像DECLARE CURSOR，FETCH INTO和UPDATE WHERE CURRENT用于对一个或多个表单独行的操作。

**非过程化**

非关系数据模型：数据操纵语言“面向过程”，必须指定存取路径。

SQL：只要提出“做什么”，无须了解存取路径。存取路径的选择以及SQL的操作过程由系统自动完成。

**面向集合**

非关系数据模型：采用面向记录的操作方式，操作对象是一条记录。

SQL： 操作对象、查找结果可以是元组的集合； 一次插入、删除、更新操作的对象可以是元组的集合。

**多种使用方式**

SQL能够独立地用于联机交互的使用方式；也能够嵌入到高级语言（例如C，C++，Java）程序中，供程序员设计程序时使用。

**语言简洁**

核心功能只用了9个动词：

| SQL功能  | 动词                   |
| -------- | ---------------------- |
| 数据查询 | SELECT                 |
| 数据定义 | CREATE，DROP，ALTER    |
| 数据操纵 | INSERT，UPDATE，DELETE |
| 数据控制 | GRANT，REVOKE          |



## 一、数据定义

层次化的数据库对象命名机制：

RDBMS的实例→数据库→模式（schema）→表(table)、视图（view）、索引（index）

### 数据字典

RDBMS内部的一组系统表，记录了数据库中所有定义信息：关系模式、视图、索引、完整性约束、各类用户对数据库的操作权限、统计信息等。

RDBMS执行SQL的数据定义语句时，实际上就是在更新数据字典表中的相应信息。

### 1. 模式

**定义模式：**

```
CREATE SCHEMA <模式名> AUTHORIZATION <用户名>
```

后面可以跟CREATE TABLE，VIEW，GRANT字句。

定义模式实际上是定义了一个命名空间，在此空间中可以定义该模式包含的数据库对象。

**删除模式：**

```
DROP SCHEMA <模式名> <CASCADE|RESTRICT>
```

CASCADE删除模式中所有对象，RESTRICT只在模式中没有对象（即该模式没有被其他对象引用/依赖）时允许删除。

### 2. 基本表

**定义基本表：**

```
CREATE TABLE <表名>
( <列名1> <数据类型> [<列级完整性约束条件>],
  <列名2> <数据类型> [<列级完整性约束条件>],
  ...,
[<表级完整性约束条件>] );
```

**修改基本表：**

```
ALTER TABLE <表名>
[ ADD [COLUMN] <新列名> <数据类型> [ 完整性约束 ] ]
[ ADD <表级完整性约束>]
[ DROP [COLUMN] <列名> [CASCADE|RESTRICT] ]
[ DROP CONSTRAINT <完整性约束名> [RESTRICT|CASCADE] ]
[ ALTER COLUMN <列名> <数据类型> ] ;
```

后五行分别为添加列，添加表级约束，删除列，删除列约束，修改原有列的名字和数据类型。

**删除基本表：**

```
DROP TABLE <表名> [RESTRICT|CASCADE];
```

表所属的模式：

1. 显式给出模式名：CREATE TABLE "模式名".表名(...);
2. 创建模式语句中同时创建表
3. 设置所属的模式（SET search_path TO "模式名",PUBLIC），然后再定义基本表
4. 默认根据搜索路径（SHOW search_path）来确定对象所属的模式

### 3. 索引

索引由数据库管理员建立，由RDBMS自动维护和使用。

目的：加快查询速度

方式：顺序、B+树（动态平衡）、散列（查找快速）、位图

**建立索引：**

```
CREATE [UNIQUE] [CLUSTER] INDEX <索引名> ON <表名>
( <列名1> [<次序>],
  <列名2> [<次序>],
  …
);
```

次序：ASC（升序，默认），DESC（降序）。

UNIQUE：每一个索引值只对应唯一的数据记录

CLUSTER：聚簇索引

**修改索引：**

```
ALTER INDEX <旧索引名> RENAME TO <新索引名>;
```

**删除索引：**

```
DROP INDEX <索引名>;
```



### 附录：完整性约束条件

（涉及多个属性列时使用表级完整性约束条件）

（多个约束条件之间不需要逗号分隔）

PRIMARY KEY：主码

FOREIGN KEY & REFERENCES：外码&被参照表和被参照列

UNIQUE：取唯一值

NOT NULL：不允许空值

CHECK：满足一个条件表达式

### 附录：数据类型

用于实现“域”的概念，根据取值范围和所需运算来选择类型。

| 数据类型                        | 含义                                                         |
| ------------------------------- | ------------------------------------------------------------ |
| CHAR(n), CHARACTER(n)           | 长度为n的定长字符串                                          |
| VARCHAR(n), CHARACTERVARYING(n) | 最大长度为n的变长字符串                                      |
| CLOB                            | 字符串大对象                                                 |
| BLOB                            | 二进制大对象                                                 |
| INT, INTEGER                    | 长整数（4字节）                                              |
| SMALLINT                        | 短整数（2字节）                                              |
| BIGINT                          | 大整数（8字节）                                              |
| NUMERIC(p, d)                   | 定点数，由p位数字（不包括符号、小数点）组成，小数后面有d位数字 |
| DECIMAL(p, d), DEC(p, d)        | 同NUMERIC                                                    |
| REAL                            | 取决于机器精度的单精度浮点数                                 |
| DOUBLE PRECISION                | 取决于机器精度的双精度浮点数                                 |
| FLOAT(n)                        | 可选精度的浮点数，精度至少为n位数字                          |
| BOOLEAN                         | 逻辑布尔量                                                   |
| DATE                            | 日期，包含年、月、日，格式为YYYY-MM-DD                       |
| TIME                            | 时间，包含一日的时、分、秒，格式为HH:MM:SS                   |
| TIMESTAMP                       | 时间戳类型                                                   |
| INTERVAL                        | 时间间隔类型                                                 |



## 二、数据查询

```
SELECT [ALL|DISTINCT] <列表达式1>[<别名>], … 
FROM <表名或视图名1>[<别名>], … 
[ WHERE <条件表达式> ]
[ ORDER BY <列名1> [ ASC|DESC ] ];
[ GROUP BY <列名2> [ HAVING <条件表达式> ] ]
```

- SELECT-FORM：从指定的基本表或视图中查找指定的属性列
  - DISTINCT表示取消重复的行，默认为ALL
  - 目标列表达式：即指定查询结果表中需要出现的属性列，查询所有列时可用*代替；可以是表达式；
  - 别名：用来改变查询结果的列标题
- WHERE子句：指定查询条件（行操作，对每个元组进行判断）
- ORDER BY子句：对查询结果按指定列值的升序或降序排序
- GROUP BY子句：对查询结果按指定列的值分组，该属性列值相等的元组为一个组。通常会在每组中作用聚集函数。
- HAVING短语：只有满足指定条件的组才予以输出

### 常用查询条件

| 查询条件 | 谓词                                            |
| -------- | ----------------------------------------------- |
| 比较     | =, >, <, >=, <=, !=, <>, !>, !<; NOT+比较运算符 |
| 范围     | BETWEEN ... AND ..., NOT BETWEEN ... AND ...    |
| 集合     | IN (elem1,elem2,...), NOT IN ...                |
| 字符匹配 | LIKE ..., NOT LIKE ...（通配符%和_）            |
| 空值     | IS NULL, IS NOT NULL                            |
| 多重条件 | AND, OR, NOT （AND优于OR，可用括号              |

### 聚集函数

使用GROUP BY将查询结果按某一属性进行分组（如相同名字的聚为一组），然后对组内所有元素使用聚集函数。

可用于SELECT子句中，若要将聚集函数用于WHERE筛选，必须将表达式写在HAVING子句中。

如果未对查询结果分组，聚集函数将作用于整个查询结果；对查询结果根据某一属性分组（GROUP BY）后，该属性列值相等的元组作为一个组，HAVING短语中的聚集函数将分别作用于每个组 。

统计一列中值的个数：COUNT( [DISTINCT|<u>ALL</u>] <列名>)

求和：SUM( [DISTINCT|<u>ALL</u>] <列名>)

求平均值：AVG( [DISTINCT|<u>ALL</u>] <列名>)

最值：MAX/MIN( [DISTINCT|<u>ALL</u>] <列名>)

### 连接查询

当查询结果来自于多个表时，会将两个表中的元组进行连接。通过WHERE指定需要满足的连接条件，最常见的是等值连接，直接使用=连接两个列属性。

自身连接：要给FROM的表名起两个别名，作为SELECT、WHERE中属性列的前缀。

左外连接：FROM <表名1> LEFT OUT JOIN <表名2> ON (<连接条件>);

### 嵌套查询

一个SELECT-FROM-WHERE语句称为一个查询块，一个查询块可以嵌套在WHERE或HAVING中。

允许多重嵌套，但内层查询不能使用ORDER BY语句。

如：WHERE <列名> IN (<一个查询块>);

- ANY/ALL(查询块)：用在比较运算符的右侧，表示“存在一个”/“所有”，如WHERE 列名 > ALL(查询块);表示查询“大于查询结果中的所有值”的元组。
- [NOT] EXISTS(查询块)：查询块非空时返回TRUE，语义为“目标存在于某集合中”。
- 【下面两个不太懂，等我学完离散再说】
- 实现全称量词（for all）：... WHERE NOT EXISTS(... WHERE NOT EXISTS(...))

$$
(\forall\  x)\  P\equiv \urcorner \ (\ \exist\  x \ (\urcorner P))
$$

- 实现逻辑蕴含（implication）：

$$
p \to q \equiv \urcorner\ p\or q
$$

### 集合操作

将查询结果作为集合，各行作为集合中元素，进行并/交/差。参加集合操作的查询结果的列数必须相同，且对应列的数据类型也要相同。

- 并集（UNION / UNION ALL）：“或”，合并查询结果，去掉/保留重复元组
- 交集（INTERSECT）：“且”
- 差集（EXCEPT）

如：WHERE <列名>='...' UNION 查询块;

### 派生表

子查询除了可以出现在WHERE子句中，还可以出现在FROM子句中，作为查询对象。

FROM (查询块) AS <表名 [(列名)] >，将查询结果作为临时的派生表。



## 三、数据更新

### 插入数据

- 插入元组
- 插入子查询结果（多个元组）

```SQL
/*提供的值必须与属性列的个数、类型匹配，没有赋值的属性取空值；
  若不指定属性列，则表示插入完整的元组*/
INSERT INTO 表名[(列名1,列名2,...)] VALUES (常量1,常量2,...);
INSERT INTO 表名[(列名1,列名2,...)] VALUES 子查询块;
```

RDBMS在插入时检查实体完整性、参照完整性、用户定义完整性。

### 修改数据

```sql
/*先根据WHERE筛选出元组，在对这些元组进行修改，若无WHERE则修改全部元组*/
UPDATE <表名> 
SET <列名1>=<表达式1>, <列名2>=<表达式2>, ...
[ WHERE <条件> ]; 
```

RDBMS在修改时检查实体完整性、主码不允许修改、用户定义完整性。

### 删除元素

```sql
/*删除满足WHERE的元组或全部元组，但不删除表的定义*/
DELETE FROM <表名> [ WHERE <条件> ]; 
```



## 四、空值处理

空值就是“不知道”或“不存在”或“无意义”的值。

可能的情况：

- 该属性不应该有值
- 该属性应该有值，但暂时不知道其具体值
- 由于某种原因不便于填写

产生：将某个属性赋值为NULL，或者插入元组时不设置该属性的值。

判断：用 <属性名> IS NULL 或 <属性名> IS NOT NULL。

约束：属性定义中，NOT NULL、UNIQUE、码属性不能取空值。

运算：空值进行算术运算=空值，空值进行比较运算=UNKNOWN（和TRUE、FALSE构成三值逻辑）。



## 五、视图

视图是从多个基本表、视图上导出的虚表，只存放视图的定义而没有对应的数据，其中的数据会随基本表动态变化。

作用：

- 简化用户的操作
- 使用户能以多种角度看待同一数据 
- 对重构数据库提供了一定程度的逻辑独立性 
- 对机密数据提供安全保护
- 适当的利用视图可以更清晰的表达查询

**定义视图**

创建视图的定义

```sql
CREATE VIEW 视图名[(列名1,列名2,...)] --列名可省略
AS <子查询>             --任意的SELECT语句(不是真查询)
[ WITH CHECK OPTION ]; --保证对视图中元组进行插入、修改、删除的操作符合子查询中的WHERE条件
```

删除视图的定义

```sql
/*若视图导出的其他视图，只能用CASCADE删除基视图，删除基本表不会删除视图*/
DROP VIEW <视图名> [CASCADE];
```

**查询视图**

对于用户而言，与查询基本表相同；

对于RDBMS，采用视图消解法（转换为等价的基本表查询、进行有效性检查、执行修正后的查询）。【局限：WHERE中使用聚集函数时】

**更新视图**

与更新基本表的语法相同，转换为对基本表的更新。

对视图的更新是有限的。

限制：一些视图不可更新，因为对这些视图的更新不能唯一地有意义地转换成对相应基本表的更新。如：不能更新基本表中的含有聚集函数的属性列。

- 若视图是由两个以上基本表导出的，则此视图不允许更新。
- 若视图的字段来自字段表达式或常数，则不允许对此视图执行INSERT和UPDATE操作，但允许执行DELETE操作。
- 若视图的字段来自聚集函数，则此视图不允许更新。
- 若视图定义中含有GROUP BY子句，则此视图不允许更新。
- 若视图定义中含有DISTINCT短语，则此视图不允许更新。
- 若视图定义中有嵌套查询，并且内层查询的FROM子句中涉及的表也是导出该视图的基本表，则此视图不允许更新。



## 六、安全性控制

安全标准：TCSEC/TDI（美国，1985/1991）→CC V2.1（国际标准ISO15408，1999）

实现数据库系统安全性的技术和方法：

- 用户身份鉴别
- 存取控制技术：自主存取控制和强制存取控制
- 视图技术
- 审计技术
- 数据加密存储和加密传输
- 其他：推理控制、隐蔽信道、隐私保护

存取控制方法：

- 自主存取控制（Discretionary Access Control）
  - C2级
  - 用户对不同的数据对象有不同的存取权限
  - 不同的用户对同一对象也有不同的权限
  - 用户还可将其拥有的存取权限转授给其他用户
- 强制存取控制（Mandatory Access Control）
  - B1级
  - 每一个数据对象被标以一定的密级
  - 每一个用户也被授予某一个级别的许可证
  - 对于任意一个对象，只有具有合法许可证的用户才可以存取

### 自主存取控制（DAC）

定义存取权限（授权）：定义<u>用户</u>可以对<u>数据库对象</u>（schema、table、view、index）进行哪些类型的<u>操作</u>（SELECT、INSERT、UPDATE、DELETE、REFERENCES、ALL PRIVILIGES）。

授权

```sql
GRANT <操作名1>,<操作名2>,... --ALL PRIVILIGES表示所有操作（可以用形如UPDATE(列名)表示授权对某属性列的操作）
ON <对象类型> <对象名>,...
TO <用户名>,...              --PUBLIC表示全体用户
[ WITH GRANT OPTION ];      --该选项允许此用户继续把自己的权限再授权给其他用户
```

收回

```sql
REVOKE <操作名1>,...
ON <对象类型> <对象名>,...
FROM <用户名>,...            --从被授权者收回权限
[CASCADE|RESTRICT];         --CASCADE级联回收权限，即还回收此用户授权过的权限
```

创建用户

```sql
/*非SQL标准，取决于各RDBMS实现，只有超级用户才可以创建用户*/
CREATE USER <用户名> 
[WITH] [DBA|RESOURCE|CONNECT] 
/*CONNECT为默认用户权限，只允许登录数据库进行查询；
  RESOURCE用户可以创建基本表、视图；
  DBA为超级用户，可以创建新用户、创建模式、存取数据库对象等所有权限。*/
```

角色

```sql
CREATE ROLE <角色名>   --角色是一组操作权限的集合
/*给角色授权*/
GRANT <操作名>,...
ON <对象类型> <对象名>,...
TO <角色名>,...;
/*回收角色的权限*/
REVOKE <操作名>,...
ON <对象类型> <对象名>,...
FROM <角色名>,...;

/*将角色授予用户*/
GRANT <角色名>,...
TO <用户/角色名>,...
[ WITH ADMIN OPTION ]; --允许此用户继续把自己的角色再授予其他用户
/*回收用户的角色*/
REVOKE <角色名>,...
FROM <用户/角色>,...
```

### 强制存取控制（MAC）

自主存取控制可能存在数据的“无意泄露”，因为只控制了对数据的存取权限，而数据本身无安全性标记。

将DBMS中的全部实体分为**主体**（用户、用户进程）、**客体**（文件、表、索引、视图）两大类。主体、客体的敏感度标记分别称为**许可级别**、**密级**。当主体的许可级别≥客体的密级时允许**读**，许可级别≤密级时允许**写**客体（即高级用户读低级数据，低级用户写高级数据）。

检查过程：SQL语法分析&语义检查→DAC检查→MAC检查→继续语义检查

### 审计

启用一个专用的审计日志（Audit Log），将用户对数据库的所有操作记录在上面。

审计员利用审计日志，监控数据库中的各种行为，找出非法存取数据的人、时间和内容。

C2以上安全级别的DBMS必须具有审计功能。



## 七、完整性

防止数据库中存在不符合语义的、不正确的数据。

### 完整性约束

- 实体完整性定义（PRIMARY KEY）
- 参照完整性定义（FOREIGN KEY-REFFERENCES）
- 用户定义的完整性（NOT NULL、UNIQUE、CHECK）

主码：非空且唯一。

外码：联系外码和另一被参照表的主码；显式声明违约处理；外码列应定义是否允许空值。

```sql
CREATE TABLE SC
(Sno CHAR(9) NOT NULL,     --列级约束条件
 Cno CHAR(4) NOT NULL,
 Sex CHAR(2) CHECK(Sex IN ('男','女')),
 Grade SAMLLINT CHECK(Grade >= 0 AND Grade <= 100),
 --表级约束
 PRIMARY KEY (Sno,Cno),                     --属性组(Sno,Cno)为主码
 FOREIGN KEY (Sno) REFFERENCES Student(Sno) --外码Sno参照Student(Sno)
  ON DELETE CASCADE        ---表Student删除时，级联删除SC中相应元组
  ON UPDATE CASCADE,       ---表Student更新时，级联更新SC中相应元组
 FOREIGN KEY (Cno) REFFERENCES Course(Cno)  --外码Cno参照Course(Cno)
  ON DELETE NO ACTION      ---删除表Course中元组导致SC不一致时拒绝删除
  ON UPDATE CASCADE,
 CHECK(Grade>=60 OR Cno LIKE 'MATH')        --元组的约束？只允许MATH课不及格
);
```

给约束条件命名

```sql
/*可以将上面的列级、表级约束条件定义成名字*/
CREATE TABLE SC
(Sno CHAR(9),
 CONSTRAINT C1 NOT NULL, --约束条件C1
 Cno CHAR(4),
 CONSTRAINT C2 NOT NULL, --约束条件C2
 Sex CHAR(2),
 CONSTRAINT C3 CHECK(Sex IN ('男','女')),  --约束条件C3
 CONSTRAINT SCKey PRIMARY KEY(Sno,Cno)    --主码约束条件SCKey
);
/*修改完整性限制*/
ALTER TABLE SC      --删除旧约束条件C3
DROP CONSTRAINT C3;    
ALTER TABLE SC      --添加新约束条件C3
ADD CONSTRAINT C3 CHECK(Sex IN ('男'));
```

### 断言

更一般性的约束，可以定义涉及<u>多个表</u>的、或涉及<u>聚集操作</u>的比较复杂的完整性约束。

任何对断言中所涉及的关系的操作都会触发RDBMS对断言的检查，任何使断言不为真值的操作都会被拒绝执行。

**创建断言**

```sql
CREATE ASSERTION <断言名> <CHECK子句>;
/*限制每一门课程最多60名学生选修*/
CREATE ASSERTION ASSE1
 CHECK(60>=ALL(SELECT count(*) --涉及了聚集函数
               FROM SC
               GROUP BY Cno));
```

**删除断言**

```sql
DROP ASSERTION <断言名>;
```

### 触发器

定义在关系表上的一类由<u>事件驱动</u>的特殊过程。触发器保存在数据库服务器中，用户对表的增删改操作都会由服务器自动激活相应的触发器，具有更精细和强大的数据控制能力。

**定义触发器**

```sql
/*触发器定义在模式内，定义在其中的基本表上*/
CREATE TRIGGER <触发器名>
  {BEFORE|AFTER} <触发事件> ON <表名>  --触发事件为INSERT、DELETE、UPDATE
REFERENCING
  NEW ROW AS <变量1>,  --将新元组和旧元组取别名，用于下面的WHEN语句中
  OLD ROW AS <变量2>,
  NEW TABLE AS <变量3>
FOR EACH {ROW|STATEMENT}
--FOR EACH ROW表示对每次行操作都激活触发器，STATEMENT则是对每次语句的执行激活触发器
  [ WHEN <触发条件> ] <触发动作体> 
--激活触发器后，触发条件为真才执行某些操作
--只有行级触发器才能在触发动作体中使用NEW和OLD
--触发动作体中可以用BEGIN-END来写一段小操作
```

**删除触发器**

```sql
DROP TRIGGER <触发器名> ON <表名>;
```

