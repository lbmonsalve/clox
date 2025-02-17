// main.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"

static void repl() {
    printf("clox 0.0.241102 (d0c5c90) type .help for more information\n");

    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        if (strcmp(".q\n", line) == 0) {
            return;
        } else if (strcmp(".help\n", line) == 0) {
            printf("Lox language implementation in C (https://github.com/lbmonsalve/CLox)\n\n");
            printf("Commands:\n\n");
            printf("  .help         this info\n");
            printf("  .quit         quit (or .q)\n\n");
            printf("LICENCE and COPYRIGHT on github site.\n\n");
            continue;
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

    if (argc == 1) {
        repl();
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
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

/*

fun fib(n) { if (n < 2) return n; return fib(n - 2) + fib(n - 1); } var start = clock(); print fib(35); print clock() - start;

var x = "global"; fun outer() { var x = "outer"; fun inner() { print x; } inner(); } outer();

fun outer() { var a = 1; var b = 2; fun middle() { var c = 3; var d = 4; fun inner() { print a + c + b + d; } } }

fun outer() {var x = "before";fun inner() {x = "assigned";}inner();print x;}outer();

fun outer() {var x = "outside";fun inner() {print x;}inner();}outer();

var globalSet;var globalGet;fun main() {var a = "initial";fun set() { a = "updated"; }fun get() {print a; }globalSet = set;globalGet = get;}main();globalSet();globalGet();

class Toast {}var toast = Toast();print toast.jam = "grape"; // Prints "grape".

class Pair {}var pair = Pair();pair.first = 1;pair.second = 2;print pair.first + pair.second; // 3.

class Brunch {bacon() {}eggs() {}}

class Scone {topping(first, second) {print "scone with " + first + " and " + second;}}
var scone = Scone();
scone.topping("berries", "cream");

// err
class Nested {method() {fun function() {print this;}function();}}
Nested().method();
// err

print this; // At top level
fun notMethod() {print this;}
notMethod();

class CoffeeMaker {init(coffee) {this.coffee = coffee;}brew() {print "Enjoy your cup of " + this.coffee;this.coffee = nil;}}
var maker = CoffeeMaker("coffee and chicory");
maker.brew();


class Oops {init() {fun f() {print "not a method";}this.field = f;}}
var oops = Oops();
oops.field();

class Doughnut {cook() {print "Dunk in the fryer.";this.finish("sprinkles");}finish(ingredient) {print "Finish with " + ingredient;}}

class Cruller < Doughnut {finish(ingredient) {super.finish("icing");}}



project/properties/Debugging/Command Arguments: ..\test\benchmark\binary_trees.lox


fun echo(n) {print n;return n;}
print echo(echo(1) + echo(2)) + echo(echo(4) + echo(5));


*/