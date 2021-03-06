前端如何判断login登录状态：检查返回代码 res.data.code 是否为 401

```
if (res.data.code == 401) {
    uni.showToast({title:'请登录', icon:'none'})
    setTimeout(function(){uni.navigateTo({url:'/pages/login/login'})}, 1000); // 跳转登录页面
    return
}
```



库存问题：

提交订单时允许超过库存

调用支付时，统计数据库中当日已付款的商品数量，检查库存，如果超出库存，则返回422



# 数据表设计



用户、订单、商品信息、公告

**用户**

- （id、注册日期）
- 账号、密码
- 昵称、头像、openid

```go
type User struct {
	gorm.Model
    Openid		string `gorm:"type:varchar(100); unique"`
	Nickname	string `gorm:"type:varchar(50)"`
	Avatar		string `gorm:"type:varchar(200)"`
}
```

**订单**

- （订单号id、创建日期）
- 订单状态（待支付/待发货/待接收/已接收/取消）
- 订单发起人user
- 商品列表（商品id、数量、单价）
- 总价
- 预定发货日期、
- 快递地址（省、市、区）、联系手机
- 快递单号
- 

```go
type Order struct {
	gorm.Model
    
    // 发起的用户
    user
    
    // 商品列表（stringfy的）
    Products[] {
        id	//1-6 羊肉、带骨羊肉、羊爪、羊肚
        amount
        price//单价
    }
    TotalPrice//总价
    
    // 预定的发货日期
    SendDate
    
    // 收件人信息
    Receiver	64B
    Telephone	32B
    Province	64B
    City		64B
    Area		64B
    Address		512B

    // 
    PrepayId
    
    // 快递单号
    WayBillNo

    // 订单状态
	OrderStatus	string
}
```



**商品信息**

- （商品id、创建日期）
- 商品名、价格
- 文字说明、图片说明
- 状态：能否购买





# 接口文档

##### 登录

```
POST /liuling/api/v1/auth/register（login）
{
	code:
	nickname:
	avatar:
}

响应
{
	status:
	token:
}
```



##### 商品信息

创建订单前，前端需要获取一些数据。

```
GET /liuling/api/v1/orderdata
响应
{
	//可选的发货日期
	date_list:	["2020-08-17","2020-08-18","2020-08-19"]
	//商品信息
	products_list: [
		{
			id:
			name:
			weight:	//重量：克
			price:	//单价
		},
		{},{},...
	]
}

//管理员可以设置这些数据
POST 

```



##### 创建订单

```
POST /liuling/api/v1/orders
{
	products: [		//商品列表
		{
			id:
			amount:
		},{},{},...
	],
	total_price:	//总价
	send_date:		//预定发货日期
	
	// 收件人信息
    receiver	64B/4=16
    telephone	32B/4=8
    province	64B
    city		64B
    county		64B
    detail		512B/4=128
	
	// 备注信息
	meomo:		512B/4=128
	
	
}
```







# 后端程序流程

1. router分发HTTP请求到控制器
2. 控制器：将请求体binding到结构体，检查参数，处理，返回结果（这些可以封装成一个service，直接让控制器调用service）
3. 处理时，如果需要访问数据库，则用到model结构体
4. 返回结果时，将model结构体转换为dto结构体（写一个从model到dto的转换方法）



# 需求分析

1. 用户注册/登录/登出
2. 用户创建/查看/修改（取消）订单
3. 管理员查看/修改（取消）订单





```
关于客服
1.有问题可以咨询店主，微信号为liulingyangrou（刘伶羊肉的拼音）。
2.平时卖羊肉较忙，没空看手机，可能无法及时回复。

购买说明
1.我们的羊肉是发货前一天新鲜做出来，放冰箱冻好，然后采用冰袋+泡沫箱包装后发货的。
2.付款前请仔细核对收件人信息。
3.付款完成后，订单状态变为“待发货”，我们将会在预定日期发货。
4.未支付的订单可在“订单列表”中进行支付。
5.若收件人信息填写有误、支付后订单状态仍为“未付款”等，请联系客服。

快递说明：
1.快递采用顺丰生鲜速配，不包邮。
2.通常在发货的次日可以到货。
3.可在订单详情页中查看快递单号，请自行关注快递信息.
4.节假日等特殊情况可能延误，一旦快递发出，具体到货时间我们无法保证。
5.快递总重量不能超过5kg。
6.不支持货到付款。

价格说明：
1.订单的总价格由：羊肉费、快递费，以及6元的包装费（冰袋+泡沫箱）构成。
2.由于是我们自己做的小程序，邮费计算可能有误，如果误差较大，我们会联系您，多退少补。



```









拆骨羊肉(无骨)羊肉，每斤95，羊肚每斤95.带骨羊肉每斤85.冻羊肉每斤80元，冻羊杂每份30元，羊头每份50元，心肺，每份20元，肝每份20元，羊爪大的每只20元，略小的每只15元，羊肠每斤60元，羊脑每份15元，羊鞭每条15元，羊蛋每幅50元，礼盒装拆骨羊肉中份的150元，大份的200元。带骨羊肉礼盒装中份130，大份礼盒装180元。简装的羊肉，用普通加厚保鲜袋装，带骨的每份100元，拆骨羊肉每份100元，拆骨羊肉内可以拼四分之一羊肚，每份100元。羊肚每份50元。

```
拆骨羊肉(无骨)羊肉，每斤95，
羊肚每斤95.
带骨羊肉每斤85.
冻羊羔每斤80元，
冻羊杂每份30元，
羊头每份50元，
心肺，每份20元，？？？？
肝每份20元，
羊爪大的每只20元，略小的每只15元，
羊肠每斤60元，
羊脑每份15元，
羊鞭每条15元，
羊蛋每幅50元，

简装:
带骨羊肉每份100元，
拆骨羊肉每份100元，
简装的羊肉，用普通加厚保鲜袋装，拆骨羊肉内可以拼四分之一羊肚，每份100元。羊肚每份50元。
(拆骨羊肉拼羊肚每份100元,羊肚每份50元，????)

礼盒:
拆骨羊肉每盒150元，
带骨羊肉每盒130元
```



快递说明

```
所有快递，全部顺丰生鲜速配，另加6元的冰袋泡沫箱由本店提供。江浙沪一份羊肉快递费20元，两份也是20元。外省的按份量计算价格，如北京，广东每份30元，200元的羊肉，快递费33(运费)十6(包装)十2(生鲜)，因为每份羊肉一斤多，加上汤汁的份量，冰袋份量接近二斤了。

所有快递，全部采用顺丰生鲜速配。
另加6元的冰袋泡沫箱由本店提供。

快递费的计算公式为：
快递费（运费）+6（包装费）+2（生鲜速配）
具体价格在下单时老板娘会说明的。

一般可以在发货的次日到货。
不支持货到付款。
```

食用说明

```
我们的羊肉是现杀，现烧，现做的，
三天之内吃可以放(冰箱)保鲜。如果放速冻，可以放三至四个月，吃之前，放保鲜自然解冻，加热会快点。
加热用微波炉，或蒸，四至五分钟，带骨羊肉蒸好后，可以放至锅里大火收汁，出锅时，撒上大蒜叶，老姜，辣椒即可。
```

接单说明

```
上午8:00至11:00，当天发货
下午13:00至16:00，晚上19:00到22:00，隔天发货
```





**数据库设计**



**用户数据表**

id：自增id

openid

name

avatar

regsiter_time



```mysql
CREATE TABLE member (
	uid INT(11) NOT NULL AUTO_INCREMENT COMMENT '用户id',
    openid VARCHAR(100) NOT NULL COMMENT '微信openid',
	name VARCHAR(50) NOT NULL COMMENT '用户昵称',
	avatar VARCHAR(200) NOT NULL COMMENT '用户头像',
	regsiter_time DATETIME NOT NULL COMMENT '用户注册时间',
	PRIMARY KEY (uid),
	UNIQUE KEY (openid)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4;
```





- 