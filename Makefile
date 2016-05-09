DEVICEID := $(shell cat .deviceid)


build:
	particle compile photon cellar-sensor.ino 

build-cloud:
	particle cloud compile photon cellar-sensor.ino 

flash:
	particle flash $(DEVICEID) cellar-sensor.ino 

clean:
	rm *.bin
