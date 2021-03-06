发送数据时，压缩数据与发送数据，流水线并行，可以提高速率，代价是使用了更多CPU资源。



##### 阻塞IO的死锁

（echo服务器，客户端发完全部数据后才开始接收数据）

1. 问题：客户端发送的数据量 > 服务端的TCP接收缓冲区大小
2. 服务器接收缓冲区填满后，<u>客户端阻塞</u>在send上
3. echo服务器向客户端发回数据
4. 由于客户被阻塞，没有调用recv，客户端的TCP接收缓冲区一直积累数据
5. 客户端接收缓冲区填满后，<u>服务器也阻塞</u>在send上
6. 形成死锁

查看阻塞现象：

```shell
#查看服务器与客户端的连接状态
netstat -tpn | grep '端口号' 
#Recv-Q 和 Send-Q 代表了接收与发送缓冲区中的数据大小

#查看本机设定的tcp接收/发送缓冲区大小（tcp_rmem, tcp_wmem）
sysctl -A | grep tcp.*mem 
```

解决方法：应用层协议设计：

1. 客户端先发送header告知服务器要发生数据的大小，再发送payload
2. 服务器应该根据header来分配接收缓冲区，再接收payload
3. 服务器向客户端发送时同理。



##### TCP的自连接

客户端对本地端口发起连接，即使没有服务器在侦听，也能建立连接(ESTABLISHED)

```shell
#查看本地端口号(ip_local_port_range)
sysctl -A | grep range
```

原因：

TCP的同时打开功能，当客户端发送一个SYN时，由于内核发现目标端口上有应用程序在，因此不返回RST，而是建立连接。

解决方案 ：

一般网络库在建立连接后，就会检查是否自连接（getsockname/getpeername），若是自连接则释放掉该连接sock。









##### 时间服务

系统调用

gettimeofday()：1us

clock_gettime()：1ns

NTP

- 测量客户端/服务端的发送/接收4个时间点，得时间误差：[(T1+T4)-(T2+T3)]/2，
- 通过反馈循环连续地调整offset和frequency
- 避免时间、频率的跳变（时域的跳变引起频域的剧烈震荡）
- 只和固定的服务器进行多次校正

**分布式系统的时间**

- Time, clocks and the Ordering of Events in a Distributed system. by Leslie Lamport
- Rethinking Time in Distributed Systems. by Paul Borrill



##### UDP  vs TCP

UDP：无连接、不可靠的、数据包协议

TCP：面向连接、可靠的、字节流协议

TCP有流量控制和拥塞控制。

**并发**

TCP：线程不安全，因此服务器一般一个客户分配一个sockfd

UDP：线程安全，服务器只需一个sockfd即可



##### TCP 连接的的正确关闭

问题：

1. 服务端的 write 的返回只表示数据被写入到发送缓冲区，而不能保证对端是否已经收到；
2. 同理，close调用：直接关闭套接字，而不是发送完缓冲区术数据后才关闭套接字；
3. 服务器执行完 wirte， 随后调用 close，如果此时接收缓冲区有数据未读，直接close，会发送一个RST，强行断开连接，如果此时TCP发送缓冲区还有数据，则会导致待发送的数据丢失。

解决方案，发送端：

1. 发送端发送完数据后，shutdown(write)
2. 读系统的接收缓冲区，直至read返回0（即等待客户端关闭）
3. 关闭套接字，close

接收端的情况：

1. 服务端的shutdown，发送一个FIN，告知接收端数据已发完全部数据，read返回0（EOF）
2. 此时可以正确关闭连接，close，导致服务端read返回0，告知服务器接收端已经接收到全部数据。

注意：

1. 这种交互建立在接收端能正确处理服务器的数据上。接收端可能永远不close，导致发送端read阻塞，因此发送端的read可以设一个超时。
2. 此处是依赖FIN来通知数据的收发完毕。更好的方案：预先通知要发送的数据大小，从而保证对端可以正确读取正确数量的字节数。



##### 在并发 TCP 服务中忽略SIGPIPE

默认行为：关闭进程

服务器与某个客户通讯时的SIGPIPE，会导致服务器进程关闭，影响其他客户。

因此在服务器启动时忽略SIGPIPE信号。

但此时要自己检查任何的输出函数（write，printf）的返回值，并正确处理（exit）。



##### Nagle算法，TCP_NODELAY

目的：通过累计多个请求，单次发送，减少网络中的TCP分节、降低网络负担。

算法：每次发完一个TCP分节后，直到收到ACK后，或累积的数据量超过MSS，才继续发下一个TCP分节。

缺点：两次数据的发送间隔一个RTT，延迟会变高，影响请求流水线。

解决办法：

1. 建立缓冲区，将多个发送请求合并发送；
2. 禁用：TCP_NODELAY



##### TCP三部曲

1. SO_REUSEADDR

   TCP可以在崩溃、被杀死后迅速重启（TIME_WAIT状态）

2. 忽略 SIGPIPE

3. TCP_NODELAY



多线程：适合并发连接数较少、线程较廉价时。它节省了等待IO就绪的时间。

IO复用：事件驱动，reactor，同步。

通常与非阻塞IO一起使用，因为在进行阻塞IO操作时可能会“永久”阻塞：

1. accept 使得 listenfd 就绪，却会阻塞读，但客户此时可能会关闭连接；
2. 数据到达，fd就绪，但是可能由于错误的校验和，丢弃数据，阻塞读；
3. 还有其他的fd虚假的可读的情形。

非阻塞IO容易出现 short write / short read，

