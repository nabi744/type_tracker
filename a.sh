#!/bin/bash

cd "/Users/seunggeon/Documents/vscode/type_tracker/" && gcc -I./include -o server server.c src/*.c && ./server
