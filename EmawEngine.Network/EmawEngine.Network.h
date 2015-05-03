// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the EMAWENGINENETWORK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// EMAWENGINENETWORK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef EMAWENGINENETWORK_EXPORTS
#define EMAWENGINENETWORK_API __declspec(dllexport)
#else
#define EMAWENGINENETWORK_API __declspec(dllimport)
#endif

// This class is exported from the EmawEngine.Network.dll
class EMAWENGINENETWORK_API CEmawEngineNetwork {
public:
	CEmawEngineNetwork(void);
	// TODO: add your methods here.
};

extern EMAWENGINENETWORK_API int nEmawEngineNetwork;

EMAWENGINENETWORK_API int fnEmawEngineNetwork(void);
