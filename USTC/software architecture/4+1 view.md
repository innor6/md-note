OVERVIEW

“A view represents a partial aspect of  a software architecture that shows specific properties of a software  system”

a software design is a multi-faceted artifact produced by the design  process and generally composed of relatively independent and  orthogonal views.

**Logical View**: object model (OOD). End-user/Functionality

**Process View**: concurrency and synchronization. Integrator / Performance / Scalability

**Physical View**: hardware and distributed. System engineers / Topology / Communications

**Development View**: static organization of development  environment. Programmers / Software management

(The description of an architecture—the decisions made—can be organized  around these four views)

**Use Cases**: illustrated by this fifth view

![4+1view](.\pic\4+1view.png)

## Logical Architecture

Supports the <u>functional  requirements</u>

The system is decomposed into a set of key abstractions

- taken (mostly) from the problem domain, 
- in the form of objects or object  classes.(OOD)

Representing: use the UML :

- class diagrams: classes and their logical relationships (association,  usage, composition, inheritance)
- class templates: focus on each individual class (class operations, key object characteristics)

## Process Architecture

Focuses on some <u>non-functional requirements</u> (such as performance and availability)

Describe in highest level:

- PA is a set of  independently executing logical networks of communicating programs, 
- distributed across a set of hardware resources connected by a LAN  or a WAN
- Multiple logical networks may sharing the same physical  resources.

A process is a grouping of tasks that form an executable unit.

We can distinguish then in communicate:

- Major tasks communicate via a set of well-defined inter-task communication  mechanisms: synchronous and asynchronous message-based communication  services, RPC, event broadcast, etc.

- Minor tasks may communicate by rendezvous or shared memory.

## Development View

Focuses on <u>actual software module</u>(program libraries,  subsystems)

Represent by:

- module and subsystem diagrams
- showing the ‘export’ and  ‘import’ relationships.

takes into  account internal requirements related to:

- the ease of development,
- software management,
- reuse or commonality,
- and to the constraints imposed by the toolset, or the programming  language.

is the Basis for requirement allocation:

- allocation of work,
- cost evaluation and planning,
- monitoring the progress of the project,
- reasoning about software reuse, portability and security.

## Deployment View

Focuses on the <u>non-functional requirements</u>:

- availability, reliability (fault-tolerance), performance (throughput), and  scalability.

use several different physical configurations:

- some for development and testing,
- others for the deployment of the system for various sites or for different  customers.

## Scenarios

The elements in the four views are shown to work together seamlessly by the use of <u>a small set</u> of important scenarios (general use cases).

contains only architecturally significant use cases (whereas the  final use case model contains all the use cases):

- critical use cases, most important to the users 
- use cases that carry the major risks
- use cases that have the most important quality requirements

is an abstraction of the most  important requirements.

is redundant with other views, but:

- is a driver to discover the architectural elements during the architecture
  design as we will describe later 
- is a validation and illustration role after this architecture design is complete,  both on paper and as the starting point for the tests of an architectural prototype.

Derive the logical view.

## Correspondence Between the Views

The various views are not fully orthogonal or independent.

##### From logical to the process view

several important characteristics of the classes of the logical  architecture:

- Autonomy: are the objects active, passive, protected?
- Persistence: are the objects transient , permanent? Do they the failure of a  process or processor?
- Subordination: are the existence or persistence of an object depending on  another object?
- Distribution: are the state or the operations of an object accessible from many  nodes in the physical architecture, from several processes in the process  architecture?

Determine the ‘right’ amount of concurrency and define the  set of processes that are needed:

1. Inside-out: Starting from the logical architecture:

- define agent tasks which multiplex a single thread of control object are  also executed on that same agent;
- several classes that need to be executed in mutual exclusion, or that  require only small amount of processing share a single agent.
- This clustering proceeds until we have reduced the processes to a  reasonably small number that still allows distribution and use of the  physical resources.

2. Outside-in: Starting with the physical architecture:

- identify external stimuli (requests) to the system,
- define client processes to handle the stimuli and servers processes that  only provide services and do not initiate them;
- use the data integrity and serialization constraints of the problem to  define the right set of servers,
- and allocate objects to the client and servers agents;
- identify which objects must be distributed.

##### From logical to development

Collections of closely related classes—class categories—are  grouped into subsystems.

Additional constraints must be considered for the definition of  subsystems.

##### From process to physical

Processes and process groups are mapped onto the available  physical hardware, in various configurations for testing or  deployment.

##### From scenarios to

relate mostly to the logical view: which classes are used

relate to the process view: interactions between objects involve more than one thread of  control.

## Tailoring

Not all software architecture need the full “4+1” views.

Views that are useless can be omitted from the architecture  description, such as

- the physical view, if there is only one processor
- the process view, if  there is only one process or program.
- For very small system, it is even possible that the logical view and the  development view are so similar that they do not require separate  descriptions.
- The scenarios are useful in all circumstances.

# Use Case View

Use Case Model

- illustrates the system’s intended functions (use cases), 
- its  surroundings (actors),
- relationships between the use cases  and actors (use case diagrams).

## Graphical Constructs

Actors:

- interact with the system, but are not part of the system.
- input and receive information to and from the system
- UML: a stickman

Use Cases:

- represent the functionality provided by the system
- sequence of transactions that yields a  measurable result of values 
- UML: an oval with a name inside

Use Case Relationships:

- association: communication between an actor and a use case
- inheritance: between actors
- include: a use cases shared by multiple use cases
- extend: optional behavior, run under certain conditions, run based on actor selection

![Use Case Diagrams](.\pic\Use Case Diagrams.png)

## Textual Description

...

# Logical Architecture

Purpose: specify the <u>functional requirements</u> of the system

Main Artifact: Design Model, gives a concrete description of the functional  behavior of the system. It is derived from the Analysis Model (which is an abstract description).

- class, interaction, and state diagrams
- the subsystems and their interfaces described using package diagrams

## Static Structures

##### Notion of Class

a description of a group of objects with:

- common properties (attributes)
- common behavior (operations)
- common relationships to other objects, and common semantics.



![Notion of Class](.\pic\Notion of Class.png)

##### Notion of Stereotype

- Stereotype (template?)
- Tagged value
- Constraint

![Notion of Stereotype](.\pic\Notion of Stereotype.png)

##### Boundary, Entity, and Control Classes

The Rational Unified Process advocates for finding the classes for a  system by looking for *boundary*, *control*, and *entity* classes.

Entity classes:

- model information and associated behavior that is <u>generally long lived</u>
- may reflect a real-world entity, or may be needed to perform tasks internal  to the system
- are <u>application independent</u>: may be used in more than one application.

Boundary classes:

- handle the <u>communication</u> between the system surroundings and the inside of the system
- can provide the interface to a user or another system

Control classes:

- model <u>sequencing behavior</u> specific to one or more use cases.
- typically are <u>application-dependent</u> classes.

##### Relationships

- Association   <---------
- Dependency <- - - - - 
- Realization   ◁ - - - - - 
- Aggregation  ◇---------
- Inheritance  ◁---------

![Relationships_association](.\pic\Relationships_association.png) 

##### Class Diagram

##### Object Diagram

##### Package Diagrams