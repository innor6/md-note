# Markov decision processes (MDP)

五元组：{S, A, P_sa, γ, R}

MDP过程：
$$
s_0 \stackrel{a_0}{\longrightarrow} s_1 \stackrel{a_1}{\longrightarrow} \dots 
$$
奖励：
$$
R(s_0, a_0) + \gamma R(s_1, a_1) + \gamma^2 R(s_2, a_2) + \dots
$$
对于给定初始状态s0、决策 pi，定义值函数：
$$
V^\pi(s) = E[R(s_0) + \gamma R(s_1) + \gamma^2 R(s_2) + \dots]
$$
Bellman equations（递归定义）：
$$
V^\pi(s) = R(s) + \gamma \sum_{s' \in S} P_{s,\pi(s)}(s')V^\pi(s')
$$

- 含义：当前状态s的奖励 + 以下一状态s'开始的奖励
- 等式中只有V是未知的，求的就是V，是V的线性组合



### 目标

找到一个策略pi，使得值函数V最大化：
$$
V^* = R(s) + \max_a \gamma \sum_{s' \in S} P_{s, a}(s')V^*(s')
$$
（可以看到这里好像存在最优子结构？但是V之间可能互相引用。。）



### 算法

##### Value iteration

1. 初始化所有的V(s) = 0；
2. 每次迭代时，同时对每个s根据上式用旧的V(s)计算出新的V(s)。

（也可以一次只更新一个V(s)，但是同步更新的方式在代码矩阵计算时更方便，有点像Bellman-Ford算法）

##### Policy iteration

1. 随机选择一个策略pi，计算V；（解一个线性系统方程组）
2. 每次迭代根据上式更新策略pi(s)，然后回到步骤1重新计算V

（Policy iteration需要计算V，当状态空间S很大时（>1000），计算量很大，因此倾向于使用Value iteration）



### 学习

随机初始化pi = pi0，重复：

1. 使用pi0进行几次MDP实验
2. 根据实验计算Psa、Reward
3. 通过Value iteration更新V，并得到新的策略pi（贪心）



Exploration vs Exploitation：探索还是利用？

随机初始化的pi如果一开始找到了一个局部最优解，由于贪心策略，可能再也不能找到更优决策。

改进（ε-贪心）：决策时，有ε=0.1的概率执行随机的决策



### 





# 连续的状态空间

### 状态空间离散化

缺点：导致值函数V变为分段函数，而不是光滑的曲线，只有将网格分的很细才有较好的近似；同时随着状态维度的线性增长，状态空间会指数增长k^d。（只适合1d、2d的状态空间，最多6d）



### 值函数近似

（approximating the value function）

##### simulator

输入s、a，输出下一状态s'（其实就是模拟P_sa）

获取simulator：

1. 通过物理建模得到；
2. 执行m次MDP过程收集数据，然后使用其他的机器学习方法对s、a、s'建模（如线性回归）。

（可以加噪声，如高斯噪声）

有了simulator，就可以得到大量的数据用于后面的学习。



##### fitted value iteration 拟合值迭代算法

假设：S是连续的，行动空间A是离散且较小的。

得到积分形式的 Bellman equations：
$$
V(s) = R(s) + \gamma \max_a \int_{s' \in S} P_{s, a}(s')V(s')ds'
$$
想法：

假设存在线性模型：
$$
V(s) \approx y = \theta^T \phi(s)
$$
这里φ是状态s的特征提取函数。

如果得到了这个模型，对于任意连续的s，都能立刻计算出V(s)的近似y。



算法

1. 初始化 θ = 0
2. 重复：
   1. 随机选取m个状态s：
      1. 对每个行动a，通过simulator（P_sa）采样k次得到k个可能的后续状态s'，
      2. 计算 V(s) 的近似 $y = \frac{1}{k}\sum_k R(s) + \gamma V(s')$ （这里的V(s')直接通过θ的线性模型得到）
      3. 选取y最大时的a、y
   2. 得到了m个训练样本 (s, y) 后，通过监督学习得到新的 θ

- 此方法不能证明是收敛的，虽然实践中经常能收敛。

- 监督学习不一定要用线性回归。



部署：

运行时，通过对于所有a计算对应的V(simulator(s,a)) = V(s')，来找出使V最大的a，作为下一步的行动。
