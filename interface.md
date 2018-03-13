# How to use kos

kos is a distributed operating system that runs on 1+ physical machines that are connected with a switch.

  *----switch-----*
  |       |       |
*----*  *----*  *----*
| M1 |  | M2 |  | M3 |
*----*  *----*  *----*
          |
       *-----*
       | TTY |
       *-----*

Steps for the user:

* Connect a TTY client (ex: PuTTY) to any machine's UART port. (See diagram above.)
* Send a ! character to start the shell.
* Start using the shell.

# What programs can run on kos?

Programs can use a subset of the ARMv6 instruction set.
In particular these categories of instructions are valid:

* Branch
* Comparison
* Arithmetic 
* Data movement
* SWI for system calls

Programs can read/write the full address space of 2^32 bytes.

# Architecture

## Distributed and virtualized RAM

When a program first starts, only the first 4KB of RAM is paged in.

When the program accesses non-paged memory and generates exception, the kernel will do one of the following:

* Virtualize: Page in memory from the same machine.
* Distribute: Allocate memory on a different machine, and perform the read/write over the network.
* Overflow: Tell the task that it is using too much memory.

## Distributed and virtualized processor

Programs can start another thread of execution by issuing an exec system call.
Exec starts another thread at the given instruction_pointer:

void exec(uint64_t instruction_pointer);

These are properties of the new thread:

* Register values start at reset.
* Register values are private to the thread.
* The memory space is shared with existing threads.

When the kernel receives this syscall, it does one of the following:

* Allocate (traditional way): Start another core on the same machine.
* Virtualize: Add thread state to an existing core's scheduler.
* Distribute: Start another core on a different machine.
