# 基本操作

登录

```bash
mysql -u root -p
```



查看数据库

```mysql
show databases;
```

创建数据库

```mysql
create database DB_NAME;
```



选择数据库

```mysql
use DB_NAME
```

（也可以在shell中直接选择数据库：`mysql -u root -p DB_NAME`）

查看当前选中的数据库

```mysql
select database();
```



查看数据表

```mysql
show tables;
```

创建表

```mysql
CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20), species VARCHAR(20), sex CHAR(1), birth DATE, death DATE);
```

查看表信息

```mysql
DESCRIBE TABLE_NAME;
DESC TABLE_NAME;
```

插入记录

```mysql
INSERT INTO test (name,avatar,regsiter_time,openid) value ('a','b','1997-08-24','1253');
```







退出

```mysql
exit;  
```



创建数据表

```sql
CREATE TABLE table_name (col1,col2,...,constrain)
```

添加数据

```sql
INSERT INTO table_name
VALUES (..., ..., ...);
```



赋予访问权限：

```mysql
GRANT ALL ON menagerie.* TO 'your_mysql_name'@'your_client_host';
-- menagerie.*表示允许访问menagerie数据库的所有表，name指定用户名，host指定ip
```









## 从文件中导入数据

对于表

```sql
CREATE TABLE pet (
    name VARCHAR(20), 
    owner VARCHAR(20), 
    species VARCHAR(20), 
    sex CHAR(1), 
    birth DATE, 
    death DATE
);
```

一个`pet.txt`文件中一行包含一条记录（用tab分隔，空值用`\N`表示）：

```
Whistler	Gwen	bird	\N	1997-12-09	\N
```

mysql中导入数据：

```mysql
LOAD DATA LOCAL INFILE '/path/pet.txt' INTO TABLE pet;
```

注：windows文件需要在语句末尾加上`LINES TERMINATED BY '\r\n';`



## 开启和关闭MySQL Server

查看状态：

```
sudo service mysql status
```

开启服务：

```
sudo service mysql start
```

关闭服务：

```
sudo service mysql stop
```







## 开启远程连接

登录

```
mysql -u root -p
```

选择数据库

```mysql
use mysql;
select host from user where user='root';
```

user表中的host属性指定了允许用户登录所使用的IP，修改：

```mysql
update user set host = '192.168.40.%' where user ='root';

/* 另一种方法，*.*表示对所有库的所有表，这样做会在该表中添加另一条记录 */
grant all privileges on *.* to root@115.208.110.211 identified by '密码';
```

为使修改生效，执行：

```mysql
flush privileges;
```

随后可用navicat进行连接。

### 修改mysqld监听的ip配置

有时到这里还是不行，执行：

```
netstat -antp | grep LISTEN
```

会发现mysqld只监听了本地端口，这需要修改my.cnf配置文件，过程如下：

1. 寻找my.cnf文件，命令行输入：

   ```
   mysqld --help --verbose | less
   ```

   输出中看到，my.cnf应该在这些位置：

   ```
   Default options are read from the following files in the given order:
   /etc/my.cnf /etc/mysql/my.cnf ~/.my.cnf
   ```

2. 我是在`/etc/mysql/my.cnf`找到的，打开后发现里面有

   ```
   !includedir /etc/mysql/conf.d/
   !includedir /etc/mysql/mysql.conf.d/
   ```

   在`/etc/mysql/mysql.conf.d/mysql.cnf`里，找到了：

   ```
   # By default we only accept connections from localhost
   bind-address	= 127.0.0.1
   ```

   将`bind-address	= 127.0.0.1`用`#`注释掉即可。

3. 再次执行：

   ```
   netstat -antp | grep LISTEN
   ```

   可以看到此时mysqld已经监听了所有ip。



