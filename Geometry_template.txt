#include<bits/stdc++.h>
using namespace std;

typedef long long int LL;
typedef long double LD;

int dx[] = {0, 0, -1, +1};
int dy[] = {+1, -1, 0, 0};


//********.........GEOMETRY.........********

//My edits: double -> LD
//2 lines in halfPlaneIntersection(...)
//all(vector<...>) to (v.begin(), v.end()) -> MinimumEnclosingCircle(3), PolygonStubbing(1)
//Point to PT in GetLineABC(...)
//UNVERIFIED CW and CCW sorting section at the end
//(Should work if we can see every corner from the inside from the center of the minimum enclosing circle)
//PolygonPolygonIntersection(...) function

#define M_PI acos(-1.0)
#define EPS 1e-12
#define NEX(x) ((x+1)%n)
#define PRV(x) ((x-1+n)%n)
#define RAD(x) ((x*M_PI)/180)
#define DEG(x) ((x*180)/M_PI)
#define mp make_pair
const LD PI=acos(-1.0);

inline int dcmp (LD x) { return x < -EPS ? -1 : (x > EPS); }
//inline int dcmp (int x) { return (x>0) - (x<0); }

class PT {
public:
    LD x, y;
    PT() {}
    PT(LD x, LD y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    LD Magnitude() {return sqrt(x*x+y*y);}

    bool operator == (const PT& u) const { return dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0; }
    bool operator != (const PT& u) const { return !(*this == u); }
    bool operator < (const PT& u) const { return dcmp(x - u.x) < 0 || (dcmp(x-u.x)==0 && dcmp(y-u.y) < 0); }
    bool operator > (const PT& u) const { return u < *this; }
    bool operator <= (const PT& u) const { return *this < u || *this == u; }
    bool operator >= (const PT& u) const { return *this > u || *this == u; }
    PT operator + (const PT& u) const { return PT(x + u.x, y + u.y); }
    PT operator - (const PT& u) const { return PT(x - u.x, y - u.y); }
    PT operator * (const LD u) const { return PT(x * u, y * u); }
    PT operator / (const LD u) const { return PT(x / u, y / u); }
    LD operator * (const PT& u) const { return x*u.y - y*u.x; }
};

LD dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
LD dist2(PT p, PT q)   { return dot(p-q,p-q); }
LD dist(PT p, PT q)   { return sqrt(dist2(p,q)); }
LD cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }

LD myAsin(LD val) {
    if(val>1) return PI*0.5;
    if(val<-1) return -PI*0.5;
    return asin(val);
}

LD myAcos(LD val) {
    if(val>1) return 0;
    if(val<-1) return PI;
    return acos(val);
}

ostream &operator<<(ostream &os, const PT &p) {
    os << "(" << p.x << "," << p.y << ")";
}

istream &operator>>(istream &is, PT &p) {
    is >> p.x >> p.y;
    return is;
}

// rotate a point CCW or CW around the origin
PT RotateCCW90(PT p)   { return PT(-p.y,p.x); }
PT RotateCW90(PT p)    { return PT(p.y,-p.x); }

PT RotateCCW(PT p,LD t) {
    return PT(p.x*cos(t)-p.y*sin(t),p.x*sin(t)+p.y*cos(t));
}

PT RotateAroundPointCCW(PT p,PT pivot,LD t) {
    PT trans=p-pivot;
    PT ret=RotateCCW(trans,t);
    ret=ret+pivot;
    return ret;
}

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
    return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

LD DistancePointLine(PT a,PT b,PT c) {
    return dist(c,ProjectPointLine(a,b,c));
}

// project point c onto line segment through a and b
PT ProjectPointSegment(PT a, PT b, PT c) {
    LD r = dot(b-a,b-a);
    if (fabs(r) < EPS) return a;
    r = dot(c-a, b-a)/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}

// compute distance from c to segment between a and b
LD DistancePointSegment(PT a, PT b, PT c) {
    return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
LD DistancePointPlane(LD x, LD y, LD z,
                          LD a, LD b, LD c, LD d)
{
    return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(PT a, PT b, PT c, PT d) {
    return dcmp(cross(b-a, c-d)) == 0;
}

bool LinesCollinear(PT a, PT b, PT c, PT d) {
    return LinesParallel(a, b, c, d)
      && dcmp(cross(a-b, a-c)) == 0
      && dcmp(cross(c-d, c-a)) == 0;
}

//UNTESTED CODE SEGMENT
// determine if line segment from a to b intersects with
// line segment from c to d
bool SegmentsIntersect(PT a, PT b, PT c, PT d) {
    if (LinesCollinear(a, b, c, d)) {
        if (dcmp(dist2(a, c)) == 0 || dcmp(dist2(a, d)) == 0 ||
            dcmp(dist2(b, c)) == 0 || dcmp(dist2(b, d)) == 0) return true;
        if (dcmp(dot(c-a, c-b)) > 0 && dcmp(dot(d-a, d-b)) > 0 && dcmp(dot(c-b, d-b)) > 0)
            return false;
        return true;
    }
    if (dcmp(cross(d-a, b-a)) * dcmp(cross(c-a, b-a)) > 0) return false;
    if (dcmp(cross(a-c, d-c)) * dcmp(cross(b-c, d-c)) > 0) return false;
    return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
PT ComputeLineIntersection(PT a, PT b, PT c, PT d) {
    b=b-a; d=c-d; c=c-a;
    assert(dot(b, b) > EPS && dot(d, d) > EPS);
    return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
PT ComputeCircleCenter(PT a, PT b, PT c) {
    b=(a+b)/2;
    c=(a+c)/2;
    return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

bool PointOnSegment(PT s, PT e, PT p) {
    if(p == s || p == e)    return 1;
    return dcmp(cross(s-p, s-e)) == 0
        && dcmp(dot(PT(s.x-p.x, s.y-p.y), PT(e.x-p.x, e.y-p.y))) < 0;
}

int PointInPolygon(vector < PT > p, PT q) {
    int i, j, cnt = 0;
    int n = p.size();
    for(i = 0, j = n-1; i < n; j = i++) {
        if(PointOnSegment(p[i], p[j], q))
            return 1;
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (LD)(p[j].x-p[i].x)*(q.y-p[i].y)/(LD)(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<PT> &p, PT q) {
    for (int i = 0; i < p.size(); i++)
        if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
            return true;
    return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
//THIS DOESN'T WORK FOR a == b
vector<PT> CircleLineIntersection(PT a, PT b, PT c, LD r) {
    vector<PT> ret;
    b = b-a;
    a = a-c;
    LD A = dot(b, b);
    LD B = dot(a, b);
    LD C = dot(a, a) - r*r;
    LD D = B*B - A*C;
    if (D < -EPS) return ret;
        ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
    if (D > EPS)
        ret.push_back(c+a+b*(-B-sqrt(D))/A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<PT> CircleCircleIntersection(PT a, PT b, LD r, LD R) {
    vector<PT> ret;
    LD d = sqrt(dist2(a, b));
    if (d > r+R || d+min(r, R) < max(r, R)) return ret;
    LD x = (d*d-R*R+r*r)/(2*d);
    LD y = sqrt(r*r-x*x);
    PT v = (b-a)/d;
    ret.push_back(a+v*x + RotateCCW90(v)*y);
    if (y > 0)
        ret.push_back(a+v*x - RotateCCW90(v)*y);
    return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
LD ComputeSignedArea(const vector<PT> &p) {
    LD area = 0;
    for(int i = 0; i < p.size(); i++) {
        int j = (i+1) % p.size();
        area += p[i].x*p[j].y - p[j].x*p[i].y;
    }
    return area / 2.0;
}

LD ComputeArea(const vector<PT> &p) {
    return fabs(ComputeSignedArea(p));
}

LD ShoeLace(vector<PT> &vec) {
    int i,n;
    LD ans=0;
    n=vec.size();
    for(i=0;i<n;i++) ans+=vec[i].x*vec[NEX(i)].y-vec[i].y*vec[NEX(i)].x;
    return fabs(ans)*0.5;
}

PT ComputeCentroid(const vector<PT> &p) {
    PT c(0,0);
    LD scale = 6.0 * ComputeSignedArea(p);
    for (int i = 0; i < p.size(); i++){
        int j = (i+1) % p.size();
        c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
    }
    return c / scale;
}

LD PAngle(PT a,PT b,PT c) { //Returns positive angle abc
    PT temp1(a.x-b.x,a.y-b.y),temp2(c.x-b.x,c.y-b.y);
    LD ans=myAsin((temp1.x*temp2.y-temp1.y*temp2.x)/(temp1.Magnitude()*temp2.Magnitude()));
    if((ans<0&&(temp1.x*temp2.x+temp1.y*temp2.y)<0)||(ans>=0&&(temp1.x*temp2.x+temp1.y*temp2.y)<0))
        ans=PI-ans;
    ans=ans<0?2*PI+ans:ans;
    return ans;
}

LD SignedArea(PT a,PT b,PT c){ //The area is positive if abc is in counter-clockwise direction
    PT temp1(b.x-a.x,b.y-a.y),temp2(c.x-a.x,c.y-a.y);
    return 0.5*(temp1.x*temp2.y-temp1.y*temp2.x);
}

bool XYasscending(PT a,PT b) {
    if(abs(a.x-b.x)<EPS) return a.y<b.y;
    return a.x<b.x;
}

//Makes convex hull in counter-clockwise direction without repeating first point
//undefined if all points in given[] are collinear
//to allow 180' angle replace <= with <
void MakeConvexHull(vector<PT>given,vector<PT>&ans){
    int i,n=given.size(),j=0,k=0;
    vector<PT>U,L;
    ans.clear();
    sort(given.begin(),given.end(),XYasscending);
    for(i=0;i<n;i++){
        while(true){
            if(j<2) break;
            if(SignedArea(L[j-2],L[j-1],given[i])<=EPS) j--;
            else break;
        }
        if(j==L.size()){
            L.push_back(given[i]);
            j++;
        }
        else{
            L[j]=given[i];
            j++;
        }
    }
    for(i=n-1;i>=0;i--){
        while(1){
            if(k<2) break;
            if(SignedArea(U[k-2],U[k-1],given[i])<=EPS) k--;
            else break;
        }
        if(k==U.size()){
            U.push_back(given[i]);
            k++;
        }
        else{
            U[k]=given[i];
            k++;
        }
    }
    for(i=0;i<j-1;i++) ans.push_back(L[i]);
    for(i=0;i<k-1;i++) ans.push_back(U[i]);
}

typedef PT Vector;
typedef vector<PT> Polygon;

struct DirLine {
    PT p;
    Vector v;
    LD ang;
    DirLine () {}
//    DirLine (PT p, Vector v): p(p), v(v) { ang = atan2(v.y, v.x); }
    //adds the left of line p-q
    DirLine (PT p, PT q) { this->p = p; this->v.x = q.x-p.x; this->v.y = q.y-p.y; ang = atan2(v.y, v.x); }
    bool operator < (const DirLine& u) const { return ang < u.ang; }
};

bool getIntersection (PT p, Vector v, PT q, Vector w, PT& o) {
    if (dcmp(cross(v, w)) == 0) return false;
    Vector u = p - q;
    LD k = cross(w, u) / cross(v, w);
    o = p + v * k;
    return true;
}

bool onLeft(DirLine l, PT p) { return dcmp(l.v * (p-l.p)) >= 0; }

int halfPlaneIntersection(DirLine* li, int n, vector<PT>& poly) { // my_edit
    sort(li, li + n);

    int first, last;
    PT* p = new PT[n];
    DirLine* q = new DirLine[n];
    q[first=last=0] = li[0];

    for (int i = 1; i < n; i++) {
        while (first < last && !onLeft(li[i], p[last-1])) last--;
        while (first < last && !onLeft(li[i], p[first])) first++;
        q[++last] = li[i];

        if (dcmp(q[last].v * q[last-1].v) == 0) {
            last--;
            if (onLeft(q[last], li[i].p)) q[last] = li[i];
        }

        if (first < last)
            getIntersection(q[last-1].p, q[last-1].v, q[last].p, q[last].v, p[last-1]);
    }

    while (first < last && !onLeft(q[first], p[last-1])) last--;
    if (last - first <= 1) { delete [] p; delete [] q; return 0; }
    getIntersection(q[last].p, q[last].v, q[first].p, q[first].v, p[last]);
    poly.resize(last - first + 1); // my_edit
    int m = 0;
    for (int i = first; i <= last; i++) poly[m++] = p[i];
    delete [] p; delete [] q;
    return m;
}

// 2nd_part

LD CirclishArea(PT a, PT b, PT cen, LD r) {
    LD ang = fabs(atan2((a-cen).y, (a-cen).x) - atan2((b-cen).y, (b-cen).x));
    if (ang > PI) ang = 2*PI - ang;
    return (ang * r * r) / 2.0;
}
//intersection of circle and triangle
LD CicleTriangleIntersectionArea(PT a, PT b, PT c, LD radius) {
    vector<PT>g = CircleLineIntersection(a, b, c, radius);
    if (b < a) swap(a, b);
    if (g.size() < 2) return CirclishArea(a, b, c, radius);
    else {
        PT l = g[0], r = g[1];
        if (r < l) swap(l, r);
        if (b < l || r < a) return CirclishArea(a, b, c, radius);
        else if (a < l && b < r) return fabs(SignedArea(c, b, l)) + CirclishArea(a, l, c, radius);
        else if (r < b && l < a) return fabs(SignedArea(a, c, r)) + CirclishArea(r, b, c, radius);
        else if (a < l && r < b) return fabs(SignedArea(c, l, r)) + CirclishArea(a, l, c, radius) + CirclishArea(b, r, c, radius);
        else return fabs(SignedArea(a, b, c));
    }
    return 0;
}
//intersection of circle and simple polygon (vertexes in counterclockwise order)
LD CirclePolygonIntersectionArea(vector<PT> &p, PT c, LD r) {
    int i, j, k, n = p.size();
    LD sum = 0;
    for (i = 0; i < p.size(); i++) {
        LD temp = CicleTriangleIntersectionArea(p[i], p[(i+1)%n], c, r);
        LD sign = SignedArea(c, p[i], p[(i+1)%n]);
        if (dcmp(sign) == 1) sum += temp;
        else if (dcmp(sign) == -1) sum -= temp;
    }
    return sum;
}

//returns the left portion of convex polygon u cut by line a---b
vector<PT> CutPolygon(vector<PT> &u, PT a, PT b) {
    vector<PT> ret;
    int n = u.size();
    for (int i = 0; i < n; i++) {
        PT c = u[i], d = u[(i+1)%n];
        if (dcmp((b-a)*(c-a)) >= 0) ret.push_back(c);
        if (ProjectPointLine(a, b, c) == c || ProjectPointLine(a, b, d) == d) continue;
        if (dcmp((b-a)*(d-c)) != 0) {
            PT t;
            getIntersection(a, b-a, c, d-c, t);
            if (PointOnSegment(c, d, t))
                ret.push_back(t);
        }
    }
    return ret;
}

typedef pair < PT, PT > seg_t;

vector<PT> tanCP(PT c, LD r, PT p) {
    LD x = dot(p - c, p - c);
    LD d = x - r * r;
    vector<PT> res;
    if (d < -EPS) return res;
    if (d < 0) d = 0;
    PT q1 = (p - c) * (r * r / x);
    PT q2 = RotateCCW90((p - c) * (-r * sqrt(d) / x));
    res.push_back(c + q1 - q2);
    res.push_back(c + q1 + q2);
    return res;
}
//Always check if the circles are same
vector<seg_t> tanCC(PT c1, LD r1, PT c2, LD r2) {
    vector<seg_t> res;
    if (fabs(r1 - r2) < EPS) {
    PT dir = c2 - c1;
    dir = RotateCCW90(dir * (r1 / dir.Magnitude()));
    res.push_back(seg_t(c1 + dir, c2 + dir));
    res.push_back(seg_t(c1 - dir, c2 - dir));
    } else {
    PT p = ((c1 * -r2) + (c2 * r1)) / (r1 - r2);
    vector<PT> ps = tanCP(c1, r1, p), qs = tanCP(c2, r2, p);
    for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
      res.push_back(seg_t(ps[i], qs[i]));
    }
    }
    PT p = ((c1 * r2) + (c2 * r1)) / (r1 + r2);
    vector<PT> ps = tanCP(c1, r1, p), qs = tanCP(c2, r2, p);
    for (int i = 0; i < ps.size() && i < qs.size(); ++i) {
    res.push_back(seg_t(ps[i], qs[i]));
    }
    return res;
}
//move segment a---b perpendicularly by distance d
pair < PT, PT > MoveSegmentLeft(PT a, PT b, LD d) {
    LD l = dist(a, b);
    PT p = ((RotateCCW90(b - a) * d) / l) + a;
    return mp(p, p + b - a);
}

void GetLineABC(PT A, PT B, LD &a, LD &b, LD &c) {
    a=A.y-B.y; b=B.x-A.x; c=A.x*B.y-A.y*B.x;
}

LD Sector(LD r, LD alpha) {
    return r * r * 0.5 * (alpha - sin(alpha));
}
LD CircleCircleIntersectionArea(LD r1, LD r2, LD d) {
    if (dcmp(d - r1 - r2) != -1) return 0;
    if (dcmp(d + r1 - r2) != 1) return PI * r1 * r1;
    if (dcmp(d + r2 - r1) != 1) return PI * r2 * r2;
    // using law of cosines
    LD ans = Sector(r1, 2 * acos((r1 * r1 + d * d - r2 * r2) / (2.0 * r1 * d)));
    ans += Sector(r2, 2 * acos((r2 * r2 + d * d - r1 * r1) / (2.0 * r2 * d)));
    return ans;
}

//length of common part of polygon p and line s-t, O(nlogn)
LD PolygonStubbing(vector <PT> &p, PT s, PT t) {
    int n = p.size();
    LD sm = 0;
    for(int i=0;i<n;i++) sm+=p[i]*p[(i+1)%n];
    if(dcmp(sm) == -1)reverse(p.begin(), p.end()); // my_edit
    vector< pair<LD,int> >event;
    for(int i=0; i<n; i++) {
        int lef = dcmp(cross(p[i]-s, t-s));
        int rig = dcmp(cross(p[NEX(i)]-s, t-s));
        if(lef == rig) continue;
        LD r = cross(p[NEX(i)]-s, p[NEX(i)]-p[i])/cross(t-s, p[NEX(i)]-p[i]);
        if(lef>rig) event.push_back(make_pair(r,(!lef || !rig ? -1 : -2)));
        else event.push_back(make_pair(r,(!lef || !rig ? 1 : 2)));
    }
    sort(event.begin(),event.end());
    int cnt = 0;
    LD sum = 0,la = 0;
    for(int i=0; i<(int)event.size(); i++) {
        if (cnt>0) sum += event[i].first-la;
        la = event[i].first;
        cnt += event[i].second;
    }
    return sum*(t-s).Magnitude();
}

// Minimum Enclosing Circle Randomized O(n)
// Removing Duplicates takes O(nlogn)

typedef pair < PT, LD > circle;
bool IsInCircle(circle C, PT p) {
    return dcmp(C.second - dist(C.first, p)) >= 0;
}
circle MinimumEnclosingCircle2(vector < PT > &p, int m, int n) {
    circle D = mp((p[m]+p[n])/2.0, dist(p[m], p[n])/2.0);
    for (int i = 0; i < m; i++)
        if (!IsInCircle(D, p[i])) {
            D.first = ComputeCircleCenter(p[i], p[m], p[n]);
            D.second = dist(D.first, p[i]);
        }
    return D;
}
circle MinimumEnclosingCircle1(vector < PT > &p, int n) {
    circle D = mp((p[0]+p[n])/2.0, dist(p[0], p[n])/2.0);
    for (int i = 1; i < n; i++)
        if (!IsInCircle(D, p[i])) {
            D = MinimumEnclosingCircle2(p, i, n);
        }
    return D;
}
//changes vector; sorts and removes duplicate points(complexity bottleneck, unneccessary)
circle MinimumEnclosingCircle(vector < PT > p) {
    srand(time(NULL));
    sort(p.begin(), p.end()); //comment if tle // my_edit
    p.resize(distance(p.begin(), unique(p.begin(), p.end()))); //comment if tle // my_edit
    random_shuffle(p.begin(), p.end()); // my_edit
    if (p.size() == 1) return mp(p[0], 0);
    circle D = mp((p[0]+p[1])/2.0, dist(p[0], p[1])/2.0);
    for (int i = 2; i < p.size(); i++)
        if (!IsInCircle(D, p[i])) {
            D = MinimumEnclosingCircle1(p, i);
        }
    return D;
}

// UNVERIFIED CODE // my_edit
// Should work if we can see every corner from the inside from the center of the minimum enclosing circle
// Sort points clockwise & counterclockwise

PT polygonCenter;

bool less_comp(PT a, PT b)
{
    if (dcmp(a.x - polygonCenter.x) != -1 && dcmp(b.x - polygonCenter.x) == -1)
        return true;
    if (dcmp(a.x - polygonCenter.x) == -1 && dcmp(b.x - polygonCenter.x) != -1)
        return false;
    if (dcmp(a.x - polygonCenter.x) == 0 && dcmp(b.x - polygonCenter.x) == 0) {
        if (dcmp(a.y - polygonCenter.y) != -1 || dcmp(b.y - polygonCenter.y) != -1)
            return a.y > b.y;
        return b.y > a.y;
    }

    // compute the cross product of vectors (polygonCenter -> a) x (polygonCenter -> b)
    LD det = (a.x - polygonCenter.x) * (b.y - polygonCenter.y) - (b.x - polygonCenter.x) * (a.y - polygonCenter.y);
    if (dcmp(det) == -1)
        return true;
    if (dcmp(det) == 1)
        return false;

    // points a and b are on the same line from the polygonCenter
    // check which point is closer to the polygonCenter
    LD d1 = (a.x - polygonCenter.x) * (a.x - polygonCenter.x) + (a.y - polygonCenter.y) * (a.y - polygonCenter.y);
    LD d2 = (b.x - polygonCenter.x) * (b.x - polygonCenter.x) + (b.y - polygonCenter.y) * (b.y - polygonCenter.y);
    return (d1 - d2) == 1; // This line determines what to do if multiple points are on the same "hour.
    // 1 gives furthest first and -1 gives closest first.
}

//This will order the points clockwise starting from the 12 o'clock.
//Points on the same "hour" will be ordered starting from the ones that are further from the center.
void sortCW(vector<PT>& given)
{
    if ((int)given.size() < 3) return;
    polygonCenter = MinimumEnclosingCircle(given).first;
    sort(given.begin(), given.end(), less_comp);
}

//Exactly opposite of sortCW()
void sortCCW(vector<PT>& given)
{
    sortCW(given);
    reverse(given.begin(), given.end());
}

// make sure p1 and p2 are anti-clockwise(because of DirLine)
int PolygonPolygonIntersection(vector<PT> p1, vector<PT> p2, vector<PT>& poly) // my_edit
{
    DirLine d[(int)p1.size()+(int)p2.size()];
    for (int i = 0; i < (int)p1.size(); i++) {
        d[i] = DirLine(p1[i], p1[(i+1)%(int)p1.size()]);
    }
    for (int i = 0; i < (int)p2.size(); i++) {
        d[i+(int)p1.size()] = DirLine(p2[i], p2[(i+1)%(int)p2.size()]);
    }
    int n = halfPlaneIntersection(d, (int)p1.size() + (int)p2.size(), poly);
    sortCCW(poly); // Just to be sure the points are CCW
    return n;
}

// polygon must be clockwise sorted beforehand (use sortCW(..) function)
// strictly inside polygon : -1, on polygon : 0, outside polygon : 1
// complexity : logn
int pointAndConvexPolygonInLogn(const vector<PT>& poly, PT p)
{
    int n = (int)poly.size();
    // if binary search is going to work
    if (poly[0] == p) return 0;
    else if (onLeft(DirLine(poly[0], poly[1]), p) && onLeft(DirLine(poly[n-1], poly[0]), p)) return 1;
    // binary search
    int low = 1, high = n - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        DirLine d(poly[0], poly[mid]);
        if (onLeft(d, p) || dcmp(DistancePointLine(poly[0], poly[mid], p)) == 0) {
            high = mid - 1;
        }
        else {
            low = mid;
        }
    }
    // corner case
    if (low == 1) {
        if (PointOnSegment(poly[0], poly[1], p)) return 0;
        else if (onLeft(DirLine(poly[0], poly[1]), p)) return 1;
    }
    // all other conditions
    if (low == n - 1) {
        return 1;
    }
    else if (low == n - 2) {
        if (PointOnSegment(poly[n-2], poly[n-1], p) || PointOnSegment(poly[0], poly[n-1], p))
            return 0;
        else if (onLeft(DirLine(poly[n-1], poly[n-2]), p))
            return -1;
        else
            return 1;
    }
    else {
        if (PointOnSegment(poly[low], poly[low+1], p))
            return 0;
        else if (onLeft(DirLine(poly[low+1], poly[low]), p))
            return -1;
        else
            return 1;
    }
}

//********.........GEOMETRY.........********

int main()
{
    int co = 0;
    while (1) {
        int n;
        cin >> n;
        if (!n) break;
        vector<PT> given;
        for (int i = 0; i < n; i++) {
            PT temp;
            cin >> temp;
            given.push_back(temp);
        }
        sortCW(given);
        for (int i = 0; i < n; i++) {
            cout << given[i] << endl;
        }
        sortCCW(given);
        for (int i = 0; i < n; i++) {
            cout << given[i] << endl;
        }
    }

    return 0;
}
