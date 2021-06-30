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



表单

- 常用属性：
  - id：全局唯一id，用于选择对象
  - name：提交时的key，也用于在表单内选择对象，也是单选按钮的组名
  - value：提交时的value，控件的显示内容
- HTML5属性：
  - `novalidate`：提交时不校验，只用于form标签
  - `autocomplete="on"`：自动完成，input域会显示以前的输入（也可用于form标签）
  - 以下属性针对input
    - `placeholder="First name"`：input为空时显示的提示信息
    - `autofocus`：自动聚焦
    - `required`：提交时必须非空
    - `pattern="[A-Za-z]{3}"`：提交时匹配正则表达式
    - `form="form1 form2"`：在form外指定input所属的表单
  - 以下属性用于提交控件：type="submit" 和 type="image"
    - ` formaction="demo-admin.php"`：覆盖form的action，提交到另一个url
    - `formtarget="_blank"`：提交到一个新的页面上
    - `formenctype="multipart/form-data"`：编码（好像只支持三种）
    - `formmethod="post"`：提交方法
    - `formnovalidate `：不校验



拖放、地理定位（Geolocation）



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