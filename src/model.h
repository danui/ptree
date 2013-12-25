#ifndef MODEL_H_header_file
#define MODEL_H_header_file

typedef struct elm_st elm_t;

struct elm_st
{
    char *name;

    char *path;

    /*
     * parent - Parent element.
     * children - List of children.
     * _children - Last element in list of children.
     * next - Next element.
     */
    elm_t *parent;
    elm_t *children;
    elm_t *_children;
    elm_t *next;
};

elm_t* elm_new(elm_t *parent, const char *name);
void elm_show(elm_t *e);
void elm_free(elm_t *e);

#endif
