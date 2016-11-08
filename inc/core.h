#ifndef ASC_CORE_H
#define ASC_CORE_H

#include <stdio.h>

typedef struct _var variable;

typedef enum {VDouble, VInt, VStr, VList, VFile, VUnknown} Type;

typedef enum {UnknownType, VarNoExist} Error;

typedef union {
    double     d;
    int        i;
    char*      s;
    variable*  v;
    FILE*      f;
} value;

struct _var {
    value     val;
    char*     name;
    variable* next;
    Type      type;
}

struct _func {
    char*     text;
    variable* inputs;
} func;

typedef struct _asci {
    variable* vars;
    func*     funcs;
    FILE*     i_stream;
    FILE*     e_stream;
    FILE*     o_stream;
} asc_instance;

asc_instance ASC_Start       (void);
void         ASC_Create_Var  (asc_instance, const char*, const char*);
void         ASC_Destroy_Var (asc_instance, const char*);
Type         ASC_Typeof      (const char*);

#endif
