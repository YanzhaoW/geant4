// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4AntiBMesonZero.cc,v 1.4 2000/02/27 05:56:30 kurasige Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD Group
//
//      Created                 Hisaya Kurashige, 16 June 1997
// **********************************************************************
//  Change both methods to get the pointer into non-inlined H.Kurashige 4 Aug. 1998
// ----------------------------------------------------------------

#include "g4std/fstream"
#include "g4std/iomanip"

#include "G4AntiBMesonZero.hh"

#include "G4DecayTable.hh"

// ######################################################################
// ###                      AntiBMesonZero                            ###
// ######################################################################

G4AntiBMesonZero::G4AntiBMesonZero(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable )
 : G4VMeson( aName,mass,width,charge,iSpin,iParity,
             iConjugation,iIsospin,iIsospin3,gParity,pType,
             lepton,baryon,encoding,stable,lifetime,decaytable )
{
   SetParticleSubType("B");
}

// ......................................................................
// ...                 static member definitions                      ...
// ......................................................................
//     
//    Arguments for constructor are as follows
//               name             mass          width         charge
//             2*spin           parity  C-conjugation
//          2*Isospin       2*Isospin3       G-parity
//               type    lepton number  baryon number   PDG encoding
//             stable         lifetime    decay table 

// In this version, charged pions are set to stable
G4AntiBMesonZero G4AntiBMesonZero::theAntiBMesonZero(
	    "anti_B0",      5.2792*GeV,   4.22e-10*MeV,          0., 
		    0,              -1,             0,          
		    1,              +1,             0,             
	      "meson",               0,             0,        -511,
		false,      1.56e-3*ns,          NULL
);

G4AntiBMesonZero*  G4AntiBMesonZero::AntiBMesonZeroDefinition(){return &theAntiBMesonZero;}
G4AntiBMesonZero*  G4AntiBMesonZero::AntiBMesonZero(){return &theAntiBMesonZero;}
// initialization for static cut values
G4double   G4AntiBMesonZero::theAntiBMesonZeroLengthCut = -1.0;
G4double*  G4AntiBMesonZero::theAntiBMesonZeroKineticEnergyCuts = NULL;

void G4AntiBMesonZero::SetCuts(G4double aCut)
{
  theCutInMaxInteractionLength = aCut;

  const G4MaterialTable* materialTable = G4Material::GetMaterialTable();
  // Create the vector of cuts in energy
  // corresponding to the stopping range cut
  if(theKineticEnergyCuts) delete [] theKineticEnergyCuts;
  theKineticEnergyCuts = new G4double [materialTable->length()];

  // Build range vector for every material, convert cut into energy-cut,
  // fill theKineticEnergyCuts and delete the range vector
  for (G4int J=0; J<materialTable->length(); J++)
  {
    G4Material* aMaterial = (*materialTable)[J];
    theKineticEnergyCuts[J] = LowestEnergy;
  }
  theAntiBMesonZeroLengthCut = theCutInMaxInteractionLength;  
  theAntiBMesonZeroKineticEnergyCuts = theKineticEnergyCuts;
}





