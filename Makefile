all: myls.o myShell.o mycd.o mycp.o myps.o mygrep.o myman.o
	gcc  *.o -lreadline -o myShell  && rm *.o 
myShell.o: myShell.c
	gcc -c myShell.c -o myShell.o
mycd.o: mycd.c
	gcc -c mycd.c -o mycd.o
myls.o: myls.c
	gcc -c myls.c -o myls.o
mycp.o: mycp.c
	gcc -c mycp.c -o mycp.o
myps.o: myps.c
	gcc -c myps.c -o myps.o
mygrep.o:
	gcc -c mygrep.c -o mygrep.o
myman.o:
	gcc -c myman.c -o myman.o
clean:
	rm myShell 
