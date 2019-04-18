#include "include/function.h"
#include <stdio.h>
#include <string.h>

Token tokens[TOKENSUM] = {0};
int tokenNum = 0;
int begin = 0;
int forward = 0;
extern stateNode allstate[STATESUM];
extern int IDState;
extern int numStateNum;
extern const char* doubleOperator[DOUBLE_OPR_NUM];

/*
 *this program not use double buffer.It is just suitable for one line
 *which was fetched from source file.
 *so you should make the buffer size big enough.
 * */
void LexicalAnalyze(){
    char buffer[BUFFSIZE*2];
    char *filename = tgtFILENAME;
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("analyzer cannot open the file!\n");
        return;
    }
    fgets(buffer, BUFFSIZE, fp);
    while(begin < BUFFSIZE && buffer[begin] != '\0'){
        newUnit(buffer);
    }
    for(int i = 0; i < tokenNum; i++){
        printToken(tokens + i);
    }
    fclose(fp);
}
void newUnit(char buffer[]){
        switch(buffer[begin]){
            case ' ':
                begin++;
                break;
            case '>':
                if(buffer[begin+1] == '='){
                    newOperatorToken(doubleOperator[1]);
                    begin = begin + 2;
                }else{
                    newOperatorToken(doubleOperator[0]);
                    begin++;
                }
                break;
            case '<':
                if(buffer[begin+1] == '='){
                    newOperatorToken(doubleOperator[3]);
                    begin = begin+2;
                }else{
                    newOperatorToken(doubleOperator[2]);
                    begin++;
                }
                break;
            case '!':
                if(buffer[begin+1] == '='){
                    newOperatorToken(doubleOperator[5]);
                    begin = begin+2;
                }else{
                    newOperatorToken(doubleOperator[4]);
                    begin++;
                }
                break;
            default:
                getTokenFromTree();
        }
}
void getTokenFromTree(char buffer[]){
    int preState = 0;
    if(buffer[begin] >= 48 && buffer[begin] <= 57){
        preState = numStateNum;
    }
    forward = begin;
    while(1){   //process every character
        if(preState == numStateNum){//first take number in view
            if(buffer[forward] >= 48 && buffer[forward] <= 57){
                forward++;
                continue;
            }else{  //num end
                newToken(NUM, buffer+begin, forward-begin);
                begin = forward;
                return;
            }
        }
        int findflag = 0;
        for(int i = 0; i < allstate[preState].childNum; i++){
            //second take reseverd word in view
           int index = allstate[preState].children[i];
           if(allstate[index].value == buffer[forward]){
               preState = index;
               findflag = 1;
               forward++;
               break;
           }
        }
        if(!findflag){
            if((allstate[preState].type == RES || allstate[preState].type == IDF) && isIdentifier(buffer[forward])){
                //last take identifier in view
                preState = IDState;
                forward++;
            }else{
                newToken(allstate[preState].type, buffer+begin, forward-begin);
                begin = forward;
                return;
            }
        }
    }
}
int isIdentifier(char ch){
    int res = 0;
    if((ch == '_') ||(ch >=48 && ch<= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122))
        res = 1;
    return res;
}

void newToken(int type, const char *ch, int length){
    if(tokenNum > TOKENSUM){
        printf("the sum of token is not enough\n");
    }
    tokens[tokenNum].id = type;
    assignValueOfToken(tokens+tokenNum, ch, length);
    tokenNum++;
    return;
}

void newPunctuationToken(const char *ch){
    newToken(PUN, ch, strlen(ch));
    return;
}

void newOperatorToken(const char *ch){
    newToken(OPR, ch, strlen(ch));
    return;
}

void assignValueOfToken(Token *tk, const char *buf, int chNum){
    int i = 0;
    for(i = 0; i < chNum; i++){
        tk->value[i] = *(buf+i);
    }
    return;
}

void printToken(Token *tk){
    printf("the token is (%d,'%s')\n",tk->id,tk->value);
}
