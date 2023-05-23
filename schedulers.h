#define MIN_PRIORITY 1
#define MAX_PRIORITY 10


static struct node *RR;

// add a task to the list
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();


void addFCFS(char *name, int burst);
void scheduleFCFS();

// add a task to the list
void addRRP(char *name, int priority, int burst);

// invoke the scheduler
void scheduleRRP();
