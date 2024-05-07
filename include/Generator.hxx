#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

class TestPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
    public:
        TestPrimaryGeneratorAction(int n_per_event, G4String particle, G4ThreeVector gun_origin, G4ThreeVector particle_momentum_dir, G4float particle_momentum);
        ~TestPrimaryGeneratorAction();
        virtual void GeneratePrimaries(G4Event*);
    private:
        G4ParticleGun* particle_gun;
        G4String particle_name;
        G4ThreeVector gun_position;
        G4ThreeVector particle_momentum_dir;
        G4float particle_momentum;
};