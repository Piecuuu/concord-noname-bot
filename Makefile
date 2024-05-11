SRC = src
CMDDIR = $(SRC)/commands
EVEDIR = $(SRC)/events

ROOT = $(SRC)/bot.o $(SRC)/config.o $(SRC)/main.o $(SRC)/event.o $(SRC)/command.o \
       $(SRC)/db.o
EVENTS = $(EVEDIR)/interaction_create.o $(EVEDIR)/ready.o
COMMANDS = $(CMDDIR)/ping.o

OBJS = $(COMMANDS) $(EVENTS) $(ROOT)

PROGRAM = bot

CC = cc
CCLD = cc
CFLAGS = -g -I/usr/local/include -std=gnu99
LDFLAGS = -ldiscord -lcurl -ltoml -lpq

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(PROGRAM): $(OBJS)
	$(CCLD) -o $(PROGRAM) $(OBJS) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean

clean:
	rm -f $(OBJS) $(PROGRAM) *.db *.log
