#include <iostream>
using namespace std;
#define tab "\t"
#include<ctime>
#pragma comment(linker,"/STACK:100000000")


class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
		Element(int Data, Element * pLeft = nullptr, Element * pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
#ifdef DEBUG
			cout << "EConstructor: " << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor: " << this << endl;
#endif // DEBUG
		}
		bool isLeaf()const
		{
			return pLeft == pRight;
	    }
		friend class Tree;
	}*Root;
	int count = 0;
				
	//		Private Methods:
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
	int MinValue(Element* Root)const {return Root->pLeft == nullptr ? Root->Data : MinValue(Root->pLeft);}
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
	void Erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		Data < Root->Data ? Erase(Data, Root->pLeft) : Erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->isLeaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))
				{
					Root->Data = MaxValue(Root->pLeft);
					Erase(MaxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = MinValue(Root->pRight);
					Erase(MinValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int Depht(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return max(Depht(Root->pLeft), Depht(Root->pRight)) + 1;
	}
	void Balance(Element* Root)
	{
		if (Root == nullptr)return;
		if (abs(Count(Root->pLeft) - Count(Root->pRight)) < 2)return; //проверяем вес левой и правой ветки
		if (Count(Root->pLeft) > Count(Root->pRight)) // Если левая тяжелее делаем правый поворот
		{
			if(Root->pRight == nullptr) Root->pRight = new Element(Root->Data);
			else insert(Root->Data, Root->pRight);
			Root->Data = MaxValue(Root->pLeft);
			Erase(MaxValue(Root->pLeft), Root->pLeft);
		}
		else //Если правая тяжелее делаем левый поворот 
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Root->Data);
			else insert(Root->Data, Root->pLeft);
			Root->Data = MinValue(Root->pRight);
			Erase(MinValue(Root->pRight), Root->pRight);
		}
		Balance(Root->pLeft);
		Balance(Root->pRight);
		Balance(Root);
	}
	void out(Element*Root, int max, int indent, int space)
	{
		++count;
		if (count == 1) for (int i = 0; i < indent; i++)cout << "  ";
		if (Root == nullptr)cout << "  ";
		else cout << Root->Data;
		if (count == max) for (int i = 0; i < indent; i++)cout << "  ";
		else for (int i = 0; i < space; i++)cout << "  ";
	}
	void depth_print(Element* Root, int depth,int max, int indent,int space, int d)
	{
		if (depth == 0)
		{
			out(Root, max, indent, space);
			return;
		}
		if (Root == nullptr)
		{
			for(int i=0; i<d-depth; i++)out(Root, max, indent, space);
			return;
		}
		depth_print(Root->pLeft, depth - 1,max, indent,space,d);
		depth_print(Root->pRight, depth - 1,max, indent,space,d);
	}
	void tree_print(int depth, int max, int indent, int space)
	{
		if (depth+1> Depht(Root))return;
		depth_print(Root, depth, pow(2,depth),indent,space,depth);
		count = 0;
		cout << endl;
		cout << endl;
		if(depth<1)tree_print(depth+1, max, (indent - 1) / 2, max - 1);
		else if (depth==Depht(Root))tree_print(depth + 1,max,0,2);
		else tree_print(depth + 1,max,(indent-1)/2,(space-1)/2);
	}

public:
	Element* getRoot()const { return Root; };
	Tree() { Root = nullptr; cout << "TConstructor: " << this << endl; }
	Tree(const std::initializer_list<int>list) :Tree()
	{
		for (int const *i = list.begin(); i != list.end(); ++i) insert(*i, Root);
	}
	~Tree() {Clear(Root); cout << "TDestructor: " << this << endl;}

	//						Public Methods:

	void insert(int Data) { insert(Data, Root); }
	void print() { print(Root); cout << endl; }
	int MinValue()const { return MinValue(Root); }
	int MaxValue()const { return MaxValue(Root); }
	int Count()const { return Count(Root); }
	int Sum()const { return Sum(Root); }
	double Avg()const { return (double)Sum(Root)/Count(Root); }
	void Clear() { Clear(Root); Root = nullptr; };
	void Erase(int Data) { Erase(Data, Root); }
	int Depht()const { return Depht(Root); }
	void Balance() { Balance(Root); }
	void tree_print()
	{ 
		int max = pow(2, Depht(Root) - 1); 
		tree_print(0, max,max-1,0); 
	}
	
};
template<typename T> void performance(string name, const Tree& tree, T(Tree::* Method)()const)
{
	clock_t start = clock();
	cout << (tree.*Method)() << endl;
	clock_t end = clock();
	cout << "Производительность "<<name<<": " << double(end - start) / CLOCKS_PER_SEC << endl;
}
template<typename T1, typename T2> void performance(string name, Tree& tree, T1(Tree::* Method)(T2), T2 Data)
{
	clock_t start = clock();
	(tree.*Method)(Data);
	clock_t end = clock();
	cout << "Производительность " << name << ": " << double(end - start) / CLOCKS_PER_SEC << endl;
}
template<typename T> void performance(string name, Tree& tree, T(Tree::* Method)())
{
	clock_t start = clock();
	(tree.*Method)();
	clock_t end = clock();
	cout << "Производительность " << name << ": " << double(end - start) / CLOCKS_PER_SEC << endl;
}
void main()
{

	setlocale(LC_ALL, "");

	int n;
	cout << "Введите рзмер дерева: "; cin >> n;
	Tree tree;
	clock_t start = clock();
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	clock_t end = clock();
	cout << "Производительность - " << double(end - start) / CLOCKS_PER_SEC << endl;
	performance("Print",tree, &Tree::print);
	cout << "Min значение дерева: "; performance("Min", tree, &Tree::MinValue);
	cout << "Max значение дерева: "; performance("Max",tree, &Tree::MaxValue);
	cout << "Размер дерева: "; performance("Count", tree, &Tree::Count);
	cout << "Сумма элементов дерева: "; performance("Sum", tree, &Tree::Sum);
	cout << "Среднее-арифметическое элементов дерева: "; performance("Arg",tree, &Tree::Avg);
	performance("tree-print", tree, &Tree::tree_print);
	performance("Erase", tree, &Tree::Erase, 41);
	tree.tree_print();
	cout << "Глубина дерева: "; performance("Depth",tree, &Tree::Depht);
	performance("Balance", tree, &Tree::Balance);
	tree.tree_print();
	//Tree tree{ 41,25,67,16,89 };
	//tree.print();
	
	
		


	


	
	



		
}