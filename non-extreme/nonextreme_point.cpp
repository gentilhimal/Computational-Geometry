#include<iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Point{
    public: int x_cor,y_cor;
    void enterPointCoordinate(){
       cout<<"\t\t\tX-coordinate: ";
       cin>>x_cor;
       cout<<"\t\t\tY-coordinate: ";
       cin>>y_cor;
    }
    void displayPoint(){
        cout<<"("<<x_cor<<" ,"<<y_cor<<")";
    }
};

class TurnTest{
    public: int turn = 0;
    template <class A, class B, class C>
    int turnTest(A& a, B& b, C& c){
        double area;
        area = 0.5*(a.x_cor*(b.y_cor-c.y_cor)+b.x_cor*(c.y_cor-a.y_cor)+c.x_cor*(a.y_cor-b.y_cor));
        if (area > 0)
            turn = 1;
        else if (area < 0)
            turn = -1;
        else
            turn = 0;
        return turn;
    }
};

struct vertex {
    Point info;
    struct vertex *n;
    struct vertex *p;
}*start, *last;
int count = 0;

class polygon: public TurnTest {
    public:
    polygon() {
        start = NULL;
        last = NULL;
    }

    vertex *create_vertex(Point p){
        count++;
        struct vertex *t;
        t = new(struct vertex);
        t->info = p;
        t->n = NULL;
        t->p = NULL;
        return t;
    };

    //Function to insert the point in vertex
    void insert(int n1, int n2){
        Point p;
        p.x_cor = n1;
        p.y_cor = n2;
        struct vertex *t;
        t = create_vertex(p);
        if (start == last && start == NULL) {
            start = last = t;
            start->n= last->n = NULL;
            start->p = last->p= NULL;
        } else {
            last->n= t;
            t->p= last;
            last = t;
            start->p = last;
            last->n= start;
        }
    };

    //Function to sort the given vertices according to slope
    void arrangePolygon(){
        int i, flag, *passedValue, tot=0, poss[count], positions;
        float slope[count];
        struct vertex *s, *p, *n;
        s = start;
        n = s->n;
        p = n->n;
        // Finding the centroid for given vertices
        float xc = 0, yc = 0;
        for (i = 0;i < count;i++) {
            xc = xc + s->info.x_cor;
            yc = yc + s->info.y_cor;
            p = p->n;
            s = s->n;
            n = n->n;
        }
        xc = xc / count;
        yc = yc / count;
        //Finding the slope
        for (i = 0;i < count;i++) {
            float x = s->info.x_cor;
            float y = s->info.y_cor;
            float xd = xc - x;
            float yd = yc - y;
            if(xd>=0 and yd>=0)
				slope[i]=atan((yd)/(xd));
			else if(xd<0 and yd>=0)
				slope[i]=atan((yd)/(xd)) + 3.14;
			else if(xd<=0 and yd<0)
				slope[i]=atan((yd)/(xd)) + 3.14;
			else
				slope[i]=6.28+atan((yd)/(xd)) ;
            p = p->n;
            s = s->n;
            n = n->n;
        }
        //sorting the slope
        float sl[count];
        for(int i=0; i<count; ++i)
            sl[i] = slope[i];
        for(i =0;i<count;i++){
            for(int j =i;j<count;j++){
                if(sl[i]>sl[j]){
                    float temp = sl[j];
                    sl[j]=sl[i];
                    sl[i]=temp;
                }
            }
        }
        Point pal[count];
        //Reordering the vertex points according to slope
        for(i =0;i<count;i++){
            s= start;
            n = s->n;
            p = n->n;
            for(int j =0;j<count;j++){
                if(sl[i] == slope[j]){
                    pal[i] = s->info;
                    break;
                }
                s = s->n;
                n = n->n;
                p = p->n;
            }
        }
        s= start;
        n = s->n;
        p = n->n;
        for(i =0;i<count;i++){
            s->info.x_cor = pal[i].x_cor;
            s->info.y_cor = pal[i].y_cor;
            s = s->n;
            n = n->n;
            p = p->n;

        }
    };

    //Function to Display vertices of polygon
    void display(){
        int i;
        struct vertex *s;
        s = start;
        for (i = 0;i < count-1;i++) {
            s->info.displayPoint();
            cout<<",";
            s = s->n;
        }
        s->info.displayPoint();
    };
};

//Function to test if point lies inside the triangle
int checkTriangleInclusion(Point i, Point j, Point k,Point l){
    int a = 0;
    TurnTest t1;
    int turn1 = t1.turnTest(j, k, i);
    int turn2 = t1.turnTest(k, l, i);
    int turn3 = t1.turnTest(l, j, i);
    if (turn1 == 0 || turn2 == 0 || turn3 == 0){
        a = 0;
    }
    else if (turn1 == turn2 && turn2 == turn3){
        a = 1;
    }
    return a;
}

//Function to eliminate the non extreme points and display the extreme points in sorted order
void nonExtremePointEliminaion(int pnt[][2], int n){
    int i, status[n];
    Point point[n];
    for(i = 0;i < n; i++){
        point[i].x_cor = pnt[i][0];
        point[i].y_cor = pnt[i][1];
    }
    cout<<"\n\n\t n = "<<n;
    for (i = 0; i < n; i++) {
        int triangleCount = 0;
        int count = 0;
        for (int j = 0; j < n ; j++){
            if (i != j){
                for (int k = 0; k < n ; k++){
                    if ( k!=i && i!= j && j!=k){
                        for (int l = 0; l < n ; l++){
                            if (l != i && l != j && l != k && i != j && i != k && j != k){
                                triangleCount++;
                                cout<<"\n\t\tl = "<<l;
                                cout<<"\n\t Triangle count = "<<triangleCount;
                                if(checkTriangleInclusion(point[i],point[j],point[k],point[l]) != 1){
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(triangleCount==count)
            status[i] = 1;
    }
    polygon pol;
    for (i = 0; i < n; i++) {
        if(status[i] == 1){
            pol.insert(point[i].x_cor, point[i].y_cor);
            cout<<"\n\n\t\t x = "<<point[i].x_cor;
            cout<<"\n\n\t\t y = "<<point[i].y_cor;
        }
    }
    cout<<"\n\t The vertices  of convex hull: ";
    pol.display();
    pol.arrangePolygon();
    cout<<"\n\t The vertices of convex hull in sorted form: ";
    pol.display();
};

int main() {
    int choice, convexFlag, intersectionNum, vertexNo;
    char cont;
    polygon pol;


    cout<<"\t\t * 1. Constructing Polygon by non-extreme point elimination. *"<<endl;


    aa:
    cout<<"\n\t Enter the number of points: ";
    cin>>vertexNo;
    if(vertexNo<4){

        cout<<"\n\t\t* Total number of points must be >  3 *";

        goto aa;
    }
    int point[vertexNo][2];
    cout<<"\nEnter the Points: "<<endl;
    for(int i=0;i<vertexNo;i++){
        cout<<"\n\t\tPoint P"<<i<<": "<<endl;
        cout<<"\t\tEnter the X-coordinate: ";
        cin>>point[i][0];
        cout<<"\t\tEnter the Y-coordinate: ";
        cin>>point[i][1];
    }

    cout<<"\t*          Points  inserted !         *"<<endl;

    nonExtremePointEliminaion(point, vertexNo);
   return 0;
}
