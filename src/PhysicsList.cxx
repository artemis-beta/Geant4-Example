#include "PhysicsList.hxx"

TestPhysicsList::TestPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics);
}

TestPhysicsList::~TestPhysicsList(){}