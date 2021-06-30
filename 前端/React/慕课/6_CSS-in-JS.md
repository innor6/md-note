安装Material-UI

https://material-ui.com/zh/getting-started/installation/

```
yarn add @material-ui/core
```



## Style

```
yarn add @material-ui/styles
```



```jsx
import { makeStyles } from '@material-ui/core/styles';

// 1 在这个Hook中定义多个css（其实是用object表示的css）
const useStyles = makeStyles( theme => ({
  // 样式一
  root: { color: 'red' },
  // 样式二，可以通过传props来动态改变样式
  buttonStyle: props => {
    return {
        color: props.cool ? "blue" : "red",
        // 驼峰命名
        backgroundColor: props.cool? "orange" : "purple",
        // 根据断点来变换样式
        [theme.breakpoint.up("sm")]: {
            color: "cyan"
        },
        // calc
        height: "calc(100vh - 6rem)",
        // 表达式
        paddingLeft: `calc(1em + ${theme.spacing(4)}px)`,
    }
  }
}));

// 2 在组件中使用样式
export default function MyButton(props) {
  // 2.1 通过Hook获取所有样式（这里还给useStyle传props来动态控制样式）
  const classes = useStyles(props);
  
  // 2.2 在组件的className中设置样式
  return (
      <Button className={classes.buttonStyle}>Hook</Button>;
      // 同时使用多个class
      <div className={`${classes.sty1} ${classes.sty2}`}></div>;
  )
}
```





# 布局

## Container

用于居中

```
<Container maxWidth="sm"></Container>
```



- Flex：一维布局，内容数量不定
- Grid：二维的、固定的布局





```jsx
// 一个简单的页面居中
<Grid
  container
  justify="center"
  alignItems="center"
  style={{ minHeight: "100vh" }}
>
  <Grid item>
      <CircularProgress />
  </Grid>
</Grid>
```



## Grid

12栅格宽度系统

```tsx
<Grid container spacing={3}>
  <Grid item xs={12} sm={6}></Grid>
</Grid>
```

- container 可以设置的属性：
  - **spacing**：单位为 8px
  - **direction**：默认"row"，也可以是"column"，通过嵌套不同 direction的 container 设计复杂的排版。
  - **juestify**：控制 direction 方向上 item 的分布
    - flex-start | center | flex-end | space-between | space-around | space-evenly
    - space-around是item和item之间会有两倍间距
    - 要让 `<Grid item/>` 内部的元素居中，可以设置 `<Grid item style={{ textAlign: "center"}}>`
  - **alignItem**：控制垂直方向上的对齐
    - flex-start | center | flex-end | strech | baseline
    - baseline是居中对齐后再移到垂直方向的最前端
- item 可以设置的属性：
  - 断点：控制宽度
- 一个 Grid 可以既是 container，又是 grid。
- item 内的元素通常要设置一个 **minWidth** 以防止元素被压缩的太窄。如果 xs = {6} 且6栅格时的宽度小于了 minWidth，则一行两个 xs = {6} 的元素会重叠，建议改为 xs={12}。



# Typography

浏览器默认字体为 16px，Material-UI 的字体大小默认为 14px，浏览器计算出的大小为：
$$
computed = specification \frac{typography.fontSize}{14} \frac{htmlfontSize}{typography.htmlFontSize}
$$

修改主题字体大小

```jsx
const theme = createMuiTheme({
  typography: {
    // 中文字符选用一个略小的 fontsize 会比较合适。
    fontSize: 12,
  },
});
```

如果想用 `10px` 简化：

```jsx
const theme = createMuiTheme({
  typography: {
    // 告知 Material-UI 此 html 元素的具体字体大小。
    htmlFontSize: 10,
  },
});

html {
  font-size: 62.5%; /* 62.5% of 16px = 10px */
}
```



建议使用 `rem`， `1rem == 默认字体大小`



align：排版方向

color：字体颜色

noWarp：文本太长时不自动换行，而是显示...

variant：默认为 body1，可以修改为其他的dom类型：

'h1'
| 'h2'
| 'h3'
| 'h4'
| 'h5'
| 'h6'
| 'subtitle1'
| 'subtitle2'
| 'body1'
| 'body2'
| 'caption'
| 'button'
| 'overline'
| 'srOnly'
| 'inherit'