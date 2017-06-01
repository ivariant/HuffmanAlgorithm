// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HuffmanAlgorithm.h"

int main()
{


	std::string str = "it is my striiiiing!!!!";


	//std::cout << packHuffmanAlgorithm(str);

	variant::HuffmanAlgorithm* huffmanAlgorithm = new variant::HuffmanAlgorithm();

	//std::cout << huffmanAlgorithm->packHuffmanAlgorithm(str) << "\n\n";
	//std::cout << huffmanAlgorithm->packHuffmanAlgorithm("gregregrewqrewr43243423ffwrt f");

	huffmanAlgorithm->packHuffmanAlgorithmFile("HuffmanAlgorithm1.log");
	//huffmanAlgorithm->unpackHuffmanAlgorithmFile("pack.bin");

	delete huffmanAlgorithm;
	std::cin >> str;
    return 0;
}

