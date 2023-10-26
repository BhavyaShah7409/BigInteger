#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node 
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *head;
};


void reverse_str(char *str)
{
    int l = strlen(str);
    for(int i=0; i< l/2; i++)
    {
        char t = str[i];
        str[i] = str[l-i-1];
        str[l-i-1] = t;
    }
}

struct node* create_node(int data)
{
    struct node* new = (struct node*)malloc(sizeof(struct node));
    if (new == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new->data = data;
    new->next = NULL;
    return new;
}

struct BigInteger initialise(char* str) 
{
    struct BigInteger res;
    res.head = NULL;
    struct node* tail = NULL;
    int l = strlen(str);
    reverse_str(str);
    for (int i = 0; i < l; i++) {
        struct node* newNode = create_node(str[i]-'0');
        if (res.head == NULL) 
        {
            res.head = newNode;
            tail = newNode;
        } 
        else 
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return res;
}

void display2(struct node *head)
{
    if(head==NULL)
    return ;
    display2(head->next);
    printf("%d",head->data);
}
void display(struct BigInteger a)
{
    display2(a.head);
}

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    res.head = NULL;
    struct node *n1 = a.head;
    struct node *n2 = b.head;
    struct node* current = NULL;
    int carry = 0;
    while (n1 || n2 || carry) 
    {
        int sum = carry;
        if (n1) {
            sum += n1->data;
            n1 = n1->next;
        }
        if (n2) {
            sum += n2->data;
            n2 = n2->next;
        }
        carry = sum / 10;
        sum %= 10;
        struct node* new = create_node(sum);
        if (res.head == NULL) {
            res.head = new;
            current = new;
        }
        else
        {
            current->next = new;
            current = new;
        }
    }
    return res;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    res.head = NULL;
    struct node *n1 = a.head;
    struct node *n2 = b.head;
    struct node* current = NULL;
    int borrow = 0;
    while (n1)
    {
        int differ = n1->data - borrow;
        if (n2)
        {
            differ -= n2->data;
            n2 = n2->next;
        }
        if (differ < 0)
        {
            differ += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        struct node* new = create_node(differ);
        if (res.head == NULL) {
            res.head = new;
            current = new;
        }
        else
        {
            current->next = new;
            current = new;
        }
        n1 = n1->next;
    }
    return res;
}
void insert_before(struct node *head, int val)
{
    struct node* new = (struct node *)malloc(sizeof(struct node));
    new->data = val;
    new->next = NULL;
    new->next = head;
    head = new;
}
struct node * addlist(struct node* n1, struct node *n2)
{
    struct node *result = NULL;
    struct node* current = NULL;
    int carry = 0;
    while (n1 || n2 || carry) 
    {
        int sum = carry;
        if (n1) {
            sum += n1->data;
            n1 = n1->next;
        }
        if (n2) {
            sum += n2->data;
            n2 = n2->next;
        }
        carry = sum / 10;
        sum %= 10;
        struct node* new = create_node(sum);
        if (result == NULL) {
            result = new;
            current = new;
        }
        else
        {
            current->next = new;
            current = new;
        }
    }
    return result;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    struct node *n1 = a.head;
    struct node *n2 = b.head;
    struct node *prev = create_node(0);
    int i=-1;
    while(n2)
    {
        i++;
        int carry =0;
        struct node *n =n1;
        struct node *result = NULL;
        struct node *tail = NULL;
        while(n || carry>0)
        {
            int sum;
            if(n)
            sum = n->data * n2->data +carry;
            if(!n && carry)
            sum = carry;
            carry = sum/10;
            sum =sum%10;
            struct node *new = create_node(sum);
            if(result == NULL)
            {
                result = new;
                tail = new;
            }
            tail->next = new;
            tail = new; 
            n=n->next;
        }
        if(i)
        {
            int j=1;
            while(j<=i)
            {
                insert_before(result, 0);
                j++;
            }
        }
        prev = addlist(prev, result);
        n2 = n2 ->next;
    }
    res.head = prev;
    return res;
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger res;
    struct node *dividend = a.head;
    struct node*divisor = b.head;
    struct node* quotient = NULL;
    struct node* currentQuotientNode = NULL;
    struct node* remainder = NULL;
    struct node* currentRemainderNode = NULL;

    if (divisor->data == 0) {
        printf("Division by zero is not allowed.\n");
        exit(1);
    }

    while (dividend != NULL) {
        int currentDividend = dividend->data;
        if (remainder != NULL) {
            struct node* temp = create_node(currentDividend);
            temp->next = remainder;
            remainder = temp;
        } else {
            remainder = create_node(currentDividend);
        }

        int currentQuotient = 0;

        while (currentDividend >= divisor->data) {
            currentDividend -= divisor->data;
            currentQuotient++;
        }

        if (currentQuotient > 0) {
            if (quotient == NULL) {
                quotient = create_node(currentQuotient);
                currentQuotientNode = quotient;
            } else {
                currentQuotientNode->next = create_node(currentQuotient);
                currentQuotientNode = currentQuotientNode->next;
            }
        }

        dividend = dividend->next;
    }
    res.head = quotient;
    return res;
}