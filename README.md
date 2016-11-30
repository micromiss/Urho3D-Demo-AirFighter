Introduction
=============
This is a multiplayer(LAN) 2d-shooting game demo built in *Urho3D*. *Urho3D* is a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license.

We made this demo for those who are interested in game and game engines since there are really few game demos made in lightweight game engines. 

*AirFighter* is a relatively complete demo with character control system, shooting system, networking system, BUFF system and skill system although we have only few instances of them.Anyone who is interested in updating these systems is welcome!

Because of the limit of all kinds of resources, *AirFighter* is just a demo without ,art design, sound design or level design. 

How To Play
===

##Before We Start

What you need to do is just run the **AirFighter.exe** in the path /AirFighter/bin/.We do recommend you to directly run the **AirFighter.exe** in its own path to avoid unnecessary troubles.
After you ran the **AirFighter.exe** a new window will pop up and you will found those buttons at the bottom of the window.
![Buttons](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Buttons.png?raw=true)

**SinglePlayer:** Start a singleplayer game in which there is just a game scene with a demo box and a fighter for you ahahaㄟ(▔▽▔)ㄏ

**Connect:**Join a multiplayer game as a client.To join a LAN game, you should input your username and ip address like this "username:ip"(e.g."Alex:192.168.150.132") in the LineEdit then click *Connect* 
Sometimes the connection may fail in the first time. But don't worry! What you need to do is just clicking,waiting...failed! clicking,waiting...failed! click,waiting...success!!!(´・ω・)ﾉ

**Disconnect:** It seems that we haven't realize the function of the button?┑(￣▽ ￣)┍ 

**Start Server:** Start a multiplayer game as a host. Certainly you will also get a fighter for you.

##Singleplayer Game
When you click the *SinglePlayer* button a single player game will start. The fighter for you is standing by!
![SinglePlayer](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Singleplayer.png?raw=true)

But the only thing you can do is to shoot and to destory the demo box pupupu(which showed in the image below) ￣ω￣! Also you can try all of your skills in singleplayer game although these haven't had any effect(￢_￢). You can move your fighter with arrow keys in your keyboard and fire by pushing space. **PAYATTENTION** that you should click in the game scene just once right after you start a game to divert the focus of your operations to the game scene from the buttons.
![SinglePlayer_boom](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Singleplayer_boom.png?raw=true)

##Multiplayer Game
We found that there is really few examples of multiplayer games in the forum of *Urho3D*. The official large example *NinjaSnowWar* is a simple 3d-game without skill systems which coded in *AS(angelscript)*. So we built this demo in pure C++ (JUST pure C++, NOT pure C!(¬､¬)).

When you click the button *Start Server*, a multiplayer game will start and you will join the game as the host which called "migu"(my NickName ahaha). You can move your fighter by the arrow keys and fire by pushing space.

After you run a server, find another PC and connect the server(What? How to connect? I've just told you before!).For example that you called Alex and the ip of the server is 192.168.150.132 then input "Alex:192.168.150.132" in the LineEdit and click *Connect*!
![Multiplayer](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Multiplayer.png?raw=true)

When a multiplayer game started, all you should do is to kill others with your bullets and skills. Why we do not have scoreboard or any gameplay instructions? Cause that *AirFighter* is just a game example for developers, not for players!(;￢д￢)

Actually we do have a lot of bugs in our multiplayer game system. Everything goes well in the server yet something always goes wrong in the clients. We will try to fix all of this bugs if only we have time＋﹏＋.We submitted these bugs in the *Issue* section. Anyone who is interested in fixing these bugs will be welcome!!!!๑乛◡乛๑

##Controls
Arrow Keys: 
UP: Acceleration
DOWN: Deceleration
LEFT: Turn left
RIGHT: Turn right
SPACE: Fire

##Skills
We have made three classic skills in *AirFighter*: *Missile*, *Flare* and *Blink*. All of these skills has its built-in cooldown though you cannot see it cause we haven't made the GUI. These skills are separately bound to the key Q, W and E in the keyboard. YES! WE DO NOT HAVE A ULT! WE DO NOT SET R SKILL!(づ￣ 3￣)づ

Missile(KEY Q): Your fighter will launch a missile which will track any one who has a BUFF *heatsource* except yourself and the missile will boom when it hit the target. A missile has a initial velocity when it is launched. Pay attention that the missile can be tracked by more than one target at a time and it will boom when it hit any of then.
![Missile](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Missile.png?raw=true)



Flare(KEY W): Your fighter will emit some flares to interface the tracking of the missiles. The effect of this skill will last a few seconds and go into cooldown at the same time .
![Flare](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Flare.png?raw=true)


Blink(KEY E): Your fighter will be transported forward for short distance.Then the skill will go into cooldown. It improves the fighter's initiation range and escape ability. 
![Blink](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Blink.png?raw=true)



How To Build
====

We strongly recommend you to build your own project with our .h, .cpp and resources rather than to build the project you clone from our repository. Otherwise your project will not be built successfully because of all kinds of environment problems.

Since official doc *Using Urho3D as external library*(https://urho3d.github.io/documentation/1.6/_using_library.html) of *Urho3D* doesn't tell us how to build our own project quite clearly. We will teach you to build your own project by our resources hand-by-hand. 

First you should get Urho3D from https://urho3d.github.io/. Then build the sample project by cmake. You can find the tutorials here (https://urho3d.github.io/documentation/1.6/_building.html). We strongly recommend you to use cmake-gui if you are using windows like us. 

For convenience narration, we call the directory of the Urho3D you downloaded **directory_origin** and the sample project you built **directory_build**. The directory of your own project is called **directory_own**.
e.g.:
**directory_origin**: 'E:/Urho3D'
**directory_build**: 'E:/Urho3D-build'
**directory_own**: 'E:/AirFighter'

Here is a simple way to build our project if you are new to Urho3D. Just choose one of the sample project(e.g. '01_HelloWorld') then replace all of the .h and .cpp in it to our .h and .cpp. Finally copy the resouces in the path '\bin\Data\Urho2D' of our project to the same path of **directory_build**. Certainly this way is not recommended if you are building your own project rather than learning our project.

To build your own project(Using Urho3D as external library), here is the official tutorials(https://urho3d.github.io/documentation/1.6/_using_library.html). There is no need for you to read the part below if you are familiar with it.

First of all, structure your project(**directory_own**) similar to Urho3D project as below.
    <PROJECT_ROOT>(directory_own)/
     ├ bin/
     │  ├ Data/
     │  └ CoreData/
     ├ CMake/
     │  ├ Modules/
     │  └ Toolchains/
     ├ CMakeLists.txt
     ├ *.cpp and *.h
     └ *.bat or *.sh
The point is, how to structure it? Now we create a folder called *AirFighter* as our **directory_own**. Copy the directory *bin* and *CMake* in **directory_origin** to **directory_own**. Then create an empty *CMakeLists.txt* in **directory_own**.

Edit the *CMakeLists.txt* like this:

    # Set CMake minimum version and CMake policy required by Urho3D-CMake-common module
    if (WIN32)
        cmake_minimum_required (VERSION 3.2.3)      # Going forward all platforms will use this as minimum version
    else ()
        cmake_minimum_required (VERSION 2.8.6)
    endif ()
    if (COMMAND cmake_policy)
        cmake_policy (SET CMP0003 NEW)
        if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
            # INTERFACE_LINK_LIBRARIES defines the link interface
            cmake_policy (SET CMP0022 NEW)
        endif ()
        if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
            # Disallow use of the LOCATION target property - so we set to OLD as we still need it
            cmake_policy (SET CMP0026 OLD)
            # MACOSX_RPATH is enabled by default
            cmake_policy (SET CMP0042 NEW)
        endif ()
    endif ()
    # Set project name
    project (AirFighter)
    # Set CMake modules search path
    set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
    # Set the Urho3d_home enviroment
    set (ENV{URHO3D_HOME} E:/!Package/Urho3D-Build)
    # Include Urho3D Cmake common module
    include (Urho3D-CMake-common)
    # Define target name
    set (TARGET_NAME AirFighter)
    # Define source files
    define_source_files ()
    # Setup target with resource copying
    setup_main_executable ()

**PAY ATTENTION** to change 'E:/!Package/Urho3D-Build' to your **directory_build**(This sample project should be built by yourself after it was generated by Cmake).

After that you need to copy all of our .h and .cpp to your **directory_own**(root directory) and copy our resources in '/bin/Data/Urho2D' to your '**directory_own**/bin/Data/Urho2D'. Now your project has been structured!!(。◕‿◕。)ノ

Now use your cmake to make the project! If you are using cmake-gui as we recommended, you can set it like this:
![Cmake-gui](https://github.com/micromiss/Urho3D-Demo-AirFighter/blob/master/Pic/Cmake_gui.png?raw=true)



**PAY ATTENTION** to change the path 'D:/Project/Urho3D/AirFighter' to your **directory_own**.

Finally, Configure and Generate!↖(▔▽▔)↗ 

If you have any problems with your project building. Please contact us via *microface87@gmail.com*.



Project Structure Introduction
===

##Overview

As mentioned above, still we have lots of bugs in our project. So we do welcome you to solve these problems with us. Although we have detailed program annotation in our project, we still want to make a introduction to our project structure for your quick start. 

First of all, the structure of our project is like this:
    <PROJECT_ROOT>/
     ├ BUFF/
     │ Bullets/
     │ Effects/
     ├ GameObjects/
     │ Lists/
     │ Skills/
     ├ AirFighter.h
     ├ AirFighter.cpp
     └ Toolkit.h

**BUFF**: We have only one buff *HeatSource* in our game demo. BUFF can be set to a gameobject directly as a logic component.

**Bullets**: Special object can be created by the *Fire* operation of fighters. We have only one bullet instance *AP(armor-piercing projectile)* which will move forward once it has been created and will damage the first gameobject it impacted.

**Effects**: Most are just visual effects. But some of them has game logic effects such as *Effect_Boom*.

**GameObjects**: As the name indicates, game objects.

**Lists**: All kinds of lists like BUFFs, Controls and RemoteEvents.

**Skills**: As the name indicates, skills.
Skils can be added in our project like this:
    Skill_Blink* skillBlink = node->CreateComponent<Skill_Blink>();
    skillBlink->SetTriggerKey(CTRL_E);
CTRL_E is a macro defined in ControlList.h. Surely you can define your own controls macro but remember to set them to 2^n cause they are operated through binary in Urho3D. Each bit represents a key/operation.


**AirFighter.h .cpp**: Main files.

**Toolkit.h**: Some support functions such as *print* and *StringOperation*.

##Networking System
The basic idea is that all of the gameobjects are created by server and then replicate to the clients. All the calculation are completed on server and then effect the clients. The operations of clients are sent to server by the Urho3D built-in class *controls*. Server will analyze all of these operations requests then apply them to their corresponding gameobjects.

The following sections just make a simple introduction to our networking system. To get a better understand of it you may read the program annotation in our project. (≡ω≡．)
###Server
When server started, it will create a game scene and a fighter for the server player. Then it will wait for others' connection requests. When anyone who connected to server successfully, the server will wait for its identity. When the identity is received and confirmed, a fighter and a camera will be spawned to the newcomer by the function *SpawnPlayer(Connection\* connection)*. After that server will send a remote event(RE_PLAYERSPAWNED) to the client. Server will receive the operations requests from all of the clients and apply them to corresponding gameobjects each fixed frame.

###Clients:
Each client will create a empty scene before game start. When it connects to a server it will try to get scene replication from server. When it get the scene replication it will be waiting for the RE_PLAYERSPAWNED signal. When it received this remote event it will found its own camera allocated by server and create a viewport through it. Each client will catch the user's operations(which has been registered) and send them to server every fixed frame.

##Shooting System

We build the shooting system based on the built-in 2d-physics system in Urho3D which call Box2D (You can get it from https://github.com/erincatto/Box2D).

The shooting system is quite simple that all of the gameobjects has a attribute called hp. And each gameobject has a *damaged(float)* function if it is not invincible. Bullets will trigger the *damaged* function of the gameobject which it firstly impacted. Missiles will trigger the *damaged* function of any gameobjects who enter its *boom range*.

When a gameobject's hp is reduced to 0 it will be removed from the scene.




Words in the End
===
Although there are still lots of bugs in our project(We submitted them in the Issue section). We hope that our project can be a learning example for those who are interested in games and game engines.

Again, we will really appreciate your help if you are interested in fixing these bugs. You can contact us via **microface87@gmail.com** .

Build games,better,together.

THANKS!







 





