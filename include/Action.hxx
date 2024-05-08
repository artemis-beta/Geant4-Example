#pragma once

#include "G4VUserActionInitialization.hh"

#include "Generator.hxx"
#include "Run.hxx"

class TestActionInitialization : public G4VUserActionInitialization {
    public:
        TestActionInitialization(int n_per_event, G4String particle, G4ThreeVector gun_origin, G4ThreeVector particle_momentum_dir, G4float particle_momentum, G4String output_file);
        ~TestActionInitialization();
        virtual void Build() const;
    private:
        TestPrimaryGeneratorAction* generator;
        const G4String output_file;       
};
