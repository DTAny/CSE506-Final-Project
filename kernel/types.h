#include "param.h"

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

typedef uint64 pde_t;

typedef struct pinfo_t
{
    int n;
    int pids[NPROC];
    int t[NPROC];
    int tickets[NPROC];
    int ctime[NPROC];
#ifdef ULE
    int stime[NPROC];
    int rtime[NPROC];
    int nice[NPROC];
    int score[NPROC];
#endif
} pinfo_t;

typedef struct node
{
    struct proc *p;
    struct node *next;
} node;

typedef struct queue
{
    node *head;
    node *tail;
} queue;