### 标题

```tsx
// 组件被渲染时设置标题，卸载时恢复标题
const defaultTitle = process.env.REACT_DEFAULT_TITLE;
export const useDocumentTitle = (title: string, keepOnUnmount = false) => {
  // 使用useRef记录旧title
  const oldTitle = useRef(document.title).current;

  // 设置新title
  useEffect(() => {
    document.title = title;
  }, [title]);

  // 组件卸载时调用return函数
  // 若设置不保留title，则恢复默认title
  useEffect(() => {
    return () => {
      if (!keepOnUnmount) {
        document.title = defaultTitle || "no title";
      }
    };
  }, [keepOnUnmount, oldTitle]);
};

// 组件中使用
useDocumentTitle("项目列表");
```





### react-router

```
yarn add react-router@6 react-router-dom@6
yarn add history
```

- v6还在beta

使用：

```tsx
import { BrowserRouter } from "react-router-dom";
import { Route, Routes } from "react-router";

// 根据path渲染组件，BrowserRouter是Provider提供上下文
<BrowserRouter>
  <Routes>
    <Route path={"projects"} element={<ProjectListScreen />} />
    <Route path={"projects/:projectId/*"} element={<ProjectScreen />} />
  </Routes>
</BrowserRouter>


import { Link } from "react-router-dom";

// 跳转到在当前路径下的子路径（）
// - to只能接受string
// - 如果to的路径以/开头，则表示去根路由(what about Route path?)
<Link to={'apple'}>apple</Link>
<Link to={'banana'}>banana</Link>
// 添加子路由
<Routes>
  <Route path={'/apple'} element={<Apple/>}/>
  <Route path={'/banana'} element={<Banana/>}/>
  // 默认路由
  <Navigate to={window.location.pathname + '/apple'}/>
</Routes>
```



### 重置路由并刷新页面

```js
// 重置路由并刷新页面
export const resetRoute = () => (window.location.href = window.location.origin);
```



### 管理URL参数状态

```tsx
import { useSearchParams } from "react-router-dom";

// 获取url的query-string中指定的fields，转换为object
export const useUrlQueryParam = (keys: string[]) => {
  const [searchParams, setSearchParams] = useSearchParams();

  return [
    keys.reduce((prev, key) => {
      return { ...prev, [key]: searchParams.get(key) || "" };
    }, {}) as { [key in string]: string },
    setSearchParams,
  ] as const;
};
```

