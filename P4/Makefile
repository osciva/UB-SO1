# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)

default: plantilla

exercici: plantilla.o
	gcc plantilla.o -o plantilla -lm

# Creating object files
plantilla.o: plantilla.c  
	gcc -c plantilla.c


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) plantilla *.o *~


