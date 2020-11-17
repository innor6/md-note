# CRUD

创建、查询、更新成功后，&user 对象都会被更新。

- 创建记录

  ```go
  user := User{Name: "Jinzhu", Age: 18, Birthday: time.Now()}
  db.Create(&user)
  fmt.Println(user.ID)	//Create成功后，user对象被更新，如ID
  ```

  - 字段为零值（`0`、`''`、`false`）时，使用默认值代替（如要避免，则用指针或实现 Scanner/Valuer 接口，如：Age  sql.NullInt64 `gorm:"default:18"`）
  
- 查询

  https://gorm.io/zh_CN/docs/query.html

  ```go
  // 第一条(按主键顺序)
  db.First(&user)
  //// SELECT * FROM users ORDER BY id LIMIT 1;
  
  // - 指定主键(主键必须为整型)
  db.First(&user, 10)
  //// SELECT * FROM users WHERE id = 10;
  
  // - 所有记录
  db.Find(&users)
  //// SELECT * FROM users;
  
  // - 外键(写结构体名)
  db.Preload("User").(...).Find(&orders)
  
  // 内联where条件
  db.Find(&users, User{Age: 20})
  //// SELECT * FROM users WHERE age = 20;
  ```

  - 使用结构体作为where条件时，为零值（`0`、`''`、`false`）的字段不会被用于查询条件。
  - 查询到的结果，会自动填充到原来的`&user`中的空字段

  **WHERE条件**：

  ```go
  // - 表达式
  db.Where("name = ?", "jinzhu").First(&user)
  
  // - 结构体
  db.Where(&User{Name: "jinzhu", Age: 20}).First(&user)
  //// SELECT * FROM users WHERE name = "jinzhu" AND age = 20 ORDER BY id LIMIT 1;
  
  // 所有匹配的
  db.Where("name = ?", "jinzhu").Find(&users)
  //// SELECT * FROM users WHERE name = 'jinzhu';
  
  // AND
  db.Where("name = ? AND age >= ?", "jinzhu", "22").Find(&users)
  
  // IN
  db.Where("name IN (?)", []string{"jinzhu", "jinzhu 2"}).Find(&users)
  
  // LIKE
  db.Where("name LIKE ?", "%jin%").Find(&users)
  
  // Time
  db.Where("updated_at > ?", lastWeek).Find(&users)
  
  // NOT
  db.Not("name = ?", "jinzhu").First(&user)
  
  // OR
  db.Where("name = ?", "jinzhu").Or(User{Name: "jinzhu 2"}).Find(&users)
  ```

  指定字段：

  ```go
  db.Select("name, age").Find(&users)
  //// SELECT name, age FROM users;
  ```

  排序：

  ```go
  db.Order("age desc, name").Find(&users)
  //// SELECT * FROM users ORDER BY age desc, name;
  ```

  数量：

  ```go
  db.Limit(3).Find(&users)
  //// SELECT * FROM users LIMIT 3;
  ```

  偏移：

  ```go
  db.Offset(3).Find(&users)
  //// SELECT * FROM users OFFSET 3;
  ```

  计数：（Count必须是最后一个操作）

  ```go
  db.Where("name = ?", "jinzhu").Or("name = ?", "jinzhu 2").Find(&users).Count(&count)
  //// SELECT * from USERS WHERE name = 'jinzhu' OR name = 'jinzhu 2'; (users)
  //// SELECT count(*) FROM users WHERE name = 'jinzhu' OR name = 'jinzhu 2'; (count)		从users中计数，存到变量count
  
  db.Model(&User{}).Where("name = ?", "jinzhu").Count(&count)
  //// SELECT count(*) FROM users WHERE name = 'jinzhu'; (count)
  ```

- 更新

  - 使用 `Model(&user)` 相当于查找主键：id=111
  - 只更新有变化的属性
  - 使用 struct 更新属性时，只更非零值的字段

  ```go
  //下面的调用链中，Model(&user) 表示查找主键：id=111
  
  // 更新单个属性
  db.Model(&user).Update("name", "hello")
  //// UPDATE users SET name='hello', updated_at='2013-11-17 21:34:10' WHERE id=111;
  
  // 使用 struct 更新多个属性，只会更新非零值的字段
  db.Model(&user).Updates(User{Name: "hello", Age: 18})
  //// UPDATE users SET name='hello', age=18, updated_at = '2013-11-17 21:34:10' WHERE id = 111;
  ```

- 删除

  ```go
  db.Delete(&email)
  // 必须确保id字段非空，否则删除全部
  //// DELETE from emails where id=10;
  ```

  批量删除

  ```
  db.Where("age = ?", 20).Delete(&User{})
  db.Where("email LIKE ?", "%jinzhu%").Delete(Email{})
  //// DELETE from emails where email LIKE "%jinzhu%";
  ```

  软删除：如果model存在DeletedAt字段，则不会真的删除，而是更新该字段。





### 自动迁移

```
`db.AutoMigrate(&User{})`
```



### 错误处理

使用 `err := First(&user).Error`

```go
if err := db.Where("name = ?", "jinzhu").First(&user).Error; err != nil {
  // error 处理...
}
```

“未找到记录”错误：

```go
if db.Model(&user).Related(&credit_card).RecordNotFound() {
  // 未找到记录
}

if err := db.Where("name = ?", "jinzhu").First(&user).Error; gorm.IsRecordNotFoundError(err) {
  // 未找到记录
}
```





### 链式操作

在调用立即执行方法前不会生成 Query 语句。

链式使用多个立即执行方法时，后一个立即执行方法会复用前一个 立即执行方法的条件：

```go
// Find 和 Count 都会使用 Where("name LIKE ?", "jinzhu%")
// 但是 Count 是从 users 中进行查询
db.Where("name LIKE ?", "jinzhu%").Find(&users, "id IN (?)", []int{1, 2, 3}).Count(&count)
```





规定：

数据库中列名不区分大小写。

默认主键：ID字段

默认表名：shema对象的复数形式，如user的表名为users

默认列名：字段名称+下划线分割

```
CreatedAt time.Time // CreatedAt字段 默认生成的列名是 `created_at`
```

默认时间追踪：CreatedAt、UpdatedAt、DeletedAt字段



模型定义：

- 默认值：`gorm:"default:'galeone'"`



外键：

一对一：包含一个模型User和外码UserID，

```go
// `Profile` 属于 `User`， 外键是`UserID` 
type Profile struct {
  gorm.Model
  UserID int
  User   User
  Name   string
}
```

