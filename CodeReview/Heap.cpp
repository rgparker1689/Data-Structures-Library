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


        int left_index(int idx){
            int temp = 2*idx + 1;
            if(temp >= heap.Length()){
                return -1;
            } else {
                return temp;
            }
        }

        int right_index(int idx){
            int temp = 2*idx + 2;
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
        
        void heapify_down(int idx){
            int left = left_index(idx);
            int right = right_index(idx);
            int min = idx;
            
            if(left >= 0 && heap[left] < heap[min]){
                min = left;
            }

            if(right >= 0 && heap[right] < heap[min]){
                min = right;
            }

            if(min != idx){
                keytype temp = heap[idx];
                heap[idx] = heap[min];
                heap[min] = temp;
                heapify_down(min);
            }

        }

        void heapify_up(int idx){

            if(idx > 0 && heap[parent_index(idx)] > heap[idx]){
                keytype temp = heap[idx];
                heap[idx] = heap[parent_index(idx)];
                heap[parent_index(idx)] = temp;
                heapify_up(parent_index(idx));
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
            cout<<parent<<endl;
            for(int i = parent; i >= 0; i--){
                int cur_parent = i;
                keytype temp = heap[cur_parent];
                bool satisfied = false;
                while(!satisfied && left_index(cur_parent) > 0){
                    int to_check = left_index(cur_parent); // Starting at left child

                    if(to_check < heap.Length()){
                        if(heap[to_check] > heap[cur_parent]){
                            to_check++; // Navigating to right child
                        }
                    }
                    
                    if(heap[cur_parent] < heap[to_check]){
                        satisfied = true;
                    } else {
                        heap[cur_parent] = heap[to_check];
                        heap[to_check] = temp;
                        cur_parent = to_check;
                        i++;
                    }
                }
                heap[cur_parent] = temp;
            }
        }

        // Copy Constructor
        Heap(Heap &source){
            CDA<keytype> new_data;
            for(int i = 0; i < source.size(); i++){
                new_data.AddEnd(source.heap[i]);
            }
            heap = new_data;
        }

        // Copy Assignment Operator
        Heap& operator=(Heap source){
            CDA<keytype> new_data;
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
        }

        // Print keys in array starting at root
        void printKey(){
            heap.PrintArray();
        }

        int size(){
            return heap.Length();
        }
};


// int main(){
//     string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
// 	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
// 	Heap<int> T1, T2(B,10);
	
// 	T2.printKey();
// 	//Should output  1 2 4 3 6 5 8 10 7 9
	
// 	for(int i=0; i<10; i++) T1.insert(B[i]);
	
// 	T1.printKey();
// 	// Should output 1 2 5 4 3 9 6 10 7 8
	
// 	cout << T2.peekKey() << endl;
// 	//Should output 1
	
// 	cout << T1.extractMin() << endl;
// 	//Should output 1
	
// 	T1.printKey();
// 	//Should output 2 3 5 4 8 9 6 10 7
// }