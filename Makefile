MAKDIR = mk
MAK = $(wildcard $(MAKDIR)/*.mk)

all: $(BIN_IMAGE)

include $(MAK)

$(BIN_IMAGE): $(EXECUTABLE)
	@$(OBJCOPY) -O binary $^ $@
	@$(OBJCOPY) -O ihex $^ $(HEX_IMAGE)
	@$(OBJDUMP) -h -S -D $^ > $(LIST_FILE)
	@echo "   ALL   |  OBJCOPY   "$@	
	@echo "   ALL   |  OBJCOPY   "$(HEX_IMAGEX)	
	@echo "   ALL   |  OBJDUMP   "$(LIST_FILE)
	@$(SIZE) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS) $(HALOBJS) $(BSPOBJS) $(RTOSOBJS) $(DSPOBJS) $(FATOBJS) $(USBOBJS) $(UGFXOBJS)
	@echo "   ALL   |   LD    "$@	
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(LDFLAGS) -lc -lgcc -lm -o $@ $^

