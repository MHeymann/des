#OBJS specifies which files to compile as part of the project
OBJS = keys.c

#CC specifies which compiler we're using
CC = gcc

# RM is the comand for removing binaries.  
RM = rm -f

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS 	= -Wall -ansi -pedantic
DFLAGS			= -DDEBUGFLAG

#LINKER_FLAGS specifies the libraries we're linking against

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = keys

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(DFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean: 
	$(RM) *.o $(OBJ_NAME)
