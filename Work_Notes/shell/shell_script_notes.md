# Shell 脚本学习笔记

```makefile
$0 : 脚本名
$0-$9: 脚本的参数
$@ ($*) : 所有参数
$# : 参数个数
$? : 前一个命令的返回值
$$ : 当前脚本的识别码
!! : 完整的上一条命令(包括参数)
$_ : 上一条命令的最后一个参数

$* 会将所有参数视为一个单一的字符串，而 $@ 会将每个参数视为一个独立的字符串,这意味着当参数包含空格时，$* 可能会导致问题，而 $@ 则不会。
```

```Makefile
hey : one two
    echo $@ 输出hey
    echo $? 输出比目标更新的所有先决条件
    echo $n 输出所有先决条件
```

## 1. 基本概念

- **Shell**：Shell 是一个命令行解释器，用于执行用户输入的命令。常见的 Shell 包括 Bash、Zsh、Ksh 等。

- **Shell 脚本**：Shell 脚本是由一系列 Shell 命令组成的文件，通常用于自动化任务。

## 2. 脚本基础

- **脚本文件**：Shell 脚本文件通常以 `.sh` 作为扩展名。

- **Shebang**：脚本的第一行通常是 `#!/bin/bash`，用于指定脚本使用的解释器。

- **执行权限**：在运行脚本之前，需要为脚本文件添加执行权限。
  ```bash
  chmod +x script.sh
  ```

## 3. 变量

- **定义变量**：使用等号 `=` 定义变量，等号两边不能有空格。
  ```bash
  name="Alice"
  ```

- **使用变量**：使用 `$` 符号引用变量。
  ```bash
  echo $name
  ```

- **环境变量**：使用 `export` 命令将变量导出为环境变量。
  ```bash
  export PATH=$PATH:/new/path
  ```

## 4. 控制结构

- **条件判断**：使用 `if`、`elif`、`else` 进行条件判断。
  ```bash
  if [ condition ]; then
      # 代码
  elif [ condition ]; then
      # 代码
  else
      # 代码
  fi
  ```

- **循环**：使用 `for`、`while`、`until` 进行循环。
  ```bash
  for i in {1..5}; do
      echo $i
  done

  while [ condition ]; do
      # 代码
  done

  until [ condition ]; do
      # 代码
  done
  ```

## 5. 函数

- **定义函数**：使用 `function` 关键字或直接定义。
  ```bash
  function my_function {
      echo "Hello, World!"
  }

  my_function() {
      echo "Hello, World!"
  }
  ```

- **调用函数**：直接使用函数名调用。
  ```bash
  my_function
  ```

## 6. 输入输出

- **读取输入**：使用 `read` 命令读取用户输入。
  ```bash
  read -p "Enter your name: " name
  echo "Hello, $name"
  ```

- **输出**：使用 `echo` 或 `printf` 输出信息。
  ```bash
  echo "Hello, World!"
  printf "Name: %s\n" "$name"
  ```

## 7. 文件操作

- **重定向**：使用 `>`、`>>` 将输出重定向到文件。
  ```bash
  echo "Hello, World!" > file.txt
  echo "Append this line" >> file.txt
  ```

- **管道**：使用 `|` 将一个命令的输出作为另一个命令的输入。
  ```bash
  ls -l | grep "txt"
  ```

## 8. 调试

- **调试模式**：使用 `-x` 选项运行脚本以调试。
  ```bash
  bash -x script.sh
  ```

- **语法检查**：使用 `-n` 选项检查脚本语法。
  ```bash
  bash -n script.sh
  ```

## 9. 常用命令

- **文件操作**：`cp`、`mv`、`rm`、`touch`、`mkdir` 等。

- **文本处理**：`grep`、`awk`、`sed`、`cut`、`sort` 等。

- **系统信息**：`uname`、`df`、`du`、`top`、`ps` 等。
