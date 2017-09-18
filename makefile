DRIVEROBJ=\
	driver.o\
	inventory.o

all: driver

driver: $(DRIVEROBJ)
	g++ $(DRIVEROBJ) -o driver

driver.o: driver.cpp
	g++ -c -o driver.o driver.cpp

inventory.o: inventory.cpp
	g++ -c -o inventory.o inventory.cpp

clean:
	\rm *.o driver
