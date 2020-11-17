[effective-modern-cpp](https://downdemo.gitbook.io/effective-modern-cpp/)



- [ ] unique_ptr
- [ ] 命名空间
- [ ] lambda
- [ ] thread
- [ ] RAII



虚函数，虚函数表？

四种类型转换？

红黑树、跳表、hash表？



`typedef typename Base::pointer pointer`？

typedef int T[100]：声明类型int[100]的别名为T

using xxx = typename aaa：声明类型aaa的别名xxx



运算符重载

```c++
T& operator++()		//前置++i
T operator++(int)	//后置i++，一般会调用前置++
T* operator->() const	{ return &(operator*()); }	//->返回一个指针，然后编译器会再次对这个内置指针执行一次->
```





拷贝构造：参数类型必须为&或const &，绝对不能为自己的类类型的值传递（循环调用）。



sizeof(数组)：整个数组的大小

sizeof(指针)：指针的大小4/8 byte（32/64位）（而不是数组大小）

当数组作为函数的参数传递后，数组自动退化为指针！



随机数

```c++
#include<time.h>
srand(time(0)); //随机数种子，只执行一次
int r = rand()%100; //i = [0,99]
double d = rand() / double(RAND_MAX); //取得0～1之间的浮点数
```



new

```c++
vector* vec = new vector();		
char* str = new char;
char* str = new char[len+1];	//长度别忘了\0
```



传入可变数量的实参

```c++
// 可变数量的实参，类型必须相同
// 注意：il中的对象永远是常量值，不像vector
void error_msg(initializer_list<string> il) {
	for (auto beg = il.begin(); beg != il.end(); ++beg) {
		cout << *beg << "";
	}
}

// 使用
error_msg({"this", "is", "arguement"});
```

默认实参

```c++
int func(int a, int b = 0);	//默认实参必须在最右边
```





cstring操作

```c++
const char *	//cstr的类型

ch != '\0'		//判结尾
strlen(cstr)	//\0不计入长度
strcpy
Sprintf
```

##### string

https://zh.cppreference.com/w/cpp/string/basic_string

```c++
s.data();		//返回cstr，包含\n
s.substr(index, len);	//返回从下标index开始的len个字符：[index, index+len)，如果越界则只到字符串末尾
s.erase(index, len);	//范围删除
s.erase(s.begin() + index);//单个删除
```



##### 字符串转数字

```
// 简单方法
string str = to_string(i);	//<sstream>
int x = stoi(str);			//<string>
char ch = 1 + '0';			//只适合个位数

// 流：字符串 <-> 数字 （可以是浮点数）<sstream> 
stringstream ss;
string str;
double x = 3.14;
ss << x;
ss >> str;
```



##### stringstream

<sstream>

```c++
stringstream ss(data_str);
string str;
while(ss >> str) {
	cout << str << " ";
}

// 以','作为分隔符读入
while(getline(ss, str, ',')) {
	cout << str << " ";
}
```





##### 迭代器

 <iterator>

```
vector<int> v{ 3, 1, 4 };
distance(v.begin(), v.end()); //3
```



##### pair

```c++
int i = 1;
string str = "1";
pair<int,string> p = make_pair(i, str);
```





##### vector

```c++
vector<int> vec(3,100);	//vector中放入3个100
vector<int> vec({1, 2});	//列表初始化
vector<int> vec(begin(arr), end(arr));	//使用内置数组来初始化
vec.push_back(elem)
vec.pop_back()

vec.size()
vec.empty()
    
int a = vec.front()
int b = vec.back()	//最后一个元素的引用
int* arr = vec.data()	//返回底层数组的指针

// insert 插入示例
auto iter = vec.begin();
vec.insert(iter, 200);	//在iter之前插入一个元素200
vec.insert(iter+2, vec2.begin(), vec2.end());	//iter+2之前插入vec2所有元素

// 删除
int del = vec[index];
vec.erase(vec.begin() + index);   //移除下标为index的元素

// 翻转 <algorithm>
std::reverse(vec.begin(), vec.end());
```



```c++
// 自定义比较函数，对vec中元素按 a1 < a2 < ... 排序
sort(vec.begin(), vec.end(), [](int a, int b){return a < b;})
```



##### 双端队列

允许在其首尾两端快速插入及删除。

```c++
std::deque<int> d = {7, 5, 16, 8};

// 从 deque 的首尾添加整数
d.push_front(13);
d.pop_front();

d.push_back(25);
d.pop_back();
```

- deque 的元素不是相接存储的：典型实现用单独分配的固定大小数组的序列，外加额外的登记，这表示下标访问必须进行二次指针解引用，与之相比 vector 的下标访问只进行一次。
- 扩张 deque 比扩张 vector 更优，因为它不涉及到复制既存元素到新内存位置。
- deque 典型地拥有较大的最小内存开销；只保有一个元素的 deque 必须分配其整个内部数组





##### unordered_map【C++11】

唯一键值对，元素（元素是pair）通过哈希放入对应的桶

```c++
unordered_map<char,int> m = {{'a',1},{'b',2}};

//插入新值，并自增
++m['c'];	//以0初始化value，结果m['c'] == 1

// 遍历pair（key和value）
for(const auto& p : m) {
    std::cout << "Key:[" << p.first << "] Value:[" << p.second << "]\n";
}

// 查找key，返回迭代器。
// - 找不到时，返回尾后迭代器end()
// - 找到时，iter->first、iter->second 分别为 key 和 value
auto iter = m.find('a');
if (iter != m.end())
	cout << iter->first << " " << iter->second << '\n';
//if (m.find('a') != m.end())

// 删除
m.erase(iter);	//删除pair
m.erase(key);	//删除key
```



##### unordered_set【C++11】

```c++
unordered_set<int> s;
// 插入key
s.insert(1);
// 删除
s.erase(iter);	//删除iter
s.erase(key);	//删除key

// 查找key
auto iter = s.find(1);
if (iter != s.end())	cout<< *iter << endl;
```



##### 栈

```c++
stack<int> stk;
stk.push(item);		//入栈
int item = stk.top();	stk.pop();	//出栈
```



##### 队列

```c++
// 层序遍历二叉树示例
queue<int> q;
q.push(root);	//入队
while(!q.empty()) {
    int size = q.size();	// 确保只访问一层的结点
    for (int i = 0; i < size; ++i) {
        // 访问队首，队首出队
        TreeNode* pnode = q.front(); q.pop();	
        // 左右孩子入队
        if(pnode->left != nullptr) q.push(pnode->left);
        if(pnode->right != nullptr) q.push(pnode->right);
    }
}

int i = q.back();
```



##### 优先队列

<queue>

```c++
// 最大堆，弹出最大值，但指定的是”小于“函数
auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
// 注意!!：如果要用自定义的比较，必须用三个模板参数，第二个参数可以为vector<T>
std::priority_queue<int, std::vector<int>, decltype(cmp)> q(cmp);

q.size() < k;

q.push(3);
int a = q.top();
q.pop();
```





##### 内存空间

Static

1. 生存期：局部变量vs静态变量。静态变量，分配在静态存储区，在数据段中。第一次访问时创建，函数退出之后，变量值不变。
2. 全局变量vs全局静态变量：作用域。全局的静态变量、静态函数只能在本文件中使用。而非静态全局变量的作用域是整个源程序。