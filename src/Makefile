bcc:	parser.tab.c lex.yy.c ASTDefinitions.cpp ASTDefinitions.h Intrepretor.cpp  Codegen.cpp
	g++ -g parser.tab.c lex.yy.c  -lfl -lLLVM-3.6 -o bcc
parser.tab.c: parser.y 
	bison -d parser.y 
parser.tab.h: parser.y
	bison -d parser.y 
lex.yy.c: scanner.l parser.tab.h
	flex scanner.l

.PHONY: clean 
clean:
	-@rm -rf parser.tab.c parser.tab.h lex.yy.c bcc 2>/dev/null || true
