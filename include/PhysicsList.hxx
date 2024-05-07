#pragma once

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

class TestPhysicsList : public G4VModularPhysicsList {
    public:
    TestPhysicsList();
    ~TestPhysicsList();
};