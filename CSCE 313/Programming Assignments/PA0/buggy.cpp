#include <iostream>
#include <cstring>
using namespace std;
struct Point {
    int x, y;
    Point () : x(), y() {}
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
    int vertices;
    Point** points;
    double* area_val; // pointer to something 
    public:

        Shape (int _vertices){
            vertices = _vertices;
            points = new Point *[vertices + 1];
            for (int i = 0; i < vertices; i++){
                points[i] = new Point();}
        }

        ~Shape () {
            for (int i = 0; i < vertices; i++) {
                delete points[i]; //deallocate each element of array of pointers container
            }
            delete[] points; //deallocated the array of pointers container
            delete area_val; // once delete is called in main it goes to the the deconstructor to do actual deletion
        }

        void addPoints (Point pts[]) {
            for (int i = 0; i < vertices; i++) {
                memcpy(points[i], &pts[i%vertices], sizeof(Point));  
            }
        }

        double* area () {
            int temp = 0;
            //vertices - 1 because we do not want to go out of bounds in lhs points[i+1]
            for (int i = 0; i < vertices-1; i++) {
                // FIXME: there are two methods to access members of pointers
                //        use one to fix lhs and the other to fix rhs 
                int lhs = points[i]->x * points[i+1]->y;
                int rhs = points[i+1]->x * points[i]->y;
                temp += (lhs - rhs);
            }
            this->area_val = new double(abs(temp)/2.0); // added this to be safe, should work without it as well
            return this->area_val;
        }
};

int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
    //          tri1 = (0, 0)
    //          tri2 = (1, 2)
    //          tri3 = (2, 0)

    // adding points to tri

    // tri-1 : defining use struc method 1
     Point tri1 = {0,0};

    // tri-2 : defining use struc method 2
    struct Point tri2;
    tri2.x = 1;
    tri2.y = 2;
    // tri-3 : defining use struc method 3
     Point tri3 = Point (2,0);

    //adding all points to shape (tri)
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
    //          quad1 = (0, 0)
    //          quad2 = (0, 2)
    //          quad3 = (2, 2)
    //          quad4 = (2, 0)
    Point quad1 = {0,0};
    Point quad2 = {0,2};
    Point quad3 = {2,2};
    Point quad4 = {2,0};
    // adding points to quad
    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    cout << *tri->area() << endl; //dereferencing tri and quad so we can get double value in area bc area() returns pointer
    cout << *quad->area() << endl;

    // delete
    delete quad;
    delete tri;
}
