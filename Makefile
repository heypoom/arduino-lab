build:
	pio run

run:
	pio run -t upload

clean:
	pio run -t clean

verbose-build:
	pio run -v

verbose-upload:
	pio run -v -t upload

upload-and-monitor:
	pio run -t upload -t monitor

upload-programmer:
	pio run -t program

monitor:
	pio device monitor

test:
	pio test

remote:
	pio remote run -t upload

debug:
	pio debug

update-libs:
	pio lib update

rebuild:
	pio init --ide clion

rebuild-vscode-intellisense:
	pio init --ide vscode
