# Calculator
> Project说明：使用LL(1)文法实现的计算器（基于龙书介绍）

## 所需背景知识
1. 龙书第一、二、三、四、五章相关内容
2. 相关简单计算器文法产生式
3. 消除左递归的方法
4. LL(1)文法
5. 预测分析表
6. 自顶向下的SDD语义规则

## 简单计算器文法产生式
```
expression => expression + term  | expression - term | term
term => term * factor | term / factor | factor
factor => (expression) | - factor | id
```

## 消除左递归的文法产生式
```
expression => term expression'
expression' => + term expression' | - term expression' | epsilon
term => factor term'
term' => * factor term' | / factor term' | epsilon
factor => (expression) | - factor | id
```

## 预测分析表
| 输入符号 \ 非终结符号 |   E   |  E'   |   T   |    T'   |   F    |
|:----:|-------:|--------:|-------:|--------:|-------:|
|FIRST |-, id, ( |+, - |-, id, ( |*, / |-, id, ( |
|FOLLOW|$, ) |$, ) |$, ), +, - |$, ), +, - |$, ), +, -, *, / |
|  id  |  | |F T' | |id |
|  (   |T E' | |F T' | |(E) |
|  )   | |epsilon | |epsilon | |
|  +   | |+ T E'| |epsilon | |
|  -   |T E' |- T E' |F T'|epsilon |-F |
|  *   | | | |* F T' | |
|  /   | | | |/ F T' | |
|  $  |T E' | epsilon | |epsilon | |

## 自顶向下的SDD语义规则

|  产生式  |  语义规则    |
|:----:|:------:|
|E => T E' | E.syn = E'.syn , E'.inh = T.syn |
|E' => + T E1'|E'.syn = E1'.syn, E1'.inh = E'.inh + T.syn|
|E' => - T E1'|E'.syn = E1'.syn, E1'.inh = E'.inh - T.syn|
|E' => epsilon |E'.syn = E'.inh|
|T => F T'|T.syn = T'.syn, T'.inh = F.syn|
|T' => * F T1'|T'.syn = T1'.syn, T1'.inh = T'.inh * F.syn|
|T' => / F T1'|T'.syn = T1'.syn, T1'.inh = T'.inh / F.syn|
|T' => epsilon |T'.syn = T'.inh|
|F => (E)|F.syn = E.syn|
|F => id|F.syn = id.val|
|F => -F1|F.syn = -F1.syn|

## 一点说明
1. 其中 **id** 实际上等同于程序语言中的变量，但是作为计算器的实现所以实际上把 **id** 当作数字（可以是整数也可以是浮点数）。
2. 实际的代码中我主要分成两个部分，第一个部分是词法分析器部分（WordParser），这部分直接和输入流进行交流；而第二部分是语法分析器，语法分析器通过词法分析器获取词法单元，而词法分析器则返回一个词法单元给语法分析器进行处理。
3. 实际的语法分析器是根据预测分析表来决定究竟下一步用什么表达式，同时通过语义规则来实际计算相应的结果。
4. 使用命令**make**可以编程项目，编译完的项目有一个**cal**可执行文件，通过以下命令可以执行程序：
```
$ ./cal
```
