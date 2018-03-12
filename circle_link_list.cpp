#include <iostream>
using namespace std;


typedef struct Node
{
	int data;
	Node* next;
}CNode, *LinkList;

void init(LinkList& tail)
{
	if(tail != NULL)
	{
		cout << "tail is not NULL";
		return;
	}
	
	tail = new CNode();
	tail->data = -1;
	tail->next = tail;

	return;
}

void output(LinkList tail)
{
	if(tail->next == tail)
	{
		cout << "empty" << endl;
		return;
	}
	
	CNode* head = tail->next;
	CNode* p = head->next;
	while(p != head)
	{
		cout << p->data << endl;
		p = p->next;
	}

	return;
}

void createList(LinkList& tail, int n)
{
	if(n < 1)
	{
		return;
	}

	CNode* p = NULL;
	for(int i = 0; i  < n ; ++i)
	{
		p = new CNode();
		
		cout << "input elem:";
		cin >> p->data;

		p->next = tail->next;
		tail->next = p;
		tail = p;
	}
	
	return;
}

void merge(LinkList& a, LinkList b)
{
	if(b->next == b)
	{
		return;
	}
	
	CNode* b_head = b->next;
	CNode* b_first = b->next->next;

	b->next = a->next;
	a->next = b_first;
	a = b;

	delete b_head;

	return;
}
int main(int argc, char** argv)
{

	LinkList a = NULL, b = NULL;

	init(a);
	init(b);

	int len = 0;
	cout << "input list a len:";
	cin >> len;
	createList(a, len);

	output(a);

	cout << "input list b len:";
	cin >> len;
	createList(b, len);

	cout << "a list:" << endl;
	output(a);
	cout << "b list:" << endl; 
	output(b);


	merge(a, b);
	cout << "after merge:" << endl;
	output(a);

	return 0;
}