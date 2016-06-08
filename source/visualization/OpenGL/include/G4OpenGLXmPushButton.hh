// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4OpenGLXmPushButton.hh,v 1.3 1999/12/15 14:54:05 gunter Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
// 
//Push button class. Inherits from G4OpenGLXmVWidgetComponent

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#ifndef G4OPENGLXMPUSHBUTTON_HH
#define G4OPENGLXMPUSHBUTTON_HH

#include "G4OpenGLXmVWidgetComponent.hh"

class G4OpenGLXmPushButton : public G4OpenGLXmVWidgetComponent
{

public:
  G4OpenGLXmPushButton (char* = NULL,
			XtCallbackRec* = NULL); //constructor
  ~G4OpenGLXmPushButton ();                     //destructor

  void SetName (char*);
  char* GetName ();

  void AddYourselfTo (G4OpenGLXmVWidgetContainer*);

  Widget* GetPointerToParent ();
  Widget* GetPointerToWidget ();

private:
  char* name;
  XtCallbackRec* callback;
  Widget button;
  Widget* parent;
};

#endif

#endif