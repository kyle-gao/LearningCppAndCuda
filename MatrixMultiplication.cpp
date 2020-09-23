#include <iostream>
#include <vector>

using namespace std;

void main()
{   
    //A is (m,p) B is (p,n)
    vector<vector<float>> A {{2, 3, 4},
                             {2, 3, 1}}; 

    vector<vector<float>> B {{5, 6}, 
                             {8, 3},
                             {6, 3}}; //(3,2)

    vector<vector<float>> C(2, vector<float>(2));

    const int m = A.size();
    const int p = A[0].size();
    const int p2 = B.size();
    const int n = B[0].size();
    float dot;
   

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            dot = 0;
            for (int k = 0; k < p; k++) {
                dot = dot + A[i][k] * B[k][j];
            }
            C[i][j] = dot;
            cout << C[i][j];
            cout << " ";
        }cout << "\n";
    }
}
