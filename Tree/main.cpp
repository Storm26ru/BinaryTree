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
	int MinValue(Element* Root)
	{
		if (Root->pLeft->pLeft == nullptr) return Root->Data;
		MinValue(Root->pLeft);
	}

public:
	Element* getRoot()const { return Root; };
	Tree() { Root = nullptr; cout << "TConstructor: " << this << endl; } 
	~Tree() { cout << "TDestructor: " << this << endl; }
	void insert(int Data) { insert(Data, Root); }
	//						Methods:
	void print() { print(Root); }
	int MinValue() { return MinValue(Root); }



};




void main()
{

	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите рзмер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "«начение " << tree.MinValue() << endl;


		
}