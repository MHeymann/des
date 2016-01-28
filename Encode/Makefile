#OBJS specifies which files to compile as part of the project
OBJS = expand.o substitution.o permute.o feistel.o encode.o testencode.c

#CC specifies which compiler we're using
CC = gcc

# RM is the comand for removing binaries.  
RM = rm -f

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS 	= -Wall -ansi -pedantic
DFLAGS			= -DDEBUGFLAG# -DVERBOSE

#LINKER_FLAGS specifies the libraries we're linking against

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = testencode

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(DFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

expand.o: Feistel/Expansion/expand.c Feistel/Expansion/expand.h
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

substitution.o: Feistel/Substitution/substitution.c Feistel/Substitution/substitution.h
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

feistel.o:	Feistel/feistel.c	Feistel/Expansion/expand.h	Feistel/Substitution/substitution.h
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

permute.o: Permutation/permute.c
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<

encode.o: encode.c
	$(CC) $(COMPILER_FLAGS) $(DFLAGS) -c $<


clean: 
	$(RM) *.o $(OBJ_NAME)
