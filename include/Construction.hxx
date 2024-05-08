#pragma once

#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Detector.hxx"

class TestDetectorConstruction : public G4VUserDetectorConstruction {
    public: 
        TestDetectorConstruction(const G4float target_dz=0.1);
        ~TestDetectorConstruction();
        virtual G4VPhysicalVolume* Construct();
    private:
        G4LogicalVolume*  detector_logic;
        const G4float target_dz;
        virtual void ConstructSDandField();
};
