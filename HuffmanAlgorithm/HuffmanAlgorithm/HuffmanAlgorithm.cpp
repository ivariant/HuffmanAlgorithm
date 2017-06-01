// HuffmanAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HuffmanAlgorithm.h"

namespace variant
{

		HuffmanAlgorithm::HuffmanAlgorithm()
		{

		}


		HuffmanAlgorithm::~HuffmanAlgorithm()
		{

		}


		void  HuffmanAlgorithm::makeTable(NodeCountChar* root)
		{
			if (root->left != nullptr)
			{
				huffmanCode.push_back(0);
				makeTable(root->left);
			}

			if (root->right != nullptr)
			{
				huffmanCode.push_back(1);
				makeTable(root->right);
			}

			if (root->symbol)
			{
				huffmanTable[root->symbol] = huffmanCode;
			}

			if (huffmanCode.size())
			{ 
				huffmanCode.pop_back();
			}
	
		}


		std::string HuffmanAlgorithm::packHuffmanAlgorithm(std::string str)
		{

			std::map<char, int> countChar;

			for (int i(0); i < str.length(); i++)
			{
				char c = str[i];
				countChar[c]++;
			}


			//for (auto it = countChar.begin(); it != countChar.end(); ++it)
			//{
			//	std::cout << it->first << ":" << it->second << "\n";
			//}

			std::list<NodeCountChar*> huffmanTree;

			for (auto it = countChar.begin(); it != countChar.end(); ++it)
			{
				NodeCountChar* nodeCountChar = new NodeCountChar();
				nodeCountChar->symbol = it->first;
				nodeCountChar->count = it->second;

				nodeCountChar->left = nodeCountChar->right = nullptr;

				huffmanTree.push_back(nodeCountChar);
			}


			while (huffmanTree.size() != 1)
			{
				huffmanTree.sort(iCompare());

				NodeCountChar* leftNodeCountChar = huffmanTree.front();
				huffmanTree.pop_front();

				NodeCountChar* rightNodeCountChar = huffmanTree.front();
				huffmanTree.pop_front();

				NodeCountChar* newNodeCountChar = new NodeCountChar(leftNodeCountChar, rightNodeCountChar);
				huffmanTree.push_back(newNodeCountChar);
			}

			makeTable(huffmanTree.front());

			std::string huffmanStr = "";

			for (int i(0); i < str.length(); i++)
			{
				std::vector<bool> huffmanCode  = huffmanTable[str[i]];

				for (int n(0); n < huffmanCode.size(); n++)
				{
					huffmanStr += (huffmanCode[n] + '0');
				}
			}
		

			return huffmanStr;
		}


		std::map<char, std::vector<bool> > HuffmanAlgorithm::getTable()
		{
			return huffmanTable;
		}

	
		int HuffmanAlgorithm::packHuffmanAlgorithmFile(std::string fileName)
		{
			
			std::ifstream f(fileName);

			if (f.fail())
			{
				return 0;
			}

			std::map<char, int> countChar;

			while (!f.eof())
			{
				char c;
				f >> c;
				countChar[c]++;
			}

			std::list<NodeCountChar*> huffmanTree;

			for (auto it = countChar.begin(); it != countChar.end(); ++it)
			{
				NodeCountChar* nodeCountChar = new NodeCountChar();
				nodeCountChar->symbol = it->first;
				nodeCountChar->count = it->second;

				nodeCountChar->left = nodeCountChar->right = nullptr;

				huffmanTree.push_back(nodeCountChar);
			}


			while (huffmanTree.size() != 1)
			{
				huffmanTree.sort(iCompare());

				NodeCountChar* leftNodeCountChar = huffmanTree.front();
				huffmanTree.pop_front();

				NodeCountChar* rightNodeCountChar = huffmanTree.front();
				huffmanTree.pop_front();

				NodeCountChar* newNodeCountChar = new NodeCountChar(leftNodeCountChar, rightNodeCountChar);
				huffmanTree.push_back(newNodeCountChar);
			}

			makeTable(huffmanTree.front());

			f.clear(); //Указатель в начало
			f.seekg(0);

			std::ofstream fPack("pack.bin");
			int count = 0;
			char buf = 0;

			while (!f.eof())
			{
				char charFile;
				f >> charFile; //Побитово

				std::vector<bool> huffmanCode = huffmanTable[charFile];

				for (int n(0); n < huffmanCode.size(); n++)
				{
					buf = buf | huffmanCode[n] << (7 - count);
					count++;
					if (count == 8)
					{
						fPack << buf; // Ложу байт
						count = 0;
						buf = 0;
					}
				}
			
			}

			f.close();
			fPack.close();
			return 1;
		}
}