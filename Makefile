.PHONY: clean push run
CC = clang

CF = $(wildcard *.c)
OF = $(CF:.c=.out)



# compile all the c file to out
all: $(OF)

%.out: %.c
	$(CC) $^ -o $@


# will run all .out files
run :
	for item in $(OF); do ./$$item; done

clean:
	rm *.out


push:
	git add .
	git commit -m "$(m)"
	git push origin $(b)