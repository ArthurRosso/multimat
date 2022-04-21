all: produto_clang

produto_clang: produto_clang.o 
	@clang produto_clang.o -o produto_clang -lm -Ofast -march=native -mtune=native

produto_clang.o: produto.c
	@clang -c produto.c -o produto_clang.o

clean:
	@rm produto_clang produto_clang.o

run:
	@echo "Teste com N=10" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 10 >> testes-clang.txt
	@echo "Teste com N=16" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 16 >> testes-clang.txt
	@echo "Teste com N=50" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 50 >> testes-clang.txt
	@echo "Teste com N=64" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 64 >> testes-clang.txt
	@echo "Teste com N=100" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 100 >> testes-clang.txt
	@echo "Teste com N=128" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 128 >> testes-clang.txt
	@echo "Teste com N=500" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 500 >> testes-clang.txt
	@echo "Teste com N=512" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 512 >> testes-clang.txt
	@echo "Teste com N=750" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 750 >> testes-clang.txt
	@echo "Teste com N=1000" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 1000 >> testes-clang.txt
	@echo "Teste com N=1024" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 1024 >> testes-clang.txt
	@echo "Teste com N=1250" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 1250 >> testes-clang.txt
	@echo "Teste com N=1600" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 1600 >> testes-clang.txt
	@echo "Teste com N=2000" >> testes-clang.txt && echo "clang :" >> testes-clang.txt && ./produto_clang 2000 >> testes-clang.txt