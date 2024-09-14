
<h1 align="center">
  <br>
  <a href="http://dual.sphysics.org/"><img src="http://design.sphysics.org/img/logo_dualsphysics.png" alt="DualSPHysics" width="300"></a>
  <br>
  DualSPHysics
  <br>
</h1>

<h4 align="center"><a href="http://www.dual.sphysics.org" target="_blank">DualSPHysics</a> is based on the Smoothed Particle Hydrodynamics model named <a href="http://www.sphysics.org" target="_blank">SPHysics</a>.</h4>

<h4 align="center">The code is developed to study free-surface flow phenomena where Eulerian methods can be difficult to apply, such as waves or impact of dam-breaks on off-shore structures. DualSPHysics is a set of C++, <a href="https://developer.nvidia.com/cuda-zone" target="_blank">CUDA</a> (replaced with <a href="https://rocm.docs.amd.com/en/latest/" target="_blank">AMD ROCm</a> in this fork) and Java codes designed to deal with real-life engineering problems.</h4>

# This is a fork adjusted for AMD ROCm

# Instructions for regular users

If you only want a copy of DualSPHysics to create and run cases in your system, you probably want <a href="http://www.dual.sphysics.org/index.php/downloads/" target="_blank">the full DualSPHysics package</a> from the official website. There you will find documentation and packages of different versions for different Operating Systems.

It is possible that you want the latest version in this repository that is not yet uploaded in the official web page. In this case check the [Building the project](#building-the-project) section to build an executable.

Have in mind that DualSPHysics needs a case already created to execute the SPH solver, so you need to use GenCase, which is included the main package on the <a href="http://www.dual.sphysics.org/index.php/downloads/" target="_blank">DualSPHysics webpage</a>.

If you need help check out the wiki for this project.

# Instructions for developers

If you are a developer and want to use this code check the following guides.

Take into account that for pre- and post-processing you will need to use GenCase and the different post-processing tools included in the main DualSPHysics package, <a href="http://www.dual.sphysics.org/index.php/downloads/" target="_blank"> here</a>. If you compile your own DualSPHyiscs version just overwrite the one in the package.

## Developing a modified version to fit your own needs.

You can fork this repository and change or add anything you want. Keep in mind that your changes will not be taken into account into the main versions. If your objective is to implement your changes/improvements to the main code, check the next section.

## Developing a modified or improved version to contribute to the project.

We appreciate your efforts! But please, if you are trying to develop/implement a functionality to be added to the main repository, be sure to follow the steps described in the [CONTRIBUTING.md](CONTRIBUTING.md) file. 

# Building the project

## Microsoft Windows

This fork is aimed for Linux/AMD ROCm.

## GNU/Linux

### Using Makefile

You can build the project in GNU/Linux using the [Makefile](src/source/Makefile) included in the source folder. Follow these steps (for the GPU version):

1. Clone this repository into your system `git clone https://github.com/kwahoo2/DualSPHysics.git`
2. In a terminal, go to the folder `cd DualSPHysics/src/source/`
3. Edit the `Makefile` file with a text editor and then:
   * Set the `DIRTOOLKIT` variable with the path to ROCm in your system e.g. `DIRTOOLKIT=/opt/rocm-6.1.2`
   * Adjust the `CCFLAGS` variable with info got from the `hipconfig --cxx_config` command, e.g. `CCFLAGS +=-D__HIP_PLATFORM_HCC__= -D__HIP_PLATFORM_AMD__= -I/usr/include -I/usr/lib64/llvm17/bin/../../../lib/clang/17`
4. Execute `make clean` to make sure the environment is clean and ready to compile.
5. Execute `make`

Note: Some Linux distributions have ROCm/HIP prepackaged. Eg. for Fedora:

`sudo dnf install rocm-core-devel rocm-hip-devel rocprim-devel`

After compiling you should see a message like `--- Compiled Release GPU/CPU version ---`. Go to `bin/linux/` to check that `DualSPHyiscs5.2_linux64` or `DualSPHyiscs5.2CPU_linux64` is there and build correctly.

**For the CPU version**: If you want to compile de CPU version just ignore HIP and use the makefile `Makefile_cpu`. To specify a different file to `make`, use the `-f` parameter: `make -f Makefile_cpu`

# Graphical user interface (GUI)

<h1 align="center">
  <a href="http://design.sphysics.org/"><img src="https://i.imgur.com/D5dabSD.png" alt="DualSPHysics" width="1000"></a>
</h1>

Please check [DesignSPHysics website](http://design.sphysics.org/).

# Advanced visualisation with Blender

<h1 align="center">
  <a href="http://visual.sphysics.org/"><img src="https://i.imgur.com/I1psKiT.png" alt="DualSPHysics" width="1000"></a>
</h1>

Please check [VisualSPHysics website](http://visual.sphysics.org/).

# Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) if you want to make changes to the code.

# Authors and people involved

* **Dr Jose M. Dominguez Alonso** - *Main Developer*
* **Dr Alejandro J.C. Crespo**
* **Prof. Moncho Gomez Gesteira**
* **Prof. Benedict D. Rogers**
* **Dr Georgios Fourtakas**
* **Prof. Peter Stansby**
* **Dr Renato Vacondio**
* **Dr Corrado Altomare**
* **Dr Angelo Tafuni**
* **Orlando Garcia Feal**
* **Ivan Martinez Estevez**
* **Dr Joseph O'Connor**
* **Dr Aaron English**


## Former people involved
* **Dr Jose Gonzalez Cao**
* **Dr Ricardo Canelas**
* **Dr Athanasios Mokos**
* **Dr Stephen Longshaw**
* **Dr Anxo Barreiro**

See also the list of [contributors](https://github.com/dualsphysics/DualSPHysics/contributors) who participated in this project.

## License

This project is licensed under the LGPL License - see the [LICENSE](LICENSE) file for details.
