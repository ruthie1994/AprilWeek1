////////////////////////////////////////////////////////////////////////////////////////////////
// File :			DTSLab8.cpp
// Author :			Rodney Stoeffler
// Created :		06.03.2008
// Last Modified :	01.25.2019
// Purpose :		Driver Program for the Bit Stream classes.
// Notes :			Property of Full Sail University, Data Structures Course.
//					DON'T CHANGE THIS FILE. change your code if something is not working
//					Program Output should match the Lab Document
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;
#include "BitStream.h"		// Include for provided BitStream header.

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// Return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char ** argv)
{
////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
//	_CrtSetBreakAlloc();

////////////////////////////////////////////////////////////////////////////////////////////////
// LAB 8
////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "**********************************************************************\n";
	cout << "**                              LAB 8:                              **\n";
	cout << "**********************************************************************\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 1 - BitOStream (No Header) test
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 1 ***\n";
	cout << "Writing a Sample Bit Stream (No Header)...\n";
	BitOStream out ("L8output1.bin");
	// an example bit sequence to write:
	// HEX:             35                ED           80 (because of pad)
	int seq[] = { 0,0,1,1,0,1,0,1 , 1,1,1,0,1,1,0,1 , 1,0 };
	// fiveBits = 00110, oneBit = 1, twoBits = 01, tenBits = 1110110110
	vector<int> fiveBits (5);  memcpy (&fiveBits[0],&seq[0],5*sizeof(int));  
	vector<int> oneBit (1);    memcpy (&oneBit[0],&seq[5],1*sizeof(int));
	vector<int> twoBits (2);   memcpy (&twoBits[0],&seq[6],2*sizeof(int));
	vector<int> tenBits (10);  memcpy (&tenBits[0],&seq[8],10*sizeof(int));
	// write the bit sequence.
	out << fiveBits;
	out << oneBit;
	out << twoBits;
	out << tenBits;
	out.close ();

	// test the contents of the file, to see what's inside!
	ifstream testOut1 ("L8output1.bin");
	while (true)
	{
		unsigned char ch;
		testOut1.read ((char *)&ch, 1);
		if (testOut1.eof ()) break;
		cout << hex << (int)ch << " ";
	}
	testOut1.close ();
	cout << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 2 - BitOStream (with header)
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 2 ***\n";
	cout << "Writing a Sample Bit Stream (WITH Header)...\n";
	char header[4] = "ABC"; // Hex 41, 42, 43
	BitOStream out2 ("L8output2.bin", header, 3);
	// write the bit sequence. (Hex 35)
	out2 << fiveBits;
	out2 << oneBit;
	out2 << twoBits;
	out2.close ();
	// test the contents of the file, to see what's inside!
	ifstream testOut2 ("L8output2.bin");
	while (true)
	{
		unsigned char ch;
		testOut2.read ((char *)&ch, 1);
		if (testOut2.eof ()) break;
		cout << hex << (int)ch << " ";
	}
	testOut2.close ();
	cout << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 3 - BitIStream (no header)
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 3 ***\n";
	cout << "Reading a Sample Bit Stream (No Header)...\n";
	BitIStream in1 ("L8input.bin");
	int cnt = 0;
	// show the file in binary (single bits).
	while (true)
	{
		int bit;
		in1 >> bit;
		if (in1.eof ()) break;
		cout << bit;
		cnt++;  
		if (cnt == 8)
		{   
			cout << " ";
			cnt = 0;
		}
	}
	in1.close ();
	cout << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 4 - BitIStream (with header)
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 4 ***\n";
	cout << "Reading a Sample Bit Stream (WITH Header)...\n";
	BitIStream in2 ("L8input.bin", header, 2);
	cnt = 0;
	// show the file in binary (single bits).
	while (true)
	{
		int bit;
		in2 >> bit;
		if (in2.eof ()) break;
		cout << bit;
		cnt++;
		if (cnt == 8)
		{   
			cout << " ";
			cnt = 0;
		}
	}
	in2.close ();
	cout << "\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// Complete
	////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}