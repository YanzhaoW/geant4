// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4VRML1Viewer.cc,v 1.4 1999/12/15 14:54:16 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// G4VRMLView.cc
// Yasuhide Sawada & Satoshi Tanaka

//=================//
#ifdef G4VIS_BUILD_VRML_DRIVER
//=================//


//#define DEBUG_FR_VIEW

#include "G4Scene.hh"
#include "G4VRML1Viewer.hh"
#include "G4VRML1SceneHandler.hh"
#include "G4VRML1.hh"
#include "G4ios.hh"

G4VRML1Viewer::G4VRML1Viewer(G4VRML1SceneHandler& scene, const G4String& name) :
   G4VViewer(scene, scene.IncrementViewCount(), name), fSceneHandler(scene)
{}

G4VRML1Viewer::~G4VRML1Viewer()
{}

void G4VRML1Viewer::SetView()
{
#if defined DEBUG_FR_VIEW
  G4cerr << "***** G4VRML1Viewer::SetView(): No effects" << G4endl;
#endif
}

void G4VRML1Viewer::DrawView()
{
#if defined DEBUG_FR_VIEW
	G4cerr << "***** G4VRML1Viewer::DrawView()" << G4endl;
#endif

	fSceneHandler.VRMLBeginModeling();

	// Here is a minimal DrawView() function.
	NeedKernelVisit();
	ProcessView();
	FinishView();
}

void G4VRML1Viewer::ClearView(void)
{
#if defined DEBUG_FR_VIEW
  G4cerr << "***** G4VRML1Viewer::ClearView(): No effects" << G4endl;
#endif
}

void G4VRML1Viewer::ShowView(void)
{
#if defined DEBUG_FR_VIEW
  G4cerr << "***** G4VRML1Viewer::ShowView()" << G4endl;
#endif
	fSceneHandler.VRMLEndModeling();
}

void G4VRML1Viewer::FinishView(void)
{
#if defined DEBUG_FR_VIEW
  G4cerr << "***** G4VRML1Viewer::FinishView(): No effects" << G4endl;
#endif
}

#endif