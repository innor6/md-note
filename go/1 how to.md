##### 工作空间GOPATH

包含bin，pkg，src三个子目录

添加到环境变量

```
$ mkdir $HOME/go
$ export GOPATH=$HOME/go
$ export PATH=$PATH:$GOPATH/bin #安装的可执行文件在这里(GOBIN)
```

设置环境变量？？

```bash
$ go env -w GOBIN=/somewhere/else/bin
$ go env -u GOBIN	#unset
```



##### 基本结构

package：同一目录，一起编译的源文件。是变量、函数的作用域。

module：一起发布的多个package构成module。

repository：

- 根目录包含一个module。
- go.mod声明了module path
- 导入package的语法：module/package（标准库不需要前缀）



##### 创建module

模块路径：'github.com/user/hello'，建议和他的远程仓库url一致

```bash
$ mkdir hello
$ cd hello
$ go mod init github.com/user/hello
go: creating new go.mod: module github.com/user/hello
$ cat go.mod
module example.com/user/hello

go 1.14
```

module文件夹内自动生成了go.mod文件，它声明了模块路径，也是导入该模块内的包时，所用的前缀。



编写源文件：hello.go（内容见下面“使用pacakge”）

go源文件的第一句必须是`package 包名`，执行命令的源文件为`package main`。



##### 构建与安装

```bash
$ go install github.com/user/hello
```

go自动到GOPATH中找对应包进行构建，并安装到GOPATH/bin

如果已经在该目录中，则可以省略路径：`go install`



##### 版本控制（可选）

```bash
$ git init
Initialized empty Git repository in /home/user/hello/.git/
$ git add go.mod hello.go
$ git commit -m "initial commit"
[master (root-commit) 0b4507d] initial commit
 1 file changed, 7 insertion(+)
 create mode 100644 go.mod hello.go
$
```



##### 创建package

在module path下创建一个子目录`$HOME/hello/morestrings`

创建文件`reverse.go`：

```
package morestrings

// 反转字符
func ReverseRunes(s string) string {
	r := []rune(s)
	for i, j := 0, len(r)-1; i < len(r)/2; i, j = i+1, j-1 {
		r[i], r[j] = r[j], r[i]
	}
	return string(r)
}
```

注意：这里函数ReverseRunes**开头大写**，表示它是**exported**的，可被其他包使用。

构建

```bash
$ cd $HOME/hello/morestrings
$ go build
```

因为不是main，不生成可执行文件，只是缓存到本地的build cache中。



##### 使用package

修改`hello.go`文件，导入package：

```
package main

import (
	"fmt"

	"example.com/user/hello/morestrings"
)

func main() {
	fmt.Println(morestrings.ReverseRunes("!oG ,olleH"))
}
```

安装

```bash
$ go install example.com/user/hello
```

使用远程包

如果导入的是远程的package，如"github.com/google/go-cmp/cmp"，则在构建时（go install, go build, or go run）会自动下载，并在`go.mod`中记录它的版本号。

远程模块保存在`GOPATH/pkg/mod`，可用`go clean -modcache`清空。



##### 代码测试

使用 `go test` 命令以及 `testing` 包。

先创建以`_test.go`结尾的文件，其中的函数为`func TestXXX (t *testing.T)`。

测试框架会运行这些函数，如果发现t.Error或t.Fail，则测试失败。

例子：

（检测ReverseRunes输出是否等于预期）

```
package morestrings

import "testing"

func TestReverseRunes(t *testing.T) {
	//测试样例
	cases := []struct {
		in, want string
	}{
		{"Hello, world", "dlrow ,olleH"},
		{"Hello, 世界", "界世 ,olleH"},
		{"", ""},
	}
	//测试
	for _, c := range cases {
		got := ReverseRunes(c.in)
		if got != c.want {
			t.Errorf("ReverseRunes(%q) == %q, want %q", c.in, got, c.want)	//错误信息
		}
	}
}
```

执行命令

```
$ go test
PASS
ok  	example.com/user/morestrings 0.165s
```

