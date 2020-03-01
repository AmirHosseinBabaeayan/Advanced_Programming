#ifndef Matrix_prac5_uni
#define Matrix_prac5_uni
#include <array>
class Matrix
{
public:
	Matrix(int, int);
	Matrix(int, int, float);
	explicit Matrix(int);
	Matrix();
	template<size_t n , size_t m>
	explicit Matrix(const std::array<std::array<float,n>,m> &);

	static Matrix eye(int);
	static Matrix rand(int,int);
	
	float &get(int,int);
	float & at(int, int);

	float & operator()(int, int);
	friend std::ostream &operator<<(std::ostream &, const Matrix &);
	const Matrix & operator=(const Matrix &);
	bool operator==(const Matrix &)const;
	Matrix operator+(const Matrix &)const;
	Matrix operator-(const Matrix &)const;
	Matrix operator*(const Matrix &)const;
	Matrix operator*(const int &)const;
	Matrix operator^(int)const;
	Matrix operator~()const;

	Matrix rowRange(int, int);
	Matrix colRange(int, int);

	Matrix add(const Matrix&)const;
	Matrix subtract(const Matrix&)const;
	Matrix mul(const Matrix&)const;
	Matrix mul(const int &)const;
	Matrix power(int)const;
	Matrix transpose()const;

	int rows()const;
	int cols()const;
	int size()const;

	float& getSafeElement(int,int)const;

	~Matrix();

private:
	float **matrix;
	int row_size=0;
	int coloumn_size=0;
};
#endif