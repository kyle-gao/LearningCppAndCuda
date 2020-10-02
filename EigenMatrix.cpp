#include <iostream>
#include<Eigen/Core>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
	Matrix3f A; //3x3 matrix of floats
	Matrix<float, 3, 3> B;
	A << 1.0f, 0.0f, 0.0f, //0f doesnt work, 0.0f instead for a float.
		0.0f, 1.0f, 0.0f,
		0.0f, 0.1f, 1.0f;
	for (float i = 0;i < 3;i++) {
		for (float j = 0;j < 3;j++) { //indexing starts at 0
			B(i, j) = i;
		}
	}
	cout << B << endl;
	cout << A * B << endl; //matrix multiplication
	cout << A.cwiseProduct(B) << endl; //hadamard product
	cout << A.array() * B.array() << endl; //also hadamard product
	cout << Matrix3f::Random() << endl; //uniform random [-1,1]
	cout << Matrix3f::Identity() << endl;
	Matrix3f Ones = Matrix3f::Ones();
	cout << Ones << endl;
	//!= and == work for matrix
	//M1==M2 iff all elements are equal
	Matrix4f M1 = Matrix4f::Random();
	Matrix4f M2 = Matrix4f::Constant(2.2);

	cout << M1.inverse()<<endl;


}