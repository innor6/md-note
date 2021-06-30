文档：

http://nginx.org/en/docs/beginners_guide.html#proxy



##### 安装

```
sudo apt-get install nginx
```



##### 启动、关闭

```
sudo nginx
sudo nginx -s reload/stop/quit
```



##### 日志信息

```
tail /var/log/nginx/access.log
tail /var/log/nginx/error.log
```



##### 配置文件

```
sudo vim /etc/nginx/nginx.conf
```

修改文件第一行的用户（否则可能403无权限打开文件）

```
user ubuntu; # 或者root
```

另一个配置文件

```
sudo vim /etc/nginx/sites-enabled/default
```



##### 路径匹配优先级

1. 正则表达式匹配
2. 最长前缀匹配
3. 根路径



### 静态文件服务

打开配置文件

```
sudo vim /etc/nginx/sites-enabled/default
```

添加路径映射：

将 `.../images/xx.jpg` 映射到 `/home/ubuntu/images/xx.jpg`：

```
server {
	listen 80;
	
	# root命令的写法
	location /images/ {
		root /home/ubuntu;
	}
	
	# alias命令的写法，与上面命令的作用相同
	location /images/ {
		alias /home/ubuntu/images/;
	}
}
```



### 反向代理

使用 `proxy_pass` 命令，将 `...:80/fun/` 打到 `...:8080/fun/`

```
location /fun/ {
	proxy_pass http://localhost:8080/fun/;
	# 下面加了四个请求头，用来传递客户端的真实ip
    proxy_set_header Host $http_host;
    proxy_set_header X-Real-IP $remote_addr;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
}
```

- 若proxy_pass命令后的地址不包含具体路径，则使用原始请求的路径



[WebSocket](http://nginx.org/en/docs/http/websocket.html) proxying requires special configuration and is supported since version 1.3.13.



# 一个完整的配置示例

```bash
server {
		# TLS
        listen 443 ssl default_server;
        listen [::]:443 ssl default_server;
        server_name _;
        ssl_certificate /home/ubuntu/www/tls/1_www.innor.fun_bundle.crt;
        ssl_certificate_key /home/ubuntu/www/tls/2_www.innor.fun.key;

		# 首页
        root /home/ubuntu/www/html;
        index index.html index.htm index.nginx-debian.html;

        location / {
                try_files $uri $uri/ =404;
        }

		# 反向代理
        location /fun/ {
        		# z
                proxy_pass http://localhost:8080;
                # 下面加了四个请求头，用来传递客户端的真实ip
                proxy_set_header Host $http_host;
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header X-Forwarded-Proto $scheme;
        }

        location /liuling/ {
                proxy_pass http://localhost:8081;
                proxy_set_header Host $http_host;
                proxy_set_header X-Real-IP $remote_addr;
                proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
                proxy_set_header X-Forwarded-Proto $scheme;
        }

		# 静态文件
        location /static/ {
                alias /home/ubuntu/www/static/;
        }
}
```

