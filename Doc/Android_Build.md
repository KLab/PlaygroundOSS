Windows Specific Install
========================

The easiest and fastest to build for Android is to use a Linux emulated machine.
Using a virtual PC will make the task quite easy.

If you have already a Linux virtual machine running you can skip this section.

1. First we will use VirtualBox, Windows version (select the version fitting your OS)
   https://www.virtualbox.org/wiki/Downloads
   
   Start Download VirtualBox.

2. We will use Ubuntu to do the build, so we download also Ubuntu at the same time.
   
   http://www.ubuntu.com/download

   Then select Ubuntu Desktop, and download your ISO file (12.04 recommended).
   
   We would advise to install everything in 64 bit version if your machine supports it.

   
3. Run the VirtualBox installer
   
   WARNING : VirtualBox may temporarly disrupt your network connection during install.
   If you are still downloading, wait all the files are downloaded.

   *Follow the classic wizard like installation.*

4. Launch VirtualBox
   - Click on the New button to create a new Virtual Machine.
   
   - Setup Name and type of OS you are installing.
   Type    -> Linux
   Version -> Ubuntu 
   Then click 'next'.

   - Let's create a memory size of 2GB, that should be enough. (
   Then click 'next'.

   - Create a virtual hard drive as asked.
   Then click 'next'.

   - Fixed Size hard disk is nicer for performance during build, but dynamic is OK.
   Do as you wish, just make sure you have space to create that disk.
   Then click 'next'.
   
   - Select the location and size of the virtual drive.
   Then click 'next'.

   Now the virtual PC setup is complete, now we will install Ubuntu on this virtual PC.

   Select your new virtual machine and click the "Settings" button
   Goto to Storage Tab, Add a CD/DVD (click on CD/DVD icon with +)
   Then select the ISO file of Ubuntu we have just downloaded.

   Make sure the boot order select the CD/DVD drive first (Under System / Motherboard)
   Close the setup and go back to the main window of VirtualBox.
   Select the virtual machine, run the PC.

   Now the PC will boot and install Ubuntu.
   Make sure the account you will use has the admin rights. (By default, it will work)
   
   You can also check that online tutorial :
   http://www.wikihow.com/Install-Ubuntu-on-VirtualBox


1. Tools install
=================

NDK
---

### For OSX
http://dl.google.com/android/ndk/android-ndk-r9-darwin-x86_64.tar.bz2

### For Ubuntu (for our virtual machine)

Run Ubuntu, launch firefox and goto the following URL :
http://developer.android.com/tools/sdk/ndk/index.html

Then download the Linux android x86 NDK
32 bit OR 64 bit based on your Virtual Box and hardware setup

**32 bit** : http://dl.google.com/android/ndk/android-ndk-r9-linux-x86.tar.bz2
**64 bit** : http://dl.google.com/android/ndk/android-ndk-r9-linux-x86_64.tar.bz2

Firefox ask you to use with Archive Manager to handle the archive, please use it.
Once the download is finished, select extract, the file explorer appears,
select "File system", then home/ and select your folder with your account. (ie home/myUserName)
  
SDK
---

### For OSX & Windows

http://developer.android.com/sdk/index.html

### For Windows: 

Download Android SDK development environment (ADT)
Select the bundle for your machine.

- 32 bit OR 64 bit based on your hardware
- 32 bit : http://dl.google.com/android/adt/adt-bundle-windows-x86-20130917.zip
- 64 bit : http://dl.google.com/android/adt/adt-bundle-windows-x86_64-20130917.zip

IMPORTANT NOTE : package include the date, so if you need to download a higher version, please take care of
modifiying the path accordingly to the packages you have downloaded.

### For OSX :

[Download Android SDK development environment](http://dl.google.com/android/adt/adt-bundle-mac-x86_64-20130917.zip
) (ADT)

**Put uncompressed files into /Applications/ directory ( /Applications/adt-bundle-mac-x86_64-20130917/ )**.

For OSX : launch a terminal	

- zsh is ```~/.zshrc```
- bash is ```~/.bashrc```

* NDK Setup

```
ANDROID_NDK_ROOT="/Applications/android-ndk-r9"
export ANDROID_NDK_ROOT
```

* SDK Setup

```
ANDROID_SDK_ROOT="/Applications/adt-bundle-mac-x86_64-20130917/sdk"
```

* Add to the PATH

```
PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/opt/local/bin:${ANDROID_NDK_ROOT}:${ANDROID_SDK_ROOT}/platform-tools"
```

### For Ubuntu
Run Ubuntu, search your computer for local ressource, type "text editor" and launch it.

- Go inside '/home/myUserName' with the file explorer, right click, select show hidden files in the popup menu.
- Select ```.bashrc```
- Add the following accordingly to YOUR ACCOUNT NAME :

```
export ANDROID_NDK_ROOT="/home/myUserName/android-ndk-r9"
```

then

```
export PATH="$PATH:${ANDROID_NDK_ROOT}"
```

- Then save the file.
We now need to mount the host windows folder owning the playground engine to be visible from Ubuntu.
From the virtual machine window :
- Select "Device" -> "Install Guest Additions"
- It will ask you to run the package, and then ask you your user password because root access right are necessary.
- Press return when finished, shell close.

    - Select "Device" -> "Shared Folder"
    - Select the "Add folder" icon and give a mount name and select the path on Windows. (ie Playground).
    - Make sure "Folder Name" is set to "Playground".
    - Then, turn "Auto-mount" option on.

    - Launch terminal :

    *(replace "myUserName" with your actual username on Ubuntu)*

    ```
    sudo usermod -aG vboxsf myUserName
    ```

    - Reboot Ubuntu.

2. Build Engine library (native module)
---------------------------------------

## For OS X:

Launch terminal :

```
> cd [PATH TO PROJECT BASE]/Engine/porting/Android/GameEngine-android/
> chmod +x ./build.py (note: First time only)
> ./build.py --rebuild --project SampleProject
```

(note: Maybe project name is 'SampleProject' only)

## For Ubuntu:

Launch terminal :

```
> cd /media/sf_Playground/Engine/porting/Android/GameEngine-android/
> chmod +x ./build.py (note: First time only)
> ./build.py --rebuild --project SampleProject
```

(note: Maybe project name is 'SampleProject' only)

3. Build package assets
------------------------
(Target assets should be compiled prior to packaging. Please refer Tools document for how)
For instance, we're packaging "SimpleItem" example here.
We assume you already have Tutorial/ inside Playground root directory, please continue
reading with replacing them if you have things in other location.

### Move to the samples directory

### For OS X:
Launch terminal :

```
> cd [PATH TO PROJECT BASE]/Tutorial/01.SimpleItem/.publish/android/
> zip -r -0 [PATH TO PROJECT BASE]/Engine/porting/Android/GameEngine-android/assets/AppAssets.zip ./*
> echo -n "1" > [PATH TO PROJECT BASE]/Engine/porting/Android/GameEngine-android/assets/version ./*
> md5 AppAssets.zip | cut -d " " -f 4 > [PATH TO PROJECT BASE]/Engine/porting/Android/GameEngine-android/assets/version ./*
```


### For Ubuntu:
Launch terminal :

```
> cd /media/sf_Playground/Tutorial/01.SimpleItem/.publish/android/
> zip -r -0 /media/sf_Playground/Engine/porting/Android/GameEngine-android/assets/AppAssets.zip ./*
> md5sum AppAssets.zip | cut -d " " -f 1 > [PATH TO PROJECT BASE]/Engine/porting/Android/GameEngine-android/assets/version ./*
```


4. Import Engine project into your ADT
--------------------------------------

a. Open ADT

b. Open File > Import Menu

c. Choose "Existing Android Code into Workspace" and press "Next"

d. Press "Browse" button and navigate to "GameEngine-android" directory on your filesystem

e. Press "OK" to close directory browser

f. Make sure a project named "GameEngine" is selected and press "Finish"

5. Build Android Package & Run on a device
------------------------------------------
a. Connect your Android device

b. Open ADT

c. Right click "GameEngine" project and navigate to "Run As > Android Application"

d. Choose your device if a dialog is prompted and press "OK". Skip this step if no dialog is prompted.

