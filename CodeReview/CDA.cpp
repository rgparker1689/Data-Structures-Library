#include <iostream>
#include <cstdlib>
using namespace std;

#pragma once
const int RUN = 32;

template <typename elmtype>
class CDA   
{
private:

    size_t front_idx;
    size_t rear_idx;
    size_t top;
    elmtype init_val;
    size_t size;
    size_t capacity;
    elmtype* array;
    size_t* from;
    size_t* to;
    bool init_supplied;

public:

    // Default Constructor
    CDA<elmtype>(){
        capacity = 1;
        size = 0;
        front_idx = 0;
        rear_idx = 0;

        top = 0;
        array = new elmtype[capacity];
        from = new size_t[capacity];
        to = new size_t[capacity];
        
        init_supplied = false;
    }

    // Constructor given size
    CDA<elmtype>(int s){
        size = s;   
        capacity = s;
        front_idx = 0;
        rear_idx = s - 1;

        top = 0;
        array = new elmtype[capacity];
        from = new size_t[capacity];
        to = new size_t[capacity];

        init_supplied = false;
    }

    // Consructor given init
    CDA<elmtype>(int s, elmtype init){
        size = s;
        capacity = s;
        init_val = init;
        front_idx = 0;
        rear_idx = s - 1;

        top = 0;
        array = new elmtype[capacity];
        from = new size_t[capacity];
        to = new size_t[capacity];

        init_supplied = true;
    }

    // Copy constructor
    CDA(const CDA &source){
        size = source.size;
        capacity = source.capacity;
        if(source.init_supplied){
            init_supplied = true;
            init_val = source.init_val;
        } else {
            init_supplied = false;
        }
        front_idx = source.front_idx;
        rear_idx = source.rear_idx;
        top = source.top;
        
        elmtype* new_array = new elmtype[capacity];
        size_t* new_from = new size_t[capacity];
        size_t* new_to = new size_t[capacity];
        for(int i = 0; i < capacity; i++){
            new_array[i] = source.array[i];
            new_from[i] = source.from[i];
            new_to[i] = source.to[i];
        }

        array = new_array;
        from = new_from;
        to = new_to;
    }

    // Copy assignment operator
    CDA& operator=(CDA source){
        size = source.size;
        capacity = source.capacity;
        if(source.init_supplied){
            init_supplied = true;
            init_val = source.init_val;
        } else {
            init_supplied = false;
        }
        front_idx = source.front_idx;
        rear_idx = source.rear_idx;
        top = source.top;
        
        elmtype* new_array = new elmtype[capacity];
        size_t* new_from = new size_t[capacity];
        size_t* new_to = new size_t[capacity];
        for(int i = 0; i < capacity; i++){
            new_array[i] = source.array[i];
            new_from[i] = source.from[i];
            new_to[i] = source.to[i];
        }

        array = new_array;
        from = new_from;
        to = new_to;

        return *this;
    }

    // Destructor
    ~CDA(){
        delete[] array;
        delete[] from;
        delete[] to;
    }

    // [] operator
    elmtype& operator[](int idx){
        if(idx < 0 || idx > size - 1){
            cout<<"Out of bounds. "<<idx<<endl;
            return init_val;
        }
        size_t true_idx = (front_idx + idx) % capacity;

        if(from[true_idx] < top && to[from[true_idx]] == true_idx){
            return array[true_idx];
        } else if(init_supplied){
            from[true_idx] = top;
            to[top] = true_idx;
            array[true_idx] = init_val;
            top++;
            return array[true_idx];
        } else {
            return array[true_idx];
        }
    }

    // Doubles array capacity- MAKE COMPATIBLE WITH CIRCULARITY/ADJ IDXS
    void grow(){
        size_t factor = capacity;
        capacity *= 2;

        elmtype* new_array = new elmtype[capacity];
        size_t* new_from = new size_t[capacity];
        size_t* new_to = new size_t[capacity];
        size_t ctr = 0;
        top = 0;

        for(int i = front_idx; i != rear_idx; i++){
            if(i == factor){
                i %= factor;
            }
            new_array[ctr] = array[i];
            new_from[ctr] = top;
            new_to[top] = ctr;
            top++;
            ctr++;
            if(i == rear_idx){
                break;
            }
        }
        new_array[ctr] = array[rear_idx];
        new_from[ctr] = top;
        new_to[top] = ctr;
        top++;

        array = new_array;
        from = new_from;
        to = new_to;
        front_idx = 0;
        rear_idx = size - 1;
    }

    // Halves array capacity
    void shrink(){
        size_t factor = capacity;
        capacity /= 2;

        elmtype* new_array = new elmtype[capacity];
        size_t* new_from = new size_t[capacity];
        size_t* new_to = new size_t[capacity];
        size_t ctr = 0;
        top = 0;

        for(int i = front_idx; i != rear_idx; i++){
            if(i == factor){
                i %= factor;
            }
            new_array[ctr] = array[i];
            new_from[ctr] = top;
            new_to[top] = ctr;
            top++;
            ctr++;
        }
        new_array[ctr] = array[rear_idx];
        new_from[ctr] = top;
        new_to[top] = ctr;
        top++;

        array = new_array;
        from = new_from;
        to = new_to;
        front_idx = 0;
        rear_idx = size - 1;
    }

    // Add to end
    void AddEnd(elmtype v){
        if(size + 1 > capacity){
            grow();
        }
        size++;
        rear_idx ++;
        if(rear_idx == capacity){
            rear_idx %= capacity;
        }
        array[rear_idx] = v;
        from[rear_idx] = top;
        to[top] = rear_idx;
        top++;
    }

    // Add to front
    void AddFront(elmtype v){
        if(size + 1 > capacity){
            grow();
        }
        size++;
        if(front_idx == 0){
            front_idx += capacity;
        }
        front_idx--;
        array[front_idx] = v;
        from[front_idx] = top;
        to[top] = front_idx;
        top++;
    }

    // Delete end
    void DelEnd(){
        if(size - 1 <= .25 * capacity && capacity >= 8){
            shrink();
        }
        size--;
        array[rear_idx] = '\0';
        if(rear_idx == 0){
            rear_idx += capacity;
        }
        rear_idx--;
    }

    // Delete front
    void DelFront(){
        if(size - 1 <= .25 * capacity && capacity >= 8){
            shrink();
        }
        size--;
        array[front_idx] = '\0';
        front_idx++;
        if(front_idx == capacity){
            front_idx %= capacity;
        }
    }

    // Get length
    int Length(){
        return size;
    }

    // Get capacity
    int Capacity(){
        return capacity;
    }

    int min(int a, int b){
        if(a < b){
            return a;
        } else {
            return b;
        }
    }

    // Running insertion sort on TimSort Runs
    void insertionSort(CDA<elmtype> *array, int left, int right){
        for(int i = left + 1; i <= right; i++){
            elmtype temp = array->operator[](i);
            int j = i - 1;
            while(j >= left && array->operator[](j) > temp){
                array->operator[](j+1) = array->operator[](j);
                j--;
            }
            array->operator[](j+1) = temp;
        }
    }

    // Merging runs for TimSort
    void mergeRuns(CDA<elmtype> *array, int left, int mid, int right){
        int len1 = mid - left + 1;
        int len2 = right - mid;
        CDA<elmtype> left_array(len1);
        CDA<elmtype> right_array(len2);
        for(int i = 0; i < len1; i++){
            left_array.operator[](i) = array->operator[](left + i);
        }
        for(int i = 0; i < len2; i++){
            right_array.operator[](i) = array->operator[](mid + i + 1);
        }

        int i = 0;
        int j = 0;
        int k = left;

        while(i < len1 && j < len2){
            if(left_array[i] <= right_array[j]){
                array->operator[](k) = left_array.operator[](i);
                i++;
            } else {
                array->operator[](k) = right_array.operator[](j);
                j++;
            }
            k++;
        }

        while(i < len1){
            array->operator[](k) = left_array[i];
            k++;
            i++;
        }

        while(j < len2){
            array->operator[](k) = right_array[j];
            k++;
            j++;
        }
    }

    int partition(CDA<elmtype> *array, int low, int high){
        elmtype pivot = array->operator[](high);
        int i = (low - 1);
    
        for (int j = low; j <= high - 1; j++){
            if (array->operator[](j) <= pivot) {
                i++;
                swap(array->operator[](i), array->operator[](j));
            }
        }
        swap(array->operator[](i+1), array->operator[](high));
        return (i + 1);
    }


    int partition_r(CDA<elmtype> *array, int low, int high){
        srand(time(NULL));
        int random = low;
        // Check for div by zero
        if(high != low){
            random = low + rand() % (high - low);
        }
        // Make random pivot high index/selected by partition function
        swap(array->operator[](random), array->operator[](high));
    
        return partition(array, low, high);
}


    elmtype kthSmallest(CDA<elmtype> *array, int     l, int r, int k){
        if (k > 0 && k <= r - l + 1) {
            int index = partition_r(array, l, r);
            if (index - l == k - 1)
                return array->operator[](index);    
            if (index - l > k - 1)
                return kthSmallest(array, l, index - 1, k);
            return kthSmallest(array, index + 1, r,
                                k - index + l - 1);
        }
        return init_val;
    }

    // Quickselect kth smallest element
    elmtype Select(int k){
        return kthSmallest(this, 0, size-1, k);
    }

    // Sorts in O(nlog(n)) Using TimSort
    void Sort(){

        for(int i = 0; i < size; i += RUN){
            insertionSort(this, i, min((i + RUN - 1), (size - 1)));
        }
        for(int width = RUN; width < size; width *= 2){
            for(int left = 0; left < size; left += (2 * width)){
                int mid = left + width - 1;
                int right = min((left + 2*width - 1), (size - 1));
                if(mid < right){
                    mergeRuns(this, left, mid, right);
                }
            }
        }
    }

    // Linear search of unsorted array, returning ..idx or -1
    int Search(elmtype e){
        for(int i = 0; i < size; i++){
            if(this->operator[](i) == e){
                return i;
            }
        }
        return -1;
    }

    // Recursive helper function for binary search
    int BinSearchHelper(int left, int right, elmtype e){
        if(right >= left){
            int mid = left + (right - left) / 2;
            if(this->operator[](mid) == e){
                return mid;
            }
            if(this->operator[](mid) > e){
                return BinSearchHelper(left, mid - 1, e);
            } else {
                return BinSearchHelper(mid + 1, right, e);
            }
        }
        if(this->operator[](right) > e){
            return ~right;
        } else {
            return ~(right + 1);
        }
        return -1;
    }

    // Binary search of sorted array, returning idx or bitwise complement of idx of next largest element or bitwise complement of size
    int BinSearch(elmtype e){
        return BinSearchHelper(0, size-1, e);
    }

    void PrintArray(){
        for(int i = 0; i < size; i++){
            cout<<this->operator[](i)<<' ';
        }
        cout<<endl;
    }

    void PrintTrue(){
        for(int i = 0; i < capacity; i++){
            cout<<i<<": "<<array[i]<<" ";
        }
        cout<<endl;
    }

    bool compare(elmtype a, elmtype b){
        return (a > b);
    }

    void PrintFromTo(){
        for(int i = 0; i < capacity; i++){
            cout<<from[i]<<" ";
        }
        cout<<endl;
        for(int i = 0; i < capacity; i++){
            cout<<to[i]<<" ";
        }
        cout<<endl;
    }

};
