Tasks
=====

This file will introduce the tasks used in the engine.

The tasks are the basics object used by scripting.
Refer to the Tasks module documentation for more details about implementation and architecture. (Doc/Modules/Tasks.txt)

Tasks are splitted into System Tasks and User Tasks as follows
--------------------------------------------------------------

### System Tasks

System tasks are task that the developper do not control fully or control at all.
Things like processing the event queue to detect UI click or perform the rendering, execute the script, are system tasks.

### User Tasks

#### User UI Tasks

Those are visual task (=displayed on screen) that the developper can use freely, decide how and when to use them.

#### User other Tasks

Those are task that the develloper can use freely but they are not visual.
Things like using a timer, request the event queue, etc... are user task.

Here are the C++ classes used in the game engine.

### Base Abstract Classes 

#### Tasks Root class : CKLBTask

The Game Engine is based on a frame-by-frame processing.
Each unit processed each frame is managed by the class CKLBTask.
CKLBTask is the base class for all the tasks of the engine.
By registering a task in the TaskManager it will be run as a process in the game.

For more details regarding the Tasks management, refer to the TaskManager documentation
or the Tasks module documentation (Doc/Modules/Tasks.txt).

#### CKLBLuaTask : CKLBTask

CKLBLuaTask is the abstract root class for every task 
that can be created from a script command.
It defines some virtual methods and some generic callbacks.

CKLBLuaTask objects can interact with the scripting langage
throught methods/commands calls depending on the scripting langage.

#### CKLBLuaPropTask : CKLBLuaTask

CKLBLuaPropTask is a CKLBLuaTask with properties (int, uint, float, string, bool, pointers).
These properties can be read and/or written by the scripting part of the game,
depending on their declaration.
It is an abstract class for every class in the Engine using properties.

#### CKLBUITask : CKLBLuaPropTask

CKLBUITask is the root class for every UI Task Classes in the Engine.
It defines some properties helpful for every subclasses (such as
alpha, color, scale, rotation, position, visibility).
You can also attach to a CKLBUITask some spline animations.

Each UITask is linked with a Node of the SceneGraph to be rendered.
Both objects point each other.
For more details, see Doc/Modules/SceneGraph.txt

The different CKLBUITask subclasses will be detailled above.

### System Tasks 

System Tasks are tasks created when launching the game and not controlled
by the programmer.
It regroups the following tasks : 

#### CKLBDebugMenu : CKLBTask

CKLBDebugMenu allows to create a debug menu task for your game.
Several items can be used in the Menu : 

- Switch between 2 values.
- Numbers.
- Select between several values.

#### CKLBDrawTask  : CKLBTask

CKLBDrawTask is in charge of drawing the game resources each frame.

**Actually it has several steps**

- Perform node spline animation update.
- Perform scene graph update.
- Perform rendering.

It is instancied only once and draws all the resources in one and only one draw call.
This task is instancied when the game starts and dies when it stops.

#### CKLBLuaScript : CKLBTask

CKLBLuaScript is used to load and execute some Lua script from an URL.

#### CKLBOSCtrlEvent : CKLBTask

CKLBOSCtrlEvent is the class in charge of handling the OS events.
Each frame it allows some events to be visible for the Engine.
This task is instanciated once when the game starts.

CKLBTouchEventUITask : CKLBTask
CKLBTouchEventUITask is in charge of handling the various touch events 
of the game and redistribute it to the right item. 
Forms can be registered in order to be able to process some actions 
on Touch Pad events.
This task is instanciated once when the game starts.

#### CKLBTouchPad : CKLBTask 

CKLBTouchPad is similar to CKLBOSCtrlEvent, but only handles Touch Pad events.
It owns a queue of Touch Pad events.
This task is instanciated once when the game starts.

### User Tasks

User Tasks are tasks the programmer can instanciate through LUA (or another scripting language).
They all inherits from CKLBLuaTask previously described.
User Tasks can be User UI Tasks (all UI related tasks) or User Other Tasks (download, unzip, network, etc).

### User UI Tasks

#### CKLBUIActivityIndicator : CKLBUITask

This task display an OS native "busy" indicator to show that the device is busy doing some work.
As an example, when application is connecting or transfering data with the server.

#### CKLBUIButton : CKLBLuaTask

This task allow to detect and use click on physical button on a
device.

#### CKLBUICanvas : CKLBUITask

CKLBUICanvas regroups various images to draw Canvas
The different assets must be in the same texture.

#### CKLBUIClip : CKLBUITask

CKLBUIClip creates a Task clipping the screen for the required area.
Sub tasks outside the clipping area will not be drawn.

#### CKLBUIControl : CKLBLuaTask

CKLBUIControl is a high level Touch Pad Events handler.
Events (Tap, Drag, Release) are interpreted into higher level events such as 
Click, Double Click, Drag, Long Tap, Pinch).
It provides a few callbacks that are called when some actions are processed.
Events can be masked to select only the ones you want.

#### CKLBUIDebugItem : CKLBUITask

CKLBUIDebugItem allows to display debug purpose items in the Game.
A few properties (such as text, color, etc.) can be modified in runtime 
and used for debugging.

#### CKLBUIDragIcon : CKLBUITask

CKLBUIDragIcon allows to create a Task owning an image and answering the Drag Events.
The image can be scalled and/or moved while draging.
A specific drag area can also be defined to limitate the DragIcon possible received events.
#### CKLBUIForm : CKLBUITask

CKLBUIForm is designed to manage forms in the Game.
It allows to manage a whole form (composed of several sub elements) very easily.

#### CKLBUIFreeVertItem : CKLBUITask

CKLBUIFreeVertItem can display image like CKLBUISimpleItem.
However, it is possible to modify the UV, Colors and coordinate for each vertex.
It is usefull also to just display a filled area with a given RGBA color, or gradient display 
without texture at all.

#### CKLBUIGroup : CKLBUITask

CKLBUIGroup allows to easily manage UITasks groups.
With CKLBUIGroup you can anim or skip the anim of a whole group of tasks 
at the same time with a single command.

#### CKLBUILabel : CKLBUITask

CKLBUILabel is a basic text label task.

#### CKLBUIList : CKLBUITask

CKLBUIList allows to create and manage lists of items.
It comes with its own scrollbar.
Items can be added dynamically and managed easily through the several developped APIs.

#### CKLBUIMoviePlayer : CKLBUITask
CKLBUIMoviePlayer is used to play movies into the Game.
It provides a few APIs to manage the movie display and some playing option 
(play, stop, pause, resume).
The task is platform independant as it uses a CKLBMovieNode which
uses itself an implementation of IWidget that is platform specific.
/!\ CKLBUIMoviePlayer does NOT work on Windows at the moment.

#### CKLBUIMultiImgItem : CKLBUITask

CKLBUIMultiImgItem is used to regroup some images into one Task.
One image only is displayed every frame, but the active image can be changed
at any moment through provided APIs.

#### CKLBUIPieChart : CKLBUITask

CKLBUIPieChart allows to create progress bar that are circular.

#### CKLBUIPolyline : CKLBUITask

CKLBUIPolyline allows to create Polylines.

#### CKLBUIProgressBar : CKLBUITask

CKLBUIProgressBar allows to create dynamic Progress Bars.

#### CKLBUIRubberBand : CKLBUITask

CKLBUIRubberBand allows to create dynamic Rubber Bands.

#### CKLBUIScale9 : CKLBUITask

CKLBUIScale9 is designed to manage assets cut in 9 parts.
4 for corners, 4 for borders and 1 for the center.
It uses a CKLBSpriteScale9, refer to CKLBSpriteScale9 documentation for more details
(Doc/Modules/Rendering.txt).

#### CKLBUIScore : CKLBUITask

CKLBUIScore is designed for managing Score.
It handles 10 assets, one for each digit and uses it to display a score.
It also manages the animation going with the two different scores transitions.

#### CKLBUIScrollBar : CKLBUITask

CKLBUIScrollBar allows to create and manage a Scroll Bar.
The Scroll Bar action into the Game can be defined through a callback.

#### CKLBUISimpleItem : CKLBUITask

CKLBUISimpleItem is a simple Image.

#### CKLBUISWFPlayer : CKLBUITask

CKLBUISWFPlayer is a Flash Player that can read and display our SWFAssets.

#### CKLBUITextInput : CKLBUITask

CKLBUITextInput is a UITask managing text inputs.
In addition to providing desing and display APIs, it also provides some control ones 
such as a maximum length control.

#### CKLBUITouchPad : CKLBLuaTask

CKLBUITouchPad is a simple low level Touch Pad Events handler.
It provides a few callbacks that are called when some actions are processed
(Only Tap, Drag and Release).
For a higher level Touch Pad Events handling, see UIControl.

#### CKLBUIVariableItem : CKLBUITask

CKLBUIVariableItem is nearly similar to CKLBUISimpleItem.
However, it is possible to modify the UV on the texture 
or to change the asset associated to an instance of CKLBUIVariableItem.

#### CKLBUIVirtualDoc : CKLBUITask

CKLBUIVirtualDoc creates and allows to manage a Virtual Document.
A Virtual Document allows to manage the rendering of an area of the screen.
Several items can be associated to it, such as text, lines or images.

#### CKLBUIWebArea : CKLBUITask

CKLBUIWebArea is used to create a web browser instance.

### User Other Tasks

#### CKLBNetAPI : CKLBLuaTask

Networking task perform network connections and retrieve data from a server.
See more detail in Modules/Network.txt

#### CKLBAsyncFilecopy : CKLBLuaPropTask
File copy may be a long operation to process.
In order to lighten the process cost for the game, it can be done
by another thread through a CKLBAsyncFilecopy object.

To load a resource in an asynchronous way, see CKLBAsyncLoader.

#### CKLBAsyncLoader : CKLBLuaPropTask

Loading resources can be a long task for the Game and make it long to load some scenes.
In order to be able to keep on processing the Game Logic while loading resources, 
CKLBAsyncLoader has been implemented.
It allows the Engine to load resources through another thread.

To copy a file in an asynchronous way, see CKLBAsyncLoader.

#### CKLBDebugSign : CKLBTask

Internal task created by CKLBDebugMenu for controlling the appearance or disappearance of debug menu.
It detect a specific sign made by moving the finger on the screen.

1x          x3
  xx      xx  x
    xx  xx    x
  xx      x
    xx  xx    x
  xx      xx  x
4x          x2

**Following the 1,2,3,4 order.**

#### CKLBDebugMenu : CKLBTask

CKLBDebugMenu allows to create a debug menu task for your game.
Several items can be used in the Menu : 

- Switch between 2 values.
- Numbers.
- Select between several values.

Compile option DEBUG_MENU must be set to be able to use it.

#### CKLBGenericTask : CKLBLuaPropTask

CKLBGenericTask is the most generic class of the Engine that can be used
for scripting purpose.
It is just made to execute some script code every frame.

#### CKLBIntervalTimer : CKLBLuaPropTask

CKLBIntervalTimer is a basic timer class.
It makes a call to the callback function when the timer reached the defined time limit.
It can make this call just once and then die or be in a repeat mode and reset itself
every time it reaches the defined time limit.

#### CKLBLifeCtrlTask : CKLBLuaTask

CKLBLifeCtrlTask is a Task made for controlling the life of another Task
of the Engine. 
CKLBLifeCtrlTask has 2 mods : TIME and FRAME.
A Task can be linked with an instance of CKLBLifeCtrlTask. In that case, the 
CKLBLifeCtrlTask will kill the Task after X milliseconds or frames.

#### CKLBPauseCtrl : CKLBLuaTask

CKLBPauseCtrl allows to add control to a class when you pause and/or resume it, 
as it is not provided by default in a CKLBTask.
You can register callbacks that will be called when pausing and resuming the Task.

#### CKLBStoreService : CKLBLuaTask

CKLBStoreService is responsible for the different interactions with the Application Store,
as getting the products list or buying items.
This task is platform independant as it uses IPlatformRequest to process its requests.

#### CKLBUpdate : CKLBLuaTask

CKLBUpdate is used to update files.
It downloads it from a specified URL and unzips it.
Specific callbacks can be registered to be called after different steps
such as the end of the dowload step, the unzipping step or when the whole 
process is over.

#### CKLBUpdateZip : CKLBUpdate

CKLBUpdateZip works the same way as CKLBUpdate but only unzips a file already downloaded.
See CKLBUpdate for more details.

