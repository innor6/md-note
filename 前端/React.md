## 函数组件

如果你想写的组件只包含一个 `render` 方法，并且不包含 state，那么使用**函数组件**就会更简单：

```js
// 使用props传递属性
function Square(props) {
  return (
    <button className="square" onClick={props.onClick}>
      {props.value}
    </button>
  );
}

// 给组件传props
renderSquare(i) {
	return (
        <Square
        	value={this.state.squares[i]}
			onClick={() => this.handleClick(i)}
		/>
    );
}
```



## key属性

```
<li key={val}></li>
```

如果 React 发现当前的列表有一个之前不存在的 key，那么就会创建出一个新的组件。如果 React 发现和之前对比少了一个 key，那么就会销毁之前对应的组件。如果一个组件的 key 发生了变化，这个组件会被销毁，然后使用新的 state 重新创建一份。

`key` 是 React 中一个特殊的保留属性，直接存储在返回的元素上。不能通过 `this.props.key` 来获取 `key`。

**我们强烈推荐，每次只要你构建动态列表的时候，都要指定一个合适的 key。**

组件的 key 值并不需要在全局都保证唯一，只需要在当前的同一级元素之前保证唯一即可。



## 计算属性名称

[...]自动将表达式转换成属性名

```jsx
handleInputChange(event) {
    const name = target.name;

    this.setState({
        [name]: value
    });
}
```





# JSX

可以使用在大括号内任何的JavaScript表达式：

同时 JSX 可以当作 JavaScript 表达式来使用。

```jsx
const element = (
  <h1>
    Hello, {formatName(user)}!
  </h1>
);


ReactDOM.render(element, document.getElementById('root'));
```



```jsx
const element = <div tabIndex="0"></div>;			// 引号表示字符串
const element = <img src={user.avatarUrl}></img>;	// {}表示js表达式
```



防止注入：React DOM 在渲染所有输入内容之前，默认会进行转义。

React 只更新它需要更新的部分：React DOM 会将元素和它的子元素与它们之前的状态进行比较，并只会进行必要的更新来使 DOM 达到预期的状态



### 组件

- 属性名：小驼峰
- 事件名：小驼峰
- 组件名称必须大写开头

```jsx
// 函数组件
function Welcome(props) {
  return <h1>Hello, {props.name}</h1>;
}

// 使用自定义组件时，赋予的属性都被转换为单个props对象传给组件
const element = <Welcome name="Sara" />;
```



### props 和 state

- props：只读，不要修改它
  - props.children：特殊的 props，类似于槽，可以将传来的 children 放到组件的任意位置。
- state：只能通过 this.setState 来更新，构造函数是唯一可以给 this.state 赋值的地方

```jsx
// class组件（有生命周期）
class Clock extends React.Component {
  constructor(props) {
    super(props);
    this.state = {date: new Date()};
  }
  
  // 组件渲染到DOM后，启动计时器：
  componentDidMount() {
    this.timerID = setInterval(() => this.tick(),1000);
  }

  // 组件移除前，清除计时器
  componentWillUnmount() {
    clearInterval(this.timerID);
  }

  // 更新state
  tick() {
    this.setState({date: new Date()});
  }
    
  render() {
    return (
      <div>
        <h1>Hello, {this.props.name}!</h1>
        <h2>It is {this.state.date.toLocaleTimeString()}.</h2>
      </div>
    );
  }
}

ReactDOM.render(
  <Clock />,
  document.getElementById('root')
);
```

- `setState()` 可以单独更新state中的部分变量
- 自上而下的数据流：state 可以作为子组件的 props 传入
  - 状态提升：
  - 移除子组件的 state，改为使用从父组件的 state 传给子组件的 props
  - 父组件给子组件传一个绑定了自己 this 的函数，这个函数中包含 `this.setState()` ，子组件通过调用这个函数来引发父组件 state 的更新。
  - 从而触发重新渲染。
- state 是异步更新的：因为 `this.props` 和 `this.state` 可能会异步更新，所以你不要依赖他们的值来更新下一个状态。可以让 `setState()` 接收一个函数而不是一个对象，用上一个 state 作为参数： `setState((state, props) => ({counter: state.counter + props.increment}))`
- 通过问自己以下三个问题，你可以逐个检查相应数据是否属于 state：
  1. 该数据是否是由父组件通过 props 传递而来的？如果是，那它应该不是 state。
  2. 该数据是否随时间的推移而保持不变？如果是，那它应该也不是 state。
  3. 你能否根据其他 state 或 props 计算出该数据的值？如果是，那它也不是 state。



### Context

```jsx
// 创建上下文，初始化为defaultValue
const MyContext = React.createContext(defaultValue);
// 设置html中的名字
MyContext.displayName = 'MyDisplayName';

// 设置上下文为someValue，子组件都能读到这个上下文
() => <MyContext.Provider children={children} value={someValue}/>

// 在子组件（消费者）中读取这个context
const value = useContext(MyContext);
```

- 当 Provider 的 `value` 值发生变化时，它内部的所有消费组件都会重新渲染。





### 事件处理

方法一：在构造器中绑定this

```jsx
class Toggle extends React.Component {
  constructor(props) {
    super(props);
    this.state = {isToggleOn: true};
    // 给handleClick绑定this
    this.handleClick = this.handleClick.bind(this);
  }

  handleClick() {
    this.setState(state => ({isToggleOn: !state.isToggleOn}));
  }

  render() {
    return (
      <button onClick={this.handleClick}>
        {this.state.isToggleOn ? 'ON' : 'OFF'}
      </button>
    );
  }
}
```



方法二：用箭头函数来绑定 this

```jsx
<button onClick={(e) => this.handleClick(e)}>
```

绑定了 this 的箭头函数可以作为 props 传入子组件，但是可能会有额外的渲染性能问题。



### 条件渲染

方法一：if-else

```jsx
render() {
    const isLoggedIn = this.state.isLoggedIn;
    let button;
    if (isLoggedIn) {
        button = <LogoutButton onClick={this.handleLogoutClick} />;
    } else {
        button = <LoginButton onClick={this.handleLoginClick} />;
    }

    return (
        <div>
            {button}
        </div>
    );
}
```



方法二：&&

```jsx
render() {
  const cond = true;
  return (
    <div>
      { cond && <h1>'ON'</h1>}
    </div>
  );
}
```



方法三：c ? a : b

```jsx
render() {
  const isLoggedIn = this.state.isLoggedIn;
  return (
    <div>
      {isLoggedIn
        ? <LogoutButton onClick={this.handleLogoutClick} />
        : <LoginButton onClick={this.handleLoginClick} />
      }
    </div>
  );
}
```



### 列表渲染

利用map

```jsx
function NumberList(props) {
  const numbers = props.numbers;
  const listItems = numbers.map((number) =>
    // 必须用 key 属性来标识每个列表元素
    <ListItem key={number.toString()} 
              value={number} />
  );
  return (
    <ul>{listItems}</ul>
  );
}
```

- 列表渲染的时候必须包含key属性，必须保证key在兄弟结点的唯一性，不建议用索引作为key。
- 经验法则：在 `map()` 方法中的元素需要设置 key 属性。
- 组件无法读取 key 属性，如果需要，请显式通过 props 传递。
- 也可以直接在 `<ul>` 中用  `map()` 展开。



### Hook

使用规则：

1. 只能在**函数最外层**调用 Hook。不要在循环、条件判断或者子函数中调用。
2. 只能在 **React 函数组件中** 调用 Hook。不要在其他 JavaScript 函数中调用。



##### useState

```jsx
const [todos, setTodos] = useState([{ text: 'Learn Hooks' }]);

<button onClick={() => setTodos([...todos, { text: 'new todo' }])}>
	Click me
</button>
```

- `useState` 会返回一对值：一个state状态和一个用于更新它的函数；
- `useState` 唯一的参数就是初始 state 值。
- 即使函数退出，state 也会被 React 保留。
- 可以通过 props 传给子组件



##### useEffect

```jsx
// 相当于 componentDidMount 和 componentDidUpdate:
useEffect(() => {
    // 使用浏览器的 API 更新页面标题
    document.title = `You clicked ${count} times`;
    // 返回一个清除函数
    return () => alart('clean up');
  },
  // 指定依赖数组
  [var1, var2]
);
```

- `useEffect` 传入一个函数，React 在每次更新 DOM 之后调用它。
- 传入的函数可以选择**返回一个清除函数**，这个函数将在 DOM 清除之前被调用。（React 会在执行当前 effect 之前调用上一次 effect 的清除函数）
- `useEffect` 可以选择传入第二个参数，依赖数组，只有其中的值发送变化才会触发 effect 。（注意：如果不传第二个参数，则useEffect中的函数如果用到了外部变量，由于闭包特性，只会取第一次传入时的值。如果传了依赖数组，则内部函数每次都可以读到变量最新的值）
- **只运行一次**：第二个参数传入一个空数组 `[]` 

###### 陷阱：无限重复渲染

```jsx
const myComponent = () => {
  const obj = {a: 1, b: 2}
  const [num, setNum] = useState(0)
  
  // 原因：setNum导致num变化，触发组件重新渲染，obj对象被重新赋值（虽然值一样，但是是新的obj地址不同）从而再次触发effect，再次调用setNum，c循环
  useEffect(() => {
    setNum(num + 1)
  }, [obj])
}
```

- 把object/arr对象放在effect的依赖列表里时需要谨慎
  - 因为即使对象的值相同，地址不同也会触发effect。
  - 依赖列表可以放的：基本类型、状态类型
- 解决办法：可以使用 `useMemo` ，只在输入值变化的时候才生成新的object。缺点：useMemo具有传递性，如果继续封装，就得再次使用useMemo





说明：

一个组件里可能使用了多个 Hooks，每次渲染时这些 Hook 被依次调用

1. `useState` 在第二次调用时，不会再用参数去初始化状态值，只是读取 state 变量？
2. `useEffect` 会调用上一次 effect 的清除函数，再去执行自己的函数。



##### useRef

```jsx
// 每次组件渲染时，给变量oldTitle赋值，都会赋最开始传给useRef的初始值
const oldTitle = useRef(document.title).current
```

- 传入一个初始值，保存在 **current** 中，则这个值在这个组件的整个生命周期内都不会改变



##### useMemo

用于解决useEffect无限循环渲染的问题：https://www.notion.so/useCallback-useMemo-f5add874170f494fafca8ec99449f560





### react-spring

https://react-spring.io/basics

```js
import { useSpring, animated } from 'react-spring'

function App() {
  // 给opacity的值设定动画
  const props = useSpring({ to: { opacity: 1 }, from: { opacity: 0 } })
  // 传给的style
  return <animated.div style={...props, border: "1px solid #000"}>I will fade in</animated.div>
}
```

- 只有扩展了animated的元素才能使用动画数值

- 实际上 props = {opacity: ...} 就是一个动态变化的数值，被转给了style，其实也可以被传给其他属性，如：

  ```
  <animated.div>{props.opacity}</animated.div>
  ```



另一种写法（better）

```js
// useSpring里也可以传其他的任意属性名
const {x, y} = useSpring({x: 0, y: 0, from: {x: 100, y: 100}})
const {x, y} = useSpring({to: {x: 0, y: 0}, from: {x: 100, y: 100}}) // 等价写法
<animated.div style={{ x, y }}>啊啊啊</animated.div>
// 用to对值进行额外处理
<animated.div>{x.to(n => n.toFixed(2))}</animated.div>
```

- 注意这里使用useSpring赋值给{x, y}，即只提取了x和y属性，随后x和y可以被当成普通的动态变化的数值使用
- 语法糖：所有不能被useSpring识别的属性都会被当作 to 里的属性，如这里的 x 和 y
- 特殊的简写：x、y、z，可以被用于translateX、rotateX、scaleX等



依赖数组

```
const [style, api] = useSpring({ x: 0, y: 0 }, [])
```





# API

### JSON

```
str = JSON.stringify(data || {})
const obj = JSON.parse(str)
```



### 计时器 setTimeout

```js
let timeoutID = setTimeout(function, delay, arg1, arg2);
clearTimeout(timeoutID);
```

- 定时器到期后，将参数 args 传递给函数执行
- `setTimeout` 返回一个定时器id，可通过 `clearTimeout` 取消未发生的定时器



### localStorage

```js
const key = "__auth_provider_token__";
window.localStorage.setItem(key, user.token || "")
window.localStorage.getItem(key)
window.localStorage.removeItem(key)
```



### 刷新页面 reload

```
window.location.reload()
```



### 获取当前路由

```js
window.location.pathname

// 重置路由并刷新页面
export const resetRoute = () => window.location.href = window.location.origin
```



### 设置页面标题

```
document.title = "请登录"
```



### 顶部沉浸式的颜色

```
<head>
  <meta name="theme-color" content="#000000" />
</head>
```



### 静止手机浏览器下拉刷新

```
<body style="overflow:hidden">
</body>
```



