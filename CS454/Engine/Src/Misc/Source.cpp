#include "WhereAmI.h"

void GetPath() {
    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return ;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    printf("*****************************************************************************\n");
    printf("The current working directory is %s \n", cCurrentPath);
    printf("*****************************************************************************\n");

    return ;
}