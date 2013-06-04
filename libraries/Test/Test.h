/*
  Test.h - Test library for Wiring - description
  Copyright (c) 2006 John Doe.  All right reserved.
*/


#include "Arduino.h"

// library interface description
class Test
{
  // user-accessible "public" interface
  public:
    Test(int);
    void doSomething(void);

  // library-accessible "private" interface
  private:
    int value;
    void doSomethingSecret(void);
};



