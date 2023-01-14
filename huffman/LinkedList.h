#pragma once
using namespace std;
#include <string>


class LinkedListNode
{
public:
	LinkedListNode();
	explicit LinkedListNode(void* value);
	~LinkedListNode();
	void* Value;
	LinkedListNode* Next;
	/// <summary>
	/// No anterior
	/// </summary>
	LinkedListNode* Previous;
};

class LinkedList
{
public:
	LinkedListNode* Add(void* value);
	void BoobbleShort(bool compareFnc(const void*, const void*));
	static void SwapDataNodes(LinkedListNode* ptr1, LinkedListNode* ptr2);
	/// <summary>
/// Cabeça (primeiro elemento)
/// </summary>
	LinkedListNode* Head;
	/// <summary>
	/// Cauda (ultimo elemento)
	/// </summary>
	LinkedListNode* Tail;
	LinkedListNode* GenericFind(const void *value, bool compareFnc(const void*, const void*));
};
