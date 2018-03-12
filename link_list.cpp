#include <iostream>
using namespace std;


typedef struct LNode
{
	int data;
	LNode* next;
}SLNode, *LinkList;

void init(LinkList& head)
{	
	head = new LNode();
	head->data = -1;
	head->next = NULL;

	return;
}

void destroy(LinkList& head)
{
	if(head == NULL)
	{
		return;
	}
	LNode* p = head->next;
	LNode* curr_p = NULL;
	while(p != NULL)
	{
		curr_p = p;
		p = curr_p->next;

		cout << "delete elem:" << curr_p->data << endl;
		delete curr_p;
		curr_p = NULL;
	}

	cout << "delete head" << endl;
	delete head;
	head = NULL;

	return;
}

void print(LinkList head)
{
	if(head == NULL)
	{
		return;
	}

	SLNode* p = head->next;
	while(p != NULL)
	{
		cout << p->data << endl;
		p = p->next;
	}

	return;
}

void append(LinkList head)
{
	cout << "input elem:";
	SLNode* p = new SLNode();
	cin >> p->data;

	p->next = head->next;
	head->next = p;

	return;
}

bool insert(LinkList head, int i, int elem)
{
	if(head == NULL) //链表未初始化
	{
		return false;
	}

	if(i < 1) //插入位置不满足条件
	{
		return false;
	}
	
	int j = 0;
	SLNode* p = head;
	while(p != NULL && j < i - 1)
	{
		p = p->next;
		++j;
	}

	if(p == NULL || j != (i - 1))
	{
		return false;
	}

	cout << "insert pos" << j << endl;

	SLNode* tmp = new SLNode();
	tmp->data = elem;

	tmp->next = p->next;
	p->next = tmp;

	return true;
}

void createList(LinkList& head, int n)
{
	if(n < 1)
	{
		return;
	}
	init(head);
	SLNode* p = NULL;
	for(int i = 0; i < n; ++i)
	{
		p = new SLNode();
		cout << "input elem:";
		cin >> p->data;

		p->next = head->next;
		head->next = p;
	}
}

void merge(LinkList& a, LinkList&b, LinkList& c)
{
	if(a == NULL || b == NULL || c == NULL)
	{
		return;
	}
	
	SLNode* pa = a->next;
	SLNode* pb = b->next;
	SLNode* pc = c;
	
	while(pa != NULL && pb != NULL)
	{
		if(pa->data > pb->data)
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
			pc->next = NULL;
		}
		else
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			pc->next = NULL;
		}
	}

	pa == NULL ? pc->next = pb : pc->next = pa;

	return;
}

void back_output(LinkList p)
{
	if(p == NULL)
	{
		return;
	}

	back_output(p->next);
	cout << p->data << endl;
	
	return;
}

void back_output_v1(LinkList head)
{
	if(head == NULL)
	{
		return;
	}

	SLNode* pre = head;
	SLNode* curr = head->next;
	SLNode* next = NULL;

	while(curr != NULL)
	{
		next = curr->next;
		if(pre == head)
		{
			curr->next = NULL;
		}
		else
		{
			curr->next = pre;
		}

		pre = curr;
		curr = next;	
	}

	head->next = pre;

	print(head);

	return;
}

void find_k(LinkList head, int k)
{
	if(head == NULL)
	{
		cout << "list empty" << endl;
		return;
	}

	if(k < 1)
	{
		cout << "k not right" << endl;
		return;
	}
	
	SLNode* p1 = head->next;
	SLNode* p2 = head->next;
	int count = 0;
	while(p2 != NULL)
	{
		++count;
		if(count == k)
		{
			break;
		}

		p2 = p2->next;
	}

	if(p2 == NULL)
	{
		cout << "k not right" << endl;
		return;
	}

	while(p2 != NULL)
	{
		p2 = p2->next;
		if(p2 != NULL)
		{
			p1 = p1->next;
		}
	}

	cout << "back " << k << " is:" << p1->data << endl;

	
}

/*
输入都是第一个节点
*/
LinkList merge_v1(LinkList phead1, LinkList phead2)
{
	if(phead1 == NULL)
	{
		return phead2;
	}
	else if(phead2 == NULL)
	{
		return phead1;
	}

	LinkList pmerge = NULL;
	LinkList mergehead = NULL;
	if(phead1->data < phead2->data)
	{
		pmerge = phead1;
		mergehead = merge_v1(phead1->next, phead2);
		
	}
	else
	{
		pmerge = phead2;
		mergehead = merge_v1(phead1, phead2->next);
	}

	pmerge->next = mergehead;

	return pmerge;
	
}

bool check_circle(LinkList head)
{
	SLNode* p1 = head->next;
	SLNode* p2 = head->next->next;
	while(p1 != p2 && p1 != NULL && p2 != NULL)
	{
		p1 = p1->next;
		p2 = p2->next->next;
	}

	if(p1 == p2 && p1 != NULL && p2 != NULL)
	{
		return true;
	}

	return false;
}

LNode* find_circle_node(LinkList head)
{
	if(head == NULL)
	{
		cout << "invalid List head, head is NULL" << endl;
		return NULL;
	}
	SLNode* p1 = head->next;
	SLNode* p2 = head->next->next;
	while(p1 != p2 && p1 != NULL && p2 != NULL)
	{
		cout << "(" << p1->data << ", " << p2->data << ")" << endl;
		p1 = p1->next;
		p2 = p2->next->next;
		if(p1 == p2 && p1 != NULL && p2 != NULL)
		{	
			break;
		}
	}

	//第二轮扫描
	p1 = head;
	while(p1 != p2 && p1 != NULL && p2 != NULL)
	{
		cout << "(" << p1->data << ", " << p2->data << ")" << endl;
		p1 = p1->next;
		p2 = p2->next;
	}

	if(p1 == p2 && p1 != NULL && p2 != NULL)
	{
		return p1;
	}

	return NULL;
}

int main(int argc, char** argv)
{
	LinkList a = NULL;
	init(a);
	for(int i = 1; i < 10; ++i)
	{
		insert(a, i, i);
	}

	print(a);

	SLNode* p = a->next;
	while(p != NULL && p->data != 8)
	{
		p = p->next;
	}

	SLNode* tail = a->next;
	while(tail->next != NULL)
	{
		tail = tail->next;
	}

	tail->next = p;

	bool res = check_circle(a);

	if(res)
	{
		cout << "has circle" << endl;
	}
	else
	{
		cout << "no circle" << endl;
	}

	SLNode* node = find_circle_node(a);
	if(node  != NULL)
	{
		cout << "circle start node:" << node ->data << endl;
	}
	else
	{
		cout << "error" << endl;
	}
	
	
	
/*
	LinkList a = NULL, b = NULL, c = NULL;
	int n = 0;
	cout << "input elem num:";
	cin >> n;
	createList(a, n);

	cout << "list a:" << endl;
	print(a);


	cout << "input elem num:";
	cin >> n;
	createList(b, n);

	a->next = merge_v1(a->next, b->next);

	print(a);
	

	int k = 0;
	cout << "input k:";
	cin >> k;

	find_k(a, k);
*/
/*
	cout << "back list a:" << endl;
	back_output(a->next);

	cout << "back output list v1:" << endl;
	back_output_v1(a);

	cout << "output list a:" << endl;
	print(a);

	init(b);

	init(c);

	merge(a, b, c);
	
	print(c);

*/
	

	return 0;
}
