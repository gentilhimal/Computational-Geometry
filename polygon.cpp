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
	struct node* new_node;

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

	//insert a node at linked list
	void insert_node(int x, int y)
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

void circular_link()
{
	struct node* temp = head;
	temp->prev=new_node;
	new_node->next=temp;

}
	//Prints all the elements in linked list in forward traversal order
	void print(int n)
	{
	struct node* temp = head;
		while(n>=0)
		{
			cout <<"("<< temp->point.first<<"," << temp->point.second<<")"<<endl;
			temp=temp->next;
			n=--n ;
		}
	}
};

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
		cout << "Co-ordinates for v"<<i<<": ";
		cin >>x >>y;
		shape.insert_node(x,y);
	}

	shape.circular_link();
	shape.print(n);

	return 0;

}
