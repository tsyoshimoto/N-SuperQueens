#include "square.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

int main(int argc, char *argv[])
{
	//variable declarations
	int sol_counter = 0;	 	//counter for how many solutions you have
	bool place_queen = true; 	//boolean used to keep track of the 
	int a,b,p; 		 	//intermediate variables used for the rows and to place down the number of commas in the output
	int i, j; 		 	//used to keep track of the rows and columns
	bool pop_extra = false;		//used to see if the stack that houses the expanded nodes should pop another element
	
	//gathering values from command line and assigning them more meaningful names
	int const Nqueens = atoi(argv[1]); //atoi() changes from type string to int
	
	//opening the output file
	ofstream fout;
	fout.open(argv[2]);
	fout<<"Number of Super Queens: "<<Nqueens<<endl;
	
	//creating the chessboard based on the dimensions given
	square chess_board[Nqueens][Nqueens];
	
	//the main stack to run through the entire chessboard
	stack<square> myStack;
	//stacks used for printing out the queen positions. Using two in order to reverse the order of output
	stack<square> print_list;
	stack<square> temp_print_list; 
	
	//making sure that each element has a starting value of 0 and each element contains its row and column
	for ( int g = 0; g<Nqueens; g++)
	{
		for (int h =0; h<Nqueens; h++)
		{
			chess_board[g][h].set_data(0);
			chess_board[g][h].set_row(h);
            		chess_board[g][h].set_column(g);
		}
	}
	
	//pushing in the initial elements into the stack from the first column
	for (int h =Nqueens-1; h>=0; h--) 
	{
            	myStack.push(chess_board[0][h]);
	}
	
	//iterating through all possible combinations
	//until we go through the last possible starting row in the first column
	while (!myStack.empty())
	{
		//i and j get set the current column and row
		i=myStack.top().get_column();
		j=myStack.top().get_row();
		myStack.pop(); //pop off the current element in stack
		
			for(int k=0;k<Nqueens;k++)
			{
				//for each row in same column its in
				if(chess_board[i][k].get_data()==1)
					place_queen=false; //continue onward in while loop
				//for each column in same row its in
				if(chess_board[k][j].get_data()==1)
					place_queen=false;//continue onward in while loop
			}
					
			///*checking for the diagonals to see if 1*///////////
			//row+1,column+1
			a=i,b=j;
			while(a<Nqueens && b<Nqueens) 
			{
				if(chess_board[a++][b++].get_data()==1)
					place_queen=false;//continue onward in for-loop
			}
			//row+1,column-1
			a=i;b=j;
			while(a>=0 && b<Nqueens) 
			{
				if(chess_board[a--][b++].get_data()==1)
					place_queen=false;//continue onward in for-loop
			}
			//row-1,column+1
			a=i;b=j;
			while(a<Nqueens && b>=0) 
			{
				if(chess_board[a++][b--].get_data()==1)
					place_queen=false;//continue onward in for-loop
			}
			//row-1,column-1
			a=i;b=j;
			while(a>=0 && b>=0) 
			{
				if(chess_board[a--][b--].get_data()==1)
					place_queen=false;//continue onward in for-loop
			}
					
			/////checking the knight moves////////////////////////////////////
			if(chess_board[i+2][j+1].get_data()==1 && (i+2)<Nqueens && (j+1)<Nqueens)
			{
				place_queen = false;
			}
			else if(chess_board[i+2][j-1].get_data()==1 && (i+2)<Nqueens && (j-1)>=0)
			{
				place_queen = false;
			}
			else if(chess_board[i+1][j+2].get_data()==1 && (i+1)<Nqueens && (j+2)<Nqueens)
			{
				place_queen = false;
			}
			else if(chess_board[i-1][j+2].get_data()==1 && (i-1)>=0 && (j+2)<Nqueens)
			{
				place_queen = false;
			}
			else if(chess_board[i-2][j+1].get_data()==1 && (i-2)>=0 && (j+1)<Nqueens)
			{
				place_queen = false;
			}
			else if(chess_board[i-2][j-1].get_data()==1 && (i-2)>=0 && (j-1)>=0)
			{
				place_queen = false;
			}
			else if(chess_board[i+1][j-2].get_data()==1 && (i+1)<Nqueens && (j-2)>=0)
			{
				place_queen = false;
			}
			else if(chess_board[i-1][j-2].get_data()==1 && (i-1)>=0 && (j-2)>=0)
			{
				place_queen = false;
			}
					
			//in case there is a 1 in any of those paths, decides what to do								
			if(!place_queen)
			{
				place_queen = true; //reseting the flag
				if(j==Nqueens-1)    //reaching the final row in a column
				{
					if(i==0) //if it is the last element, just continue because it will end after this anyways
					{
						continue;
					}
					print_list.pop(); //going back a column so the queen cannot be in the position placed in previous column
					for (int y=Nqueens-1;y>=0;y--)
					{
						chess_board[i][y].set_data(0); //set the current columns so there is no queen
						chess_board[i-1][y].set_data(0); //making sure that the column before also has no queen
						//do the following in order to see if the previous column was already expanded on the last row
						if (i>=2)
							if(myStack.top().get_column() == i-2)
							{
								chess_board[i-2][y].set_data(0); //then go back two columns
								pop_extra =true; //have to pop another element because going back two columns
							}	
					}
					if(pop_extra)
					{
						pop_extra = false;
						print_list.pop();
					}
						
				}
				
				continue; //go to the next element in stack
			}
			
			//if reach this far, then we actually place a queen
			chess_board[i][j].set_data(1);
			print_list.push(chess_board[i][j]);	
				
			//checking to see if it should print out to file////
			if (print_list.size()==Nqueens) //if there are n levels for the n Super Queens
			{
				fout<<"Solution "<<++sol_counter<<": ";
				p=0; //initializing to later use for printing the commas
				//putting elements into another stack temporarily
				while(!print_list.empty())
				{
					temp_print_list.push(print_list.top());
					print_list.pop();
				}
				//using this stack to print out the elements so that it goes in increasing column order
				while(!temp_print_list.empty())
				{
					print_list.push(temp_print_list.top());
					//state position of queens & reversing order to make it (row,column) format
					fout<<"("<<Nqueens - temp_print_list.top().get_row()<<","<<temp_print_list.top().get_column() + 1<<")";
					
					if(p<Nqueens-1) //deciding when to put a comma
					{
						fout<<", ";
					}
					p++;
					temp_print_list.pop();
				}
				fout<<endl;
				
				//the last element in the solution changes to 0 so that we can see further solutions
				chess_board[print_list.top().get_column()][print_list.top().get_row()].set_data(0);
				print_list.pop();
				
				if (Nqueens >=2)
				{
					if(myStack.top().get_column() == Nqueens-2) //if previous column was expanded on last row in column already
					{
						chess_board[print_list.top().get_column()][print_list.top().get_row()].set_data(0); //get rid of queen
						print_list.pop();
					}
				}
				continue;		
			}
			//reached this far, then you have put down the queen and moving on to next column by adding on next column elements in stack
			for(int k=Nqueens-1;k>=0;k--)
			{
				myStack.push(chess_board[i+1][k]);
			}
	}
	fout<<"Total number of solutions: "<<sol_counter<<endl; //print number of solutions at end
	fout.close();
	return 0;
}
