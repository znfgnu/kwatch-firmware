gdbserver:
	LD_LIBRARY_PATH=$(STLINK_GDBSRV_PATH)/native/linux_x64/ \
	$(STLINK_GDBSRV_PATH)/ST-LINK_gdbserver -p 61234 -l 1 -d -t -s -cp $(STCUBEPROGRAMMER_PATH) -m 0 -k

gdb:
	$(GDB) $(BUILD_DIR)/$(PROJECT_NAME).elf -ex "target remote localhost:61234" -ex "load"
