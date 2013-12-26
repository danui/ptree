default: build

build:
	scons

check: build

clean:
	scons -c
	find . -name "*~" -exec rm -vf \{\} \;
	find . -name "*.o" -exec rm -vf \{\} \;
	rm -vrf out
