wxml:

```html
<view class="card">
  <image src="../../img/bg.jpg" mode="widthFix"></image>
</view>
```

wxss:

```css
.card {
  margin: 10px;
}

//后代选择器
.card image{
  width: 100%;
  border-radius: 30px;
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
  
  /*子元素为绝对定位*/
  position: absolute; 
  top: 10px;
  right: 20px;
}
```

