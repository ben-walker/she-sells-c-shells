#include "processSupervisor.h"
#include "internal.h"
#include "external.h"

void child(pid_t pid, char **argv) {
    isInternal(argv[0]) ? runInternal(argv) : runExternal(argv);
}
