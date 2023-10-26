#ifndef BIGINTEGER_H
#define BIGINTEGER_H

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

typedef struct BigInteger 
{
    struct Node* head;
    int sign;
} BigInteger;

BigInteger initialize(char*);
BigInteger add(BigInteger,BigInteger);
BigInteger sub(BigInteger,BigInteger);
BigInteger mul(BigInteger,BigInteger);
BigInteger div1(BigInteger,BigInteger);
BigInteger mod(BigInteger,BigInteger);
void display(BigInteger);

#endif 
