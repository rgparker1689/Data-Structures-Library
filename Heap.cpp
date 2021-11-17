#include <iostream>
#include <cstdlib>
#include "CDA.cpp"
using namespace std;

template <typename keytype>
class Heap
{
    private:
        CDA<keytype> heap;
        keytype left(keytype parent);
        keytype right(keytype parent);
        int size;
        
        void heapyify_down(){
        }

        void heapify_up(){
        }
    
    public:

        // Default Constructor
        Heap(){
            size = 0;
        }

        // Constructor given data
        Heap(keytype k[], int s){
            for(int i = 0; i < s; i++){
                Insert(k[i]);
            }
        }

        // Copy Constructor
        Heap(const Heap &source){
        }

        // Copy Assignment Operator
        Heap& operator=(Heap source){
        })

        // Destructor
        ~Heap(){
            delete heap;
        }

        // Return min without modifying
        keytype peekKey(){
            if (heap.Length() == 0){
                return;
            }
            return heap[0];
        }

        // Remove min and return it
        keytype extractMin(){
            keytype cur_min = this.peekKey();
            if (heap.Length() == 0){
                return;
            }

            heap[0] = heap[heap.Length() - 1];
            heap.DelEnd();
            heapify_down(0);
            return cur_min;
        }

        // Insert key into heap
        void insert(keytype k){
            heap.AddEnd(k);
            heapify_up(heap.Length() - 1);
        }

        // Print keys in array starting at root
        void printKey(){
            heap.PrintArray();
        }

        int size(){
            return size;
        }
};

