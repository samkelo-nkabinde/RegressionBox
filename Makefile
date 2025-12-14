CC = gcc
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -Iraylib/ 
LDFLAGS = -Llib/
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -lm

SRC = statsSandBox.c
OBJ = $(SRC:.c=.o)
OUT = main.exe

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OUT) *.o src\*.o

