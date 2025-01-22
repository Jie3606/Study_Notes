## 学习笔记

## 技术笔记


- [How_is_the_network_connected](Technical_Books/How_is_the_network_connected/1.Browser_generates_messages.md)

## 工作笔记


### 数学公式

多行公式块：

$$
\frac{1}{
  \Bigl(\sqrt{\phi \sqrt{5}}-\phi\Bigr) e^{
  \frac25 \pi}} = 1+\frac{e^{-2\pi}} {1+\frac{e^{-4\pi}} {
    1+\frac{e^{-6\pi}}
    {1+\frac{e^{-8\pi}}{1+\cdots}}
  }
}
$$

行内公式：

公式 $a^2 + b^2 = \color{red}c^2$ 是行内。


### 流程图

```mermaid
graph TB
    c1-->a2
    subgraph one
    a1-->a2
    end
    subgraph two
    b1-->b2
    end
    subgraph three
    c1-->c2
    end
```

### 时序图

```mermaid
sequenceDiagram
    Alice->>John: Hello John, how are you?
    loop Every minute
        John-->>Alice: Great!
    end
```

### 甘特图

```mermaid
gantt
    title A Gantt Diagram
    dateFormat  YYYY-MM-DD
    section Section
    A task           :a1, 2019-01-01, 30d
    Another task     :after a1  , 20d
    section Another
    Task in sec      :2019-01-12  , 12d
    another task      : 24d
```


### Graphviz

```graphviz
digraph finite_state_machine {
    rankdir=LR;
    size="7,4"
    node [shape = doublecircle]; S;
    node [shape = point ]; qi
    node [shape = circle];
    qi -> S;
    S  -> q1 [ label = "a" ];
    S  -> S  [ label = "a" ];
    q1 -> S  [ label = "a" ];
    q1 -> q2 [ label = "ddb" ];
    q2 -> q1 [ label = "b" ];
    q2 -> q2 [ label = "b" ];
}
```


### 脚注

这里是一个脚注引用 [^1]，这里是另一个脚注引用 [^bignote]。
这里是一个脚注引用 [^1]，这里是另一个脚注引用 [^bignote]。

[^1]: 第一个脚注定义。
[^bignote]: 脚注定义可使用多段内容。

    缩进对齐的段落包含在这个脚注定义内。

    ```
    可以使用代码块。
    ```

<div style="color:black; background-color: blue; ">
这是带有红色字体和黄色背景色的段落。
</div>

<font color="red">这是红色的文字（使用十六进制颜色值）</font>
