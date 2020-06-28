每个socket自带一个连接队列，以及一个接收缓冲区、发送缓冲区



listen之后，客户端调用connect，内核会自动完成三次握手，进入某个sockfd的连接队列，等待被accept提取。



write/send只是把数据写入该sockfd的IO缓冲区就返回了，不代表真的发出，随后由内核控制将数据发出

write/send在向发送缓冲区写入时：

- 如果缓冲区已满，阻塞；
- 如果内核正在发送缓冲区中数据，阻塞；
- 如果缓冲区太小，则分多次写入后再返回



##### socket()

```c
#include <sys/types.h> 
#include <sys/socket.h> 
int socket(int af, int type, int protocol);
```

返回值：正常时返回Socket 描述符；否则，返回-1 ，错误状态在全局变量errno中。



##### bind()

```c
#include <sys/types.h> 
#include <sys/socket.h> 
int bind(int sockfd, struct sockaddr *my_addr, int addrlen);  
```

返回值：正常时返回0，否则返回-1 ，同时errno是系统错误码。

注：sockaddr*是被强制转型后的通用格式。



转换

```
字节顺序：大端：低位字节在内存的高地址端，如0x0102，先存01，再存02。
ntohs()  ：将一个无符号短整形数从网络字节顺序转换为主机
ntohl()   ：将一个无符号长整形数从网络字节顺序转换为主机字节顺序。
htons()  ：将主机的无符号短整形数转换成网络字节顺序
htonl()  ：将主机的无符号长整形数转换成网络字节顺序
地址转换
inet_addr()：将一个点间隔地址转换成一个in_addr。
inet_ntoa()   ：将网络地址转换成“.”点隔的字符串格式
inet_pton()   ： 将点分十进制转换为整数
atoi() ：array to integer将字符串转换为整形数数
```



##### listen()

```c
#include <sys/socket.h> 
int listen(int sockfd, int backlog);   
```

返回值： 正常时返回0，否则返回-1 ，同时errno是系统错误码。

backlog：是连接请求暂存队列的长度，满了客户端会收到ECONNREFUSED错误。



##### accept()

```c
#include <sys/types.h> 
#include <sys/socket.h> 
int accept(int sockfd, struct sockaddr *addr, int *addrlen);   
```

返回值： 正常时返回新连接的sockfd，否则返回-1 。

addrlen：在调用 accept()之前，`*addrlen` 必须被设置为 addr 数据结构的合法长度。在accept()返回之后，`*addrlen` 中是对方地址信息的长度。 



##### connect()

```c
#include <sys/types.h> 
#include <sys/socket.h> 
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen ); 
```

返回值：正常时返回新连接的sockfd，否则返回-1 。



##### close()

```c
#include <unistd.h> 
int close(int fd); 
```

返回值： 正常时返回0，-1 表示出错。

注意：close操作只是使相应socket描述字的引用计数-1，只有当引用计数为0的时候，才会触发TCP客户端向服务器发送终止连接请求。



read/write

send/recv