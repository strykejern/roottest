#include "TFile.h"
#include "TTreeReader.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TTreeReaderValue.h"
#include "TTreeReaderArray.h"
#include <vector>
#include "A.h"
#include "B.h"

#define TREE_ENTRIES 10
#define LIST_ENTRIES 10

#define NUM_CONSTANT 14
#define MULTIPLIER_B_OBJECT 1
#define MULTIPLIER_VECTOR_B 1
#define MULTIPLIER_VECTOR_B_STAR 3
#define MULTIPLIER_VECTOR_STAR_B 2
#define MULTIPLIER_B_STAR 2
#define MULTIPLIER_B_ARRAY 4
#define MULTIPLIER_B_STAR_ARRAY 5
#define MULTIPLIER_B_CLONES_ARRAY 6
#define MYDOUBLEARRAY_SIZE 8
#define MYBOOLARRAYB_SIZE 12

void makeTree(const char* fileName = "HardTreeFile.root", Int_t startI = 1){
	TFile *myFile = new TFile(fileName, "RECREATE");
	TTree *myTree = new TTree("HardTree", "This is hard to read");

	A myObject0 (NUM_CONSTANT);

	struct {
		Float_t myFloatX;
		Float_t myFloatY;
		Int_t myIntN;
		Bool_t myBoolArrayB [MYBOOLARRAYB_SIZE];
		Double_t myDoubleArrayA [MYDOUBLEARRAY_SIZE];
	} myLeaves;

	myLeaves.myFloatX = 0.0;
	myLeaves.myFloatY = 0.0;
	myLeaves.myIntN = MYDOUBLEARRAY_SIZE;

	myTree->Branch("A0.",	"A", 	&myObject0,		32000, 0);
	myTree->Branch("A1.",	"A", 	&myObject0,		32000, 1);
	myTree->Branch("A99.",	"A", 	&myObject0,	32000, 99);
	myTree->Branch("A101.",	"A", 	&myObject0,	32000, 101);

	myTree->Branch("S0_num",			&myObject0.num,	32000, 0);
	myTree->Branch("S1_num",			&myObject0.num,	32000, 1);
	myTree->Branch("S99_num",			&myObject0.num,	32000, 99);
	myTree->Branch("S101_num",			&myObject0.num,	32000, 101);

	myTree->Branch("S0_vectorB",		&myObject0.vectorB,	32000, 0);
	myTree->Branch("S1_vectorB",		&myObject0.vectorB,	32000, 1);
	myTree->Branch("S99_vectorB",		&myObject0.vectorB,	32000, 99);
	// myTree->Branch("S101_vectorB",		&myObject0.vectorB,	32000, 101); // Breaks Fill()

	myTree->Branch("S0_vectorBStar",	&myObject0.vectorBStar,	32000, 0);
	myTree->Branch("S1_vectorBStar",	&myObject0.vectorBStar,	32000, 1);
	myTree->Branch("S99_vectorBStar",	&myObject0.vectorBStar,	32000, 99);
	// myTree->Branch("S101_vectorBStar",	&myObject0.vectorBStar,	32000, 101); // Breaks Fill()

	myTree->Branch("S0_vectorStarB",	&myObject0.vectorStarB,	32000, 0);
	myTree->Branch("S1_vectorStarB",	&myObject0.vectorStarB,	32000, 1);
	myTree->Branch("S99_vectorStarB",	&myObject0.vectorStarB,	32000, 99);
	// myTree->Branch("S101_vectorStarB",	&myObject0.vectorStarB,	32000, 101); // Breaks Fill()

	myTree->Branch("S0_BStar",			&myObject0.BStar,	32000, 0);
	myTree->Branch("S1_BStar",			&myObject0.BStar,	32000, 1);
	myTree->Branch("S99_BStar",			&myObject0.BStar,	32000, 99);
	myTree->Branch("S101_BStar",			&myObject0.BStar,	32000, 101);

	// myTree->Branch("S0_BArray[12]",		"B[12]",		&myObject0.BArray,	32000, 0); // Will not get made
	// myTree->Branch(199_BArray[12]",	"B[12]",		&myObject0.BArray,	32000, 99); // Will not get made
	// myTree->Branch("S99_BArray[12]",	"B[12]",		&myObject0.BArray,	32000, 99); // Will not get made

	// myTree->Branch("S0_BStarArray",		&myObject0.BStarArray,	32000, 0); // No way of specifying an array
	// myTree->Branch(199_BStarArray",	&myObject0.BStarArray,	32000, 99); // No way of specifying an array
	// myTree->Branch("S99_BStarArray",	&myObject0.BStarArray,	32000, 99); // No way of specifying an array

	myTree->Branch("S0_BObject.",		&myObject0.BObject,	32000, 0);
	myTree->Branch("S1_BObject.",		&myObject0.BObject,	32000, 1);
	myTree->Branch("S99_BObject.",		&myObject0.BObject,	32000, 99);
	myTree->Branch("S101_BObject.",		&myObject0.BObject,	32000, 101);

	myTree->Branch("S0_BClonesArray",	&myObject0.BClonesArray,	32000, 0);
	myTree->Branch("S1_BClonesArray",	&myObject0.BClonesArray,	32000, 1);
	myTree->Branch("S99_BClonesArray",	&myObject0.BClonesArray,	32000, 99);
	myTree->Branch("S101_BClonesArray",	&myObject0.BClonesArray,	32000, 101);

	myTree->Branch("MyLeafList",		&myLeaves,	"x:y/F:n/I:b[12]/O:a[n]/D");


	for (int i = startI; i < TREE_ENTRIES + startI; ++i){
		printf("\nEntry %i\n\n", i);

		// Clear old values
		myObject0.ResetVectorB();

		printf("Setting BObject\n");
		myObject0.BObject.dummy = i;

		for (int j = 0; j < LIST_ENTRIES; ++j){
			// Vector of objects
			B obj (i*j);
			printf("Adding %i to vectorB\n", i*j);
			myObject0.AddToVectorB(obj);

			obj.dummy *= 2;
			// Hangs makeTree
			printf("Adding %i to vectorStarB\n",  obj.dummy);
			myObject0.AddToVectorStarB(obj);

			// Vector of pointers
			printf("Adding %i to vectorBStar\n", i*j*2);
			B *ptr = new B(i*j*3);
			myObject0.AddToVectorBStar(ptr);
		}

		printf("Setting BStar\n");
		B *objPtr = new B(i*2);
		myObject0.SetBStar(objPtr);

		printf("Filling BArray\n");
		B *myArray = new B[12];
		for (int j = 0; j < 12; ++j){
			myArray[j].dummy = i * j * 4;
		}
		myObject0.FillBArray(myArray);
		delete [] myArray;

		printf("Filling BStarArray\n");
		for (int j = 0; j < NUM_CONSTANT; ++j){
			myObject0.BStarArray[j] = i*j*5;
		}

		printf("Filling BClonesArray\n");
		for (int j = 0; j < LIST_ENTRIES; ++j ){
			((B*)myObject0.BClonesArray.New(j))->dummy = i*j*6;
		}

		printf("Filling leaflist\n");
		myLeaves.myFloatX = (Float_t)i;
		myLeaves.myFloatY = (Float_t)i / 10.0f;
		for (int j = 0; j < MYDOUBLEARRAY_SIZE; ++j){
			myLeaves.myDoubleArrayA[j] = myLeaves.myFloatY * j;
		}
		for (int j = 0; j < MYBOOLARRAYB_SIZE; ++j){
			//myLeaves.myBoolArrayB[j] = (i + (i * j)) % 2;
			myLeaves.myBoolArrayB[j] = j % 2;
			//myLeaves.myBoolArrayB[j] = true;
		}

		printf("Filling tree\n");
		myTree->Fill();

		myObject0.ResetVectorStarB();

		myObject0.vectorBStar.clear();

		printf("Entry created\n");
	}
	printf("Tree created\n");

	myFile->Write();
}

void readNum(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "num";

	TTreeReaderValue<Int_t> myNum (myTreeReader, finalBranchName);

	// Bool_t success = !myNum.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && *myNum != NUM_CONSTANT) success = false;
		if (printOut) printf("Num: %i\n", *myNum);
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBObject(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BObject";

	TTreeReaderValue<B> myBObject (myTreeReader, finalBranchName);

	// Bool_t success = !myBObject.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && myBObject->dummy != i * MULTIPLIER_B_OBJECT) success = false;
		if (printOut) printf("Dummy: %i\n", myBObject->dummy);
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBObjectBranch(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BObject.";

	TTreeReaderValue<B> myBObject (myTreeReader, finalBranchName);

	// Bool_t success = !myBObject.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && myBObject->dummy != i * MULTIPLIER_B_OBJECT) success = false;
		if (printOut) printf("Dummy: %i\n", myBObject->dummy);
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBObjectDummy(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BObject.dummy";

	TTreeReaderValue<Int_t> myDummy (myTreeReader, finalBranchName);

	// Bool_t success = !myDummy.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && *myDummy != i * MULTIPLIER_B_OBJECT) success = false;
		if (printOut) printf("Dummy: %i\n", *myDummy);
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBStar(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BStar";

	TTreeReaderValue<B> myBStar (myTreeReader, finalBranchName);

	// Bool_t success = !myBStar.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && myBStar->dummy != i * MULTIPLIER_B_STAR) success = false;
		if (printOut) printf("Dummy: %i\n", myBStar->dummy);
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorBValue(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorB";

	TTreeReaderValue<std::vector<B> > myVectorB (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorB.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorB dummies:");

		for (int j = 0; j < LIST_ENTRIES; ++j){
			if (testValues && myVectorB->at(j).dummy != i * j * MULTIPLIER_VECTOR_B) success = false;
			if (printOut) printf(" %i", myVectorB->at(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorStarBValue(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorStarB";

	TTreeReaderValue<std::vector<B> > myVectorStarB (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorStarB.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorB dummies(%lu):", myVectorStarB->size());

		for (int j = 0; j < LIST_ENTRIES; ++j){
			if (testValues && myVectorStarB->at(j).dummy != i * j * MULTIPLIER_VECTOR_STAR_B) success = false;
			if (printOut) printf(" %i", myVectorStarB->at(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorStarBArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorStarB";

	TTreeReaderArray<B> myVectorStarB (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorStarB.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorB dummies(%lu):", myVectorStarB.GetSize());

		for (int j = 0; j < LIST_ENTRIES; ++j){
			if (testValues && myVectorStarB.At(j).dummy != i * j * MULTIPLIER_VECTOR_STAR_B) success = false;
			if (printOut) printf(" %i", myVectorStarB.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorBArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorB";

	TTreeReaderArray<B> myVectorB (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorB.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorB dummies(%lu):", myVectorB.GetSize());

		for (int j = 0; j < LIST_ENTRIES && j < (int)myVectorB.GetSize(); ++j){
			if (testValues && myVectorB.At(j).dummy != i * j * MULTIPLIER_VECTOR_B) success = false;
			if (printOut) printf(" %i", myVectorB.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BArray[12]";

	TTreeReaderArray<B> myBArray (myTreeReader, finalBranchName);

	// Bool_t success = !myBArray.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("BArray dummies(%lu):", myBArray.GetSize());

		for (int j = 0; j < LIST_ENTRIES; ++j){
			if (testValues && myBArray.At(j).dummy != i * j * MULTIPLIER_B_ARRAY) success = false;
			if (printOut) printf(" %i", myBArray.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBStarArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BStarArray";

	TTreeReaderArray<B> myBStarArray (myTreeReader, finalBranchName);

	// Bool_t success = !myBStarArray.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("BStarArray dummies(%lu):", myBStarArray.GetSize());

		for (int j = 0; j < (int)myBStarArray.GetSize(); ++j){
			if (testValues && myBStarArray.At(j).dummy != i * j * MULTIPLIER_B_STAR_ARRAY) success = false;
			if (printOut) printf(" %i", myBStarArray.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorBStarValue(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorBStar";

	TTreeReaderValue<std::vector<B*> > myVectorBStar (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorBStar.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorBStar dummies(%lu):", myVectorBStar->size());

		for (int j = 0; j < LIST_ENTRIES && j < (int)myVectorBStar->size(); ++j){
			if (testValues && myVectorBStar->at(j)->dummy != i * j * MULTIPLIER_VECTOR_B_STAR) success = false;
			if (printOut) printf(" %i", myVectorBStar->at(j)->dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorBStarArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorBStar";

	TTreeReaderArray<B> myVectorBStar (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorBStar.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorBStar dummies(%lu):", myVectorBStar.GetSize());

		for (int j = 0; j < LIST_ENTRIES && (int)myVectorBStar.GetSize(); ++j){
			if (testValues && myVectorBStar.At(j).dummy != i * j * MULTIPLIER_VECTOR_B_STAR) success = false;
			if (printOut) printf(" %i", myVectorBStar.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBClonesArrayValue(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BClonesArray";

	TTreeReaderValue<TClonesArray> myBClonesArray (myTreeReader, finalBranchName);

	// Bool_t success = !myBClonesArray.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("BClonesArray dummies(%i):", myBClonesArray->GetSize());

		for (int j = 0; j < LIST_ENTRIES && j < myBClonesArray->GetSize(); ++j){
			if (testValues && ((B*)myBClonesArray->At(j))->dummy != i * j * MULTIPLIER_B_CLONES_ARRAY) success = false;
			if (printOut) printf(" %i", ((B*)myBClonesArray->At(j))->dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBClonesArrayArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BClonesArray";

	TTreeReaderArray<B> myBClonesArray (myTreeReader, finalBranchName);

	// Bool_t success = !myBClonesArray.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("BClonesArray dummies(%lu):", myBClonesArray.GetSize());

		for (int j = 0; j < LIST_ENTRIES && j < (int)myBClonesArray.GetSize(); ++j){
			if (testValues && myBClonesArray.At(j).dummy != i * j * MULTIPLIER_B_CLONES_ARRAY) success = false;
			if (printOut) printf(" %i", myBClonesArray.At(j).dummy);
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readVectorBDummyArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "vectorB.dummy";

	TTreeReaderArray<Int_t> myVectorBDummyArray (myTreeReader, finalBranchName);

	// Bool_t success = !myVectorBDummyArray.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("vectorB.dummies(%lu):", myVectorBDummyArray.GetSize());

		for (int j = 0; j < LIST_ENTRIES && j < (int)myVectorBDummyArray.GetSize(); ++j){
			if (testValues && myVectorBDummyArray.At(j) != i * j * MULTIPLIER_VECTOR_B) success = false;
			if (printOut) printf(" %i", myVectorBDummyArray.At(j));
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readBClonesArrayDummyArray(const char* branchName = "A99.", Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString finalBranchName = branchName;
	finalBranchName += "BClonesArray.dummy";

	TTreeReaderArray<Int_t> myBClonesArrayDummy (myTreeReader, finalBranchName);

	// Bool_t success = !myBClonesArrayDummy.GetSetupStatus();
	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("BClonesArray.dummies(%lu):", myBClonesArrayDummy.GetSize());

		for (int j = 0; j < LIST_ENTRIES && j < (int)myBClonesArrayDummy.GetSize(); ++j){
			if (testValues && myBClonesArrayDummy.At(j) != i * j * MULTIPLIER_B_CLONES_ARRAY) success = false;
			if (printOut) printf(" %i", myBClonesArrayDummy.At(j));
		}

		if (printOut) printf("\n");
	}
	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readLeafFloatX(Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString branchName = "MyLeafList.x";

	TTreeReaderValue<Float_t> myFloat (myTreeReader, branchName);

	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && *myFloat - (Float_t)i > 0.0001f) success = false;
		if (printOut) printf("MyLeafList.x: %f\n", *myFloat);
	}

	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readLeafFloatY(Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString branchName = "MyLeafList.y";

	TTreeReaderValue<Float_t> myFloat (myTreeReader, branchName);

	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && *myFloat - ((Float_t)i / 10.0f) > 0.0001f) success = false;
		if (printOut) printf("MyLeafList.y: %f\n", *myFloat);
	}

	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readLeafIntN(Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString branchName = "MyLeafList.n";

	TTreeReaderValue<Int_t> myInt (myTreeReader, branchName);

	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (testValues && *myInt != MYDOUBLEARRAY_SIZE) success = false;
		if (printOut) printf("MyLeafList.n: %i\n", *myInt);
	}

	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readLeafDoubleAArray(Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString branchName = "MyLeafList.a";

	TTreeReaderArray<Double_t> myDoubles (myTreeReader, branchName);

	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("MyLeafList.a(%lu):", myDoubles.GetSize());

		for (size_t j = 0; j < myDoubles.GetSize() && j < 10; ++j){
			if (testValues && fabs(myDoubles.At(j) - (i * j) / 10.0f) > 0.0001f) success = false;
			if (printOut) printf(" %f", myDoubles.At(j));
		}

		if (printOut) printf("\n");
	}

	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readLeafBoolBArray(Bool_t printOut = true, Bool_t testValues = false, const char* fileName = "HardTreeFile.root"){
	TFile::Open(fileName);
	TTreeReader myTreeReader ("HardTree");

	TString branchName = "MyLeafList.b";

	TTreeReaderArray<Bool_t> myBools (myTreeReader, branchName);

	Bool_t success = true;
	Bool_t read = false;
	for (int i = 1; myTreeReader.SetNextEntry(); ++i){
		read = true;
		if (printOut) printf("MyLeafList.b(%lu):", myBools.GetSize());

		for (size_t j = 0; j < myBools.GetSize() && j < 10; ++j){
			if (testValues && myBools.At(j) != j % 2) success = false;
			if (printOut) printf(" %s", myBools.At(j) ? "true" : "false" );
		}

		if (printOut) printf("\n");
	}

	if (testValues) printf("%s\n", success && read ? "Success!" : "Failure");
}

void readTree(const char* fileName = "HardTreeFile.root"){
	TFile *myFile = TFile::Open(fileName);
	TTree *myTree = (TTree*)myFile->Get("HardTree");
	myTree->Print();
	
	for (int i = 0; i < 10 && i < myTree->GetEntries(); ++i){
		myTree->Show(i);
	}

	myFile->Close();
}


void output(Bool_t printAll = false, Bool_t testAll = true, const char* fileName = "HardTreeFile.root"){
	printf("A1: readNum(): ------------------------------ %s", printAll ? "\n": ""); readNum(					"A1.", printAll, testAll, fileName);
	printf("A1: readBObject(): -------------------------- %s", printAll ? "\n": ""); readBObject(				"A1.", printAll, testAll, fileName);
	printf("A1: readBStar(): ---------------------------- %s", printAll ? "\n": ""); readBStar(					"A1.", printAll, testAll, fileName);
	printf("A1: readVectorBValue(): --------------------- %s", printAll ? "\n": ""); readVectorBValue(			"A1.", printAll, testAll, fileName);
	printf("A1: readVectorStarBValue(): ----------------- %s", printAll ? "\n": ""); readVectorStarBValue(		"A1.", printAll, testAll, fileName);
	printf("A1: readVectorStarBArray(): ----------------- %s", printAll ? "\n": ""); readVectorStarBArray(		"A1.", printAll, testAll, fileName);
	printf("A1: readVectorBArray(): --------------------- %s", printAll ? "\n": ""); readVectorBArray(			"A1.", printAll, testAll, fileName);
	printf("A1: readBArray(): --------------------------- %s", printAll ? "\n": ""); readBArray(				"A1.", printAll, testAll, fileName);
	printf("A1: readBStarArray(): ----------------------- %s", printAll ? "\n": ""); readBStarArray(			"A1.", printAll, testAll, fileName);
	printf("A1: readVectorBStarValue(): ----------------- %s", printAll ? "\n": ""); readVectorBStarValue(		"A1.", printAll, testAll, fileName);
	printf("A1: readVectorBStarArray(): ----------------- %s", printAll ? "\n": ""); readVectorBStarArray(		"A1.", printAll, testAll, fileName);
	printf("A1: readBClonesArrayValue(): ---------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"A1.", printAll, testAll, fileName);
	printf("A1: readBClonesArrayArray(): ---------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"A1.", printAll, testAll, fileName);


	printf("A99: readNum(): ----------------------------- %s", printAll ? "\n": ""); readNum(					"A99.", printAll, testAll, fileName);
	printf("A99: readBObject(): ------------------------- %s", printAll ? "\n": ""); readBObject(				"A99.", printAll, testAll, fileName);
	printf("A99: readBObjectDummy(): -------------------- %s", printAll ? "\n": ""); readBObjectDummy(			"A99.", printAll, testAll, fileName);
	printf("A99: readBStar(): --------------------------- %s", printAll ? "\n": ""); readBStar(					"A99.", printAll, testAll, fileName);
	printf("A99: readVectorBValue(): -------------------- %s", printAll ? "\n": ""); readVectorBValue(			"A99.", printAll, testAll, fileName);
	printf("A99: readVectorStarBValue(): ---------------- %s", printAll ? "\n": ""); readVectorStarBValue(		"A99.", printAll, testAll, fileName);
	printf("A99: readVectorStarBArray(): ---------------- %s", printAll ? "\n": ""); readVectorStarBArray(		"A99.", printAll, testAll, fileName);
	printf("A99: readVectorBArray(): -------------------- %s", printAll ? "\n": ""); readVectorBArray(			"A99.", printAll, testAll, fileName);
	printf("A99: readBArray(): -------------------------- %s", printAll ? "\n": ""); readBArray(				"A99.", printAll, testAll, fileName);
	printf("A99: readBStarArray(): ---------------------- %s", printAll ? "\n": ""); readBStarArray(			"A99.", printAll, testAll, fileName);
	printf("A99: readVectorBStarValue(): ---------------- %s", printAll ? "\n": ""); readVectorBStarValue(		"A99.", printAll, testAll, fileName);
	printf("A99: readVectorBStarArray(): ---------------- %s", printAll ? "\n": ""); readVectorBStarArray(		"A99.", printAll, testAll, fileName);
	printf("A99: readBClonesArrayValue(): --------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"A99.", printAll, testAll, fileName);
	printf("A99: readBClonesArrayArray(): --------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"A99.", printAll, testAll, fileName);
	printf("A99: readVectorBDummyArray(): --------------- %s", printAll ? "\n": ""); readVectorBDummyArray(		"A99.", printAll, testAll, fileName);
	printf("A99: readBClonesArrayDummyArray(): ---------- %s", printAll ? "\n": ""); readBClonesArrayDummyArray("A99.", printAll, testAll, fileName);
	//printf("readAObject(): ------------------------ %s", printAll ? "\n": ""); readAObject();


	printf("A101: readNum(): ---------------------------- %s", printAll ? "\n": ""); readNum(					"A101.", printAll, testAll, fileName);
	printf("A101: readBObject(): ------------------------ %s", printAll ? "\n": ""); readBObject(				"A101.", printAll, testAll, fileName);
	printf("A101: readBStar(): -------------------------- %s", printAll ? "\n": ""); readBStar(					"A101.", printAll, testAll, fileName);
	printf("A101: readVectorBValue(): ------------------- %s", printAll ? "\n": ""); readVectorBValue(			"A101.", printAll, testAll, fileName);
	printf("A101: readVectorStarBValue(): --------------- %s", printAll ? "\n": ""); readVectorStarBValue(		"A101.", printAll, testAll, fileName);
	printf("A101: readVectorStarBArray(): --------------- %s", printAll ? "\n": ""); readVectorStarBArray(		"A101.", printAll, testAll, fileName);
	printf("A101: readVectorBArray(): ------------------- %s", printAll ? "\n": ""); readVectorBArray(			"A101.", printAll, testAll, fileName);
	printf("A101: readBArray(): ------------------------- %s", printAll ? "\n": ""); readBArray(				"A101.", printAll, testAll, fileName);
	printf("A101: readBStarArray(): --------------------- %s", printAll ? "\n": ""); readBStarArray(			"A101.", printAll, testAll, fileName);
	//printf("A101: readVectorBStarValue(): --------------- %s", printAll ? "\n": ""); readVectorBStarValue(			"A101.", printAll, testAll, fileName); // Segfault
	//printf("A101: readVectorBStarArray(): --------------- %s", printAll ? "\n": ""); readVectorBStarArray(			"A101.", printAll, testAll, fileName); // Segfault
	printf("A101: readBClonesArrayValue(): -------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"A101.", printAll, testAll, fileName);
	printf("A101: readBClonesArrayArray(): -------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"A101.", printAll, testAll, fileName);


	// printf("S0_: readNum(): ----------------------------- %s", printAll ? "\n": ""); readNum(						"S0_", printAll, testAll, fileName); // Leaflist
	printf("S0_: readBObject(): ------------------------- %s", printAll ? "\n": ""); readBObjectBranch(					"S0_", printAll, testAll, fileName);
	// printf("S0_: readBObjectDummy(): -------------------- %s", printAll ? "\n": ""); readBObjectDummy(				"S0_", printAll, testAll, fileName); // Branch not created
	printf("S0_: readBStar(): --------------------------- %s", printAll ? "\n": ""); readBStar(					"S0_", printAll, testAll, fileName);
	printf("S0_: readVectorBValue(): -------------------- %s", printAll ? "\n": ""); readVectorBValue(				"S0_", printAll, testAll, fileName);
	printf("S0_: readVectorStarBValue(): ---------------- %s", printAll ? "\n": ""); readVectorStarBValue(			"S0_", printAll, testAll, fileName);
	printf("S0_: readVectorStarBArray(): ---------------- %s", printAll ? "\n": ""); readVectorStarBArray(			"S0_", printAll, testAll, fileName);
	printf("S0_: readVectorBArray(): -------------------- %s", printAll ? "\n": ""); readVectorBArray(				"S0_", printAll, testAll, fileName);
	// printf("S0_: readBArray(): -------------------------- %s", printAll ? "\n": ""); readBArray(					"S0_", printAll, testAll, fileName); // Branch not created
	// printf("S0_: readBStarArray(): ---------------------- %s", printAll ? "\n": ""); readBStarArray(				"S0_", printAll, testAll, fileName); // Branch not created
	printf("S0_: readVectorBStarValue(): ---------------- %s", printAll ? "\n": ""); readVectorBStarValue(			"S0_", printAll, testAll, fileName);
	printf("S0_: readVectorBStarArray(): ---------------- %s", printAll ? "\n": ""); readVectorBStarArray(			"S0_", printAll, testAll, fileName);
	// printf("S0_: readBClonesArrayValue(): --------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"S0_", printAll, testAll, fileName); // TBranchProxy->Read() fails
	// printf("S0_: readBClonesArrayArray(): --------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"S0_", printAll, testAll, fileName); // TBranchProxy->Read() fails
	// printf("S0_: readVectorBDummyArray(): --------------- %s", printAll ? "\n": ""); readVectorBDummyArray(		"S0_", printAll, testAll, fileName); // Branch not found
	// printf("S0_: readBClonesArrayDummyArray(): ---------- %s", printAll ? "\n": ""); readBClonesArrayDummyArray(	"S0_", printAll, testAll, fileName); // Branch not found


	// printf("S1_: readNum(): ----------------------------- %s", printAll ? "\n": ""); readNum(						"S1_", printAll, testAll, fileName); // Leaflist
	printf("S1_: readBObject(): ------------------------- %s", printAll ? "\n": ""); readBObjectBranch(					"S1_", printAll, testAll, fileName);
	printf("S1_: readBObjectDummy(): -------------------- %s", printAll ? "\n": ""); readBObjectDummy(				"S1_", printAll, testAll, fileName);
	printf("S1_: readBStar(): --------------------------- %s", printAll ? "\n": ""); readBStar(					"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorBValue(): -------------------- %s", printAll ? "\n": ""); readVectorBValue(				"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorStarBValue(): ---------------- %s", printAll ? "\n": ""); readVectorStarBValue(			"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorStarBArray(): ---------------- %s", printAll ? "\n": ""); readVectorStarBArray(			"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorBArray(): -------------------- %s", printAll ? "\n": ""); readVectorBArray(				"S1_", printAll, testAll, fileName);
	// printf("S1_: readBArray(): -------------------------- %s", printAll ? "\n": ""); readBArray(					"S1_", printAll, testAll, fileName); // Branch not created
	// printf("S1_: readBStarArray(): ---------------------- %s", printAll ? "\n": ""); readBStarArray(				"S1_", printAll, testAll, fileName); // Branch not created
	printf("S1_: readVectorBStarValue(): ---------------- %s", printAll ? "\n": ""); readVectorBStarValue(			"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorBStarArray(): ---------------- %s", printAll ? "\n": ""); readVectorBStarArray(			"S1_", printAll, testAll, fileName);
	printf("S1_: readBClonesArrayValue(): --------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"S1_", printAll, testAll, fileName);
	printf("S1_: readBClonesArrayArray(): --------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"S1_", printAll, testAll, fileName);
	printf("S1_: readVectorBDummyArray(): --------------- %s", printAll ? "\n": ""); readVectorBDummyArray(		"S1_", printAll, testAll, fileName);
	printf("S1_: readBClonesArrayDummyArray(): ---------- %s", printAll ? "\n": ""); readBClonesArrayDummyArray(	"S1_", printAll, testAll, fileName);


	// printf("S99_: readNum(): ---------------------------- %s", printAll ? "\n": ""); readNum(						"S99_", printAll, testAll, fileName); // Leaflist
	printf("S99_: readBObject(): ------------------------ %s", printAll ? "\n": ""); readBObjectBranch(					"S99_", printAll, testAll, fileName);
	printf("S99_: readBObjectDummy(): ------------------- %s", printAll ? "\n": ""); readBObjectDummy(				"S99_", printAll, testAll, fileName);
	printf("S99_: readBStar(): -------------------------- %s", printAll ? "\n": ""); readBStar(					"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorBValue(): ------------------- %s", printAll ? "\n": ""); readVectorBValue(				"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorStarBValue(): --------------- %s", printAll ? "\n": ""); readVectorStarBValue(			"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorStarBArray(): --------------- %s", printAll ? "\n": ""); readVectorStarBArray(			"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorBArray(): ------------------- %s", printAll ? "\n": ""); readVectorBArray(				"S99_", printAll, testAll, fileName);
	// printf("S99_: readBArray(): ------------------------- %s", printAll ? "\n": ""); readBArray(					"S99_", printAll, testAll, fileName); // Branch not created
	// printf("S99_: readBStarArray(): --------------------- %s", printAll ? "\n": ""); readBStarArray(				"S99_", printAll, testAll, fileName); // Branch not created
	printf("S99_: readVectorBStarValue(): --------------- %s", printAll ? "\n": ""); readVectorBStarValue(			"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorBStarArray(): --------------- %s", printAll ? "\n": ""); readVectorBStarArray(			"S99_", printAll, testAll, fileName);
	printf("S99_: readBClonesArrayValue(): -------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"S99_", printAll, testAll, fileName);
	printf("S99_: readBClonesArrayArray(): -------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"S99_", printAll, testAll, fileName);
	printf("S99_: readVectorBDummyArray(): -------------- %s", printAll ? "\n": ""); readVectorBDummyArray(		"S99_", printAll, testAll, fileName);
	printf("S99_: readBClonesArrayDummyArray(): --------- %s", printAll ? "\n": ""); readBClonesArrayDummyArray(	"S99_", printAll, testAll, fileName);

	// printf("S101_: readNum(): --------------------------- %s", printAll ? "\n": ""); readNum(						"S101_", printAll, testAll, fileName); // Leaflist
	printf("S101_: readBObject(): ----------------------- %s", printAll ? "\n": ""); readBObjectBranch(					"S101_", printAll, testAll, fileName);
	printf("S101_: readBObjectDummy(): ------------------ %s", printAll ? "\n": ""); readBObjectDummy(				"S101_", printAll, testAll, fileName);
	printf("S101_: readBStar(): ------------------------- %s", printAll ? "\n": ""); readBStar(					"S101_", printAll, testAll, fileName);
	// printf("S101_: readVectorBValue(): ------------------ %s", printAll ? "\n": ""); readVectorBValue(				"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readVectorStarBValue(): -------------- %s", printAll ? "\n": ""); readVectorStarBValue(			"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readVectorStarBArray(): -------------- %s", printAll ? "\n": ""); readVectorStarBArray(			"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readVectorBArray(): ------------------ %s", printAll ? "\n": ""); readVectorBArray(				"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readBArray(): ------------------------ %s", printAll ? "\n": ""); readBArray(					"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readBStarArray(): -------------------- %s", printAll ? "\n": ""); readBStarArray(				"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readVectorBStarValue(): -------------- %s", printAll ? "\n": ""); readVectorBStarValue(			"S101_", printAll, testAll, fileName); // Branch not created
	// printf("S101_: readVectorBStarArray(): -------------- %s", printAll ? "\n": ""); readVectorBStarArray(			"S101_", printAll, testAll, fileName); // Branch not created
	printf("S101_: readBClonesArrayValue(): ------------- %s", printAll ? "\n": ""); readBClonesArrayValue(		"S101_", printAll, testAll, fileName);
	printf("S101_: readBClonesArrayArray(): ------------- %s", printAll ? "\n": ""); readBClonesArrayArray(		"S101_", printAll, testAll, fileName);
	// printf("S101_: readVectorBDummyArray(): ------------- %s", printAll ? "\n": ""); readVectorBDummyArray(		"S101_", printAll, testAll, fileName);  // Branch not created
	printf("S101_: readBClonesArrayDummyArray(): -------- %s", printAll ? "\n": ""); readBClonesArrayDummyArray(	"S101_", printAll, testAll, fileName);

	printf("readLeafFloatX(): --------------------------- %s", printAll ? "\n": ""); readLeafFloatX(		printAll, testAll, fileName);
	printf("readLeafFloatY(): --------------------------- %s", printAll ? "\n": ""); readLeafFloatY(		printAll, testAll, fileName);
	printf("readLeafIntN(): ----------------------------- %s", printAll ? "\n": ""); readLeafIntN(			printAll, testAll, fileName);
	printf("readLeafDoubleAArray(): --------------------- %s", printAll ? "\n": ""); readLeafDoubleAArray(	printAll, testAll, fileName);
	printf("readLeafBoolBArray(): ----------------------- %s", printAll ? "\n": ""); readLeafBoolBArray(	printAll, testAll, fileName);
}

void testAll(){
	output(false, true);
}

void printAll(){
	output(true, true);
}

void testChain(){
	output(false, true, "HardChainFile.root");
}

void printChain(){
	output(true, true, "HardChainFile.root");
}
