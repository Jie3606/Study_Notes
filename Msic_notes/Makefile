# 定义默认变量
SRC_DIR ?= src
BIN_DIR ?= bin
INCLUDE_DIR ?= include
CC ?= gcc

# 设置删除和创建目录的命令
RM := rm -rf
MKDIR := mkdir -p

# 定义编译选项
DEBUG_FLAGS ?= -g3 -std=c11 -Wall
RELEASE_FLAGS ?= -O2 -std=c11 -Wall

# 默认使用调试模式
CFLAGS ?= $(DEBUG_FLAGS)

# 定义目标文件名
TARGET ?= $(BIN_DIR)/main

# 收集源文件和头文件
SRCS := $(wildcard $(SRC_DIR)/*.c)
INCLUDES := $(wildcard $(INCLUDE_DIR)/*.h)

# 生成对象文件名
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# 定义伪目标
.PHONY: all clean run debug release

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# 编译C源文件到对象文件
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) | $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# 创建目录目标（确保目录存在）
$(BIN_DIR):
	$(MKDIR) $@

# 清理目标
clean:
	$(RM) $(BIN_DIR)/*

# 运行目标
run:
	./$(TARGET)

# 调试模式
debug: CFLAGS := $(DEBUG_FLAGS)
debug: all

# 发布模式
release: CFLAGS := $(RELEASE_FLAGS)
release: all