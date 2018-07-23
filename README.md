# PLAYIMF
A very simple ID software IMF music file player for MS-DOS. This literally started out as a hello world program while trying to get the hang of OpenWatcom and its debugging facilities which then became a x86 assembly exercize.

PLAYIMF can play both Type 0 and Type 1 IMF files at any playback rate. The timing logic was based from Wolfenstein 3D's original source so playback should be 100%  accurate.

Please note that this player is to be run under MS-DOS with an OPL2 compatible sound card.

The entire player code is contained in a single assembler file which should make it very easy to integrate into your own projects with little to no modifications as long as your project targets to 16-bit DOS.

# Compiling
You will need OpenWatcom with 16-bit DOS targets (make sure wcc is not a copy of wcc386).

Run wmake to compile PLAYIMF.

Or...

Open the project file with the OpenWatcom IDE and compile with F4.

# Credits
* Programmed by Lameguy64 of Meido-Tek productions.
* Timer code based from RAD's sample player code.
* IMF timing logic based from Wolfenstein 3D's original source code.