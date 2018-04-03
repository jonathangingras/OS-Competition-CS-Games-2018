# Operating System Competition

**All the source code MUST remain secret before the CS Games 2018.**


# Statement

Both French and English statements are written in Markdown language and are stored in the `statement` directory.


## Compilation & Installation

Compiling and installing everything needed for the competition is done by running the following in a terminal, assuming your present working directory is `os` and you are NOT using sudo (sudo password will be asked during execution):

```Shell
$ bash install.sh
```


## Post-installation

ALL CONTENT OF THIS DIRECTORY MUST BE REMOVED FROM THE CONTESTANTS' VM AFTER THE INSTALLATION PROCESS.
THEY MAY NOT HAVE ACCESS TO SOURCE CODE FOR THE COMPETITION.


## Kernel Module (Behind the scene, core of the challenge)

The kernel module is the virtual device that must be manipulated by the challenge library to be implemented by the contestants.


## Middleware C API (The actual challenge)

The challenge is to implement the functions found in `c_api/include/kiki_api.h`


## Unit Tests (Correction)

Correction will be done using Google Tests.
