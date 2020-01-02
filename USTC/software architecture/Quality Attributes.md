# Quality Attributes

three classes:

- Qualities of the system: availability, modifiability,  performance, security, testability, and usability.

- Business qualities: (such as time to market) that are affected by the  architecture.

- Architecture qualities: such as conceptual integrity, that are about the  architecture itself although they indirectly affect other qualities, such as  modifiability.

##### Quality Attribute Scenarios

- Source of stimulus

- Stimulus

- Environment

- Artifact

- Response

- Response measure



### Availability

——concerned with <u>system failure</u>.

Stimulus: omission, crash, timing, response

Response: record, notify, continued, disable, be unavailable

##### tactics

- fault detection
  - ping/echo
  - heartbeat
  - exceptions
- fault recovery
  - Active redundancy (hot restart, fast!), 多个组件同时运行，只使用一个组件的返回结果
  - Passive redundancy (warm restart/dual redundancy/triple redundancy), 周期性地备份
  - Spare，在备用组件上恢复到保存的checkpoint。
- fault repair
  - shadow operation
  - state  resynchronization
  - checkpoint/rollback
- ­fault prevention
  - Removal from service
  - Transactions
  - Process monitor



### Modifiability

——about the cost of change. (what can and when?)

goal:
controlling  the time and cost to  implement, test, and deploy changes

##### tactics

- localize modifications（减少被直接影响的模块数，模块设计）
  - maintain semantic coherence
  - anticipate expected changes
  - generalize the module
  - limit possible options
- prevent the ripple effect（减少间接修改，依赖关系）
  - hide information
  - maintain existing interfaces
  - restrict communication paths
  - use an intermediary
- defer binding time（控制部署时间与费用）
  - Runtime registration
  - Configuration Files  
  - Polymorphism 
  - Component replacement 
  - Adherence 

### Security

—— system's ability to resist  unauthorized usage.

不可否认、保密、完整、保证、可用、审计。

##### tactics:

- resisting attacks
  - Authenticate users.
  - Authorize users
  - Maintain data confidentiality（加密）
  - Maintain integrity（校验和）
  - Limit exposure
  - Limit access（防火墙）
- detecting attacks
  - Intrusion detection
- recovering from  attacks
  - restoration
  - audit trail

### Performance

—— is about timing

在时间限制内生成响应。

1. latency
2. deadlines in processing
3. throughput
4. jitter of the response
5. miss rate
6. data loss

##### tactics:

- resource demand
- resource management
- resource  arbitration

### Testability

—— the ease in discovering faults 

Response: observability & controllability

##### tactics:

- manage input/output
  - Record/playback.
  - Separate interface from implementation.
  - Specialize access routes/interfaces.
- internal monitoring
  - Built­-in monitors



### Usability

—— how easy it is for the user to accomplish a desired task 

1. Learning system features.
2. Using a system efficiently.
3. Minimizing the impact of errors.
4. Adapting the system to user needs.
5. Increasing confidence and satisfaction.

##### tactics:

- Separate user interface (MVC, PAC)
- support user initiative (cancel, undo, aggregate)
- support system initiative (user model, system model, task model)