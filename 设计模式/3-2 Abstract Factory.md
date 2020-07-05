#   Abstract Factory

（Kit）

**定义**：提供一个接口，让该接口负责创建“一系列相关或者相互依赖的对象”，无需指定它们具体的类。

**动机**：Factory Method中一个factory只创建一种product，如果几种product是相互依赖的（如要创建mysql的connection、command、result），即product应该是配套的，则应该用一个factory来负责这几种product的创建。
个人理解：其实就是把Factory Method抽象基类接口里声明一个创建对象，变成声明多个创建对象。

**适用性**：

1. 系统要由多个产品系列中的一个来配置时。
2. 强调一系列相关产品对象的设计以便进行联合使用。



**结构**：

（与Factory Method基本相同）

- product：对象的抽象基类。
- factory：声明多种对象的创建接口createXX，返回创建的product。子类实现创建具体的product。
- 一个类中含有一个factory*指针成员，当需要product时，通过来factory创建。



**总结**：

1. “系列对象”指某一特定系列下的对象之间有相互依赖关系，不同系列对象之间不能相互依赖。
2. 易于交换产品系列、有利于产品的一致性。
3. 难以支持新种类的产品：抽象基类应该是稳定的，因此不能在factory添加新的创建对象的接口，否则所有子类都要改变。  