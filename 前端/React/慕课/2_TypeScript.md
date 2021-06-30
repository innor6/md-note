将文件名从 js 改为 ts



可以类型自动推断时，可以不必声明类型，如：定义变量、函数返回类型



### 给函数添加类型声明：interface

```tsx
// 声明类型
interface SearchPanelProps {
  users: User[]
  param: {
    name: string
    personId: string
  }
  // 声明函数类型，其中入数param又引向了自己接口中的param类型
  setParam: (param: SearchPanelProps["param"]) => void
}

// 变量后面用冒号指定类型
({ users, param, setParam }: SearchPanelProps) => { ... }

// 也可以像这样不声明接口，直接指定类型
let param: {id: number, name: string}
```



### 类型强转 as

```jsx
<Select
    value={param.personId}
    onChange={
        (evt) => setParam({
        	...param,
        	personId: evt.target.value as string,	//类型转成string
    	})
    }
>
```



##### as const

数组默认每个元素都具体相同类型，若要求不同

```tsx
let a = [1,""]			// 类型：(string || number)[]
let b = [1,""] as const	// 类型：[1,""]
```





### 顶级类型

- **any**：表示可以传任意类型
- **unknown**：any的类型安全版本，unknown只能赋值给unknown类型（传递性）
  - 不能赋值给其他类型
  - 也不能对它通过 `value.fun()` 这样调用函数

##### 给unknown限定类型：

可以通过 `typeof` 或 `instanceof` 运算符来限定 `unknown` 类型。

```js
if (typeof value === "function") {
    // `value` has type `Function`,
    const functionName = value.name || "(anonymous)";
    return `[function ${functionName}]`;
  }
 
  if (value instanceof Date) {
    // `value` has type `Date`,
    return value.toISOString();
  }

```



类型object表示范围很广，如果对其展开 `...object` ，如果object是函数，会返回 `null`，如果明确是键值对时：

```
let obj: { [key: string]: unknown }
```



技巧：特化的object

```tsx
// 特化返回obj的类型：根据输入值自动生成类型
let a = <K extends string>(keys: K[]) => {
  return {} as { [key in K]: string } // 关键在这里
}

// v的类型为 {a: string, b:string}，而不是任意的key-value对
let v = a(["a","b"])
```



### 可选参数：?

```
(a: number, b?: string) => {}

// 当有展开语法时，不能用?表示可选
// 但是可以用=赋予默认值
// 有默认值的参数是可选的
({a, b, ...c}: MyProps = {}) => {}

// 传参时，可以传undefined给可选参数，从而相当于没传（例如第一个参数是可选的，想传第二个参数，又不想传第一个参数时，第一个参数传undefined）
```



### 或：|

可以**用于允许null，常用于配合三目运算符**

```tsx
const [user, setUser] = useState<User | null>(null)

// 这里对user做了判断，所以div里的user一定是User类型而不是null！
return {user? <div>{user.name}<div> : null}
```



### 泛型：<>

```tsx
// 参数后加?表示可选参数
<T>(array: T[], delay?: number) => {}
```



### utility type

用于根据已有的类型，转换得到一个新的类型

可以使用别人的类型：

```
// Parameters<T> 获取已有的类型
param: Parameters<typeof http>
// 配合展开语法
// 这里的场景是声明了一个类型，它对应了一个列表
// 为了调用这函数的时候，不是传一个列表，而是还是普通的传两个参数，使用了rest语法
(...[endpoint, config]: Parameters<typeof http>) => {}

// Partial<T> 允许只含T的部分key
const Jack: Partial<Person> = {name: 'Jack'}

// Omit<T, any> 删除类型T中的某些key
const MrMistery: Omit<Person, 'name' | 'age'> = {}

// Pick<T, any> 取其中的类型
let param: Pick<Project, 'name' | 'personId'>
```



### 透传组件类型

https://coding.imooc.com/lesson/482.html#mid=41632

```tsx
// 获取组件的props
type SelectProps = React.ComponentProps<typeof Select>

// 自定义的props先exten的组件的props，再omit同名的类型
interface MySelectPros extend Omit<SelectProps, 'value'|'onChange'|'options'> {
  value: string | number | null | undefined;
  onChange: (value?: number) => void;
  defaultOptionName?: string;
  options?: { name: string; id: number }[];
}

//
export const MySelect = (props: IdSelectProps) => {
  // 提取传给原组件的props
  const {value, onChange, defaultOptionName, options, ...restProps} = props
  
  // 把props透传给原组件
  return <Select {...restProps}>...</Select>
}
```





### 类型别名：

```
type FavoriteNumber = string | number
let myFavoriteNumber: FavoriteNumber = '7'

type Person = {name: string}	//可以当interface用
```





### 忽略类型检查

使用下面的注释：

```
// @ts-ignore
```



### 继承

```
interface Base {
	id: number
}

interface Person extends Base {
	name: string
}
```



