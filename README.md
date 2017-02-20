# glVertexAttribDivisor Apple/AMD Driver Bug

Simple OpenGL demo to illustrate some broken functionality in my Mac driver; [glVertexAttribDivisor](<https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribDivisor.xhtml>) doesn't work as intended for divisors >1

Overview: Draws NUM_INSTANCES instanced quads with random screen position and colour
*Generates NUM_INSTANCES screen positions as instance data
*Generates NUM_INSTANCES/2 RGB colours as instance data, and uses glVertexAttribDivisor to specify that this attribute should advance every 2 instances

Observed result:
http://i.imgur.com/sVyfYcw.png

I've tested a few other configurations, and glVertexAttribDivisor just does not work on Mac for any divisor other than 0 (per-vertex) or 1 (per-instance).
