#include "../Source/include/Common.h"
#include "../Source/include/CommandLineParser.h"
#include "stdio.h"

int main(int argc, char* argv[])
{
    PINPUT_CMD input = NULL;
    initilizeS("-");
    getAllInputCmdListS(argc, argv, input);
    printf("%s", input->cmd);
    deinitilizeS(input);
    return 0;
}

