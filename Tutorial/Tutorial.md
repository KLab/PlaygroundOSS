Tutorial Playground (Engine) / Toboggan (Tool) 
==============================================

Install
-------

### Install the tools

First, we need to have the tools installed. See documentation concerning the tools.
  
### Install the samples

So as you are reading this text file, it means
that you have unzipped the sample archive.

We are now ready to go.

First steps
-----------

### Run the editor
  
From start menu, execute the newly installed "Tobbogan"
  
If you go to the file menu, you can directly create a new project and new resources inside it.

#### IMPORTANT 

To run the sample, you MUST setup command line option to disable some engine features to avoid ASSERT when
we start the engine.

**Go to Tools -> Setup** 

Setting window appears.

**Go to [General] Tab, then "Bundled GameEngine Settings" entry, on argument "CmdLine Parameters" type**

```
- no defaultdb -no defaultfont
```
  
### The tools has mainly the following editors included 

- Image / Texture resources editors
- UI resources Editor
- Various plugin about database, audio, flash conversion, etc...
- AI resources Editor (out of this scope)
  
A texture is a collection of multiple images, with a specific size and color depth for the texture itself.
Image editor allows to add engine-specific properties to standard images.
  
#### IMPORTANT 

You can not display images without creating textures.

[More detail]

- Complete User Guide
  - Toboggan_Operation_Manual_(JPN).docx &
  - Toboggan_Plugin_Manual_(JPN).docx
  
#### It includes 

- Image Editor.

**Note**

images are different properties, in some use-cases (ie with a specific task), images must set to have specific properties.
The most specific properties the image to be rectangular with 4 vertices in the default order.
This allows computations to be performed. See documentation in detail.
    
- Texture Editor.
    
- Create a new texture.
[Future improvment : Put it as PDF inside ebisu drive with sample in case of access issue, update link with page number]
  
## "Open the box" and launch a project.

For this tutorial, we will not worry much about detailed functionnality.
As described in the previous section, you can read the full manual of the tool if you wonder about a specific feature.
We will try to focus only on the general process on how to make an application with Playground.
  
In section 1.2, you have unzipped sample playground projects, so we are going to use them.
Let say that you have unzipped everything in "C:\Unzip\"

### You have started toboggan, then go to "File" -> "Open", and select any FOLDER from the unzipped archive.

A complete project folder always contains all the assets necessary to run a project.
The tool will load everything inside the folder and then you are ready to execute the sample.

### Go to "Tools" -> "Run" and see the sample run.

A Playground instance appears and execute the sample project.

#### IMPORTANT:

You can close the windows by closing the log window, or having the game engine as the main window and do ALT-F4.
The tool can close the engine client with "Tools"->"Shutdown" menu.

Now you can test all the samples, folder by folder. Load a different folder and go to "Tools" -> "Run" to test each of those.
  
## Dissecting a project

You have opened and runned some projects now, but you need to know how it works in detail.

Let's open "SimpleItem" which is the most simple project.
It takes an image and display it to the screen.

### Image
  
In the project explorer windows, you can see there are different files :

- itemimage.png
- start.lua
- SimpleItem.lua
- textureBoat.xml

itemimage.png and textureBoat are the graphics ressources.
start.lua and SimpleItem.lua are programs source code written in the LUA language.
  
### Entry point & LUA file life-cycle
  
For a project to run, it needs to execute the programmer code.

#### IMPORTANT

The playground engine ALWAYS start with "start.lua" in the root of the project.
(ie as a file directly in the project main folder)

- Inside "start.lua" in this sample

```lua
function setup()
end

function execute(deltaT)
  sysLoad("asset://SimpleItem.lua")
end

function leave()
end
```

When a LUA file is loaded the following execution sequence occurs :

- run previous lua file "leave" function.
- run "setup" in newly loaded lua file, then the lua file become the current file.
- run "execute" forever once per frame, until engine stops or another LUA file is loaded.

```
+-------------------------------------------+
| Execute "leave" in previous lua file      |<--------+
+-------------------------------------------+         |
                 |  |  |                              |
                 V  V  V                              |
+-------------------------------------------+         |  New LUA file is loaded, current becomes
| Execute "setup" in new lua file           |         |  previous, new file is current.
+-------------------------------------------+         |
                 |  |  |                              |
                 V  V  V                              |
+-------------------------------------------+         |
| Execute "execute" in new lua file         | <---+   |
+-------------------------------------------+     |   |
                  |   |                           |   |
                  |   |                           |   |
+------------------------------------------------------+
|                       Game Execute                   |
|                                                      |
+------------------------------------------------------+
```

So, going back to our tutorial,

1. start.lua is loaded
2. there is no previously loaded LUA file, so leave() is not executed.
3. setup() in start.lua is executed
4. execute() in start.lua is executed
    We see that in execute(), we call :
    sysLoad("asset://SimpleItem.lua")
5. The code request the loading of simpleItem.lua
6. SimpleItem.lua is loaded
7. start.lua leave() is executed
8. SimpleItem.lua setup() is executed
9. SimpleItem.lua execute() is executed forever until you stop the program.
  
#### IMPORTANT 

Leave is executed RIGHT AWAY when requestion the loading of the new file.
But Setup is executed at the BEGINNING of the NEXT FRAME.
In this case, the engine disable the execution of "execute" to make sure no problem occurs.
  
### The sample itself
  
Now in SimpleItem.lua, we create an instance of an object displaying an image.

**The call is the following**
 
```lua
# <task pointer> = UI_SimpleItem( <parent pointer>, <order>, <x>, <y>, "<asset>")

pSimpleItem = UI_SimpleItem( nil, 7000, 100, 100, "asset://itemimage.png.imag")
```

Which can be described as : we create an instance of an image, with no parent relationship at coordinate 100,100 of the image we have
in the project.
  
**In execute, we also modify the properties of the object using the following code**

Example, change alpha to 128 from 255

```lua
prop = TASK_getProperty(pSimpleItem)
prop.alpha = 128
TASK_setProperty(pSimpleItem, prop)  
```

Here is a list of ALL properties, supported by ALL UI_* component (not only UI_SimpleItem)
See document in archive DocLUA_HTML.zip : properties.html

### What can I create ? What do I modify ?

There are multiple type of object that can be created.

- Tasks / UI Tasks
  
  Task are object that are updated in real time or perform changes over time, thus they need to refresh every frame.
  UI tasks are tasks that also displayed to the screen.
    
  The full list is here : 
  See document in archive DocLUA_HTML.zip : tasks.html

  UI tasks can be connected to each other in a tree-like fashion. Allowing for coordinate system to be relative between items.
  (example : the child is X+30,Y+30 pixels from its parents, whatever the parent is located)
  See document in archive DocLUA_HTML.zip : tree.html

  As already said, all UI tasks have also a common set of properties that can be modified at runtime.
  See document in archive DocLUA_HTML.zip : properties.html
    
- Standard Function, some create objects (Font, Dataset, Sound, DB, ...), some other get or set engine status.
  
  - Set of API to control the following areas :
    - System control APIs.
    - Identification APIs.
    - Display control APIs.
    - Engine related APIs.
    - Font.
    - Audio.
    - Asset management.
    - Task control.
    - AI.
    - Utility / Math.
    - Language support.
    - Database.
    
    The full list is here with sample code and description : 
    See document in archive DocLUA_HTML.zip : functions.html & tasks.html

## Rendering : Node, Asset & Priority

### From the programmer's point of view, visual graphics can only be created the following way

- Creating a graphics UI* task from LUA by code.
- Creating a graphic UI* task or other graphic component inside a form using UI editor.
  
All are scene graph based, which means that an objet coordinate is RELATIVE to its parent coordinate.
By having a parent-child relation ship a tree of graphics can be built.
Any item in the tree have common properties such as scaling, rotation, color, position.

Coordinate and geometric transformation
    
As written in the previous paragraph, screen coordinate are decided by the parent coordinates 
and transformation and own coordinates.
    
Transformation including combination of rotation, scaling and translation.
   
### Exception of native component
    
In some cases, things like Web Browser, Input Box and the like are system component that are
overdrawn on the top of the rendering view directly by the OS, so they may not support
completly all the transformation. So behavior is not garanteed if any transformation is applied.
Only coordinates can be set.
      
- Ex : font size will not change even if we scale
- Ex : Most of them will not support rotation either and end up beeing a rectangle aligned on X and Y axis.
      
### Exception of clipping

There are two possible clipping possible when using container in forms.
One way does support any transform. The other one does NOT support rotation. (See details)
    
### Priority

All the graphics objects (graphics tasks, items in a form, ...) have a priority property.
Most of the time, the order in the tree should be enough to define the rendering order but
by having the priority set seperatly from the tree definition, rendering order is unrelated to the
tree structure of the display.

### Color transformation

Same as rotation and other transformations with the tree structure of visual object,
color can be multiplied by channel allow to have a parent to globally control the color of all the children.
    
**As the transformation is by channel it is very easy**

```lua
Child Screen Color = Child Original Color * Parent Screen Color  (same formula for all R,G,B,A component)
```

##  List & description of all samples

1.SimpleItem

Load an image from a texture and displays it to the screen.
    
2.Score

Associate a list of images for 0..9 score character.

- Create Score instance
- Create a list of animation when the score changes.
  - Animation for old value
  - Animation for new value
- Modify properties over time
- Execute various command
    
**See also**

See document in archive DocLUA_HTML.zip : UI_Score.html

3.PieChart (& TouchPad)

- Create a pie chart
- Create a touch pad task and use user touch event to control the pie chart.
    
**Usage**

- The upper horizontal part of the screen on click defines the start angle.   

  ```
(y between 0..200)
```

- The middle horizontal part of the screen on click defines the end angle.    

  ```
(y between 200..400)
```

- The lower horizontal part of the screen on click defines the current value.  

  ```
(y more than 400)
```

**See also**

See document in archive DocLUA_HTML.zip : UI_TouchPad.html & UI_PieChart.html

4.ProgressBar

- Create a progress bar instance.(empty by default)
- Setup the progress bar to be full.

**Note**

- Progress bar only support "rectangular" images.

**See also**

See document in archive DocLUA_HTML.zip : UI_ProgressBar.html

5.Polyline

- Create 2 lines with different colors
- Modify generic node properties
- Modify the polyline point count and coordinate.
    
**See also**

See document in archive DocLUA_HTML.zip : UI_Polyline.html
  
6.Texbox

- Create a OS native text input box.
- Modify the generic node properties.
- Execute text input specific commands.

**IMPORTANT NOTE**

- Some command may fully work only on IOS or Android (font aspect, font color)
  (Windows port is limited)
- Native object does not support rotation or scaling fully because of OS non supporting
  those features.
  Thus, some generic property like color, rotation, scaling may not work as they would suppose to.
      
**See also**

See document in archive DocLUA_HTML.zip : UI_TextInput.html
    
7.Label

- Create a label with "Hello World !!!" text.
- Modify generic node properties
- Execute label specific commands.

**IMPORTANT NOTE**

To use this sample, you will need to have a font installed inside the game engine.
There are 2 ways to have a font installed.
    

- The first method is to :
  - Use an executable which load a font by default and provide the font.
  - Have the true type font (ttf) file provided inside your root project.

- The second method is to load the font through LUA :
  - still have "-no defaultfont" in the command line (in case exe try a default font)
  - Have your own true type font file provided inside your root project.
  - Call font loader from LUA.
      
In our sample we will use the second option and provide a default font.

**IMPORTANT NOTE**

- Label used in Form and label created using tasks behave differently.
  - In the case of label inside form, the size is fixed.
  - In the case of label created dynamically using UI_Label task, size vary
    automatically to fit text size.
      
  - Each time a new text is displayed, allocation of a 2D surface, then rendering is performed.

     This, UI_Label is very heavy for dynamically changing text.
     If text changes often, using the label inside a form OR use a virtual document (see later) is a recommanded usage.
     
  - Node color and text color are two different things and they combine the same way as node colors.
    
**See also**

See document in archive DocLUA_HTML.zip : UI_Label.html
See document in archive DocLUA_HTML.zip : functions.htm#フォント情報関数
    
8.DragIcon (& UI_Group)

- Create a draggable icon.
- Handle all the drag event.
  - Create an image instance on release
  - Modify properties over time
- Use of UI_Group to store a list of sub items.
    
**See also**

See document in archive DocLUA_HTML.zip : UI_Group.html
See document in archive DocLUA_HTML.zip : UI_DragIcon.html

9.RubberBand (& UI_TouchPad + Sound API + Task API)

- Create / destroy a rubber band object based on tap event.
- Rubber band object perform an animation while active.
- Rubber band is updated while tap event position changes.
- Load, play, stop sounds.
  
Rubber band is showing an animated band that show a direction between a start and end point.
User can setup the design and various behaviours.
  
**See also**

- See document in archive DocLUA_HTML.zip : UI_RubberBand.html
- See document in archive DocLUA_HTML.zip : UI_TouchPad.html
- See document in archive DocLUA_HTML.zip : functions.htm#サウンド関数
- See document in archive DocLUA_HTML.zip : functions.htm#タスク関数

10.IntervalTimer

- Create a timer task that callback the user when a specific time is reached.
- Modify timer properties at run time and see the difference (loop, time)
- Call to log and string formatting functions to show the timer in action.

**See also** 

See document in archive DocLUA_HTML.zip : UTIL_IntervalTimer.html
(syslog)
See document in archive DocLUA_HTML.zip : functions.htm#システム関数

11.LangTest

- Load a database with language information.
- Get a string from the database.

tableScheme.csql file will define how to create the language table.
lang_tbl.csv file will define the data to fill the lang_tbl table.

Language API allow support for multilingual application.

**IMPORTANT**

See text resource section

**See also**

See document in archive DocLUA_HTML.zip : functions.htm#言語DB関数
  
12.FreeVertItem

- Create a task that can take "rectangular" images and modify the X,Y coordinate of each vertex freely.
- Modify standard node properties
- Execute task specific coordinate, sub image (UV coordinate) and color modification for each vertex.

FreeVertItem is an object allowing to freely modify the vertex position and texture coordinate within the original image.
    
**See also**

See document in archive DocLUA_HTML.zip : UI_FreeVertItem.html

13.VariableItem

This task is like SimpleItem, except it is possible to :

- Change the image asset at runtime.
- Streatch the image.
- Apply masking to the image.

**See also**

See document in archive DocLUA_HTML.zip : UI_VariableItem

14.MultiImgItem

Multi Image Item is like Simple Item except that it preloads a list of images.
It makes things easy in a way that programmer do not need to lookup a list of image name each time
the image is changed, moreover inside the engine as images are preloaded, performance is slightly better.

- Create a multiple item instance with 3 images.
- Modify generic and item properties.
- Call UI_MULTIIMG_SET_INDEX and switch images.

**See also**

See document in archive DocLUA_HTML.zip : UI_MultiImgItem.html

15.Scale9

Scale9 is an image which is stretchable in both width and height, with corner of FIXED size.
To use as image as a "Scale9", properties of the image must be set inside the tool.

- Create instances of Scale9 task.
- Modify generic properties.
- Modify width and height properties.

Tools documentation :
Toboggan_Plugin_Manual_(JPN).docx in /Doc. (Using Scale9 in Forms)

See sample code and engine implementation for command detail.
    
16.Sound
  
- Load and start a BGM sound.

  A BGM is a long audio stream that should not be fully loaded in memory but streamed and decoded over time.

- Load and start an SE sound. (SE = Sound Effect)

  SE are decoded in memory, thus requiring close to none decoding time but consuming memory.

In this sample, we use the RubberBand object to associate sound and graphic effects.
Using SND_Open, SND_Close, SND_Play.

**See also**

See document in archive DocLUA_HTML.zip : functions.htm#サウンド関数
    
17.VDoc

Virtual docuement is a surface, like a canvas where it is possible to render a list of drawing command.
The canvas can scroll and the graphics objects are redrawn. Current limitation is that scrolling is either horizontal or vertical but not both at the same time.
[Fail with embedded but work with latest master branch !?]

- Create Virtual Document
- Setup draw command to the virtual document.
- Handle event to scroll the document.
  
**See also**

See document in archive DocLUA_HTML.zip : UI_VirtualDoc.html

18.DebugItem

Create a DebugLabel. Use for debugging.

**WARNING**

  In this sample, font MUST BE PREINSTALLED. Ie have a font that match the hardcoded preinstalled font name.
  (normally georgia.ttf with the default EXE provided by the tool)
  We provide a default font file in this sample renamed as georgia, but it is the same font as provided in sample 07.Label

  -> Debug internal object are created BEFORE scripting language starts

[This sample need further document with complete sample about using debug system, for now
people should look at fully functionning internal project]

**See also**

See document in archive DocLUA_HTML.zip : UI_DbgLabel.html

19.GenericTask

Create a task that can control tasks done in LUA.
Three task scrolling vertically, controlled by lua.

It is important to notice in this sample that :
- We kill the controlled task in execute of the generic task once we need to get rid of it, NOT in DIE callback.
- We also kill the generic task the same way.
- We MUST NOT PASS the generic task as parent : it has NO graphic node -> Object will be out of screen.

**See also**

See document in archive DocLUA_HTML.zip : TASK_Generic.html

20.LifeCtrl

LifeCtrl attaches as parent task to a given task. When timer is reached, LifeCtrl self destruct, resulting in destroying also all the child tasks.

**See also**
See document in archive DocLUA_HTML.zip : LIFECtrl.html

21.Form

A form is a task that regroup a complete tree of task but also other component available in the UI tree.
Inside the editor we create a form with container, checkboxes, button, label, editable text.
In the sample code, we create an instance of a form and show how to jump from a form to another.

Form has a lot of commands, so look at the documentation in detail.

**See also**

See document in archive DocLUA_HTML.zip : UI_Form.html

22.List

- Create a list instance, using dynamic mode (basically create the minimum amount of item, and perform callback when item is restored on scroll)

- Create a scrollbar in "scroll by page" mode, link a bitmap for its display.
- Have the asset in the tool for the bitmap, and for the default item associated with the list.
- Load the form asset associated with each item in the list.
- Add items to the list.

**IMPORTANT NOTE**

As the sample use label, font is also added to the project.

Many many more possibilities are available with list :

- Dynamic or static list (closer to fly-weight objects)
- Usage of scrollbars

**See also**

Complete Documentation :
See document in archive DocLUA_HTML.zip : UI_List.html

**FAQ**

See document in archive DocLUA_HTML.zip : engine_design_task_FAQ.htm#UI_List%E7%B7%A8
See document in archive DocLUA_HTML.zip : engine_design_task_FAQ.htm#UI_FormUI_List%E5%85%B1%E9%80%9A%E7%B7%A8

23.ListSpline

Create a form with a list contained inside the editor.

The list design contains a spline which define how items will behave when scrolling along the spline.
- X,Y offsets
- Scale X,Y
- Rotation
- Colors
- Layout (spacing)

**Complete Documentation**

See document in archive DocLUA_HTML.zip : UI_List.html

**FAQ**

See document in archive DocLUA_HTML.zip : engine_design_task_FAQ.htm#UI_List%E7%B7%A8
See document in archive DocLUA_HTML.zip : engine_design_task_FAQ.htm#UI_FormUI_List%E5%85%B1%E9%80%9A%E7%B7%A8

**Spline for list inside the tool**

[Currently Undocumented on the intra]

24.Canvas

Canvas is a "graphic batch" object.
It is like a collection of sprite, rendering commands.
Its only limitation is to have ALL the graphic assets INSIDE the SAME TEXTURE.

**Canvas has the following syscommand**

  ```lua
  UI_CANVAS_ADDRESOURCE, asset      : Add an asset usable by the canvas    
  UI_CANVAS_FREEZE, free_true_false    : Decide if the Canvas will callback the draw function each frame or if the batch is 'static'. 
  ```

**Graphic primitive**

  ```lua
  UI_CANVAS_DRAWIMAGE,      x,y, assetIndex, colorARGB    : Draw an image
  UI_CANVAS_DRAWIMAGESCALE, x,y,scale,assetIndex, colorARGB  : Draw a scaled image
  UI_CANVAS_FILLRECT,       x,y,width,height,colorARGB    : Draw a filled surface.
  ```
We will ignore those more advanced functions for now :

  ```lua
  UI_CANVAS_STARTSECTION
  UI_CANVAS_ENDSECTION    
  UI_CANVAS_SECTIONTRANSLATE  
  UI_CANVAS_SECTIONCOLOR    
  ```

The easiest use case could be as an example a labyrinth background for a pacman game or a tetris.
You want to minimize the amount of surface to draw to save GPU bandwidth, the memory used (ie not using a complete surface for no background)

**Sequence**

- Set freeze to false somewhere in your logic. (canvas is set to false by default when created) 
- Callback will occur on the Canvas object, draw all primitives on the canvas, all the tiles for the background.
- Set freeze to true inside the callback after the last primive.

**Creation**

```lua
taskCanvas = UI_Canvas( <parentTask>, <priority>, <x>, <y>, <max number of vertex>, <max number of index>, <callback function>)
```

The number of vertex/index is the number of polygons that can be batched in this canvas instance.
With default usage, a good approximation is to have 4 vertices and 6 index per image drawn.
(Counting could be different if you use more complex model)

**See also**

[Incomplete Documentation][Wiki is not done at all]
    
25.SWFPlayer

- Create an instance of a flash asset.
- Detect when reaching a given label or the end of the flash content.
- Force player to jump to a specific frame.

The flash player support audio, support movie in movie.
It of course support images but they must be wrapped in a movie as seen in the sample flash content.

Flash file include relation to assets, and it is possible to switch asset at runtime and use the flash
animation as a template for contents.

**See also**

See document in archive DocLUA_HTML.zip : UI_SWFPlayer.html    
    
26.ScrollBar

- Create horizontal and vertical scrollbars.
- Use a callback function to know when the scroll bar has changed.
- Modify various scrollbar properties and see the effects.

**See also**
See document in archive DocLUA_HTML.zip : UI_ScrollBar.html    
  
## Future task, no sample yet.

27.UI_ActivityIndicator]

Only documented, no sample for now.

**See also**

See document in archive DocLUA_HTML.zip : UI_ActivityIndicator.html

28.UI_Clip

Only documented, no sample for now.

**See also**
See document in archive DocLUA_HTML.zip : UI_Clip.html

29.WebView & Movie Player

Windows platform does not support those. Only the devices.

As a result, please use the online documentation for those, there are no sample in this tutorial.
But their usage are quite simple anyway.

**See also**

- UI_MoviePlayer
  See document in archive DocLUA_HTML.zip : UI_MoviePlayer.html
- UI_WebView
  See document in archive DocLUA_HTML.zip : UI_WebView.html

# Features of Toboggan Tool

- Encryption support 
- Enable FileSystemWatching
- Publish Target
- Command line parameters for Windows client
- Setting up the plugins
- Clean    

**Note**
if you have a file locked message, try to see if you need to shutdown the client first

```
"Tools"->"Shutdown"
```

## Engine specific behaviour.

When assigning a text to a control, if the text starts with '#' character,
the characters following the '#' symbol are used as a key into the language dictionnary.
See the LangTest sample.
