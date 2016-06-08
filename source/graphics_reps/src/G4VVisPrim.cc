// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VVisPrim.cc,v 1.5 1999/12/15 14:50:36 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
// John Allison  August 1995

#include "G4VVisPrim.hh"
#include "G4VisAttributes.hh"
#include "G4ios.hh"

G4VVisPrim::~G4VVisPrim () {}

G4Visible& G4VVisPrim::operator = (const G4Visible& right) {
  return G4Visible::operator = (right);
}

G4VVisPrim& G4VVisPrim::operator = (const G4VVisPrim& right) {
  if (&right == this) return *this;
  G4Visible::operator = (right);
  return *this;
}

G4bool G4VVisPrim::operator == (const G4Visible& right) const{
  return G4Visible::operator == (right);
}

G4bool G4VVisPrim::operator == (const G4VVisPrim& right) const{
  return G4Visible::operator == (right);
}

G4std::ostream& operator << (G4std::ostream& os, const G4VVisPrim& prim) {
  return os << (G4Visible) prim;
}