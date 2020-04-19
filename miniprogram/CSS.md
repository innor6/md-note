[官方文档](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxss.html)

绿色：#09BB07

红色：#E64340

深灰：#353535

灰色：#888888

灰蓝：#576B95

字体：

https://developers.weixin.qq.com/miniprogram/design/#%E5%AD%97%E4%BD%93

![img](https://res.wx.qq.com/wxdoc/dist/assets/img/8Font.5c21b122.png)



[MATERIAL DESIGN](https://material.io/design/typography/the-type-system.html)

单位pt：20 16 14 12

![img](https://storage.googleapis.com/spec-host/mio-staging%2Fmio-design%2F1584058305895%2Fassets%2F1W8kyGVruuG_O8psvyiOaCf1lLFIMzB-N%2Ftypesystem-typescale.png)



##### 居中

文字居中

```
.popup-title{
	width: 250upx;
	height: 90upx;
	text-align: center;	//水平居中
	line-height: 90upx; //垂直居中
}
```

元素居中

```
竖直排列
.box{
	display: flex;
	flex-direction: column;        /* 竖直排列 */
	align-items: center;        /* 水平居中 */
	justify-content: space-around | space-between
}
```





##### 字体属性

```css
/* wxml: <view class="commet">...</view> */
/* 字体属性 */
.commet{
	font-size: 14px;
    font-weight: bold;
	color: #999;
    
	padding: 30px;
    padding-top: 10px;
    padding-bottom: 10px;
}


```



##### 盒状阴影

```
box-shadow: 10px 10px 5px -5px #888888;
box-shadow: 0 10px 10px -10px rgba(0, 0, 0, 0.5);
水平位移 垂直位移 模糊 范围增加/缩减

box-shadow: rgba(251, 114, 153, 0.4) 0px 6px 10px 0px;
```





##### 渐变

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



