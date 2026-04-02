# [Makefile] - xDLoad LIB

# [X]: GCC
# [X]: TCC
# [X]: CLANG
# [X]: ARM-GCC

# [Compiler]
CC      	:= gcc
AR      	:= ar -rcs
RM      	:= rm
MKDIR   	:= mkdir -p

# [Include]
INC_DIR 	:= ../../
INC     	:= $(foreach dir,$(INC_DIR),-I$(dir))

# [Flag]
CFLAGS  	:= -std=c99 -Wall -Wextra -O3 $(INC)
LDFLAGS 	:= 

# [Folder]
DIR_LIB 	:= Lib

# [Source]
SRC     	:= xDLoad.c
OBJ     	:= $(SRC:.c=.o)

# [Lib]
DLIB_NAME	:= $(DIR_LIB)/libxDLoad.so
SLIB_NAME	:= $(DIR_LIB)/libxDLoad.a
DLL_NAME	:= $(DIR_LIB)/xDLoad.dll

# [Info]
INFO_NAME := $(DIR_LIB)/DLoad.info

# [Content]
.PHONY: all FOLDER DLIB SLIB DLL clean

all: DLIB SLIB DLL INFO

FOLDER:
	@$(MKDIR) $(DIR_LIB)

SLIB: FOLDER
	$(AR) $(SLIB_NAME) $(OBJ)

DLIB: FOLDER $(OBJ)
	$(CC) -shared -o $(DLIB_NAME) $(OBJ) $(LDFLAGS)

DLL: FOLDER $(OBJ)
	$(CC) -shared -o $(DLL_NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

INFO:
	@echo "Generate Information"
	@echo "[SIZE]" 							>> $(INFO_NAME)
	@size $(SLIB_NAME)   				>> $(INFO_NAME)
	@echo "" 										>> $(INFO_NAME)
	@echo "" 										>> $(INFO_NAME)
	@echo "[SYMBOL]" 						>> $(INFO_NAME)
	@nm -S $(SLIB_NAME) 				>> $(INFO_NAME)
	@echo "OUT: $(INFO_NAME)"

# [Remove]
clean:
	$(RM) -rf $(DIR_LIB)
	$(RM) $(OBJ)
