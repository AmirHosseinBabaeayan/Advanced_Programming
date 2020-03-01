// 3d_4d_array_impelimention.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <math.h>
using namespace std;
//image functions
int *** createImage(short int coloumn, short int row)
{
	int *** image;
	image = new int**[row];
	for (int j = 0; j < row; j++)
	{
		*(image + j) = new int*[coloumn];
		for (int i = 0; i < coloumn; i++)
		{
			*(*(image + j) + i) = new int[3];
			for (int k = 0; k < 3; k++)
			{
				*(*(*(image + j) + i) + k) = rand() % 256;
			}
		}
	}
	return image;
}

void display(const int *const*const* image, short int coloumn, short int row)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			cout << "[ ";
			for (int k = 0; k < 3; k++)
			{
				cout <<setw(3)<<left <<*(*(*(image + i) + j) + k) << " ";
			}
			cout << "]";
		}
		cout << endl;
	}
	cout << "\n\n\n";
}
int*** addImage(const int*const*const*img1, const int*const*const*img2, int coloumn, int row)
{
	int ***image_temp=createImage(coloumn,row);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				*(*(*(image_temp + i) + j) + k) = *(*(*(img1 + i) + j) + k) + *(*(*(img2 + i) + j) + k);
			}
		}
	}
	return image_temp;
}
int*** diffImage(const int*const*const*img1, const int*const*const*img2, int coloumn, int row)
{
	int ***image_temp2 = createImage(coloumn,row);
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < coloumn; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				*(*(*(image_temp2 + i) + j) + k) =abs(*(*(*(img1 + i) + j) + k) - *(*(*(img2 + i) + j) + k));
			}
		}
	}
	return image_temp2;
}
void rotateImage(const int*** &image, int coloumn, int row)
{
	int ***temp = createImage(row, coloumn);
	//free(image);
	cout << "\n\n\n";
	for (int i = coloumn - 1; i >= 0; i--)
	{
		for (int j = 0; j < row; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				*(*(*(temp + coloumn - i - 1) + j) + k) = *(*(*(image + j) + i) + k);
			}
		}
	}
	const_cast<int***&>(image) = temp;
}
//videos functions
int **** createVideo(int number, int coloumn, int row)
{
	int ****video;
	video = new int***[number];
	for (int r = 0; r < number; r++)
	{
		*(video + r) = new int**[row];
		for (int i = 0; i < row; i++)
		{
			*(*(video + r) + i) = new int*[coloumn];
			for (int j = 0; j < coloumn; j++)
			{
				*(*(*(video + r) + i) + j) = new int[3];
				for (int k = 0; k < 3; k++)
				{
					*(*(*(*(video + r) + i) + j) + k) = rand() % 256;
				}
			}
		}
	}
	return video;
}
void display(const int*const*const*const*video, int number, int coloumn, int row)
{
	for (int r = 0; r < number; r++)
	{
		cout << "frame " << r + 1 << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < coloumn; j++)
			{
				cout << "[ ";
				for (int k = 0; k < 3; k++)
				{
					cout <<setw(3)<<left<<*(*(*(*(video + r) + i) + j) + k) << " ";
				}
				cout << "]";
			}
			cout << endl;
		}
		cout << "\n\n\n";
	}
}
void swapFrame(const int****&video, int f1, int f2)
{
	const int ***frame_temp;
	frame_temp = *(video + f1 - 1);
	*(video + f1 - 1) = *(video + f2 - 1);
	*(video + f2 - 1) = frame_temp;
	//video[0][0][0][0] = 22;
}
//free memory
void freeMemory(int ***&image, int coloumn, int row)
{
	for (int j = 0; j < row; j++)
	{
		for (int i = 0; i < coloumn; i++)
		{
			free(*(*(image + j) + i));
		}
	}
	cout << "(image)memory released :)" << endl;
}
void freeMemory(int ****&video, int number, int coloumn, int row)
{
	for (int r = 0; r < number; r++)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < coloumn; j++)
			{
				free(*(*(*(video + r) + i) + j));
			}
		}
	}
	cout << "(video)memory released :)" << endl;
}
int main()
{
	srand(static_cast<unsigned int>(time(NULL)));
	//image
	int***image1;
	image1 = createImage(3, 5);
	int***image2;
	image2 = createImage(3, 5);
	display(image1,3,5);
	display(image2, 3, 5);

	int*** image_sum = addImage(image1, image2, 3, 5);
	display(image_sum, 3, 5);

	int*** image_diff = diffImage(image1, image2, 3, 5);
	display(image_diff, 3, 5);

	rotateImage(const_cast<const int***&>(image1), 3, 5);
	display(image1, 5, 3);

	//video
	int ****video;
	video = createVideo(3, 3, 4);
	display(video, 3, 3, 4);

	swapFrame(const_cast<const int****&>(video), 1, 3);
	display(video, 3, 3, 4);

	//released memory
	freeMemory(image1, 5, 3);
	freeMemory(image2, 3, 5);
	freeMemory(video, 3, 3, 4);
	cin.get();
	return 0;
}

