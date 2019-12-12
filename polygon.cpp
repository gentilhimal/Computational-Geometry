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
	while(n>=0)
	{
		cout <<"("<< temp->point.first<<"," << temp->point.second<<")"<<endl;
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
	int i,j,x1,x2,x3,y1,y2,y3;
	ack[2]='\0';
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
	 if(ack[i+1] !='\0')
	 {
		 if(ack[i]==ack[i+1]) continue;
		 else {
				 cout<<"Its not a convex polygon";
				 break;
		 	  }
	 }
	cout<<ack[i]<<endl;
	index=index->next;
	temp=index;
	i=i+1;
}
while(index != head);

}

char polygon::turn_test(int x1,int y1,int x2,int y2,int x3,int y3)
{
//		cout<<x1<<","<<y1<<endl;
//		cout<<x2<<","<<y2<<endl;
//		cout<<x3<<","<<y3<<endl;
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
	cout<<"Input total no. of vertices in Polygon: ";
	cin>>n;
	cout<<"Input vertices for "<< n <<" sized polygon"<<endl;
	for(int i=0; i<=n-1; i++)
	{
		cout << "Co-ordinates for V"<<i<<": ";
		cin >>x >>y;
		shape.insert_node(x,y);
	}

	shape.circular_link();
	//shape.print(n);
	shape.test_convexity(n);

	return 0;

}
