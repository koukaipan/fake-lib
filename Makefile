all: main encode_fake.so encode_true.so

main: main.c encode_fake.so
	gcc -g main.c encode_fake.so -o main -Xlinker -rpath ./

encode_fake.so: encode_fake.c
	gcc -g encode_fake.c -fPIC -shared -o encode_fake.so -ldl

encode_true.so: encode_true.c
	gcc -g encode_true.c -fPIC -shared -o encode_true.so

run: all
	./main

clean:
	rm main encode_fake.so encode_true.so
