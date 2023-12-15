sgr: sgr_process.o
	gcc -Wall sgr.c -o sgr sgr_process.o -g

sgr_process.o: sgr_process.c
	gcc -c sgr_process.c