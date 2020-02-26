#include <iostream>
#include <utility>
#include <cmath>
using namespace std;
class polygon{
public:
	struct node
	{
		struct node* prev;
		struct node* next;
		std::pair<int,int> point;
	};

	struct node* head; //global variable pointer to head node
	struct node* new_node;//global variable pointer to new node

	//creates a new node and returns a pointer to it
	struct node* get_new_node(int x, int y)
	{
		struct node* new_node = (struct node*) malloc (sizeof(struct node));
		new_node->point.first = x;
		new_node->point.second = y;
		new_node->prev = NULL;
		new_node->next = NULL;
		return new_node;
	}

	void insert_node(int, int);//insert a node at linked list
	void circular_link();//links last node and head node;
	void print(int);//prints all the nodes in forward traversal order
	void test_convexity(int);//checks polygon is convex or not
	char turn_test(int, int, int, int, int, int);//checks the let or right turn of adjacent edges of polygon
	void point_inclusion(int);//checks whether a point lies inside the convex polygon or not
	void ray_casting(int);//checks whether a point lies inside non-convex polygon or not
	float *sort(float a[],int n);

};

float *polygon::sort(float a[], int n)
{
	 static float b[10];
	 int i, j, min;
	 float temp;
	    for (i = 0; i < n - 1; i++) {
	       min = i;
	       for (j = i + 1; j < n; j++)
	          if (a[j] < a[min])
	             min = j;
	       temp = a[i];
	       a[i] = a[min];
	       a[min] = temp;
}
	    for (i = 0; i < n ; i++)
	    {
	    	b[i]=a[i];
	    }
	    return b;
}

void polygon::insert_node(int x, int y)
	{
		struct node* temp = head;
		new_node = get_new_node(x,y);

		if(head == NULL)
			{
				head=new_node;
				return;
			}

		while(temp->next != NULL)  temp=temp->next; // Go to last node

			temp->next = new_node;
			new_node->prev = temp;
	}

void polygon::circular_link()
{
	struct node* temp = head;
	temp->prev=new_node;
	new_node->next=temp;
}

void polygon::print(int n)
{
	struct node* temp = head;
	cout<<"\n\tPolygon is Constructed with vertices: ";
	while(n>=1)
	{
		cout <<"("<< temp->point.first<<"," << temp->point.second<<")";
		temp=temp->next;
		n=n-1;
	}
}

void polygon::test_convexity(int n)
{
		struct node* temp =head;
		struct node* index =head;
		int* x_test=new int[2];
		int* y_test=new int[2];
		char* ack=new char[n];
		int i=0,j,x1,x2,x3,y1,y2,y3,flag;
	do
	{

		for(j=0; j<=2; j++)
		{

			x_test[j]=temp->point.first;
			y_test[j]=temp->point.second;
			temp=temp->next;
		}

		 x1=x_test[0],x2=x_test[1],x3=x_test[2];
		 y1=y_test[0],y2=y_test[1],y3=y_test[2];

		 ack[i] = this->turn_test(x1,y1,x2,y2,x3,y3);

		 if(i>=1)
		 {
			 if(ack[i]!=ack[i-1])
			 {
			 flag = 1;
			 cout<<"\n\n\tConstructed Polygon is not convex"<<endl;
			 cout<<"\n\tPoint Inclusion Test for Non-Convex Polygon using Ray Casting"<<endl;
			 this->ray_casting(n);
			 break;
			 }
		 }

		index=index->next;
		temp=index;
		i=i+1;
	}

	while(index != head);

		if(flag != 1)
		{
		cout<<"\n\n\tConstructed Polygon is convex"<<endl;
		cout<<"\n\tPoint Inclusion Test for Convex Polygon using Turn Test"<<endl;
		this->point_inclusion(n);
		}
}

void polygon::point_inclusion(int n)
{
	struct node* temp =head;
	struct node* index =head;
	int* x_test=new int[1];
	int* y_test=new int[1];
	char* ack=new char[n];
	int i=0,j,x1,x2,x3,y1,y2,y3,flag;

	cout<<"\n\tEnter the co-ordinates for point Q: ";
	cin>>x3>>y3;
do
{
	for(j=0; j<=1; j++)
	{
		x_test[j]=temp->point.first;
		y_test[j]=temp->point.second;
		temp=temp->next;
	}

	 x1=x_test[0],x2=x_test[1];
	 y1=y_test[0],y2=y_test[1];

	 ack[i] = this->turn_test(x1,y1,x2,y2,x3,y3);

	 if(i>=1)
	 {
		 if(ack[i]!=ack[i-1])
		 {
		 flag = 1;
		 cout<<"\n\tPoint does not falls inside Polygon!!!"<<endl;
		 break;
		 }
	 }

	index=index->next;
	temp=index;
	i=i+1;
}

while(index != head);

	if(flag != 1)
	{
	cout<<"\n\tPoint falls inside Polygon!!!"<<endl;
	}
}

void polygon::ray_casting(int n)
{
		struct node* temp =head;
		struct node* index =head;
		int* x_test=new int[1];
		int* y_test=new int[1];
		int j,x1,x2,x3,y1,y2,y3,x4,y4,flag=0;

		cout<<"\n\tEnter the co-ordinates for point Q: ";
		cin>>x3>>y3;
		cout<<"\n\tEnter the terminus point for ray: ";
		cin>>x4>>y4;
	do
	{
		for(j=0; j<=1; j++)
		{
			x_test[j]=temp->point.first;
			y_test[j]=temp->point.second;
			temp=temp->next;
		}

		 x1=x_test[0],x2=x_test[1];
		 y1=y_test[0],y2=y_test[1];

		 char LT1= this->turn_test(x1,y1,x2,y2,x3,y3);
		 char LT2= this->turn_test(x1,y1,x2,y2,x4,y4);
		 char RT1= this->turn_test(x3,y3,x4,y4,x1,y1);
		 char RT2= this->turn_test(x3,y3,x4,y4,x2,y2);

		 if ( ( (LT1=='L' and LT2=='R') or (LT1=='R' and LT2=='L') ) and ( (RT1=='R' and RT2=='L') or (RT1=='L' and RT2=='R') ) )
			 {
			 flag =flag+ 1;
			 }

		index=index->next;
		temp=index;
	}

	while(index != head);


		if((flag % 2) == 1) cout<<"\n\tPoint falls inside Non-Convex Polygon!!!"<<endl;
		else cout<<"\n\tPoint does not falls inside Non-Convex Polygon!!!"<<endl;
}

char polygon::turn_test(int x1,int y1,int x2,int y2,int x3,int y3)
{
	float ar = 0.5*(x1 * (y2 - y3) +  x2 * (y3 - y1) + x3 * (y1 - y2));
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





int main()
{
	polygon shape;
	shape.head = NULL;
	int n,x,y,k,x_sum=0,y_sum=0;
	float cen_x=0,cen_y=0;
	cout<<"\n\n\tPoint Inclusion Test For Convex and Non-Convex Polygon"<<endl;
	cout<<"\n\tInput total no. of vertices in Polygon: ";
	cin>>n;
	cout<<"\n\tInput vertices for "<< n <<" sized polygon"<<endl;
	float points[n][2],g_points[n][2];
	float p_angles[n],sorted[n],unsorted[n];
	int index[n],p_sorted[n][2];
	for(int i=0; i<n; i++)
	{
		cout << "\tCo-ordinates for V"<<i<<": ";
		cin >>x >>y;
		points[i][0]=x;
		points[i][1]=y;

		x_sum = x_sum + points[i][0];
		y_sum = y_sum + points[i][1];

	}
	 cen_x=(x_sum)/(float)n;
	 cen_y=(y_sum)/(float)n;

	for(int i=0; i<n; i++)
	{
		g_points[i][0]=cen_x-points[i][0];
		g_points[i][1]=cen_y-points[i][1];
		//cout<<points[i][0]<<","<<points[i][1]<<endl;
			if(g_points[i][0]>=0 and g_points[i][1]>=0)
			{
				p_angles[i]=atan((g_points[i][1])/(g_points[i][0]));
			}
			else if(g_points[i][0]<0 and g_points[i][1]>=0)
			{
				p_angles[i]=atan((g_points[i][1])/(g_points[i][0])) + 3.14;
			}
			else if(g_points[i][0]<=0 and g_points[i][1]<0)
			{
				p_angles[i]=atan((g_points[i][1])/(g_points[i][0])) + 3.14;
			}
			else
			{
				p_angles[i]=6.28+atan((g_points[i][1])/(g_points[i][0])) ;
			}
			cout<<p_angles[i]<<endl;
	}
	for (int i=0;i<n;i++)
	{
		unsorted[i]=p_angles[i];
	}

float *p;
p = shape.sort(p_angles,n);
for (int i=0;i<n;i++)
{
	 sorted[i]=*(p+i);
	 cout<<sorted[i]<<endl;
}
for (int i=0;i<n;i++)
{
	for(int j=0;j<n;j++)
	{
		if(sorted[i]==unsorted[j])
		{
			index[i]=j;
			break;
		}
	}
}

for (int i=0;i<n;i++)
{
	k=index[i];
	p_sorted[i][0]=points[k][0];
	p_sorted[i][1]=points[k][1];
	shape.insert_node(p_sorted[i][0],p_sorted[i][1]);
}


	shape.circular_link();
	shape.print(n);
	shape.test_convexity(n);
	main();

	return 0;

}
