// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4GeometricRepresentationContextCreator.hh,v 1.3 2000/11/09 16:35:46 gcosmo Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// ----------------------------------------------------------------------
// Class G4GeometricRepresentationContextCreator
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
#ifndef G4GEOMETRICREPRESENTATIONCONTEXTCREATOR_HH
#define G4GEOMETRICREPRESENTATIONCONTEXTCREATOR_HH

#include "G4GeometryCreator.hh"

class G4GeometricRepresentationContextCreator: private G4GeometryCreator 
{
  public:

  // Constructor & destructor

    G4GeometricRepresentationContextCreator();
    ~G4GeometricRepresentationContextCreator();

  // Member functions

    void CreateG4Geometry(STEPentity&);
    void CreateSTEPGeometry(void*);
    const char* Name() const { return "Geometric_Representation_Context"; }
    static G4GeometricRepresentationContextCreator GetInstance() { return csc; }

  // Members

  private:

    static G4GeometricRepresentationContextCreator csc;
};

#endif