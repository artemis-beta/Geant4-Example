#include "Run.hxx"

TestRunAction::TestRunAction() {}
TestRunAction::~TestRunAction() {}

void TestRunAction::BeginOfRunAction(const G4Run*){
    G4AnalysisManager* manager = G4AnalysisManager::Instance();

    G4cout << "Opening file" << std::endl;
    manager->SetVerboseLevel(1);
    manager->OpenFile("output.root");
    manager->CreateNtuple("Hits", "Hits");
    manager->CreateNtupleIColumn("fEvent");
    manager->CreateNtupleIColumn("fX");
    manager->CreateNtupleIColumn("fY");
    manager->CreateNtupleIColumn("fZ");
    manager->CreateNtupleIColumn("fCharge");
    manager->FinishNtuple(0);
}
void TestRunAction::EndOfRunAction(const G4Run*){
    G4AnalysisManager* manager = G4AnalysisManager::Instance();

    G4cout << "Closing file" << std::endl;
    manager->Write();
    manager->CloseFile();
}