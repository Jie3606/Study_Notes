#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct __attribute__((packed)) {
    uint8_t type;
    uint8_t length;
    uint16_t handle;
} dmi_header;

// 读取 SMBIOS 数据
int read_smbios_data(uint8_t **buffer, size_t *size)
{
    FILE *fp = fopen("/sys/firmware/dmi/tables/DMI", "rb");
    if (!fp)
    {
        perror("Failed to open DMI table");
        return -1;
    }

    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    rewind(fp);

    *buffer = (uint8_t *)malloc(*size);
    if (!*buffer)
    {
        perror("Memory allocation failed");
        fclose(fp);
        return -1;
    }

    fread(*buffer, 1, *size, fp);
    fclose(fp);
    return 0;
}

// 打印十六进制数据
void hexdump(const void *buffer, size_t size)
{
    const unsigned char *p = (const unsigned char *)buffer;
    size_t offset = 0;
#define ADDR_WIDTH 8
#define HEX_COLS 16
#define GROUP_SIZE 8

    while (offset < size)
    {
        printf("%08lx  ", offset);
        size_t line_size = (size - offset) > HEX_COLS ? HEX_COLS : (size - offset);

        for (size_t i = 0; i < line_size; i++)
        {
            printf("%02x ", p[offset + i]);
            if (i == GROUP_SIZE - 1)
                printf(" ");
        }

        for (size_t i = line_size; i < HEX_COLS; i++)
        {
            printf("   ");
            if (i == GROUP_SIZE - 1)
                printf(" ");
        }

        printf(" |");
        for (size_t i = 0; i < line_size; i++)
        {
            printf("%c", isprint(p[offset + i]) ? p[offset + i] : '.');
        }
        printf("|\n");

        offset += line_size;
    }
}

// 解析 UUID
void parse_uuid(const uint8_t *p, int version)
{
    char uuid[37];
    if (version >= 0x0206) // UUID 采用小端序
        snprintf(uuid, sizeof(uuid),
                 "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                 p[3], p[2], p[1], p[0], p[5], p[4], p[7], p[6],
                 p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
    else
        snprintf(uuid, sizeof(uuid),
                 "%02X%02X%02X%02X-%02X%02X-%02X%02X-%02X%02X-%02X%02X%02X%02X%02X%02X",
                 p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7],
                 p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);

    printf("System UUID: %s\n", uuid);
}

// 解析 DMI 数据
void parse_smbios(uint8_t *buffer, size_t size)
{
    uint8_t *p = buffer;
    while (p < buffer + size)
    {
        dmi_header *h = (dmi_header *)p;
        if (h->length < sizeof(dmi_header))
            break;

        if (h->type == 1) // System Information
        {
            printf("\n[System Information]\n");
            parse_uuid(p + 0x08, 0x0206);
        }

        // 跳到下一个结构体
        p += h->length;
        while (p < buffer + size && (p[0] != 0 || p[1] != 0))
            p++;
        p += 2;
    }
}

int main()
{
    uint8_t *smbios_data = NULL;
    size_t smbios_size = 0;

    if (read_smbios_data(&smbios_data, &smbios_size) != 0)
        return 1;

    hexdump(smbios_data, smbios_size);
    parse_smbios(smbios_data, smbios_size);

    free(smbios_data);
    return 0;
}
