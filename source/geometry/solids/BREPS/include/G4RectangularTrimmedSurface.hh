// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4RectangularTrimmedSurface.hh,v 1.6 2000/11/08 14:22:03 gcosmo Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// ----------------------------------------------------------------------
// Class G4BezierSurface
//
// Class description:
// 
// Definition of a rectangular trimmed surface.

// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
// ----------------------------------------------------------------------
#ifndef __RECTRIMMEDSURFACE_H
#define __RECTRIMMEDSURFACE_H

#include "G4FCylindricalSurface.hh"

class G4RectangularTrimmedSurface : public G4Surface
{

public:  // with description

  G4RectangularTrimmedSurface();
  virtual ~G4RectangularTrimmedSurface();  
    // Constructor & destructor

  G4int Intersect(const G4Ray&);  
    // Counts the number of intersections of a the surface by a ray.
    // If no intersection is found, it sets distance = kInfinity and returns 0.

  void CalcBBox();
    // Computes the bounding-box.

  virtual const char* Name() const;
    // Returns the class type name.

private:

  G4RectangularTrimmedSurface(const G4RectangularTrimmedSurface&);
  G4RectangularTrimmedSurface& operator=(const G4RectangularTrimmedSurface&);

private:

  G4Surface* BasisSurface;

  G4double TrimU1,TrimU2;
  G4double TrimV1,TrimV2; 
 
  G4Point3D TrimPointU1, TrimPointU2;
  G4Point3D TrimPointV1, TrimPointV2;  
  
};

#endif