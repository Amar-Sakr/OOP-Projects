#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

struct point{
    string name;
    float x;
    float y;
    float dis_origin;
   struct point* next;
};

point* start = NULL;
point* finish = NULL;

float dis(float x1,float x2,float y1,float y2);
string nearest(point* start,point *p2);
void swap(struct point *p1,struct point *p2);
void print(struct point *start);
void delete_nodes(point *start);

int main(){

    while(1){
        point* p = new point;
        p->next = NULL;

        if (start == NULL)
            start = p;
        cout<<"string describing obstacle (\"end\" for end of input):";
        cin >> p->name;
        if(p->name == "end")
            break;
        cout << "x and y coordinate: ";
        cin >> p->x >> p->y;
        p->dis_origin = dis(0, p->x, 0, p->y);
        if (finish != NULL)
            finish->next=p;
            finish = p;
    }
    print(start);
    delete_nodes(start);

    return 0;
}


float dis(float x1,float x2,float y1,float y2){
    float d=sqrt(pow((x1-x2),2)+pow((y1-y2),2));
    return d;
}


string nearest(point* start,point* p2){
    point* p=NULL;
    point* temp=NULL;
    double Min=pow(10,10);

    for(point* p=start; p != NULL; p=p->next){
        if(dis(p2->x, p->x, p2->y, p->y) != 0 && dis(p2->x, p->x, p2->y, p->y) < Min){

            Min=dis(p2->x, p->x, p2->y, p->y);
            temp=p;
        }
    }
    return temp->name;
}


void swap(struct point* p1,struct point* p2){
    float dis =p1->dis_origin;
    p1->dis_origin =p2->dis_origin;
    p2->dis_origin =dis;

    float x =p1->x;
    p1->x =p2->x;
    p2->x =x;

    float y =p1->y;
    p1->y =p2->y;
    p2->y =y;

    string name =p1->name;
    p1->name =p2->name;
    p2->name =name;
}


void print(struct point* start){
     int x;
     struct point* p;
     struct point* ptr =NULL;
     if (start == NULL)
        return;

     do
     {
        x =0;
        p =start;
     while (p->next !=ptr)
        {
            if(p->next->dis_origin < p->dis_origin)
            {
                 swap(p, p->next);
                 x =1;
            }
            p =p->next;
        }
        ptr = p;
     } while (x);

     for(point* p =start; p != NULL; p =p->next){
         cout << fixed << showpoint << setprecision(2)<<"obstacle "<<p->name<<": (  "<<p->x<<",\t"<<p->y<<"),\tdistance:  "
         <<dis(0, p->x, 0, p->y)<<"m, nearest to this: "<<nearest(start, p)<<endl;
        }
}


void delete_nodes(point* start){
    point *temp1, *temp2;
    cout << "delete: ";
    for(point* p =start; p != NULL; p =p->next){
        cout <<" "<<p->name<<" ";
    }

    for (temp1 =start; temp1 != NULL; temp1 =temp2){
    temp2 = temp1->next;
    delete temp1;
    }
}

