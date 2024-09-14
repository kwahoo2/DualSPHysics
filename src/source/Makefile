#DualSPHysics GPU/CPU v5.2.251 23-09-2022

#=============== Compilation Options (YES/NO) ===============
USE_DEBUG=NO
USE_FAST_MATH=YES
USE_NATIVE_CPU_OPTIMIZATIONS=NO
COMPILE_VTKLIB=YES
COMPILE_NUMEXLIB=YES
COMPILE_CHRONO=YES
COMPILE_WAVEGEN=YES
COMPILE_MOORDYN=YES

LIBS_DIRECTORIES=-L./
LIBS_DIRECTORIES:=$(LIBS_DIRECTORIES) -L../lib/linux_gcc

EXECNAME=DualSPHysics5.2_linux64
EXECS_DIRECTORY=../../bin/linux

# -std=c++0x ---> Used to avoid errors for calls to enums
ifeq ($(USE_DEBUG), YES)
  CCFLAGS=-c -O0 -g -Wall -fopenmp -D_WITHGPU -std=c++0x
else
  CCFLAGS=-c -O3 -fopenmp -D_WITHGPU -std=c++0x
  ifeq ($(USE_FAST_MATH), YES)
    CCFLAGS+= -ffast-math
  endif
  ifeq ($(USE_NATIVE_CPU_OPTIMIZATIONS), YES)
    CCFLAGS+= -march=native
  endif
endif
CC=hipcc
CCLINKFLAGS=-fopenmp -lgomp
#use to find paths: hipconfig --cxx_config
CCFLAGS +=-D__HIP_PLATFORM_HCC__= -D__HIP_PLATFORM_AMD__= -I/usr/include -I/usr/lib64/llvm17/bin/../../../lib/clang/17

ifeq ($(COMPILE_VTKLIB), NO)
  CCFLAGS:=$(CCFLAGS) -DDISABLE_VTKLIB
endif
ifeq ($(COMPILE_NUMEXLIB), NO)
  CCFLAGS:=$(CCFLAGS) -DDISABLE_NUMEXLIB
endif
ifeq ($(COMPILE_CHRONO), NO)
  CCFLAGS:=$(CCFLAGS) -DDISABLE_CHRONO
endif
ifeq ($(COMPILE_WAVEGEN), NO)
  CCFLAGS:=$(CCFLAGS) -DDISABLE_WAVEGEN
endif
ifeq ($(COMPILE_MOORDYN), NO)
  CCFLAGS:=$(CCFLAGS) -DDISABLE_MOORDYN
endif

#=============== HIP ROCM toolkit directory (make appropriate for local ROCM installation) ===============
DIRTOOLKIT=/usr

#=============== Files to compile ===============
OBJXML=JXml.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o
OBJSPHMOTION=JMotion.o JMotionList.o JMotionMov.o JMotionObj.o JMotionPos.o JDsMotion.o
OBCOMMON=Functions.o FunGeo3d.o FunSphKernelsCfg.o JAppInfo.o JBinaryData.o JCfgRunBase.o JDataArrays.o JException.o JLinearValue.o JLog2.o JObject.o JOutputCsv.o JRadixSort.o JRangeFilter.o JReadDatafile.o JSaveCsv2.o JTimeControl.o randomc.o
OBCOMMONDSPH=JDsphConfig.o JDsPips.o JPartDataBi4.o JPartDataHead.o JPartFloatBi4.o JPartOutBi4Save.o JCaseCtes.o JCaseEParms.o JCaseParts.o JCaseProperties.o JCaseUserVars.o JCaseVtkOut.o
OBSPH=JArraysCpu.o JCellDivCpu.o JSphCfgRun.o JComputeMotionRef.o JDsDcell.o JDsDamping.o JDsExtraData.o JDsGaugeItem.o JDsGaugeSystem.o JDsPartsOut.o JDsSaveDt.o JSphShifting.o JSph.o JDsAccInput.o JSphCpu.o JDsInitialize.o JFtMotionSave.o JSphMk.o JDsPartsInit.o JDsFixedDt.o JDsViscoInput.o JDsOutputTime.o JDsTimers.o JWaveSpectrumGpu.o main.o
OBSPHSINGLE=JCellDivCpuSingle.o JPartsLoad4.o JSphCpuSingle.o
OBCOMMONGPU=FunctionsCuda.o JObjectGpu.o 
OBSPHGPU=JArraysGpu.o JDebugSphGpu.o JCellDivGpu.o JSphGpu.o JDsGpuInfo.o 
OBSPHSINGLEGPU=JCellDivGpuSingle.o JSphGpuSingle.o
OBCUDA=JCellDivGpu_ker.o JCellDivGpuSingle_ker.o JDsPips_ker.o JDsGauge_ker.o JReduSum_ker.o JSphShifting_ker.o JDsAccInput_ker.o JSphGpu_ker.o JSphGpuSimple_ker.o JWaveOrder2_ker.o

OBWAVERZ=JMLPistonsGpu.o JRelaxZonesGpu.o
OBWAVERZCUDA=JRelaxZone_ker.o
OBCHRONO=JChronoObjects.o
OBMOORDYN=JDsMooredFloatings.o JDsFtForcePoints.o
OBINOUT=JSphCpu_InOut.o JSphCpuSingle_InOut.o JSphInOut.o JSphInOutZone.o JSphInOutGridData.o JSphInOutPoints.o JSphInOutVel.o JSphInOutVelAwas.o JSphInOutZsurf.o JSimpleNeigs.o
OBINOUTGPU=JSphGpuSingle_InOut.o
OBMDBC=JPartNormalData.o

OBJECTS=$(OBJXML) $(OBJSPHMOTION) $(OBCOMMON) $(OBCOMMONDSPH) $(OBSPH) $(OBSPHSINGLE)
OBJECTS:=$(OBJECTS) $(OBCOMMONGPU) $(OBSPHGPU) $(OBSPHSINGLEGPU) $(OBCUDA)
OBJECTS:=$(OBJECTS) $(OBWAVERZ) $(OBWAVERZCUDA) $(OBCHRONO) $(OBMOORDYN) $(OBINOUT) $(OBINOUTGPU) $(OBMDBC)

#=============== DualSPHysics libs to be included ===============
JLIBS=${LIBS_DIRECTORIES}
ifeq ($(COMPILE_VTKLIB), YES)
  JLIBS:=$(JLIBS) -ljvtklib_64
endif
ifeq ($(COMPILE_NUMEXLIB), YES)
  JLIBS:=$(JLIBS) -ljnumexlib_64
endif
ifeq ($(COMPILE_CHRONO), YES)
  JLIBS:=$(JLIBS) -ldsphchrono -lChronoEngine 
endif
ifeq ($(COMPILE_WAVEGEN), YES)
  JLIBS:=$(JLIBS) -ljwavegen_64
endif
ifeq ($(COMPILE_MOORDYN), YES)
  JLIBS:=$(JLIBS) -ldsphmoordyn_64
endif

#=============== GPU Code Compilation ===============
CCFLAGS := $(CCFLAGS) -I./ -I$(DIRTOOLKIT)/include
CCLINKFLAGS := $(CCLINKFLAGS) -L$(DIRTOOLKIT)/lib64 -ldl -lrt

NCC=hipcc
ifeq ($(USE_DEBUG), NO)
  NCCFLAGS+=-c $(GENCODE) -O3
else
  NCCFLAGS+=-c $(GENCODE) -O0
endif
ifeq ($(USE_FAST_MATH), YES)
  NCCFLAGS+= -use_fast_math
endif

all:$(EXECS_DIRECTORY)/$(EXECNAME)
	rm -rf *.o
ifeq ($(USE_DEBUG), NO)
	@echo "  --- Compiled Release GPU version ---"
else
	@echo "  --- Compiled Debug GPU version ---"
	mv $(EXECS_DIRECTORY)/$(EXECNAME) $(EXECNAME)_debug
endif

$(EXECS_DIRECTORY)/$(EXECNAME):  $(OBJECTS)
	$(CC) $(OBJECTS) $(CCLINKFLAGS) -o $@ $(JLIBS)

.cpp.o: 
	$(CC) $(CCFLAGS) $< 

JSphGpu_ker.o: JSphGpu_ker.cu
	$(NCC) $(NCCFLAGS) JSphGpu_ker.cu

JSphGpuSimple_ker.o: JSphGpuSimple_ker.cu
	$(NCC) $(NCCFLAGS) JSphGpuSimple_ker.cu

JCellDivGpu_ker.o: JCellDivGpu_ker.cu
	$(NCC) $(NCCFLAGS) JCellDivGpu_ker.cu

JCellDivGpuSingle_ker.o: JCellDivGpuSingle_ker.cu
	$(NCC) $(NCCFLAGS) JCellDivGpuSingle_ker.cu

JSphShifting_ker.o: JSphShifting_ker.cu
	$(NCC) $(NCCFLAGS) JSphShifting_ker.cu

JDsAccInput_ker.o: JDsAccInput_ker.cu
	$(NCC) $(NCCFLAGS) JDsAccInput_ker.cu

JDsPips_ker.o: JDsPips_ker.cu
	$(NCC) $(NCCFLAGS) JDsPips_ker.cu

JDsGauge_ker.o: JDsGauge_ker.cu
	$(NCC) $(NCCFLAGS) JDsGauge_ker.cu

JWaveOrder2_ker.o: JWaveOrder2_ker.cu
	$(NCC) $(NCCFLAGS) JWaveOrder2_ker.cu

JReduSum_ker.o: JReduSum_ker.cu
	$(NCC) $(NCCFLAGS) JReduSum_ker.cu

JRelaxZone_ker.o: JRelaxZone_ker.cu
	$(NCC) $(NCCFLAGS) JRelaxZone_ker.cu

clean:
	rm -rf *.o $(EXECNAME) $(EXECNAME)_debug

