#include "body.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define G 1e-8

/* Body */
Body newBody(Vector pos, Vector vel, double radius) {
	Vector *arr = malloc(PATHLEN*sizeof(Vector));
	int i;
	for(i = 0; i<PATHLEN; i++) {
		arr[i] = pos;
	}
	Path path = {
		arr,
		0
	};
	Body out = {
		pos,
		vel,
		{0,0},
		radius,
		path,
		randColour()
	};

	return out;
}
double newt(double m, double r) {
	return G*m/(r*r);
}
double mass(Body *b) {
	return b->radius*b->radius*b->radius;
}
bool collide(Body *thing, Body *rest, int l, int skip) {
	int i;
	double n, r;
	Vector ds = {0,0}, diff, u ,m;
	Body b;
	for(i=0; i<l; ++i) {
		if(i == skip) continue;
		b = rest[i];
		r = distance(&(thing->position),&(b.position));
		printf("%f %f\n",r, thing->radius+b.radius);
		if(r < thing->radius+b.radius) return true;
	}
	return false;
}
Vector move(Body* thing, Body* rest, int l, int skip) {
	int i;
	double n, r;
	Vector ds = {0,0}, diff, u ,m;
	Body b;
	for(i=0; i<l; ++i) {
		if(i == skip) continue;
		b = rest[i];
		r = distance(&(thing->position),&(b.position));
		n = newt(mass(&b),r);
		diff = vminus(&(b.position),&(thing->position));

		u = unit(&diff);
		m = smult(n,&u);
		ds = vplus(&ds,&m);
	}
	return ds;
}
