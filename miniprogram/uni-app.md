##### 微信小程序配置

打开工程中的manifest.json文件，选择微信小程序配置，输入小程序id即可。

##### 导入样式组件库

复制helloworld工程的common文件夹；在App.vue的`<style>`中导入组件样式`@import './common/uni.css';`；`static`目录下的`uni.ttf`也要复制过去。

##### 开发调试时快速进入页面

pages.json中“condition”配置多个路径，保存后，ctrl+R可以选择打开哪个页面。

进入微信开发者工具—工具—编译配置，选择页面。

##### 底部导航

在pages.json中的"tabBar"中设置；

图标可以去iconfont网站下载，下两种颜色#333333、选中颜色，大小80，png。图标放到static/tabbar文件夹下。

##### view

`<view hover-class="other-class>"`属性hover-class可以为其他的css样式，使得在按下时样式发生变化。

##### text

换行\n。

属性selectable是bool类型，需要冒号：`<text :selectable="true">`

##### css选择器

class="..."

id="..."

```css
.classname>view{} /*子类选择器*/
.view:nth-of-type(2){...}
.view:nth-of-type(odd){...} /*奇偶选择器*/
.view:nth-of-type(even){...}
```

[CSS选择器](https://www.runoob.com/cssref/css-selectors.html)

##### Flex布局

[A Complete Guide to Flexbox](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)

[阮一峰的flex教程](http://www.ruanyifeng.com/blog/2015/07/flex-grammar.html)

组件的嵌套，里面的元素变为item。

```css
/*居中*/
display: flex;
justify-content: center;
align-items: center;

.parent {
display: flex;
/*主轴方向*/
flex-direction: row | row-reverse | column | column-reverse;
/*如何换行*/
flex-wrap: nowrap | wrap | wrap-reverse;
/*主轴对齐方式*/
justify-content: flex-start | flex-end | center | space-between | space-around;
/*cross轴对齐方式*/
align-items: flex-start | flex-end | center | baseline | stretch;
/*cross轴对齐方式*/
align-content: flex-start | flex-end | center | space-between | space-around | stretch;
}

.sub {
    flex: i; /*[推荐]这个item占i份的空间（自动缩放）*/
    flex-shrink: 0; /*此item不被flex缩放*/
    align-self: auto | flex-start | flex-end | center | baseline | stretch; /*某个item覆盖父类的align-items*/
}
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





