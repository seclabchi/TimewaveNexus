.PHONY: clean All

All:
	@echo "----------Building project:[ AudioEngine - Debug ]----------"
	@cd "AudioEngine" && $(MAKE) -f  "AudioEngine.mk"
clean:
	@echo "----------Cleaning project:[ AudioEngine - Debug ]----------"
	@cd "AudioEngine" && $(MAKE) -f  "AudioEngine.mk" clean
