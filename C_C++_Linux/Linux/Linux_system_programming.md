# GCC

-E 预处理指定的源文件，不进行编译
-S 编译指定的源文件，但是不进行汇编
-c 编译、汇编指定的源文件，但是不进行链接
-o [file1] [file2] / [file2] -o [file1] 将文件 file2 编译成可执行文件 file1
-I directory 指定 include 包含文件的搜索目录
-g 在编译的时候，生成调试信息，该程序可以被调试器调试
-D 在程序编译的时候，指定一个宏
-w 不生成任何警告信息
-Wall 生成所有警告信息
-On n的取值范围：0~3。编译器的优化选项的4个级别，-O0表示没有优化，-O1为缺省值，-O3优化级别最高
-l 在程序编译的时候，指定使用的库
-L 指定编译的时候，搜索的库的路径。
-fPIC/fpic 生成与位置无关的代码
-shared 生成共享目标文件，通常用在建立共享库时
-std 指定C方言，如:-std=c99，gcc默认的方言是GNU C

// gcc -nostartfiles -efunc test.c

// 编译test.c指定fun()  为函数入口

---

# 静态库

命名规则：
Linux : libxxx.a
 lib : 前缀（固定）
 xxx : 库的名字，自己起
 .a : 后缀（固定）
Windows : libxxx.li

# 静态库的制作：

1)gcc 获得 .o 文件(gcc -c)
2)将 .o 文件打包，使用 ar 工具（archive）
   ar rcs libxxx.a xxx.o xxx.o
      r – 将文件插入备存文件中
      c – 建立备存文件
      s – 索引

编译：gcc main.c -o app -I ./include/ -L ./ -lcalc

库小的时候使用静态库，反之则使用动态库

# 动态库

命名规则
Linux : libxxx.so
 lib : 前缀（固定）
 xxx : 库的名字，自己起
 .so : 后缀（固定）
 在Linux下是一个可执行文件
Windows : libxxx.dll

# 动态库的制作：

gcc 得到 .o 文件，得到和位置无关的代码
   gcc -c –fpic/-fPIC a.c b.c
gcc 得到动态库
   gcc -shared a.o b.o -o libcalc.so

gcc main.c -o app -I [头文件目录] -L [动态库所在目录] -lcalc

# 动态库的配置

ldd main - 查看程序main的动态库依赖
程序启动之后，动态库会被动态加载到内存中，通过 ldd （list dynamic dependencies）命令检查动态库依赖关系
动态库环境变量的配置：

如何定位共享库文件呢？
当系统加载可执行代码时候，能够知道其所依赖的库的名字，但是还需要知道绝对路
径。此时就需要系统的动态载入器来获取该绝对路径。对于elf格式的可执行程序，是
由ld-linux.so来完成的，它先后搜索elf文件的 DT_RPATH段 ——> 环境变量
LD_LIBRARY_PATH ——>  ——> /lib/，/usr/lib
目录找到库文件后将其载入内存。

 1.DT_RPATH无法修改
2.LD_LIBRARY_PATH export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:动态库所在文件夹[好像只可以在当前会话用]
3./etc/ld.so.cache文件列表 中加入一行：动态库所在文件夹(推荐)
4./lib/，/usr/lib:拷贝到/lib/，/usr/lib(不推荐)

---

# makefile
```Makefile
 app:div.c add.c mult.c sub.c main.c

 		gcc div.c add.c mult.c sub.c main.c -o app
 定义变量
 src=div.o add.o mult.o sub.o main.o
src=$(wildcard PATTERN ./*.c)
objs=$(patsubst %.c,%.o,$(src))
target=app
--------------------------------
 $(target):$(src)
 		$(CC) $(src) -o $(target)
--------------------------------
$(target):$(objs)
		$(CC) $(objs) -o $(target)

 div.o:div.c
 		gcc -c div.c -o div.o

 add.o:add.c
 		gcc -c add.c -o add.o

 mult.o:mult.c
 		gcc -c mult.c -o mult.o

 sub.o:sub.c
 		gcc -c sub.c -o sub.o

 main.o:main.c
 		gcc -c main.c -o main.o

 模式匹配

%.o:%.c
		$(CC) -c $< -o $@
.PHONY:clean
clean:
		rm -f $(objs)

#函数

```
```c++

# $(wildcard PATTERN...)
# 功能：获取指定目录下指定类型的文件列表
# 参数：PATTERN 指的是某个或多个目录下的对应的某种类型的文件,如果有多个目录，一般使用空格间隔
# 返回：得到的若干个文件的文件列表，文件名之间使用空格间隔
# 示例：
# 	$(wildcard *.c ./sub/*.c)
#     返回值格式: a.c b.c c.c d.c e.c f.c

# $(patsubst <pattern>,<replacement>,<text>)
# 功能：查找<text>中的单词(单词以“空格”、“Tab”或“回车”“换行”分隔)是否符合
# 模式<pattern>，如果匹配的话，则以<replacement>替换。<pattern>可以包括通配符`%`，表示任意长度的字串。
# 如果<replacement>中也包含`%`，那么，<replacement>中的这个`%`将是<pattern>中的那个%所代表的字串。
# (可以用`\`来转义，以`\%`来表示真实含义的`%`字符)
# 返回：函数返回被替换过后的字符串
# 示例：
# 	$(patsubst %.c, %.o, x.c bar.c)
# 	返回值格式: x.o bar.o
 -->
```
# GDB

关闭编译器优化选项（-O），打开调试（-g），打开所有warnin(-Wall)

启动和退出
   gdb 可执行程序(test)
   quit/q
给程序设置参数/获取设置参数
   set args 10 20
   show args
GDB 使用帮助
   help
查看行号
   vim set nu
查看当前文件代码
   参看当前文件代码 list/l (默认10行)
   参看当前文件指定行附近代码 list/l [行号]
   参看当前文件指定行附近代码 list/l [函数]
查看非当前文件代码
   list/l 文件名：行号
   list/l 文件名：函数名
设置显示的行数
   show list/listsize
   set list/listsize 行数
设置断点
   b/break 行号
   b/break 函数名
   b/break 文件名:行号
   b/break 文件名:函数
查看断点
   i/info b/break
删除断点
   d/del/delete 断点编号
设置断点无效
   dis/disable 断点编号
设置断点生效
   ena/enable 断点编号
设置条件断点（一般用在循环的位置）
   b/break 10 if i==5
   05 / GDB 命令 – 调试命令
运行GDB程序
   start（程序停在第一行）
   run（遇到断点才停）
继续运行，到下一个断点停
   c/continue
向下执行一行代码（不会进入函数体）
   n/next
变量操作
   p/print 变量名（打印变量值）
   ptype 变量名（打印变量类型）
向下单步调试（遇到函数进入函数体）
   s/step
   finish（跳出函数体）
自动变量操作
   display 变量名（自动打印指定变量的值）
   i/info display
   undisplay 编号
其它操作
   set var 变量名=变量值 （循环中用的较多）
   until （跳出循环）
   THANK

# GDB多进程调试

## 设置调试父进程或者子进程

set follow-fork-mode [parent（默认）| child]
(gdb) show follow-fork-mode // 默认的调试父进程
Debugger response to a program call of fork or vfork is "parent".
(gdb) set follow-fork-mode child//修改为子进程
(gdb) show follow-fork-mode
Debugger response to a program call of fork or vfork is "child".

## 设置调试模式

(gdb) set detach-on-fork
(gdb) show detach-on-fork
Whether gdb will detach the child of a fork is on.

set detach-on-fork [on | off]
默认为 on，表示调试当前进程的时候，其它的进程继续运行，如果为 off，调试当前进
程的时候，其它进程被 GDB 挂起。

## 查看调试的进程：

info inferiors

## 切换当前调试的进程：

inferior id

## 使进程脱离 GDB 调试：

detach inferiors id
