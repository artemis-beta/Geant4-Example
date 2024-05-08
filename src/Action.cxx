#include "Action.hxx"

TestActionInitialization::TestActionInitialization(
    int n_per_event,
    G4String particle,
    G4ThreeVector gun_origin,
    G4ThreeVector particle_momentum_dir,
    G4float particle_momentum,
    G4String output_file
): generator(new TestPrimaryGeneratorAction(n_per_event, particle, gun_origin, particle_momentum_dir, particle_momentum)), output_file(output_file) {}

TestActionInitialization::~TestActionInitialization() {}

void TestActionInitialization::Build() const {
    SetUserAction(generator);

    TestRunAction* action = new TestRunAction(output_file);
    SetUserAction(action);
}