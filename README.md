# vint

- A auxiliary vector table interpreter for human readable format

At loading a new program process into the memory the loader goes to load the actual auxiliary vector table from the Operating System and to use/send this information to the new process application.

> Some applications that runs into arm machine that does hasn't an cpuid like instruction, uses some flags value from the auxiliary vector to identifier some hardwares capabilities, like the flag:

```c
#define AT_HWCAP  16    /* arch dependent hints at CPU capabilities */
```

## How to build

Just type:

```bash
make
```

## References

- Auxiliary vector table: <https://refspecs.linuxfoundation.org/LSB_1.3.0/IA64/spec/auxiliaryvector.html>

- Auxiliary flags identifier: <https://elixir.bootlin.com/linux/latest/source/include/uapi/linux/auxvec.h>
<https://elixir.bootlin.com/linux/latest/source/arch/nds32/include/uapi/asm/auxvec.h>
