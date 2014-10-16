Teleop2015
==========

Teleop program for the Archmere Academy's FIRST FTC team for the 2014-2015 season (Cascade Effect).
This code is designed to control a robot via two remote controllers over a wifi network using a samantha module. This code was developed for a robot with a holonomic drive and certain other components onboard, and portability to other robots may be limited.

To Do:
==========

So far (as of Oct. 16), we are focusing on updating the code for our current robot. This means:
* Ensuring that the new motor encoders work with the PID control/are compatible in general. We may have to write new PID code.
* Updating for better coding techniques. This includes include guards, pragma guards/pragma once's, removal of dead code, optimizations, etc.
*  Documentation. Goal: try for a comment on each function, describing what it does, what its parameters are for, and what it returns. The general idea is that anyone can join this project, and understand (pretty well) what everything does. This also means no using `void foo(int bar)` or other generic names for functions.
*  Releases. Github has this feature, and we should use it to mark working builds. When making releases, upload compiled code (if safe) and attach it.
