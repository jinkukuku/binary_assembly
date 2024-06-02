#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

int stack[STACK_SIZE]; // 스택
int sp = 0; // 스택 포인터
int dr = 0; // 데이터 레지스터

int memory[256]; // 메모리

void load_num(int num) {
    dr = num;
}

void load_mem(int address) {
    dr = memory[address];
}

void store_mem(int address) {
    memory[address] = dr;
}

void push_num(int num) {
    stack[sp++] = num;
}

void push() {
    stack[sp++] = dr;
}

void pop() {
    dr = stack[--sp];
}

void add() {
    stack[sp-1] += dr;
}

void sub() {
    stack[sp-1] -= dr;
}

void write_mem(int address) {
    memory[address] = stack[sp-1];
}

void print_mem(int address) {
    

    int binary[32], i = 0;
    
    while (memory[address] > 0) {
        binary[i] = memory[address] % 2;
        memory[address] /= 2;
        i++;
    }
    
    printf("result : ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binary[j]);
    }
}

int main() {


    char line[1024];
    FILE *fp = fopen("code1.txt", "r");
    if (fp == NULL) {
        perror("file open error");
        return 1;
    }


    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token;
        int left, right;

        // 문자열을 공백(" ")을 기준으로 분리
        if(line[5]!=0){
            token = strtok(line, " ");
            left = (int)strtol(token, NULL, 2);
            
            token = strtok(NULL, " ");
            right = (int)strtol(token, NULL, 2);            
        }
        else {
            left = (int)strtol(line, &token, 2);
            if (*token == '\n' || *token == '\r' || *token == '\0') { 
                right = -1;
            } else {
                right = (int)strtol(token, NULL, 2);
            }
        }
        
        printf("left: %d, right: %d, sp : %d\n", left, right,sp);

        switch (left) {
                case 0x00:
                    load_num(right);
                    break;
                case 0x01:
                    load_mem(right);
                    break;
                case 0x03:
                    push_num(right);
                    break;
                case 0x02:
                    store_mem(right);
                    break;
                case 0x04:
                    push();
                    break;
                case 0x06:
                    add();
                    break;
                case 0x08:
                    write_mem(right);
                    break;
                case 0x09:
                    print_mem(right);
                    break;
                case 0x05:
                    pop();
                    break;
                case 0x07:
                    sub();
                    break;
                default:
                    fprintf(stderr, "Invalid opcode: %02X\n", left);
                    exit(1);
            }
        


        }


    fclose(fp);

    return 0;
}