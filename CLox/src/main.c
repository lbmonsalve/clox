// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl() {
    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        interpret(line);
    }
}

static char* readFile(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char* path) {
    char* source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[])
{
    initVM();

    //Chunk chunk;
    //initChunk(&chunk);
    //
    //int constant = addConstant(&chunk, 1.2);
    //writeChunk(&chunk, OP_CONSTANT, 123);
    //writeChunk(&chunk, constant, 123);
    //constant = addConstant(&chunk, 3.4);
    //writeChunk(&chunk, OP_CONSTANT, 123);
    //writeChunk(&chunk, constant, 123);
    //writeChunk(&chunk, OP_ADD, 123);
    //constant = addConstant(&chunk, 5.6);
    //writeChunk(&chunk, OP_CONSTANT, 123);
    //writeChunk(&chunk, constant, 123);
    //writeChunk(&chunk, OP_DIVIDE, 123);
    //writeChunk(&chunk, OP_NEGATE, 123);
    //writeChunk(&chunk, OP_RETURN, 123);
    //disassembleChunk(&chunk, "test chunk");
    //interpret(&chunk);
    //freeChunk(&chunk);

    if (argc == 1) {
        repl();
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        fprintf(stderr, "Usage: clox [path]\n");
        exit(64);
    }

    freeVM();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file