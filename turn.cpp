/*
 * turn.cpp
 *
 *  Created on: Nov 19, 2019
 *      Author: himal
 */
#include <iostream>
using namespace std;

class area{
public:
	float ar;
	void turn_data(int*, int*, int*, int*, int*, int*);
	float calculate(int , int , int , int , int , int );
	char decide(float);
	void notify(char);

};

class intersection:public area{
public:
	void get_data(int*, int*, int*, int*, int*, int*, int*, int*);
	void decision(char,char,char,char);
};

void area::turn_data(int *x1, int *y1,int *x2, int *y2,int *x3, int *y3)
{
	cout<<"\t Enter the co-ordinate for P0:";
			cin >> *x1 >> *y1;
			cout<<"\t Enter the co-ordinate for P1:";
			cin >> *x2 >> *y2;
			cout<<"\t Enter the co-ordinate for P2:";
			cin >> *x3 >> *y3;
}

float area::calculate(int x1, int y1, int x2, int y2, int x3, int y3)
{

	 ar = 0.5*(x1 * (y2 - y3) +  x2 * (y3 - y1) + x3 * (y1 - y2));
	 return ar;

}

char area::decide(float ar)
{
	if (ar > 0)
	{
		return 'L';
	}
	else if (ar < 0)
	{
		return 'R';
	}
	else
	{
		return 'C';
	}
}

void area::notify(char I)
{
	if (I=='L')
	{
		cout<<"\n\tP0 P1 P2 has Left Turn";
	}
	else if (I=='R')
	{
		cout<<"\n\tP0 P1 P2 has Right Turn";
	}
	else
	{
		cout<<"\n\tP0 P1 P2 are Collinear";
	}
}

void intersection::get_data(int *x1,int *y1, int *x2, int *y2, int *x3, int *y3,int *x4, int *y4)
{
	cout<<"\n\tInput co-ordinates for line segment AB: ";
	cin>>*x1>>*y1>>*x2>>*y2;
	cout<<"\n\tInput co-ordinate for line segment CD: ";
	cin>>*x3>>*y3>>*x4>>*y4;

}

void intersection::decision(char LT1,char LT2,char RT1,char RT2)
{

	if ( ( (LT1=='L' and LT2=='R') or (LT1=='R' and LT2=='L') ) and ( (RT1=='R' and RT2=='L') or (RT1=='L' and RT2=='R') ) )
	{
		cout<<"\n\tLine Segment AB and CD Intersect each other ! "<<endl;
	}
	else if( ( (LT1=='L' and LT2=='L') or (LT1=='R' and LT2=='R') ) and ( (RT1=='R' and RT2=='R') or (RT1=='L' and RT2=='L') ) )
	{
		//check for collinearity and check or betweenness
	}
	else if(LT1=='C' and LT2=='C')
	{
		cout<<"\n\tLine Segment AB and CD are Collinear !"<<endl;
	}
	else
	{
		cout<<"\n\tLine Segment AB and CD do not Intersect each other ! "<<endl;
	}
}

int main()
{

	char I,LT1,LT2,RT1,RT2;
	float ar,L1,L2,R1,R2;
	int n,x1,y1,x2,y2,x3,y3,x4,y4;

	cout<<"\t \n\n Please Select"<<endl;
	cout<<"\t \t 1: For Turn Test"<<endl;
	cout<<"\t \t 2: For Line Segment Intersection Test"<<endl;
	cout<<"\t \t 3: For Program Termination"<<endl;
	cout<<"\t Enter number .....";
	cin>>n;

	switch(n)
	{
	case 1:
		cout<<"\n\n\t\t Turn Test\n"<<endl;
		area turn;
		turn.turn_data(&x1,&y1,&x2,&y2,&x3,&y3);

		ar = turn.calculate(x1,y1,x2,y2,x3,y3);
		I = turn.decide(ar);

		turn.notify(I);
		main();
		break;
	case 2:
		cout<<"\n\n\t \tLine Segment Intersection Test\n"<<endl;
		intersection line;
		line.get_data(&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);

		intersection ack;
		L1=ack.calculate(x1,y1,x2,y2,x3,y3);
		L2=ack.calculate(x1,y1,x2,y2,x4,y4);
		R1=ack.calculate(x3,y3,x4,y4,x1,y1);
		R2=ack.calculate(x3,y3,x4,y4,x2,y2);
		LT1=ack.decide(L1);
		LT2=ack.decide(L2);
		RT1=ack.decide(R1);
		RT2=ack.decide(R2);

		ack.decision(LT1,LT2,RT1,RT2);

		main();
		break;
	case 3:
		  cout<<"\n \t \tProgram Terminated"<<endl;
		  exit(0);
		  break;
	default:
		cout<<"\n \t \tInvalid Input"<<endl;
		main();
		break;
	}

	return 0;

}



