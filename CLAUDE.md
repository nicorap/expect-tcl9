# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is **Expect 5.45.4**, a C extension for Tcl that enables programmed dialogue with interactive applications via pseudo-terminals (PTYs). This fork targets **Tcl 9 compatibility**. It builds as a TEA (Tcl Extension Architecture) compliant shared library and optionally as a standalone `expect` binary.

## Build Commands

```bash
# Configure (first time or after configure.in changes)
./configure

# Build
make

# Run all tests
make test

# Install
make install
```

### Running a Single Test File

```bash
# From the repo root, after building:
./expect tests/expect.test

# With options (verbose, specific test pattern):
./expect tests/expect.test -verbose bps -match "expect-1.*"

# Run all tests interactively:
./expect
# then: source tests/all.tcl
```

## Architecture

### Core Layer (C)

- **`exp_command.c`** — Implements all Tcl commands: `spawn`, `send`, `expect`, `interact`, `stty`, `log_file`, etc. This is the heart of the extension.
- **`exp_clib.c`** — C library API (`Exp_*` functions) for embedding Expect in C programs without Tcl.
- **`exp_inter.c`** — The `interact` command engine; handles human↔process dialogue with terminal passthrough.
- **`exp_pty.c` / `exp_tty.c`** — PTY allocation and TTY control. Platform-specific logic lives here (termios, SGTTYB, Unicos variants).
- **`exp_glob.c`** — Glob pattern matching used by `expect`.
- **`exp_regexp.c`** — Regexp matching layer.
- **`exp_event.c`** — Event loop integration; dispatches I/O events to Tcl's event system.
- **`exp_select.c` / `exp_poll.c` / `exp_noevent.c`** — Alternative I/O multiplexing backends (selected at compile time).
- **`exp_chan.c`** — Tcl channel driver for spawned processes; integrates PTY I/O with Tcl's channel abstraction.
- **`exp_log.c`** — Logging infrastructure (`log_file`, `log_user`).
- **`Dbg.c`** — Tcl debugger (the `Dbg_*` API).

### Tcl Integration Layer

- **`expTcl.c`** — Extension initialization (`Expect_Init`), registers all commands with the interpreter.
- **`expect_tcl.h` / `expTcl.h`** — Public headers for embedding.
- **`pkgIndex.tcl`** — Package index so `package require Expect` works.

### Standalone Binary

- **`exp_main_exp.c`** — `main()` for the `expect` executable; starts a Tcl interpreter, loads the extension, and runs user scripts.
- **`exp_main_sub.c`** — Shared startup logic for the binary.

### Tcl 9 Compatibility Work

Recent commits focus on Tcl 9 channel profiles (`-profile tcl8`) to handle binary/text encoding differences introduced in Tcl 9. Key files touched: `exp_chan.c`, `exp_command.c`, `exp_main_sub.c`. The `case` command is also aliased to `switch` (removed in Tcl 9).

## Test Infrastructure

Tests live in `tests/` and use the `tcltest` package. Each `.test` file covers one or a few commands. The runner is `tests/all.tcl`.

Test constraint flags useful for CI: `-constraints nonPortable` to include platform-specific tests.

## Key Development Notes

- **Tcl 9 target**: When modifying channel or I/O code, be aware of the `-profile tcl8` setting applied to stdin/stdout/stderr and spawned channels. This suppresses Tcl 9's strict encoding enforcement and preserves binary-transparent behavior.
- **PTY platform variance**: PTY allocation code has several `#ifdef` branches for different UNIX PTY APIs. Changes here need testing on multiple platforms.
- **Stubs**: The extension uses Tcl stubs (`USE_TCL_STUBS`). `Tcl_InitStubs` is called with the minimum required version; keep this in sync with actual API usage.
- **No Tk/expectk**: Tk support (`expectk`) was removed. Ignore any Tk-related dead code.
