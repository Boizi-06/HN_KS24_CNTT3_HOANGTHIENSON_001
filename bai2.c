#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100


typedef struct {
    char action;
    char value;
} Operation;


typedef struct {
    Operation data[MAX];
    int top;
} Stack;


void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Operation op) {
    if (!isFull(s)) {
        s->data[++s->top] = op;
    }
}

Operation pop(Stack *s) {
    Operation op = {' ', ' '};
    if (!isEmpty(s)) {
        op = s->data[s->top--];
    }
    return op;
}


void menu() {

    printf("1. INSERT x\n");
    printf("2. UNDO\n");
    printf("3. REDO\n");
    printf("4. HIEN THI\n");
    printf("5. OUT\n");
    printf("CHON: ");
}

int main() {
    char text[MAX] = "";
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    int choice;
    char x;

    do {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("nhap ki tu: ");
                scanf(" %c", &x);
                if (strlen(text) < MAX - 1) {
                    int len = strlen(text);
                    text[len] = x;
                    text[len + 1] = '\0';

                    Operation op = {'I', x};
                    push(&undoStack, op);
                    initStack(&redoStack);
                }
                break;

            case 2:


            case 3:

                break;

            case 4:

                break;

            case 5:
                printf("out.\n");
                break;

            default:
                printf("lua chon ko hop le.\n");
                break;
        }

    } while (choice != 5);

    return 0;
}
