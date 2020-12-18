HTML

[my page](./learn_html/first.html)

```HTML
<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title>网页名字</title>
</head>

<body>

    <h1>这是一个标题</h1>
    <h2>这是一个标题</h2>
    <h3>这是一个标题</h3>

    <p>这是一个段落。</p>
    <p>这是另外一个段落。</p>

    <a href="https://www.runoob.com">这是一个链接</a>
    
    <br>

    <img src="/images/logo.png" width="258" height="39" />

</body>

</html>
```



- html不区分大小写，但标签、标签属性、属性值建议使用小写
- html元素都可以设置属性
- 属性值要用引号，建议用双引号，除非属性值本身就含有双引号
- 所有连续的空格或空行都会被算作一个空格显示
- div是块级元素，可用组合其他 HTML 元素
- span是内联元素，可用作文本的容器
- 颜色：#FF0000，#F00，rgb(255,0,0)，rgba(255,0,0,0.5)



URL

- 只能使用 ASCII 字符集
- 使用 "%" 其后跟随两位的十六进制数来替换非 ASCII 字符
- 不能包含空格。URL 编码通常使用 + 来替换空格。



head中的元素：

```html
<head>
    
    // title旁边的小图标
    <link rel="shortcut icon" href="图片url">

    // 30s自动刷新一次页面：
    <meta http-equiv="refresh" content="30">

	// css
    <style type="text/css">
        body {background-color:yellow}
        p {color:blue}
    </style>
    
    // 导入外部样式
    <link rel="stylesheet" type="text/css" href="styles.css">
</head>
```



杂

- [创建图像映射](https://www.runoob.com/try/try.php?filename=tryhtml_areamap)：使用map、area标签，可以点击图片中的不同区域时，跳转到不同的页面