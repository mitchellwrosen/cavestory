CC=g++
CFLAGS=-Wall
LDFLAGS=-Wall

SRCS=$(wildcard *.cc **/*.cc)
OBJS=$(patsubst %.cc,%.o,$(SRCS))
INC=-I.
LIBS=-lSDL

EXE=cavestory

all: $(EXE)

debug: CC += -g -DDEBUG
debug: $(EXE)

release: CC += -O3
release: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(INC) $(OBJS) $(LIBS) -o $(EXE)

%.o: %.cc
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(EXE)
