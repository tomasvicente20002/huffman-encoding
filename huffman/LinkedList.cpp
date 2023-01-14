#pragma once
#include "LinkedList.h"


LinkedListNode::LinkedListNode()
{
	this->Next = nullptr;
	this->Previous = nullptr;
	this->Value = nullptr;
}

LinkedListNode::LinkedListNode(void* value)
	:LinkedListNode()
{
	this->Value = value;
}

LinkedListNode::~LinkedListNode()
{
	//Free the node data content
	delete(this->Value);
}

LinkedListNode* LinkedList::Add(void* value)
{
	try
	{
		//Obter um novo nó
		LinkedListNode* node = new LinkedListNode(value);


		//Cenário 1 lista está vazia
		if (this->Head == nullptr && this->Tail == nullptr)
		{
			//Cabeça e igual ao nó
			this->Head = node;
		}
		//Cenário 2  já tem elementos
		else
		{
			//O cauda irá passar a ser o penultimo nó , logo o nex passa apontar para o novo nó que irá ser a nova cauda
			this->Tail->Next = node;
			//O nó antererior a novo nó (nova cauda) é a cauda atual
			node->Previous = this->Tail;
		}

		//A cauda é igual o nova a inserir
		this->Tail = node;

		return node;
	}
	catch (...)
	{
		return nullptr;
	}
}

void LinkedList::BoobbleShort(bool compareFnc(const void*, const void*))
{
	LinkedListNode** h;
	bool swapped = true;

	for (int i = 0; swapped; i++) {

		h = &this->Head;
		swapped = false;

		for (int j = 0; *h != nullptr && !(*h == this->Tail); j++) {

			LinkedListNode* p1 = *h;
			LinkedListNode* p2 = p1->Next;

			if (compareFnc(p1->Value, p2->Value))
			{
				LinkedList::SwapDataNodes(p1, p2);
				swapped = true;
			}

			h = &(*h)->Next;
		}

		if (swapped == 0)
			break;
	}
}

void LinkedList::SwapDataNodes(LinkedListNode* ptr1, LinkedListNode* ptr2)
{
	void* tmp = ptr2->Value;
	ptr2->Value = ptr1->Value;
	ptr1->Value = tmp;
}

LinkedListNode* LinkedList::GenericFind(const void* value, bool compareFnc(const void*, const void*))
{
	LinkedListNode* no = this->Head;

	while (no != nullptr)
		if (compareFnc(value, no->Value))
			return no;
		else
			no = no->Next;

	return nullptr;
}

