.DEFAULT_GOAL := run

hello:
	@echo "Assignment 6 by Abhiroop Mukherjee (510519109)"

generate: hello
	@echo "Generating Required Files"
	lex test.l
	yacc test.y -d
	gcc y.tab.c lex.yy.c symTable.c syntaxTree.c -ll
	@echo "Now do 'make run' to run"

info:
	@echo "Open y.output"
	yacc test.y -v

run: generate
	@echo "Running program"
	./a.out < file.c

clean: hello
	@echo "Cleaning up..."
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h
	rm ./a.out
	rm y.output