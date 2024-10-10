#include <iostream>
using namespace std;
#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight) { cout << "EConstructor: " << this << endl; }
		~Element() { cout << "EDestructor: " << this << endl; }
		friend class Tree;
	}*Root;

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);

	}
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	int MinValue(Element* Root)const
	{
		return Root->pLeft == nullptr ? Root->Data : MinValue(Root->pLeft);
		//if (Root->pLeft == nullptr) return Root->Data;
		//MinValue(Root->pLeft);
	}
	int MaxValue(Element* Root)const { return Root->pRight == nullptr ? Root->Data : MaxValue(Root->pRight); }
	int Count(Element* Root)const { return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1; }
	int Sum(Element* Root)const { return Root == nullptr ? 0 : Sum(Root->pLeft)+Sum(Root->pRight) + Root->Data; }
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	} 


public:
	Element* getRoot()const { return Root; };
	Tree() { Root = nullptr; cout << "TConstructor: " << this << endl; } 
	~Tree() { Clear(Root);  cout << "TDestructor: " << this << endl; }
	void insert(int Data) { insert(Data, Root); }
	//						Methods:
	void print() { print(Root); }
	int MinValue() { return MinValue(Root); }
	int MaxValue() { return MaxValue(Root); }
	int Count() { return Count(Root); }
	int Sum() { return Sum(Root); }
	double Avg() { return (double)Sum(Root)/Count(Root); }
	void Clear() { Clear(Root); Root = nullptr; };



};




void main()
{

	setlocale(LC_ALL, "");
	int n;
	cout << "Введите рзмер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "Значение min " << tree.MinValue() << endl;
	cout << "Значение max " << tree.MaxValue() << endl;
	cout << "Размер дерева: "<<tree.Count() << endl;
	cout << "сумма: " << tree.Sum() << endl;
	cout << "Среднее значение: " << tree.Avg() << endl;
	//tree.Clear();
	//tree.print();


		
}