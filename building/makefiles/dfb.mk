DFB_OUTDIR= $(OUTDIR)/dfb
DFB_OUTDIR_DEBUG = $(DFB_OUTDIR)/debug
DFB_OUTDIR_RELEASE = $(DFB_OUTDIR)/release

DFB_SED_OUTPUT_DIR_DEBUG= $(subst /,\\/,$(DFB_OUTDIR_DEBUG))
DFB_SED_OUTPUT_DIR_RELEASE= $(subst /,\\/,$(DFB_OUTDIR_RELEASE))

# Get product version.
DFBVERSION=-$(shell $(EPROSIMADIR)/scripts/common_pack_functions.sh printVersionFromCPP $(BASEDIR)/include/cpp/DFB_version.h)

# Get cdr version.
CDRVERSION=-$(shell $(EPROSIMADIR)/scripts/common_pack_functions.sh printVersionFromCPP $(BASEDIR)/../CDR/include/cpp/cdr/Cdr_version.h)

DFB_TARGET_DEBUG_FILE= libdfbd$(DFBVERSION).so
DFB_TARGET_DEBUG_Z_FILE= libdfbzd$(DFBVERSION).a
DFB_TARGET_FILE= libdfb$(DFBVERSION).so
DFB_TARGET_Z_FILE= libdfbz$(DFBVERSION).a

DFB_TARGET_DEBUG_LINK= libdfbd.so
DFB_TARGET_DEBUG_Z_LINK= libdfbzd.a
DFB_TARGET_LINK= libdfb.so
DFB_TARGET_Z_LINK= libdfbz.a

DFB_TARGET_DEBUG= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_FILE)
DFB_TARGET_DEBUG_Z= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_Z_FILE)
DFB_TARGET= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_FILE)
DFB_TARGET_Z= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_Z_FILE)

DFB_CFLAGS += $(CFLAGS) -std=c++0x
DFB_CFLAGS_DEBUG += $(CFLAGS_DEBUG) -std=c++0x

DFB_LIBS_DEBUG= $(LIBS_DEBUG) -lcdrd
DFB_LIBS= $(LIBS) -lcdr

DFB_LIBS_DEBUG_DIR= -L$(BASEDIR)/lib/$(EPROSIMA_TARGET) -L$(BASEDIR)/../CDR/lib/$(EPROSIMA_TARGET)
DFB_LIBS_DIR= $(DFB_LIBS_DEBUG_DIR)

DFB_INCLUDE_DIRS= $(INCLUDE_DIRS) -I$(BASEDIR)/include -I$(BASEDIR)/include/cpp \
		  -I$(EPROSIMADIR)/code -I$(BASEDIR)/../CDR/include -I$(BASEDIR)/../CDR/include/cpp

DFB_SRC_CPPFILES= $(BASEDIR)/src/cpp/TypecodeAPI.cpp \
		  $(BASEDIR)/src/cpp/BytecodeAPI.cpp \
		  $(BASEDIR)/src/cpp/SerializerAPI.cpp \
  		  $(BASEDIR)/src/cpp/CommonData.cpp \
    	  $(BASEDIR)/src/cpp/exceptions/NotEnoughParamsException.cpp \
		  $(BASEDIR)/src/cpp/exceptions/WrongParamException.cpp \
		  $(BASEDIR)/src/cpp/exceptions/WrongTypeException.cpp

# Project sources are copied to the current directory
DFB_SRCS= $(DFB_SRC_CFILES) $(DFB_SRC_CPPFILES)

# Source directories
DFB_SOURCES_DIRS_AUX= $(foreach srcdir, $(dir $(DFB_SRCS)), $(srcdir))
DFB_SOURCES_DIRS= $(shell echo $(DFB_SOURCES_DIRS_AUX) | tr " " "\n" | sort | uniq | tr "\n" " ")

DFB_OBJS_DEBUG = $(foreach obj,$(notdir $(addsuffix .o, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_DEBUG)/$(obj))
DFB_DEPS_DEBUG = $(foreach dep,$(notdir $(addsuffix .d, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_DEBUG)/$(dep))
DFB_OBJS_RELEASE = $(foreach obj,$(notdir $(addsuffix .o, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_RELEASE)/$(obj))
DFB_DEPS_RELEASE = $(foreach dep,$(notdir $(addsuffix .d, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_RELEASE)/$(dep))

OBJS+= $(DFB_OBJS_DEBUG) $(DFB_OBJS_RELEASE)
DEPS+= $(DFB_DEPS_DEBUG) $(DFB_DEPS_RELEASE)

.PHONY: dfb checkDFBDirectories

dfb: checkDFBDirectories $(DFB_TARGET_DEBUG) $(DFB_TARGET_DEBUG_Z) $(DFB_TARGET) $(DFB_TARGET_Z) $(DFB_TARGET_EXE)

checkDFBDirectories:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(DFB_OUTDIR)
	@mkdir -p $(DFB_OUTDIR_DEBUG)
	@mkdir -p $(DFB_OUTDIR_RELEASE)
	@mkdir -p lib
	@mkdir -p lib/$(EPROSIMA_TARGET)
	@mkdir -p $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)

$(DFB_TARGET_DEBUG): $(DFB_OBJS_DEBUG)
	$(LN) $(LDFLAGS) -shared -o $(DFB_TARGET_DEBUG) $(DFB_LIBS_DIR) $(DFB_LIBS_DEBUG) $(DFB_OBJS_DEBUG)
	$(LNK) -s -f $(DFB_TARGET_DEBUG_FILE) $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_LINK)
	$(CP) $(DFB_TARGET_DEBUG) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)
	$(LNK) -s -f $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_FILE) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_LINK)

$(DFB_TARGET_DEBUG_Z): $(DFB_OBJS_DEBUG)
	$(AR) -cru $(DFB_TARGET_DEBUG_Z) $(DFB_OBJS_DEBUG)
	$(LNK) -s -f $(DFB_TARGET_DEBUG_Z_FILE) $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_Z_LINK)
	$(CP) $(DFB_TARGET_DEBUG_Z) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)
	$(LNK) -s -f $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_Z_FILE) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_DEBUG_Z_LINK)

$(DFB_TARGET): $(DFB_OBJS_RELEASE)
	$(LN) $(LDFLAGS) -shared -o $(DFB_TARGET) $(DFB_LIBS_DIR) $(DFB_LIBS) $(DFB_OBJS_RELEASE)
	$(LNK) -s -f $(DFB_TARGET_FILE) $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_LINK)
	$(CP) $(DFB_TARGET) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)
	$(LNK) -s -f $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_FILE) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_LINK)

$(DFB_TARGET_Z): $(DFB_OBJS_RELEASE)
	$(AR) -cru $(DFB_TARGET_Z) $(DFB_OBJS_RELEASE)
	$(LNK) -s -f $(DFB_TARGET_Z_FILE) $(BASEDIR)/lib/$(EPROSIMA_TARGET)/$(DFB_TARGET_Z_LINK)
	$(CP) $(DFB_TARGET_Z) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)
	$(LNK) -s -f $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_Z_FILE) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)/$(DFB_TARGET_Z_LINK)

vpath %.cpp $(DFB_SOURCES_DIRS)

$(DFB_OUTDIR_DEBUG)/%.o:%.cpp
	@echo Calculating dependencies \(DEBUG mode\) $<
	@$(CPP) $(DFB_CFLAGS_DEBUG) -MM $(DFB_INCLUDE_DIRS) $< | sed "s/^.*:/$(DFB_SED_OUTPUT_DIR_DEBUG)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(DEBUG mode\) $<  
	$(CPP) $(DFB_CFLAGS_DEBUG) $(DFB_INCLUDE_DIRS) $< -o $@

$(DFB_OUTDIR_RELEASE)/%.o:%.cpp
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CPP) $(DFB_CFLAGS) -MM $(DFB_INCLUDE_DIRS) $< | sed "s/^.*:/$(DFB_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	$(CPP) $(DFB_CFLAGS) $(DFB_INCLUDE_DIRS) $< -o $@

