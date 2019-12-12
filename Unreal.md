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

