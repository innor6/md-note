创建文件：touch file.c

打开文件：vim ./test.c

编译：`gcc ./test.c -o b.out`（-o选项指定生成名字为b.out，也可以不加.out后缀；若编译c++则把gcc改为g++即可 ）

运行：./b.out



vim:

进入输入模式：i（esc退出）

# 添加超级用户权限

给普通用户赋予`sudo`权限。

1. 切换至`root`用户

   ```
   $ su -root
   ```

2. 修改/etc/sudoers文件权限（可用`ls -l`查看权限）

   ```
   $ chmod 777 /etc/sudoers
   ```

3. 用`vi`编辑/etc/sudoers文件

   ```
   $ vi /etc/sudoers
   ```

   在`root    ALL=(ALL:ALL)ALL`这一行下面，添加：

   `innor    ALL=(ALL)ALL`

   保存退出（`:wq`）。

4. 改回/etc/sudoers文件权限，退出root用户

   ```
   $ chmod 440 /etc/suders
   $ exit
   ```

# 更新源

```
$ sudo vim /etc/apt/sources.list
```

添加

```
deb http://mirrors.ustc.edu.cn/debian/ buster mian
deb-src http://mirrors.ustc.edu.cn/debian/ buster mian
```



# 添加字体

1. 下载字体tff文件
2. 在`/usr/share/fonts`下新建custom目录
3. 修改权限`chmod 755 custom`
4. 把tff文件放入文件夹中
5. `sudo fc-cache -f -v`完成



# 软件包安装

##### net-tools

（netstat, arp, ifconfig, netstat, rarp, nameif, route）

```
apt-get install net-tools
```

##### go

- 下载

  ```
  wget https://dl.google.com/go/go1.14.1.linux-amd64.tar.gz
  ```

- 校验（2f49e...）

  ```
  sha256sum go1.14.1.linux-amd64.tar.gz
  ```

- 解压到`/usr/local`

  ```
  sudo tar -xzvf go1.14.1.linux-amd64.tar.gz -C /usr/local
  ```

- 设置环境变量

  ```
  sudo vim /etc/profile
  ```

  末尾添加

  ```
  export GOROOT=/usr/local/go
  export GOPATH=$HOME/go
  export PATH=$PATH:$GOROOT/bin:$GOPATH/bin
  ```

  在当前终端应用（完全应用需要重新登录）

  ```
  source /etc/profile
  ```

- 查看版本号，以测试安装成功

  ```
  go version
  ```

  
  
- 创建工作空间，如下：（好像不用）

  ```
  go/
  	bin/	# 可执行命令
  	pkg/	# 包对象
  	src/	# 源码
  ```

  



## c/c++编译

1. GCC编译环境的安装：

   `apt-get install gcc`

   `apt-get install g++`

2. 配置VIM配置编辑环境：

   1. `apt-get install vim`
   2. 编辑VIM的配置文件

   ```
   sudo vim /etc/vim/vimrc
   ```

   末尾加上（语法高亮显示，自动缩进，显示行号，缩进4格）：

   ```
   syntax on
   set autoindent
   set cindent
   set nu
   set tabstop=4
   ```

3. 编译：

   ```
   gcc hello.c -o file //-o后面接要生成的可执行文件名字（会自动生成a.out文件）
   ```
   
   编译多个文件：
   
   ```
   gcc f1.c f2.c -o file //同时编译f1和f2
   ```
   
   UNP代码编译（[UNIX网络编程之一：代码环境搭建](https://blog.csdn.net/u013457167/article/details/78078187)）：

   ```
   gcc file.c -o file -lunp
   ```











## CMAKE

安装：`apt-get install cmake`

官方教程：[CMake Tutorial](https://cmake.org/cmake/help/v3.16/guide/tutorial/index.html)

### 格式

编写CMakeLists.txt（不区分大小写）

```
# 可省略，写自己所用的版本
cmake_minimum_required(VERSION 3.10)

# 项目名称、版本号
project(Tutorial VERSION 1.0)

# 声明C++标准，这里为C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 生成一个头文件用于将CMake设置传递给源代码（如:版本号、可选库）
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 子目录（子目录也要有CMakeLists.txt，这里是库目录）
add_subdirectory(MathFunctions)

# 执行文件
add_executable(Tutorial tutorial.cxx) 

# 链接库目录
target_link_libraries(Tutorial PUBLIC MathFunctions)

# 包含目录(头文件、库目录)
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}" //configure_file文件目录
                          )
```



条件编译版本：

```
# 可省略，写自己所用的版本
cmake_minimum_required(VERSION 3.10)

# 项目名称、版本号
project(Tutorial VERSION 1.0)

# 声明C++标准，这里为C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

### 可选库（必须在configure_file之前）
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# 生成一个头文件用于将CMake设置传递给源代码（如:版本号、可选库）
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 子目录（子目录也要有CMakeLists.txt）
add_subdirectory(MathFunctions)
### 包含可选库目录
if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
endif()

# 执行文件
add_executable(Tutorial tutorial.cxx) 

# 链接库目录
target_link_libraries(Tutorial PUBLIC MathFunctions)
### 链接可选的库目录
target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS})

# 包含目录(头文件、库目录)
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}" //configure_file文件目录
                          )
```





##### 配置头文件

在源代码目录中创建`TutorialConfig.h.in`文件，内容如下：

```c++
// 一些CMake的配置信息：版本号、是否包含MathFunctions库
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
#cmakedefine USE_MYMATH
```

CMake会自动生成对应的头文件（见CMakeList.txt第3行），修改cpp源代码，令其包含头文件`TutorialConfig.h`，就可以获得配置信息：

```c++
// 在cpp中输出版本号
if (argc < 2) {
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;
    std::cout << "Usage: " << argv[0] << " number" << std::endl;
    return 1;
  }

// 可选库，是否包含MathFunctions库
#ifdef USE_MYMATH
#  include "MathFunctions.h"
#endif
// 根据是否包含MathFunctions库来决定代码
#ifdef USE_MYMATH
  const double outputValue = mysqrt(inputValue);
#else
  const double outputValue = sqrt(inputValue);
#endif
```

##### 库

在库（librariy）所在的文件夹编写`CMakeLists.txt`（这里假设库目录是源代码目录的子目录，且库的源代码名为`mysqrt.cxx`）：

```
add_library(MathFunctions mysqrt.cxx)

# 声明使用依赖INTERFACE,即链接到该库者必须包含当前目录
target_include_directories(MathFunctions
          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
          )
```



### 构建

创建一个`Step1_build`文件夹，命令行：

```
$ mkdir Step1_build
$ cd Step1_build
$ cmake ../Step1 //CMakeLists.txt所在文件夹
$ cmake --build .
```

