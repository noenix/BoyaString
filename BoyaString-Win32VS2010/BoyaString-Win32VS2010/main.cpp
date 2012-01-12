#include "Bootstrap.h"

#ifdef __cplusplus
extern "C" {
#endif

int 
main(int argc, char *argv[])
{
	Bootstrap bootstrap;
	bootstrap.go();
	return 0;
}

#ifdef __cplusplus
};
#endif
