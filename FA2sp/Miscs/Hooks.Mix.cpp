#include <Helpers/Macro.h>

DEFINE_HOOK(527F95, MixFile_PostOpen_CheckTD, 7)
{
	return 0x527FBB;
}

DEFINE_HOOK(5281EE, MixFile_PostOpen_CheckRAUnencrypted, 5)
{
	return 0x52823E;
}

DEFINE_HOOK(5280FC, MixFile_PostOpen_CheckRAEncrypted, 7)
{
	return 0x528124;
}

