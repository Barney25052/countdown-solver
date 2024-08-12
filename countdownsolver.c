#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char operationChars[4] = {'+', '-', '*', '/'};
int minDifference = 100;

enum Operation {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
};


struct NumNode {
    int* nums;
    int numsLength;
    int output;
    int numOne;
    int numTwo;
    enum Operation operation;
    char steps[128];
    bool isMinNode;
};

struct NumNode* minNode = NULL;

void createNodes(struct NumNode* node, int target);

void numNodeCreate(int target, int* nums, int numsLength, int numOneIndex, int numTwoIndex, enum Operation operation, char* steps) {
    if(numsLength == 1) {
        return;
    }
    struct NumNode* node = malloc(sizeof(struct NumNode));
    node->steps[0] = 0;
    node->isMinNode = false;
    node->output = 0;

    if(numOneIndex == -1) { //Start node has numOneIndex of -1 to signify its the start node
        for(int i = 0; i < strlen(steps); i++) {
            node->steps[i] = steps[i];
        }
        node->steps[strlen(steps)] = 0;
        node->nums = nums;
        node->numsLength = numsLength;
        createNodes(node, target);
        return;
    }

    node->numOne = nums[numOneIndex];
    node->numTwo = nums[numTwoIndex];
    node->operation = operation;
    node->nums = calloc(sizeof(int), numsLength -1);
    switch(operation) {
        case ADD:
            node->output = node->numOne + node->numTwo;
            break;
        case SUBTRACT:
            node->output = node->numOne - node->numTwo;
            if(node->output < 0) {
                node->output = -node->output;
            }
            break;
        case MULTIPLY:
            node->output = node->numOne * node->numTwo;
            break;
        case DIVIDE:
            if(node->numOne % node->numTwo != 0) {
                if(node->numTwo % node->numOne != 0) {
                    free(node->nums);
                    free(node);
                    return;
                }
                int temp = node->numOne;
                node->numOne = node->numTwo;
                node->numTwo = temp;
            }
            node->output = node->numOne / node->numTwo;
            break;
    }

    if(node->output == 0) {
        free(node->nums);
        free(node);
        return; //If the current output is 0, its not helpful so we can exit this path
    }

    int numsCount = 0;
    for(int i = 0; i < numsLength; i++) {
        if(i != numOneIndex && i != numTwoIndex) {
            node->nums[numsCount] = nums[i];
            numsCount++;
        }
    }
    node->nums[numsCount] = node->output;
    node->numsLength = numsCount + 1;

    sprintf(node->steps, "%s%d %c %d = %d\n", steps,node->numOne, operationChars[operation], node->numTwo, node->output);

    if(node->numsLength == 1) {
        if(node->output == target) {
            printf("%s", steps);
            exit(0);
        }
    }

    int distanceFromTarget = abs(target-node->output);
    if(distanceFromTarget < minDifference) {
        minDifference = distanceFromTarget;
        node->isMinNode = true;
        minNode = node;
    }

    createNodes(node, target);
}

void createNodes(struct NumNode* node, int target) {
    for(int i = 0; i < node->numsLength; i++) {
        for(int j = 0; j < node->numsLength; j++) {
            if(i == j) {
                continue;
            }
            for(int o = 0; o < 4; o++) {        //Multiply and Add are communative
                if(j > i) {
                    continue;
                }
                numNodeCreate(target, node->nums, node->numsLength, i, j, (enum Operation)o, node->steps);
            }
        }
    }

    free(node->nums);
    if(!node->isMinNode) {
        free(node);
    } 
}

bool isInteger(char* num) {
    int number = atoi(num);
    if(number == 0 && strcmp(num, "0") != 0) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        printf("Invalid number of arguments: target [nums]\n");
        return -1;
    } 

    int target = atoi(argv[1]);
    if(!isInteger(argv[1]) || target<0) {
        printf("Target '%s' is not a positive integer\n", argv[1]);
        return -1;
    }

    int numsLength = argc-2;
    int* nums = calloc(sizeof(int), numsLength);
    
    for(int i = 0; i < numsLength; i++) {
        nums[i] = atoi(argv[i+2]);
        if(!isInteger(argv[i+2]) || nums[i]<0) {
            printf("Number '%s' is not a positive integer\n", argv[i+2]);
            free(nums);
            return -1;
        }
    }

    char startString[] = "Target Found\n";
    numNodeCreate(target, nums, numsLength, -1, -1, ADD, startString);
    printf("Closest is %d off:\n", minDifference);
    struct NumNode* currentNode = minNode;
    printf("%s", minNode->steps);
}