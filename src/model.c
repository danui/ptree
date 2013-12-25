#include "app.h"

static void show_prefix(elm_t *e);
static char* get_path(elm_t *e);
static int should_reject_elm(elm_t *e);

elm_t* elm_new(elm_t *parent, const char *name)
{
    elm_t *e = NULL;

    e = (elm_t*)malloc(sizeof(elm_t));
    if (e == NULL)
    {
        fprintf(stderr, s_ERR"malloc() failed\n", __OUT__);
        goto end;
    }

    e->name = strdup(name);
    if (e->name == NULL)
    {
        fprintf(stderr, s_ERR"strdup() failed\n", __OUT__);
        goto end;
    }
    e->path = NULL;
    e->parent = parent;
    e->children = NULL;
    e->_children = NULL;
    e->next = NULL;

end:
    return e;
}

void elm_show(elm_t *e)
{
    DIR *dir = NULL;
    struct dirent *entry = NULL;
    elm_t *child = NULL;

    /* Show self */
    show_prefix(e);
    printf("%s\n", e->name);

    /* Show children, if any */
    dir = opendir(get_path(e));
    if (dir)
    {
        while (NULL != (entry = readdir(dir)))
        {
            child = elm_new(e, entry->d_name);

            if (should_reject_elm(child))
            {
                elm_free(child);
                continue;
            }

            if (e->children == NULL)
            {
                e->children = child;
                e->_children = child;
            }
            else
            {
                e->_children->next = child;
                e->_children = child;
            }
        }
        closedir(dir);
    }
    /* Show and Free children */
    while (e->children)
    {
        elm_show(e->children);
        child = e->children;
        e->children = e->children->next;
        elm_free(child);
    }
}

void elm_free(elm_t *e)
{
    free(e->name);
    if (e->path != NULL && e->path != e->name)
    {
        free(e->path);
    }
    free(e);
}

static void show_prefix(elm_t *e)
{
    elm_t *ancestor = NULL;

    if (e->parent == NULL)
    {
        return;
    }
    ancestor = e->parent;
    while (ancestor->parent)
    {
        ancestor = ancestor->parent;
    }
    while (ancestor != e)
    {
        if (ancestor->children == ancestor->_children)
        {
            if (ancestor->children == e)
            {
                printf("`-- ");
            }
            else
            {
                printf("    ");
            }
        }
        else
        {
            if (ancestor->children == e)
            {
                printf("|-- ");
            }
            else
            {
                printf("|   ");
            }
        }
        ancestor = ancestor->children;
    }

    return;
}

static char* get_path(elm_t *e)
{
    size_t len;
    char *parent_path = NULL;

    /* First check if get_path() was ever called on e.  If so, then
     * e->path would have been set, reuse that. */
    if (e->path)
    {
        return e->path;
    }

    /* If there is a parent, get the parent's path and make e->path,
     * otherwise (no parent), the path is the same as e->name. */
    if (e->parent)
    {
        parent_path = get_path(e->parent);
        len = strlen(parent_path) 
            + 1 // '/'
            + strlen(e->name)
            + 1 // '\0'
            ;
        e->path = (char*)malloc(len);
        sprintf(e->path, "%s/%s", parent_path, e->name);
    }
    else
    {
        e->path = e->name;
    }
    return e->path;
}

static int should_reject_elm(elm_t *e)
{
    if (0 == strcmp(".", e->name)) return 1;
    if (0 == strcmp("..", e->name)) return 1;
    if (e->name[0] == '.') return 1;
    if (app->opt_dir_only)
    {
        DIR *dir = opendir(get_path(e));
        if (dir)
        {
            closedir(dir);
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
