#
# Makefile 
#

SYSTEMC = /opt/lib/systemc-2.3.1
TARGET_ARCH = linux64
WAVE_VIEWER = simvision
CC = g++

LIBS   = -lsystemc 
LIBDIR = -L. -L$(SYSTEMC)/lib-$(TARGET_ARCH)
INCDIR = ./ -I$(SYSTEMC)/include

TARGET = intctrl_prio
VPATH = ./

.SUFFIXES: .cpp .o

SRCS = main.cpp tb.cpp ic.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CC) $(LIBDIR) -o $@ $(OBJS) ${LIBS}

%.o: %.cpp
	$(CC) $(INCDIR) -c -o $@ $<

clean:
	rm -f *.o $(TARGET) *.dsn *.trn *.vcd -rf

run:
	make $(TARGET)
	./$(TARGET)

wave:
	$(WAVE_VIEWER) $(TARGET).vcd
