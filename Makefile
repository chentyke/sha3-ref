.PHONY: all clean test

CC = gcc

CFLAGS = -Wall -g -std=c11

# If you want to DEBUG and see which step has an error,
# please comment out the CFLAGS on the previous line and enable the following line.

#CFLAGS = -Wall -g -std=c11 -DDEBUG
LDFLAGS = -lpthread

OBJS = round.o keccak_f.o sponge.o main.o
TARGET = sha3

all: $(TARGET) test

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	@echo "Running $(TARGET) with sample message..."
	./$(TARGET)

clean:
	rm -rf $(OBJS) $(TARGET)