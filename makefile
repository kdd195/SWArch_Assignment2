DRIVEROBJ=\
	driver.o\
	inventory.o\
	cart.o\
	orderHistory.o

all: driver

driver: $(DRIVEROBJ)
	g++ $(DRIVEROBJ) -o driver

driver.o: driver.cpp
	g++ -c -o driver.o driver.cpp

inventory.o: inventory.cpp
	g++ -c -o inventory.o inventory.cpp

cart.o: cart.cpp
	g++ -c -o cart.o cart.cpp

orderHistory.o: orderHistory.cpp
	g++ -c -o orderHistory.o orderHistory.cpp

clean:
	\rm *.o driver
