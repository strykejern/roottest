//////////////////////////////////////////////////////////
//   This class has been generated by TFile::MakeProject
//     (Tue Jun 14 15:33:00 2011 by ROOT version 5.31/01)
//      from the StreamerInfo in file http://root.cern.ch/files/atlasFlushed.root
//////////////////////////////////////////////////////////


#ifndef TrigT2MbtsBitsContainer_tlp1_h
#define TrigT2MbtsBitsContainer_tlp1_h
class TrigT2MbtsBitsContainer_tlp1;

#include "Riostream.h"
#include <vector>
#include "TrigT2MbtsBitsContainer_p1.h"
#include "TrigT2MbtsBits_p1.h"

class TrigT2MbtsBitsContainer_tlp1 {

public:
// Nested classes declaration.

public:
// Data Members.
   vector<TrigT2MbtsBitsContainer_p1> m_trigT2MbtsBitsContainerVec;    //(TrigT2MbtsBitsContainer_p1)
   vector<TrigT2MbtsBits_p1>          m_trigT2MbtsBitsVec;             //(TrigT2MbtsBits_p1)

   TrigT2MbtsBitsContainer_tlp1();
   TrigT2MbtsBitsContainer_tlp1(const TrigT2MbtsBitsContainer_tlp1 & );
   virtual ~TrigT2MbtsBitsContainer_tlp1();

};
#endif