#pragma once
using namespace std;
#include<string>
class BinaryTree
{
public:
	BinaryTree* parent;
	BinaryTree* left;
	BinaryTree* right;
	/// <summary>
	/// True if is a leaf node, no childs
	/// </summary>
	/// <returns></returns>
	bool IsLeaf();

	BinaryTree();
	~BinaryTree() {};
	int weight;
	string path;
};
