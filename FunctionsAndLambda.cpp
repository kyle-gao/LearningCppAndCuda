#include <iostream>
#include <vector>

int factorial(int n, int optional_parameter = 100) { 
	//Recursive function works just as expected
	//optional parameter can be like in python.

	if (n == 1) {
		return n;
	}
	else {
		return n * factorial(n - 1);
	}
}

int reference_argument(const int & a,const int & b) {
	//functions in c++ by default make a copy of their arguments
	//declaring parameters as references prevents this.
	//declaring parameters as constants prevents modifying their values
	return a + b;
}
//a proto function can be declared allowing it to be called. It is then properly defined later.
int protofunction(int, int);

//c++ allows for the overloading of functions if they have different arguments. This is useful when we want to consider arguments of different type.
int overload_sum(int a, int b) {
	return a + b;
}
int overload_sum(int a, int b,int c) {
	return 2*a +2*b + 2*c;
}

//a template can be used to overload functions with same function body
//note that a template can take multiple unknown type parameters. 
//the function body should resolve ambiguity should it arise. 
//templates can also take particular type as arguments 
template <class Type,class Type2, int N =3>
Type sum(Type a, Type2 b) {
	return a+b;
}


using namespace std;


int main() {
	int fact = factorial(5);
	cout << fact << " is the factorial of 5" << endl;
	cout << protofunction(1,2) << " is from protofunction(1,2)" << endl; //functions can be called without storing the return value.
	int array[2] = { 1,2 };
	int& ref = fact; //shares address
	cout << overload_sum(1, 2, 3) <<" is overloaded"<< endl;
	cout << sum(1, 1) << sum(1.0, 1.0) << endl;
	cout << [](int a, int b) {return a + b;}(10,20) << endl; //Lambda functions are declared as such in c++
	// [...] denotes the capture clause, [] denotes the lambda has no access to surrounding scope.
	cout << [&,fact](int a, int b) {return a + b + fact;}(10, 20) << endl;
	//variable fact is captured here from surrounding scope 
	//[&,...] means capture by reference
	//[=,...] means capture by value
	//[&,=a,..] means reference by default, value for var a.

}

int protofunction(int a, int b) {
	//we define the protofunction.
	return a + b;
}
