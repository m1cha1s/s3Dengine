.PHONy: all

all: main s3Dengine
	gcc -o s3Dengine ./build/main ./build/s3Dengine

main:
	gcc -c -o ./build/main ./src/main.c

s3Dengine:
	gcc -c -o ./build/s3Dengine ./src/s3Dengine.c


dev: all
	./s3Dengine