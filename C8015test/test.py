import serial  
import threading  
import time  
  
# 定义串口参数  
SERIAL_PORT = '/dev/ttyUSB0'  
BAUD_RATE = 1500000  
TIMEOUT = 1  
  
# 创建串口对象  
ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=TIMEOUT)  
  
# 全局退出标志  
exit_flag = False  
  
def read_from_port(ser):  
    """从串口读取数据的函数"""  
    try:  
        while not exit_flag and ser.is_open:  
            if ser.in_waiting > 0:  
                data = ser.readline()  
                print(f"Received: {data.decode().strip()}")  
            # 可以添加一个小延迟来减少CPU使用率  
            # time.sleep(0.01)  
    except Exception as e:  
        print(f"读取线程异常: {e}")  
  
def write_to_port(ser, message):  
    """向串口写入数据的函数"""  
    ser.write(message.encode() + b'\n')  
  
# 创建一个线程用于读取数据  
thread_read = threading.Thread(target=read_from_port, args=(ser,))  
thread_read.start()  
  
try:  
    while True:  
        message = input("Enter message to send: ")  
        if message.lower() == 'exit':  
            exit_flag = True  # 设置退出标志  
            break  
        write_to_port(ser, message)  
except KeyboardInterrupt:  
    print("Exiting...")  
    exit_flag = True  # 确保在键盘中断时也设置退出标志  
  
# 等待读取线程结束（虽然在这个例子中它可能会因为串口关闭而自然退出）  
thread_read.join()  
  
# 关闭串口  
ser.close()

ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBb9EZgkEIkJpUgXlZpAcPdqKfA2tfAY0a0hkzcxVIiG msik\jieliu@jieliu
