EXE = graph.exe
SRC = convertor.c evaluator.c graph.c parser.c ps_creator.c stack.c validator.c
OB = $(SRC:.c=.o)
OPT = -std=c99 -Wall -Wextra -pedantic -lm

$(EXE): $(OB)
	gcc $(OB) -o $(EXE) $(OPT)

%.o: %.c
	gcc -c $< -o $@ $(OPT)

clean:
	rm -f $(OB) $(EXE)

.PHONY: clean
