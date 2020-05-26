TARGET=app.o
SRCDIR := src
OUTDIR := build
SRCS := $(shell ls $(SRCDIR)/*.c)
OBJS := $(addprefix $(OUTDIR)/,$(patsubst %.c,%.o,$(SRCS)))

CC = gcc 
CFLAGS = -g -Wall -O2 -MMD -MP

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o:%.c
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OUTDIR)
