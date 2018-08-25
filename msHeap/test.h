// FILE: test.h
// NAME: Mark Sattolo

#ifndef __MHS_TEST_H__
#define __MHS_TEST_H__

// FOR SOME REASON WILL NOT COMPILE WITH #include <iostream> !!
#include <iostream.h>
//using namespace std;  // CANNOT USE NAMESPACE WITHOUT #include <iostream>

class test_class 
{
 private:
    static int last_id;
    int id;
    double value;

 public:
	 //constructor sets 'value'
	 test_class(const double&);

	 //overload operator* to return 'value'
	 double& operator*();

 friend ostream& operator<<(ostream&, const test_class&);
};

ostream& operator<<(ostream&, const test_class&);

#endif
