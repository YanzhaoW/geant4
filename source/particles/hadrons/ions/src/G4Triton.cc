// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4Triton.cc,v 1.3 1999/12/15 14:51:02 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// ----------------------------------------------------------------------
//      GEANT 4 class implementation file
//
//      For information related to this code contact:
//      CERN, CN Division, ASD Group
//      History: first implementation, based on object model of
//      4th April 1996, G.Cosmo
// **********************************************************************
//  Added by J.L.Chuma, TRIUMF, 27 June 1996
//  Add  G4Triton::TritonDefinition()  by H.Kurashige 27 June 1996
// ----------------------------------------------------------------------

#include "g4std/fstream"
#include "g4std/iomanip"

#include "G4Triton.hh"

// ######################################################################
// ###                           TRITON                               ###
// ######################################################################

G4Triton::G4Triton(
       const G4String&     aName,        G4double            mass,
       G4double            width,        G4double            charge,   
       G4int               iSpin,        G4int               iParity,    
       G4int               iConjugation, G4int               iIsospin,   
       G4int               iIsospin3,    G4int               gParity,
       const G4String&     pType,        G4int               lepton,      
       G4int               baryon,       G4int               encoding,
       G4bool              stable,       G4double            lifetime,
       G4DecayTable        *decaytable )
 : G4VIon( aName,mass,width,charge,iSpin,iParity,
           iConjugation,iIsospin,iIsospin3,gParity,pType,
           lepton,baryon,encoding,stable,lifetime,decaytable )
{
}

G4Triton::~G4Triton()
{
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

G4Triton G4Triton::theTriton(
             "triton",     2.80925*GeV,       0.0*MeV,  +1.0*eplus, 
		    1,              +1,             0,          
		    0,               0,             0,             
	    "nucleus",               0,            +3,           0,
		 true,            -1.0,          NULL
);

G4Triton* G4Triton::TritonDefinition(){return &theTriton;}
// initialization for static cut values
G4double   G4Triton::theTritonLengthCut;
G4double*  G4Triton::theTritonKineticEnergyCuts;