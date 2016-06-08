// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4ConicCreator.cc,v 1.3 2000/11/20 18:17:29 gcosmo Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// ----------------------------------------------------------------------
// Class G4ConicCreator
//
// Authors: J.Sulkimo, P.Urban.
// Revisions by: L.Broglia, G.Cosmo.
//
// History:
//   18-Nov-1999: First step of re-engineering - G.Cosmo
// ----------------------------------------------------------------------

#include "G4ConicCreator.hh"
#include "G4GeometryTable.hh"

G4ConicCreator G4ConicCreator::csc;

G4ConicCreator::G4ConicCreator()
{
  G4GeometryTable::RegisterObject(this);
}

G4ConicCreator::~G4ConicCreator() {}

void G4ConicCreator::CreateG4Geometry(STEPentity& Ent)
{
//  G4Placement *place;
  G4String attrName("edge_start");
  STEPattribute *Attr = GetNamedAttribute(attrName, Ent);

  // Get the placement
    STEPentity* TmpEnt= *Attr->ptr.c;
    G4GeometryTable::CreateObject(*TmpEnt);
//  place = (G4Placement*)place;
  
}


void G4ConicCreator::CreateSTEPGeometry(void* G4obj)
{
}