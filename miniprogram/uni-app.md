# 常用

定时器

```js
uni.showToast({title: '注册成功'});
setTimeout(function(){uni.navigateBack();},1000);
```



##### toast

```
uni.showToast({
    title: '标题',
    icon: none	//不设置该属性则为√的图标
	duration: 1500 //ms，默认值
});

uni.showLoading({title: '加载中',});	//onLoad开头使用
uni.hideLoading();	//onLoad中request返回success时
uni.showToast({title:'连接服务器失败', icon:'none'})	//fail时
```



##### action_sheet

用于列表类的选择

```js
uni.showActionSheet({
    itemList: this.examTypeList,
    success: res => { this.examType = this.examTypeList[res.tapIndex] }
});
```



##### 跳转

```
uni.navigateTo({url: '../login/login',});
uni.redirectTo	//清空页面栈，重定向
uni.reLaunch
uni.switchTab
uni.navigateBack
```

https://uniapp.dcloud.io/api/router?id=navigateto



##### 数据缓存

```
//同步存
uni.setStorageSync('SUID' , res.data.u_id + '');
//同步取
var SUID  = uni.getStorageSync('SUID');
//同步删除
uni.removeStorageSync('key');
```



https://uniapp.dcloud.io/api/storage/storage?id=setstorage

设置失效时间：

https://www.csweigou.com/article/2143.html



##### 定时器

```
setTimeout(callback, delay, rest)
setTimeout(function(){uni.navigateBack();},1000);
```

dealy为毫秒，rest为可选的传给回调函数的参数。

使用场景：数据提交成功后，显示toast，然后1000ms后触发页面跳转



##### 日期格式

```js
// 计算今天的日期
let now = new Date();
let y = now.getFullYear();
let m = now.getMonth()+1;	if (m<10) m = '0'+m;
let d = now.getDate();
this.setDateTime = y+'-'+m+'-'+d+' 00:00:00';

    
// 计算经过的时间的hh-mm-ss格式
//先获取从1970-1-1 8:00:00到现在的毫秒数
{ let d = new Date(); this.start = d.getTime()  }	
{ let d = new Date(); this.end = d.getTime()  }
//毫秒数相减
let passed =  this.end - this.start;	
//从1970-1-1 08:00:00减去8小时,再加上passed毫秒数
let t = new Date();
t.setTime(-28800000+passed);
//时间格式的转化
let hh = t.getHours();		if (hh<10) hh = '0' + hh;
let mm = t.getMinutes();	if (mm<10) mm = '0' + mm;
let ss = t.getSeconds();	if (ss<10) ss = '0' + ss;
this.passedtime = hh + ':' + mm + ':' + ss;

//hh-mm-ss转换为秒数
let tt = '01:30:03'
let hh = '' + tt[0] + tt[1];
let mm = '' + tt[3] + tt[4];
let ss = '' + tt[6] + tt[7];
this.duration = hh*3600+mm*60+ss*1;
```





##### 下拉刷新

[需要在page.json的style中设置](https://uniapp.dcloud.io/api/ui/pulldown)



# 配置

##### 小程序id配置

打开工程中的manifest.json文件，选择微信小程序配置，输入小程序id即可。

##### 服务器域名

微信公众平台——开发——开发设置——服务器域名（域名写到/以前就可以）

##### 获取用户唯一标识openid

https://blog.csdn.net/qq_34328404/article/details/80624577

##### 导入样式组件库

复制helloworld工程的common文件夹；在App.vue的`<style>`中导入组件样式`@import './common/uni.css';`；`static`目录下的`uni.ttf`也要复制过去。

##### 开发调试时快速进入页面

pages.json中“condition”配置多个路径，保存后，ctrl+R可以选择打开哪个页面。

进入微信开发者工具—工具—编译配置，选择页面。

##### tabBar

在pages.json中的"tabBar"中设置；

图标可以去iconfont网站下载，下两种颜色#333333、选中颜色，大小80，png。图标放到static/tabbar文件夹下。

```
"tabBar": {
		"color":"#000000",
		"selectedColor":"#4CD964",
		"borderStyle":"white",
		"backgroundColor":"#FFFFFF",
		"list": [
			{
				"pagePath":"pages/index/index",
				"text":"主界面",
				"iconPath":"static/tabbar/index.png",
				"selectedIconPath":"static/tabbar/indexed.png"
			},
			{
				"pagePath":"pages/my/my",
				"text":"测试用",
				"iconPath":"static/tabbar/my.png",
				"selectedIconPath":"static/tabbar/myed.png"
			}
		]
	},
```

##### 顶部导航标题

在 `pages.json` 中的每个 `page` 的 `style` 属性，添加：

`"navigationBarTitleText": "标题"`



# thorui

pages.json

```
//自动引入 thorui组件
	"easycom": {
			"autoscan": true,
			"custom": {
				"tui-(.*)": "@/components/thorui/tui-$1/tui-$1.vue"
			}
	},
```

App.vue

```
/*每个页面公共css uParse为优化版本*/
	@import './common/app.css';
	/* #ifndef APP-NVUE */
	@import './components/uni/uParse/src/wxParse.css';
	/* #endif */
```





# JS

一定要先写`export default{}`包括所有。

框架：

```html
<script>
	export default {
        data() {return {}},
        methods: {
            
        }
    }
</script>
```

##### 数据绑定

```html
<view>{{var}}</view> //绑定变量
<view :class="var"> //使用了冒号，使得var是动态绑定的变量
	//上述两个地方都可以用三目运算?:
<button @tap="choose"> //绑定了choose函数
```

class&style：

[官方](https://uniapp.dcloud.io/use?id=class-%e4%b8%8e-style-%e7%bb%91%e5%ae%9a)

```html
<view :class="['c1',var]"> //一个组件可以含有多个class样式(c1和var)
<view :class="[var>10?c1:'', v2>10?c2:'']">//使用三目运算符?:
<view :class="{c1:isTrue1, c2:isTrue2}"> //条件样式

<view class="box" :style="{'color':var,'font-size':size+'px'}">
//所有非变量都要用引号''圈起来，style不要用upx
```

##### 条件渲染

```html
<view class="box" v-if="isShow"> //使用isShow变量控制
<view class="box" v-if="(age>20)"> //使用age变量控制，建议加括号
<view class="box" v-show="isShow">
<view class="box" v-show="(age>20)">
/*【推荐写法】*/
<template v-if="isShow">
    <view>...</view>
</template>
<template v-else-if="(age>20)">
    <view>...</view>
</template>
<template v-else>
    <view>...</view>
</template>
   
```

 v-show小结：
1、v-show仅仅控制元素的显示方式，通过display属性的none
2、当我们需要经常切换某个元素的显示/隐藏时，使用v-show会更加节省性能上的开销

v-if小结：
1、v-if会控制这个DOM节点的存在与否。
2、如果在运行时条件很少改变，则使用 v-if 较好。



##### 列表渲染

```html
/*一维数组*/
<view class="c" v-for="(val,index) in list1" :key="index">
    {{val.name}} - {{val.id}}
</view>

list1:[
	{ name:"a",id:"1" },
	{ name:"b",id:"2" },
	{ name:"c",id:"3" },
]

/*二维数组*/
<view class="c" v-for="(val1,index1) in list2" :key="index1">
    <view>{{val1.name}}</view>
    <view v-for="(val2,index2) in val1.list" :key="index2">				{{index2}} - {{val2}}
    </view>
</view>
list2:[
	{
		name:"a",
		list:["1.1","1.2","1.3"]
	},
	{
		name:"b",
		list:["2.1","2.2","2.3"]
	},
]

/*对象*/
<view class="c" v-for="(val,key) in objlist" :key="key">
    {{key}} - {{val}}
</view>
objlist:{
	attr1:"a",
	attr2:"b",
	attr3:"c",
}

/*【推荐用block】*/
<block v-for="(val,index) in objlist" :key="index">
    <view class="c">
        {{index}} - {{val}}
    </view>
</block>
```





##### 动态变量名

```js
var vars={}; //批量定义
for(var i=0;i<5;i++){
    var varName='name-'+i;  //动态定义变量名
    vars[varName]='value-'+i;  //动态赋值
}
console.log(vars);
```

另一种方法（没试过）

```js
var v_1 = "我是v_1 的值";
var v_2 = "我是v_2 的值";
var v_ = 'v_' + ${value}; //拼接变量名
console.log( eval( v_) );
```





