#include <iostream>
#include <utility>
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
};


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
	int n,x,y;
	cout<<"\n\n\tPoint Inclusion Test For Convex and Non-Convex Polygon"<<endl;
	cout<<"\n\tInput total no. of vertices in Polygon: ";
	cin>>n;
	cout<<"\n\tInput vertices for "<< n <<" sized polygon"<<endl;
	for(int i=0; i<=n-1; i++)
	{
		cout << "\tCo-ordinates for V"<<i<<": ";
		cin >>x >>y;
		shape.insert_node(x,y);
	}

	shape.circular_link();
	shape.print(n);
	shape.test_convexity(n);
	main();

	return 0;

}
