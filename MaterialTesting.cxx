#include "G4RunManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "Construction.hxx"
#include "PhysicsList.hxx"
#include "Action.hxx"

int main(int argc, char** argv) {
    int n_per_event=1;
    G4String particle="proton";
    G4ThreeVector gun_origin=G4ThreeVector(0., 0., -1.9 * m);
    G4ThreeVector particle_momentum_dir=G4ThreeVector(0., 0., 1.);
    G4float particle_momentum=100.*GeV;

    G4RunManager* run_manager = new G4RunManager;
    run_manager->SetUserInitialization(new TestDetectorConstruction);
    run_manager->SetUserInitialization(new TestPhysicsList);
    run_manager->SetUserInitialization(new TestActionInitialization(n_per_event, particle, gun_origin, particle_momentum_dir, particle_momentum));
    run_manager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);

    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();

    G4UImanager* ui_manager = G4UImanager::GetUIpointer();

    ui_manager->ApplyCommand("/control/execute vis.mac");

    ui->SessionStart();

    return 0;
}