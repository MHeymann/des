#OBJS specifies which files to compile as part of the project
OBJS = expand.o substitution.o feistel.o testfeistel.c

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
OBJ_NAME = testfeistel

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(DFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

expand.o: Expansion/expand.c
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

substitution.o: Substitution/substitution.c
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

feistel.o: feistel.c
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

clean: 
	$(RM) *.o $(OBJ_NAME)
