#include "app.h"

struct app_st app[1];

static void show_usage(void);
static int tree_main(int argc, char **argv);
static int visit_dir_path(const char *dir_path);
static int visit_dir(const char *path, const char *prefix, DIR *dir, int depth);

int main (int argc, char **argv)
{
    int ret = 0;
    int ch;

    app->argc = argc;
    app->argv = argv;
    app->opt_dir_only = 0;
    app->opt_verbose = 0;

    while ((ch = getopt(argc, argv, "dvh")) != -1) {
        switch (ch) {
            case 'd':
                app->opt_dir_only = 1;
                break;
            case 'v':
                app->opt_verbose++;
                break;
            case 'h':
                show_usage();
                ret = 0;
                goto end;
            default:
                show_usage();
                ret = 1;
                goto end;
        }
    }
    argc -= optind;
    argv += optind;

    ret = tree_main(argc, argv);
    if (ret != 0)
    {
        fprintf(stderr, s_ERR"tree_main() failed\n", __OUT__);
        goto end;
    }

end:
    return ret;
}

static void show_usage(void)
{
    printf("Usage: %s [options] directories...\n", app->argv[0]);
    printf("  -h This help.\n");
    printf("  -d Show directories only\n");
    printf("  -v Add a verbosity level\n");
}

static int tree_main(int argc, char **argv)
{
    int ret = 0;
    int err;
    int i;
    DIR *dir = NULL;

    if (argc > 0)
    {
        for (i=0; i<argc; i++)
        {
            ret = visit_dir_path(argv[i]);
            if (ret != 0)
            {
                fprintf(stderr, s_ERR"visit_dir_path() failed, i=%d\n",
                    __OUT__, i);
                goto end;
            }
        }
    }
    else
    {
        ret = visit_dir_path(".");
        if (ret != 0)
        {
            fprintf(stderr, s_ERR"visit_dir_path() failed\n",
                __OUT__);
            goto end;
        }
    }

       
end:
    return ret;
}

static int visit_dir_path(const char *dir_path)
{
    int ret = 0;
    elm_t *elm = NULL;

    elm = elm_new(NULL, dir_path);
    elm_show(elm);
    elm_free(elm);

    return ret;
}
