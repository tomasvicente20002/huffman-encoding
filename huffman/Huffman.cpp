#include"Huffman.h"

/// <summary>
/// Returns true if the letter in value occurs more times then the valueToCompare
/// </summary>
/// <param name="value">value</param>
/// <param name="valueToCompare">valueToCompare</param>
/// <returns>true if the letter in value occurs more times then the valueToCompare</returns>
bool ComparaOcorrenciasLetra(const void* value, const void* valueToCompare)
{
	OcorrenciaLetras a = (*static_cast<const OcorrenciaLetras*>(value));
	OcorrenciaLetras b = (*static_cast<const OcorrenciaLetras*>(valueToCompare));
	return a.cnt > b.cnt;
}

/// <summary>
/// Prints a table with the huffman that correponds to a letter
/// </summary>
void Huffman::PrintMapTable()
{
	if (this->MapList != nullptr)
	{
		LinkedListNode* no = this->MapList->Head;
		MapValue* value = nullptr;

		while (no != nullptr)
		{
			value = (MapValue*)no->Value;
			printf("Caracter %s Valor %s\n", value->leter.c_str(), value->newValue.c_str());
			no = no->Next;
		}
		
	}
}

/// <summary>
/// Returns the 2 least frequent numbers
/// </summary>
/// <param name="min">Least frequent number </param>
/// <param name="segundoMin">Second least frequent number</param>
/// <returns>if i could at least get the least frequent</returns>
bool Huffman::GetTheLeastFrequentTwo(OcorrenciaLetras** min, OcorrenciaLetras** segundoMin)
{
	if (this->List == nullptr)
		return false;

	if (this->List->Head != nullptr)
	{
		*min = (OcorrenciaLetras*)this->List->Head->Value;

		if (this->List->Head->Next != nullptr)
			*segundoMin = (OcorrenciaLetras*)this->List->Head->Next->Value;

		return true;
	}
	else
		return false;

	return false;
}

/// <summary>
/// Set the nodes thei huffman code
/// </summary>
/// <param name="root"></param>
/// <param name="path"></param>
void Huffman::GetNodesCodes(BinaryTree* root, string path)
{
	if (root == nullptr)
		return;

	//If it does't have more childs when end the recursion and set their values
	if (root->IsLeaf())
	{
		MapValue* map = new MapValue();
		map->leter = root->path[0];
		map->newValue = path;
		this->MapList->Add(map);
	}
	else
	{
		//Call recursively the funciton until it gets to a leaf node

		//Left side adds a 0
		this->GetNodesCodes(root->left, path + "0");
		//Right side adds a 1
		this->GetNodesCodes(root->right, path + "1");
	}
}

/// <summary>
/// Reads the files and creates the list with the char and their ocurrencie
/// </summary>
/// <returns></returns>
bool Huffman::ReadFile()
{
	//Check if the list is empty
	if (this->List != nullptr)
		delete(this->List);

	this->List = new LinkedList();

	FILE* fp;
	char caracter = '\0';
	LinkedListNode* no;
	OcorrenciaLetras* letra;

	fopen_s(&fp, this->ReadPath.c_str(), "r");

	if (fp == nullptr)
	{
		perror("Error while opening the file.\n");
		return false;
	}


	//Reads the file
	while ((caracter = fgetc(fp)) != EOF)
	{
		string let = getString(caracter);
		//Check if it is already in the list
		no = this->List->GenericFind(&let, CompareVoidTypeString);

		//if it returns null whe nedd to add to the list
		if (no == nullptr)
		{
			letra = new OcorrenciaLetras();

			letra->letra = let;
			letra->cnt = 1;
			this->List->Add(letra);
		}
		else
		{
			//Already exist only encrements the nº of time that occurs
			letra = (OcorrenciaLetras*)no->Value;
			letra->cnt += 1;
		}
	}

	fclose(fp);

	return true;
}

/// <summary>
/// Build the Huffman binary tree
/// </summary>
/// <returns></returns>
bool Huffman::BuildTree()
{
	OcorrenciaLetras* min = nullptr;
	OcorrenciaLetras* segundoMin = nullptr;
	BinaryTree* root = nullptr;

	while (this->List->Head != nullptr && this->List->Head->Next != nullptr)
	{
		//always sort the list from least frequent to most frequent
		this->List->BoobbleShort(ComparaOcorrenciasLetra);
		root = new BinaryTree();

		//Obter o 2 minimos
		this->GetTheLeastFrequentTwo(&min, &segundoMin);

		//Left side gets the least frequente letter, a right the 2º
		root->left = min->no;
		root->right = segundoMin->no;

		if (root->left == nullptr)
		{
			root->left = new BinaryTree();
			root->left->parent = root;
			root->left->path = min->letra;
		}
		if (root->right == nullptr)
		{
			root->right = new BinaryTree();
			root->right->parent = root;
			root->right->path = segundoMin->letra;
		}

		//Concs the 2 string with their values
		root->path = root->left->path + root->right->path;

		//Sums their occurencie
		int somaOcorrencia = min->cnt;

		if (segundoMin != nullptr)
			somaOcorrencia += segundoMin->cnt;

		//The fisrt element now is trash becouse whe already have built the the tree with the 2 values,
		//And whe take the second node of the list o be the parent node of the sum of the left and right tree nodes
		if (this->List->Head->Next != nullptr)
		{
			this->List->Head = this->List->Head->Next;
		}

		min = (OcorrenciaLetras*)this->List->Head->Value;
		min->cnt = somaOcorrencia;
		min->no = root;
		min->letra = root->path;
	}

	this->Tree = root;

	return true;
}

/// <summary>
/// Gte the huffman code for a given letter
/// </summary>
/// <param name="caracter"></param>
/// <returns></returns>
string Huffman::GetCode(string caracter)
{
	if (this->MapList != nullptr)
	{
		LinkedListNode* no = this->MapList->Head;

		while (no != nullptr)
		{
			/// <summary>
			/// Check if the leteer is the same
			/// </summary>
			/// <param name="caracter"></param>
			/// <returns></returns>
			if (!CompareVoidTypeString(no->Value, &caracter))
			{
				MapValue* value = (MapValue*)no->Value;
				return value->newValue;
			}


			no = no->Next;
		}
	}

	return "";
}

/// <summary>
/// Write the file with the new binary coce
/// </summary>
/// <returns></returns>
bool Huffman::WriteCodedFile()
{
	char caracter;
	int num = 0;
	int cnt = 0;
	int nrOfCaracters = 0;
	int nrOfBytesWriten = 0;
	string carac;
	string newCode;
	FILE* fp, * fpWrite;
	fopen_s(&fp, this->ReadPath.c_str(), "r");
	fopen_s(&fpWrite, this->WritePath.c_str(), "wb+");

	if (!(fp && fpWrite))
		return false;

	while ((caracter = fgetc(fp)) != EOF)
	{
		nrOfCaracters += 1;
		carac = caracter;
		newCode = this->GetCode(carac);
		printf("%s", newCode.c_str());
		

		for (int idx = 0; idx < newCode.length(); idx++)
		{
			

			if(newCode[idx] == '1')			
				SetTheNBitTo1(&num, 8 - cnt - 1);

			if (cnt == 7)
			{
				fprintf(fpWrite, "%c", num);
				num = cnt = 0;
				nrOfBytesWriten += 1;
			}
			else
				cnt++;
		}
	}

	if (cnt > 0 && cnt <= 7)
	{
		fprintf(fpWrite, "%c", num);
		num = cnt = 0;
		nrOfBytesWriten += 1;
	}

	fclose(fp);
	fclose(fpWrite);
	printf("\n");
	printf("Nr of bits original %d\n", nrOfCaracters*8);
	printf("Nr of bits compressed %d\n", nrOfBytesWriten*8);
	printf("Compress ratio %d:%d", ((nrOfCaracters * 9) / 8), nrOfBytesWriten);
	return true;
}

/// <summary>
/// Encode the file
/// </summary>
/// <returns></returns>
bool Huffman::Encode()
{
	try
	{
		if (this->ReadFile() && this->BuildTree())
		{
			if (this->MapList != nullptr)
				delete(this->MapList);

			this->MapList = new LinkedList();

			this->GetNodesCodes(this->Tree, "");
			this->PrintMapTable();
			this->WriteCodedFile();
		}

		return true;
	}
	catch (...)
	{

	}

	return false;
}