CC 	  ?= clang
SOURCE = ./src/bitmap.c ./src/bitmap.h
ARGS   = -O3 -Wno-pragma-pack

bitmap_test.bmp : bitmap-gen
	@ ./$^ $@
	@ echo "image generated"
	@ rm $^
	@ echo "executable deleted"

bitmap-gen : *.o
	@ $(CC) $< -o $@ $(ARGS) 
	@ rm -f $< *.pch ./src/$< ./src/*.pch
	@ echo "$@ generated"

*.o : $(SOURCE)
	@ echo "compiling files..."
	@ $(CC) $^ -c $(ARGS)

clean:
	@ rm -f bitmap-gen *.bmp
	@ echo "everything cleaned up"

exec : bitmap-gen
