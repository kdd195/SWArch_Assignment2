DRIVEROBJ=\
	client.o\
	packet.o

all: driver

driver: $(DRIVEROBJ)
	g++ $(DRIVEROBJ) -o driver

driver.o: driver.cpp
	g++ -c -o driver.o driver.cpp

clean:
	\rm *.o driver
