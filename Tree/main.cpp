#include <iostream>
using namespace std;
#define tab "\t"
#include<ctime>

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight) { /*cout << "EConstructor: " << this << endl;*/ }
		~Element() { /*cout << "EDestructor: " << this << endl;*/ }
		friend class Tree;
	}*Root;

	//						Private Methods:
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
		//Balance();
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
	
	void Erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		Data < Root->Data ? Erase(Data, Root->pLeft) : Erase(Data, Root->pRight);
		//Erase(Data, Root->pLeft);
		//Erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
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

public:
	Element* getRoot()const { return Root; };
	Tree() { Root = nullptr; /*cout << "TConstructor: " << this << endl;*/ }
	Tree(const std::initializer_list<int>list) :Tree()
	{
		for (int const *i = list.begin(); i != list.end(); ++i) insert(*i, Root);
	}
	~Tree() { /*Clear(Root); cout << "TDestructor: " << this << endl; */}
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
};
template<typename T> void performance(const Tree& tree,T(Tree::*Method)()const)
{
	clock_t start = clock();
	cout << (tree.*Method)() << endl;
	clock_t end = clock();
	cout << "Производительность - " << double(end - start) / CLOCKS_PER_SEC << endl;
}

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
	//tree.print();
	//cout << "Min значение дерева: " << tree.MinValue() << endl;
	//cout << "Max значение дерева: " << tree.MaxValue() << endl;
	//cout << "Размер дерева: " << tree.Count() << endl;
	//cout << "Сумма элементов дерева: " << tree.Sum() << endl;
	//cout << "Среднее-арифметическое элементов дерева: " << tree.Avg() << endl;
	////tree.Clear();
	////tree.print();
	////tree.Erase(41);
	////tree.print();
	//cout << "Глубина дерева: " << tree.Depht() << endl;
	//tree.Erase1(41);
	//tree.print();
	//tree.Balance();
	//Tree tree{ 41,25,67,16,89 };
	//tree.print();
	/*clock_t start = clock();
	tree.Balance();
	clock_t end = clock();
	cout << "Производительность - " << double(end - start) / CLOCKS_PER_SEC << endl;*/
	performance(tree, &Tree::Depht);
	tree.Balance();
	performance(tree, &Tree::Depht);
	tree.print();

	


	
	



		
}