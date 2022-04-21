CC     = gcc
CFLAGS = -O -Wno-int-to-void-pointer-cast -Wno-void-pointer-to-int-cast -Wunused-value
ALL    = produto-threads produto

produto: produto.o  dclock.o
	$(CC) -o produto produto.o dclock.o -lm

produto.o: produto.c
	$(CC) $(CFLAGS) -c produto.c

produto-threads: produto-threads.o dclock.o
	$(CC) produto-threads.o dclock.o -o $@ -lpthread

produto-threads.o: produto-threads.c dclock.c

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(ALL)

clean:
	/bin/rm -f *.o *~ $(ALL)
