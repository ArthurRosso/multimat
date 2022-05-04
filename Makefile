all: produto_gcc produto_icx produto_dpcpp produto_clang produto-openmp_gcc produto-openmp_icx produto-openmp_dpcpp produto-openmp_clang produto-pthreads_gcc produto-pthreads_icx produto-pthreads_dpcpp produto-pthreads_clang

produto_gcc: produto_gcc.o
	@gcc produto_gcc.o -o produto_gcc -lm -Ofast -march=native -mtune=native

produto_gcc.o: produto.c
	@gcc -c produto.c -o produto_gcc.o

produto_icx: produto_icx.o
	@icx produto_icx.o -o produto_icx -O3

produto_icx.o: produto.c
	@icx -w -c produto.c -o produto_icx.o

produto_dpcpp: produto_dpcpp.o
	@dpcpp produto_dpcpp.o -o produto_dpcpp

produto_dpcpp.o: produto.c
	@dpcpp -c produto.c -o produto_dpcpp.o

produto_clang: produto_clang.o 
	@clang produto_clang.o -o produto_clang -lm -Ofast -march=native -mtune=native

produto_clang.o: produto.c
	@clang -c produto.c -o produto_clang.o

produto-openmp_gcc: produto-openmp_gcc.o
	@gcc produto-openmp_gcc.o -o produto-openmp_gcc -fopenmp -lm -Ofast -march=native -mtune=native

produto-openmp_gcc.o: produto-openmp.c
	@gcc -c produto-openmp.c -o produto-openmp_gcc.o

produto-openmp_icx: produto-openmp_icx.o
	@icx produto-openmp_icx.o -o produto-openmp_icx -qopenmp -O3

produto-openmp_icx.o: produto-openmp.c
	@icx -w -c produto-openmp.c -o produto-openmp_icx.o

produto-openmp_dpcpp: produto-openmp_dpcpp.o
	@dpcpp produto-openmp_dpcpp.o -o produto-openmp_dpcpp -lpthread

produto-openmp_dpcpp.o: produto-openmp.c
	@dpcpp -c produto-openmp.c -o produto-openmp_dpcpp.o

produto-openmp_clang: produto-openmp_clang.o 
	@clang produto-openmp_clang.o -o produto-openmp_clang -fopenmp=libomp -lm -Ofast -march=native -mtune=native

produto-openmp_clang.o: produto-openmp.c
	@clang -c produto-openmp.c -o produto-openmp_clang.o

produto-pthreads_gcc: produto-pthreads_gcc.o
	@gcc produto-pthreads_gcc.o -o produto-pthreads_gcc -lm -Ofast -march=native -mtune=native

produto-pthreads_gcc.o: produto-pthreads.c
	@gcc -c produto-pthreads.c -o produto-pthreads_gcc.o

produto-pthreads_icx: produto-pthreads_icx.o
	@icx produto-pthreads_icx.o -o produto-pthreads_icx -qpthreads -O3

produto-pthreads_icx.o: produto-pthreads.c
	@icx -w -c produto-pthreads.c -o produto-pthreads_icx.o

produto-pthreads_dpcpp: produto-pthreads_dpcpp.o
	@dpcpp produto-pthreads_dpcpp.o -o produto-pthreads_dpcpp -lpthread

produto-pthreads_dpcpp.o: produto-pthreads.c
	@dpcpp -c produto-pthreads.c -o produto-pthreads_dpcpp.o

produto-pthreads_clang: produto-pthreads_clang.o 
	@clang produto-pthreads_clang.o -o produto-pthreads_clang -lm -Ofast -march=native -mtune=native

produto-pthreads_clang.o: produto-pthreads.c
	@clang -c produto-pthreads.c -o produto-pthreads_clang.o

clean:
	@rm produto_gcc produto_gcc.o produto_icx produto_icx.o produto_dpcpp produto_dpcpp.o produto_clang produto_clang.o

run:
	@echo "Teste com N=10" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 10 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 10 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 10 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 10 >> testes.txt
	@echo "Teste com N=16" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 16 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 16 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 16 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 16 >> testes.txt
	@echo "Teste com N=50" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 50 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 50 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 50 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 50 >> testes.txt
	@echo "Teste com N=64" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 64 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 64 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 64 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 64 >> testes.txt
	@echo "Teste com N=100" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 100 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 100 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 100 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 100 >> testes.txt
	@echo "Teste com N=128" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 128 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 128 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 128 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 128 >> testes.txt
	@echo "Teste com N=500" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 500 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 500 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 500 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 500 >> testes.txt
	@echo "Teste com N=512" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 512 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 512 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 512 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 512 >> testes.txt
	@echo "Teste com N=750" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 750 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 750 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 750 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 750 >> testes.txt
	@echo "Teste com N=1000" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 1000 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 1000 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 1000 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 1000 >> testes.txt
	@echo "Teste com N=1024" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 1024 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 1024 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 1024 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 1024 >> testes.txt
	@echo "Teste com N=1250" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 1250 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 1250 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 1250 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 1250 >> testes.txt
	@echo "Teste com N=1600" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 1600 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 1600 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 1600 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 1600 >> testes.txt
	@echo "Teste com N=2000" >> testes.txt && echo "gcc :" >> testes.txt && ./produto_gcc 2000 >> testes.txt && echo "icx :" >> testes.txt && ./produto_icx 2000 >> testes.txt && echo "dpcpp :" >> testes.txt && ./produto_dpcpp 2000 >> testes.txt && echo "clang :" >> testes.txt && ./produto_clang 2000 >> testes.txt
	@echo "Teste com N=10" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 10 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 10 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 10 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 10 >> testes-openmp.txt
	@echo "Teste com N=16" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 16 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 16 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 16 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 16 >> testes-openmp.txt
	@echo "Teste com N=50" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 50 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 50 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 50 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 50 >> testes-openmp.txt
	@echo "Teste com N=64" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 64 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 64 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 64 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 64 >> testes-openmp.txt
	@echo "Teste com N=100" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 100 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 10 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 100 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 100 >> testes-openmp.txt
	@echo "Teste com N=128" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 128 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 12 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 128 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 128 >> testes-openmp.txt
	@echo "Teste com N=500" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 500 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 50 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 500 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 500 >> testes-openmp.txt
	@echo "Teste com N=512" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 512 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 512 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 512 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 512 >> testes-openmp.txt
	@echo "Teste com N=750" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 750 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 750 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 750 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 750 >> testes-openmp.txt
	@echo "Teste com N=1000" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 1000 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 1000 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 1000 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 1000 >> testes-openmp.txt
	@echo "Teste com N=1024" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 1024 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 1024 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 1024 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 1024 >> testes-openmp.txt
	@echo "Teste com N=1250" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 1250 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 1250 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 1250 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 1250 >> testes-openmp.txt
	@echo "Teste com N=1600" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 1600 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 1600 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 1600 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 1600 >> testes-openmp.txt
	@echo "Teste com N=2000" >> testes-openmp.txt && echo "gcc :" >> testes-openmp.txt && ./produto-openmp_gcc 2000 >> testes-openmp.txt && echo "icx :" >> testes-openmp.txt && ./produto-openmp_icx 2000 >> testes-openmp.txt && echo "dpcpp :" >> testes-openmp.txt && ./produto-openmp_dpcpp 2000 >> testes-openmp.txt && echo "clang :" >> testes-openmp.txt && ./produto-openmp_clang 2000 >> testes-openmp.txt
	@echo "Teste com N=10" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 10 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 10 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 10 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 10 >> testes-pthreads.txt
	@echo "Teste com N=16" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 16 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 16 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 16 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 16 >> testes-pthreads.txt
	@echo "Teste com N=50" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 50 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 50 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 50 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 50 >> testes-pthreads.txt
	@echo "Teste com N=64" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 64 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 64 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 64 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 64 >> testes-pthreads.txt
	@echo "Teste com N=100" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 100 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 10 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 100 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 100 >> testes-pthreads.txt
	@echo "Teste com N=128" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 128 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 12 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 128 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 128 >> testes-pthreads.txt
	@echo "Teste com N=500" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 500 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 50 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 500 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 500 >> testes-pthreads.txt
	@echo "Teste com N=512" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 512 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 512 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 512 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 512 >> testes-pthreads.txt
	@echo "Teste com N=750" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 750 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 750 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 750 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 750 >> testes-pthreads.txt
	@echo "Teste com N=1000" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 1000 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 1000 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 1000 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 1000 >> testes-pthreads.txt
	@echo "Teste com N=1024" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 1024 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 1024 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 1024 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 1024 >> testes-pthreads.txt
	@echo "Teste com N=1250" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 1250 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 1250 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 1250 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 1250 >> testes-pthreads.txt
	@echo "Teste com N=1600" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 1600 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 1600 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 1600 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 1600 >> testes-pthreads.txt
	@echo "Teste com N=2000" >> testes-pthreads.txt && echo "gcc :" >> testes-pthreads.txt && ./produto-pthreads_gcc 2000 >> testes-pthreads.txt && echo "icx :" >> testes-pthreads.txt && ./produto-pthreads_icx 2000 >> testes-pthreads.txt && echo "dpcpp :" >> testes-pthreads.txt && ./produto-pthreads_dpcpp 2000 >> testes-pthreads.txt && echo "clang :" >> testes-pthreads.txt && ./produto-pthreads_clang 2000 >> testes-pthreads.txt