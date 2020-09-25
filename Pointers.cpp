#include <iostream>

using namespace std;
//pointers store address of another variable 
int main(){
	string hello = "Hello World"; //string is a std::string class, not a fundamental variable

	string * point; //* declares pointer to an address
	point = &hello; //& declares reference to an address. 
	//is also used to reference parameters in function e.g. void func(int &a,int &b) {} when used in variable declaration.


	cout << point << "\n"; //Prints the address stored at point
	cout << *point << endl; //endl is equivalent to newline \n

	int array[5] = { 1,2,3,4,5 }; //The address stored in the variable name is that of the first element. 
								  //Note, c++ arrays are not bounded, accessing out of bound index will return what ever is stored there. 
	int * element_pointer;
	int * (array_of_pointer[5]); //an array of pointers
	int * same_as_abbove[5]; //syntactically the same as above * comes after [] in order of operation 
	int (*array_pointer)[5]; //a pointer to the whole array

	element_pointer = array; //point to the first member of array itself an address
	array_pointer = &array; //point to the address of array

	cout << "The address pointed to is " << element_pointer << endl;
	cout << "The value pointed to is " << *element_pointer << endl;
	/*This is equivalent to */
	cout << "The first address is " << array << endl; //
	cout << "The first element is " << array[0] << endl;

	element_pointer++; //shifts the pointer
	cout << "The next element is" << *element_pointer <<endl; //points to the next element

	*(element_pointer + 1) = 1000; //assign value to next element of the array i.e. VALUE at (pointer + 1) = 1000
	cout << array[2] <<endl;
	

	for (int i = 0;i < 5;i++) {
		array_of_pointer[i] = &array[i]; //assign address to all the elements of the pointer array
		cout << *array_of_pointer[i] << endl;
	}

	/*We can use pointer operations to index arrays*/
	int array_2d[2][2] = { {1,2},{3,4} };

	cout <<"The last element is "<< array_2d[1][1] << endl; 
	cout <<"The last element is "<< *(*(array_2d + 1)+1)<<endl;
	/* *(array_2 +1) points to the (first element of the) second row which is {3,4)*/

}

// Summary:

//    & when used with a variable declaration: "reference to"
//    Example: int &ra = a;
//    "ra is a reference to a"

//    * when used with a variable declaration: "pointer to"
//    Example: int *pa;
//    "pa is a pointer to an integer"

//    & when used with an already declared variable: "address of"
//    Example: &a;
//    "address of a"

//    * when used with an already declared pointer: "dereference"
//    Example: std::cout << *pa << std::endl;
//    "print the underlying value of a"

//     variable name for an array returns the address of the first element, behaves similarly to a pointer.
