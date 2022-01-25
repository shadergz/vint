/*
 *  Source code written by Gabriel Correia
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

#include "fpu_uapi_auxvec.h"
#include "uapi_auxvec.h"
#include "power_pc_auxvec.h"

const char process_info_dir[] = "/proc/";
const char aux_fileentry[] = "auxv";

typedef struct {
    long int a_type;
    union {
        long int a_val;
        void *a_ptr;
        void (*a_fcn) (void);
    } a_un;
} auxv_t;

int main (void)
{
    int fd = -1;
    char aux_fn[0x2d];
    auxv_t abuffer;

    /*  Using the self pseudo-dir (It's the same if I has used the PID info value to access the 
     *  actual process pseudo-dir informaton) 
    */
    snprintf (aux_fn, 0x2d, "%s/self/%s", process_info_dir, aux_fileentry);

    assert ((fd = open (aux_fn, O_RDONLY)) != -1);

    while (read (fd, &abuffer, sizeof (auxv_t))) {
        switch (abuffer.a_type) {
            case AT_NULL:
                puts ("End of auxiliary vector table");
                break;
            case AT_IGNORE:
                puts ("Ignore vector flag");
                break;
            case AT_EXECFD:
                printf ("Program file descriptor: %d\n", (int)abuffer.a_un.a_val);
                break;
            case AT_PHDR:
                printf ("Program headers for program: 0x%p\n", abuffer.a_un.a_ptr);
                break;
            case AT_PHENT:
                printf ("Size of program header entry: 0x%lx\n", abuffer.a_un.a_val);
                break;
            case AT_PHNUM:
                printf ("Number of program headers: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_PAGESZ:
                printf ("System page size: 0x%lx\n", abuffer.a_un.a_val);
                break;
            case AT_BASE:
                printf ("Interpreter base address: 0x%p\n", abuffer.a_un.a_ptr);
                break;
            case AT_FLAGS:
                printf ("Flags: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_ENTRY:
                printf ("Program entry point: 0x%p\n", abuffer.a_un.a_ptr);
                break;
            case AT_NOTELF:
                printf ("The program is: %s", abuffer.a_un.a_val ? "Not ELF" : "ELF");
                break;
            case AT_UID:
                printf ("Real process ID: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_EUID:
                printf ("Effective UID: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_GID:
                printf ("Real GID: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_EGID:
                printf ("Effective GID: %ld\n", abuffer.a_un.a_val);
                break;
            case AT_CLKTCK:
                printf ("Frequently of times: %fF\n", (float)abuffer.a_un.a_val);
                break;
            case AT_PLATFORM:
                printf ("Plataform string id: %s\n", (char*)abuffer.a_un.a_ptr);
                break;
            case AT_HWCAP:
                printf ("Machine dependent hints about processor capabilities value: 0x%lx\n", abuffer.a_un.a_val);
                break;
            case AT_FPUCW:
                printf ("FPU informations:\n\t0x%ld\n\t%p\n\t0x%p\n", abuffer.a_un.a_val, abuffer.a_un.a_ptr, abuffer.a_un.a_fcn);
                break;
            case AT_DCACHEBSIZE:
                printf ("Data cache block size: 0x%lu", abuffer.a_un.a_val);
                break;
            case AT_ICACHEBSIZE:
                printf ("Instruction cache block size: 0x%lu", abuffer.a_un.a_val);
                break;
            case AT_UCACHEBSIZE:
                printf ("Unified cache block size: 0x%lu", abuffer.a_un.a_val);
                break;
            default:
                break;
                //puts ("Undefined flag");
        }
    }

    close (fd);
}

