/**
 * @Author: jieliu
 * @Date: 2/24/2025, 2:06:57 PM
 * @LastEditors: jieliu
 * @LastEditTime: 2/24/2025, 5:24:14 PM
 * Description: read and print pcie config memory infomation
 */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdlib.h>

// PCI 配置空间访问的 IO 端口
#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA 0xCFC

// ANSI 转义序列
#define ANSI_COLOR_YELLOW "\x1b[93m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[91m" // 红色

// 配置地址生成
uint32_t pci_config_address(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
    return (1 << 31) |      // 使能位
           (bus << 16) |    // 总线号
           (dev << 11) |    // 设备号
           (func << 8) |    // 功能号
           (offset & 0xFC); // 寄存器偏移（对齐到 4 字节）
}

// 读取32位配置寄存器
uint32_t pci_read_config(uint8_t bus, uint8_t dev, uint8_t func, uint8_t offset)
{
    outl(pci_config_address(bus, dev, func, offset), PCI_CONFIG_ADDRESS);
    return inl(PCI_CONFIG_DATA);
}

// 检查设备是否存在
int device_exists(uint8_t bus, uint8_t dev, uint8_t func)
{
    uint32_t vendor = pci_read_config(bus, dev, func, 0x00);
    return (vendor != 0xFFFFFFFF && (vendor & 0xFFFF) != 0xFFFF);
}

void print_config_info(uint8_t bus, uint8_t device, uint8_t func)
{
    // 读取 Vendor ID 和 Device ID
    uint32_t vendor_device = pci_read_config(bus, device, func, 0x00);
    uint16_t vendor_id = vendor_device & 0xFFFF;
    uint16_t device_id = (vendor_device >> 16) & 0xFFFF;

    // 读取 Class Code、Subclass 和 Prog IF
    uint32_t class_rev = pci_read_config(bus, device, func, 0x08);
    uint8_t class_code = (class_rev >> 24) & 0xFF;
    uint8_t subclass = (class_rev >> 16) & 0xFF;
    uint8_t prog_if = (class_rev >> 8) & 0xFF;

    // 读取子系统信息
    uint32_t subsystem_info = pci_read_config(bus, device, func, 0x2C);
    uint16_t subsystem_vendor_id = subsystem_info & 0xFFFF;
    uint16_t subsystem_device_id = (subsystem_info >> 16) & 0xFFFF;

    // 打印基础信息
    printf("\n== PCI Device @ %02X:%02X.%X ==\n", bus, device, func);
    printf("  Vendor: %04X  Device: %04X\n", vendor_id, device_id);
    printf("  Class: %02X  Subclass: %02X  Prog IF: %02X\n", class_code, subclass, prog_if);
    printf("  Subsystem: %04X:%04X\n", subsystem_vendor_id, subsystem_device_id);

    // 判断设备类型
    if (class_code == 0x06)
    { // 桥设备
        const char *bridge_type = "Generic PCI Bridge";
        switch (subclass)
        {
        case 0x04:
            bridge_type = "PCI-to-PCI Bridge";
            break;
        case 0x05:
            bridge_type = "PCI-to-CardBus Bridge";
            break;
        case 0x06:
            bridge_type = "RACEway Bridge";
            break;
        case 0x07:
            bridge_type = "PCI-to-PCI (Subtractive)";
            break;
        case 0x09:
            bridge_type = "PCI Host Bridge";
            break;
        }

        printf("  Device Type: %s\n", bridge_type);

        // 读取桥设备专用信息
        uint32_t bridge_config = pci_read_config(bus, device, func, 0x18);
        uint8_t secondary_bus = (bridge_config >> 8) & 0xFF;
        uint8_t subordinate_bus = (bridge_config >> 16) & 0xFF;

        printf("  Secondary Bus: %02X\n", secondary_bus);
        printf("  Subordinate Bus: %02X\n", subordinate_bus);

        // 读取I/O和内存地址范围
        uint32_t io_base = pci_read_config(bus, device, func, 0x1C);
        uint32_t mem_base = pci_read_config(bus, device, func, 0x20);
        printf("  I/O Base: 0x%08X\n  Mem Base: 0x%08X\n", io_base, mem_base);
    }
    else
    { // 普通设备
        const char *device_type = "Unknown Device";
        switch (class_code)
        {
        case 0x01:
            device_type = "Mass Storage Controller";
            break;
        case 0x02:
            device_type = "Network Controller";
            break;
        case 0x03:
            device_type = "Display Controller";
            break;
        case 0x04:
            device_type = "Multimedia Controller";
            break;
        case 0x05:
            device_type = "Memory Controller";
            break;
        case 0x06:
            device_type = "Bridge Device";
            break;
        case 0x07:
            device_type = "Communication Controller";
            break;
        case 0x08:
            device_type = "Generic System Peripheral";
            break;
        case 0x09:
            device_type = "Input Device";
            break;
        case 0x0A:
            device_type = "Docking Station";
            break;
        case 0x0B:
            device_type = "Processor";
            break;
        case 0x0C:
            device_type = "Serial Bus Controller";
            break;
        }

        printf("  Device Type: %s\n", device_type);

        // 显示具体设备类型（示例：显示控制器）
        if (class_code == 0x03 && subclass == 0x00)
        {
            printf("  [VGA Compatible Controller]\n");
        }

        // 读取并显示BAR信息
        uint32_t bar0 = pci_read_config(bus, device, func, 0x10);
        uint32_t bar1 = pci_read_config(bus, device, func, 0x14);
        uint32_t bar2 = pci_read_config(bus, device, func, 0x18);
        uint32_t bar3 = pci_read_config(bus, device, func, 0x1C);
        uint32_t bar4 = pci_read_config(bus, device, func, 0x20);
        uint32_t bar5 = pci_read_config(bus, device, func, 0x24);

        printf("  BAR0: 0x%08X\n  BAR1: 0x%08X\n  BAR2: 0x%08X\n", bar0, bar1, bar2);
        printf("  BAR3: 0x%08X\n  BAR4: 0x%08X\n  BAR5: 0x%08X\n", bar3, bar4, bar5);

        // 读取中断信息
        uint8_t int_line = pci_read_config(bus, device, func, 0x3C) & 0xFF;
        uint8_t int_pin = (pci_read_config(bus, device, func, 0x3C) >> 8) & 0xFF;
        printf("  IRQ Line: %02X\n  IRQ Pin:  %02X\n", int_line, int_pin);
    }
    printf("\n");
}

// 打印配置空间内容
void print_config_space(uint8_t bus, uint8_t dev, uint8_t func)
{
    print_config_info(bus, dev, func);
    printf(ANSI_COLOR_RED "    00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f\n" ANSI_COLOR_RESET);
    printf("   +------------------------------------------------+\n");

    for (int row = 0; row < 4; row++)
    {
        printf(ANSI_COLOR_RED "%02x" ANSI_COLOR_RESET " |", row * 16);
        for (int col = 0; col < 16; col++)
        {
            uint8_t offset = row * 16 + col;
            uint32_t value = pci_read_config(bus, dev, func, offset & 0xFC);
            uint8_t byte_value = (value >> ((offset % 4) * 8)) & 0xFF;

            if (byte_value != 0)
            {
                printf(ANSI_COLOR_YELLOW "%02x " ANSI_COLOR_RESET, byte_value);
            }
            else
            {
                printf("%02x ", byte_value);
            }
        }
        printf("|\n");
    }

    printf("   +------------------------------------------------+\n");
}

// 递归扫描PCI总线
void scan_bus(uint8_t bus);

// 处理PCI-PCI桥设备
void process_bridge(uint8_t primary_bus, uint8_t dev, uint8_t func)
{
    uint32_t config = pci_read_config(primary_bus, dev, func, 0x18);
    uint8_t secondary_bus = (config >> 8) & 0xFF;
    printf("Found PCI-PCI Bridge at %02x:%02x.%x -> Secondary Bus %02x\n",
           primary_bus, dev, func, secondary_bus);
    scan_bus(secondary_bus);
}

// 扫描单个设备
void scan_device(uint8_t bus, uint8_t dev)
{
    for (uint8_t func = 0; func < 8; func++)
    {
        if (!device_exists(bus, dev, func))
            continue;

        print_config_space(bus, dev, func);

    }
}

// 扫描整个总线
void scan_bus(uint8_t bus)
{
    for (uint8_t dev = 0; dev < 32; dev++)
    {
        // 快速检测：如果设备 dev 功能 0 不存在则跳过整个设备
        if (dev > 0 && !device_exists(bus, dev, 0))
            continue;

        scan_device(bus, dev);
    }
}

int main()
{
    if (iopl(3) != 0)
    {
        fprintf(stderr, "需要ROOT权限运行！\n");
        return 1;
    }

    //system("clear");

    printf("PCI/PCIe 设备配置空间扫描：\n");
    scan_bus(0); // 从总线0开始扫描

    iopl(0);
    return 0;
}
