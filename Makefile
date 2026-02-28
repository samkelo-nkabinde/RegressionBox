RAYLIB_PATH = ../raylib

CC = emcc

CFLAGS = -Os -Wall -Iraylib -Iinclude -I$(RAYLIB_PATH)/src -L. -L$(RAYLIB_PATH)/src -DPLATFORM_WEB

LIBS = $(RAYLIB_PATH)/src/libraylib.web.a

EMFLAGS = -s USE_GLFW=3 -s ASYNCIFY --shell-file $(RAYLIB_PATH)/src/minshell.html

SRC = main.c $(wildcard src/*.c)
OUT = index.html

all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LIBS) $(EMFLAGS)

clean:
	rm -f index.html index.js index.wasm src/*.o *.o
