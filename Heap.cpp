#include <iostream>
#include <cstdlib>
#include "CDA.cpp"
#include <string>
using namespace std;

template <typename keytype>
class Heap
{
    private:
        CDA<keytype> heap;
        int num;


        int left_index(int idx){
            int temp = (idx + 1) * 2;
            if(temp >= heap.Length()){
                return -1;
            } else {
                return temp;
            }
        }

        int right_index(int idx){
            int temp = (idx + 1) * 2 + 1;
            if(temp >= heap.Length()){
                return -1;
            } else {
                return temp;
            }
        }

        int parent_index(int idx){
            if(idx == 0){
                return -1;
            }
            return (idx-1) / 2;
        }
        
        void heapify_down(int idx, bool debug=false){
            int left = left_index(idx);
            int right = right_index(idx);
            
            if(debug){
                string leftId;
                string rightId;
                if(left == -1){
                    leftId = "No child.";
                } else {
                    leftId = to_string(heap[left - 1]);
                }
                if(right == -1){
                    rightId = "No child.";
                } else {
                    rightId = to_string(heap[right - 1]);
                }
                cout<<"Parent: "<<heap[idx]<<" is compared to left: "<<leftId<<" and right: "<<rightId<<endl;
            }
            
            if(left >= 0 && right >= 0 && heap[right-1] < heap[left-1]){
                keytype temp = heap[idx];
                heap[idx] = heap[right-1];
                heap[right-1] = temp;
                heapify_down(right-1);
            }
            else if(left >= 0){
                keytype temp = heap[idx];
                heap[idx] = heap[left-1];
                heap[left-1] = temp;
                heapify_down(left-1);
            } else {
                return;
            }
        }

        void heapify_up(int idx){
            int parent = parent_index(idx);
            if(parent < 0){
                return;
            }
            if(heap[parent] > heap[idx]){
                keytype temp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = temp;
                heapify_up(parent);
            } else {
                return;
            }
        }
    
    public:

        // Default Constructor
        Heap(){
        }

        // Constructor given data
        Heap(keytype k[], int s){

            // First construct in given order
            for(int i = 0; i < s; i++){
                heap.AddEnd(k[i]);
            }

            int parent = s/2;
            for(int i = parent; i >= 1; i--){
                int start_index = i;
                keytype temp = k[start_index-1];
                bool satisfied = false;
                while(!satisfied && 2 * start_index <= s){
                    int j = 2 * start_index;
                    if (j < s){
                        if(heap[j-1] > heap[j]){
                            j++;
                        }
                    }
                    if (temp < heap[j-1]){
                        satisfied = true;
                    } else {
                        heap[start_index-1] = heap[j-1];
                        start_index=j;
                    }
                }
                heap[start_index-1] = temp;
            }
        }

        // Copy Constructor
        Heap(const Heap &source){
            CDA<keytype> new_data = new CDA<keytype>;
            for(int i = 0; i < source.size(); i++){
                new_data[i] = source.heap[i];
            }
            heap = new_data;
        }

        // Copy Assignment Operator
        Heap& operator=(Heap source){
            CDA<keytype> new_data = new CDA<keytype>;
            for(int i = 0; i < source.size(); i++){
                new_data[i] = source.heap[i];
            }
            heap = new_data;
            return *this;
        }

        // Destructor
        ~Heap(){
        }

        // Return min without modifying
        keytype peekKey(){
            if (heap.Length() == 0){
                cout<<"SegFault at peekkey"<<endl;
            }
            return heap[0];
        }

        // Remove min and return it
        keytype extractMin(){
            keytype cur_min = this->peekKey();
            if (heap.Length() == 0){
                cout<<"SegFault at extractMin"<<endl;
            }
            heap[0] = heap[heap.Length() - 1];
            heap.DelEnd();
            heapify_down(0);
            return cur_min;
        }

        // Insert key into heap
        void insert(keytype k){
            heap.AddEnd(k);
            heapify_up(heap.Length()-1);
            num++;
        }

        // Print keys in array starting at root
        void printKey(){
            heap.PrintArray();
        }

        int size(){
            return heap.Length();
        }
};


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
}