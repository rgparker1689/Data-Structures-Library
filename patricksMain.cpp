#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "FibHeap.cpp"


int main(){
	int A[10] = {54, 48, 69, 31, 58, 47, 74, 21, 30, 84};
	int B[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    FibHeap<int> T1(A, 10), T3(B, 10);
	FibHeap<int> T2 = T1;

	cout << "T1 (Original):\n";
	T1.printKey();
	cout << "-----------------------------\n\n";

	cout << "T2 (Tests copy constructor; should = T1):\n";
	T2.printKey();
	cout << "-----------------------------\n\n";

	cout << "Copy assignment operator calling next. Remember that if there is already data in the FibHeap, you must clear it before the copy.\n";
	T2 = T3;

	cout << "T2 (Tests copy assignment operator):\n";
	T2.printKey();
	cout << "-----------------------------\n\n";

	for (int i = 0; i < 10; i++){
		int j = T2.extractMin();
		if (j == i + 1) cout << "ExtractMin Successful\n";
		else cout << "ExtractMin failed. Returned " << j << " instead of " << i << '\n';
	}

	cout << "The next line is going to call extractMin on what should be an empty heap. Dixon said we wouldn't be tested on this but I figured that we might as well.\n";

	cout << "Great! You didn't segmentation fault. It doesn't matter what it returned.\n---------------------------------------------------------------------\n";

	for (int i = 0; i < 43000; i++){
		T2.insert(i);
	}
	T2.extractMin();
	for (int i = 43001; i < 60000; i++){
		T2.insert(i);
	}
	T2.extractMin();

	FibHeap<int> T4(B, 10);

	cout << "T1:\n";
	T1.printKey();
	cout << "-----------------------------\n\n";

	cout << "T4:\n";
	T4.printKey();
	cout << "-----------------------------\n\n";
	
	T1.merge(T4);

	cout << "T1 (After merge):\n";
	T1.printKey();
	cout << "-----------------------------\n\n";

	for (int i = 0; i < 19; i++){
	cout<<T1.extractMin()<<" ";
	}
	cout<<endl;

	cout << "T1 (After merge & 19 extractMins):\n";
	T1.printKey();

	return 0;
}

/* OUTPUT
T1 (Original):
B1
30 84

B3
21 31 48 54 69 47 58 74
-----------------------------

T2 (Tests copy constructor; should = T1):
B1
30 84

B3
21 31 48 54 69 47 58 74
-----------------------------

Copy assignment operator calling next. Remember that if there is already data in the FibHeap, you must clear it before the copy.
T2 (Tests copy assignment operator):
B1
1 2

B3
3 7 9 10 8 5 6 4
-----------------------------

ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
ExtractMin Successful
The next line is going to call extractMin on what should be an empty heap. Dixon said we wouldn't be tested on this but I figured that we might as well.
Great! You didn't segmentation fault. It doesn't matter what it returned.
---------------------------------------------------------------------
T1:
B1
30 84

B3
21 31 48 54 69 47 58 74
-----------------------------

T4:
B1
1 2

B3
3 7 9 10 8 5 6 4
-----------------------------

T1 (After merge):
B1
30 84

B3
21 31 48 54 69 47 58 74

B1
1 2

B3
3 7 9 10 8 5 6 4
-----------------------------

T1 (After merge & 19 extractMins):
B0
84
*/