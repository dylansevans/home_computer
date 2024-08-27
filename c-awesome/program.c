//To compile: run
//gcc program.c -o "programName"
// ./"program name".out to run

//Include definitions from standard library
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h> //stdint, standard types: int32_t int64_t uint32_t uint64_t uint8_t int8_t

//#include copies the contents of 1 file, and puts it in the current one

/*returnType functionName(param1Type param1, param2Type param2) { functionContent; }*/
int add(int x, int y) {
    int sum = x + y;
    return sum;
}

int main(int argc, char** argv) {
    puts("Hello World!"); //Put string, writes the given string to stdout with a newline character after
    int sum = add(5,4);
    printf("Your sum is: %d\n",sum); //printf, print formatted, print the format string into stdout but anytime the escape character "%" is found, format one of the variable arguments in
    printf("Here are some fun printf things %d %f %s\n",21,10.561f,"here is my string!");
    int8_t x = 1;
    while (x != 0) {
        printf("%d\n",x++);
    }
    return 0;
}
