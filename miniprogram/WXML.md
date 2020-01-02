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

