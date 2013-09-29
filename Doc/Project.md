What's this Playground project?
===============================

Introduction
------------

By comparing various platforms and solutions, the following points come to mind :

- How much does it cost ? License model ?
- What is the technology behind it ?
- How much control do we have over it ?
- On how many platform does it work ?
- Can it do easily our specific task ?

Etc...

We decided that we could write a small core at first and get some functions easily
that the other solutions do not provide (ie basic flash player, rendering optimized for 2D, etc...)


Concept
-------

- Multiplatform, 2D only support, scriptable, customizable game engine.
- Support for debugging at low level (resource and memory leak detection made easy).
- Provide from start feature like primitive flash player.
- Can implement game logic in LUA but also in C++ and create custom task. 

The goal is to use LUA as much as possible for game level logic, C++ for game specific parts/systems.

History
-------

The project was started for 3 months with 3 people and we ended up having a robust base :

- Rendering system with batching was in place.
- Task system was in place
- Logging, memory leak tracking was in place with appropriate tools.
- Basic flash player to help with animation was in place.

After that, game development grew and we mostly spent time to add new features, new tasks to the system,
fix bugs, improve multiplatform support, tool extension, etc...

How to run
----------

See How_to_run.md

Documents about architecture and C++
------------------------------------

We try to gather all the documentation inside the Docs folder.
Those documents are related to implementation details and architecture of the engine at C++ level mainly,
not much user friendly to write LUA script for creating a game.

### Documentation_Libraries.md

This document is about all the open source libraries we have been using.
In some cases, the library have been modified to fit our purpose, so we needed to document it.
The other purpose is also to show that there are no license issue with the engine.

### Documentation_Modules.md

This document is about all the different "systems" or features inside the engine.
- Some are clean in the way that they are working around a singleton, and a bunch of instance with various subclasses,
independantly from other parts.
- Some features needed to modify source code in multiple places. (ie Encryption)
Basically the sum of the modules IS the engine itself.

See also /Modules/ directory with all modules specific information.

### Document_Tasks.txt

This document list the tasks that are implemented inside the engine.
Some are system tasks that the programmer is never aware of, some are system tasks that programmer can control.
Some are freely instanciable and here for the programmer to be manipulated.

### Documents about function and feature available from LUA
Doc/DocLUA_HTML.zip contains the list of functions, constants and command available
through LUA to create application using scripting.

Samples and Tutorials
---------------------

While it may not be a tutorial in the strict sense of the term, because there are not much step by step explaination,
we have also a tutorial-like showing LUA code testing different features of the engine.

See ```Tutorial/Samples.zip``` (for download size reason, we keep it zipped)

Prototype with C# Instead of LUA
---------------------------------
We also provide a version of the engine using C# instead of LUA as a scripting language.
The engine works with Mono, but also works with a custom compiler able to convert C# into C++.

See Doc/Documentation_CSharp.md
	
PLEASE UNDERSTAND THAT IT IS A PROTOTYPE and has not be completed to be in production, still
we believe that the amount of work put into this part of the project made it quite close to reality.

Implementation
--------------

Here is a representation of the important folders of the project :

- Engine 
  - fonts

      Contains the fonts used in the Engine.

  - include

      Contains some header files.

    - libs

        Contains the several libraries used in the Engine.

    - porting

        Contains the files related to the porting of the Engine on several platforms.

      - Android

          For Android

      - iOS

          For iOS

      - Win32

        For Windows

    - source

       Contains the source files.

  - SampleProject

      Sample project C++ base and C# prototype related implementation.

  - Tools

      Tool use for the games.(Toboggan)

  - CSharpVersion

      Everything related to the C# prototype

  - Tutorial

      List of tutorial to show LUA scripting and available APIs

#### Where are the project files ?

- Windows

  Engine/porting/Win32/GameLibraryWin32.sln

- Android

  Engine/porting/Android/

- iOS

  Engine/porting/iOS/Project/SampleProject/SampleProject.xcodeproj

Modify things
-------------

### Add new tasks.

  See "How To Add A New Task ?" in Docs/Modules/Tasks.txt

### Add new asset type.

  See "How To Add A New Asset Type ?" in Docs/Modules/Assets.txt

Road Map
--------

### Two main systems

- Font rendering based on texture-charmap support would be a big plus.

For now we render directly the text into a surface, each label cost memory.
We could trade-off those by having dynamically managed textures using only char cached instead of complete text.
This should result in less memory pressure on the textures but more vertex to process.

- Particle Effect System.
A particle system is necessary, Flash player is may be good enough for static animation,
but it lacks the fluidity,randomness and smoothness that a particle system can bring to games.

Post Mortem : What has been done correctly
-------------------------------------------

- Tasks system and basic architecture are modular enough.
- Binding to scripting language.
- Ability to import animation from a system like Flash.

Post Mortem : What could have been better
-----------------------------------------

- Scripting, APIs to be more user friendly.
- Sometime discrepancies between features, "holes" in API features.
- Current behavior not like originally planned after many iterations and user feedback.
Result in sometime idiotic/illogic behavior to fix an issue that should not have occured in the first place by design.

### Many of those issues resulted for various causes

- Difference in skills, understanding the necessity for architecture cleanness between the different developpers.
- Engine feature done/added/modified on a "for yesterday" basis.
- Political compromise over technical rightness.
- Different priorities.
