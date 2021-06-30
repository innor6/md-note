# fun项目设计



# IM

### websocekt

（见gorilla/websocket）

client:

- （进入房间）请求同步历史消息 syn(start_index, end_index = 0, type = room, roomid, ) ([]msg)
- 发送消息 send(msg)

server:
- （一旦有用户send，向所有人push）推送新消息 push(msg)



### 数据存储

房间：

用户（连接的、断开连接的）[]menber{ user, socketid, state }

聊天记录 ：[]chatLog{ index, msg, userid, time }

