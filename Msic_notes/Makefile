# 定义变量
SRC_DIR := src
BIN_DIR := bin
INCLUDE_DIR := include
CC := gcc

CFLAGS := -g3 -std=c11 -Wall -I$(INCLUDE_DIR) # 添加头文件搜索路径和编译选项

# 定义目标文件名
TARGET := $(BIN_DIR)/main

# 收集源文件
SRCS := $(wildcard $(SRC_DIR)/*.c)

# 生成对象文件名
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# 定义伪目标
.PHONY: all clean run

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# 编译C源文件到对象文件
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 创建目录目标（确保目录存在）
$(BIN_DIR):
	mkdir -p $@

# 清理目标
clean:
	rm -rf $(BIN_DIR)/*
# 运行目标
run:
	./bin/main