UE4

输入映射：

编辑——项目设置：引擎——输入：绑定——操作映射、轴映射

简单碰撞：

项目设置——物理——Simulation——默认形状复杂度——use simple collision

声明可见属性：

```
// 球体碰撞组件
UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
// 弹簧臂、相机组件
	UPROPERTY(EditAnywhere)
		USpringArmComponent* OurCameraSpringArm;
```



##### Tick

利用tick()函数进行定时刷新。

每次刷新中又分为好几个阶段（物理计算前、中、后）。

actor和component都有自己的tick，`PrimaryActorTick` 使用 Actor 的 `Tick()` 函数，而 `PrimaryComponentTick` 使用 ActorComponent 的 `TickComponent()` 函数。

- 在构造函数中通过 `PrimaryActorTick` 成员设定该actor如何调用tick()。
- 在 actor 的`BeginPlay `中，注册其主 tick 函数和其组件的 tick 函数。

```c++
PrimaryActorTick.bCanEverTick = true;
PrimaryActorTick.bTickEvenWhenPaused = true;
PrimaryActorTick.TickGroup = TG_PrePhysics;
```



定时器



##### UE4_.uproject文件关联或者默认打开问题

解决办法： 

1. 找到发射器的安装目录，寻找lancher->Engine->Binaries->Win64->UnrealVersionSelector.exe
2. 把UnrealVersionSelector.exe 拷贝到Ue4的版本工程目录，例如UE_4.18->Engine->Binaries->Win64
3. 双击运行UnrealVersionSelector.exe 即可，可能会有延迟，重启一下电脑也可



##### 删除一个指定的C++类

为了从你的项目中删除一个C++类，请遵循以下步骤：

1. 关闭Visual Studio
2. 关闭UE4编辑器
3. 在文件管理器（explorer）中从你的硬盘移除相应的.cpp和.h文件
4. 移除Binaries文件夹中的所有内容
5. 右键点击.uproject文件然后点击生成Visual Studio项目文件（Generate Visual Studio Project Files）
6. 返回到你的正常工作中

如果一个错误信息弹出，告诉你要在启动UE4编辑器的时候重新编译项目，点击“是”。



##### 背景音乐

1. 导入wav格式的音乐，右键-创建cue，得到cue格式文件。

2. 打开cue格式文件的蓝图，选择第一个结点，勾选looping。

3. 打开关卡蓝图，事件BeginPlay连出PlaySound2D，音乐选择对应的cue文件。



##### UI

使用widget创建UI

UI的显示：可以在关卡蓝图，或PlayerController蓝图中添加创建。

关卡的切换：给UI中的按钮添加click事件，调用“打开关卡”。

[官方UI设置教程](https://docs.unrealengine.com/zh-CN/Engine/UMG/QuickStart/index.html)



##### 关卡

1. 事件Begin Play—Play Sound 2D—创建UI控件—Add to Viewport—(Set: Show Mouse Cursor + Get Player Controller)
2. 在世界场景设置中，Game Mode游戏模式覆盖选择游戏模式。



##### 碰撞通道

1. 项目设置—引擎—Collision

2. 创建通道：Object Channels—新建Object通道

3. 创建预设：Preset—新建：对象类型选择刚创建的通道，并设置该通道与其他对象的碰撞响应

4. 给C++类添加碰撞组件：

   ```c++
   // 使用球体代表简单碰撞
   CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
   // 设置碰撞预设
   CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
   // 设置球体的碰撞半径。
   CollisionComponent->InitSphereRadius(15.0f);
   // 将碰撞组件设为根组件。
   RootComponent = CollisionComponent;
   ```

5. 设定游戏中的物体的碰撞通道

6. 在类或蓝图中编写碰撞/重叠事件触发的函数，如修改属性值。



##### 自动曝光

1. 项目工程—正在渲染（rendering）—Default Setting：取消勾选“自动曝光”。
2. 场景中添加：视觉效果—Post Process Volume；
3. 设置其缩放：以覆盖需要的场景；
4. 限定曝光范围：Lens—Exposure: 修改Min EV100和Max EV100。



##### 打包

项目—地图和模式：设置默认的关卡和游戏模式

项目—正在打包：

- project-编译配置：shipping
- packing-创建压缩烘焙包：勾选
- packing-打包版本中要包括的地图列表：添加要打包的关卡.umap