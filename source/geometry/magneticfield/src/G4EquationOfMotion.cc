// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4EquationOfMotion.cc,v 1.3 2000/11/01 15:15:53 gcosmo Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
#include "G4EquationOfMotion.hh"

static const int G4maximum_number_of_field_components = 16;

G4EquationOfMotion::~G4EquationOfMotion()
{}

void 
G4EquationOfMotion::RightHandSide( const  G4double y[],
				   G4double dydx[]   ) const
{
     G4double Field[G4maximum_number_of_field_components];   

     GetFieldValue(y, Field) ;
     EvaluateRhsGivenB( y, Field, dydx );
}

void 
G4EquationOfMotion::EvaluateRhsReturnB( const G4double y[],
				 G4double dydx[],
				 G4double  Field[]  ) const
{
     GetFieldValue(y, Field) ;
     EvaluateRhsGivenB( y, Field, dydx );
}

#if  HELP_THE_COMPILER
void 
G4EquationOfMotion::doNothing()
{
}
#endif