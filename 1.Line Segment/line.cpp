/*
 * line.cpp
 *
 *  Created on: Nov 12, 2019
 *      Author: himal
 */

#include <iostream>
using namespace std;

class point{
public:
	int x,y;
	void mypoint()
	{
		cout<<"\n\tPoint Implementation \n"<<endl;
		cout<<"\tInput X-coordinate:";
		cin>>x;
		cout<<"\tInput Y-coordinate:";
		cin>>y;
		cout<<"\tpoint in 2-D graph: ("<<x<<","<<y<<")"<<endl;

	}


};

class line_segment{
public:
	int x1,y1,x2,y2;
	void my_line_segment()
	{
		cout<<"\n\tLine Segment Implementation \n"<<endl;
		cout<<"\tInput X-coordinate for P1:";
		cin>>x1;
		cout<<"\tInput Y-coordinate for P1:";
		cin>>y1;
		cout<<"\tInput X-coordinate for P2:";
		cin>>x2;
		cout<<"\tInput Y-coordinate for P2:";
		cin>>y2;
		cout<<"\tLine_Segment in 2-D graph: P1("<<x1<<","<<y1<<") to P2( "<<x2<<","<<y2<<")"<<endl;
	}


};

class point_line{
public:
	int x1,y1,x2,y2,x3,y3;
	float slope1,slope2,slope3;

	void point_line_classication()
	{
		cout<<"\n\tPoint Line Classification \n"<<endl;
		cout<<"\tInput X-coordinate for start P:";
		cin>>x1;
		cout<<"\tInput Y-coordinate for start P:";
		cin>>y1;
		cout<<"\tInput X-coordinate for terminus Q:";
		cin>>x2;
		cout<<"\tInput Y-coordinate for terminus Q:";
		cin>>y2;
		cout<<"\tLine_Segment in PQ is constructed: P("<<x1<<","<<y1<<") to Q("<<x2<<","<<y2<<")"<<endl;
		cout<<"\tInput a point R for checking 5 dimensions of Point Line Classiication"<<endl;
		cout<<"\tInput X-coordinate for start R:";
		cin>>x3;
		cout<<"\tInput Y-coordinate for start R:";
		cin>>y3;

		//checking for collinearity of Point R
		//if area of traingle is 0 then points are collinear

		float a = 0.5*(x1 * (y2 - y3) +  x2 * (y3 - y1) + x3 * (y1 - y2));
		if (a==0)
		{
			check_dimensions();
		}
		else
		{
			cout<<"\tPoints are not collinear"<<endl;
		}

	}


	//checking for 5 dimensions
	void check_dimensions()
			{
				if(((x3==x1) && (y3==y1)))
				{
					cout<<"\tPoint R("<<x3<<","<<y3<<") is Starting Point"<<endl;
				}
				else if ((x3==x2) && (y3==y2))
				{
					cout<<"\tPoint R("<<x3<<","<<y3<<") is Terminus Point"<<endl;
				}
				else if (((x3>=x1) && (x3<=x2)) && ((y3>=y1) && (y3<=y2)))
				{
					cout<<"\tPoint R("<<x3<<","<<y3<<") lies in Between Line Segment PQ " <<endl;
				}
				else if ((x3>=x2) && (y3>=y2))
				{
					cout<<"\tPoint R("<<x3<<","<<y3<<") lies in Beyond Line Segment PQ  "<<endl;
				}
				else
				{
					cout<<"\tPoint R("<<x3<<","<<y3<<") lies in Behind Line Segment PQ "<<endl;
				}

			}
};

int main() {
	int num;

		cout<<"\n\tPress \n\t 1: For Point Implementation \n\t 2: For Line Segment Implementation \n\t 3: For testing 5 Dimensions of Point Line Classification\n\t 4: Terminate the Program\n\t"<<endl;
		cout<<"\tEnter the number...";
		cin>>num;

	switch(num) {
	  case 1:
		  point dot;
		  dot.mypoint();
		  main();
	    break;
	  case 2:
		  line_segment line;
		  line.my_line_segment();
		  main();
	    break;
	  case 3:
		  point_line my_point_line;
		  my_point_line.point_line_classication();
		  main();
	    break;
	  case 4:
		  cout<<"\n \t Program Terminated"<<endl;
		  exit(0);
		  break;

	  default:
	    cout<<"\tInvalid Input"<<endl;
	    main();
	}
  return 0;
}


