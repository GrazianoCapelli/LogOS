##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Linux
ProjectName            :=LogOS
ConfigurationName      :=Linux
WorkspacePath          :=/home/Graziano/Dropbox/Projects/LogOS
ProjectPath            :=/home/Graziano/Dropbox/Projects/LogOS
IntermediateDirectory  :=./Linux
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Graziano Capelli
Date                   :=02/06/19
CodeLitePath           :=/home/Graziano/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="LogOS.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --libs)
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
CXXFLAGS :=  -O2 -Wall $(shell wx-config --cflags) $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/globals.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(ObjectSuffix) $(IntermediateDirectory)/Emoticons.cpp$(ObjectSuffix) $(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IntermediateDirectory)/DlgNuovoPaziente.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/FrmPaziente.cpp$(ObjectSuffix) $(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IntermediateDirectory)/FrmReport.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/FrmProiettore.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	cp -r ./doc/CartelleProgramma/* ./Linux/
	@echo Done

MakeIntermediateDirs:
	@test -d ./Linux || $(MakeDirCommand) ./Linux


$(IntermediateDirectory)/.d:
	@test -d ./Linux || $(MakeDirCommand) ./Linux

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/globals.cpp$(ObjectSuffix): globals.cpp $(IntermediateDirectory)/globals.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/globals.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/globals.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/globals.cpp$(DependSuffix): globals.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/globals.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/globals.cpp$(DependSuffix) -MM globals.cpp

$(IntermediateDirectory)/globals.cpp$(PreprocessSuffix): globals.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/globals.cpp$(PreprocessSuffix) globals.cpp

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix): wxcrafter_bitmaps.cpp $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/wxcrafter_bitmaps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix): wxcrafter_bitmaps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(DependSuffix) -MM wxcrafter_bitmaps.cpp

$(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix): wxcrafter_bitmaps.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter_bitmaps.cpp$(PreprocessSuffix) wxcrafter_bitmaps.cpp

$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(ObjectSuffix): DlgNuovoEsercizio.cpp $(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/DlgNuovoEsercizio.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(DependSuffix): DlgNuovoEsercizio.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(DependSuffix) -MM DlgNuovoEsercizio.cpp

$(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(PreprocessSuffix): DlgNuovoEsercizio.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DlgNuovoEsercizio.cpp$(PreprocessSuffix) DlgNuovoEsercizio.cpp

$(IntermediateDirectory)/Emoticons.cpp$(ObjectSuffix): Emoticons.cpp $(IntermediateDirectory)/Emoticons.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/Emoticons.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Emoticons.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Emoticons.cpp$(DependSuffix): Emoticons.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Emoticons.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Emoticons.cpp$(DependSuffix) -MM Emoticons.cpp

$(IntermediateDirectory)/Emoticons.cpp$(PreprocessSuffix): Emoticons.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Emoticons.cpp$(PreprocessSuffix) Emoticons.cpp

$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix): wxcrafter.cpp $(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/wxcrafter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix): wxcrafter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxcrafter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/wxcrafter.cpp$(DependSuffix) -MM wxcrafter.cpp

$(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix): wxcrafter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxcrafter.cpp$(PreprocessSuffix) wxcrafter.cpp

$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(ObjectSuffix): DlgNuovoPaziente.cpp $(IntermediateDirectory)/DlgNuovoPaziente.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/DlgNuovoPaziente.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(DependSuffix): DlgNuovoPaziente.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(DependSuffix) -MM DlgNuovoPaziente.cpp

$(IntermediateDirectory)/DlgNuovoPaziente.cpp$(PreprocessSuffix): DlgNuovoPaziente.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DlgNuovoPaziente.cpp$(PreprocessSuffix) DlgNuovoPaziente.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/FrmPaziente.cpp$(ObjectSuffix): FrmPaziente.cpp $(IntermediateDirectory)/FrmPaziente.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/FrmPaziente.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FrmPaziente.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FrmPaziente.cpp$(DependSuffix): FrmPaziente.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FrmPaziente.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FrmPaziente.cpp$(DependSuffix) -MM FrmPaziente.cpp

$(IntermediateDirectory)/FrmPaziente.cpp$(PreprocessSuffix): FrmPaziente.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FrmPaziente.cpp$(PreprocessSuffix) FrmPaziente.cpp

$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix): MainFrame.cpp $(IntermediateDirectory)/MainFrame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/MainFrame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix): MainFrame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MainFrame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/MainFrame.cpp$(DependSuffix) -MM MainFrame.cpp

$(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix): MainFrame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MainFrame.cpp$(PreprocessSuffix) MainFrame.cpp

$(IntermediateDirectory)/FrmReport.cpp$(ObjectSuffix): FrmReport.cpp $(IntermediateDirectory)/FrmReport.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/FrmReport.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FrmReport.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FrmReport.cpp$(DependSuffix): FrmReport.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FrmReport.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FrmReport.cpp$(DependSuffix) -MM FrmReport.cpp

$(IntermediateDirectory)/FrmReport.cpp$(PreprocessSuffix): FrmReport.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FrmReport.cpp$(PreprocessSuffix) FrmReport.cpp

$(IntermediateDirectory)/FrmProiettore.cpp$(ObjectSuffix): FrmProiettore.cpp $(IntermediateDirectory)/FrmProiettore.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/Graziano/Dropbox/Projects/LogOS/FrmProiettore.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FrmProiettore.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FrmProiettore.cpp$(DependSuffix): FrmProiettore.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FrmProiettore.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FrmProiettore.cpp$(DependSuffix) -MM FrmProiettore.cpp

$(IntermediateDirectory)/FrmProiettore.cpp$(PreprocessSuffix): FrmProiettore.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FrmProiettore.cpp$(PreprocessSuffix) FrmProiettore.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Linux/


