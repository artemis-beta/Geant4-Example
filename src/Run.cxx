#include "Run.hxx"

TestRunAction::TestRunAction(const G4String output_file): output_file(output_file) {}
TestRunAction::~TestRunAction() {}

void TestRunAction::BeginOfRunAction(const G4Run*){
    G4AnalysisManager* manager = G4AnalysisManager::Instance();

    G4cout << "Opening file '" << output_file << "'" << std::endl;
    manager->SetVerboseLevel(1);
    manager->OpenFile(output_file);
    manager->CreateNtuple("Hits", "Hits");
    manager->CreateNtupleIColumn("fEvent");
    manager->CreateNtupleIColumn("fX");
    manager->CreateNtupleIColumn("fY");
    manager->CreateNtupleIColumn("fZ");
    manager->CreateNtupleIColumn("fCharge");
    manager->CreateNtupleIColumn("fID");
    manager->FinishNtuple(0);
}
void TestRunAction::EndOfRunAction(const G4Run*){
    G4AnalysisManager* manager = G4AnalysisManager::Instance();

    G4cout << "Closing file" << std::endl;
    manager->Write();
    manager->CloseFile();
}
