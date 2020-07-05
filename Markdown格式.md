# Markdown格式

### 1 标题

```
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
```

### 2 文字编辑

```
*斜体*
**加粗**
分割线：---

***加粗斜体***
~~删除线~~
<u>下划线</u>
```

### 3 列表

```
- 无序列表
1. 有序列表
```

- 无序列表

1. 有序列表

### 4 引用

```
> 引用
```

> 引用效果

### 5 代码

```
​```
代码块
​```

`行内代码`
```

`行内代码`

### 6 上下标

```
x^2^
H~2~O
```

x^2^
H~2~O

### 7 表格

```
ctrl+T
```

### 8 Latex

[一份其实很短的 LaTeX 入门文档]: https://liam.page/2014/09/08/latex-introduction/

##### 普通

```
换行 \\
空格 `\ `

```

##### 集合

$$
集合的大括号：                  \{ ...   \} \\
集合中的“|”：                \mid \\
属于：                    \in \\
不属于：                    \not\in \\
A包含于B：                A\subset B \\
A真包含于B：                A\subsetneqq B \\
A包含B：                    A\supset B \\
A真包含B：                A\supsetneqq B \\
A不包含于B：                A\not\subset B \\
A交B：                    A\cap B \\
A并B：                    A\cup B \\
\overline{A} \\
A\setminus B \\
\mathbb{R} \ \emptyset \\
\forall \ \exist \\
\equiv \\
\gets \ \to \  \leftrightarrow \ \Leftrightarrow \\
$$

$$
T(n)=\left\{
\begin{array}{lcl}
\Theta(1) & & {若n\leq c}\\
aT(n/b)+D(n)+C(n) & & {其他}
\end{array} \right.
$$

[常用符号](http://www.mohu.org/info/symbols/symbols.htm)



# LATEX-math

行间：`$...$`

独立：`$$...$$` 或 `\[...\]`



换行：`\\`

空格：`\`+空格

间距：`\quad`	1 em间距

对齐：`&`



##### 上下标、根号

$$
x_{ij}^2	\quad
{}_1^2X_3^4	\quad
\sqrt[3]{x}
$$

##### 分数

`\frac{1}{2}`
$$
\frac{1}{2}
$$

##### 运算符

$$
\pm\; 	\times\; 	\div\; 	\cdot\; \\
\cap\; 	\cup\;
\geq\; 	\leq\;
\neq\;	\approx\; \equiv \\
\in \not\in \\
$$

##### 积分、求和

$$
\sum_{i=1}^n i
\quad\prod_{i=1}^n
\quad\lim_{x\to\infty}x^2
\quad\int_a^b x^2 dx\quad	\iint
$$

##### 箭头

$$
\leftarrow\quad \longleftarrow	\\
\rightarrow\quad \longrightarrow	\\
\leftrightarrow\quad \longleftrightarrow	\\
\Leftarrow\quad \Longleftarrow	\\
\Rightarrow\quad \Longrightarrow	\\
\Leftrightarrow\quad \Longleftrightarrow
$$

##### 标注

$$
\bar{x}\quad 
\vec{x}\quad
\hat{x}\quad
\mathring{x}\quad
\dot{x}
$$

##### 括号

$$
(x)\quad	[x]\quad	\{x\} \quad
\lvert x \rvert
$$

##### 省略号

$$
\dots\quad \cdots\quad
\vdots\quad
\ddots\quad
$$

##### 矩阵

$$
\begin{array}{ccc}
x_1 & x_2 & \dots\\
x_3 & x_4 & \dots\\
\vdots& \vdots& \ddots
\end{array}
$$

加分隔符的矩阵：
$$
\begin{pmatrix} a&b\\c&d \end{pmatrix} \quad
\begin{bmatrix} a&b\\c&d \end{bmatrix} \quad
\begin{Bmatrix} a&b\\c&d \end{Bmatrix} \quad
\begin{vmatrix} a&b\\c&d \end{vmatrix} \quad
\begin{Vmatrix} a&b\\c&d \end{Vmatrix}
$$

##### 对齐长公式

$$
\begin{split}
x ={} &a+b+c+{} \\
&d+e+f+g
\end{split}
$$

##### 公式组

$$
\begin{gather}
a = b+c+d \\
x = y+z
\end{gather}
$$

对齐公式组,，用`&`对齐
$$
\begin{align}
a &= b+c+d \\
x &= y+z
\end{align}
$$

##### 分支公式

$$
y=
\begin{cases}
-x,\quad x\leq0 \\
x,\quad x>0
\end{cases}
$$

##### 数学字体

$$
\mathcal A	\mathcal Z	\\
\mathbb R	\mathbb N	\\
\mathfrak F	\mathfrak L	\\
\mathscr F	\mathscr K
$$

