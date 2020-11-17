### 准备

1. node.js安装：github上nvm-windows，下载nvm-noinstall.zip解压安装。

2. 包管理器yarn安装：进入yarn官网，下载安装包

   ```bash
   yarn -v		#查看是否安装成功
   ```

3. Vue CLI安装：进入官网，复制下载命令

   ```
   yarn global add @vue/cli
   ```

4. chrome安装vue插件



### 创建项目

1. 创建项目：powershell中打开：

   ```
   $ vue create vuetify-admin	#项目文件夹名
   ```

   选择默认设置，回车。

2. 安装vuetify vue CLI：移动到项目文件夹`cd vuetify-admin`

   ```
   $ vue add vuetify
   ```

   选择默认预设，回车。

3. 启动：

   ```
   $ yarn serve
   ```



注意：

- 每个组件只能有一个根元素
- 所有vuetify组件放在：\<v-app>



代码补全：

- vue：生成一个vue结构



### 类

- 栅格布局
  
  ```vue
  <v-container>
      <v-row align="start" no-gutters> 
          <v-col>宽度自动缩放扩张</v-col>
          <v-col cols="12" md="6">小屏宽度为12，md以上宽度为6</v-col>
          <v-col cols="auto">宽度随内容改变</v-col>
          <v-col offset="4">偏移4</v-col>
      </v-row>
      <v-row>
          <v-col></v-col>
          <v-col class="ml-auto">左侧自动边距，效果是两列分散在两边</v-col>
      </v-row>
      <v-row>
          <v-col></v-col>
          <v-spacer>使用空格自动隔开列</v-spacer>
          <v-col></v-col>
      </v-row>
  </v-container>
  ```
  
  - 垂直对齐（align）：start，center，end
  - 水平对齐（justify）：start，center，end，space-around，space-between
  
- [颜色](https://vuetifyjs.com/zh-Hans/styles/colors/#sass-%E8%89%B2%E5%BD%A9%E5%8C%85)
  
  - 背景颜色：`purple darken-2`
  - 文字颜色：`red--text text--lighten-1`
  
- 显示（display）
  - 内联：`d-inline`
  - 块元素：`d-block`
  - flex：`d-flex flex-column justify-space-around align-center`（主轴、副轴）
  
- 间距
  - 边距（margin）：`mt-n12 mx-auto`（向上负12*4px，x方向auto自动居中）
  - 填充（padding）：`pa-2`（所有方向padding 2*4px）
  
- [文本](https://vuetifyjs.com/zh-Hans/styles/text-and-typography/)
  
  - 左对齐：`text-left`
  - 中对齐：`text-center`
  - 右对齐：`text-right`
  - 加粗：`font-weight-bold`
  - 下划线：`text-decoration-underline`
  - 截断成省略号：`text-truncate`
  - 字体大小
    - `text-h1`
    - `text-subtitle-1`
    - `text-subtitle-2`
    - `text-body-1`
    - `text-body-2`
    - `text-button`
    - `text-caption`（更小的字体）



# Vue.js

##### 命名规范

- 组件名：

  - 引入时：PascalCase（首字母大写），
  - html模板中：kebab-case（短横线）

  ```
  Vue.component('MyComponent', {});
  import MyComponent from 'MyComponent.vue';
  export default {
      name: 'MyComponent'
  }
  
  在DOM中使用的时候，  <my-component></my-component>
  ```

- props：

  - 声明时：驼峰命名（myProps），
  - 模板中：kebab-case（短横线）（my-props）

  ```
  props: {
      myProps: {}
  }
  
  <my-component :my-props="abc"></my-component>
  ```

- emit事件：

  都用 kebab-case（短横线）

  ```
  this.$emit（'my-event'）;
  
  <my-component @my-event="abc"></my-component>
  ```

  



### 自定义组件

1. components文件夹下创建一个Header.vue（一般都是大写开头），组件中写好html。

2. 页面中引用组件：

   ```vue
   <template>
     <v-app>
       <Header :items="items"></Header>	<!-- 使用组件，prop传数据给组件 -->
     </v-app>
   </template>
   
   <script>
   import Header from "./components/Header"	// 引入组件路径
   
   export default {
     components: {
       Header		// 组件
     },
       
     data: () => ({
       items: [	// 组件要用到的数据，通过prop传入
         { title: 'Dashboard', icon: 'mdi-view-dashboard' },
         { title: 'Photos', icon: 'mdi-image' },
         { title: 'About', icon: 'mdi-help-box' },
       ],
     }),
   </script>
   ```

3. prop：（父组件传数据给子组件）子组件中：

   ```vue
   <script>
   export default {
       props: {
           items: Array	// 组件用到的外部数据items、说明类型。像data一样使用。
       },
   }
   </script>
   ```

   [prop文档](https://cn.vuejs.org/v2/guide/components-props.html)

4. emit：（子组件传数据给父组件）

   - 子组件中发射事件：

     ```vue
     <script>
     export default {
         data: () => ({
             name: "innor",
         }),
         
         methods: {
             clicked() {
                 this.$emit('my-event', this.name)	// 将this.name传给父组件
             }
         }
     }
     </script>
     ```

   - 父组件中监听事件`my-event`：

     ```vue
     <template>
       <v-app>
         <Header @my-event="recv"></Header>	<!-- 监听事件，调用recv方法 -->
       </v-app>
     </template>
     
     <script>
     export default {
       data: () => ({
         name: 'not recevied'
       }),
     
       methods: {
         recv(data) {
           this.name = data	// recv方法将收到的数据传给this.name
         }
       }
     };
     </script>
     ```

5. slot（插槽）：父组件中标签里的内容，会被放到子组件中写了`<slot></slot>`的地方。

   

