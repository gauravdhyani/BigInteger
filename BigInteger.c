#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}s,Node;

typedef struct BigInteger 
{
    struct Node* head; 
    int sign;  
}BigInteger;

BigInteger initialize(char*);
BigInteger add(BigInteger,BigInteger);
BigInteger sub(BigInteger,BigInteger); 
BigInteger mul(BigInteger, BigInteger);
BigInteger div1(BigInteger,BigInteger);
BigInteger mod(BigInteger,BigInteger);
void display(BigInteger);

int count(const s* num1) {
    int count = 0;
    const s* current = num1;
    while (current != NULL && current->data == 0) {
        current = current->next;
    }
    while (current != NULL) {
        count++;
        current = current->next;
    }
    if (count == 0) {
        count = 1; 
    }
    return count;
}

void appendNode(BigInteger* bigInt, int value) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (bigInt->head == NULL) 
    {
        bigInt->head = newNode;
    } else {
        Node* current = bigInt->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void prependNode(BigInteger* bigInt, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = bigInt->head;
    bigInt->head = newNode;
}
BigInteger initialize(char* str) {
    BigInteger bigInt;
    bigInt.head = NULL;
    bigInt.sign = 1;

    if (str[0] == '-') {
        bigInt.sign = -1;
        str++; 
    }

    
    for (int i = 0; str[i] != '\0'; i++) 
    {
        if (str[i] >= '0' && str[i] <= '9') 
        {
            int digit = str[i] - '0';
            prependNode(&bigInt, digit);
        } 
    }

    return bigInt;
}
void reverseBigInteger(BigInteger* num) {
    Node* prev = NULL;
    Node* current = num->head;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    num->head = prev;
}
BigInteger copyReverseBigInteger( BigInteger num) {
    BigInteger reversedCopy;
    reversedCopy.head = NULL;
    reversedCopy.sign = num.sign;

    Node* current = num.head;
    while (current != NULL) {
        appendNode(&reversedCopy, current->data);
        current = current->next;
    }

    reverseBigInteger(&reversedCopy);
    return reversedCopy;
}
void printBigIntegerRecursive(Node* current) 
{
    if (current == NULL) 
    {
        return;
    }
    printBigIntegerRecursive(current->next);
    printf("%d", current->data);
}
void display(BigInteger bigInt)
{
    if (bigInt.sign == -1) {
        printf("-");
    }
    printBigIntegerRecursive(bigInt.head);
    printf("\n");
}
int compareBigIntegers(BigInteger num1, BigInteger num2) {
    int count1 = count(num1.head);
    int count2 = count(num2.head);

    if (count1 > count2) { 
        return 1;
    } else if (count2 > count1 ) {
        return -1;
    } else if (count2 == count1) {
        Node* current1 = num1.head;
        Node* current2 = num2.head;
        while (current1 && current2) {
            if (current1->data > current2->data) {
                return 1;
            } else if (current2->data > current1->data) {
                return -1;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
    }
    return 0;
}
BigInteger add(BigInteger num1, BigInteger num2) {
    BigInteger result;
    result.head = NULL;
    int sum, carry = 0;
    if (num1.sign == num2.sign) {
        result.sign = num1.sign;
        Node* current1 = num1.head;
        Node* current2 = num2.head;

        while (current1 || current2) {
            int x = (current1) ? current1->data : 0;
            int y = (current2) ? current2->data : 0;

            sum = x + y + carry;
            carry = sum / 10;
            appendNode(&result, sum % 10);

            if (current1) {
                current1 = current1->next;
            }

            if (current2) {
                current2 = current2->next;
            }
        }

    if (carry > 0) 
    {
        appendNode(&result, carry);
    }
    } 
    else 
    {
        
        if (num1.sign == -1) 
        {
            num1.sign=1;
            num2.sign=1;
            result = sub(num2, num1);

        } 
        else 
        {
            num1.sign=1;
            num2.sign=1;
            result = sub(num1, num2);
             
        }
    }
    if (result.head == NULL) 
    {
        return initialize("0");
    }
    return result;
}
BigInteger sub(BigInteger num1, BigInteger num2) 
{
    BigInteger result;
    result.head = NULL;

    if (num1.sign == num2.sign) {
        if (compareBigIntegers(copyReverseBigInteger(num1),copyReverseBigInteger(num2)) >= 0) {
            int borrow = 0;
            Node* current1 = num1.head;
            Node* current2 = num2.head;

            while (current1 || current2) {
                int x = (current1) ? current1->data : 0;
                int y = (current2) ? current2->data : 0;

                int diff;
                if (x < y + borrow) {
                    x += 10;
                    diff = x - y - borrow;
                    borrow = 1;
                } else {
                    diff = x - y - borrow;
                    borrow = 0;
                }

                prependNode(&result, diff);

                if (current1) {
                    current1 = current1->next;
                }
                if (current2) {
                    current2 = current2->next;
                }
            }

            while (result.head && result.head->data == 0) {
                Node* temp = result.head;
                result.head = result.head->next;
                free(temp);
            }

            reverseBigInteger(&result);
            result.sign = num1.sign; 
        } else {
            result = sub(num2, num1);
            result.sign = -result.sign;
        }
    } else {
        BigInteger absNum1 = num1;
        absNum1.sign = 1; 
        BigInteger absNum2 = num2;
        absNum2.sign = 1;
        result = add(absNum1, absNum2);
        if (num1.sign == -1) {
            result.sign = -1; 
        } else {
            result.sign = 1;
        }
    }
    if(result.head==NULL)
     {return initialize("0");}
    return result;
}
BigInteger mul(BigInteger num1, BigInteger num2) {
    BigInteger result;
    result.head = NULL;
    result.sign = 1;
    BigInteger num1copy = num1;
    if (num1.head == NULL || num2.head == NULL) {
        prependNode(&result, 0);
        return result;
    }

    int multiplier = 0;
    while (num1copy.head != NULL) {
        int carry = 0;
        BigInteger tempResult;
        tempResult.head = NULL;
        tempResult.sign = 1;

        BigInteger num2Copy = num2;

        int i;
        for (i = 0; i < multiplier; i++) {
            appendNode(&tempResult, 0);
        }

        while (num2Copy.head != NULL) {
            int product = (num1copy.head->data * num2Copy.head->data) + carry;
            carry = product / 10;
            appendNode(&tempResult, product % 10);
            num2Copy.head = num2Copy.head->next;
        }

        if (carry > 0) {
            appendNode(&tempResult, carry);
        }
        result = add(result, tempResult);
        num1copy.head = num1copy.head->next;
        multiplier++;
    }
    if (num1.sign == num2.sign) {
        result.sign = 1;
    } else {
        result.sign = -1;
    }
    return result;
}
BigInteger div1(BigInteger dividend, BigInteger divisor)
{
    if (divisor.head == NULL || compareBigIntegers(divisor, initialize("0")) == 0) 
    {
        printf("Division by zero is not allowed!\n");
        return initialize("0");
    }
    BigInteger quotient;
    quotient.head = NULL;
    quotient.sign = 1;
    BigInteger currentDividend = dividend;
    BigInteger currentDivisor = divisor;
    BigInteger temp = initialize("1");
    BigInteger tempResult=currentDivisor;
    while (compareBigIntegers(copyReverseBigInteger(currentDividend),copyReverseBigInteger(tempResult)) >= 0)
    {
        quotient = add(quotient,temp);
        tempResult = mul(divisor,quotient);
        tempResult = add(tempResult, currentDivisor);
        
    }
    if(quotient.head==NULL)
     {return initialize("0");}
    if (dividend.sign == divisor.sign) {
        quotient.sign = 1;
    }
    else {
        quotient.sign = -1;
    }
    return quotient;
}
BigInteger mod(BigInteger dividend, BigInteger divisor)
{
    BigInteger quotient=div1(dividend,divisor);
    BigInteger currentdivisor=mul(divisor,quotient);
    BigInteger result=sub(dividend,currentdivisor);
    result.sign=1;
    return result;
}
