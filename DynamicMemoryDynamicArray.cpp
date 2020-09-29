#include <iostream>
#include <vector>

using namespace std;



template <class Type>
class dynamicArray {
private:
	Type* pa;  //points to array
	int length; //number of elements
	int nextIndex; //next index
public: 
	dynamicArray(); //constructor
	~dynamicArray();//destructor
	Type& operator[](int index); 
	void add(Type val);
	int size();
};

template <class T>
dynamicArray<T>::dynamicArray() {
	//Constructor using scope traversal
	//creates a array of ten 0's ;
	pa = new T[10];
	for (int i = 0;i < 10;i++)
		pa[i] = 0;
	length = 10;
	nextIndex = 0;
}

template <class T>
dynamicArray<T>::~dynamicArray() {
	delete [] pa; 
}

template <class T>
T& dynamicArray<T>::operator[](int index) {
	//overloading the indexing operator
	T* pnewa;
	if (index >= length) { //if index out of range
		pnewa = new T[index + 10]; //assigns a bigger array
		for (int i = 0;i < nextIndex; i++)
			pnewa[i] = pa[i]; //copies values of old array
		for (int i = nextIndex; i < index + 10;i++)
			pnewa[i] = 0; //initialize the rest of the values to 0;
		length = index + 10; //increase the length
		delete[] pa; //delete old array
		pa = pnewa; //reassign the pointer to new array (first element)
	}
	if (index > nextIndex) 
		nextIndex = index + 1; //set nextIndex after index
	return *(pa + index); //return the value indexed.

}

template <class T>
void dynamicArray<T>::add(T val) {
	T* pnewa;
	if (nextIndex == length) {
		length = length + 10;
		pnewa = new T[length];
		for (int i = 0; i < nextIndex; i++)
			pnewa[i] = pa[i];
		for (int j = nextIndex; j < length; j++)
			pnewa[j] = 0;
		delete[] pa;
		pa = pnewa;
	}
	pa[nextIndex++] = val;
}

template <class T>
int dynamicArray<T>::size() {
	return length;
}


int main() {
	//dynamic memory is allocated using new
	//pointer = new type 
	//pointer_array = new type [num_elements]

	int* pointer;
	pointer = new int[5];

	//dynamicly allocated pointer and memory is destroyed with delete
	//delete pointer;
	//delete[] pointer;

	dynamicArray<int> myArray;
	for (int i = 0;i < 12;i++) {
		myArray.add(i);
	}
	for (int i = 0;i < myArray.size(); i++) {
		cout << myArray[i] << endl;
	}

}