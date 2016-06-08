// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4IonConstructor.hh,v 1.2 1999/12/15 14:51:01 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// --------------------------------------------------------------
//	GEANT 4 class implementation file 
//
#ifndef G4IonConstructor_h
#define G4IonConstructor_h 1

#include "globals.hh"
#include "G4ios.hh"

class G4IonConstructor
{
  //This class is a utility class for construction 
  //short lived particles

  public:
    G4IonConstructor();
    ~G4IonConstructor();
  
  public:
    void ConstructParticle();

  protected:
    void ConstructLightIons();
};

#endif