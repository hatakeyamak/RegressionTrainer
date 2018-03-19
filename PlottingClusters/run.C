#if defined(__CINT__) && !defined(__MAKECINT__)
#include "Plot.C+"
#else
#include "Plot.C"
#endif


void run()
{
  Plot t;
  /*t.Loop("EB","ZS");
  t.Loop("EE","ZS");
  //t.Loop("FULl","ZS");

  t.Loop("EB","FULL");
  t.Loop("EE","FULL");
  //t.Loop("FULl","FULL");
  */


  //t.Loop("EB","ALL");
  t.Loop("EB","ZS");
  t.Loop("EB","FULL");
  //t.Loop("EE","ALL");
  t.Loop("EE","ZS");
  t.Loop("EE","FULL");
}
