compile = g++

driver:
	$(compile) driver.cpp -o $@ 

.PHONY: clean
clean: 
	rm  driver
