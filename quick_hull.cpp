
#include <bits/stdc++.h>
using namespace std;

struct point
{
    int x, y;
};
bool comp(point a, point b)
{  
    return (a.x<b.x);
}
int determinant(point p, point q, point r)
{   
    return (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y);
}
void findPartialHull(vector<point> &arr, vector<point> &result, point p1, point pn)
{
    vector<point> s1 = vector<point>();   //holds points of a part
    for (vector<point>::iterator it = arr.begin(); it < arr.end(); it++)
    {  
        if (determinant(p1,pn,*it) > 0)
        {    
            //if the point is on the left of p1-->pn line put it into the vector
            s1.push_back(*it); 
        }
    }
    if (s1.empty())
    {    
        
        result.push_back(p1);
    } 
    else 
    {    
        float maxDist = 0; 
        point pmax;  
        float dist; 
        float length = sqrt(pow(p1.x - pn.x, 2) + pow(p1.y - pn.y, 2));
        for (vector<point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            dist = determinant(p1,pn,*it) / length; 
            if (dist > maxDist)
            {    
               
                maxDist = dist;
                pmax = *it;
            }
        }
       
        vector<point> s11 = vector<point>(); 
        vector<point> s12 = vector<point>(); 
        for (vector<point>::iterator it = s1.begin(); it < s1.end(); it++)
        {
            
            if (determinant(p1,pmax,*it) > 0)
            {  
                
                s11.push_back(*it);
            } 
            else if (determinant(pmax,pn,*it) > 0)
            {   
                
                s12.push_back(*it);
            }
        }
        findPartialHull(s11, result, p1, pmax); 
        findPartialHull(s12, result, pmax, pn); 
    }
}
int main(){
    int n;
    cin>>n;
    vector<point> P = vector<point>();   
    vector<point> upper = vector<point>();    
    vector<point> lower = vector<point>();   
    for (int i=0;i<n;i++)
    {   
        point p;
        cin>>p.x>>p.y;
        P.push_back(p);
    }
    float t0 = clock();
    sort(P.begin(),P.end(),comp); 
    findPartialHull(P, upper, P[0], P[n-1]);   
    findPartialHull(P, lower, P[n-1], P[0]);  
    sort(upper.begin(),upper.end(),comp); 
    sort(lower.begin(),lower.end(),comp);
    float t1 = clock();
    for (vector<point>::iterator it = upper.begin(); it < upper.end(); it++)
    {  
       
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    for (vector<point>::iterator it = lower.end()-1; it >= lower.begin(); it--)
    {
        
        cout <<"("<< (*it).x<< ", " << (*it).y<<")" << endl;
    }
    cout << "Total time: " << (t1-t0)/CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}
