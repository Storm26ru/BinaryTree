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
public:
	Element* getRoot()const { return Root; };
	Tree() { Root = nullptr; cout << "TConstructor: " << this << endl; } 
	~Tree() { cout << "TDestructor: " << this << endl; }
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
	//						Methods:
	void print(Element* Root=nullptr)const
	{
		Root = this->Root;
		cout << Root << endl;
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
		
	}



};




void main()
{

	setlocale(LC_ALL, "");
	int n;
	cout << "Âגוהטעו נחלונ הונוגא: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print();


		
}