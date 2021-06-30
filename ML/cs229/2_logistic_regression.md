# 逻辑回归

分类问题

考虑二分类问题，即 y 只有 0 和 1。

定义：
$$
h_\theta(x) = g(\theta^T x) = \frac{1}{1+e^{-\theta^T x}}
$$
其中 g(z) 是 logistic 函数（sigmoid function）：
$$
g(z) = \frac{1}{1+e^{-z}}
$$

1. 图像：s形曲线，在 z = -∞ 取到 0，在 z = +∞ 取到 1，在 z=0 处取到 0.5。
2. 特殊性质（LME要用到）：$g'(z) = g(z)(1 - g(z))$



二分类问题，有似然函数：
$$
\begin{align}
L(\theta) 
&= p(\vec{y} | X; \theta) \\
&= \prod_{i=1}^n (h_\theta(x^{(i)}))^{y^{(i)}} (1 - h_\theta(x^{(i)}))^{1 - y^{(i)}} \\

l(\theta) 
&= \log L(\theta) \\
&= \sum_{i=1}^n y^{(i)}\log h(x^{(i)}) + (1-y^{(i)})\log(1 - h(x^{(i)})
\end{align}
$$
为了最大化似然估计，取log，得到随机梯度上升的迭代公式：
$$
\begin{align}
\theta_j &:= \theta_j + \alpha \nabla_\theta l(\theta) \\
&:= \dots \\
&:= \theta_j + \alpha(y^{(i)} - h_\theta(x^{(i)}))x_j^{(i)}
\end{align}
$$

1. 这里的 nabla 是对 θ 的分量 θj 求偏导
2. 虽然迭代公式与线性回归的梯度下降**在形式上一模一样**，但实际上它们的 **h_θ(x) 是不同**的，h在这里是一个非线性的函数，因此是不同的算法。
3. sigmoid的导数是凸函数，只有一个全局最优解，所以可以梯度上升
4. 逻辑回归没有正则化方程，只能通过迭代求解



### 几何解释

寻找一条直线（超平面），尽可能地将正面和负面数据分离。



# 牛顿迭代法

牛顿迭代法用于快速找到 f(θ) = 0 的点 θ。

而梯度下降的目标就是找到导数 $l'(\theta) = 0$ 的点。

相比梯度下降，牛顿迭代法收敛的更快。



方法：从 θ = θ0 开始，过 f(θ) 做切线交 x 轴于点 θ1，令 θ = θ1，...

已知斜率、高、宽有如下关系：
$$
f'(\theta) = \frac{f(\theta)}{\Delta}
$$
所以有迭代：
$$
\begin{align}
\theta &:= \theta - \Delta \\
&:= \theta - \frac{f(\theta)}{f'(\theta)}
\end{align}
$$

1. 牛顿迭代是“二次收敛”的，即每次迭代后误差的缩小速度是平方级别的，即每次迭代后，精确到的小数位位数倍增。

2. 梯度下降时，由于梯度函数本身是一阶导数，因此它的导数是二阶导数，有：
   $$
   \theta := \theta - H^{-1}\nabla_\theta l(\theta)
   $$
   其中 nabla l(θ) 是偏导向量，H 是d*d维的hessian矩阵，表示二阶偏导，它的第 ij 项是 $\frac{\partial^2 f(\theta)}{\partial \theta_i \partial \theta_j}$。

3. 缺点：在高维的情形中，每次迭代的代价会很大（需要对d*d的hessian矩阵求逆）。而当参数维度小于50的时候，使用牛顿迭代可以在10次以内收敛。





# 感知机

用一个超平面来进行二分类。

令 $h_\theta(x) = g(\theta^Tx)$ ，其中阈值函数 g(z)：
$$
g(z) = \left\{\begin{matrix}
 1 & z\ge0\\
 0 & z<0
\end{matrix}\right.
$$
学习规则：
$$
\theta_j := \theta_j + \alpha(y^{(i)} - h_\theta(x^{(i)}))x_j^{(i)}
$$


### 几何解释

θ 其实表示的是“过原点的超平面”的法向量，当 θ 与 x 相似时，分类为 $g(\theta^Tx) = 1$ 

1. 当 y 和 h 相同时，θ 不变
2. 当 y = 1 而 h = 0 时，说明希望 x 与超平面的法向量 θ 相似，因此在 θ 上加一个 αx 的分量
3. 同理，当 y = 0 而 h = 1 时，减去一个小的 x 的分量



### 缺点

1. 没有概率解释
2. 对无法用超平面划分的数据无法分类（因此实践中不使用）



# softmax？

k分类问题，结果用一个k*1向量表示，每个分量表示预测为该分类的概率，选择概率最大的分量，设他为1，其他的设为0。
