#include <iostream>
#include <cstdlib>
#include <string>
#include <stack>
using namespace std;

template <typename T>
struct  Stack
{
	T* base;
	T* top;
	int size;
};

//typedef struct Stack<T> Stack<T>;

const int INCSIZE = 10;

template <typename T>
bool initStack(Stack<T>& s, int size)
{
	if(size <= 0)
	{
		cout << "init stack fail, size error" << endl;
		return false;
	}
	
	s.base = new T[size];
	s.top = s.base;
	s.size = size;

	cout << "init stack suc, size:" << s.size << endl;

	return true;
}

template <typename T>
void clearStack(Stack<T>& s)
{
	s.top = s.base;
	return;
}


template <typename T>
bool empty(Stack<T> s)
{
	return s.base == s.top;	
}


template <typename T>
int len(Stack<T> s)
{
	return s.top - s.base;
}


template<typename T> void copy(T* left, T* right);

template <typename T>
T* getTop(Stack<T> s)
{
	if(s.base == s.top)
	{
		return NULL;
	}
	T *p = s.top - 1;

	return p;
}


template <typename T>
void push(Stack<T>& s, T elem)
{
	if(s.size == (s.top - s.base))
	{
		T* tmp = (T*)realloc(s.base, (s.size + INCSIZE) * sizeof(T));
		if(tmp == NULL)
		{
			cout << "stack full" << endl;
			return;
		}

		s.base = tmp;
		s.top = s.base + s.size;
		s.size += INCSIZE;
	}

	copy(s.top, &elem);

	++s.top;

	return;
}

template <typename T>
T pop(Stack<T>& s)
{
	--s.top;
	T elem;
	copy(&elem, s.top);

	return elem;
}

template <typename T> void visit(T*);
template <typename T>
void print(Stack<T> s)
{
	T* p = s.base;
	int cnt = 0;
	
	cout << "base:" << endl;
	while(p != s.top)
	{
		visit(p);
		++cnt;
		p = s.base + cnt;
	}
	cout << "top" << endl;

	return;
}



/*
template <typename T>
void input(Stack& s1, Stack& s2)
{
	if(!empty(s1) || !empty(s2))
	{
		cout << "stack not empty" << endl;
		return;
	}
	
	char c;
	while(true)
	{
		cin >> c;
		if(c == '.')
		{
			break;
		}
		switch(c)
		{
			case '+':	
			case '-':	
			case '*':	
			case '/':
				push(s1, (double)c);
				break;
			default:
				push(s2, atof(&c));
		}
	}
	
	return;
}

double cal(Stack& s1, Stack& s2)
{
	if(empty(s1) || empty(s2))
	{
		cout << "stack needs not empty" << endl;
		return 0;
	}

	int calsign;
	double param1 = 0;
	double param2 = 0;


	while(!empty(s1))
	{
		calsign = (int)pop(s1);
	
		switch(calsign)
		{
			case '+':
				param1 = pop(s2);
				param2 = pop(s2);
				if(param1 == -1 || param2 == -1)
				{
					cout << "error" << endl;
					return 0;
				}
				push(s2, param1 + param2);
				break;
			case '-':
				param1 = pop(s2);
				param2 = pop(s2);
				if(param1 == -1 || param2 == -1)
				{
					cout << "error" << endl;
					return 0;
				}
				push(s2, param2 - param1);
				break;
			case '*':
				param1 = pop(s2);
				param2 = pop(s2);
				if(param1 == -1 || param2 == -1)
				{
					cout << "error" << endl;
					return 0;
				}
				push(s2, param2 * param1);
				break;
			case '/':
				param1 = pop(s2);
				param2 = pop(s2);
				if(param1 == -1 || param2 == -1)
				{
					cout << "error" << endl;
					return 0;
				}
				push(s2, param2 / param1);
				break;
			default:
				cout << "cal sign not right" << endl;
				return 0;
		}
	}

	if(empty(s2))
	{
		cout << "expression error" << endl;
		return 0;
	}
	return pop(s2);
}

void convension(int format)
{
	if(format != 2 &&  format != 8)
	{
		cout << "format param error" << endl;
		return;
	}
	
	Stack<int> s;
	initStack(s, 10);
	
	int num = 0;
	cout << "input num:";
	cin >> num;
	
	while(num)
	{
		push(s, num % format);
		num = num / format;
	}

	cout << "the " << format << ":";
	while(!empty(s))
	{
		cout << pop(s);
	}
	cout << endl;

	return;
}

void bracketfit()
{
	string inputstr;

	cout << "please input brackets:";

	while(true)
	{
		getline(cin, inputstr);

		if(inputstr.size() > 0)
		{
			break;
		}
	}

	Stack<char> s;
	initStack(s, 10);

	size_t size = inputstr.size();
	char left = ' ';
	for(int i = 0; i < size; ++i)
	{
		if(inputstr[i] == '(' || inputstr[i] == '[')
		{
			push(s, inputstr[i]);
			continue;
		}

		if(inputstr[i] == ')' || inputstr[i] == ']')
		{
			left = pop(s);
			if(left == -1)
			{
				cout << "stack empty, format error" << endl;
				return;
			}
			if(inputstr[i] == ')')
			{
				if(left == '(')
				{
					cout << "find fit bracket:" << left << " " << inputstr[i] << endl;
				}
				else
				{
					cout << "format error" << __LINE__ << endl;
					return;
				}
			}
			else
			{
				if(left == '[')
				{
					cout << "find fit bracket:" << left << " " << inputstr[i] << endl;
				}
				else
				{
					cout << "format error" << __LINE__ << endl;
					return;
				}
			}
			
		}
		else
		{
			cout << "format error:" << inputstr << endl;
			return;
		}
	}

	return;
}
*/

const int MAZE_SIZE = 4;
typedef struct Node
{
	int x;
	int y;
	int direction; //�´ο�����̽�ķ��򣬴�0��ʼ��3
}Node;

int direction[4][2] = {
	{1, 0},
	{0, 1},
	{-1, 0},
	{0, -1}
};

template<> void visit<Node>(Node* p)
{
	cout << "x:" << p->x << ", y:" << p->y << ", direction:" << p->direction << endl;
	return;
}
template<> void copy<Node>(Node* left, Node* right)
{
	left->x = right->x;
	left->y = right->y;
	left->direction = right->direction;

	return;
}

template<> void visit<double>(double* p)
{
	cout << *p << endl;
	return;
}
template<> void visit<char>(char* p)
{
	cout << *p << endl;
	return;
}

template<> void visit<string>(string* p)
{
	cout << *p << endl;
	return;
}

template<> void copy<double>(double* left, double* right)
{
	*left = *right;
	return;
}

template<> void copy<char>(char* left, char* right)
{
	*left = *right;
	return;
}

template<> void copy<string>(string* left, string* right)
{
	*left = *right;
	return;
}


const int NOT_VISITED = 0;
const int  VISITED = 1;

void maze()
{
	//�����Թ�
	int maze[MAZE_SIZE][MAZE_SIZE] = 
	{
		{0, 0, 0, 1},
		{0, 0, 1, 0},
		{0, 0, 1, 0},
		{1, 0, 1, 0}
	};

	//�����Ƿ񱻷��ʣ�1 �ѷ��ʹ���0 δ���ʹ�
	int visit[MAZE_SIZE][MAZE_SIZE] = 
	{
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	int start_x = 0, start_y = 0;
	while(true)
	{
		cout << "input start x:";
		cin >> start_x;
		if(start_x >= 0 && start_x < MAZE_SIZE)
		{
			break;
		}
	}

	while(true)
	{
		cout << "input start y:";
		cin >> start_y;
		if(start_y >= 0 && start_y < MAZE_SIZE)
		{
			break;
		}
	}

	if(maze[start_x][start_y] == 1)
	{
		cout << "no path" << endl;
		return;
	}

	
	int end_x = 0, end_y = 0;

	while(true)
	{
		cout << "input end_x:";
		cin >> end_x;
	}

	cout << "input end_y:";
	cin >> end_y;


	Stack<Node> s;
	initStack(s, 10);
	
	//��ʼ��
	Node node;
	node.x = start_x;
	node.y = start_y;
	node.direction = 0;
	visit[start_x][start_y] = VISITED;
	push(s, node);
	
	//��ʼ��̽
	Node* curr_node = NULL;
	int next_x = 0, next_y = 0;
	while(!empty(s))
	{
		curr_node = getTop(s);
		//�ж��Ƿ�Ϊ����λ��
		if(curr_node->x == end_x && curr_node->y == end_y)
		{
			cout << "find path" << endl;
			break;
		}
		
		//�жϸõ����з����Ƿ񶼷������
		//������ϵ����ýڵ�
		if(4 <= curr_node->direction)
		{
			pop(s);
			continue;
		}
		
		//δ������ϣ������һ������Ľڵ�����Ϊ�ѷ��ʣ���ǰ�ڵ㷽������
		while(curr_node->direction < 4)
		{
			next_x = curr_node->x + direction[curr_node->direction][0];
			next_y = curr_node->y + direction[curr_node->direction][1];
			if(next_x >= 0 && next_x < MAZE_SIZE 
				&& next_y >=0 && next_y < MAZE_SIZE
				&& maze[next_x][next_y] == 0
				&& visit[next_x][next_y] == 0)
			{
				node.x = next_x;
				node.y = next_y;
				node.direction = 0;

				visit[node.x][node.y] = VISITED;

				push(s, node);
				++curr_node->direction;
				break;
			}

			++curr_node->direction;
		}
	}

	//����Թ�·��
	if(!empty(s))
	{
		Node* p = s.base;
		while(p != s.top)
		{
			maze[p->x][p->y] = -5;
			++p;
		}

		for(int i = 0; i < MAZE_SIZE; ++i)
		{
			for(int j = 0; j < MAZE_SIZE; ++j)
			{
				cout << maze[i][j] << "       ";
			}

			cout << endl;
		}
	}
	else
	{
		cout << "no path" << endl;
	}

	return;
}

int get_op_level(char op)
{
	if(op == '+' || op == '-')
	{
		return 0;
	}

	if(op == '*' || op == '/')
	{
		return 1;
	}

	return -1;
}

bool check_input(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/'
		|| (c >= '0' && c <= '9') || c == '(' || c == ')');
}

void compute()
{
	//����һ�����ʽ
	string line;

	getline(cin, line);

	if(line.empty())
	{
		cout << "empty string" << endl;
		return;
	}

	//��ʼ��2��ջ��һ����������һ����Ų���
	Stack<double> s1;
	Stack<char> s2;
	initStack(s1, 10);
	initStack(s2, 10);

	//ɨ����ʽ
	int size = line.size();
	int i = 0, former = 0;
	while(i < size)
	{	
		/*
		cout << "++++++" << endl;
		print(s1);
		cout << "++++++" << endl;
		print(s2);
		*/
		bool check = check_input(line[i]);
		if(!check)
		{
			cout << "line format error, " << __LINE__ << endl;
			return;
		}
		
		if(line[i] == '(')
		{
			push(s2, line[i]);
			++i;
			former = i;
			continue;
		}

		//cout << "meet char " << line[i] << endl;
		if(line[i] == ')')
		{
			//cout << "meet )" << endl;
			++i;
			former = i;
			
			//ѭ���������źͲ������㣬ֱ������(����
			while(true)
			{
				if(empty(s2))
				{
					cout << "line format error, " << __LINE__ << endl;
					return;
				}
				
				char op = pop(s2);
				//cout << "meet ), pop operator:" << op << endl;
				if(op == '(')
				{
					cout << "pop (" << endl;
					break;
				}
				
				if(empty(s1))
				{
					cout << "line format error, " << __LINE__ << endl;
					return;
				}
				double p1 = pop(s1);

				if(empty(s1))
				{
					cout << "line error, " << __LINE__ << endl;
					return;
				}
				double p2 = pop(s1);
				double res = 0;
			
				switch(op)
				{
					case '+':
						res = p1 + p2;
						break;
					/*
					case '-':
						res = p1 - p2;
						break;
					*/
					case '*':
						res = p1 * p2;
						break;
					case '/':
						res = p2 / p1;
						break;
					default:
						{
							cout << "line format error, " << __LINE__ << endl;
							return;
						}
				}
				push(s1, res);
			}

			continue;
		}

		
		
		//��������
		if(line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
		{
			if(empty(s2))
			{
				push(s2, line[i]);
				++i;
				former = i;
				continue;
			}

			char* p = getTop(s2);
			int op1_level = get_op_level(*p);
			int op2_level = get_op_level(line[i]);
			
			//���ڵ���ջ��������ȼ�������ջ
			if(op2_level >= op1_level)
			{
				push(s2, line[i]);
				++i;
				former = i;
				continue;
			}

			//С��ջ�����ȼ����򵯳����������м���
			if(op1_level >= op2_level)
			{
				if(empty(s1))
				{
					cout << "line error, " << __LINE__ << endl;
					return;
				}
				double p1 = pop(s1);

				if(empty(s1))
				{
					cout << "line error, " << __LINE__ << endl;
					return;
				}
				double p2 = pop(s1);
				double res = 0;
				char op = pop(s2);
				switch(op)
				{
					case '+':
						res = p1 + p2;
						break;
					/*
					case '-':
						res = p1 - p2;
						break;
					*/
					case '*':
						res = p1 * p2;
						break;
					case '/':
						res = p2 / p1;
						break;
				}
				push(s1, res);
				continue;
			}
		}

		
		while(line[i] >= '0' && line[i] <= '9' && i < size)
		{
			++i;
		}

		string str = line.substr(former, i - former);
		if(str.size() <= 0)
		{
			cout << "line format error, " << __LINE__ << endl;
			return;
		}

		//�ǲ�������ѹ�����ջ
		double param = atof(str.c_str());
		//���ǰһ�������ǲ��Ǽ��ţ��Ǽ��ŵ�ʱ����Ҫת���µ�ǰ����
		if(!empty(s2))
		{
			char* former_op = getTop(s2);
			if(*former_op == '-')
			{
				pop(s2);
				param = 0 - param;
				push(s2, '+');
				cout << "get a - operator, push " << param << " in stack." << endl;
			}
		}
		
		push(s1, param);
	}


	
	//���ʽɨ����ϣ����ջ�л���Ԫ��δ��ɼ��㣬����㣬ֱ������������������
	while(!empty(s2))
	{
		/*
		cout << "########" << endl;
		print(s1);
		cout << "########" << endl;
		print(s2);
		*/
		
		if(empty(s1))
		{
			cout << "line error, " << __LINE__ << endl;
			return;
		}

		double p1 = pop(s1);

		if(empty(s1))
		{
			cout << "line error, " << __LINE__ << endl;
			return;
		}

		double p2 = pop(s1);
		double res = 0;
		char op = pop(s2);
		switch(op)
		{
			case '+':
				res = p1 + p2;
				break;
			case '-':
				res = p1 - p2;
				break;
			case '*':
				res = p1 * p2;
				break;
			case '/':
				res = p2 / p1;
				break;
		}
		push(s1, res);
	}

	if(empty(s1))
	{
		cout << "line format error, " << __LINE__ << endl;
		return;
	}

	double res = pop(s1);
	if(empty(s1))
	{
		cout << "res: " << res << endl;
	}
	else
	{
		cout << "line format error, " << __LINE__ << endl;
	}

	return;
}

bool check_char(const char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/' || ('0' <= c && c <= '9');
}

int get_level(const char* c)
{
	if(*c == '+' || *c == '-')
	{
		return 0;
	}


	return 1;
}

int compare_level(const char* c1, const char* c2)
{
	return get_level(c1) > get_level(c2) ? 1 : 0;
}
void transform_center_to_back()
{
	//����һ�����ʽ��ֻ����0-9֮������֣������ֻ֧��+,-,*/
	string line;
	while(true)
	{
		cout << "please input expression:";
		cin >> line;
		if(line.size() > 0)
		{
			break;
		}
		line.clear();
	}

	//��ʼ��2��ջ��һ�����������һ���������
	stack<string> optr, opnd;

	//��ʼ�Ӻ���ǰɨ����ʽ
	/*
	1��������ֱ����ջ;
	4�����������ţ���ջ���㣬ֱ�����������ţ�
	5���������ȼ���ջ��������͵����㣬����ջ��������ȼ��㣻
	6��ɨ����Ϻ󣬵��������������㣬֪�������ջΪ�գ�
	*/

	int size = line.size();
	int i = size - 1;
	while(i >= 0)
	{
		//cout << "meet char " << line[i] << endl;
		if(check_char(line[i]))
		{
			//������
			if('0' <= line[i] && line[i] <= '9')
			{
				string tmp(1, line[i]);
				opnd.push(tmp);
				--i;
				continue;
			}

			//�����
			if(optr.empty()) //�״�ֱ����ջ
			{
				string tmp(1, line[i]);
				optr.push(tmp);
				--i;
				continue;
			}

			string top_optr = optr.top();
			string curr_optr_str(1, line[i]);
			if(compare_level(top_optr.c_str(), curr_optr_str.c_str()) == 1)
			{
				//����
				string p1 = opnd.top();
				opnd.pop();
				string p2 = opnd.top();
				opnd.pop();

				optr.pop();

				
				p1 = p1 + p2 + top_optr;
				
				opnd.push(p1);
				continue;
			}

			//�����ֱ����ջ
			string str(1, line[i]);
			optr.push(str);
			--i;
		}
		else
		{
			cout << "invalid char, " << line[i] << ", " << __LINE__ << endl;
			return;
		}
		
	}

	//ɨ����Ϻ�
	while(!optr.empty())
	{
		string top = optr.top();
		optr.pop();
		if(opnd.empty())
		{
			cout << "line format error, " << __LINE__ << endl;
			return;
		}

		string p1 = opnd.top();
		opnd.pop();
		if(opnd.empty())
		{
			cout << "line format error, " << __LINE__ << endl;
			return;
		}

		string p2 = opnd.top();
		opnd.pop();
		
		p1 = p1 + p2 + top;

		opnd.push(p1);
	}

	if(opnd.empty())
	{
		cout << "line format error, " << __LINE__ << endl;
		return;
	}

	string res = opnd.top();
	opnd.pop();
	if(opnd.empty())
	{
		cout << "res: " << res << endl;
	}
	else
	{
		cout << "line format error, " << __LINE__ << endl;
	}
	

	return;
}
int main(int argc, char** argv)
{
	transform_center_to_back();
/*
	compute();

	maze();

	bracketfit();

	convension(2);

	Stack s1, s2;
	initStack(s1, 10);
	initStack(s2, 10);
	input(s1, s2);

	cout << "s1" << endl;
	print(s1);
	cout << "s2" << endl;
	print(s2);

	double res = cal(s1, s2);

	cout << "res:" << res << endl;

	Stack s;
	int n = 0;

	cout << "input stack size:";
	cin >> n;

	bool cres = initStack(s, n);
	if(!cres)
	{
		cout << "init stack fail." << endl;
		return 1;
	}

	print(s);

	if(empty(s))
	{
		cout << "stack empty" << endl;
	}
	else
	{
		cout << "stack not empty" << endl;
	}

	cout << "input elem size:";
	cin >> n;
	int elem = 0;
	for(int i = 0; i < n; ++i)
	{
		cout << "input elem:";
		cin >> elem;
		push(s, elem);
	}

	print(s);

	if(empty(s))
	{
		cout << "stack empty" << endl;
	}
	else
	{
		cout << "stack not empty" << endl;
	}

	cout << "top elem:" << getTop(s) << endl;

	pop(s);
	cout << "after pop, top elem:" << getTop(s) << endl;
	
	print(s);

	clearStack(s);

	cout << "after clear stack" << endl;
	print(s);
*/	
	return 0;

}
