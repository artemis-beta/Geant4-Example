#include "G4RunManager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4PhysListFactory.hh"

#include <toml++/toml.hpp>
#include "args.hxx"
#include <filesystem>

#include "Construction.hxx"
#include "Action.hxx"

int main(int argc, char** argv) {
    args::ArgumentParser parser(
        "Geant4 fixed target demonstration.",
        "This simulation models a particle gun positioned along the Z axis relative to a target of Beryllium.\n\n"
    );
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::Flag batch_mode(parser, "batch_mode", "Run in batch mode, no UI", {'b', "batch"});
    args::ValueFlag<std::filesystem::path> file_flag(parser, "config_file", "Read inputs from configuration file", {'c', "config"});
    args::ValueFlag<G4String> phys_list_flag(parser, "physics_list", "Use specificed G4 Physics list", {'l', "physics-list"});
    args::ValueFlag<G4String> root_out_flag(parser, "output_file", "ROOT file to write results to", {'o', "output"});
    args::ValueFlag<G4double> momentum_flag(parser, "momentum", "Momentum Z component in GeV", {'m', "momentum"});
    args::ValueFlag<G4double> target_dz_flag(parser, "target_thickness", "Size of target in the Z axis in metres", {'t', "target-thickness"});
    args::ValueFlag<G4double> gun_z_offset_flag(parser, "gun_z_offset", "Z axis position of particle gun in metres", {'z', "pgun-zpos"});

    try
    {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help)
    {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e)
    {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    std::filesystem::path macro_path = std::filesystem::path(argv[0]).parent_path() / "vis.mac";

    if(!std::filesystem::exists(macro_path)) {
        throw std::runtime_error("Expected macro file '" + macro_path.string() + "' but file does not exist");
    }

    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);
    G4PhysListFactory factory;

    int n_per_event=1;
    G4String particle="proton";
    G4String physics_list="FTFP_BERT";
    G4String output_file="output.root";
    G4float gun_z_offset = -1.9 * m;
    G4float target_dz = 0.1;
    G4ThreeVector particle_momentum_dir=G4ThreeVector(0., 0., 1.);
    G4float particle_momentum=100.*GeV;


    if(file_flag) {
        const std::filesystem::path input_file = args::get(file_flag);

        if(!std::filesystem::is_regular_file(input_file)) {
            throw std::runtime_error("Cannot open file '" + input_file.string() + "', file does not exist");
        }

        if(input_file.extension() != ".toml") {
            throw std::runtime_error("Cannot open file '" + input_file.string() + "', file is not a valid TOML file");
        }

        auto parsed = toml::parse_file(input_file.c_str());
        particle = parsed["particle_gun"]["momentum"].value_or(particle.c_str());
        particle_momentum = (parsed["particle_gun"]["momentum"].value_or(100.)) * GeV;
        n_per_event = parsed["particle_gun"]["n_per_event"].value_or(n_per_event);
        gun_z_offset = (parsed["particle_gun"]["z_offset"].value_or(-1.9)) * m;
        physics_list = parsed["physics"]["physics_list"].value_or(physics_list.c_str());
        target_dz = parsed["target"]["thickness"].value_or(target_dz);
        output_file = parsed["output"]["root_file"].value_or(output_file.c_str());
    }

    if (momentum_flag) { particle_momentum = args::get(momentum_flag) * GeV; }
    if (phys_list_flag) { physics_list = args::get(phys_list_flag); }
    if (target_dz_flag) { target_dz = args::get(target_dz_flag); }
    if (gun_z_offset_flag) { gun_z_offset = args::get(gun_z_offset_flag); }
    if (root_out_flag) { output_file = args::get(root_out_flag); }

    if(std::filesystem::path(output_file.c_str()).extension() != ".root") {
        throw std::runtime_error("Output file '" + output_file + "', file is not a valid ROOT file name");
    }

    G4RunManager* run_manager = new G4RunManager;
    G4VModularPhysicsList* phys = factory.GetReferencePhysList(physics_list);

    run_manager->SetUserInitialization(new TestDetectorConstruction(target_dz));
    run_manager->SetUserInitialization(phys);
    run_manager->SetUserInitialization(
        new TestActionInitialization(
            n_per_event,
            particle,
            G4ThreeVector(0., 0., gun_z_offset),
            particle_momentum_dir,
            particle_momentum,
            output_file
        )
    );
    run_manager->Initialize();
    G4UIExecutive* ui = nullptr;

    if(!batch_mode) {
        ui = new G4UIExecutive(argc, argv);
        G4VisManager* vis_manager = new G4VisExecutive;
        vis_manager->Initialize();
    }

    G4UImanager* ui_manager = G4UImanager::GetUIpointer();

    if(!batch_mode) {
        G4cout << "Opening "<< macro_path.string() << G4endl;
        ui_manager->ApplyCommand("/control/execute " + macro_path.string());
        ui->SessionStart();
    }
    else {
        ui_manager->ApplyCommand("/run/beamOn");
    }

    return 0;
}