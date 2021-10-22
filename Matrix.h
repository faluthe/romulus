#pragma once

class Matrix
{
private:
	float matrix[3][4];

public:
	float* operator[](int i)
	{
		return matrix[i];
	}
};

class ViewMatrix
{
private:
	float matrix[4][4];

public:
	float* operator[](int i)
	{
		return matrix[i];
	}
};