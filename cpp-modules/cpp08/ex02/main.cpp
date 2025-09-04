#include "MutantStack.hpp"
#include <stack>
#include <list>
#include <iostream>

class Person {
	private:
		std::string _name;
		int _age;
	public:
		Person(std::string name, int age): _name(name), _age(age) {};
		~Person() {};
		Person() {};
		Person(const Person &rhs): _name(rhs._name), _age(rhs._age) {};

		const std::string &getName() const { return _name; };
		int getAge() const { return _age; };
		const std::string getPerson() const { return _name + ", " + std::to_string(_age); };
};
std::ostream& operator<<(std::ostream &os, const Person &person) { os << person.getPerson(); return os; };

static void testMutantStackPerson()
{
	std::cout << "\033[0;33m** Testing with mutantstack and person class **\033[0m\n";
	MutantStack<Person> mstack;
	Person joe("Joe", 15);
	mstack.push(joe);
	mstack.emplace("Bob", 42);
	std::cout << "Top: " << mstack.top() << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;
	MutantStack<Person>::iterator it = mstack.begin();
	MutantStack<Person>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << it->getPerson() << std::endl;
		++it;
	}
	mstack.pop();
	std::cout << "Top: " << mstack.top() << std::endl;
	std::cout << "Size: " << mstack.size() << std::endl;
	std::cout << std::endl;
}

static void testMutantStack()
{
	std::cout << "\033[0;33m** Testing with mutantstack **\033[0m\n";
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "Top: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "Size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	std::cout << std::endl;
}

static void testStack()
{
	std::cout << "\033[0;33m** Testing with stack (no iterators) **\033[0m\n";
	std::cout << "\033[0;33m-\033[0m The iterated output will be reverse\n";
	std::stack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << "Top: " << mstack.top() << std::endl;
	mstack.pop();
	std::cout << "Size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	while (mstack.size())
	{
		std::cout << mstack.top() << std::endl;
		mstack.pop();
	}
	std::cout << std::endl;
}

static void testList()
{
	std::cout << "\033[0;33m** Testing with list **\033[0m\n";
	std::list<int> mstack;
	mstack.push_back(5);
	mstack.push_back(17);
	std::list<int>::iterator topIt = mstack.end();
	--topIt;
	std::cout << "Top: " << *topIt << std::endl;
	mstack.pop_back();
	std::cout << "Size: " << mstack.size() << std::endl;
	mstack.push_back(3);
	mstack.push_back(5);
	mstack.push_back(737);
	mstack.push_back(0);
	std::list<int>::iterator it = mstack.begin();
	std::list<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::cout << std::endl;
}

int main()
{
	testMutantStackPerson();
	testMutantStack();
	testStack();
	testList();
	return 0;
}
