#if defined(ClingWorkAroundBrokenUnnamedReturn)
int make_CopyTree()
#endif
{
TChain* c = new TChain("NtpSt","NtpSt");
c->Add("ver_40200.root");
TFile* newfile = new TFile("CopyTree.root","recreate");
TTree* tc = c->CopyTree("");
tc->GetCurrentFile()->Write();
return 0;
}

