#include <iostream>
using namespace std;

/*
void printStr(string& str)
{
	cout << str << endl;
	return;
}


void f(int &a)
{
	cout << a << endl;
	return;
}

int main(int argc, char** argv)
{
	printStr(string("Hello world!"));
	int a = 1, b = 3;
	f(a + b);
	return 0;
}
*/
class cs
{
    public:
        cs(int i): i_(i)  { cout << "cs(" << i <<") constructor!" << endl; }
        ~cs() { cout << "cs destructor,i(" << i_ << ")" << endl; }

        cs& operator=(const cs& other)
        {
            i_ = other.i_;
            cout << "cs operator=()" << endl;
            return *this;
        }

        int get_i() const { return i_; }
        void change(int i)  { i_ = i; }

    private:
        int i_;
};

cs get_cs()
{
    static int i = 0;
    return cs(i++);
}

void func(cs& c)
{
   cout << "c:" << c.get_i() << endl;
}





int main()
{
     // 合法
     /*
    (get_cs() = cs(2)).change(323);
    get_cs() = cs(2);// operator=()
     */
    get_cs().change(32);
   

    //正确
//func(get_cs() = get_cs());

	//const cs& ref = get_cs();
	//ref.change(20);

	//func(get_cs());
    return 0;
}