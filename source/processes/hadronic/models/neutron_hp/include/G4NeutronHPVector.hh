// This code implementation is the intellectual property of
// neutron_hp -- header file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NeutronHPVector.hh,v 1.14 2000/11/20 10:07:41 hpw Exp $
// GEANT4 tag $Name: geant4-03-00 $
//
#ifndef G4NeutronHPVector_h
#define G4NeutronHPVector_h 1

#include "G4NeutronHPDataPoint.hh"
#include "G4PhysicsVector.hh"
#include "G4NeutronHPInterpolator.hh"
#include "Randomize.hh"
#include "G4ios.hh"
#include "g4std/fstream"
#include "G4InterpolationManager.hh"
#include "G4NeutronHPInterpolator.hh"
#include "G4NeutronHPHash.hh"
#include <math.h>
#include "g4std/vector"

class G4NeutronHPVector
{
  friend G4NeutronHPVector & operator + (G4NeutronHPVector & left, 
                                         G4NeutronHPVector & right);
  
  public:
  
  G4NeutronHPVector();

  G4NeutronHPVector(G4int n);
  
  ~G4NeutronHPVector();
  
  G4NeutronHPVector & operator = (const G4NeutronHPVector & right);
  
  inline void SetVerbose(G4int ff)
  {
    Verbose = ff;
  }
  
  inline void Times(G4double factor)
  {
    G4int i;
    for(i=0; i<nEntries; i++)
    {
      theData[i].SetY(theData[i].GetY()*factor);
    }
    if(theIntegral!=NULL)
    {
      theIntegral[i] *= factor;
    }
  }
  
  inline void SetPoint(G4int i, const G4NeutronHPDataPoint & it)
  {
    G4double x = it.GetX();
    G4double y = it.GetY();
    SetData(i, x, y);
  }
    
  inline void SetData(G4int i, G4double x, G4double y) 
  { 
//    G4cout <<"G4NeutronHPVector::SetData called"<<nPoints<<" "<<nEntries<<G4endl;
    Check(i);
    if(y>maxValue) maxValue=y;
    theData[i].SetData(x, y);
  }
  inline void SetX(G4int i, G4double e)
  {
    Check(i);
    theData[i].SetX(e);
  }
  inline void SetEnergy(G4int i, G4double e)
  {
    Check(i);
    theData[i].SetX(e);
  }
  inline void SetY(G4int i, G4double x)
  {
    Check(i);
    if(x>maxValue) maxValue=x;
    theData[i].SetY(x);
  }
  inline void SetXsec(G4int i, G4double x)
  {
    Check(i);
    if(x>maxValue) maxValue=x;
    theData[i].SetY(x);
  }
  inline G4double GetEnergy(G4int i) const { return theData[i].GetX(); }
  inline G4double GetXsec(G4int i) { return theData[i].GetY(); }
  inline G4double GetX(G4int i) const 
  { 
    if (i<0) i=0;
    if(i>=GetVectorLength()) i=GetVectorLength()-1;
    return theData[i].GetX();
  }
  inline const G4NeutronHPDataPoint & GetPoint(G4int i) const { return theData[i]; }
  
  void Hash() 
  {
    G4int i;
    G4double x, y;
    for(i=0 ; i<nEntries; i++)
    {
      if(0 == (i+1)%10)
      {
        x = GetX(i);
	y = GetY(i);
	theHash.SetData(i, x, y);
      }
    }
  }
  
  void ReHash()
  {
    theHash.Clear();
    Hash();
  }
  
  G4double GetXsec(G4double e);

  inline G4double GetY(G4double x)  {return GetXsec(x);}
  inline G4int GetVectorLength() const {return nEntries;}

  inline G4double GetY(G4int i)
  { 
    if (i<0) i=0;
    if(i>=GetVectorLength()) i=GetVectorLength()-1;
    return theData[i].GetY(); 
  }

  inline G4double GetY(G4int i) const
  {
    if (i<0) i=0;
    if(i>=GetVectorLength()) i=GetVectorLength()-1;
    return theData[i].GetY(); 
  }
  void Dump();
  
  inline void InitInterpolation(G4std::ifstream & aDataFile)
  {
    theManager.Init(aDataFile);
  }
  
  void Init(G4std::ifstream & aDataFile, G4int total, G4double ux=1., G4double uy=1.)
  {
    G4double x,y;
    for (G4int i=0;i<total;i++)
    {
      aDataFile >> x >> y;
      x*=ux;
      y*=uy;
      SetData(i,x,y);
      if(0 == nEntries%10)
      {
        theHash.SetData(nEntries-1, x, y);
      }
    }
  }
  
  void Init(G4std::ifstream & aDataFile,G4double ux=1., G4double uy=1.)
  {
    G4int total;
    aDataFile >> total;
    if(theData!=NULL) delete [] theData;
    theData = new G4NeutronHPDataPoint[total]; 
    nPoints=total;
    nEntries=0;    
    theManager.Init(aDataFile);
    Init(aDataFile, total, ux, uy);
  }
  
  void ThinOut(G4double precision);
  
  inline void SetLabel(G4double aLabel)
  {
    label = aLabel;
  }
  
  inline G4double GetLabel()
  {
    return label;
  }
  
  inline void CleanUp()
  {
    nEntries=0;   
    theManager.CleanUp();
    maxValue = -DBL_MAX;
  }

  // merges the vectors active and passive into *this
  inline void Merge(G4NeutronHPVector * active, G4NeutronHPVector * passive)
  {
    CleanUp();
    G4int s = 0, n=0, i=0, m=0;
    G4bool flag;
    G4NeutronHPVector * tmp;
    G4int a = s, p = n, t;
    while (a<active->GetVectorLength()&&p<passive->GetVectorLength())
    {
      if(active->GetEnergy(a) <= passive->GetEnergy(p))
      {
        G4double xa  = active->GetEnergy(a);
        G4double yy = active->GetXsec(a);
        SetData(m, xa, yy);
        theManager.AppendScheme(m, active->GetScheme(a));
        m++;
        a++;
        G4double xp = passive->GetEnergy(p);
        if( abs(abs(xp-xa)/xa)<0.001 ) p++;
      } else {
        tmp = active; 
        t=a;
        active = passive; 
        a=p;
        passive = tmp; 
        p=t;
      }
    }
    while (a!=active->GetVectorLength())
    {
      SetData(m, active->GetEnergy(a), active->GetXsec(a));
      theManager.AppendScheme(m++, active->GetScheme(a));
      a++;
    }
    while (p!=passive->GetVectorLength())
    {
      if(abs(GetEnergy(m)-passive->GetEnergy(p))/passive->GetEnergy(p)>0.001)
      {
        SetData(m, passive->GetEnergy(p), passive->GetXsec(p));
        theManager.AppendScheme(m++, active->GetScheme(p));
      }
      p++;
    }
  }    
  
  void Merge(G4InterpolationScheme aScheme, G4double aValue, 
             G4NeutronHPVector * active, G4NeutronHPVector * passive);
  
  G4double SampleLin() // Samples X according to distribution Y, linear int
  {
    G4double result;
    if(theIntegral==NULL) IntegrateAndNormalise();
    if(GetVectorLength()==1)
    {
      result = theData[0].GetX();
    }
    else
    {
      G4int i;
      G4double rand = G4UniformRand();
      
      // this was replaced 
//      for(i=1;i<GetVectorLength();i++)
//      {
//	if(rand<theIntegral[i]/theIntegral[GetVectorLength()-1]) break;
//      }

// by this (begin)
      for(i=GetVectorLength()-1; i>=0 ;i--)
      {
	if(rand>theIntegral[i]/theIntegral[GetVectorLength()-1]) break;
      }
      if(i!=GetVectorLength()-1) i++;
// until this (end)
      
      G4double x1, x2, y1, y2;
      y1 = theData[i-1].GetX();
      x1 = theIntegral[i-1];
      y2 = theData[i].GetX();
      x2 = theIntegral[i];
      if(abs((y2-y1)/y2)<0.0000001) // not really necessary, since the case is excluded by construction
      {
	y1 = theData[i-2].GetX();
	x1 = theIntegral[i-2];
      }
      result = theLin.Lin(rand, x1, x2, y1, y2);
    }
    return result;
  }
  
  G4double Sample(); // Samples X according to distribution Y
  
  G4double * Debug()
  {
    return theIntegral;
  }

  inline void IntegrateAndNormalise()
  {
    G4int i;
    if(theIntegral!=NULL) return;
    theIntegral = new G4double[nEntries];
    if(nEntries == 1)
    {
      theIntegral[0] = 1;
      return;
    }
    theIntegral[0] = 0;
    G4double sum = 0;
    for(i=1;i<GetVectorLength();i++)
    {
      if(abs((theData[i].GetX()-theData[i-1].GetX())/theData[i].GetX())>0.0000001)
      {
        sum+= 0.5*(theData[i].GetY()+theData[i-1].GetY())*
                  (theData[i].GetX()-theData[i-1].GetX());
      }
      theIntegral[i] = sum;
    }
    G4double total = theIntegral[GetVectorLength()-1];
    for(i=1;i<GetVectorLength();i++)
    {
      theIntegral[i]/=total;
    }
  }

  inline void Integrate() 
  {
    G4int i;
    if(nEntries == 1)
    {
      totalIntegral = 0;
      return;
    }
    G4double sum = 0;
    for(i=1;i<GetVectorLength();i++)
    {
      if(abs((theData[i].GetX()-theData[i-1].GetX())/theData[i].GetX())>0.0000001)
      {
        G4double x1 = theData[i-1].GetX();
        G4double x2 = theData[i].GetX();
        G4double y1 = theData[i-1].GetY();
        G4double y2 = theData[i].GetY();
        G4InterpolationScheme aScheme = theManager.GetScheme(i);
        if(aScheme==LINLIN||aScheme==CLINLIN||aScheme==ULINLIN)
        {
          sum+= 0.5*(y2+y1)*(x2-x1);
        }
        else if(aScheme==LINLOG||aScheme==CLINLOG||aScheme==ULINLOG)
        {
          G4double a = y1;
          G4double b = (y2-y1)/(log(x2)-log(x1));
          sum+= (a-b)*(x2-x1) + b*(x2*log(x2)-x1*log(x1));
        }
        else if(aScheme==LOGLIN||aScheme==CLOGLIN||aScheme==ULOGLIN)
        {
          G4double a = log(y1);
          G4double b = (log(y2)-log(y1))/(x2-x1);
          sum += (exp(a)/b)*(exp(b*x2)-exp(b*x1));
        }
        else if(aScheme==HISTO||aScheme==CHISTO||aScheme==UHISTO)
        {
          sum+= y1*(x2-x1);
        }
        else if(aScheme==LOGLOG||aScheme==CLOGLOG||aScheme==ULOGLOG)
        {
          G4double a = log(y1);
          G4double b = (log(y2)-log(y1))/(log(x2)-log(x1));
          sum += (exp(a)/(b+1))*(pow(x2,b+1)-pow(x1,b+1));
        }
        else
        {
          G4Exception("Unknown interpolation scheme in G4NeutronHPVector::Integrate");
        }
          
      }
    }
    totalIntegral = sum;
  }
  
  inline G4double GetIntegral() // linear interpolation; use with care
  { 
    if(totalIntegral<-0.5) Integrate();
    return totalIntegral; 
  }
  
  inline void SetInterpolationManager(const G4InterpolationManager & aManager)
  {
    theManager = aManager;
  }
  
  inline const G4InterpolationManager & GetInterpolationManager() const
  {
    return theManager;
  }
  
  inline void SetInterpolationManager(G4InterpolationManager & aMan)
  {
    theManager = aMan;
  }
  
  inline void SetScheme(G4int aPoint, const G4InterpolationScheme & aScheme)
  {
    theManager.AppendScheme(aPoint, aScheme);
  }
  
  inline G4InterpolationScheme GetScheme(G4int anIndex)
  {
    return theManager.GetScheme(anIndex);
  }
  
  G4double GetMeanX()
  {
    G4double result;
    G4double running = 0;
    G4double weighted = 0;
    for(G4int i=1; i<nEntries; i++)
    {
      running += theInt.GetBinIntegral(theManager.GetScheme(i-1),
                           theData[i-1].GetX(), theData[i].GetX(),
                           theData[i-1].GetY(), theData[i].GetY());
      weighted += theInt.GetWeightedBinIntegral(theManager.GetScheme(i-1),
                           theData[i-1].GetX(), theData[i].GetX(),
                           theData[i-1].GetY(), theData[i].GetY());
    }  
    result = weighted / running;  
    return result;
  }
  
  void Block(G4double aX)
  {
    theBlocked.push_back(aX);
  }
  
  void Buffer(G4double aX)
  {
    theBuffered.push_back(aX);
  }
  
  G4std::vector<G4double> GetBlocked() {return theBlocked;}
  G4std::vector<G4double> GetBuffered() {return theBuffered;}
  
  void SetBlocked(const G4std::vector<G4double> &aBlocked) {theBlocked = aBlocked;}
  void SetBuffered(const G4std::vector<G4double> &aBuffer) {theBuffered = aBuffer;}

  G4double Get15percentBorder();
  G4double Get50percentBorder();
  
  private:
  
  void Check(G4int i);
  
  G4bool IsBlocked(G4double aX);
  
  private:
  
  G4NeutronHPInterpolator theLin;
  
  private:
  
  G4double totalIntegral;
  
  G4NeutronHPDataPoint * theData; // the data
  G4InterpolationManager theManager; // knows how to interpolate the data.
  G4double * theIntegral;
  G4int nEntries;
  G4int nPoints;
  G4double label;
  
  G4NeutronHPInterpolator theInt;
  G4int Verbose;
  // debug only
  G4int isFreed;
  
  G4NeutronHPHash theHash;
  G4double maxValue;
  
  G4std::vector<G4double> theBlocked;
  G4std::vector<G4double> theBuffered;
  G4double the15percentBorderCash;
  G4double the50percentBorderCash;

};

#endif