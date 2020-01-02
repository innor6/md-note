### Attribute Driven Design(ADD)

A methods to design an architecture to satisfy both quality & functional requirements

recursive <u>decomposition</u> process on the quality attributes 

input: requirements (use cases) & constraints

steps

1. Choose the architectural drivers from the concrete scenarios
2. Choose an architectural pattern that satisfies the architectural drivers 
3. Instantiate modules 
4. Define interfaces of the child modules
5. refine use cases and quality scenarios
   1. A set of use cases
   2. An interface
   3. Quality scenarios
   4. A collection of constraints

The architecture provides a guide as to the  <u>implemented order</u>: First
implement the software that deals with the <u>execution</u> and <u>interaction</u> of
architectural components; then Add some simple functions.

### Architecture Modeling

- Clarify Design Intent

- Provide Analysis for Design

- Improve maintainability

- Answer Difficult Questions

##### Architecture includes：

- Components:

  •e.g.: filters, databases, objects, clients/servers

- Connectors:

  e.g.: procedure call, pipes, event broadcast

- Properties:

  e.g.: signatures, pre/post conds, RT specs

### Architectural Styles

An architectural style is a named collection of architectural  design decisions 

- lare applicable in a given development context

- lconstrain architectural design decisions that are specific  to a particular system within that context

- lelicit beneficial qualities in each resulting system

##### Benefits

Design reuse

​	Well-understood solutions applied to new problems

Code reuse

​	Shared implementations of invariant aspects of a style

Understandability of system organization

​	A phrase such as “client-server” conveys a lot of information

Interoperability

​	Supported by style standardization

Style-specific analyses

​	Enabled by the constrained design space

Visualizations

​	Style-specific depictions matching engineers’ mental models

##### Styles

- Data-flow styles
  - Pipe and filter
  - Batch sequential

- Data-centered architectures 
  - blackboard
  - repository
- layer architectures 
  - Abstraction layer architectures
  - N-tier architectures 
- Notification architectures 
  - publish/subscribe
  - point-to-point
  - Event based
- Network-Centred Style
  - Client-Server
  - Peer to peer

- Remote Invocation Architectures
  - Web services
  - Broker
- Interpreters
- Interceptor
- GUI Architectures (Interactive )
  - Model-­‐‑View­‐‑‐Controller
  - Presentation-­‐‑Abstraction-­‐‑Control
- Adaptable Architectures 
  - micro-­‐‑kernel
  - reflection
- Transaction-Processing Architectures
- Others
  - process control
  - rule-­‐‑based
- Heterogeneous   Architectures