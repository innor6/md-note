[lab1](https://pdos.csail.mit.edu/6.824/labs/lab-mr.html)

步骤

1. mrmaster调用makemaster，传入文件名，R的数量，

   - makemaster创建一个master结构m，存储数据
   - 对m调用server，启动RPC服务

2. worker通过RPC注册

3. **Map Phase**

   

   master记录该空闲worker，如果有任务则：（创建线程？）

   - 回复一个任务：类型（map/reduce）、文件地址
   - 设定超时时间
   - 检查任务完成

   worker收到任务

   - 读取文件
   - 执行map_func
   - 写出结果

   如何通知服务器任务完成？，并返回r个文件地址

4. **Reduce Phase**

   master创建多个线程

   - 向worker分配任务：类型（map/reduce）、文件地址
   - 设定超时时间
   - 检查任务完成

   worker收到任务，读取文件，执行reduce_func，写出结果，通过RPC通知服务器任务完成，并返回r个文件地址

# Your job 

implement a distributed MapReduce, consisting of two programs, the master and the worker. 

 just one master process, one or more worker processes executing in parallel.

for this lab you'll run them all on a single machine. 

- The workers will talk to the master via <u>RPC</u>.
  - Each worker process will ask the master for a task, 
  - read the task's input from one or more files, 
  - execute the task, 
  - and write the task's output to one or more files. 
- The master 
  - should notice if a worker hasn't completed its task in a reasonable amount of <u>time</u> (for this lab, use <u>ten seconds</u>), 
  - and give the <u>same task</u> to a different worker.

We have given you a little code to start you off. The "main" routines for the master and worker are in `main/mrmaster.go` and `main/mrworker.go`; don't change these files. 

- You should put your implementation in `mr/master.go`, `mr/worker.go`, and `mr/rpc.go`.



# RUN

First, make sure the word-count plugin is freshly built:

```
$ go build -buildmode=plugin ../mrapps/wc.go
```

In the `main`，run the master

```
$ rm mr-out*
$ go run mrmaster.go pg-*.txt
```

The `pg-*.txt` are the input files; each file corresponds to one "split", and is the input to one Map task.

In one or more other windows, run some workers:

```
$ go run mrworker.go wc.so
```

# TEST

test script in `main/test-mr.sh`. 

The tests check that 

- the `wc` and `indexer` MapReduce applications produce the correct output when given the `pg-xxx.txt` files as input. 
- the Map and Reduce tasks in parallel, 
- recovers from workers that crash while running tasks.

```
$ cd ~/6.824/src/main
$ sh test-mr.sh
```

You'll also see some errors from the Go RPC package that look like

```
2019/12/16 13:27:09 rpc.Register: method "Done" has 1 input parameters; needs exactly three
```

Ignore these messages.



# RULES

# HINTS