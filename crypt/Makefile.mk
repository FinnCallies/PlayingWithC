.PHONY: all
all: main

main: main.o base64.o caesar.o crypt_util.o des.o rc4.o rsa.o vigenere.o
	gcc -o $@ $^

%.o: %.c
	gcc -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o main