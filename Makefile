
all: vint

vint: vint.c
	cc -O2 -Wall -o $@ $<

clean:
	-rm -f vint

.PHONY: all clean
