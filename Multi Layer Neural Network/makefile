PROGNAME=nn
#Compiler
CC=g++

#Compiler Options for C++
CCFLAGS=-O
#Compiler Options for C
CFLAGS=$(CFLAGS)

#Source cpp files
SRCS=\
main.cpp\
Matrix.cpp\
MLP.cpp

#Header files
HDRS=\
Matrix.h\
MLP.h


ALLFILES=$(HDRS) $(SRCS) makefile


# main:	main.o 
# 	$(CC) -o $(PROGNAME) $(CCFLAGS) main.o

# g++    -c -o main.o main.cpp
# g++ -o Program main.cpp


main:	$(SRCS) 
	$(CC) -o $(PROGNAME) $(SRCS)

core:	main.o
	$(CC) -o $(PROGNAME) main.o -g

debug:
	gdb $(PROGNAME) core

all:
	touch  $(HDRS) $(SRCS)
	make

size:$(HDRS) $(SRCS)
	wc $?

srcs:	$(HDRS)  $(SRCS)
	echo $(HDRS)  $(SRCS)

allfiles: $(ALLFILES)
	echo $(ALLFILES)

clean:
	rm -f *.o *.exe core

#Make a backup file
backup: $(ALLFILES)
	mkdir -p Backup
	cp $(ALLFILES) Backup
	# shar $(ALLFILES) | gzip > Backup/backup


#Make a tar file
DATE=$(shell date +"%Y.%m.%d.%H.%M.%S")
SUBMISSION=Submit
tar:
	#rm $(SUBMISSION)/*.tar
	mkdir -p $(SUBMISSION)
	tar -cvf $(SUBMISSION)/$(PROGNAME)_$(DATE).tar $(ALLFILES)


# $(date +"%Y_%m_%d_%H_%M_%S")

# If you're on GNU Make, use the := assignment instead of =. This assignment causes the right hand side to be expanded immediately, and stored in the left hand variable.
# FILES := $(shell ...)  # expand now; FILES is now the result of $(shell ...)
# FILES = $(shell ...)   # expand later: FILES holds the syntax $(shell ...)
