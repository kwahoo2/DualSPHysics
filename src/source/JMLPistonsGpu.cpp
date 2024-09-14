//HEAD_DSPH
/*
 <DUALSPHYSICS>  Copyright (c) 2020 by Dr Jose M. Dominguez et al. (see http://dual.sphysics.org/index.php/developers/). 

 EPHYSLAB Environmental Physics Laboratory, Universidade de Vigo, Ourense, Spain.
 School of Mechanical, Aerospace and Civil Engineering, University of Manchester, Manchester, U.K.

 This file is part of DualSPHysics. 

 DualSPHysics is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
 as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 DualSPHysics is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 

 You should have received a copy of the GNU Lesser General Public License along with DualSPHysics. If not, see <http://www.gnu.org/licenses/>. 
*/

/// \file JMLPistonsGpu.cpp \brief Implements the class \ref JMLPistonsGpu.

#include "JMLPistonsGpu.h"
#ifdef _WITHGPU
  #include <hip/hip_runtime_api.h>
#endif

using namespace std;

//##############################################################################
//# JMLPistonsGpu
//##############################################################################
//==============================================================================
/// Constructor.
//==============================================================================
JMLPistonsGpu::JMLPistonsGpu(){
  ClassName="JMLPistonsGpu";
  PistonIdg=NULL; MovVelg=NULL;
  MemGpuFixed=0; 
}

//==============================================================================
/// Destructor.
//==============================================================================
JMLPistonsGpu::~JMLPistonsGpu(){
  DestructorActive=true; 
  FreeMemoryGpu();
}

//==============================================================================
/// Frees GPU memory.
//==============================================================================
void JMLPistonsGpu::FreeMemoryGpu(){
  MemGpuFixed=0;
  #ifdef _WITHGPU
    //-GPU memory for List1d.
    if(PistonIdg)hipFree(PistonIdg);  PistonIdg=NULL;
    if(MovVelg)  hipFree(MovVelg);    MovVelg=NULL;
  #endif 
}

//==============================================================================
/// Allocates GPU memory for PistonIdg and MovVelg.
//==============================================================================
void JMLPistonsGpu::PreparePiston1d(unsigned sizepistonid,const byte *pistonid,unsigned sizemovvel){
  #ifdef _WITHGPU
    hipMalloc((void**)&PistonIdg,sizeof(byte)*sizepistonid);
    hipMemcpy(PistonIdg,pistonid,sizeof(byte)*sizepistonid,hipMemcpyHostToDevice);
    hipMalloc((void**)&MovVelg,sizeof(double)*sizemovvel);
    MemGpuFixed=sizeof(byte)*sizepistonid;
    MemGpuFixed+=sizeof(double)*sizemovvel;
  #endif 
}

//==============================================================================
/// Copies MovVel data on GPU memory.
//==============================================================================
void JMLPistonsGpu::CopyMovVel(unsigned sizemovvel,const double *movvel){
  #ifdef _WITHGPU
    hipMemcpy(MovVelg,movvel,sizeof(double)*sizemovvel,hipMemcpyHostToDevice);
  #endif 
}


//##############################################################################
//# JMLPiston2DGpu
//##############################################################################
//==============================================================================
/// Constructor.
//==============================================================================
JMLPiston2DGpu::JMLPiston2DGpu(){
  ClassName="JMLPiston2DGpu";
  Size=0; MovVelyzg=NULL;
}

//==============================================================================
/// Destructor.
//==============================================================================
JMLPiston2DGpu::~JMLPiston2DGpu(){
  DestructorActive=true; 
  FreeMemoryGpu();
}

//==============================================================================
/// Frees GPU memory.
//==============================================================================
void JMLPiston2DGpu::FreeMemoryGpu(){
  Size=0;
  #ifdef _WITHGPU
    if(MovVelyzg)hipFree(MovVelyzg);  MovVelyzg=NULL;
  #endif 
}

//==============================================================================
/// Allocates GPU memory for MovVelyzg of pistons 2D.
//==============================================================================
void JMLPiston2DGpu::AllocMemoryGpu(unsigned size){
  #ifdef _WITHGPU
    FreeMemoryGpu();
    Size=size;
    hipMalloc((void**)&MovVelyzg,sizeof(double)*Size);
  #endif 
}

//==============================================================================
/// Copies MovVelyz data on GPU memory.
//==============================================================================
void JMLPiston2DGpu::CopyMovVelyz(const double *movvelyz){
  #ifdef _WITHGPU
    hipMemcpy(MovVelyzg,movvelyz,sizeof(double)*Size,hipMemcpyHostToDevice);
  #endif 
}


