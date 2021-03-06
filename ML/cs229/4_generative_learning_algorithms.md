# 生成学习算法

generative learning algorithms

对比：

- **判别学习算法**：学习p(y|x)，即直接学习输入x映射到的y应该是什么。（如上面的各种回归算法）

- **生成学习算法**：学习p(x|y)，即分别独立为每个类别建立模型，如对于类别y = 1，学习特征x应该具有什么样的性质；同时还要学习p(y)，在不知道x的情况下y先验概率。



分别独立为每个类别 y 建立模型 p(x|y) 和 p(y) ，根据贝叶斯法则得到 p(y|x) ：
$$
P(y|x) = \frac{P(x|y)P(y)}{\sum_{y' \in Val(Y)} P(x|y')P(y')}
$$
对于一个输入 x，计算 p(y|x)，选择概率大的那个y。



##### 似然估计的区别

- 判别学习算法：选择θ，使得给定输入x的p(y|x)的似然估计最大化
- 生成学习算法：选择参数，使得**联合**似然估计 $L = \prod_{i=1}^n p(x^{(i)}, y^{(i)})$最大化



### 高斯判别分析 (GDA)

Gaussian discriminant analysis

用于x是连续的随机变量、分类问题。

简述：对每个类y=1、y=0的数据x分别建立高斯模型，得到 p(x|y)，利用贝叶斯法则得到 p(y|x)，从而得知x属于拿个类别的概率更大。



考虑二分类问题：

1. 假设对于给定的类别y，特征x的条件分布 p(x|y) 是高斯分布的。（如恶性的肿瘤的大小特征服从高斯分布）：

$$
\begin{align}
y &\sim Bernoulli(\phi) \\
x|y=0 &\sim \mathcal{N} (\mu_0, \Sigma) \\
x|y=1 &\sim \mathcal{N} (\mu_1, \Sigma)
\end{align}
$$

​	注意：这里为了方便，假设两个高斯分布共用一个协方差矩阵 Σ（并非必要）

2. 根据这三个分布写出p(y)、p(x|y=0)、p(x|y=1)的PDF
3. 写出对数<u>联合</u>似然估计：

$$
l(\phi, \mu_0, \mu_1, \Sigma) = log\prod_{i=1}^n p(x^{(i)},y^{(i)};\phi, \mu_0, \mu_1, \Sigma)
$$

4. 极大似然估计，令导数=0得到四个参数
   1. φ：样本中 y=1 所占的比例
   2. μ0：y=0 的样本的x的均值
   3. μ1：y=1 的样本的x的均值
   4. Σ：协方差矩阵
5. 利用上面的贝叶斯法则可以求得 p(y=1|x) ，从而可以进行分类。

##### 几何解释

1. 对于二分类问题，x分别位于两个聚簇，最终训练得到的p(x|y=0)、p(x|y=1)其实就是用两个高斯分布模型分别地去拟合这两个聚簇，μ1、μ2 是两个高斯分布的中心位置；
2. 由于共用了 Σ，所以两个高斯分布的形状是一样的；
3. 另外还由 p(y=1|x) = 0.5 得到一个线性的决策边界



##### 一些补充

1. GDA vs 逻辑回归
   1. 事实上，p(y=1|x) 是一个 sigmod 函数。
   2. GDA对 x 的分布做了较强的假设，当知道 x 是高斯分布、较小的训练集时使用GDA能高效的工作。（因为GDA不需要迭代，直接就能算出参数，除了协方差矩阵的计算代价略大一些）
   3. 逻辑回归没有对 x 的分布作假设，因此逻辑回归总能较好的分类
   4. 事实上，当两个类别y的 x 都属于同一个指数族的时候，p(y=1|x) 都是 sigmod 函数，都可以用GDA，但是必须得先知道 x 到底是属于哪种分布。
2. 为什么用同一个 Σ ？
   1. 如果用两个Σ，则需要多算一个Σ，计算量变大；
   2. 两个高斯分布的形状不再一样，决策边界 p(y=1|x) = 0.5 不再是线性的了。



### Naive Bayes

用于特征x的分量xj是离散的情形。

考虑垃圾邮件分类

y = {0,1}

x = {0,1}^10000 （用一万个“单词是否出现在邮件中”作为特征）

则 x 就会有 2^10000 种，那么 p(y|x) 也有 2^10000 种，显然是不行的。

因此做一个强假设（**Naive Bayes假设**）：对于给定的y，各个分量xj的条件概率 p(x_j|y) 相互独立。（注意是<u>条件独立</u>，而不是各个xj之间独立）

则联合条件概率 = 简化为简单的乘积
$$
p(x|y) = p(x_1, ..., x_{10000} | y) = \prod_{j=1}^d p(x_i|y)
$$
联合似然函数
$$
L(\phi_y, \phi_{j|y=1}, \phi_{j|y=0}) = \prod_{i=1}^n p(x^{(i)}, y^{(i)})
$$
做MLE得到参数：

- $\phi_y$：即p(y=1)，y=1的先验概率
- $\phi_{j|y=1}$：当y=1时，xj=1的条件概率
- $\phi_{j|y=0}$

利用贝叶斯法则即可计算 p(y=1|x)。



##### 说明

- NB假设忽略了单词之间的相似性
- 虽然NB假设是一个很强的假设，算法依然能很好地工作
- 上面的例子中xj是二元的，完全可以扩展到xj有多个不同的离散值
- x是连续变量时也可以先离散化处理后，再使用naive bayes



##### Laplace smoothing

naive bayes 存在一个问题：如果 xj = 1 从未出现过，则 p(xj=1|y)=0，导致p(x|y)=0，在计算时会出现0/0的问题；同时一个事件从未发生过就认为发生的概率为0在统计学意义上也是不合理的。

改进：

给每种事件的出现次数 + 1，如：
$$
p(x_j | y=1) = \frac{1 + \#(y=1 \and x_j=1)}{1 + \#(y=1 \and x_j=0) + 1 + \#(y=1 \and x_j=1)}
$$
注意当xj存在k个离散值时，分母应该+k。



##### 文本分类

naive bayes的特征x只考虑了单词是否出现，而没有考虑单词出现的次数。可以将p(x|y)表示为给定y，单词xj在邮件中的出现频率。



### 生成算法总结

优点：计算高效、不需要梯度下降迭代、实现简单等。

缺点：精度不如其他的算法（逻辑回归、SVM、NN）

适合：做一些（quick and dirty）的尝试

