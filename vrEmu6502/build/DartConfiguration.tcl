# This file is configured by CMake automatically as DartConfiguration.tcl
# If you choose not to use CMake, this file may be hand configured, by
# filling in the required variables.


# Configuration directories and files
SourceDirectory: /data/data/com.termux.nix/files/home/6502-OS/vrEmu6502
BuildDirectory: /data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build

# Where to place the cost data store
CostDataFile: 

# Site is something like machine.domain, i.e. pragmatic.crd
Site: localhost

# Build name is osname-revision-compiler, i.e. Linux-2.4.2-2smp-c++
BuildName: Linux-g++

# Subprojects
LabelsForSubprojects: 

# Submission information
SubmitURL: http://
SubmitInactivityTimeout: 

# Dashboard start time
NightlyStartTime: 00:00:00 EDT

# Commands for the build/test/submit cycle
ConfigureCommand: "/nix/store/1a5svak36dh5d8av1vq7bjxapii6zjpl-cmake-3.29.2/bin/cmake" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502"
MakeCommand: /nix/store/1a5svak36dh5d8av1vq7bjxapii6zjpl-cmake-3.29.2/bin/cmake --build . --config "${CTEST_CONFIGURATION_TYPE}"
DefaultCTestConfigurationType: Release

# version control
UpdateVersionOnly: 

# CVS options
# Default is "-d -P -A"
CVSCommand: 
CVSUpdateOptions: 

# Subversion options
SVNCommand: 
SVNOptions: 
SVNUpdateOptions: 

# Git options
GITCommand: /nix/store/zi43s4ys881g0fm76c58rjqfzys99d22-git-with-svn-2.44.2/bin/git
GITInitSubmodules: 
GITUpdateOptions: 
GITUpdateCustom: 

# Perforce options
P4Command: 
P4Client: 
P4Options: 
P4UpdateOptions: 
P4UpdateCustom: 

# Generic update command
UpdateCommand: /nix/store/zi43s4ys881g0fm76c58rjqfzys99d22-git-with-svn-2.44.2/bin/git
UpdateOptions: 
UpdateType: git

# Compiler info
Compiler: /nix/store/ay527x633kv7j8ani3rrv6mhgbkddpl8-gcc-wrapper-13.2.0/bin/g++
CompilerVersion: 13.2.0

# Dynamic analysis (MemCheck)
PurifyCommand: 
ValgrindCommand: 
ValgrindCommandOptions: 
DrMemoryCommand: 
DrMemoryCommandOptions: 
CudaSanitizerCommand: 
CudaSanitizerCommandOptions: 
MemoryCheckType: 
MemoryCheckSanitizerOptions: 
MemoryCheckCommand: /nix/store/b8z2g3f30l0dai8ywsw2awggix8fgh0d-valgrind-3.22.0/bin/valgrind
MemoryCheckCommandOptions: 
MemoryCheckSuppressionFile: 

# Coverage
CoverageCommand: /nix/store/drdj5v9dz6gj7k3hg9rk2vfsfy95mb8z-gcc-13.2.0/bin/gcov
CoverageExtraFlags: -l

# Testing options
# TimeOut is the amount of time in seconds to wait for processes
# to complete during testing.  After TimeOut seconds, the
# process will be summarily terminated.
# Currently set to 25 minutes
TimeOut: 1500

# During parallel testing CTest will not start a new test if doing
# so would cause the system load to exceed this value.
TestLoad: 

UseLaunchers: 
CurlOptions: 
# warning, if you add new options here that have to do with submit,
# you have to update cmCTestSubmitCommand.cxx

# For CTest submissions that timeout, these options
# specify behavior for retrying the submission
CTestSubmitRetryDelay: 5
CTestSubmitRetryCount: 3
