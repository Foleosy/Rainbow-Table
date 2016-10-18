# RainbowTable

## Description
>#### Rainbow Table which reads in a sample of generated digests, and compares against pseudo-randomly generated rainbow tables to find the word which hashes to that particular digest. Done as part of a school assignment, and future refinements will be made in due time.

### Development Environment Requirements
===
- Recommended C++ 11 for compatibility in code, although deprecated functions have been used for now
- Developed in Visual Studio, Windows 8.1

### Dependencies 
===
- SHA1 library

### Running
===
- Generate the digests via Generate.cpp
- Build the rainbow tables via Build.cpp
- Run Find.cpp
