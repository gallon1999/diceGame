# 編譯器與參數
CC = gcc
CFLAGS = -Wall -Wextra -IINC

# 檔案與目標
SRCS = main.c DiceGame.c
OBJS = $(SRCS:.c=.o)
TARGET = dicegame

# 編譯規則
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清除
clean:
	rm -f $(OBJS) $(TARGET)
