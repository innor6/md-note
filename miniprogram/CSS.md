### 字体

80rpx：数字

40rpx：页面大标题



**36rpx**：单独的短文字，大按钮

**34rpx**：首要层级，较长段的文字，列表标题 

**28rpx**：次要层级，如标题下的摘要



26rpx：弱化内容，小按钮、链接

--22rpx：版权等说明信息







### 盒子模型

![](https://www.runoob.com/images/box-model.gif)

指定的width和height都是content的大小。

absolute相对的是父元素的padding框（即无视父元素的padding）



### 居中

元素居中

```css
竖直排列
.box{
	display: flex;
	flex-direction: column;        /* 竖直排列 */
	align-items: center;        /* 水平居中 */
	justify-content: space-around | space-between
}
```

文字居中

```css
.title{
	width: 250upx;
	height: 90upx;
	text-align: center;	//水平居中
	line-height: 90upx; //垂直居中
}
```



### 定位

子元素相对于父元素定位：

```css
/*父元素：相对定位*/
.card {
  position: relative; 
}

/*子元素：绝对定位*/
.logo{
  position: absolute; 
  top: 10px;
  right: 20px;
}
```

页面底下浮动：

```css
.container {
	padding-bottom: 110rpx; /* 页面给下方预留空间：30+80 */
}

.bottom-box{ 
    position:fixed;
    height:80rpx;
    bottom:30rpx;  
    z-index:9999;	
    /* Z-index用于防止被其他元素挡住（如果想被某些弹出窗口挡住，请在html中将优先级更高的放在更后面）*/
}
```





### css选择器

class="..."

id="..."

```css
.classname>view{} /*子类选择器*/
.card image{} /*后代选择器*/
.view:nth-of-type(2){...}
.view:nth-of-type(odd){...} /*奇偶选择器*/
.view:nth-of-type(even){...}
```

[CSS选择器](https://www.runoob.com/cssref/css-selectors.html)





### Flex

[A Complete Guide to Flexbox](https://css-tricks.com/snippets/css/a-guide-to-flexbox/)

[阮一峰的flex教程](http://www.ruanyifeng.com/blog/2015/07/flex-grammar.html)

https://zxuqian.cn/css-flex-box-layout/

组件的嵌套，里面的元素变为item。

```css
/*居中*/
display: flex;
justify-content: center;
align-items: center;

.parent {
display: flex;
    
// 主轴方向
flex-direction: row | row-reverse | column | column-reverse;
// 如何换行 
flex-wrap: nowrap | wrap | wrap-reverse;
// 主轴对齐方式
justify-content: flex-start | flex-end | center | space-between | space-around;
    
// cross轴对齐方式
align-items: flex-start | flex-end | center | baseline | stretch;
// 行与行的对齐方式
align-content: flex-start | flex-end | center | space-between | space-around | stretch;
}


.sub {
/* 覆盖父类的align-items */
align-self: auto | flex-start | flex-end | center | baseline | stretch; 

/* 要想覆盖父类的justify-content，只能用margin */
margin-left: auto;

flex-grow: 2;
    /* 若有剩余空间，自动放大，默认为0。如令3个item的该属性分别为1 2 1*/
flex-shrink: 0;
    /* 若空间不足，自动缩小，默认为1。0表示禁止缩小 */
flex-basis: <length> | auto; 
    /* 指定宽度（行模式下），优先于width */
    
flex: i; 
    /* [推荐]是上面三个属性的缩写。这个item占i份的空间 */
    /* 默认 0 1 auto*/
    /* flex: none 表示不缩小也不放大（0 0 auto）*/
    /* flex: auto 表示自动缩放（1 1 auto） */
}
```





### 字体属性

```css
/* wxml: <view class="commet">...</view> */
/* 字体属性 */
.commet{
	font-size: 14px;
    font-weight: bold; //700
	color: #999;
    
	padding: 30px;
    padding-top: 10px;
    padding-bottom: 10px;
    
    overflow: hidden;
    text-overflow: ellipsis; /* 省略号 */
}


```



### 阴影

```css
box-shadow: 10px 10px 5px -5px #888888;
box-shadow: 0 10px 10px -10px rgba(0, 0, 0, 0.5);
水平位移 垂直位移 模糊 范围增加/缩减

box-shadow: 0px 6px 10px 0px rgba(251, 114, 153, 0.4);
```



```css
bili蓝：rgb(35, 173, 229)

border: 1px solid #e9eaec;
border-radius: 8px;
box-shadow: 0 6px 12px 0 rgba(106,115,133,.22);
```









### 渐变

[使用 CSS 渐变](https://developer.mozilla.org/zh-CN/docs/Web/Guide/CSS/Using_CSS_gradients)



```css
background: linear-gradient(to right bottom, pink, blue);

//渐变中心点移到65%
background: linear-gradient(to right bottom, #11EE96, 65%, #11EEEE);

//渐变方向：0deg自下向上，角度顺时针旋转，-90deg为自右向左
background: linear-gradient(-90deg, red, yellow);

```

渐变按钮hover时变换的效果：

```css
//创建一个a-b-a的渐变，拉伸背景宽至200%
.box2 {
    background: linear-gradient(125deg, #a18cd1, #fbc2eb, #a18cd1);
    background-size: 200%;
    transition: 0.5s;

    font-size: 18px;
    color: #FFFFFF;
}

//hover时背景向左滑动，组件向上移动
.box2-hover 
{
    background-position-x: 100%;
    transform: translateY(-15px);
}
```

渐变配色

```
- #a18cd1, #fbc2eb
- #ffe29f, #ffa99f
- #8AC6E9, #9EFFE2
#43e97b, #38f9d7
#fa709a, #fee140
#4881eb, #04befe
#fdfc47, #24fe41
```





### 图片适应

```html
<view class="card">
  <image src="../../img/bg.jpg" mode="widthFix"></image>
</view>
```



### hover-class

属性hover-class可以使得在按下时样式发生变化。

```html
<view hover-class="other-class">
```



### 雪花飘飘

html：

```
<div id="snowMask"></div>
```

注：div写在一个view中时，若写在最前面，则被后面元素覆盖（常用操作）；写在最后，则会覆盖在前面的元素之上。

css：

```
@keyframes snow{
    0% {
    	background-position: 0 0, 0 0;
    }
    100% {
    	background-position: 500px 500px, 1000px 500px;
    }
}

//id选择器
#snowMask {
    position: fixed;
    left: 0;
    top: 0;
    width: 100%;
    height: 100%;
    background: url('/static/snow1.png'),url('/static/snow2.png');
    animation: 10s snow linear infinite;
    pointer-events: none;
}
```





# 文本相关

- 换行\n。
- 可选中：属性selectable是bool类型，需要冒号：`<text :selectable="true">`




### 文本省略号

```css
{
word-break: break-all;		//断句换行方式（否则可能只显示一行且超出画面）
overflow: hidden;

display: -webkit-box;
-webkit-box-orient: vertical;
-webkit-line-clamp: 2;		//设置最大行数
text-overflow: ellipsis;	//超出部分变为省略号
}
```



overflow: auto  //超出后变为scroll



缩进

```
// 实现悬挂缩进：首行缩进取负值，再用padding弥补
text-indent: -2em;
padding: 2em;

//em，相对长度单位，为父元素文本字体尺寸的倍数。
```





### 渐变文本

```css
.gradient-text{
    padding-left: 30rpx;
    font-size: 32rpx;
    font-weight: bold;

    background-image:linear-gradient(left,#f65aa1,#c592c8,#8da6d5); 
    -webkit-background-clip:text; 
    color:transparent; 
}
```

原理：使用彩色背景、用文本对背景进行裁剪、文本颜色设为透明。



