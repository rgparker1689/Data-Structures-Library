#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "FibHeap.cpp"


int main(){
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
	Heap<int> T1, T2(B,10);
	
	T2.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9
	
	for(int i=0; i<10; i++) T1.insert(B[i]);
	
	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8
	
	cout << T2.peekKey() << endl;
	//Should output 1
	
	cout << T1.extractMin() << endl;
	//Should output 1
	
	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7
	
	
	FibHeap<string> X(A,10), Y;

	X.printKey();
	//Should output 
	//B1
	//J K
	//
	//B3
	//A E H I F C D B

	cout << X.extractMin() << endl;
	//Should output A
	
	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	
	X.insert("Z");
	X.insert("A");
	X.insert("P");

	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	//
	//B0
	//Z
	//
	//B0
	//A
	//
	//B0
	//P
	
	
	
	Y.insert("M"); 
	Y.insert("O");
	Y.insert("G");
	Y.insert("N");
	Y.insert("L");
	Y.insert("A");
	Y.extractMin();
		
	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N
	
	Y.merge(X);
	cout << Y.peekKey() << endl;
	//Should output A
	
	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N
	//
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	//
	//B0
	//Z
	//
	//B0
	//A
	//
	//B0
	//P

	Y.extractMin();

	Y.printKey();
    //Should output
	//B4
	//B C E H I F J K D G M O N P Z L

	FibHeap<string> copyAssign;

	copyAssign.insert("A");
	copyAssign.insert("D");
	copyAssign.insert("C");
	copyAssign.insert("Z");
	copyAssign.insert("F");
	copyAssign.insert("B");
	copyAssign.extractMin();

	// Should output
	// B0
	// B
	//
	// B2
	// C F Z D

	cout << endl;
	copyAssign.printKey();

	copyAssign = Y;

	// Y
	// B0
	// L
	//
	// B1
	// P Z
	//
	// B2
	// G M O N
	//
	// B3
	// C E H I F J K D

	Y.extractMin();
	cout << endl << "Y" << endl;
	Y.printKey();

	// copyAssign
	// same output as above B4, tests for a deep copy

	cout << endl << "copyAssign" << endl;
	copyAssign.printKey();

	Heap<float> h;
    FibHeap<float> fh;
    int size = 100001;
    float vals[size];

    cout << endl << "building heaps..." << endl;
    for (int i = 0; i < size; i++) {
        //cout << i << endl;
        float f = rand() / (float) RAND_MAX;
        vals[i] = f;
        h.insert(f);
        fh.insert(f);
    }

    //cout << "testing heap constructor variations..." << endl;
    Heap<float> h2(vals, size);
	Heap<float> h3(h2);
    FibHeap<float> fh2(vals, size);
	FibHeap<float> fh3(fh2);


	// Tests all constructor types, with the same set of values
	// Fails if they don't all match when extracting min
	// You want no output here

    cout << "extracting min(s)..." << endl;
    float floats[size];
    for (int x = 0; x < size; x++) {
        float m1 = h.extractMin();
        float m2 = h2.extractMin();
		float m3 = h3.extractMin();
        float m4 = fh.extractMin();
        float m5 = fh2.extractMin();
		float m6 = fh3.extractMin();
		cout<<"Got ALL"<<endl;
        floats[x] = m1;
		// || m3 != m4 || m4 != m5 || m5 != m6
		// m1 != m2 || m2 != m3
        if (m1 != m2 || m2 != m3 || m3 != m4 || m4 != m5 || m5 != m6) cout << "fails @x=" << x << endl;
    }

    for (int x = 1; x < size; x++) if (floats[x] < floats[x - 1]) cout << "mins not extracted in order" << endl;

    cout << "extractions complete, heaps empty" << endl;

	// From the FibHeap lab where we did several operations on this set
	// Feel free to check output with your own hand-drawn trees

    int ints[] = {6, 2, 10, 7, 5, 1, 11, 9, 3, 4, 8};
    FibHeap<int> fhInt(ints, 11);

	// B0
	// 8
	//
	// B1
	// 3 4
	//
	// B3
	// 1 2 7 10 6 9 11 5

    cout << "8.1" << endl;
    fhInt.printKey();
    cout << endl;

	// B1
	// 5 8
	//
	// B3
	// 2 3 9 11 4 7 10 6

    cout << "8.2" << endl;
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

	// B2
	// 6 7 10 22
	//
	// B3
	// 3 5 15 19 8 9 11 4

    cout << "8.3" << endl;
    fhInt.insert(15);
    fhInt.insert(19);
    fhInt.insert(22);
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

	// B0
	// 4
	//
	// B1
	// 9 11
	//
	// B3
	// 5 6 7 10 22 15 19 8

    cout << "8.4" << endl;
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

    size = 100002;
    FibHeap<int> merge1(ints, 11);
    FibHeap<int> merge2;

    for (int x = 0; x < size; x++) merge2.insert(rand());
    for (int _ = 0; _ < size; _++) merge2.extractMin();

    // merge2 should be empty now, thus merge1.merge(merge2) shouldn't change merge1
	// BEFORE
	// B0
	// 8
	//
	// B1
	// 3 4
	//
	// B3
	// 1 2 7 10 6 9 11 5
	// MERGED
	// B0
	// 8
	//
	// B1
	// 3 4
	//
	// B3
	// 1 2 7 10 6 9 11 5

	// B0
	// 4
	//
	// B1
	// 9 11
	//
	// B3
	// 5 6 7 10 22 15 19 8
	// CONSOLIDATED
	// B0
	// 5
	//
	// B2
	// 9 9 11 11        didn't really think about equal keys when I made this but it's not like
	//					it's gonna break your program, I just can't be bothered to change it rn
	// B4				you might have different output than this as a result
	// 2 5 6 7 10 22 15 19 8 3 4 8 4 7 10 6

    cout << "BEFORE" << endl;
    merge1.printKey();
    merge1.merge(fhInt);
    cout << "MERGED" << endl;
    merge1.printKey();
    cout << "CONSOLIDATED" << endl;
    merge1.extractMin();
    merge1.printKey();

	return 0;
}