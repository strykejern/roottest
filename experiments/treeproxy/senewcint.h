//////////////////////////////////////////////////////////
//   This class has been automatically generated 
//     (Wed Oct 23 16:19:38 2002 by ROOT version3.03/09)
//   from TTree T/An example of a ROOT tree
//   found on file: Event.new.split9.root
//////////////////////////////////////////////////////////


#ifndef senewcint_h
#define senewcint_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TRef.h>
#include <TRefArray.h>

#include <TProxy.h>
#include <string>

#include <TH1F.h>

   const Int_t kMaxfTracks = 617;

#ifdef __MAKECINT__
#pragma link C++ class TObjProxy<TH1F>;
#pragma link C++ class TObjProxy<TRef>;
#endif

class Event;

class senewcint : public TSelector {
   public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   TProxyDirector  fDirector;

//Declaration of leaves types
 //Event           *event;
   TObjProxy<Event>    event;
   
   TUIntProxy          fUniqueID;
   TUIntProxy          fBits;
   TArrayCharProxy     fType; // [20]
   TIntProxy           fNtrack;
   TIntProxy           fNseg;
   TIntProxy           fNvertex;
   TUIntProxy          fFlag;
   TFloatProxy         fTemperature;
   TArrayIntProxy      fMeasures; // Int_t fMeasures[10]
   TArray2Proxy<Float_t,4> fMatrix; // fMatrix[4][4];
   TArrayFloatProxy    fClosestDistance; // [20];   //[fNvertex]

   // We want to implement a class for each branches
   // and sub-branches that have a branch which uses
   // a basic type proxy.
   // For the branch holding non-split event
   // we need a class and then a class proxy.
   // what about derivation?
   struct EventHeader {
      EventHeader(TProxyDirector* director,const TString& top) :
         fEvtNum(director,TString(top+".fEvtNum")),
         fRun(director,TString(top+".fRun")),
         fDate(director,TString(top+".fDate")) {};
      TIntProxy           fEvtNum;
      TIntProxy           fRun;
      TIntProxy           fDate;
   };
   EventHeader fEvtHdr;

   /*
     non-split case?
   struct EventHeader {
      Int_t           fEvtNum;
      Int_t           fRun;
      Int_t           fDate;
   };
   TObjProxy<EventHeader> fEvtHdr;
   fEvtHdr(fDirector,"event.fEvtHdr");
   */

   /* how to deal with clones array?
      how to deal with the case of having the library?
      the current design I am going for, it would mean that when the 
        user has its library it would be slower.  
      So the idea is to create a proxy class for ALL branches that are split.

      We will also need a proxy clones array for the clones that are split.
      But we can use a real clones array for those that are not.
   */

   class Tracks : public TClaProxy {
   public:
      Tracks(TProxyDirector* director,const TString& top) :
         TClaProxy(director,top),
         fUniqueID(director,TString(top+".fUniqueID")),
         fBits(director,TString(top+".fBits")),
         fPx(director,TString(top+".fPx")),
         fPy(director,TString(top+".fPy")),
         fPz(director,TString(top+".fPz")),
         fRandom(director,TString(top+".fRandom")),
         fMass2(director,TString(top+".fMass2")),
         fBx(director,TString(top+".fBx")),
         fBy(director,TString(top+".fBy")),
         fMeanCharge(director,TString(top+".fMeanCharge")),
         fXfirst(director,TString(top+".fXfirst")),
         fXlast(director,TString(top+".fXlast")),
         fYfirst(director,TString(top+".fYfirst")),
         fYlast(director,TString(top+".fYlast")),
         fZfirst(director,TString(top+".fZfirst")),
         fZlast(director,TString(top+".fZlast")),
         fCharge(director,TString(top+".fCharge")),
         fVertex(director,TString(top+".fVertex")),
         fNpoint(director,TString(top+".fNpoint")),
         fValid(director,TString(top+".fValid")),
         fNsp(director,TString(top+".fNsp")),
         fPointValue(director,TString(top+".fPointValue"))
         {
         };
      // TIntProxy           fTracks_; // hummm ? .. it is wrong!
      TClaUIntProxy          fUniqueID; // [kMaxfTracks];   //[fTracks_]
      TClaUIntProxy          fBits; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fPx; // ; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fPy; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fPz; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fRandom; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fMass2; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fBx; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fBy; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fMeanCharge; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fXfirst; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fXlast; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fYfirst; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fYlast; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fZfirst; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fZlast; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fCharge; // [kMaxfTracks];   //[fTracks_]
      TClaFloatProxy         fVertex; // [kMaxfTracks][3];   //[fTracks_]
      TClaIntProxy           fNpoint; // [kMaxfTracks];   //[fTracks_]
      TClaShortProxy         fValid; // [kMaxfTracks];   //[fTracks_]
      TClaIntProxy           fNsp; // [kMaxfTracks];   //[fTracks_]
      TClaArrayProxy<Float_t>fPointValue; // [kMaxfTracks];   //[fTracks_fNsp]
   };
   Tracks fTracks;

   TObjProxy<TH1F> fH;
   TObjProxy<TRef> fLastTrack;
   TObjProxy<TRef> fWebHistogram;

//List of branches
   TBranch        *b_fUniqueID;   //!
   TBranch        *b_fBits;   //!
   TBranch        *b_fType;   //!
   TBranch        *b_fNtrack;   //!
   TBranch        *b_fNseg;   //!
   TBranch        *b_fNvertex;   //!
   TBranch        *b_fFlag;   //!
   TBranch        *b_fTemperature;   //!
   TBranch        *b_fMeasures;   //!
   TBranch        *b_fMatrix;   //!
   TBranch        *b_fClosestDistance;   //!
   TBranch        *b_fEvtHdr_fEvtNum;   //!
   TBranch        *b_fEvtHdr_fRun;   //!
   TBranch        *b_fEvtHdr_fDate;   //!
   TBranch        *b_fTracks_;   //!
   TBranch        *b_fTracks_fUniqueID;   //!
   TBranch        *b_fTracks_fBits;   //!
   TBranch        *b_fTracks_fPx;   //!
   TBranch        *b_fTracks_fPy;   //!
   TBranch        *b_fTracks_fPz;   //!
   TBranch        *b_fTracks_fRandom;   //!
   TBranch        *b_fTracks_fMass2;   //!
   TBranch        *b_fTracks_fBx;   //!
   TBranch        *b_fTracks_fBy;   //!
   TBranch        *b_fTracks_fMeanCharge;   //!
   TBranch        *b_fTracks_fXfirst;   //!
   TBranch        *b_fTracks_fXlast;   //!
   TBranch        *b_fTracks_fYfirst;   //!
   TBranch        *b_fTracks_fYlast;   //!
   TBranch        *b_fTracks_fZfirst;   //!
   TBranch        *b_fTracks_fZlast;   //!
   TBranch        *b_fTracks_fCharge;   //!
   TBranch        *b_fTracks_fVertex;   //!
   TBranch        *b_fTracks_fNpoint;   //!
   TBranch        *b_fTracks_fValid;   //!
   TBranch        *b_fTracks_fNsp;   //!
   TBranch        *b_fTracks_fPointValue;   //!
   TBranch        *b_fLastTrack;   //!
   TBranch        *b_fWebHistogram;   //!

   senewcint(TTree *tree=0):
      fDirector(tree,-1),
      event        (&fDirector,"event"),
      fUniqueID    (&fDirector,"fUniqueID"),
      fBits        (&fDirector,"fBits"),
      fType        (&fDirector,"fType[20]"),
      fNtrack      (&fDirector,"fNtrack"),
      fNseg        (&fDirector,"fNseg"),
      fNvertex     (&fDirector,"fNvertex"),
      fFlag        (&fDirector,"fFlag"),
      fTemperature (&fDirector,"fTemperature"),
      fMeasures    (&fDirector,"fMeasures[10]"),
      fMatrix      (&fDirector,"fMatrix[4][4]"),
      fClosestDistance(&fDirector,"fClosestDistance"),
      fEvtHdr      (&fDirector,"fEvtHdr"),
      //      fTracks_ (&fDirector,"event.fTracks_")
      fTracks      (&fDirector,"fTracks"),
      fH           (&fDirector,"fH"),
      fLastTrack   (&fDirector,"fLastTrack"),
      fWebHistogram(&fDirector,"fWebHistogram")
 { }
   ~senewcint() { }
   void    Begin(TTree *tree);
   void    Init(TTree *tree);
   Bool_t  Notify();
   Bool_t  Process(Int_t entry);
   Bool_t  ProcessCut(Int_t entry);
   void    ProcessFill(Int_t entry);
   void    SetOption(const char *option) { fOption = option; }
   void    SetObject(TObject *obj) { fObject = obj; }
   void    SetInputList(TList *input) {fInput = input;}
   TList  *GetOutputList() const { return fOutput; }
   void    Terminate();
};

#endif

#ifdef senewcint_cxx
void senewcint::Init(TTree *tree)
{
//   Set branch addresses
   if (tree == 0) return;
   fChain    = tree;
   // fChain->SetMakeClass(1);
   fDirector.SetTree(fChain);

}

Bool_t senewcint::Notify()
{
   // Called when loading a new file.
   // Get branch pointers.
   fDirector.SetTree(fChain);
   
   return kTRUE;
}

#endif // #ifdef senewcint_cxx

