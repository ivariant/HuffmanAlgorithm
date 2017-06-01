#pragma once

namespace variant
{
	class HuffmanAlgorithm
	{
	public:
		HuffmanAlgorithm();
		~HuffmanAlgorithm();

		std::string packHuffmanAlgorithm(std::string str);
		std::map<char, std::vector<bool> > getTable();
		int packHuffmanAlgorithmFile(std::string fileName);

	private:

		std::vector<bool> huffmanCode;
		std::map<char, std::vector<bool> > huffmanTable;


		class NodeCountChar
		{
		public:
			int count;
			char symbol;
			NodeCountChar *left, *right;


			NodeCountChar()
			{

			}

			NodeCountChar(NodeCountChar* leftPointer, NodeCountChar* rightPointer)
			{
				left = leftPointer;
				right = rightPointer;
				count = leftPointer->count + rightPointer->count;
			}

		};


		struct iCompare
		{
			bool operator()(NodeCountChar* leftPointer, NodeCountChar* rightPointer) const
			{
				return leftPointer->count < rightPointer->count;
			}
		};


		void makeTable(NodeCountChar* root);
	};
}