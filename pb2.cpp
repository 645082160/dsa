#include <iostream>
using namespace std;
class Singleton
{
private:
	Singleton(){};
	Singleton(const Singleton&);
	static Singleton* m_instance;
public:
	~Singleton(){}
	static Singleton* get_instance()
	{
		if(m_instance == NULL)
		{
			//lock()
			if(m_instance == NULL)
			{
				m_instance = new Singleton;
			}
			//unlock()
		}

		return m_instance;
	}
};

Singleton* Singleton::m_instance = NULL;

int main(int argc, char** argv)
{
	Singleton* ptr = Singleton::get_instance();
	
	return 0;
}