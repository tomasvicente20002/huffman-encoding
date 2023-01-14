#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
	this->weight = -1;
	this->parent = nullptr;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

/// <summary>
/// True if is a leaf node, no childs
/// </summary>
/// <returns></returns>
bool BinaryTree::IsLeaf()
{
	return !(this->left) && !(this->right);

}