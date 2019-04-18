#define NUM 3
#define OPR 4
#define PUN 5
#define RES 1
#define IDF 2

#define BUFFSIZE 1024 
#define RESERVED_WORD_NUM 100 
#define LETTERNUM 26
#define STATESUM 300
#define TOKENSUM 1024
#define TOKENLEN 100
#define DELIMITER_NUM 20 
#define SINGLE_OPR_NUM 20
#define DOUBLE_OPR_NUM 20

#define srcFILENAME "test.c"
#define tgtFILENAME "out.c"

typedef struct token{
    int id;
    char value[TOKENLEN];
}Token;

typedef struct statenode {
    int state;
    char value;
    int childNum;
    int children[LETTERNUM];
    int type;
}stateNode;
