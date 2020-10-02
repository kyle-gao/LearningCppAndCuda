#include <iostream>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

MatrixXf MatrixMultiply(MatrixXf, MatrixXf);
MatrixXf StrassenMultiplication(MatrixXf, MatrixXf, int MinSize = 1);
//Switches to naive multiplication when submatrices reaches MinSize 

int main() {
	Matrix4f A = Matrix4f::Random();
	Matrix4f B = Matrix4f::Random();
	Matrix4f C1;
	Matrix4f C2;
	int minSize = 1;
	C1 = StrassenMultiplication(A, B);
	cout << A*B<<endl;
	cout << "Naive MM" << endl;
	cout << MatrixMultiply(A, B)<<endl;
	cout << "Strassen MM" << endl;
	cout << C1 << endl;

}

MatrixXf MatrixMultiply(MatrixXf A, MatrixXf B) {
	int m = A.rows();
	int k = A.cols();
	int k2 = B.rows();
	int n = B.cols();
	MatrixXf C(m, n);

	assert(k == k2);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			float sum = 0.0;
			for (int z = 0;z < k;z++)
				sum = sum + A(i, z) * B(z, j);
			C(i, j) = sum;
		}
	}return C;
}

MatrixXf StrassenMultiplication(MatrixXf A, MatrixXf B, int minSize) {
	//Strassen Multiplication Algorithm, A and B must be square matrices
	//of dimensions that are powers of 2.

	int m1 = A.rows();
	int n1 = A.cols();
	int m2 = B.rows();
	int n2 = B.cols();

	assert(m1 == n1 && n1 == m2 && m2 == n2); //check if square matrix and dimensions match
	assert(m1 % 2 == 0 || m1==1); //check size divisible by 2
	MatrixXf C(m1, n2);

	if (m1 <= minSize) {
		C = MatrixMultiply(A, B);
		return C;
	}

	int m = m1 / 2;

	MatrixXf A11 = A(seq(0, m-1), seq(0, m-1));
	MatrixXf A12 = A(seq(0, m - 1), seq(m, m1-1));
	MatrixXf A21 = A(seq(m, m1 - 1), seq(0, m-1));
	MatrixXf A22 = A(seq(m, m1 - 1), seq(m, m1 - 1));

	MatrixXf B11 = B(seq(0, m - 1), seq(0, m-1));
	MatrixXf B12 = B(seq(0, m - 1), seq(m, m1 - 1));
	MatrixXf B21 = B(seq(m, m1 - 1), seq(0, m - 1));
	MatrixXf B22 = B(seq(m, m1 - 1), seq(m, m1 - 1));

	MatrixXf p1 = StrassenMultiplication(A11, B12 - B22, minSize);
	MatrixXf p2 = StrassenMultiplication(A11 + A12, B22, minSize);
	MatrixXf p3 = StrassenMultiplication(A21 + A22, B11, minSize);
	MatrixXf p4 = StrassenMultiplication(A22, B21 - B11, minSize);
	MatrixXf p5 = StrassenMultiplication(A11+A22, B11 + B22, minSize);
	MatrixXf p6 = StrassenMultiplication(A12-A22, B21+B22, minSize);
	MatrixXf p7 = StrassenMultiplication(A11-A21, B11 + B12, minSize);

	C(seq(0, m - 1), seq(0, m - 1)) = p5 + p4 - p2 + p6;
	C(seq(0, m - 1), seq(m, m1 - 1)) = p1 + p2;
	C(seq(m, m1 - 1), seq(0, m - 1)) = p3 + p4;
	C(seq(m, m1 - 1), seq(m, m1 - 1)) = p1 + p5 - p3 - p7;
	return C;


}