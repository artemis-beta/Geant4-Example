#include "Construction.hxx"

TestDetectorConstruction::TestDetectorConstruction() {}
TestDetectorConstruction::~TestDetectorConstruction() {}
G4VPhysicalVolume* TestDetectorConstruction::Construct() {
    G4RotationMatrix* rotation = 0;
    const G4ThreeVector origin(0., 0., 0.);
    G4LogicalVolume* mother_volume = 0;
    const bool bool_opts = false;
    const int copy_number = 0;
    const bool checkForOverlaps = true;
    G4NistManager* nist_manager = G4NistManager::Instance();

    // Create World Volume of a vacuum
    G4Material* world_material = nist_manager->FindOrBuildMaterial("G4_Galactic");
    G4VSolid* world_solid = new G4Box("TestMaterial", 0.7 * m, 0.7 * m, 2 * m);
    G4LogicalVolume* world_logic = new G4LogicalVolume(world_solid, world_material, "worldLogic");
        G4VPhysicalVolume* world_phys = new G4PVPlacement(
        rotation,
        origin,
        world_logic,
        "worldPhys",
        mother_volume,
        bool_opts,
        copy_number,
        checkForOverlaps
    );

    // Create Target Volume of Beryllium
    G4Material* target_material = nist_manager->FindOrBuildMaterial("G4_Be");
    G4VSolid* target_sold = new G4Box("TestTarget", 0.45 * m, 0.45 * m, 0.2 * m);
    G4LogicalVolume* target_logic = new G4LogicalVolume(target_sold, target_material, "targetLogic");
    G4VPhysicalVolume* target_phys = new G4PVPlacement(
        rotation,
        G4ThreeVector(0., 0., 0.9 * m),
        target_logic, 
        "targetPhys",
        world_logic,
        false,
        0,
        true
    );

    // Create Detector as a set of pixels
    G4Box* detector_volume = new G4Box("Detector", 0.005 * m, 0.005 * m, 0.01 * m);
    detector_logic = new G4LogicalVolume(detector_volume, world_material, "pixelLogic");


    for(G4int i{0}; i < 100; ++i) {
        for(G4int j{0}; j < 100; ++j) {
            G4VPhysicalVolume* detector_phys = new G4PVPlacement(
                rotation,
                G4ThreeVector(-0.5 * m + (i+0.5) * m / 100, -0.5 * m + (j+0.5) * m / 100, 1.2 * m),
                detector_logic, 
                "detectorPhys",
                world_logic,
                false,
                j + i * 100,
                true
            );
        }
    }    

    return world_phys;
}

void TestDetectorConstruction::ConstructSDandField() {
    TestSensitiveDetector* sense_detector = new TestSensitiveDetector("SensDec");

    detector_logic->SetSensitiveDetector(sense_detector);
}