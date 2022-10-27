/**
 * Author: Kamil Debowski, Grzegorz Gawryał
 * Date: 2022-10-26
 * License: Boost Software License
 * Source: https://github.com/mareksom/acmlib/blob/master/code/kamil/halfplanes.cpp
 * Description: Online half plane intersection. Works both for ll and long double.
 * Bounding box is optional, but needed for distinguishing bounded vs unbounded.
 * Halfplanes are sorted ccw in HPI.s. Time: O(log n) per add. 
 */
#pragma once

#include "Point.h"

typedef long long T; //comparing slopes etc
typedef Point<T> P; //only cross needed
typedef long double ld; // computing intersections
const ld EPS = 1e-12; //works for |pts| <= 10^6

struct Line { //coords <= 10^9 for abc constructor and <= 10^6 for p,q
	T a,b,c; 
	Line(T a_=0, T b_=0, T c_=0): a(a_), b(b_), c(c_) {} //ax + by + c >= 0
	Line(P p, P q): a(p.y-q.y), b(q.x-p.x), c(p.cross(q)) {} //p->q ccw
	Line operator- () const {return Line(-a, -b, -c); }
	bool up() const { return a?(a<0):(b>0);}
	P v() const {return P(a,b);} 
	P vx() {return P(b,c);} P vy() {return P(a,c);}
	T wek(Line p) const {return v().cross(p.v());}
	bool operator<(Line b) const {
		if (up() != b.up()) return up() > b.up();
		return wek(b) > 0;
	}
};
bool parallel(Line a, Line b) {return !a.wek(b);}
bool same(Line a, Line b) {
	return parallel(a,b) && !a.vy().cross(b.vy()) && !a.vx().cross(b.vx());
}
ll weaker (Line a, Line b) { 
	if (abs(a.a) > abs(a.b)) return a.c*abs(b.a) - b.c*abs(a.a);
	return a.c*abs(b.b) - b.c*abs(a.b);
}
Point<ld> intersect(Line a, Line b) {
	ld det = a.wek(b);
	T x = a.vx().cross(b.vx());
	T y = a.vy().cross(b.vy());
	return Point<ld>(x/det,-y/det);
}
struct HPI {
	bool empty=0, pek=0; 
	set<Line> s;
	typedef set<Line>::iterator iter;
	iter next(iter it){return ++it == s.end() ? s.begin() : it;}
	iter prev(iter it){return it == s.begin() ? --s.end() : --it;}
	bool hide(Line a, Line b, Line c) { // do a,b hide c?
		if (parallel(a,b)) {
			if (weaker(a, -b) < 0) empty = 1;
			return 0; 
		}
		if (a.wek(b) < 0) swap(a,b);
		auto r = intersect(a,b);
		ld v = r.x*c.a + r.y*c.b + c.c;
		if (a.wek(c) >=0  && c.wek(b) >=0 && v > -EPS) return 1;
		if (a.wek(c) < 0  && c.wek(b) < 0) {
			if (v < -EPS) empty = 1;
			else if (v < EPS) pek = 1;
		}
		return 0;
	}
	void delAndMove(iter& i, int nxt) {
		iter j = i;
		if(nxt==1) i = next(i);
		else i = prev(i);
		s.erase(j);
	}
	void add(Line l) {
		if (empty) return;
		if (l.a == 0 && l.b == 0) {
			if (l.c < 0) empty = 1;
			return;
		}
		iter it = s.lower_bound(l);  //parallel
		if(it != s.end() && parallel(*it, l) && it->up() == l.up()) {
			if (weaker(l, *it)>=0) return; 
			delAndMove(it,1);
		}
		if(it == s.end()) it = s.begin(); //*it>p
		while(sz(s) >= 2 && hide(l, *next(it), *it)) 
			delAndMove(it,1);
		if(sz(s)) it = prev(it); //*it<p
		while(sz(s) >= 2 && hide(l, *prev(it), *it))
			delAndMove(it,0);
		if(sz(s) < 2 || !hide(*it, *next(it), l)) s.insert(l);
	}
	int type() { //0 = empty, 1=point, 2=segment, 3=halfline
		if(empty) return 0; //4=line, 5=polygon or unbounded
		if(sz(s) <= 4){
			vector<Line> r(all(s));
			if(sz(r) == 2 && parallel(r[0], r[1]) && weaker(r[0],-r[1])<0) 
				return 0; 
			fwd(i, sz(r)) fwd(j, i) if(same(r[i], r[j])) {
				if(sz(r) == 2) return 4;	if(sz(r) == 3) return 3;
				if(sz(r) == 4 && same(r[0], r[2]) && same(r[1], r[3])) return 1;
				return 2;
			}
			if(sz(r) == 3 && pek) return 1;
		}
		return 5;
	}
};