env --查询 cli environment variable

ELF文件是：Executable and Linkable format

单引号的字符串只是单纯的字符串，双引号的字符串中如果用特殊的符号会替换。


inode和链接数

软链接：有自己的inode，但链接数（i_nlink）的变化与指向的文件无关。创建或删除软链接时，指向文件的链接数不会改变。

硬链接：与原文件共享同一个inode。创建新的硬链接会增加链接数（i_nlink），删除硬链接会减少链接数。当链接数降到0时，文件的数据块和inode才会被删除。

tar -cvf 打包 -xvf 解包

tar -zcvf 打包并且压缩 -zxvf 解压缩并且解包

clear -清除终端
reset -重置终端
source ~/.bashrc -重新加载配置文件


tree -L 2 : 显示两层
ls -lR : 显示当前文件夹下所有文件详细信息
