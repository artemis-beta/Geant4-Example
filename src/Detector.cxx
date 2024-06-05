#include "Detector.hxx"

TestSensitiveDetector::TestSensitiveDetector(G4String name): G4VSensitiveDetector(name) {}
TestSensitiveDetector::~TestSensitiveDetector(){}

G4bool TestSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    G4Track* track = step->GetTrack();

    // Enter detector
    G4StepPoint* pre_step = step->GetPreStepPoint();

    // Leave the detector
    G4StepPoint* post_step = step->GetPostStepPoint();

    // Particle Position
    G4ThreeVector particle_position = pre_step->GetPosition();

    G4double particle_charge = pre_step->GetCharge();

    G4cout << "Position: " << particle_position << " Charge: " << particle_charge << std::endl;

    const G4Event* event = G4RunManager::GetRunManager()->GetCurrentEvent();
    
    G4AnalysisManager* manager = G4AnalysisManager::Instance();

    manager->FillNtupleIColumn(0, event->GetEventID());
    manager->FillNtupleIColumn(1, particle_position[0]);
    manager->FillNtupleIColumn(2, particle_position[1]);
    manager->FillNtupleIColumn(3, particle_position[2]);
    manager->FillNtupleIColumn(4, particle_charge);
    manager->FillNtupleIColumn(5, track->GetParticleDefinition()->GetPDGEncoding());
    manager->AddNtupleRow(0);

    return true;
}
