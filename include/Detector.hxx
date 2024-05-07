#pragma once

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class TestSensitiveDetector : public G4VSensitiveDetector {
    public:
        TestSensitiveDetector(G4String);
        ~TestSensitiveDetector();
    private:
        virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};
