.PHONY: clean All

All:
	@echo "----------Building project:[ ControlBLockService - Debug ]----------"
	@$(MAKE) -f  "ControlBLockService.mk"
clean:
	@echo "----------Cleaning project:[ ControlBLockService - Debug ]----------"
	@$(MAKE) -f  "ControlBLockService.mk" clean
