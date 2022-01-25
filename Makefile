
all: vint

vint: vint.c
	cc -o $@ $<

clean:
	-rm -f vint

.PHONY: all clean
