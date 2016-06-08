// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VIon.hh,v 1.3 2000/02/25 07:37:15 kurasige Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file 
//
//      For information related to this code contact:
//      CERN, CN Division, ASD group
//      History: first implementation, based on object model of
//      2nd December 1995, G.Cosmo
// ------------------------------------------------------------
//  Revised, Hisaya Kurashige, 16 Dec 1996
//  Revised, Hisaya Kurashige, 24 Frb 1997
// ----------------------------------------------------------------

#ifndef G4VIon_h
#define G4VIon_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4Material.hh"

#include "G4PhysicsLogVector.hh"
#include "G4ParticleWithCuts.hh"

class G4VIon : public G4ParticleWithCuts
{
  //  A virtual class for Ions particles. It defines
  //  public methods which describe the behavior of a
  //  ion.

  private:

      const G4VIon & operator=(const G4VIon &right);

  public:

      G4VIon(const G4String&  aName,  
               G4double         mass,     
               G4double         width,
               G4double         charge,   
               G4int            iSpin,
               G4int            iParity,
               G4int            iConjugation,
               G4int            iIsospin,   
               G4int            iIsospinZ, 
               G4int            gParity,
               const G4String&  pType,
               G4int            lepton,
               G4int            baryon,
               G4int            encoding,
               G4bool           stable,
               G4double         lifetime,
               G4DecayTable     *decaytable)
	: G4ParticleWithCuts(aName, mass, width, charge, iSpin, iParity,
                               iConjugation, iIsospin, iIsospinZ, gParity,
                               pType, lepton, baryon, encoding, stable,
                               lifetime, decaytable) {};

      virtual ~G4VIon() {};

 public:  //With Description
   G4int    GetAtomicNumber() const;
   G4int    GetAtomicMass() const;

   G4double GetExcitationEnergy() const {return 0.;} 
   void     SetExcitationEnergy(G4double ){}
   // These two methods are dummy because all particles derived from 
   // G4VIon is "groud state" nuclei  

};
inline
 G4int G4VIon::GetAtomicNumber() const 
{
  return int(GetPDGCharge()/eplus); 
}

inline
 G4int G4VIon::GetAtomicMass() const 
{
  return GetBaryonNumber();
}

#endif