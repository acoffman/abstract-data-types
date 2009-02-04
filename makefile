objects = AVL.o BST.o driver.o
cpp = g++

driver: $(objects)
	$(cpp) -o $@ $+

driver.o: driver.cpp
	$(cpp) -c driver.cpp

AVL.o: AVL.cpp AVL.h
	$(cpp) -c AVL.cpp

BST.o: BST.cpp BST.h
	$(cpp) -c BST.cpp


.PHONY: clean
clean: 
	rm $(objects) driver
