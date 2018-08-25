// FILE: test.cpp
// NAME: Mark Sattolo

#include "test.h"
//#include "inst.cpp"

int test_class::last_id = 0 ;//must define a static variable

//constructor sets 'value' and increments 'last_id'
test_class::test_class(const double& v)
  {
	id = last_id++ ;
	value = v ;
  }

//operator '*' is overloaded to return 'value'
double& test_class::operator*()
  { return value ; }

//print a test_class
ostream& operator<<(ostream& os, const test_class& c)
  { return os << c.value << '(' << c.id << ')' ; }
