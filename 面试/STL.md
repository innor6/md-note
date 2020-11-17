# STL

range for

```c++
for ( int i : { 2, 3, 5, 7, 9 } )
for ( auto elem : vec )
for ( auto& elem : vec )  //容器内元素可以修改
```

向缓冲区写入字符串

```c++
snprintf(buf, bufsize, “%d”, 42)
```

vector.push_back()可能引起内存分配，要try-catch：

```c++
catch (exception& e ) {
	cout<< e.what() << endl;
	abort();
}
```



### 容器

分类：

顺序容器：array、vector、deque、list、forward_list

关联容器：set/multiset、map/multimap、unordered...

注：

1. 常用函数：size(), empty(), data(), front(), back(), push_back(), pop_back(), capacity()
2. 实现：
   - vector：顺序表
   - deque：map（其实是指针数组），元素为指向buffer块的指针
   - list：双向环状链表
   - forward_list：单链表
   - set/map/multi：红黑树
   - unordered_xxx：hash，每个桶含一个链表
3. 增长：vector2倍增长，deque每次增长一个buffer。
4. stack和queue底层都是deque，插入删除用push、pop，不能用迭代器。
5. set、map添加元素用insert，map插入的是pair<T,T>(a,b)（访问pair：pair.first、pair.second）。
6. map可用map[key]进行插入，multimap不可用[]。
7. forward-list单链表只能push_front，且无法size和back



iterator必须要包含的五个关联属性（类型）：

- iterator_category
- difference_type
- value_type
- pointer
- reference

算法通过 `iterator_traits<typename I>` 来间接提取迭代器I的上面这些属性；

但当迭代器是内置指针时，没有这些属性，因此traits通过偏特化模板： `iterator_traits<T*>` 和 `iterator_traits<const T*>` 来为内置指针生成上述属性。



### 源码分析

**list**

1. 成员：只含一个空白结点，作为end结点（符合前闭后开），用以分隔头尾
2. 结点成员：包含pre、next、data

**vector**

1. 成员：start、finish、end_of_storage三个迭代器。

**array**

1. 成员：数组的头指针

**deque**

1. 构成：一个map（只是叫map，实现实际上是数组？），包含许多结点（`T**`），每个结点指向一个buffer（`T*`），buffer中存放着具体的元素。
2. 成员：
   1. 指向map的指针、map_size
   2. 两个迭代器：start、finish，即start的cur指向第一个buffer中第一个有效元素，finish的cur指向下一个可以存放元素的位置（前闭后开）
3. iterator的成员：
   1. cur指针：指向buffer中的当前元素
   2. firts、last指针：指向这一buffer区间的边界（前闭后开）
   3. node（`T**`）：指向该buffer对应在map中的结点

**stack 和 queue**

1. 底层是deque，也可以选择list作为底层结构
2. stack还可以选择vector作为底层结构，queue不行，因为vector不能pop_front。
3. 不允许遍历，即不提供iterator

**rb_tree**：map、set、multimap、multiset

**hashtable**：unordered

1. 成员：vector of nodes（每个node引出一个链表）



hashtable

将一个对象，映射为一个数字，放入顺序表中的对应位置。

-> 表长度较小时，易发生碰撞：seprate chainning，将顺序表中的元素改为链表（称为桶bucket），数据放入桶中。

-> 链表的搜寻速度是线性的，效率变低：当元素个数超过桶个数时，扩容，桶数*2，桶数量一般选择素数



算法：

lower_bound(beg, end, val)

二分查找，返回迭代器，指向第一个等于目标值的元素，如果不存在等于目标值，则指向第一个大于目标值的元素。





