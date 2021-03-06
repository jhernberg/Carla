#!/usr/bin/make -f
# Makefile for carla-backend #
# -------------------------- #
# Created by falkTX
#

CWD=..
include Makefile.mk

# ----------------------------------------------------------------------------------------------------------------------------

OBJS_standalone = \
	$(OBJDIR)/CarlaStandalone.cpp.o \
	$(OBJDIR)/CarlaStandaloneNSM.cpp.o

TARGETS = \
	$(BINDIR)/libcarla_standalone2$(LIB_EXT)

# ----------------------------------------------------------------------------------------------------------------------------

STANDALONE_LIBS  = $(MODULEDIR)/carla_engine.a
STANDALONE_LIBS += $(MODULEDIR)/carla_plugin.a
STANDALONE_LIBS += $(MODULEDIR)/jackbridge.a

STANDALONE_LIBS += $(MODULEDIR)/audio_decoder.a
STANDALONE_LIBS += $(MODULEDIR)/lilv.a
STANDALONE_LIBS += $(MODULEDIR)/native-plugins.all.a
STANDALONE_LIBS += $(MODULEDIR)/rtmempool.a
STANDALONE_LIBS += $(MODULEDIR)/sfzero.a
STANDALONE_LIBS += $(MODULEDIR)/water.a

ifeq ($(HAVE_DGL),true)
STANDALONE_LIBS += $(MODULEDIR)/dgl.a
endif

ifeq ($(HAVE_HYLIA),true)
STANDALONE_LIBS += $(MODULEDIR)/hylia.a
endif

STANDALONE_LIBS += $(MODULEDIR)/rtaudio.a
STANDALONE_LIBS += $(MODULEDIR)/rtmidi.a

# ----------------------------------------------------------------------------------------------------------------------------

STANDALONE_LINK_FLAGS  = $(JACKBRIDGE_LIBS)
STANDALONE_LINK_FLAGS += $(LILV_LIBS)
STANDALONE_LINK_FLAGS += $(NATIVE_PLUGINS_LIBS)
STANDALONE_LINK_FLAGS += $(RTMEMPOOL_LIBS)
STANDALONE_LINK_FLAGS += $(WATER_LIBS)

STANDALONE_LINK_FLAGS += $(RTAUDIO_LIBS)
STANDALONE_LINK_FLAGS += $(RTMIDI_LIBS)

STANDALONE_LINK_FLAGS += $(LIBLO_LIBS)
STANDALONE_LINK_FLAGS += $(MAGIC_LIBS)
STANDALONE_LINK_FLAGS += $(FLUIDSYNTH_LIBS)
STANDALONE_LINK_FLAGS += $(X11_LIBS)

# ----------------------------------------------------------------------------------------------------------------------------

all: $(TARGETS)
	$(MAKE) -C utils

# ----------------------------------------------------------------------------------------------------------------------------

clean:
	rm -f $(OBJS_standalone) $(TARGETS)
	$(MAKE) clean -C engine
	$(MAKE) clean -C plugin
	$(MAKE) clean -C utils

debug:
	$(MAKE) DEBUG=true

doxygen: CarlaBackend.doxygen
	doxygen $^

# ----------------------------------------------------------------------------------------------------------------------------

$(BINDIR)/libcarla_standalone2$(LIB_EXT): $(OBJS_standalone) $(STANDALONE_LIBS)
	-@mkdir -p $(BINDIR)
	@echo "Linking libcarla_standalone2$(LIB_EXT)"
	@$(CXX) $(OBJS_standalone) $(LIBS_START) $(STANDALONE_LIBS) $(LIBS_END) $(LINK_FLAGS) $(STANDALONE_LINK_FLAGS) $(SHARED) -o $@

# ----------------------------------------------------------------------------------------------------------------------------

ifeq ($(MACOS),true)
$(OBJDIR)/CarlaStandalone.cpp.o: CarlaStandalone.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling $<"
	@$(CXX) $< $(BUILD_CXX_FLAGS) -ObjC++ -c -o $@
endif

$(OBJDIR)/%.cpp.o: %.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling $<"
	@$(CXX) $< $(BUILD_CXX_FLAGS) -c -o $@

-include $(OBJS_standalone:%.o=%.d)

# ----------------------------------------------------------------------------------------------------------------------------
