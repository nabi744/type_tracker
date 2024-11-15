#!/bin/bash

cd "/Users/seunggeon/Documents/vscode/typetracker/" && gcc -I./include -o server server.c src/*.c && ./server
