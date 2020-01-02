[官方文档](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxss.html)



```css
/* wxml: <view class="commet">...</view> */
/* 字体属性 */
.commet{
	text-align: center;
	font-size: 14px;
    font-weight: bold;
	color: #999;
    
    line-height: 2;
    
	padding: 30px;
    padding-top: 10px;
    padding-bottom: 10px;
}
```



```css

.card {
  margin: 10px;
  position: relative; /*父元素为相对定位*/
}

/* 图片属性：圆角、阴影 */
.bg{
  width: 100%;
  border-radius: 30px;
  box-shadow: 2px 2px 5px #07355f;
}

/* 元素定位 */
.logo{
  border-radius: 10px;
  width: 40px;
  position: absolute; /*子元素为绝对定位*/
  top: 10px;
  right: 20px;
}
```









