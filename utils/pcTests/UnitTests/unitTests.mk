DFB_OUTDIR= $(OUTDIR)/unitTests
DFB_OUTDIR_DEBUG = $(DFB_OUTDIR)/debug
DFB_OUTDIR_RELEASE = $(DFB_OUTDIR)/release

DFB_SED_OUTPUT_DIR_DEBUG= $(subst /,\\/,$(DFB_OUTDIR_DEBUG))
DFB_SED_OUTPUT_DIR_RELEASE= $(subst /,\\/,$(DFB_OUTDIR_RELEASE))

DFB_TARGET_DEBUG= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/libdfbd.so
DFB_TARGET_DEBUG_Z= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/libdfbzd.a
DFB_TARGET= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/libdfb.so
DFB_TARGET_Z= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/libdfbz.a
DFB_TARGET_EXE= $(BASEDIR)/lib/$(EPROSIMA_TARGET)/unitTests.sh

DFB_CFLAGS += $(CFLAGS) -std=c++11
DFB_CFLAGS_DEBUG += $(CFLAGS_DEBUG) -std=c++11

DFB_LIBS_DEBUG= $(LIBS_DEBUG) -lcdrd
DFB_LIBS= $(LIBS) -lcdr

DFB_LIBS_DEBUG_DIR= -L$(BASEDIR)/lib/$(EPROSIMA_TARGET)
DFB_LIBS_DIR= $(DFB_LIBS_DEBUG_DIR)

DFB_INCLUDE_DIRS= $(INCLUDE_DIRS) -I$(BASEDIR)/include -I$(BASEDIR)/include/cpp \
		  -I$(EPROSIMADIR)/code

DFB_SRC_CPPFILES= $(BASEDIR)/src/cpp/TypecodeAPI.cpp \
		  $(BASEDIR)/src/cpp/BytecodeAPI.cpp \
		  $(BASEDIR)/src/cpp/SerializerAPI.cpp \
  		  $(BASEDIR)/src/cpp/CommonData.cpp \
    		  $(BASEDIR)/src/cpp/exceptions/NotEnoughParamsException.cpp \
		  $(BASEDIR)/src/cpp/exceptions/WrongParamException.cpp \
		  $(BASEDIR)/src/cpp/exceptions/WrongTypeException.cpp \
		  $(BASEDIR)/utils/pcTests/UnitTests/Main.cpp

# Project sources are copied to the current directory
DFB_SRCS= $(DFB_SRC_CFILES) $(DFB_SRC_CPPFILES)

# Source directories
DFB_SOURCES_DIRS_AUX= $(foreach srcdir, $(dir $(DFB_SRCS)), $(srcdir))
DFB_SOURCES_DIRS= $(shell echo $(DFB_SOURCES_DIRS_AUX) | tr " " "\n" | sort | uniq | tr "\n" " ")

DFB_OBJS_DEBUG = $(foreach obj,$(notdir $(addsuffix .o, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_DEBUG)/$(obj))
DFB_DEPS_DEBUG = $(foreach dep,$(notdir $(addsuffix .d, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_DEBUG)/$(dep))
DFB_OBJS_RELEASE = $(foreach obj,$(notdir $(addsuffix .o, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_RELEASE)/$(obj))
DFB_DEPS_RELEASE = $(foreach dep,$(notdir $(addsuffix .d, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_RELEASE)/$(dep))
DFB_EXE_RELEASE = $(foreach obj,$(notdir $(addsuffix .o, $(basename $(DFB_SRCS)))), $(DFB_OUTDIR_RELEASE)/$(obj))

OBJS+= $(DFB_OBJS_DEBUG) $(DFB_OBJS_RELEASE)
DEPS+= $(DFB_DEPS_DEBUG) $(DFB_DEPS_RELEASE)

.PHONY: utests checkDFBDirectories

utests: checkDFBDirectories $(DFB_TARGET_EXE)

checkDFBDirectories:
	@mkdir -p $(OUTDIR)
	@mkdir -p $(DFB_OUTDIR)
	@mkdir -p $(DFB_OUTDIR_DEBUG)
	@mkdir -p $(DFB_OUTDIR_RELEASE)
	@mkdir -p lib
	@mkdir -p lib/$(EPROSIMA_TARGET)
	@mkdir -p $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)

$(DFB_TARGET_EXE): $(DFB_EXE_RELEASE)
	$(LN) $(LDFLAGS) -o $(DFB_TARGET_EXE) $(DFB_LIBS_DIR) $(DFB_LIBS) $(DFB_EXE_RELEASE)
	$(CP) $(DFB_TARGET_EXE) $(EPROSIMA_LIBRARY_PATH)/proyectos/$(EPROSIMA_TARGET)

vpath %.cpp $(DFB_SOURCES_DIRS)

$(DFB_OUTDIR_RELEASE)/%.o:%.cpp
	@echo Calculating dependencies \(RELEASE mode\) $<
	@$(CPP) $(DFB_CFLAGS) -MM $(DFB_INCLUDE_DIRS) $< | sed "s/^.*:/$(DFB_SED_OUTPUT_DIR_RELEASE)\/&/g" > $(@:%.o=%.d)
	@echo Compiling \(RELEASE mode\) $<
	$(CPP) $(DFB_CFLAGS) $(DFB_INCLUDE_DIRS) $< -o $@

