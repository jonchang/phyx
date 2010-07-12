#ifndef DELTA_H
#define DELTA_H

#include <vector>
#include <string>
using namespace std;

#include <gsl/gsl_vector.h>

class Delta{
private:
	double cdf(double);
public:
	Delta();
	double shift(double p, double s, int c, int l, int r);
	double bigshift(double p, double s, int c, int l, int r);
	vector<double> delta(int, int, int);
};

class OptimizeShift{
private:
	Delta * delta;
	int maxiterations;
	double stoppingprecision;
	int c,l,r;
	double GetShift(const gsl_vector * variables);
	static double GetShift_gsl(const gsl_vector * variables, void *obj);
public:
	OptimizeShift(Delta *);
	vector<double> optimize_shift();
	void setCLR(int,int,int);
};

#endif