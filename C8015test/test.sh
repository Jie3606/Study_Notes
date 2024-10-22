#!/bin/bash  
  
# 定义串口参数  
SERIAL_PORT="/dev/ttyUSB0"  
BAUD_RATE=1500000  
  
# 设置串口参数（注意：某些系统可能不支持直接设置这么高的波特率）  
stty -F $SERIAL_PORT cs8 -parenb -cstopb $BAUD_RATE  
  
# 创建一个文件用于存储从串口读取的数据（或者使用管道，但更复杂）  
READ_FILE="/tmp/serial_read.tmp"  
  
# 在后台启动一个进程来读取串口数据  
cat $SERIAL_PORT > $READ_FILE &  
READER_PID=$!  
  
# 清理临时文件的函数  
cleanup() {  
    # 杀死读取进程  
    kill $READER_PID 2>/dev/null  
    # 删除临时文件  
    rm -f $READ_FILE  
}  
  
# 捕获Ctrl+C以进行清理  
trap cleanup SIGINT  
  
# 主循环，从标准输入读取用户输入  
while true; do  
    # 提示用户输入  
    echo -n "Enter message to send (or 'exit' to quit): "  
    read INPUT_MESSAGE  
  
    # 检查是否要退出  
    if [[ "$INPUT_MESSAGE" == "exit" || "$INPUT_MESSAGE" == "EXIT" ]]; then  
        break  
    fi  
  
    # 发送数据到串口（注意：这里假设串口已经配置为可以接受这种输入）  
    echo -n "$INPUT_MESSAGE" > $SERIAL_PORT  
    echo -n "\n" >> $SERIAL_PORT  # 发送换行符，如果需要的话  
  
    # 显示从串口读取的数据（可选，仅用于演示）  
    if [[ -s $READ_FILE ]]; then  
        tail -n +1 $READ_FILE  
        # 清空已读取的内容（注意：这可能会导致数据丢失，如果读取和显示不是原子的）  
        > $READ_FILE  
    fi  
done  
  
# 清理资源（理论上，trap应该已经处理了，但这里再次调用以确保）  
cleanup  
  
echo "Script exited."