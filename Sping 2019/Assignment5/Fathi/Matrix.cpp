#include "Matrix.h"
#include <iostream>
#include <array>
#include <random>
#include <time.h>
using namespace std;

ostream &operator<<(ostream & out,const Matrix& m)
{
    for(int i=0;i<m.row_size;i++)
    {
        for(int j=0;j<m.coloumn_size;j++)
        {
            out<<*(*(m.matrix+i)+j)<<" ";
        }
        out<<endl;
    }
    return out;
}

Matrix::Matrix(int i,int j)
{
    if(i>0&&j>0)
    {
        row_size=i;
        coloumn_size=j;

        matrix=new float*[row_size];
        for(int k=0;k<row_size;k++)
        {
            *(matrix+k)=new float[coloumn_size]{0};
        }
    }
    else
    {
        throw invalid_argument("your params must be bigger than 0 :)");
    }
    
}

Matrix::Matrix(int i,int j,float val)
{
    if(i>0&&j>0)
    {
        row_size=i;
        coloumn_size=j;

        matrix=new float*[row_size];
        for(int k=0;k<row_size;k++)
        {
            *(matrix+k)=new float[coloumn_size];
            for(int y=0;y<coloumn_size;y++)
            {
                *(*(matrix+k)+y)=val;
            }
        }
    }
    else
    {
        throw invalid_argument("your params must be bigger than 0 :)");
    }
}

Matrix::Matrix(int a)
{
    if(a>0)
    {
        row_size=a;
        coloumn_size=a;

        matrix=new float*[row_size];
        for(int k=0;k<row_size;k++)
        {
            *(matrix+k)=new float[coloumn_size]{0};
        }
    }
    else
    {
        throw invalid_argument("your params must be bigger than 0 :)");
    }
    
}
Matrix::Matrix(){}

template<size_t n , size_t m>
Matrix::Matrix(const array<array<float,n>,m> & arr)
{
    if(m>0&&n>0)
    {
        row_size=m;
        coloumn_size=n;
        
        matrix=new float*[row_size];
        for(int k=0;k<row_size;k++)
        {
            *(matrix+k)=new float[coloumn_size];
            for(int y=0;y<coloumn_size;y++)
            {
                *(*(matrix+k)+y)=arr.at(k).at(y);
            }
        }
    }
    else
    {
        throw invalid_argument("your params must be bigger than 0 :)");
    }
    
}

Matrix::~Matrix()
{
    for(int i=0;i<row_size;i++)
    {
        delete []*(matrix+i);
    }
    delete []matrix;
}

Matrix Matrix::eye(int a)
{
    Matrix temp(a,a);
    for(int i=0;i<a;i++)
    {
        temp.at(i,i)=1;
    }
    return temp;
}

Matrix Matrix::rand(int i,int j)
{
    Matrix temp(i,j);
    for(int k=0;k<i;k++)
    {
        for(int y=0;y<j;y++)
        {
            
            temp.at(k,y)=static_cast<double>(random())/RAND_MAX;
        }
    }
    return temp;
}

float &Matrix::get(int i,int j)
{
    return *(*(matrix+i)+j);
}
float &Matrix::at(int i,int j)
{
    if(i<=row_size&&j<=coloumn_size)
    {
        return *(*(matrix+i)+j);
    }
    else
    {
        throw invalid_argument("out of bound :(");
    }
    
}

float &Matrix::operator()(int i,int j)
{
    if(i<=row_size&&j<=coloumn_size)
    {
        return *(*(matrix+i)+j);
    }
    else
    {
        throw invalid_argument("out of bound :(");
    }
}

Matrix Matrix::rowRange(int i,int j)
{
    Matrix temp(j-i+1,coloumn_size);

    for(int k=i;k<=j;k++)
    {
        for(int y=0;y<coloumn_size;y++)
        {
            temp.at(k-i,y)=*(*(matrix+k)+y);
        }
    }
    return temp;
}
Matrix Matrix::colRange(int i,int j)
{
    Matrix temp(row_size,j-i+1);

    for(int k=0;k<row_size;k++)
    {
        for(int y=i;y<=j;y++)
        {
            temp.at(k,y-i)=*(*(matrix+k)+y);
        }
    }
    return temp;
}
int Matrix::rows()const
{
    return row_size;
}
int Matrix::cols()const
{
    return coloumn_size;
}
int Matrix::size()const
{
    return row_size*coloumn_size;
}
float& Matrix::getSafeElement(int i,int j)const
{
    if(i<=row_size&&j<=coloumn_size)
    {
        return *(*(matrix+i)+j);
    }
    else
    {
        throw invalid_argument("out of bound :(");
    }
}
Matrix Matrix::add(const Matrix& mat)const
{
    Matrix temp(row_size,coloumn_size);
    if(row_size==mat.rows()&&coloumn_size==mat.cols())
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                temp.at(k,y)=this->getSafeElement(k,y)+mat.getSafeElement(k,y);
            }
        }       
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}
Matrix Matrix::operator+(const Matrix& mat)const
{
    Matrix temp(row_size,coloumn_size);
    if(row_size==mat.rows()&&coloumn_size==mat.cols())
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                temp.at(k,y)=this->getSafeElement(k,y)+mat.getSafeElement(k,y);
            }
        }       
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}

Matrix Matrix::subtract(const Matrix& mat)const
{
    Matrix temp(row_size,coloumn_size);
    if(row_size==mat.rows()&&coloumn_size==mat.cols())
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                temp.at(k,y)=this->getSafeElement(k,y)-mat.getSafeElement(k,y);
            }
        }       
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}
Matrix Matrix::operator-(const Matrix& mat)const
{
    Matrix temp(row_size,coloumn_size);
    if(row_size==mat.rows()&&coloumn_size==mat.cols())
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                temp.at(k,y)=this->getSafeElement(k,y)-mat.getSafeElement(k,y);
            }
        }       
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}
const Matrix &Matrix::operator=(const Matrix & mat)
{
    if(row_size==mat.rows()&&coloumn_size==mat.cols())
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                this->at(k,y)=mat.getSafeElement(k,y);
            }
        }       
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return *this;
}

Matrix Matrix::mul(const int &a)const
{
    Matrix temp(row_size,coloumn_size);

    for(int k=0;k<row_size;k++)
    {
        for(int y=0;y<coloumn_size;y++)
        {
            temp.at(k,y)=this->getSafeElement(k,y)*a;
        }
    } 
    return temp;
}
Matrix Matrix::operator*(const int &a)const
{
    Matrix temp(row_size,coloumn_size);

    for(int k=0;k<row_size;k++)
    {
        for(int y=0;y<coloumn_size;y++)
        {
            temp.at(k,y)=this->getSafeElement(k,y)*a;
        }
    } 
    return temp;
}

Matrix Matrix::mul(const Matrix &mat)const
{
    Matrix temp(this->rows(),mat.cols());
    if(this->cols()==mat.rows()&&mat.cols()>0&&mat.rows()>0)
    {
        for(int i=0;i<this->rows();i++)
        {
            for(int j=0;j<mat.cols();j++)
            {
                for(int k=0;k<this->cols();k++)
                {
                    temp.at(i,j)+=this->getSafeElement(i,k)*mat.getSafeElement(k,j);
                }
            }
        }
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}
Matrix Matrix::operator*(const Matrix &mat)const
{
    Matrix temp(this->rows(),mat.cols());
    if(this->cols()==mat.rows()&&mat.cols()>0&&mat.rows()>0)
    {
        for(int i=0;i<this->rows();i++)
        {
            for(int j=0;j<mat.cols();j++)
            {
                for(int k=0;k<this->cols();k++)
                {
                    temp.at(i,j)+=this->getSafeElement(i,k)*mat.getSafeElement(k,j);
                }
            }
        }
    }
    else
    {
        throw invalid_argument("row or coloumns not match :(");
    }
    return temp;
}

Matrix Matrix::power(int a)const
{
    Matrix temp=Matrix::eye(row_size);
    if(a>0&&row_size==coloumn_size)
    {
        for(int i=0;i<a;i++)
        {
            temp=(*this)*temp;
        }
    }
    else
    {
        throw invalid_argument("wrong power ._.");
    }
    return temp;
}
Matrix Matrix::operator^(int a)const
{
    Matrix temp=Matrix::eye(row_size);
    if(a>0&&row_size==coloumn_size)
    {
        for(int i=0;i<a;i++)
        {
            temp=(*this)*temp;
        }
    }
    else
    {
        throw invalid_argument("wrong power ._.");
    }
    return temp;
}

bool Matrix::operator==(const Matrix& mat)const
{
    if(this->row_size!=mat.rows()||this->coloumn_size!=mat.cols()) return false;
    else
    {
        for(int k=0;k<row_size;k++)
        {
            for(int y=0;y<coloumn_size;y++)
            {
                if(this->getSafeElement(k,y)!=mat.getSafeElement(k,y)) return false;
            }
        }  
        return true;
    }
    
}

Matrix Matrix::operator~()const
{
    Matrix temp(coloumn_size,row_size);
    for(int k=0;k<row_size;k++)
    {
        for(int y=0;y<coloumn_size;y++)
        {
            temp.at(y,k)=this->getSafeElement(k,y);
        }
    }  
    return temp;
}
Matrix Matrix::transpose()const
{
    Matrix temp(coloumn_size,row_size);
    for(int k=0;k<row_size;k++)
    {
        for(int y=0;y<coloumn_size;y++)
        {
            temp.at(y,k)=this->getSafeElement(k,y);
        }
    }  
    return temp;
}
int main()
{
    srand(time(NULL));
    Matrix A(2);
    cout<<A<<endl;
    array<array<float,2>,4> a={1,2,3,4,5,6,7,8};
    array<array<float,2>,4> b={8,7,6,5,4,3,2,1};
    Matrix B(a);
    Matrix C(b);
    cout<<B<<endl;
    cout<<C<<endl;
    cout<<~C<<endl;
    cout<<C.transpose()<<endl;

    /*cout<<B.get(0,0)<<endl;
    B.at(0,0)=5;
    cout<<B<<endl;
    B(1,1)=10;
    cout<<B<<endl;
    cout<<B(1,1)<<endl;*/

    /*cout<<B.rowRange(1,2)<<endl;
    cout<<B.colRange(1,1).size()<<endl;
    cout<<C+B<<endl;
    cout<<Matrix::eye(5)<<endl;
    cout<<Matrix::rand(4,2)<<endl;*/

    /*cout<<C<<endl;
    B=C;
    cout<<B<<endl;
    cout<<C<<endl;
    cout<<C*2<<endl;*/

    /*Matrix A=Matrix::eye(4);
    Matrix B=Matrix::rand(4,4);
    cout<<B<<endl;
    cout<<B*A<<endl;
    cout<<(B^3)<<endl;
    A=B;
    if(A==B)
    {
        cout<<"are"<<endl;
    }*/
    return 0;
}