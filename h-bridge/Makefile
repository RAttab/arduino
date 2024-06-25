port := /dev/ttyACM0
fqbn := arduino:avr:mega
cli := arduino-cli

src := $(src) $(wildcard ./*.c)
src := $(src) $(wildcard ./*.h)
src := $(src) $(wildcard ./*.ino)

.PHONY: all
all: build

.PHONY: build
build: $(src)
	$(cli) compile --fqbn $(fqbn) --library ../utils .

.PHONY: upload
upload: build
	$(cli) upload --port $(port) --fqbn $(fqbn) .

.PHONY: tail
tail:
	cat $(port)
