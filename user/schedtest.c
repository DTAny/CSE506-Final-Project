#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_CHILDREN 32
#define MAX_PARENT_YEILD 10

int create_child(int tickets)
{
    int pid = fork();
    if (pid == 0)
    {
#ifndef FCFS
        chtickets(getpid(), tickets);
        while (1)
            ;
#endif
#ifdef FCFS
        long i = 999999999;
        while (i--)
            ;
        exit(0);
#endif
    }
    return pid;
}

int index(int x, int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
        {
            return i;
        }
    }
    return -1;
}

int wait_children_ready(int n_children, int *pids, int *tickets)
{
    int i, j, done, pindex;
    pinfo_t info;

    for (i = 0; i < MAX_PARENT_YEILD; i++)
    {
        sleep(1);
        done = 1;

        pinfo(&info);

        for (j = 0; j < n_children; j++)
        {
            pindex = index(pids[j], info.pids, info.n);
            if (pindex == -1 || info.tickets[pindex] != tickets[j])
            {
                done = 0;
                break;
            }
        }
        if (done)
        {
            return 0;
        }
    }
    return -1;
}

void print_result(pinfo_t *before, pinfo_t *after, int n_children, int *c_pids, int *c_tickets)
{
    int i, pindex;

    printf("PID\tTickets\tTicks\tCTime\n");

    for (i = 0; i < n_children; i++)
    {
        pindex = index(c_pids[i], before->pids, before->n);
        printf("%d\t%d\t%d\t%d\n", c_pids[i], c_tickets[i], after->t[pindex] - before->t[pindex], after->ctime[pindex]);
    }
}

int main(int argc, char *argv[])
{
    int pid = getpid();
    int sleep_time = atoi(argv[1]);
    int p_tickets = atoi(argv[2]);
    int n_children = argc - 3;

    int c_pids[MAX_CHILDREN];
    int c_tickets[MAX_CHILDREN];

    pinfo_t before, after;

    chtickets(pid, p_tickets);
    for (int i = 0; i < n_children; i++)
    {
        int tickets = atoi(argv[3 + i]);
        c_pids[i] = create_child(tickets);
        c_tickets[i] = tickets;
    }

    if (wait_children_ready(n_children, c_pids, c_tickets) != 0)
    {
        printf("schedtest: children not ready\n");
        exit(1);
    }

    chtestflag(1);
    pinfo(&before);
    sleep(sleep_time);
    pinfo(&after);
    chtestflag(0);

    for (int i = 0; i < n_children; i++)
    {
        kill(c_pids[i]);
    }

    for (int i = 0; i < n_children; i++)
    {
        wait(0);
    }

    printf("\nSummary: \n\n");
    print_result(&before, &after, n_children, c_pids, c_tickets);
    exit(0);
}