#pragma once
#include <iostream>
using namespace std;
struct Trailer;
struct Lider 
{
	int key,count;
	Lider* next;
	Trailer* tr;
	Lider() { key = count = 0; next = 0; tr = 0; }
	Lider(int k) { key = k; next = 0; tr = 0; count = 0; }

};
struct Trailer
{
	Lider* ptr;
	Trailer* next;
	Trailer() { ptr = 0; next = 0; }
};
struct Graph
{
	Lider* head = new Lider();
	Graph() { head->next = 0; head->tr = 0;head->key = 0; head->count = 0; };
	~Graph();
	Lider* Find_key(int k);
	void Print();
	void Add_to_head(int k);
	void Del(Lider*p);
	void Clear();
	void Form_graph();
	void Sort_graph(Graph & X);
	bool Is_empty();
	Lider* Find_count(int k);// поиск узла с count = 0
	void Exclude(Lider* p);
	void Add_to_tail(Lider*p);
};