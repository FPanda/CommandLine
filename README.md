##### CommandLine
##1. Introduction  
  Most of us know the module named optParser in Python. It allows users to define the way to parse the command line input by themselves. But it seems complex to do such a thing in C/C++ since no 3rd part or stl lib supported. CommandLine Parser is aimed  to solve this problem in C/C++. Developers just need to config the way to parse command line by xml file.  
  
  With the command line parser, it allows developers to focus on the features they should develop.
  
##2. Features  
  This command line parser now supplies two kinds of modes for developers to match different situations during their developing.  
  #1. Simple mode  
     Simple mode allows developers not to concerntrate on the command line parse and simply use this parser. Developers doesn't need to write their xml and just use the getAllInputCmdListS to get all the commands user input. It's easy learning, simple codes, but upgrade the development efficency.
  #2. Automatic mode  
     Automatic mode use the full features of command line parser. Developers just define their own command xml like /Source/test.xml and regist the handle function during the program initilization. All the job will be done by command line parser.  
  
##3. Consists of CommandLineParser  
  For detail information, please check the DictionaryDesciprtion.txt  
  

