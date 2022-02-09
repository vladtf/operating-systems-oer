---
title: "OS: Compute"
revealOptions:
  background-color: 'aquamarine'
  transition: 'none'
  slideNumber: true
  autoAnimateDuration: 0.0
---

# DATA

1. What Is Data?
1. A Programmer's Perspective on Data
1. Stages of Data
1. Programming Language Perspective
1. Hardware Perspective
1. Operating System Perspective
---
## 1. What Is Data?
----
### What Is Data?

* Generally: factual information (such as measurements or statistics) used as a basis for reasoning, discussion, or calculation
* Computer science: information in digital form that can be transmitted or processed
----

### Data Examples

* Anatomy coursework - data regarding the human body
* Census - data regarding population
* Your Facebook profile - data regarding yourself
* Your browser history - data regarding preferences

----

### What Is Data? (Computer Science)

![Data1](media/data.svg)

----
### What Is Data? (Computer Science)

![Data2](media/data-mem.svg)

----

### What We Want

* Optimal performance
    * retrieve and store should be as fast as possible
* Optimal use of memory space
    * once data is not used, memory is freed immediately
    * minimize the time when memory is reserved but not used
    * data should occupy the minimal required space
* Security
    * data correctness
    * data isolation
---
## A Programmer's Perspective on Data
----
### A Programmer's Perspective on Data

* Data = variables
* Operations: declare/read/write
* Variables are stored in memory, so depending on the language, you can also:
    * allocate memory
    * deallocate memory
----
### Example

- `demo/variables/c_vars.c`

----
### Performance

* Depends on
    * the number of memory copies that are being made
        - `demo/performance/copy.c`
    * the degree of reuse of memory
        - `demo/performance/reuse.c`
    * the number of memory allocations/deallocations
        - `demo/performance/alloc.c`
        - `demo/performance/alloc.c`
    * [Quiz](quiz/alloc.md)
    * the cache friendliness of the program's behavior
    * the hardware specifics

----
### Space usage

* Depends on:
    * how we store data
        - use appropriate types for variables
            - `demo/space_usage/types.c`
        - `#pragma pack(1)`
            - `demo/space_usage/pragma.c`
        - union
            - demo/space_usage/union.c
    * how soon memory is freed

----
### Security

* Buffer overflow
    - `demo/security/bo.c`
* NUL-terminated strings
    - `demo/security/nts.c`
* Integer overflow
    - `demo/security/io.c

----
### Trade-offs

* Python - performance for security, ease of use
* D - can switch between both worlds

----
### Example

* Python
    - `demo/variables/d_vars.d`
* D
    - `demo/variables/python_vars.d`
* [Quiz](quiz/pl.md)
----
### Who manages memory?

* You (the programmer) - C/C++, D
* The programming language - Python, Java, D, Rust
* A library implementation - C/C++, D
* The operating system - eveyone
---
## Stages of Data
----
### Stages of data

![Data3](media/lvl-data.svg)

----
## Programming Language Perspective
----

## Programming Language Perspective

![PL](media/PL.svg)

----
### Hardware Perspective
----

## Hardware perspective

![HP](media/HP.svg)

----

## Hardware Perspective

![HP2](media/HP2.svg)

----

## How is it mapped?

![SOP](media/SOP.svg)

---
## Operating System Perspective
----
## Storage Units - v1

![STAGENGY](media/storing-agency.svg)

----
## Storage Units - v1

* Each user needs to manually verify that a storage box is free
* The user needs to know the exact id of the box
* Extra security measures need to be implemented so that a user
does not end up opening another users box
* We expect the users to govern the situation
* Users = programs, storage unit = memory
----
## Storing Units - v2

![STAGENGY2](media/unit-interface.svg)
----
# Storage Units - part 2

* An automated system handles the requests and assigns each user a userId and a virtual unitId
* The system assigns a physical box to each pair of (userId, unitId)
* Each user will start counting its units from 0 to N
* The user does not handle physical boxes
----
## Storing Memory

* How do computers use memory?
    - v1 or v2?
    - `demo/proc_storage/`
---

## Virtual Memory

----
## Virtual Memory

![VM1](media/VM-1.svg)
----

## Virtual Memory

* Programs work with virtual memory as if it was physical memory
* Each process can address the entire address space (potentially, more thant the size of RAM) => simplicity
* Each process is encapsulated (cannot have access to another process's memory) => security
* Penalties: extra hardware and software needed, extra work is done when accessing memory
----
## How Do We Store Data?

* When we rent a storage unit, its size is fixed
* Even if we store a coin, we still get a moderately large storage unit
* The same goes for memory
----
## Pages/Frames

![PG](media/pages.svg)
----
# Pages/Frames

* A page is a virtual memory unit
* A frames is a physical memory unit
* A page/frame size is typically 4 KB
* Virtual pages are mapped to physical frames
* The mapping is stored in a page table
* Each page has access rights
----
## An Example - How does it work?

```c
int* arr = malloc(2000 * sizeof(int));
arr[1500] = 7;
```
----
## An Example - How does it work?

![EX1](media/vm-example1.svg)
----
## What About Physical Memory?

* Should we also allocate physical memory upfront?
* What if the program does not end up using that memory?
* Maybe we should allocate only when a memory location is actually used
* We mark allocated pages that don't have a corresponding frame with (U)
----
## An Example - How does it work?

![EX2](media/vm-example2.svg)

----
# An Example - How does it work?

* The requested address is checked to see if it was allocated (virtually)
* If not => _segmentation faul_
* If yes, then we must retrieve it
* Wait, about about physical frames?

----
## What About Physical Memory? (part 2)


![EX3](media/vm-example3.svg)

----
## What About Physical Memory? (part 2)

* This strategy is called **demand paging**
* We only allocate physical frames once they are needed
* The pages that have been allocated, along with their mapping status, are stored in a ledger, called the page table
* `demo/alloc_physical/`
----
## An Example - How does it work?

![EX4](media/vm-example4.svg)

----
## An Example - How does it work?

* Subsequent accesses to virtual addresses that have been mapped to a physical frame simply check that the virtual address is valid
* No need to allocate any other physical frames

----
## An Example - How does it work?


![EX5](media/vm-example5.svg)

----
## Advantages

* Each process can have a different memory mapping
* Physical RAM can be mapped into multiple processes at once
    - shared memory
* Memory regions can have access permissions
    - read, write, execute
* [Quiz](quiz/vm-draw.md)
----
## Page faults

* Occur when a virtual address access cannot be performed
* Examples:
    - A valid virtual address is accessed, but no physical frame is allocated
    - An invalid virtual address is accessed
----
## Page fault handlers

* Page faults are handled by OS routines
* A hardware unit generates a page fault that is treated by the operating system
* Once a page fault is addressed, the instruction that caused it is re-executed (assuming the OS was able to treat the page fault)

---
## Virtual Memory Architecture
----
## Virtual Memory Architecture

![VM](media/VM.svg)

----

## CPU

* The CPU always works with virtual addresses
* When a load is made the MMU intercepts the address

----
## Memory Management Unit (MMU)

* The MMU is a hardware component that checks whether the virtual address is valid
* The MMU stores the mappings (page tables) between virtual and physical addresses
* The page table is typically stored in memory (RAM), however, for faster access, a cache is used: the translation lookaside buffer (TLB)
----
## Memory Management Unit (MMU)

* If the virtual address is present in the page tables, i.e we have a physical counterpart address for it, the MMU forwards the physical address to the memory subsystem
* If not, a page fault is triggered

----
## The Operating System

* The operating system intercepts the page fault and runs the page fault handler
* The page fault handler:
    - verifies the virtual address is valid, i.e. it was allocated; issues segfault if not
    - if the address is valid, verifies if there is an already allocated physical frame for the virtual page; allocates it if not
    - verifies if the access rights allow this access
    - updates the page table with the latest mappings
    - reruns the instruction that caused the page fault
----
## The Memory Subsystem

* The memory subsystem works only with physical addresses
* Therefore, the MMU will forward only physical addresses, after it resolves the virtual address mapping
* [Quiz](quiz/swap.md)
---
## Swapping
----
## Swapping

* What happens if a process requires more memory than the available physical RAM?
* Frames that haven't been used in a while are evicted on the disk
* Once those frames are required they are brought up in RAM
* However, a large penalty will be incurred
* Typically, systems will freeze once the swap is used
----
## Swapping

![SWAP](media/Swap.svg)

----
## Swapping

![SWAPARCH](media/Swap-arch.svg)

* [Quiz](quiz/swap.md)
---
## Case Study: Index Out Of Bounds
----

## What is the result of running the following code?

```c

void main()
{
   /* some code, may contain allocations */

   int* arr = malloc(2000*sizeof(int));
   arr[2005] = 10;
}
```

* [Quiz](quiz/index-out-of-bounds.md)

---
## OS Implementation Of Virtual Memory

----
## OS Data Structures

![OSVM](media/OSVM.svg)

* [Quiz](quiz/sdfsd)
----
## OS Interface To Virtual Memory

* `/proc/<PID>/mem` - access to virtual memory
    - `demo/proc_mem/`
* `/proc/<PID>/page_map` - access to page mappings
    - `demo/proc_pagemap/`
* `/dev/mem` - access to physical memory
    - `demo/proc_pagemap/`
---
## Final Quiz

* [Quiz](quiz/vm-final.md)

---
## The End
