盒子模型

```css
.container {
    width: 80%;
    margin: auto;
}

.box1 {
    # margin：顺时针指定↑→↓←
    margin: 5px 10px 5px 10px;
    margin: 5px 10px;
    margin: 5px 10px 5px;
    margin: auto;
    margin-top: 20px;
    
    # border
    border: 5px blue solid;
    border-radius: 15px;
    border-bottom-style: dotted;
    
    # padding 类似margin

    # height
    # widtd
}
```



```css
p {
	background-color: antiquewhite;
	color: #555555;
    border: 5px dotted #cccccc;
}
```



文字居中

```css
p {
	text-align: center;
}
```



float浮动元素

```css
.block {
	float: left;
	width: 33.3%;
	border: 1px solid #ccc;
	box-sizing: border-box;	// border会导致总长超过100%，要用这个解决
}
```

浮动元素上下要用clear包围



选择器

```css
<h1 class="box" id="unique"></h1>

// 标签选择器
h1 { }

// class选择器
.box { }

// id选择器
#unique { }

// 标签属性选择器(含有title属性的标签a)
a[title] { }
a[title="choose"] { }
a[title~="contain"] { }

// 伪类与伪元素
button:hover { }
a:hover { }
a:visited { }
p:nth-child(even) { }
p:first-child { }
p::first-line { }
```



定位

```css
.box1 {
    # 相对定位，保留元素原始占用的空间，相对本身原点偏移
	position: relative;
    top: 30px;
    left: 30px;
}

.box2 {
    -# 绝对定位，元素本身不占用空间，相对采用相对定位的父元素偏移
    # “父相子绝”
	position: absolute;
    top: 30px;
    left: 30px;
}

.fixed {
    # 固定位置，下面代码是固定在右下角
    position: fixed;
    right 0;
    bottom: 0;
}
```



毛玻璃

```
backdropFilter: "blur(15px)",
background: "rgba(255,255,255,0.3)",
```

