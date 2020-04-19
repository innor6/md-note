# 流程

1. 从服务器端（getAccessToken）获取一个唯一性的token;

2. 前端对token进行随机性拆分及md5加密,产生签名（保存在本地存储中）;

   ```
   uni.setStorage({
   	key:"sign",
   	data:sign
   });
   ```

3. 前端在与后端进行交互时传递签名;

4. 后端接收数据是验证签名;



# 前端

commons文件夹内创建

- `md5.js`加密
- `sign.js`签名

http://www.hcoder.net/tutorials/info_1376.html



##### sign模块签名过程

1. 判断是否包含uni变量，若是不包含uni的环境，则函数直接返回，不进行签名过程；
2. 请求服务器获取一个临时token
3. 根据token的`时间戳+值`进行md5加密，生成签名
4. 将签名记录在本地



# 使用sign

1. 在scrpit开头引入sign.js：

   ```
   <script>
       var signModel = require('../../commons/sign.js');
   ```

2. 生成签名，保存在数据缓存中（如在login页面的onLoad开头）：

   ```
   signModel.sign('网址');
   ```

3. 获取已生成的签名变量

   场景：准备向服务器提交登录表单时，把sign也添加到表单中。
   
   ```
var sign = uni.getStorageSync('sign');
   uni.request() {
   	data: {
   		sign : sign,
   	}
   }
   ```
   
   
   
   





# 服务端

##### getAccessToken

用户请求一个token，则生成token和时间戳，放入数据库，并返回给用户。



##### checkSign

用户提交表单，如登录时，先调用该函数。

1. 若表单不含sign属性，直接返回错误；

2. 然后对sign校验
   - 失败返回错误
   - 验证成功，则把数据库中的token删除，即一个token只能用一次





# 数据库

数据库保存了accessToken，更好的方式是 redis 或 memcache，可以设置变量有效期并能自动失效！

（有些token也许用户获取后没有使用，需要定期删除）

只包含两个属性：

- token：唯一随机数
- time：时间戳

```
DROP TABLE IF EXISTS `yuedu_access_tokens`;
CREATE TABLE `yuedu_access_tokens` (
  `token` varchar(30) NOT NULL,
  `time` int(11) DEFAULT NULL,
  PRIMARY KEY (`token`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4;
```

