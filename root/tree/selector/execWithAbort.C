{
// Avoid loading the library
gInterpreter->UnloadLibraryMap("selabort_C");
TChain ch("T");
ch.Add("Event1.root/T1");
ch.Add("Event2.root/T2");
ch.Add("Event3.root/T3");
   ch->Process("selabort.C","thefirstoption");

TSelector *sel = TSelector::GetSelector("selabort.C");
ch->Process(sel,"theoptions");
return 0;
}