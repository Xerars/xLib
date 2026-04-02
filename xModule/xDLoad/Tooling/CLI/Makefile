# [Makefile] - DLoad CLI

# [Compiler]
CC       := gcc
AR       := ar -rcs
RM       := rm -f
MKDIR    := mkdir -p

# [Include]
INC_DIRS := ../								\
						../../../					\
						../../../../
INC      := $(foreach dir,$(INC_DIRS),-I$(dir))

# [Flags]
CFLAGS   := -std=c99 -Wall -Wextra -O3 $(INC)

# [Source]
SRC      := Tool_DLoad_CLI.c ../Tool_DLoad_Lib.c
OBJ      := $(SRC:.c=.o)

# [Target]
TARGET   := Tool_DLoad

# [Phony]
.PHONY: all clean

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^
	@echo "Build: $@"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(TARGET)
