// FILE: test.h
// NAME: Mark Sattolo

#ifndef _MHS_TEST_H_
#define _MHS_TEST_H_

#include <iostream.h> 

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
