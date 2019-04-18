#include "include/function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
extern const char* reservedWords[RESERVED_WORD_NUM];
extern const char* delimiter[DELIMITER_NUM];
extern const char* singleOperator[SINGLE_OPR_NUM];
int stateNum = 0;
int numStateNum = -1;
int IDState = -1;
stateNode allstate[STATESUM] = {{.state = 0, .value=' ', .childNum=0, .children={0}, .type= 0}};

stateNode getEnvironment(){
    stateNode zero = allstate[newStateNode(' ')];
    int i = 0;
    for(i = 0; i < RESERVED_WORD_NUM && reservedWords[i]!='\0'; i++){
         const char *temp = reservedWords[i];
         int j = 0;
         int insertnode = zero.state;
         for(j = 0; j < strlen(temp); j++){
            char ch = *(temp+j);
            int findres = findStateAccording(ch, insertnode);
            if(findres >= 0)
                insertnode = findres;
            else{
                stateNode node = allstate[newStateNode(ch)];
                addChildNode(stateNum-1, insertnode);
                insertnode = node.state;
            }
         }
         if(insertnode != zero.state){
             allstate[insertnode].type = RES;
         }
    }
    for(i = 0; i < DELIMITER_NUM && delimiter[i] != '\0'; i++){
         const char *temp = delimiter[i];
         int j = 0;
         int insertnode = zero.state;
         for(j = 0; j < strlen(temp); j++){
            char ch = *(temp+j);
            int findres = findStateAccording(ch, insertnode);
            if(findres >= 0)
                insertnode = findres;
            else{
                stateNode node = allstate[newStateNode(ch)];
                addChildNode(stateNum-1, insertnode);
                insertnode = node.state;
                allstate[stateNum-1].type = PUN;
            }
         }
    }
    for(i = 0; i < SINGLE_OPR_NUM && singleOperator[i] != '\0'; i++){
         const char *temp = singleOperator[i];
         int j = 0;
         int insertnode = zero.state;
         for(j = 0; j < strlen(temp); j++){
            char ch = *(temp+j);
            int findres = findStateAccording(ch, insertnode);
            if(findres >= 0)
                insertnode = findres;
            else{
                stateNode node = allstate[newStateNode(ch)];
                addChildNode(stateNum-1, insertnode);
                insertnode = node.state;
                allstate[stateNum-1].type = OPR;
            }
         }
    }
    //add num state
    stateNode num = allstate[newStateNode(' ')];
    numStateNum = stateNum-1;
    allstate[numStateNum].type = NUM;
    //add ID state
    stateNode id = allstate[newStateNode(' ')];
    IDState = stateNum-1;
    allstate[IDState].type = IDF;

    return zero;
}



void addChildNode(int nodeNum, int parentNum){
    if(parentNum < 0 || parentNum >= STATESUM){
        printf("add failed\n");
        exit(-1);
    }
    allstate[parentNum].children[allstate[parentNum].childNum] = nodeNum;
    allstate[parentNum].childNum++;
    return;
}

int findStateAccording(char va, int from){
    int *children = allstate[from].children;
    if(allstate[from].childNum <= 0)
        return -1;
    for(int i = 0; i < allstate[from].childNum; i++){
        int index = *(children+i);
        if(allstate[index].value == va)
            return index;
    }
    return -1;
}


int newStateNode(char va){
    if(stateNum >= STATESUM){
        printf("new state failed!\n");
        exit(-1);
    }
    allstate[stateNum].state = stateNum;
    allstate[stateNum].value=va;
    allstate[stateNum].childNum = 0;
    allstate[stateNum].type = IDF;
//    allstate[stateNum].children = {0};
    stateNum++;
    return stateNum-1;
}

void printStateTree(int root){
    printf("%c\n", allstate[root].value);
    for(int i = 0; i < allstate[root].childNum; i++){
        int index = allstate[root].children[i];
        if(index == IDState || index == numStateNum)
            break;
        printf("%c", allstate[index].value);
        printStateTree(index);
        printf("\n\t");
    }
    return;
}

