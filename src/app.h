#ifndef APP_H_header_file
#define APP_H_header_file

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

#include "model.h"

#define s_ERR "ERR(%s,%s,%d): "
#define s_CHK "CHK(%s,%s,%d): "
#define s_DEBUG "DEBUG(%s,%s,%d): "
#define __OUT__ __FILE__,__func__,__LINE__

struct app_st
{
    /**
     * argc - The original argc.
     * argv - The original argv.
     */
    int argc;
    char **argv;

    /**
     * opt_dir_only - Show directories only.
     * opt_verbose - Verbosity level.
     */
    int opt_dir_only;
    int opt_verbose;
};

extern struct app_st app[1];

#endif
