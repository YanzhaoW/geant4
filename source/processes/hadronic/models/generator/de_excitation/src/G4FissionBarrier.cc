// This code implementation is the intellectual property of
// the RD44 GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4FissionBarrier.cc,v 1.3 2000/06/09 11:43:36 larazb Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// Hadronic Process: Nuclear De-excitations
// by V. Lara (Oct 1998)


#include "G4FissionBarrier.hh"

G4FissionBarrier::G4FissionBarrier(const G4FissionBarrier & right)
{
  G4Exception("G4FissionBarrier::copy_constructor meant to not be accessable.");
}


const G4FissionBarrier & G4FissionBarrier::operator=(const G4FissionBarrier & right)
{
 G4Exception("G4FissionBarrier::operator= meant to not be accessable.");
 return *this;
}

G4bool G4FissionBarrier::operator==(const G4FissionBarrier & right) const 
{
 return false;
}

G4bool G4FissionBarrier::operator!=(const G4FissionBarrier & right) const 
{
 return true;
}



G4double G4FissionBarrier::FissionBarrier(const G4int A, const G4int Z, const G4double U)
  // Compute fission barrier according with Barashenkov's prescription for A >= 65
{
  if (A >= 65) return BarashenkovFissionBarrier(A,Z)/(1.0 + sqrt(U/(2.0*G4double(A))));
  else return 100.0*GeV;
}


G4double G4FissionBarrier::BarashenkovFissionBarrier(const G4int A, const G4int Z)
  // Calculates Fission Barrier heights 
{
	// Liquid drop model parameters for
	// surface energy of a spherical nucleus
	const G4double aSurf = 17.9439*MeV;
	// and coulomb energy
	const G4double aCoul = 0.7053*MeV;
	const G4int N = A - Z;
	const G4double k = 1.7826;

	// fissibility parameter
	G4double x = (aCoul/(2.0*aSurf))*(G4double(Z)*G4double(Z))/G4double(A);
	x /= (1.0 - k*(G4double(N-Z)/G4double(A))*(G4double(N-Z)/G4double(A)));
  
	// Liquid drop model part of Fission Barrier
	G4double BF0 = aSurf*pow(G4double(A),2./3.);
	if (x <= 2./3.) BF0 *= 0.38*(3./4.-x);
	else BF0 *= 0.83*(1. - x)*(1. - x)*(1. - x);


	// 
	G4double D = 1.248*MeV;
	D *= (G4double(N)-2.0*(N/2)) + (G4double(Z)-2.0*(Z/2));

  return BF0 + D - SellPlusPairingCorrection(Z,N);
}
