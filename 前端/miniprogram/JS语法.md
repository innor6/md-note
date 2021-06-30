vue强制刷新

```
this.$forceUpdate()
```



事件传递其他参数

```js
@blur="setAmount($event,date,id)"	//组件中第一个参数为事件

setAmount(e,date,id) {...}
```



if

```js
if (...) {
	...
} else if (...) {
	...
}

// *判断对象中是否包含某个键值
if (key in obj)
```



循环

```js
// for ... in ...	其中，i是index
for(let i in arr) {
	console.log(i);
	console.log(arr[i]);
}

for (let key in map) {
    console.log(key); // 'name', 'age', 'city'
}
```





列表：

```js
// length
1 == arr.length

// push 尾部插入
arr.push('插入的文本1')

// splice(ind, len) 删除从index开始的len个元素
arr.splice(1,1); 

// 拼接，注意拼接后是返回一个新数组，因此需要重新赋值
arr1 = arr1.concat(arr2)
```



map

```js
m.set('Bob', 59);
m.has('Adam'); // 是否存在key 'Adam': true
m.get('Adam'); // 67
m.delete('Adam');

Object.keys(this.date_list)	//获取对象的key列表
Object.keys(this.date_list)[Object.keys(this.date_list).length-1]	//获取最后一个key
```



深拷贝对象

```js
// 拷贝上一个库存的数量
let lastdate = Object.keys(this.date_list)[Object.keys(this.date_list).length-1]
// 把上一个对象的key全部拷贝过来（单层的，非嵌套的对象）
this.date_list[date] = {}
for (let id in this.date_list[lastdate]) {
	this.date_list[date][id] = this.date_list[lastdate][id]
}
```





JSON - String

```js
// json 转 string
str = JSON.stringify(item)

// string 转 json
item = JSON.parse(str)

// url encode 示例
// 用于页面切换时
uni.navigateTo({url:'/pages/visualPage/index?editItem='+encodeURIComponent(JSON.stringify(item))});

onLoad(option){
    const item = JSON.parse(decodeURIComponent(option.item));
},
```



正则表达式

```js
var str = 'https://ucmp.sf-express.com/service/weixin/activity/wx_b2sf_order?p1=SF1086794026382';
var reg = /^https:.+(SF\d{13})$/;	// 提取运单号
let result = reg.exec(str);
// 不匹配时返回null
if (result == null) console.log('匹配失败'); 
// 匹配时，返回list
// 内容为：[匹配的整个表达式, group1, gropu2, ...]
// 可用打组来提取各个内容
let waybill_id = result[1];	
```

