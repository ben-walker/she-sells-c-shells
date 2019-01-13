#include "shell.h"
#include "shell_data_grabber.h"

const char *DEF_PROMPT = "$";
const char *SU_PROMPT = "#";

void boot() {
    User *shellUser = newUser();
    populate(shellUser);
    char *prompt = getPrompt(shellUser, DEF_PROMPT, SU_PROMPT);
}
