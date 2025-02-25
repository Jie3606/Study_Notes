/**
 * FileName:  cmos_rw.c
 * Author:    jieliu
 * Version :  V1.1
 * Date:      2025-02-19
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/io.h>
 #include <unistd.h>
 #include <string.h>
 #define CMOS_ADDR_STANDARD 0x70
 #define CMOS_DATA_STANDARD (CMOS_ADDR_STANDARD + 1)
 #define CMOS_ADDR_EXTENDED 0x72
 #define CMOS_DATA_EXTENDED (CMOS_ADDR_EXTENDED + 1)
 #define ROWS 16
 #define COLS 16

 // 自己实现的 outb 函数
 // void my_outb(unsigned char value, unsigned short port) {
 //     __asm__ volatile (
 //         "outb %%al, %%dx"
 //         :
 //         : "a" (value), "d" (port)
 //     );
 // }

 // // 自己实现的 inb 函数
 // unsigned char my_inb(unsigned short port) {
 //     unsigned char result;
 //     __asm__ volatile (
 //         "inb %%dx, %%al"
 //         : "=a" (result)
 //         : "d" (port)
 //     );
 //     return result;
 // }

 void write_cmos_register(unsigned char reg, unsigned char value) {
     unsigned char cmos_addr_port;
     unsigned char cmos_data_port;

     if (reg < 0x80) {
         cmos_addr_port = CMOS_ADDR_STANDARD;
         cmos_data_port = CMOS_DATA_STANDARD;
     } else {
         cmos_addr_port = CMOS_ADDR_EXTENDED;
         cmos_data_port = CMOS_DATA_EXTENDED;
     }

     // 写入 CMOS 地址寄存器
     outb(reg, cmos_addr_port);
     // 写入 CMOS 数据寄存器
     outb(value, cmos_data_port);
 }

 unsigned char read_cmos_register(unsigned char index) {
     unsigned char cmos_addr_port = (index < 0x80) ? CMOS_ADDR_STANDARD : CMOS_ADDR_EXTENDED;
     unsigned char cmos_data_port = cmos_addr_port + 1;

     // 写入 CMOS 地址寄存器
     outb(index, cmos_addr_port);
     // 读取 CMOS 数据寄存器
     unsigned char value = inb(cmos_data_port);

     return value;
 }



 void print_cmos_table_to_buffer(char *buffer) {
     char temp[256];
     int offset = 0;

     // 打印表头
     offset += sprintf(buffer + offset, "    ");
     for (int col = 0; col < COLS; col++) {
         offset += sprintf(buffer + offset, "%02x ", col);
     }
     offset += sprintf(buffer + offset, "\n");

     // 打印分隔线
     offset += sprintf(buffer + offset, "   +");
     for (int i = 0; i < COLS * 3; i++) {
         offset += sprintf(buffer + offset, "-");
     }
     offset += sprintf(buffer + offset, "+\n");

     // 打印表格内容
     for (int row = 0; row < ROWS; row++) {
         offset += sprintf(buffer + offset, "%02x |", row * COLS);
         for (int col = 0; col < COLS; col++) {
             unsigned char cmos_value = read_cmos_register(row * COLS + col);
             offset += sprintf(buffer + offset, "%02x ", cmos_value);
         }
         offset += sprintf(buffer + offset, "|\n");
     }

     // 打印分隔线
     offset += sprintf(buffer + offset, "   +");
     for (int i = 0; i < COLS * 3; i++) {
         offset += sprintf(buffer + offset, "-");
     }
     offset += sprintf(buffer + offset, "+\n");
 }

 void print_cmos_time_to_buffer(char *buffer) {
     unsigned char second = read_cmos_register(0x00);
     unsigned char minute = read_cmos_register(0x02);
     unsigned char hour = ( read_cmos_register(0x04) + 8) % 24;
     sprintf(buffer, "Time (UTC +0 ): %02d:%02x:%02x\n", hour, minute, second);
 }

 void print_cmos_date_to_buffer(char *buffer) {
     unsigned char day_of_week = read_cmos_register(0x06);
     unsigned char day_of_month = read_cmos_register(0x07);
     unsigned char month = read_cmos_register(0x08);
     unsigned char year = read_cmos_register(0x09);
     sprintf(buffer, "Date : %02x-%02x-%02x week : %02X\n", year, month, day_of_month, day_of_week);
 }
 void clear_screen() {
     printf("\033[2J\033[H");  // 清屏并将光标移动到左上角
 }
 int main() {
     if (ioperm(CMOS_ADDR_STANDARD, 2, 1) != 0) {
         perror("Failed to get I/O port permissions");
         return 1;
     }
     if (ioperm(CMOS_ADDR_EXTENDED, 2, 1) != 0) {
         perror("Failed to get I/O port permissions");
         return 1;
     }
     system("clear");
     char buffer[1024];  // 缓冲区
    // 隐藏光标
    printf("%s","\033[?25l");
     while (1) {
         clear_screen();  // 清屏

         // 将内容写入缓冲区
         print_cmos_table_to_buffer(buffer);
         print_cmos_date_to_buffer(buffer + strlen(buffer));
         print_cmos_time_to_buffer(buffer + strlen(buffer));
         printf("%s","\033[?25l");
         // 一次性输出缓冲区内容
         printf("%s", buffer);

         sleep(1);
     }

     ioperm(CMOS_ADDR_STANDARD, 2, 0);
     ioperm(CMOS_ADDR_EXTENDED, 2, 0);
     return 0;
 }