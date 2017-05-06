object = main.o rb_tree.o

test : $(object)
	c99 -o test $(object)
	
main.o : rb_tree.h
rb_tree.o : rb_tree.h

.PHONY : clean

clean :
	rm -f test $(object)
