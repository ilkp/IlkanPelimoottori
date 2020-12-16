# IlkanPelimoottori
Intructions for Windows 10, Visual studio 2019

Download and extract glm-0.9.9.8.zip from https://github.com/g-truc/glm/releases/tag/0.9.9.8

Download and extract SDL2-devel-2.0.12-VC.zip from https://www.libsdl.org/download-2.0.php

### core
Go to core project properties and select all configurations and all platforms

Set:

  Configuration Properties
  
    General > Output Directory > $(SolutionDir)bin\$(ProjectName)\$(Platform)\$(Configuration)\
    
            > Configurations type > Static library (.lib)
            
            > C++ Languare Standard > C++ 17
            
  C/C++
  
    General > Additional Include Directories > write your glm folder (e.g. C:\SDK\glm)
    
---
  
Go to SDL2_renderer project properties and select all configurations and all platforms

Set:

  Configuration Properties
  
    General > Output Directory > $(SolutionDir)bin\$(ProjectName)\$(Platform)\$(Configuration)\
    
            > Configurations type > Static library (.lib)
            
            > C++ Languare Standard > C++ 17
            
  C/C++
  
    General > Additional Include Directories > write your SDL 2.0 include folder (e.g. C:\SDK\SDL\SDL2-2.0.12\include\)
    
                                             > write your glm folder (e.g. C:\SDK\glm)
                                             
                                             > $(SolutionDir)src\core\
                                             
  Librarian
  
    General > Additional Dependencies > SDL2.lib
  
                                      > SDL2main.lib
                                                
            > Additional Library Directories > Set platform to Win32 and find your SDL library directory (e.g. C:\SDK\SDL\SDL2-2.0.12\lib\x86\)
                      
                                             > Set platfor to x64 and find your SDL Library directory (e,g, C:\SDK\SDL\SDL2-2.0.12\lib\x64\)
                                             
---

Go to test_game project properties and select all configurations and all platforms

Set:

  Configuration Properties
  
    General > Output Directory > $(SolutionDir)bin\$(ProjectName)\$(Platform)\$(Configuration)\
    
            > Configurations type > Application (.exe)
            
            > C++ Languare Standard > C++ 17
            
  C/C++
  
    General > Additional Include Directories > write your SDL 2.0 include folder (e.g. C:\SDK\SDL\SDL2-2.0.12\include\)
    
                                             > write your glm folder (e.g. C:\SDK\glm)
                                             
                                             > $(SolutionDir)src\core\
                                             
                                             > $(SolutionDir)src\SDL2_renderer\
                                             
  Linker
  
    General > Additional Library Dependencies > $(Solutiondir)bin\core\$(Platform)\$(Configuration)\
  
                                              > $(Solutiondir)bin\SDL2_renderer\$(Platform)\$(Configuration)\
                                                
    Input > Additional Dependencies > core.lib
                      
                                    > SDL2_renderer.lib
                                    
  Build Events
    Post-Build Event > Command Lines > write following:

if $(Platform) == x86 (
    echo "Copying SDL2.dll for x86"
    copy "C:\SDK\SDL\SDL2-2.0.12\lib\x86\SDL2.dll" "$(TargetDir)\SDL2.dl"
)
if $(Platform) == x64 (
    echo "Copying SDL2.dll for x64
    copy "C:\SDK\SDL\SDL2-2.0.12\lib\x64\SDL2.dll" "$(TargetDir)\SDL2.dl"
)
