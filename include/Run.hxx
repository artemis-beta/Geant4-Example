#pragma once

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"


class TestRunAction : public G4UserRunAction {
    public:
        TestRunAction(const G4String);
        ~TestRunAction();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);
    private:
        const G4String output_file;
};