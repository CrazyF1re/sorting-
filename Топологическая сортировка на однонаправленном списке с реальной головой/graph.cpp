#include "graph.h"
#include <iostream>
using namespace std;
Graph::~Graph()
{
}

Lider* Graph::Find_key(int k)
{
	Lider* p = new Lider(-1);
	if (this->Is_empty())return p;
	else {
		Lider* temp = head;
		while (temp->next != 0 && temp->key != k)temp = temp->next;
		if (temp->key == k)return temp;
		else return p;
	}
}

void Graph::Print()
{
	Lider* temp = head;
	if (this->Is_empty() == 0)temp = temp->next;
	while (temp != 0) 
	{
		cout << temp->key << ' ';
		temp = temp->next;
	}
	cout << endl;
}

void Graph::Add_to_head(int k)
{	
	Lider* temp = new Lider(k);
	temp->next = head;
	head = temp;
	
}

void Graph::Del(Lider* p)
{
	Lider* temp = head;
	while (temp->next != p)temp = temp->next;
	temp->next = p->next;
	delete p;
}

void Graph::Clear()
{
	Lider* temp = head;

	while (head->next != 0) 
	{
		delete temp;
		head = head->next;
		temp = head;
	}
	delete temp;
}

void Graph::Form_graph()
{
	int a, b;//вершины
	cin >> a >> b;
	Lider* pa = Find_key(a);
	Lider* pb = Find_key(b);
	while (a != 0) 
	{
		if (pa->key == -1) {
			Add_to_head(a); pa = Find_key(a);
		}
		if (pb->key == -1) 
		{
			Add_to_head(b); pb = Find_key(b);
		}
		pb->count++;
		Trailer* s = new Trailer();
		s->ptr = pb;
		s->next = pa->tr;
		pa->tr = s;
		cin >> a >> b;
		pa = Find_key(a);
		pb = Find_key(b);
	}
}

void Graph::Sort_graph(Graph& LD)
{
	
	Lider* temp = LD.head;
	Graph LDnew;
	while (temp != 0)
	{
		if (temp->count == 0) {
			LDnew.Add_to_head(temp->key);
		}
		temp = temp->next;
	}//добавляем в LDnew вершины с count =0;

	LDnew.head = LDnew.head->next;
	while (!LDnew.Is_empty()) //основной цикл
	{
		Lider* temp = LDnew.head;
		LDnew.head = LDnew.head->next;//исключение головной вершины
			//уменьшаем на единицу поле count у всех элементов списка LD
		
		if (LD.Find_key(temp->key)->tr!=0)
		{
			Trailer* tmp = LD.Find_key(temp->key)->tr;
			while (tmp->next != 0)
			{
				LD.Find_key(tmp->ptr->key)->count--;
				if (LD.Find_key(tmp->ptr->key)->count == 0) {
					LDnew.Add_to_head(tmp->ptr->key);//добавление вершины в LDnew
				}
				Trailer* T = tmp;
				tmp = tmp->next;
				delete T;//удаляем узел в Trailer
			}
			LD.Find_key(tmp->ptr->key)->count--;
			if (LD.Find_key(tmp->ptr->key)->count == 0) {
				LDnew.Add_to_head(tmp->ptr->key);
			}
			delete tmp;
		}
		cout << temp->key << "   !   ";//выписываем в решение p->key
		this->Add_to_tail(temp);
		delete temp;
	}
}

bool Graph::Is_empty()
{
	if (head->next == 0)return 1;
	return 0;
}

Lider* Graph::Find_count(int k)
{
	Lider* temp = head;
	while (temp->count != k && temp->next!=0)temp = temp->next;
	if (temp->count == k)return temp;
	return head;
}

void Graph::Exclude(Lider* p)
{

}

void Graph::Add_to_tail(Lider* p)
{
		Lider* tmp = new Lider(p->key);
		Lider* temp = head;
		while (temp->next != 0) {
			temp = temp->next;
		}
		temp->next = tmp;
}
