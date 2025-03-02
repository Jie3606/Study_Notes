#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>

#define DMI_PATH "/sys/firmware/dmi/tables/DMI"
#define SMBIOS_ANCHOR "_SM_"
#define DMI_ANCHOR "_DMI_"

#pragma pack(push, 1)  // 禁用内存对齐
typedef struct {
    char anchor[4];       // 固定标识符 "_SM_"
    uint8_t checksum;     // EPS校验和
    uint8_t entry_len;    // EPS结构长度
    uint8_t major_ver;    // 主版本号 (e.g. 3 for SMBIOS 3.0)
    uint8_t minor_ver;    // 次版本号
    uint16_t max_size;    // 最大结构尺寸
    uint8_t ep_rev;       // EPS修订版本
    uint8_t formatted[5]; // 保留字段
    char dmi_anchor[5];   // 固定标识符 "_DMI_"
    uint8_t dmi_checksum;  // DMI校验和
    uint16_t table_len;   // DMI表总长度
    uint32_t table_addr;  // DMI表物理地址（SMBIOS 2.x）
    uint16_t num_structs; // 结构体总数
    uint8_t bcd_rev;      // BCD修订版本
} SMBIOS_EPS;
#pragma pack(pop)         // 恢复默认对齐


typedef struct {
    uint8_t type;
    uint8_t length;
    uint16_t handle;
    uint8_t data[];
} SMBIOS_STRUCT;

const char *bios_chars[] = {
    "ISA is supported",
    "PCI is supported",
    "PNP is supported",
    "BIOS is upgradeable",
    "BIOS shadowing is allowed",
    "ESCD support is available",
    "Boot from CD is supported",
    "Selectable boot is supported",
    "BIOS ROM is socketed",
    "EDD is supported",
    "5.25\"/360 kB floppy services are supported (int 13h)",
    "5.25\"/1.2 MB floppy services are supported (int 13h)",
    "3.5\"/720 kB floppy services are supported (int 13h)",
    "3.5\"/2.88 MB floppy services are supported (int 13h)",
    "Print screen service is supported (int 5h)",
    "8042 keyboard services are supported (int 9h)",
    "Serial services are supported (int 14h)",
    "Printer services are supported (int 17h)",
    "CGA/mono video services are supported (int 10h)",
    "AGP is supported",
    "LS-120 boot is supported",
    "ATAPI Zip drive boot is supported",
    "BIOS boot specification is supported"
};

void print_header(SMBIOS_EPS *eps) {
    printf("# dmidecode 3.3\n");
    printf("Getting SMBIOS data from sysfs.\n");
    printf("SMBIOS %d.%d present.\n", eps->major_ver, eps->minor_ver);
    printf("%d structures occupying %d bytes.\n",
           eps->num_structs, eps->table_len);
    printf("Table at 0x%08X.\n\n", eps->table_addr);
}

char* get_string(SMBIOS_STRUCT *s, uint8_t index) {
    if (index == 0) return "Not Specified";
    char *p = (char*)s + s->length;

    while (--index) {
        p += strlen(p) + 1;
        if (*p == 0 && *(p+1) == 0) return "BAD INDEX";
    }
    return p;
}

void print_bios(SMBIOS_STRUCT *s) {
    printf("Handle 0x%04X, DMI type %d, %d bytes\n",
           s->handle, s->type, s->length);
    printf("BIOS Information\n");

    printf("\tVendor: %s\n", get_string(s, s->data[4]));
    printf("\tVersion: %s\n", get_string(s, s->data[5]));
    printf("\tRelease Date: %s\n", get_string(s, s->data[8]));
    printf("\tAddress: 0x%04X\n", *(uint16_t*)(s->data+6));
    printf("\tRuntime Size: %d kB\n", s->data[10] * 64);
    printf("\tROM Size: %d kB\n", (1 << s->data[11]) * 512);

    printf("\tCharacteristics:\n");
    uint64_t chars = *(uint64_t*)(s->data+0x0C);
    for (int i=0; i<23; i++) {
        if (chars & (1ULL << i))
            printf("\t\t%s\n", bios_chars[i]);
    }
}

void print_system(SMBIOS_STRUCT *s) {
    printf("Handle 0x%04X, DMI type %d, %d bytes\n",
           s->handle, s->type, s->length);
    printf("System Information\n");

    printf("\tManufacturer: %s\n", get_string(s, s->data[4]));
    printf("\tProduct Name: %s\n", get_string(s, s->data[5]));
    printf("\tVersion: %s\n", get_string(s, s->data[6]));
    printf("\tSerial Number: %s\n", get_string(s, s->data[7]));

    uint8_t *uuid = s->data + 8;
    printf("\tUUID: ");
    for(int i=0; i<16; i++)
        printf("%02X%c", uuid[i], (i==3||i==5||i==7||i==9)?'-':' ');
    printf("\n");
}

int main() {
    int fd = open(DMI_PATH, O_RDONLY);
    if (fd == -1) { /* 错误处理 */ }

    SMBIOS_EPS eps;
    ssize_t read_size = read(fd, &eps, sizeof(eps));
    close(fd);

    // 新增验证步骤
    if (read_size != sizeof(eps)) {
        fprintf(stderr, "读取EPS结构不完整: %zd/%zu 字节\n",
                read_size, sizeof(eps));
        return 1;
    }

    if (memcmp(eps.anchor, "_SM_", 4) != 0) {
        fprintf(stderr, "无效的SMBIOS锚点签名: %.4s\n", eps.anchor);
        return 1;
    }

    if (memcmp(eps.dmi_anchor, "_DMI_", 5) != 0) {
        fprintf(stderr, "无效的DMI锚点签名: %.5s\n", eps.dmi_anchor);
        return 1;
    }

    uint8_t checksum = 0;
    for (int i = 0; i < eps.entry_len; i++) {
        checksum += ((uint8_t*)&eps)[i];
    }
    if (checksum != 0) {
        fprintf(stderr, "校验和验证失败: 0x%02X\n", checksum);
        return 1;
    }



    print_header(&eps);

    fd = open(DMI_PATH, O_RDONLY);
    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    uint8_t *dmi = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    uint8_t *p = dmi + sizeof(SMBIOS_EPS);

    int struct_count = 0;
    while (p < dmi + size) {
        SMBIOS_STRUCT *s = (SMBIOS_STRUCT*)p;
        if (s->type == 127) break;

        switch(s->type) {
            case 0: print_bios(s); break;
            case 1: print_system(s); break;
            // 可扩展其他类型...
        }

        p += s->length;
        while (*p != 0 || *(p+1) != 0) p++;
        p += 2;
        struct_count++;
    }

    printf("\nWrong DMI structures count: %d announced, only %d decoded.\n",
           eps.num_structs, struct_count);

    munmap(dmi, size);
    close(fd);
    return 0;
}