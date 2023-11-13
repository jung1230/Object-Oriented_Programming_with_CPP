// #include <vector>
// #include <iostream>


// int main() {

//     std::vector<int> intVec(10, 1);

//     int row = 2;
//     int col = 3;
//     std::vector<std::vector<int>> matrix(row, std::vector<int>(col,8));


//     for (int i = 0; i < row; i++) {
//         for (int j = 0; j < col; j++) {
//             matrix[i][j] = i*(col) + j;
//         }
//     }
//     for (int i = 0; i < row; i++) {
//         for (int j = 0; j < col; j++) {
//             std::cout << matrix[i][j] << ' ';
//         }
//         std::cout << std::endl;
//     }
//     return 0;
// }

#include <vector>
#include <iostream>

int main() {

    int row = 2;
    int col = 3;
    std::vector<std::vector<int>> matrix;

    for (int i = 0; i < row; i++) {
        std::vector<int> temp;
        for (int j = 0; j < col; j++) {
            temp.push_back(i * col + j);
        }
        matrix.push_back(temp);
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
