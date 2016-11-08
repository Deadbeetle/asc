#include <core.h>

asc_instance ASC_Start(void) {
    asc_instance ret = { NULL, NULL, stdin, stdout, stderr };
    return ret;
}

void ASC_Create_Var(asc_instance asc, const char* name, const char* val) {
    variable* new = asc.vars;
    if (new) {
        while (new->next) {
            new = new->next;
        }
        {
            variable* tmp = (variable*)malloc(sizeof(variable));
            new->next = tmp;
            new = new->next;
        }
    } else {
        new = (variable*)malloc(sizeof(variable));
        new->next = NULL;
    }
    new->name = (char*)malloc(strlen(name) + 1);
    strcpy(new->name, name);
    switch (new->type = ASC_Typeof(val)) {
        case VInt:
            sscanf(val, "%i", &(new->val.i));
            break;
        case VDouble:
            sscanf(val, "%f", &(new->val.d));
            break;
        case VStr:
            new->val.s = (char*)malloc(strlen(val) + 1);
            strcpy(new->val.s, val);
            break;
        case VList:
            Create_List(new, val);
            break;
        default:
            new = NULL;
            ASC_Print_Error(UnknownType);
            break;
    }
    if (asc.vars) {
        variable* spot = asc.vars;
        while (spot->next)
            spot = spot->next;
        spot->next = new;
    } else {
        asc.vars = new;
    }
}

void ASC_Destroy_Var(asc_instance asc, const char* name) {
    variable* rem = asc.vars;
    if (rem) {
        while (rem->next && strcmp(rem->next->name, name))
            rem = rem->next;
        if (rem->next) {
            variable* tmp = rem->next;
            rem->next = tmp->next;
            free(tmp);
            return;
        }
    }
    ASC_Print_Error(VarNoExist);
}

FILE* ASC_Open_File(asc_instance asc, const char* arg) {
    char* filename;
    int len = 0;
    while (*arg && *arg++ != '"');
    while (*(arg + len) && (*(arg + len + 1) != '"' || *(arg + len) == '\\')) 
        len++;
    filename = (char*)malloc(len + 1);
    strncpy(filename, arg, len);
    FILE* f = fopen(filename, "r+");
    free(filename);
    return f;
}

void ASC_Close_File(asc_instance asc, variable* var) {
    if (var && var->type == VFile) {
        fclose(var->val.f);
    } else {
        ASC_Print_Error(asc, IncompatibleType);
    }
}

void ASC_Print_Error(asc_instance asc, Error e) {
    switch (e) {
        default:
            fprintf(asc.e_stream, "An unknown error occured.\n");
            break;
    }
}

