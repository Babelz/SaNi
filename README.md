# SaNi
User friendly 2D game engine.
Version 0.0.1

WARNING: will contain spelling errors.

# About
SaNi is written in C++ and is aimed to be a powerful cross-platform 2D game engine. At the current 
state it is not viable for game development. 

In the future the engine will have an editor which is used to create the games.

# Current Features

## Layered Structure

Follows the typical layered game engine architecture.

## Service Oriented Architecture

The engine follows main principles of service oriented architecture. 

## Platform Independence

SaNi has a layer that defines a common interface between platforms. This allows the engine
to be compiled into multiple platforms easily. Adding new platforms with this layer of
abstraction is also easy.

## File System

Defines an interface to read and write files on multiple platforms. Currently supports Win32, Unix and Android.

## Resource Management

WIP

## CVar System

Used to configure the engine at start and can be used to create game specific configurations. See wiki for more information.

## Math

Contains basic vector and matrix math.

## Graphics Wrapper

Defines a common interface between diffrent graphics APIs such as DirectX and OpenGL. At the moment, only OpenGL implementation exists and DirectX will be added in the future once the renderer has been implemented.

# Supported Platforms

Currently supported:
* Win32
* Android (partially)
* Unix systems (partially)
* Windows phone (partially)

The goal is to get Win32 and Android versions to work at the end of this year.

To be added:
* Windows phone
* Unix systems
* OSX
* iOS

We might add web, PS4 and XBOne support as well if we have enough time and moti. 

# Third Party

* libpng 1.6.18
* zlib 1.2.8
* glew 
* catch

# Copyright & License

Copyright 2015 Niko 'voidbab' Salmela & Jani 'siquel' Niemelä.

Licensed under MIT license.

The third party souce code might be licensed under different licenses. Look for thirdparty/licenses folder for these licenses.
