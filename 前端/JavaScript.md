# js

[重新介绍JavaScript](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/A_re-introduction_to_JavaScript)

[继承与原型链](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Inheritance_and_the_prototype_chain)



### 神奇语法



对象

```js
// 这里插入的是一个 {text: text} 的元素
// （在传参的时候也可以这样）
const newTodos = [...todos, {text}]
newTodos[idx].isCompleted = true // 没有 isCompleted 属性则自动添加
```

变量

```js
// 此时todos变量还没声明就可以使用了
const saveTodos = () => {
	window.localStorage.setItem(todoKey, JSON.stringify(todos)
}

// 声明todos
const [todos, setTodos] = useState(loadTodos())
```

可能是动态语言的能力？但是声明之前访问todos会报错。





#### array

[更多方法](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/Array)

```js
// 拷贝数组
arr2 = [...arr1]
arr.slice()
arr.slice(beg, end) // [beg, end)

// 删除元素
arr.splice(idx, 1)	
arr.splice(idx, n, elem1, elem2, ...) // 从idx开始删除n个元素，再插入元素

// 添加元素到末尾
arr2 = [...arr1, newElem]
arr.concat(elem1, elem2, ...)

// 映射（返回一个新列表，将每个元素映射为新的值）
arr.map((elem, index) => {return xxx})

// 用分隔符拼接成字符串
arr.join(sep)

// 返回第一个满足条件的元素，如不存在返回undefined
arr.find(elem => elem.id > 10)?.name || '不存在'

// 接收一个函数，对每个元素执行“累计操作”。
// reducer可以接收四个参数：累计器、当前值、当前idx、源数组src
reducer = (accumulator, currentValue) => accumulator + currentValue
arr.reduce(reducer) // 可选第二个参数，作为accumulator的初始值
```





#### for

```js
for (let value of array) {
  // do something with value
}

for (let property in object) {
  // do something with object property
  // 注意：如果in用于数组，则遍历的其实是index，要用arr[i]来访问内容
}

// 类似map
["dog", "cat", "hen"].forEach(function(currentValue, index, array) {
  // 操作 currentValue 或者 array[index]
});
```



#### && ||

```js
// 访问某个对象的属性前，事先检测该对象是否为空
var name = o && o.getName();
// 用于缓存值（当错误值无效时）：
var name = cachedName || (cachedName = getName());
```



#### 对象

```js
// 创建
var obj = {
    name: "Carrot",
    details: {
        color: "orange",
        size: 12
    },
    // 使用变量作为key，需用[]转义
    [var1] : value,
    // 如果key里有-，需要用引号包围
    'Content-Type': data ? 'application/json' : '',
    // 'for' 是保留字，使用'_for'代替
    _for: "Max",
}

// 访问（两种都可以用了添加新属性）
obj.details.color; // orange
obj["details"]["size"]; // 12
```

对象其实是原型链继承

```js
function Person(first, last) {
    this.first = first;
    this.last = last;
}
// 给原型添加属性
Person.prototype.fullName = function() {
    return this.first + ' ' + this.last;	//this指向用.或[]调用该方法的对象
}

var s = new Person("Simon", "Willison");
s.fullName(); // "Simon Willison"

// 运行时给原型添加方法
Person.prototype.firstNameCaps = function() {
    return this.first.toUpperCase()
}
s.firstNameCaps(); // SIMON
```

原型链：

1. `Person.prototype` 是一个可以被`Person`的所有实例共享的对象
2. 当试图访问 `Person `某个实例的属性时，有访问对象自身的属性，没有再去原型 `Person.prototype`找属性。
3. 允许在运行时(runtime)修改原型（prototype）中的一些东西，例如给已存在的对象添加额外的方法。



#### 展开语法

```js
// 用数组传多个参数
function myFunction(v, w, x, y, z) { }
var args = [0, 1];
myFunction(-1, ...args, 2, ...[3]);	//等价于myFunction(-1, 0, 1, 2, 3)

// 拼接数组
var parts = ['shoulders', 'knees'];
var lyrics = ['head', ...parts, 'and', 'toes']; 

// 拷贝数组（只拷贝一层）
var arr = [1, 2, 3];
var arr2 = [...arr]; // like arr.slice()

// 浅克隆一个对象（只拷贝第一层）
var obj1 = { foo: 'bar', x: 42 };
var clonedObj = { ...obj1 };

// 拼接对象（如果key重复，后面的覆盖前面的）
var obj2 = { foo: 'baz', y: 13 };
var mergedObj = { ...obj1, ...obj2 };
```



#### 剩余参数

```js
// 将多个参数收集到args数组中
function avg(...args) {
  var sum = 0;
  for (let value of args) {
    sum += value;
  }
  return sum / args.length;
}

avg(2, 3, 4, 5); // 3.5
```



#### switch

```js
// case使用===匹配
switch(action) {
    case 'draw':
        drawIt();
        break;
    case 'eat':
        eatIt();
        break;
    default:
        doNothing();
}
```



#### 内部函数

```js
// 函数内定义函数，减少外部函数的数量，更易维护
function parentFunc() {
  var a = 1;

  function nestedFunc() {
    var b = 4; // parentFunc 无法访问 b
    return a + b;
  }
  return nestedFunc(); // 5
}
```



#### 闭包

```js
function makeAdder(a) {
  return function(b) {
    return a + b;
  }
}
var add5 = makeAdder(5);
var add20 = makeAdder(20);
add5(6); // 5 + 6
add20(7); // 20 + 7
```



#### number

（双精度浮点数）

```js
// str -> number
let num = Number(str) || undefined

parseInt("010", 10); // 10，第二个参数表示十进制
parseFloat("3.14")

// 一元运算符
+ "42";   // 42
+ "010";  // 10
+ "0x10"; // 16

// parseInt和parseFloat会逐个解析字符串中的字符，直到遇上一个无法被解析成数字的字符
// 而+则如果无法完全转换为数字，返回NaN
parseInt("10.2abc")		// 10
parseFloat("10.2abc")	// 10.2
+ "10.2abc"				// NaN

const input = parseFloat(temperature);
if (Number.isNaN(input)) {return '';}

isNaN(Number(value)) == true	//转换为number类型失败
```



#### 字符串

（unicode，UTF-16编码单元，每一个Unicode字符由一个或两个编码单元来表示）

```js
"hello".length; // 5
"hello".charAt(0); // "h"
"hello, world".replace("world", "mars"); // "hello, mars"
"hello".toUpperCase(); // "HELLO"

String(42)	// "42"

// 反点号的字符串里可以嵌入返回string的expr表达式
`You clicked ${count} times`
```



null：空值

undefined：对象声明后未赋值，实际上是一个不允许修改的常量。

boolean：

1. `false`、`0`、空字符串（`""`）、`NaN`、`null` 和 `undefined` 被转换为 `false`
2. 所有其他值被转换为 `true`

变量：

1. `var`：整个函数作用域
2. `let`、`const`：块级作用域



操作符

- 支持`+=`、`*=`
- 支持`++`、`--`前缀、后缀

```js
// 如果左边是字符串，则进行拼接
"3" + 4 + 5; // 345
3 + 4 + "5"; // 75
 
// 自动类型转换 & 不类型转换
123 == "123" // true
1 == true; // true
1 === true; //false
123 === "123"; // false
// 还有 != 和 !==
```

