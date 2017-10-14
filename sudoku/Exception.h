#pragma once
#include <string>
using namespace std;

class ParametersNumberException:public exception
{
public:
	char* m_msg;

	ParametersNumberException(char* error)
	{
		this->m_msg = error;
	}
};

class FileNotExistException :public exception
{
public:
	char* m_msg;
	FileNotExistException(char* error)
	{
		this->m_msg = error;
	}
};

class NumberOutOfBoundException :public exception
{
public:
	char* m_msg;
	NumberOutOfBoundException(char* error)
	{
		this->m_msg = error;
	}
};

class RParametersException :public exception
{
public:
	char* m_msg;
	RParametersException(char* error)
	{
		this->m_msg = error;
	}
};

class IllegalCharException :public exception
{
public:
	char* m_msg;
	IllegalCharException(char* error)
	{
		this->m_msg = error;
	}
};

class NoSolutionException: public exception
{
public:
	char* m_msg;
	NoSolutionException(char* error)
	{
		this->m_msg = error;
	}
};

class IllegalNumberException : public exception
{
public:
	char* m_msg;
	IllegalNumberException(char* error)
	{
		this->m_msg = error;
	}
};

class ModeException :public exception
{
public:
	char* m_msg;
	ModeException(char* error)
	{
		this->m_msg = error;
	}
};