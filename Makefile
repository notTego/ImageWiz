# Copyright 2021 Vladimir Marin

# compiler setup
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

# define targets
#TARGETS=image_editor

build: image_editor

image_editor: image_editor.c
	$(CC) $(CFLAGS) image_editor.c load_it.c miscellaneous.c select_all.c select_it.c rotate_it.c save_it.c hash.c filters.c -lm -o image_editor

pack:
	zip -FSr 312CA_VladimirMarin_Tema3.zip README Makefile *.c *.h

clean:
	rm -f image_editor

.PHONY: pack clean

