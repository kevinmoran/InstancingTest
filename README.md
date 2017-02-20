# glVertexAttribDivisor Apple/AMD Driver Bug

This is a simple OpenGL demo to illustrate some broken functionality in my Mac driver; [glVertexAttribDivisor](<https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribDivisor.xhtml>) doesn't work as intended for *x* number of divisors >1; instead of advancing an attribute every *x* instances, every instance just uses the first attribute value.

## Overview: Draws a number of instanced quads with random screen position and colour
* Generates NUM_INSTANCES screen positions as instance data
* Generates NUM_INSTANCES/2 RGB colours as instance data, and uses glVertexAttribDivisor to specify that this attribute should advance every 2 instances

## Observed result (There should be 8 different colours, with 2 quads using each colour):
![glVertexAttribDivisor Apple/AMD Driver Bug](http://i.imgur.com/sVyfYcw.png)

I've tested a few other configurations, and glVertexAttribDivisor just does not work on my Mac for any divisor other than 0 (per-vertex) or 1 (per-instance).

*Tested on AMD Radeon R9 M390*
