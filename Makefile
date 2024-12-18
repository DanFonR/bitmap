CC 	  ?= clang
SOURCE = ./src/bitmap.c ./src/bitmap.h
OUTPUT = bitmap-gen
ARGS   = -O3 -Wno-pragma-pack

examples : exec
	@ ./$(OUTPUT) --example 1
	@ # @ ./$(OUTPUT) --example 2
	@ echo "example image generated"
	@ rm $(OUTPUT)
	@ echo "executable deleted"

exec : *.o
	@ $(CC) $^ -o $(OUTPUT) $(ARGS) 
	@ rm -f $^ *.pch ./src/$^ ./src/*.pch
	@ echo "$(OUTPUT) generated"

*.o : $(SOURCE)
	@ echo "compiling files..."
	@ $(CC) $^ -c $(ARGS)

clean :
	@ rm -f bitmap-gen example1.bmp example2.bmp bitmap.o
	@ echo "everything cleaned up"
