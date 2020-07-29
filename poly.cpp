// Given a polygon and a point 'p', find if 'p' lies inside the polygon or not. The points lying on the border are considered inside.
#include<iostream>
using namespace std;
struct Point {
   int x, y;
};
struct line {
   Point p1, p2;
};

bool OnTheLine(line l1, Point p) {        //check whether p is on the line or not
   if(p.x <= max(l1.p1.x, l1.p2.x) && p.x <= min(l1.p1.x, l1.p2.x) &&
      (p.y <= max(l1.p1.y, l1.p2.y) && p.y <= min(l1.p1.y, l1.p2.y)))
         return true;

   return false;
}
int direction(Point a, Point b, Point c) {
   int val = (b.y-a.y)*(c.x-b.x)-(b.x-a.x)*(c.y-b.y);
   if (val == 0)
      return 0;           //colinear
   else if(val < 0)
      return 2;          //anti clockwise direction
      return 1;          //clockwise direction
}

bool intersection(line l1, line l2) {
   //four direction for two lines and points of other line
   int dir1 = direction(l1.p1, l1.p2, l2.p1);
   int dir2 = direction(l1.p1, l1.p2, l2.p2);
   int dir3 = direction(l2.p1, l2.p2, l1.p1);
   int dir4 = direction(l2.p1, l2.p2, l1.p2);

   if(dir1 != dir2 && dir3 != dir4)
      return true;           //they are intersecting
   if(dir1==0 && OnTheLine(l1, l2.p1))        //when p2 of line2 are on the line1
      return true;
   if(dir2==0 && OnTheLine(l1, l2.p2))         //when p1 of line2 are on the line1
      return true;
   if(dir3==0 && OnTheLine(l2, l1.p1))       //when p2 of line1 are on the line2
      return true;
   if(dir4==0 && OnTheLine(l2, l1.p2)) //when p1 of line1 are on the line2
      return true;
   return false;
}

bool checkInside(Point poly[], int n, Point p) {
   if(n < 3)
      return false;                  //when polygon has less than 3 edge, it is not polygon
   line exline = {p, {9999, p.y}};   //create a point at infinity, y is same as point p
   int count = 0;
   int i = 0;
   do {
      line side = {poly[i], poly[(i+1)%n]};     //forming a line from two consecutive points of poly
      if(intersection(side, exline)) {          //if side is intersects exline
         if(direction(side.p1, p, side.p2) == 0)
            return OnTheLine(side, p);
         count++;
      }
      i = (i+1)%n;
   } while(i != 0);
      return count&1;             //when count is odd
}

int main() {
   int i,n;
	cout<<"\nEnter number of vertices:";
	cin>>n;
	Point polygon[n];
	for(i=0;i<n;i++){
		cout<<"\n Enter the details of "<< i+1 <<"Point";
			cout<<"\n\t enter x value:";
			cin>>polygon[i].x;
			cout<<"\n\t Enter y value:";
			cin>>polygon[i].y;
			}
Point p;
	cout<<"Enter the point to be checked:";
	cin>>p.x;
	cin>>p.y;
		if(checkInside(polygon,n,p))
			cout<<"point is inside\n";
		else
			cout<<"Point is outside\n";
}





