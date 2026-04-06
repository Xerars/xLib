# [Makefile] - xDLoad Sample

# [Compiler]
CC       := gcc
AR       := ar -rcs
RM       := rm -f
MKDIR    := mkdir -p

# [Include]
INC_DIRS := ../								\
						../../../
INC      := $(foreach dir,$(INC_DIRS),-I$(dir))

# [Library]
LIB_DIRS := ../Lib
LIB      := $(foreach dir,$(LIB_DIRS),-L$(dir))
LINKER   := -lxDLoad
SLINK    := ../Lib/libxDLoad.a

# [Flags]
CFLAGS   := -std=c99 -Wall -Wextra -O3 $(INC)
LDFLAGS  := $(LIB) $(LINKER) 

# [Folder]
DIR_LIB  := Lib
DIR_BIN  := Bin

# [Source]
SRC1     := Sample1.c
OBJ1     := $(SRC1:.c=.o)

SRC2     := Sample2.c
OBJ2     := $(SRC2:.c=.o)

SRC_MOD  := Module.c
OBJ_MOD  := $(SRC_MOD:.c=.o)

# [Module Lib]
MOD_SLIB := $(DIR_LIB)/libModule.a
MOD_DLIB := $(DIR_LIB)/libModule.so
MOD_DLL  := $(DIR_LIB)/Module.dll

# [Target]
TARGET1  := $(DIR_BIN)/Sample1
TARGET2  := $(DIR_BIN)/Sample2

# [Memory]
VAL_BIN  := valgrind
VAL_FLAG := --leak-check=full --show-leak-kinds=all --track-origins=yes

VAL_LOG1 := --log-file=$(TARGET1).valgrid
VAL_LOG2 := --log-file=$(TARGET2).valgrid

# [Phony]
.PHONY: all FOLDER LIB MODULE SAMPLE1 SAMPLE2 MEM1 MEM2 clean

all: LIB MODULE SAMPLE1 SAMPLE2

check: MEM1 MEM2

FOLDER:
	@$(MKDIR) $(DIR_LIB)
	@$(MKDIR) $(DIR_BIN)

LIB:
	@$(MAKE) -C .. all


MODULE: FOLDER $(OBJ_MOD)
	$(AR) $(MOD_SLIB) $(OBJ_MOD)
	$(CC) -shared -o $(MOD_DLIB) $(OBJ_MOD)
	$(CC) -shared -o $(MOD_DLL)  $(OBJ_MOD)


SAMPLE1: FOLDER $(OBJ1) LIB
	$(CC) -o $(TARGET1) $(OBJ1) $(SLINK)

SAMPLE2: FOLDER $(OBJ2) LIB
	$(CC) -o $(TARGET2) $(OBJ2) $(SLINK)

MEM1: 
	$(VAL_BIN) $(VAL_FLAGS) $(VAL_LOG1) ./$(TARGET1)

MEM2: 
	$(VAL_BIN) $(VAL_FLAGS) $(VAL_LOG2) ./$(TARGET2)

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) $(OBJ1) $(OBJ2) $(OBJ_MOD)
	$(RM) -rf $(DIR_LIB) $(DIR_BIN)
	@$(MAKE) -C .. clean
