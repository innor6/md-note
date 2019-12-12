TCP client

```c++
// 解析ip地址：resolver
asio::ip::tcp::resolver resolver(io_context);
asio::ip::tcp::resolver::query query("www.boost.org", "http");
asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
asio::ip::tcp::resolver::iterator end; // End marker.
while (iter != end)
{
	asio::ip::tcp::endpoint endpoint = *iter++;
	std::cout << endpoint << std::endl;
}

// 发起连接：socket
asio::ip::tcp::socket socket(io_context);
asio::connect(socket, resolver.resolve(query));
//如果已知地址，可以直接socket.connect(endpoint);

/*数据传输*/
```

TCP server

```c++
// 接收连接：acceptor + socket
ip::tcp::endpoint my_endpoint(ip::tcp::v4(), 0); //ip:port
ip::tcp::acceptor acceptor(my_io_context, my_endpoint);
...
ip::tcp::socket socket(my_io_context);
acceptor.accept(socket);

/*数据传输*/
```

timer

```c++
void handler(/*asio::error_code ec*/)
{
    ...
    t.expires_at(timer_.expiry() + asio::chrono::seconds(1)); //延期1s
	t.async_wait(handler);
}

main()
{
	io_context ioc;
	
	steady_timer t(ioc, asio::chrono::seconds(1));
	t.async_wait(handler);
	
	i.run();
}
```

