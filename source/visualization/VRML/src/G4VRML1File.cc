// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VRML1File.cc,v 1.5 2000/08/19 18:34:57 johna Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// G4VRML1File.cc
// Satoshi Tanaka & Yasuhide Sawada

//=================//
#ifdef G4VIS_BUILD_VRMLFILE_DRIVER
//=================//


#include <stdio.h> // sscanf
#include <stdlib.h> // getenv

#include "G4VSceneHandler.hh"

#include "G4VRML1File.hh"
#include "G4VRML1FileSceneHandler.hh"
#include "G4VRML1FileViewer.hh"

#include "G4FRClient.hh"


G4VRML1File::G4VRML1File() :
	G4VGraphicsSystem("VRML1FILE", "VRML1FILE", G4VGraphicsSystem::threeD)
{
}

G4VRML1File::~G4VRML1File()
{
}


G4VSceneHandler* G4VRML1File::CreateSceneHandler(const G4String& name) 
{
	G4VSceneHandler *p = NULL;

	p = new G4VRML1FileSceneHandler(*this, name);

	G4cout << G4VRML1FileSceneHandler::GetSceneCount()
		<< " " << fName << " scene handlers extanct." << G4endl;

	return p;
}

G4VViewer* G4VRML1File::CreateViewer(G4VSceneHandler& scene, const G4String& name)
{
	G4VViewer* pView = NULL;

	G4VRML1FileSceneHandler* pScene = (G4VRML1FileSceneHandler*)&scene;
	pView = new G4VRML1FileViewer(*pScene, name);

	return pView;
}

#endif