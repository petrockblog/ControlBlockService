##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ControlBLockService
ConfigurationName      :=Debug
WorkspacePath          := "/Users/florian/github/ControlBLockService"
ProjectPath            := "/Users/florian/github/ControlBLockService"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Florian Müller
Date                   :=2014-11-22
CodeLitePath           :="/Users/florian/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++ 
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="ControlBLockService.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++ 
CC       := /usr/bin/gcc 
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as 


##
## User defined environment variables
##
CodeLiteDir:=/Users/florian/Desktop/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/ControlBlock.cpp$(ObjectSuffix) $(IntermediateDirectory)/PowerSwitch.cpp$(ObjectSuffix) $(IntermediateDirectory)/DigitalOut.cpp$(ObjectSuffix) $(IntermediateDirectory)/DigitalIn.cpp$(ObjectSuffix) $(IntermediateDirectory)/UInputGamepad.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/ControlBlock.cpp$(ObjectSuffix): ControlBlock.cpp $(IntermediateDirectory)/ControlBlock.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/ControlBlock.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ControlBlock.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ControlBlock.cpp$(DependSuffix): ControlBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ControlBlock.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ControlBlock.cpp$(DependSuffix) -MM "ControlBlock.cpp"

$(IntermediateDirectory)/ControlBlock.cpp$(PreprocessSuffix): ControlBlock.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ControlBlock.cpp$(PreprocessSuffix) "ControlBlock.cpp"

$(IntermediateDirectory)/PowerSwitch.cpp$(ObjectSuffix): PowerSwitch.cpp $(IntermediateDirectory)/PowerSwitch.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/PowerSwitch.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PowerSwitch.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PowerSwitch.cpp$(DependSuffix): PowerSwitch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PowerSwitch.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PowerSwitch.cpp$(DependSuffix) -MM "PowerSwitch.cpp"

$(IntermediateDirectory)/PowerSwitch.cpp$(PreprocessSuffix): PowerSwitch.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PowerSwitch.cpp$(PreprocessSuffix) "PowerSwitch.cpp"

$(IntermediateDirectory)/DigitalOut.cpp$(ObjectSuffix): DigitalOut.cpp $(IntermediateDirectory)/DigitalOut.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/DigitalOut.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DigitalOut.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DigitalOut.cpp$(DependSuffix): DigitalOut.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DigitalOut.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DigitalOut.cpp$(DependSuffix) -MM "DigitalOut.cpp"

$(IntermediateDirectory)/DigitalOut.cpp$(PreprocessSuffix): DigitalOut.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DigitalOut.cpp$(PreprocessSuffix) "DigitalOut.cpp"

$(IntermediateDirectory)/DigitalIn.cpp$(ObjectSuffix): DigitalIn.cpp $(IntermediateDirectory)/DigitalIn.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/DigitalIn.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DigitalIn.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DigitalIn.cpp$(DependSuffix): DigitalIn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DigitalIn.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DigitalIn.cpp$(DependSuffix) -MM "DigitalIn.cpp"

$(IntermediateDirectory)/DigitalIn.cpp$(PreprocessSuffix): DigitalIn.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DigitalIn.cpp$(PreprocessSuffix) "DigitalIn.cpp"

$(IntermediateDirectory)/UInputGamepad.cpp$(ObjectSuffix): UInputGamepad.cpp $(IntermediateDirectory)/UInputGamepad.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/florian/github/ControlBLockService/UInputGamepad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UInputGamepad.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UInputGamepad.cpp$(DependSuffix): UInputGamepad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UInputGamepad.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UInputGamepad.cpp$(DependSuffix) -MM "UInputGamepad.cpp"

$(IntermediateDirectory)/UInputGamepad.cpp$(PreprocessSuffix): UInputGamepad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UInputGamepad.cpp$(PreprocessSuffix) "UInputGamepad.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) ./Debug/*$(ObjectSuffix)
	$(RM) ./Debug/*$(DependSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/ControlBLockService"


