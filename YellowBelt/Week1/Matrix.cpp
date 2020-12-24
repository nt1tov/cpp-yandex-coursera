#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
 
using namespace std;
 
class Matrix{
    
    int rows;
    int cols;
    int *data;

public:
    Matrix(): rows{0}, cols{0}, data{nullptr} { };
    Matrix(int num_rows, int num_cols);
    ~Matrix();
    void Reset(int rs, int cls);
    int  At(int row, int col) const;
    int& At(int row, int col);
    int  GetNumRows() const {   return rows;    }
    int  GetNumColumns() const {    return cols;    }
    friend std::istream& operator>> (std::istream &in, Matrix &mat);   
    friend std::ostream& operator<< (std::ostream &out, const Matrix &mat);
    friend bool operator==(const Matrix &left, const Matrix &right);
    friend Matrix operator+(const Matrix &left, const Matrix &right);
};
 
Matrix::Matrix(int num_rows, int num_cols)
{
    if (num_rows < 0 || num_cols < 0) {
        throw std::out_of_range (
                                    "Matrix::Matrix(int, int) : " +
                                    std::to_string(num_rows)
                                    + " " + std::to_string(num_cols)
                                );
    }
    rows = num_rows;
    cols = num_cols;
    if(rows != 0 && cols != 0){
        data = new int[rows * cols]{0};
    }
    else{
        rows = cols = 0;
        data = nullptr;
    }
}
 
Matrix::~Matrix()
{
    delete[] data;
}
 
void  Matrix::Reset(int rs, int cls)
{
    if(rs < 0 || cls < 0 ){
        throw std::out_of_range (
                                    "void Matrix::Reset() : " +
                                    std::to_string(rs)
                                    + " " + std::to_string(cls)
                                );
    }
    rows = rs;
    cols = cls;
    if(data)
        delete[] data;
    if(rows != 0 && cols != 0){
        data = new int[rows * cols]{0};
    }
    else{
        rows = cols = 0;
        data = nullptr;
    }
}
 
int Matrix::At(int row, int col) const
{
    if(row < 0 || col < 0 || row >= rows || col >= cols || rows == 0 || cols == 0){ 
        throw std::out_of_range (
                                    "int Matrix::At() : "
                                          + std::to_string(row)
                                    + " " + std::to_string(col)
                                    + " " + std::to_string(rows)
                                    + " " + std::to_string(cols)
                                );
    }

    return data[col + row*cols];
}
 
int& Matrix::At(int row, int col)
{
    if(row < 0 || col < 0 || row >= rows || col >= cols || rows == 0 || cols == 0){
        throw std::out_of_range (
                                    "int& Matrix::At() : "
                                          + std::to_string(row)
                                    + " " + std::to_string(col)
                                    + " " + std::to_string(rows)
                                    + " " + std::to_string(cols)
                                );
    }

    return data[col + row*cols];
}
 
std::istream& operator>> (std::istream &in, Matrix &mat)
{
    int rows_, cols_;
    in>>rows_>>cols_;
    mat.Reset(rows_, cols_);
    for(auto i = 0; i < mat.GetNumRows();++i){
        for(auto j = 0; j < mat.GetNumColumns(); ++j){
            int tmp;
            in>>tmp;
            mat.At(i, j) = tmp;
        }
    }

    return in;
}
 
std::ostream& operator<< (std::ostream &out, const Matrix &mat)
{
    out<<mat.GetNumRows()<<" "<<mat.GetNumColumns()<<std::endl;
    for(auto i = 0; i < mat.GetNumRows(); ++i){
        for(auto j = 0; j < mat.GetNumColumns(); ++j){
            if(j < mat.GetNumColumns() - 1)
                out<<mat.At(i, j)<<" ";
            else
                out<<mat.At(i, j);
        }
        out<<std::endl;
    }
    return out;
}
 
Matrix operator+(const Matrix &left, const Matrix &right)
{
 
    if((left.GetNumRows() != right.GetNumRows()) || (left.GetNumColumns() != right.GetNumColumns())){
        throw
            std::invalid_argument(
                std::to_string(
                    left.GetNumRows() )
                + " " + std::to_string(right.GetNumRows())
                + " " + std::to_string(left.GetNumRows() )
                + " " + std::to_string(right.GetNumRows()));
    }
 
 
    Matrix sum(left.GetNumRows(), left.GetNumColumns());

 
    for(auto i = 0; i < sum.GetNumRows(); ++i){
        for(auto j = 0; j < sum.GetNumColumns(); ++j){
            sum.At(i, j) = left.At(i, j) + right.At(i, j);
        }
    }
 
    return sum;
}
 
bool operator==(const Matrix &left, const Matrix &right)
{
    if((left.GetNumRows() != right.GetNumRows()) || (left.GetNumColumns() != right.GetNumColumns()))
        return false;
    for(auto i = 0; i < left.GetNumRows(); ++i){
        for(auto j = 0; j < left.GetNumColumns(); ++j){
            if(left.At(i, j) != right.At(i, j)){
                return false;
            }
        }
    }
    return true;
}
 
int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one << two << endl;
    cout << (one == two) << endl;

    return 0;
}