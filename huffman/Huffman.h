#pragma once
using namespace std;
#include "Helpers.h"
#include "LinkedList.h"
#include "BinaryTree.h"


class OcorrenciaLetras
{
public:
	string letra;
	int cnt;
	BinaryTree* no;
	OcorrenciaLetras() {
		this->cnt = 0;
		this->no = nullptr;
		this->letra = string("");
	};
	~OcorrenciaLetras() {};

};

class MapValue
{
public:

	string leter;
	string newValue;
	MapValue() {};
	~MapValue() {};
};

class Huffman
{
private:
	string ReadPath;
	string WritePath;

public:
	Huffman(string readPath, string writePath)
	{
		this->ReadPath = readPath;
		this->WritePath = writePath;
	}
	/// <summary>
	/// Encode the file
	/// </summary>
	/// <returns></returns>
	bool Encode();
	BinaryTree* Tree;

private:

	LinkedList* List;
	LinkedList* MapList;
	/// <summary>
	/// Prints a table with the huffman that correponds to a letter
	/// </summary>
	void PrintMapTable();
	/// <summary>
	/// Returns the 2 least frequent numbers
	/// </summary>
	/// <param name="min">Least frequent number </param>
	/// <param name="segundoMin">Second least frequent number</param>
	/// <returns>if i could at least get the least frequent</returns>
	bool GetTheLeastFrequentTwo(OcorrenciaLetras** min, OcorrenciaLetras** segundoMin);
	/// <summary>
	/// Set the nodes their huffman code
	/// </summary>
	/// <param name="root"></param>
	/// <param name="path"></param>
	void GetNodesCodes(BinaryTree* root, string path);
	/// <summary>
	/// Reads the files and creates the list with the char and their ocurrencie
	/// </summary>
	/// <returns></returns>
	bool ReadFile();
	/// <summary>
	/// Build the Huffman binary tree
	/// </summary>
	/// <returns></returns>
	bool BuildTree();
	/// <summary>
	/// Gte the huffman code for a given letter
	/// </summary>
	/// <param name="caracter"></param>
	/// <returns></returns>
	string GetCode(string caracter);
	/// <summary>
	/// Write the file with the new binary coce
	/// </summary>
	/// <returns></returns>
	bool WriteCodedFile();

};


