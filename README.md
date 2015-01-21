Yalla - Yet Another Lovely Lib for AVR
======================================

This projects goal is to provide a C++11 library for basic AVR programming. It's
aim is to provide all functionality needed to write programs in C++11 without
any dependency to avr-libc.

Quick start
===========

Requirements
------------

To build Yalla the following tools are needed:

* premake (>=4.4-beta5)
* avr-gcc
* avr-libc
* avr-binutils

Build
=====

* run premake4 gmake
	* Target device can be set with --mmcu=<device> (default is atmega8)
	* Clock frequency can be set with --fcpu=<frequency> (default is 8000000)
	* see premake4 --help for details

* cd build

* make <target>