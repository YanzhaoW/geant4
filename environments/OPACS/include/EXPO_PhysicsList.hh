// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: EXPO_PhysicsList.hh,v 1.4 1999/12/15 14:48:41 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//      This class is a class derived from G4VUserPhysicsList
//      for constructing all particles and processes.
//
// ------------------------------------------------------------
#ifndef EXPO_PhysicsList_h
#define EXPO_PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class EXPO_PhysicsList: public G4VUserPhysicsList
{
  public:
    EXPO_PhysicsList();
    virtual ~EXPO_PhysicsList();

  protected:
    // Construct particle and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    // 
    virtual void SetCuts();
    
  protected:
    // these methods Construct particles 
    virtual void ConstructBosons();
    virtual void ConstructLeptons();
    virtual void ConstructMesons();
    virtual void ConstructBarions();
    virtual void ConstructIons();

  protected:
  // these methods Construct physics processes and register them
    virtual void ConstructGeneral();
    virtual void ConstructEM();
    virtual void ConstructHad();
    virtual void ConstructLeptHad();

};

#endif


