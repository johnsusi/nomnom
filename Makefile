include build/make/defaults.mk

preset ?= release
out_dir := out
current_dir := $(dir $(mkfile_path))
build_dir := $(out_dir)/build/$(preset)
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
VCPKG_ROOT ?= $(current_dir)vcpkg
vcpkg_dir := $(abspath $(VCPKG_ROOT))

.PHONY: all configure build test package documentation clean ci


$(build_dir): $(vcpkg_dir)
> @VCPKG_ROOT=$(vcpkg_dir) cmake --preset=$(preset) .

configure: | $(build_dir)

build: configure
> @cmake --build $(build_dir)

clean:
> @rm -Rf $(out_dir)
