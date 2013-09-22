//#ifndef SQUARE_H
//#define SQUARE_H
#include<iostream>

using namespace std;

class square
{
public:
    void set_data(int d);
    int get_data();
    int get_row();
    void set_row(int r);
    int get_column();
    void set_column(int c);
private:
    int data;
    int row;
    int column;
};
//#endif

void square::set_data(int d)
{
	data = d;
}

int square::get_data()
{
	return data;
}

int square::get_row()
{
    return row;
}
void square::set_row(int r)
{
    row = r;
}
int square::get_column()
{
    return column;
}

void square::set_column(int c)
{
    column = c;
}

