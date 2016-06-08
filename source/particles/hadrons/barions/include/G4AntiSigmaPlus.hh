// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4AntiSigmaPlus.hh,v 1.4 1999/12/15 14:50:54 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD group
//      History: first implementation, based on object model of
//      4-th April 1996, G.Cosmo
// ****************************************************************
//  Added particle definitions, H.Kurashige, 14 Feb 19
// ----------------------------------------------------------------

// Each class inheriting from G4VBaryon
// corresponds to a particle type; one and only one
// instance for each class is guaranteed.

#ifndef G4AntiSigmaPlus_h
#define G4AntiSigmaPlus_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4VBaryon.hh"

// ######################################################################
// ###                          AntiSigmaPlus                         ###
// ######################################################################

class G4AntiSigmaPlus : public G4VBaryon
{
 private:
   static G4AntiSigmaPlus theAntiSigmaPlus;
   static G4double  theAntiSigmaPlusLengthCut;
   static G4double* theAntiSigmaPlusKineticEnergyCuts;

 private:
   G4AntiSigmaPlus(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable
   );

 public:
   virtual ~G4AntiSigmaPlus(){}

   static G4AntiSigmaPlus* AntiSigmaPlusDefinition();
   static G4AntiSigmaPlus* AntiSigmaPlus() {return &theAntiSigmaPlus;}
   static G4double GetCuts() {return theAntiSigmaPlusLengthCut;}   
   static G4double* GetCutsInEnergy() {return theAntiSigmaPlusKineticEnergyCuts;};

   virtual void SetCuts(G4double aCut); 
};

inline void G4AntiSigmaPlus::SetCuts(G4double aCut)
{
  CalcEnergyCuts(aCut);
  theAntiSigmaPlusLengthCut = theCutInMaxInteractionLength;  
  theAntiSigmaPlusKineticEnergyCuts = theKineticEnergyCuts;
  
}


#endif