#include "../Source/include/Common.h"
#include "../Source/include/CommandLineParser.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
    PINPUT_CMD input = NULL;
    initilize(NULL,"-");
    getAllInputCmdList(argc, argv, input);
    printf("%s", input->cmd);
    deinitilize(input);
    return 0;
}

