#include "datastructure.h"

void LexicalAnalyze();
void newUnit();
void newToken(int type, const char *ch, int length);
void newPunctuationToken(const char *ch);
void newOperatorToken(const char *ch);
void getTokenFromTree();
void preProcess();
stateNode getEnvironment();
void addChildNode(int nodeNum, int parentNum);
int newStateNode(char va);
int findStateAccording(char va, int from);
void printStateTree(int root);
void printToken(Token *tk);
void assignValueOfToken(Token *tk, const char *res, int charnum);
int isIdentifier(char ch);
