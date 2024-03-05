#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readInput(string input[][100], int& rows, int& cols) {
    ifstream file("input.txt");
    string value;
    rows = 0;
    cols = 0;

    while (file >> value) {
        input[rows][cols++] = value;
        if (cols == 5) {
            cols = 0;
            rows++;
        }
    }
    file.close();
}

void compressArray(string input[][100], int rows, int cols) {
    int compressedArray[100][2] = { 0 };
    int compressedRows = 0;

    for (int i = 0; i < rows; ++i) {
        int countYes = 0;
        for (int j = 0; j < cols; ++j) {
            if (input[i][j] == "Yes") {
                countYes++;
            }
        }
        if (countYes > 0) {
            compressedArray[compressedRows][0] = countYes;
            compressedArray[compressedRows][1] = cols - countYes;
            compressedRows++;
        }
    }

    for (int i = 0; i < compressedRows; ++i) {
        cout << compressedArray[i][0] << " " << compressedArray[i][1] << endl;
    }

    // Transforming compressed array back to original input array
    int currentRow = 0;
    for (int i = 0; i < compressedRows; ++i) {
        int countYes = compressedArray[i][0];
        int countNo = compressedArray[i][1];
        for (int j = 0; j < countYes; ++j) {
            input[currentRow][j] = "Yes";
        }
        for (int j = countYes; j < cols; ++j) {
            input[currentRow][j] = "No";
        }
        currentRow++;
    }
}

int countYes(string input[][100], int rows, int cols) {
    int count = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (input[i][j] == "Yes") {
                count++;
            }
        }
    }
    return count;
}

int main() {
    string input[100][100];
    int rows, cols;

    readInput(input, rows, cols);

    compressArray(input, rows, cols);

    int yesCount = countYes(input, rows, cols);
    cout << "Number of 'Yes' values in the original array: " << yesCount << endl;

    return 0;
}
