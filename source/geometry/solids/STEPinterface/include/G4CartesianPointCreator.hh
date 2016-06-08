// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4CartesianPointCreator.hh,v 1.3 2000/11/09 16:35:43 gcosmo Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// ----------------------------------------------------------------------
// Class G4CartesianPointCreator
//
// Class description:
//
//

// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------
#ifndef G4CARTESIANPOINTCREATOR_HH
#define G4CARTESIANPOINTCREATOR_HH

#include "G4GeometryCreator.hh"

class G4CartesianPointCreator: private G4GeometryCreator 
{
  public:

  // Constructor & destructor

    G4CartesianPointCreator();
    ~G4CartesianPointCreator();

  // Member functions

    void CreateG4Geometry(STEPentity&);
    void CreateSTEPGeometry(void* G4obj);
    const char* Name() const { return "Cartesian_Point"; }
    static G4CartesianPointCreator GetInstance() { return csc; }

  // Members
  
  private:

    static G4CartesianPointCreator csc;
};

#endif