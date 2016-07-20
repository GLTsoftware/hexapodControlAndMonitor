CC = gcc -g -Wall
BIN = hpPos hpCmd defaultChop customChop moveActuator hpStatus hpVel monitor
LFLAGS = -L/usr/local/lib
LIB = -lzmq

all: $(BIN)

monitor: monitor.o hpParameters.h getHPstatus.o getPMACinfo.o
	$(CC) -o monitor monitor.o getHPstatus.o getPMACinfo.o -lcurses $(LIB) ${LFAGS}

hpPos: hpPos.o hpParameters.h
	$(CC) -o hpPos hpPos.o $(LIB) ${LFAGS}

hpVel: hpVel.o hpParameters.h
	$(CC) -o hpVel hpVel.o $(LIB) ${LFAGS}

hpCmd: hpCmd.o hpParameters.h
	$(CC) -o hpCmd hpCmd.o $(LIB) ${LFAGS}

defaultChop: defaultChop.o hpParameters.h
	$(CC) -o defaultChop defaultChop.o $(LIB) ${LFAGS}

customChop: customChop.o hpParameters.h
	$(CC) -o customChop customChop.o $(LIB) ${LFAGS}

moveActuator: moveActuator.o hpParameters.h
	$(CC) -o moveActuator moveActuator.o $(LIB) ${LFAGS}

hpStatus: hpStatus.o getHPstatus.o hpParameters.h
	$(CC) -o hpStatus hpStatus.o getHPstatus.o $(LIB) ${LFAGS}

hpPos.o:  hpPos.c hpParameters.h
	$(CC) -c hpPos.c

hpCmd.o: hpCmd.c hpParameters.h
	$(CC) -c hpCmd.c

defaultChop.o: defaultChop.c hpParameters.h
	$(CC) -c defaultChop.c

customChop.o: customChop.c hpParameters.h
	$(CC) -c customChop.c

moveActuator.o: moveActuator.c hpParameters.h
	$(CC) -c moveActuator.c

hpStatus.o: hpStatus.c hpParameters.h
	$(CC) -c hpStatus.c

hpVel.o: hpVel.c hpParameters.h
	$(CC) -c hpVel.c

getHPstatus.o: getHPstatus.c hpParameters.h
	$(CC) -c getHPstatus.c

getPMACinfo.o: getPMACinfo.c hpParameters.h
	$(CC) -c getPMACinfo.c

monitor.o: monitor.c getHPstatus.c getPMACinfo.c hpParameters.h
	$(CC) -c monitor.c 
