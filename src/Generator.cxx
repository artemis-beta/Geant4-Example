#include "Generator.hxx"

TestPrimaryGeneratorAction::TestPrimaryGeneratorAction(int n_per_event, G4String particle, G4ThreeVector gun_origin, G4ThreeVector particle_momentum_dir, G4float particle_momentum):
    particle_gun(new G4ParticleGun(n_per_event)), particle_name(particle), particle_momentum_dir(particle_momentum_dir), gun_position(gun_origin), particle_momentum(particle_momentum) {}
TestPrimaryGeneratorAction::~TestPrimaryGeneratorAction() {
    delete particle_gun;
}

void TestPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    G4ParticleTable* particle_table = G4ParticleTable::GetParticleTable();

    G4ParticleDefinition* particle = particle_table->FindParticle(particle_name);

    if (!particle) {
        throw std::runtime_error("Could not allocate particle " + particle_name + ", particle not found");
    }

    particle_gun->SetParticleMomentumDirection(particle_momentum_dir);
    particle_gun->SetParticlePosition(gun_position);
    particle_gun->SetParticleMomentum(particle_momentum);
    particle_gun->SetParticleDefinition(particle);
    particle_gun->GeneratePrimaryVertex(event);
}