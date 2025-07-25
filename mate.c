#define MATE_IMPLEMENTATION
#include "mate.h"

i32 main(){

  CreateConfig((MateOptions){.buildDirectory = "./output"});

  
  StartBuild();
  {

    Executable exe = CreateExecutable((ExecutableOptions){
      .output = "test1",
      .optimization = FLAG_OPTIMIZATION_BASIC,
      .flags = "-I./lib"
    });
    
    AddFile(exe, "./lib/I_input.c");
    AddFile(exe, "./src/teste1.c");
    InstallExecutable(exe);
    

  }
  EndBuild();
}
