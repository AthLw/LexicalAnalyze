#include <stdio.h>
#include "include/function.h"
extern stateNode allstate[STATESUM];
const char *reservedWords[RESERVED_WORD_NUM] =
{
    "break",
    "case",
    "continue",
    "char",
    "const",
    "do",
    "double",
    "else",
    "for",
    "float",
    "if",
    "int",
    "return",
    "switch",
    "struct",
    "void",
    "while"
};
const char *delimiter[DELIMITER_NUM] = {
    ",",
    ";",
    "{",
    "}",
    "(",
    ")"
};
const char *singleOperator[SINGLE_OPR_NUM] = {
    "+",
    "-",
    "*",
    "/",
    "="
};
const char *doubleOperator[DOUBLE_OPR_NUM] = {
    ">",
    ">=",
    "<",
    "<=",
    "!",
    "!="
};
int main(){
    int linenum = 0;//TODO
    preProcess();
    stateNode res = getEnvironment();
    //printStateTree(res.state);
    LexicalAnalyze();
}

void preProcess(){
    char buffer[BUFFSIZE*2];
    char *filename = srcFILENAME;
    char *targetfile = tgtFILENAME;
    FILE *fp = fopen(filename, "r");
    FILE *wfp = fopen(targetfile, "w");
    if(fp == NULL){
        printf("cannot open the source file!\n");
        return;
    }
    if(wfp == NULL){
        printf("cannot open the target file!\n");
        return;
    }
    char annotationflag = ' ';
    int skipflag = 0;
    while(!feof(fp)){
        fgets(buffer, BUFFSIZE, fp);
        int num = 0;
        for(num = 0; num < BUFFSIZE && buffer[num] != '\0'; num++){
            if(annotationflag == ' '){  //not annotation, put into file possibly
                if(buffer[num] == '\n'){    //omit
                    break;
                }
                if(buffer[num] == ' '){
                    if(skipflag){
                        continue;
                    }else{
                        skipflag = 1;
                        fputc(buffer[num], wfp);
                        continue;
                    }
                }
                if(buffer[num] == '/'){
                    if((num+1)<BUFFSIZE){
                        if(buffer[num+1] == '*'){
                            //debug
                            
                            annotationflag = '*';
                            num++;
                            continue;
                        }else if(buffer[num+1] == '/'){
                            annotationflag = '\n';
                            num++;
                            continue;
                        }
                    }
                }
                skipflag = 1;
                if((buffer[num] > 64 && buffer[num] < 91) || (buffer[num] > 96 && buffer[num] < 123)){
                    skipflag = 0;
                }
                fputc(buffer[num], wfp);
            } else if(annotationflag == '\n'){
                    if(buffer[num] == '\n')
                        annotationflag = ' ';
            }else {        //new line has been processed, here is */
                if((num+1) < BUFFSIZE && buffer[num+1] == '/'){
                        annotationflag = ' ';
                        num++;
                }
                continue;   //omit
            }
        }
        buffer[0] = '\0';
    }
    fclose(fp);
    fclose(wfp);
}
