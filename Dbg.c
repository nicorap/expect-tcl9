/* Dbg.c - Tcl Debugger stubs for Tcl 9

The original Dbg.c (Don Libes, NIST, 3/23/93) used Tcl internal structs
(Interp *, CallFrame *, varFramePtr, numLevels) that are opaque in Tcl 9.
Rather than port the debugger (which is unmaintained and unused in modern
workflows), all functions are replaced with no-ops so the rest of Expect
compiles and runs correctly.

To re-enable debug support, a full rewrite against Tcl 9's public API
(e.g. Tcl_GetInterpPath, Tcl_NRAddCallback) would be needed.
*/

#include "tcl.h"
#include "tcldbg.h"

char *Dbg_VarName       = "dbg";
char *Dbg_DefaultCmdName = "debug";

void
Dbg_On(interp, immediate)
    Tcl_Interp *interp;
    int immediate;
{
    (void)interp; (void)immediate;
}

void
Dbg_Off(interp)
    Tcl_Interp *interp;
{
    (void)interp;
}

int
Dbg_Active(interp)
    Tcl_Interp *interp;
{
    (void)interp;
    return 0;
}

char **
Dbg_ArgcArgv(argc, argv, copy)
    int argc;
    char *argv[];
    int copy;
{
    (void)argc; (void)argv; (void)copy;
    return NULL;
}

Dbg_InterStruct
Dbg_Interactor(interp, func, data)
    Tcl_Interp *interp;
    Dbg_InterProc *func;
    ClientData data;
{
    Dbg_InterStruct s;
    (void)interp; (void)func; (void)data;
    s.func = NULL;
    s.data = NULL;
    return s;
}

Dbg_IgnoreFuncsProc *
Dbg_IgnoreFuncs(interp, proc)
    Tcl_Interp *interp;
    Dbg_IgnoreFuncsProc *proc;
{
    (void)interp; (void)proc;
    return NULL;
}

Dbg_OutputStruct
Dbg_Output(interp, func, data)
    Tcl_Interp *interp;
    Dbg_OutputProc *func;
    ClientData data;
{
    Dbg_OutputStruct s;
    (void)interp; (void)func; (void)data;
    s.func = NULL;
    s.data = NULL;
    return s;
}

void
Dbg_StdinMode(mode)
    int mode;
{
    (void)mode;
}

int
Tcldbg_Init(interp)
    Tcl_Interp *interp;
{
    (void)interp;
    return TCL_OK;
}
