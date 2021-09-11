#include <iostream>
#include <cstdlib>
using namespace std;
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
            cout<<"Out of bounds. "<<endl;
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
    int partition(CDA<elmtype> *array, int left, int right){
        elmtype pivot = array->operator[](right);
        int i = left - 1;
        for(int j = left; j <= right - 1; j++){
            if(array->operator[](j) <= pivot){
                i++;
                swap(array->operator[](i), array->operator[](j));
            }
        }
        swap(array->operator[](i+1), array->operator[](right));
        return i + 1;
    }

    int gen_piv(CDA<elmtype> *array, int left, int right){
        int random = left + rand() % (right - left);
        swap(array->operator[](random), array->operator[](right));
        return partition(array, left, right);
    }

    void quickSort(CDA<elmtype> *array, int left, int right){
        if(left < right){
            int pivot = gen_piv(array, left, right);
            quickSort(array, left, pivot - 1);
            quickSort(array, pivot + 1, right);
        }
    }

    // Quickselect kth smallest element
    elmtype Select(int k){
        quickSort(this, 0, size-1);
        int ctr = 1;
        int i = 1;
        elmtype curr = this->operator[](0);
        while(ctr < k && i < size){
            if(this->operator[](i) != curr){
                curr = this->operator[](i);
                ctr++;
            }
            i++;
        }
        return curr;
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

    // Linear search of unsorted array, returning idx or -1
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

void foo(CDA<int> x) {
	for (int i=0; i<x.Length()/2; i++)
		x[i] = x[x.Length()/2+i];
	// X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"	
	for (int i=0; i< x.Length();i++) cout << x[i] << " ";  cout << endl;
}

int main(){
	CDA<float> C(10);
	for (int i=0; i< C.Length();i++) C[i] = i;
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.DelFront();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.DelEnd();
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.AddEnd(100.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.AddEnd(101.0);	
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100 101"
	C.DelEnd(); C.DelFront();
	C.AddFront(-100.0); C.AddFront(-200.0);
	for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
	// C => "-200 -100 2 3 4 5 6 7 8 100"

	CDA<int> A,B;
	for(int i=0; i<10;i++) A.AddEnd(i);
	B = A;   //Testing the copy assignment operator
	A.AddEnd(15); A.AddEnd(19);
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" 
	cout << "Search is " << A.Search(5) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Search => 5
	cout << "BinSearch is " << A.BinSearch(12) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" BinSearch => -11
	cout << "Select is " << A.Select(3) << endl;
	// A => "0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	A.Sort();
	A.AddFront(10); 
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19"
	cout << "Search is " << A.Search(5) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Search => 6
	cout << "Select is " << A.Select(3) << endl;
	// A => "10 0 1 2 3 4 5 6 7 8 9 15 19" Select => 2
	A.Sort();
	// A => "0 1 2 3 4 5 6 7 8 9 10 15 19"
	A.AddEnd(11); A.AddFront(1); A.AddFront(2); A.AddFront(3);
	cout << "Capacity is " << A.Capacity() << endl;
	// A => "3 2 1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32
	A.DelFront(); A.DelFront();
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32
	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;

	foo(A);  //Testing the copy constructor;

	for (int i=0; i< A.Length();i++) cout << A[i] << " ";  cout << endl;
	// A => "1 0 1 2 3 4 5 6 7 8 9 10 15 19 11"	  Capacity => 32

	for (int i=0; i< B.Length();i++) cout << B[i] << " ";  cout << endl;
	// B => "0 1 2 3 4 5 6 7 8 9"
	
	for(int i=1; i<200; i++) {
		CDA<double> D(100000,-1.0);
		for(int j=1; j<100; j++)
			D[i*j] = i*j;
		for(int j=50*i; j<51*i; j++)
			if(D[j] != -1.0) cout << "D["<<j<<"] is : "<<D[j] << endl;  //should output where D[j] is : j once per value of i
	}
	CDA<char> E(10,'X');
	E[5] = 'A';
	cout << E.Select(1) << endl;   //should output A
}