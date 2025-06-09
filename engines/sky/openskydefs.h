#ifndef OPENSKY_DEFS_H
#define OPENSKY_DEFS_H

// Distinguish between Windows and Linux, is it necessary?
#ifdef _WIN32
//#define OPENSKYPATH "\\opensky\\"
#elif _WIN64
//#define OPENSKYPATH "\\opensky\\"
#else
//#define OPENSKYPATH "/opensky/"
#endif

#define OPENSKYPATH "/opensky/"
#define OPENSKY_SPEECHPATH "speech/"
#define OPENSKY_TEXTFILE "texts.txt"

#endif
