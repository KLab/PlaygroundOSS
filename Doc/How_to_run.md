

How to run
==========

Getting started
---------------

### Write your LUA code.

Sample Projects can be found in Tutorial/ directory.
A list of all available APIs can be found in Doc/SysCommandList.xls

### Create your assets with Toboggan tool and publish your project.

(Unzip Tool/Toboggan-Tools.zip)
Once you have unzipped, you can run Toboggan tool from
Tools/Toboggan/KLBToolHost.exe

For more details about this tool, please refer to
the documentation (in Japanese only sorry & Word format) :

```
Doc/Toboggan_Plugin_Manual_(JPN).docx
```

```
Doc/Toboggan_Operation_Manual_(JPN).docx
```

### Run it !

For more details about how to run the Game on your platform, a dedicated section is in this document,
see "How to run".

Compile the assets.
-------------------

While you could run right away the game engine, you will need to build 
all the assets used by your project with Toboggan tool.
(See getting started at the top of this document)

### In Toboggan, just 

- Open the project folder with File -> Open
- Project -> Clean
- Project -> Force Republish

### IMPORTANT NOTE

Note you can setup Toboggan to point to your OWN exe of the game engine and run it
directly from toboggan (See plugin settings in toboggan)

### IMPORTANT NOTE

When creating your own project, you can include any file you want into the building process.
By default, as there are no plugins able to do understand your files, you can decide the tool
to pickup your file and copy it into the build.

### How to do that 

- Suppose we have a file in ```a_folder/myFile.myExt```
- Just add a empty file (0 byte)  : ```a_folder/myFile.myExt.publish```

By adding this 0 byte .publish file, it will act as a marker and force the tool chain
to include this file in the build.

See tutorial where the font files are actually copied this way.

How to run (the game engine once the project asset are build)
-------------------------------------------------------------

One of the Game Engine goal is to provide a multi-platform engine for games. Obviously it can be run with Windows (for development),
MacOS, Android and iOS. Here we will explain how to run on these different platforms.

## Windows

With the project is provided a Microsoft Visual Studio solution (2010 and higher).
The solution file is located at Engine/porting/Win32/GameLibraryWin32.sln
With the Engine is also provided a Game Project Sample and some Script Samples (See Tutorial folder).
(Files have been tested with Visual 2010 Express for this release)

### Game Project Sample

#### Opening the engine solution, you will find 2 projects 

- GameLibraryWin32 which is the Game ENGINE project.
- SampleProject which is the GAME poject.

You may want to modify the Game Engine to add Tasks Classes or to modify some Tasks behavior (see Docs/Documentation_Tasks.txt
for more details about Tasks).
You may want to modify the Game project to add Game Specific classes.

To chose the script to run, you have to modify the command line used to launch the game.
In Visual Studios, modify SampleProject ```Properties > Debugging > Command line arguments```

### Add at least these arguments to the command line : 

```
-e "PathToYourRootProjectAsset/.publish/iphone/"
-i "PathToYourRootProjectAsset/.publish/iphone/"
```

For instance, to run the "01.SimpleItem" sample project, if you have install the game engine under ```C:\Playground\```

```
-e "C:/Playground/Tutorial/01.SimpleItem/.publish/iphone/" 
-i "C:/Playground/Tutorial/01.SimpleItem/.publish/iphone/"
```

**Note** 

- /iphone if you publish using the iphone profile,
- /android if you use the android profile. 

(See tool publishing options)


### IMPORTANT Note

You can also setup the Toboggan tool to use your executable.

Start toboggan : Tool menu -> Setup -> 

1. GameEngine location : 

```
...\playgroundOSS\Engine\porting\Win32\Output\SampleProject.exe
```

(after you build the .sln file of course)

#### Command Line Arguments
- ```-w int```

  Specifies the screen width.

- ```-h int```

  Specifies the screen height.

- ```-i string```

  Specifies the install path.

- ```-e string```

  Specifies the extern path.

- ```-t int```

  Defines a constant DeltaT between frames.

- ```-enc true/1/false/0```

  Enables/Disables the encryption (see Docs/Modules/Encryption.txt for more details).


**WARNING**

Make sure the -enc options match the build option in the tool ! 
(If you rewrote the encryption of course, the default OSS is transparent so it does not apply here)

Once the command line had been added to the SampleProject, you just need to run it and the LUA script will be executed.
You can now start to write your own game !
Please refer to the "How to start a LUA Game" section for more details.

	
## MacOS and iOS

Start the XCode project from 

```
Engine/porting/iOS/Project/SampleProject/SampleProject.xcodeproj
```
	
### Now you need to bind your compiled folder

- Open Finder and go to ```PathToYourProjectAsset/.publish/iphone```
- Drag and drop to ```ProjectResources``` folder inside XCode project
- Select the ```Sample Project``` in XCode, file menu -> ```Add File to Sample Project```
- File navigation appears, select the "PathToYourProjectAsset/.publish/iphone"
- Pop up appears, DO NOT FORGET to select your target in ```Add To Targets```
- ```Finish``` button.

It will add the compiled ressources to the application.

**WARNING**

iOS version supports only encrypted data in its version (it is possible to desactivate globally the encryption) but
when trying the tutorial or your own data, make sure that you publish them as encrypted.
The OSS implementation is "transparent encryption" so it should make no difference, but just be aware of it.

#### IMPORTANT NOTE

- If you run your own project IOS and Android version need a game.db file to run, see Tutorial.txt for description of the issue.
- You need a default font in your entrance (Sample Project)

### Android 

See **Android_Build.md**

## Script Samples

Several script samples have been provided with the project.
Be aware that you need to compile them with the tool first, then embedded the data in the case of Android or iOS.

How to run C# module instead of LUA & How to run the C# to CPP compiler
------------------------------------------------------------------------

Please refer to **Documentation_CSharp.md**
