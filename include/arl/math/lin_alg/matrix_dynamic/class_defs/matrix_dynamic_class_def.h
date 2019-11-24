#ifndef MATRIX_DYNAMIC_CLASS_H_
#define MATRIX_DYNAMIC_CLASS_H_

namespace arl
{

template <typename T> struct QRMatrixPair
{
    Matrix<T> q;
    Matrix<T> r;

    QRMatrixPair(const size_t num_rows, const size_t num_cols);
};

template <typename T> struct LUMatrixPair
{
    Matrix<T> l;
    Matrix<T> u;

    LUMatrixPair(const size_t num_rows, const size_t num_cols);
};

template <typename T> struct SVDMatrixTriplet
{
    Matrix<T> u;
    Matrix<T> s;
    Matrix<T> v;

    SVDMatrixTriplet(const size_t num_rows, const size_t num_cols);
};

template <typename T> class Matrix
{
protected:
    T* data_;
    size_t num_rows_;
    size_t num_cols_;
    bool is_allocated_;

public:
    Matrix();
    Matrix(const size_t num_rows, const size_t num_cols);
    Matrix(const Matrix<T>& m);
    Matrix(const std::vector<std::vector<T>>& vm);
    Matrix(const std::initializer_list<std::initializer_list<T>>& il);
    Matrix(const T a[3][3]);
    ~Matrix();
    T& operator()(const size_t r, const size_t c);
    const T& operator()(const size_t r, const size_t c) const;

    Matrix<T> operator()(const size_t row, const IndexSpan& col_idx_span) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const size_t col) const;
    Matrix<T> operator()(const IndexSpan& row_idx_span, const IndexSpan& col_idx_span) const;

    T& operator()(const EndIndex& row_end_idx, const size_t c);
    const T& operator()(const EndIndex& row_end_idx, const size_t c) const;
    T& operator()(const size_t r, const EndIndex& col_end_idx);
    const T& operator()(const size_t r, const EndIndex& col_end_idx) const;
    Matrix<T>& operator=(const Matrix<T>& m);

    void removeRowAtIndex(const size_t row_idx);
    void removeRowsAtIndices(const IndexSpan& idx_span);
    void removeColAtIndex(const size_t col_idx);
    void removeColsAtIndices(const IndexSpan& idx_span);
    void resize(const size_t num_rows, const size_t num_cols);
    size_t rows() const;
    size_t cols() const;
    size_t size() const;
    size_t numElements() const;
    void hCat(const Vector<T>& v);
    void vCat(const Vector<T>& v);
    bool isAllocated() const;
    void fill(const T val);
    void switchRows(size_t r0, size_t r1);
    void switchColumns(size_t c0, size_t c1);
    T* getDataPointer() const;
    Matrix<T> transposed() const;

    void addVectorToMatrixCols(const Vector<T>& v);
    void addVectorToMatrixRows(const Vector<T>& v);

    Vector<T> getColumnAsVector(size_t column_idx) const;
    Vector<T> getRowAsVector(size_t row_idx) const;
    Matrix<T> getColumn(size_t column_idx) const;
    Matrix<T> getRow(size_t row_idx) const;
    size_t lastRowIdx() const;
    size_t lastColIdx() const;
    Matrix<T> inverse() const;
    void invert();
    Vector<T> solve(const Vector<T>& b) const;
    T det() const;
    T norm() const;
    LUMatrixPair<T> lu() const;
    QRMatrixPair<T> qr() const;
    SVDMatrixTriplet<T> svd() const;
};
}  // namespace arl

#endif
