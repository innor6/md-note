jwt三部分构成：

- 协议头
- payload：数据部分
- 签名：通过前两个部分 + 密钥 hash生成

（每一部分用.隔开，可用`echo xxx | base64 -d`解析出来）



状态码：

- 400：http.StatusBadRequest，请求数据是错的
- 401：http.StatusUnauthorized，权限不足
- 422：http.StatusUnprocessableEntity，请求数据不符合格式规范
- 500：http.StatusInternalServerError，服务器内部错误

