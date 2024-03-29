#include "TError.h"

void runPyClassTest() {
// The higher warning ignore level is to suppress warnings about
// classes already being in the class table (on Mac).
   int eil = gErrorIgnoreLevel;
   gErrorIgnoreLevel = kError;
   TPython::LoadMacro( "MyPyClass.py" );

   MyPyClass m;
   printf( "string (aap) : %s\n", (const char*)(*(TPyReturn*)m.gime( "aap" ))  );
   printf( "string (noot): %s\n", (const char*) ((TPyReturn&)m.gime( "noot" )) );
   printf( "string (mies): %s\n", (const char*)              m.gime( "mies" )  );
   printf( "string (zus) : %s\n",       (char*)              m.gime( "zus" )   );

   printf( "double (0.123): %.3f\n",   (double)(*(TPyReturn*)m.gime( 0.123 ))  );
   printf( "double (0.456): %.3f\n",   (double)  ((TPyReturn)m.gime( 0.456 ))  );
   printf( "double (0.789): %.3f\n",   (double)              m.gime( 0.789 )   );

// load another class
   TPython::LoadMacro( "MyOtherPyClass.py" );

// did this intefere with the old class?
   printf( "string (jet) : %s\n",       (char*)              m.gime( "zus" )   );

   MyOtherPyClass o;
   o.hop();
   o.duck();

// finally, ref counting test
   TPython::Exec( "print \'instance count:\', MyOtherPyClass.count" );
   TPython::Exec( "op = MyOtherPyClass()" );
   TPython::Exec( "print \'instance count:\', MyOtherPyClass.count" );
   (void*)TPython::Eval( "op" );
   TPython::Exec( "del op" );
   TPython::Exec( "print \'instance count:\', MyOtherPyClass.count" );
}
