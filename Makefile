CC = clang

server.out: server.c
	$(CC) $^ -o $@


run: 
	./server.out

clean:
	rm server.out


push:
	git add .
	git commit -m "$(m)"
	git push origin $(b)