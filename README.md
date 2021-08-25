[![license](https://www.gnu.org/graphics/gplv3-or-later.png)](https://www.gnu.org/licenses/gpl-3.0.en.html)
<pre>
I've decided to make this repository public so that more developers can help me improving it.
For now it had implemented all features that FA2Ext has and extended more logics than it.
The codes might be a messy, so I'd appreciate it if someone could help me to make them better arranged.

SDK: Visual Studio 2017 - Windows XP (v141_xp)
Compile Using C++ Standard Now: C++14

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~////////// FINALALERT2 - SP CHANGELOG //////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

======================= Changes (2021-08-25 RELEASE 1.0.5) ==============================================================================================
+) Enhanced SaveMap logic by Loritas
+) New ExtConfig: SaveMap.OnlySaveMAP, enable it so that FA2 will only save map with .map file extension
*) Now VXL drawing lib no longer requires DirectX 9 anymore
*) Reimplemented Building & Basenode outline rendering, also Celltags, Waypoints and Tubes rendering
*) Significantly reduce the lag of Building & Celltag & Waypoint & Tube rendering

======================= Changes (2021-08-20 RELEASE 1.0.4) ==============================================================================================
+) Now you can copy AITriggers
+) New ExtConfig: SaveMap = BOOLEAN, enable it so that we will replace FA2's vanilla slow saving function
    +) New ExtConfig: SaveMap.AutoSave = BOOLEAN, enable it so that we will enable FA2 to save map automatically after one save
        +) New ExtConfig: SaveMap.AutoSave.Interval = INTEGER, set the interval between two auto saving, need to be greater than or equal to than 30
        +) New ExtConfig: SaveMap.AutoSave.MaxCount = INTEGER, how many auto saving files can FA2 keep, set to -1 will disable the auto cleanning up

======================= Changes (2021-08-19 RELEASE 1.0.3) ==============================================================================================
*) Now we read file without extracting them to the game folder, this might fix some reading bugs
*) The ObjectBrowserView will show player locations again in Multiplayer maps (with Basic -> MultiplayerOnly=yes)
-) Easy mode is disabled, and it won't be displayed in menu either anymore

======================= Changes (2021-08-18 RELEASE 1.0.2) ==============================================================================================
+) Now Allie Editor receive double click command for listboxes
*) Fixed the bug that TransportWP was not correctly copied
*) ScriptTypes and VXLDrawing will no longer cause memory leak

======================= Changes (2021-08-14 RELEASE 1.0.1) ==============================================================================================
*) Now Unit&Aircraft&Infantry dialog will show up at the center of the screen
*) Fixed the bug that delete script do not delete the key in [ScriptTypes]
*) Fixed the bug that copy team do not really clone "Droppod" key

======================= Changes (2021-08-13 RELEASE 1.0.0) ==============================================================================================
*) Minor adjustments on ObjectBrowserControl
+) Replace the exception handler, now you can save a dmp file when FA2 crashes
*) Fix the bug that some building cannot be drawn correctly

======================= Changes (2021-08-11) ==============================================================================================
*) VXL Units' TurretOffset and Buildings' VXL turrets should be drawn at correct place
+) New ignore keys: IgnoreIdleAnim and IgnoreActiveAnimX
+) New drawing config: VehicleVoxelBarrelsRA2
*) IgnoreSuperAnimX will be read correctly now
+) Import AllieEditor for CHouses from FA2Copy
*) Adjustments on several dialogs
*) Now you can run multiple FA2sp at the same time

======================= Changes (2021-08-07B) ==============================================================================================
*) Fixed the bug for PowerUpLocs

======================= Changes (2021-08-07) ==============================================================================================
*) The drawing function is fixed for several items
*) The Isoview now will be redrawn automatically after layers are set
+) New tags in falanguage so you can translate menu items

======================= Changes (2021-08-06) ==============================================================================================
+) New param code: 30 for float, this param code can be used for action 71 & 72
+) New menu checkboxes: Layers, you can hide Strutures, Infantries and so on through this system
*) The drawing function for Structures, Infantries, Vehicles, Terrains, Smudges and Aircrafts have been completely rewritten

======================= Changes (2021-08-02) ==============================================================================================
*) Fixed fatal error on STDHelper::SplitString caused bugs on Clone Actions/Events and ExtConfig::SortByTriggerName

======================= Changes (2021-07-31) ==============================================================================================
*) Fixed wrongly painted infantry subcell place
*) Undo/Redo limit is now controlled by ExtConfig: UndoRedoLimit = INTEGER, defaults to 16
+) New ExtConfig: UseRGBHouseColor
+) Now you can copy single action/event in trigger editor
+) Now you can copy taskforce and its member

======================= Changes (2021-07-19) ==============================================================================================
*) Undo/Redo extended to 2147483647 steps, be careful about your memory
*) Fixed wrongly painted Remap color for technos using UNITXXX.PAL
*) Fixed buildings with shp turret can only been painted to NORTH
*) Refactored ScriptTypes window, now you can use MoveUp, MoveDown, InsertMode and Clones

======================= Changes (2021-06-11) ==============================================================================================
+) New ExtConfig: ExtWaypoints = BOOLEAN, enable it to support no limitation of waypoints, defaults to false (Phobos required)
+) New ExtConfig: Waypoint.Background = BOOLEAN, enable it to draw a background rectangle for waypoints, defaults to false
    +) New ExtConfig: Waypoint.Background.Color = COLORREF, custom the waypoint background color
+) New ExtConfig: Waypoint.Color = COLORREF, custom the waypoint text color
+) New ExtConfig: CopySelectionBound.Color = COLORREF, custom the copy selection bound color, defaults to 255,0,0
+) New ExtConfig: CursorSelectionBound.Color = COLORREF, same as the above one, defaults to 60,160,60
+) New ExtConfig: CursorSelectionBound.HeightIndicatorColor = COLORREF, same as the above one, defaults to 60,60,60

======================= Changes (2021-05-07) ==============================================================================================
+) New ExtConfig: SortByTriggerName = BOOLEAN, enable it so FA2 will sort the triggers dropdown and sort them by their name instead of ID
+) New ExtConfig: AdjustDropdownWidth = BOOLEAN, enable it so FA2 will adjust the param dropdown width automatically
    +) New ExtConfig: AdjustDropdownWidth.Factor = INTERGER, determines how long is a single char takes, defaults to 8
    +) New ExtConfig: AdjustDropdownWidth.Max = INTERGER, determines the max length of the combobox, defaults to 360
-) Remove ExtConfig: OverlayFilter, enable it always.

======================= Changes (2021-03-22) ==============================================================================================
*) Now you can force to use Name first instead of UIName in the ObjectBrowserControl under [ForceName] just like [IgnoreRA2]
*) More accelerators and fixes from E1Elite

======================= Changes (2021-03-05) ==============================================================================================
*) Now the game directory FA2 reads would use the path in FinalAlert.ini instead of the one in registry
*) Coordinates are now shown as X / Y - H
*) Undo/Redo extended to 127 steps (was 15 steps)
*) ObjectBrowserControl refactored
    +) Not only Buildings, but Infantrys, Aircrafts and Vehicles now have been classified into sides
    +) Not only the original hardcoded overlays but also all overlays having Wall=yes will be auto connected
*) Now infantry's facing will be correctly shown
*) Overlay which has the index bigger than 255 will be ignored
*) Teamtypes and Scripttypes are now able to use Clone just as Triggers
*) House colors will be correctly drawn instead of using a hardcoded set of colors (for most, yellow)
*) For most dialogs, the content will only be updated while lose focus. (Used to be content changed, and lead to famous stupid lag teamtype) 
*) Several dialogs UI Redrawn
+) Support Ares' += and #include functions (not recommended to use, still has several bugs)
+) Support Ares' stringtableXX.csf
+) ScriptTypes now use a different set of params and can be extended
+) Mix Extension and INI Filenames can be customed
+) Ctrl+S, Ctrl+O, Ctrl+N and Ctrl+Shift+S are now supported
+) Easy encrypted mix files will be correctly read
+) Tile manager, can be helpful while you are having lots of tiles

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~////////// FINALALERT2 - SP  DOCUMENT //////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

- GETTING START
Just like Ares, FA2sp needs Syringe to work properly, so you can just take Ares as a reference.

What you need to know is that FA2sp requires Original FinalAlert 2 1.02 version, any modified version may occur unexpected errors!
Before you launch it for the first time, write the ini files below properly, especially for essential ones (marked by **)

If you still have any problem about it or something wrong occured while using it, please contact me directly or mail me at 3179369262@qq.com
For now, I cannot ensure the stability of it, so save your maps frequently before heavy loss! XD

- BASIC TYPES
INTERGER - [-2147483648,2147483647]
BOOLEAN - Yes/No ; True/False ; 1/0
COLORREF - R,G,B each of them is in [0,255]

- BEFORE LAUNCHING IT
    - FAData.ini
        +) [ExtConfigs] (All switches defaults to false)
            +) BrowserRedraw=BOOLEAN ; Enable refactored ObjectBrowserView
                +) BrowserRedraw.GuessMode=0/1 ; Determines how FA2sp guess Technos' side, 0(Default) to Prerequisite, 1 to use first Owner 
                +) BrowserRedraw.CleanUp=BOOLEAN ; Sides classification will clear empty items
            +) AllowIncludes=BOOLEAN ; Read #include section for other ini (NOT RECOMMENDED) 
            +) AllowPlusEqual=BOOLEAN ; Read += (NOT RECOMMENDED)
            +) Stringtables=BOOLEAN ; Read stringtableXX.csf
                +) TutorialTexts.Fix=BOOLEAN ; Replace original process while loading texts to comboboxes
            +) TutorialTexts.Hide=BOOLEAN ; Reduce lags, for texts in combobox might be useless
            +) SortByTriggerName=BOOLEAN ; Enable this feature so we can sort the triggers by their names
            +) AdjustDropdownWidth = BOOLEAN ; Enable it so FA2 will adjust the param dropdown width automatically
                +) AdjustDropdownWidth.Factor = INTERGER ; Determines how long is a single char takes, defaults to 8
                +) AdjustDropdownWidth.Max = INTERGER ; Determines the max length of the combobox, defaults to 360
            +) CopySelectionBound.Color = COLORREF ; Determines the color of the selection boundary while copying, defaults to 255,0,0
            +) CursorSelectionBound.Color = COLORREF ; Determines the color of the boundary for current cell, defaults to 60,160,60
            +) HeightIndicatorColor.Color = COLORREF ; Determines the color of the height indicator for current cell, defaults to 60,60,60
            +) Waypoint.Color = COLORREF ; Determines the color of waypoint texts, default to 0,0,255
            +) Waypoint.Background = BOOLEAN ; Determines whether draw a rectangle background for waypoints or not. defaults to false
                +) Waypoint.Background.Color = COLORREF ; Determines the color of the waypoint background, defaults to 255,255,255
            +) ExtWaypoints = BOOLEAN ; Determines if FA2sp supports unlimited count of waypoints, defaults to false (Phobos required)
            +) UndoRedoLimit = INTEGER ; Determines the maximun step of undo/redo, defaults to 16
            +) UseRGBHouseColor = BOOLEAN ; Determines if House colors are recognized as RGB color instead of HSV, defaults to false 
            +) SaveMap = BOOLEAN ; Determines if FA2 will save map using a faster method
                +) SaveMap.AutoSave = BOOLEAN ; Determines if FA2 will save map automatically after one manually saving
                    +) SaveMap.AutoSave.Interval = INTERGER ; Should be greater than or equal to 30, defaults to 300, determines how many seconds should we wait during the two auto saving
                    +) SaveMap.AutoSave.MaxCount = INTERGER ; How many saving should FA2 keep, set to -1 will disable the auto cleanning, defaults to 10
            +) SaveMap.OnlySaveMAP = BOOLEAN ; Determines if FA2 will only save map with .map file extension
        +) [Sides] ** (** means Essensial, fa2sp need this section to work properly)
            {Contains a list of sides registered in rules}
            \\\ e.g.
            \\\ [Sides]
            \\\ 0=Allied
            \\\ 1=Soviet
            \\\ 2=Yuri
            \\\ 3=Neutral
            \\\ 4=Special
            \\\
        +) [ForceName]
            (xxx = Objecttype)
            {Contains a list of objecttypes forced to use Name instead of UIName}
            \\\ e.g.
            \\\ [ForceName]
            \\\ 0=E1
            \\\
        +) [ForceSides]
            (Technotype = SideIndex)
            {Contains a list of technotypes whose side cannot be correctly guessed}
            \\\ e.g.
            \\\ [ForceSides]
            \\\ ENGINEER=0
            \\\ SENGINEER=1
            \\\ YENGINEER=2
            \\\ {A LOT OF WESTWOOD CIVILIAN VEHICLES WITH PREREQUISITE [NAWEAP] WILL BE GUESSED INTO SOVIETS, FIX THEM MANUALLY}
            \\\
        +) [Filenames]
            +) EVA = FILENAME
            +) EVAYR = FILENAME
            +) Sound = FILENAME
            +) SoundYR = FILENAME
            +) Theme = FILENAME
            +) ThemeYR = FILENAME
            +) AI = FILENAME
            +) AIYR = FILENAME
            +) RulesYR = FILENAME
            +) Rules = FILENAME
            +) ArtYR = FILENAME
            +) Art = FILENAME
            +) TemperateYR = FILENAME
            +) Temperate = FILENAME
            +) SnowYR = FILENAME
            +) Snow = FILENAME
            +) UrbanYR = FILENAME
            +) Urban = FILENAME
            +) UrbanNYR = FILENAME
            +) LunarYR = FILENAME
            +) DesertYR = FILENAME
            +) MixExtension = FILENAME SUFFIX
            \\\ e.g.
            \\\ EVAYR=evamp.ini
            \\\ SoundYR=soundmp.ini
            \\\ ThemeYR=thememp.ini
            \\\ AIYR=aimp.ini
            \\\ RulesYR=rulesmp.ini
            \\\ ArtYR=artmp.ini
            \\\ TemperateYR=temperatmp.ini
            \\\ SnowYR=snowmp.ini
            \\\ UrbanYR=urbanmp.ini
            \\\ UrbanNYR=urbannmp.ini
            \\\ LunarYR=lunarmp.ini
            \\\ DesertYR=desertmp.ini
            \\\ MixExtension=mp
            \\\ 
        +) [ScriptParams] **
            {Contains a list of param types used for scripts}
            \\\ NOTICE THAT OUR SCRIPT PARAMS ARE INDEPENDENT
            \\\ HERE IS THE LIST:
            \\\ 
            \\\ (LIST BEGIN)
            \\\ 0-Nothing
            \\\ 1-Target
            \\\ 2-Waypoint
            \\\ 3-ScriptLine
            \\\ 4-SplitGroup
            \\\ 5-GlobalVariable
            \\\ 6-ScriptTypes
            \\\ 7-TeamTypes
            \\\ 8-Houses
            \\\ 9-Speeches
            \\\ 10-Sounds
            \\\ 11=Movies 
            \\\ 12=Themes 
            \\\ 13=Countries 
            \\\ 14=LocalVariables
            \\\ 15=Facing
            \\\ 16=BuildingTypes 
            \\\ 17=Animations
            \\\ 18=TalkBubbles
            \\\ 19=Status
            \\\ 20=Boolean
            \\\ (LIST END)
            \\\
            \\\ Or just copy the section below:
            \\\ [ScriptParams]
            \\\ 0=Nothing,0
            \\\ 1=Target,1
            \\\ 2=Waypoint,2
            \\\ 3=Jump To Line #,3
            \\\ 4=Split Group,4
            \\\ 5=Global,5
            \\\ 6=Script,6
            \\\ 7=Team,7
            \\\ 8=House,8
            \\\ 9=Speech,9
            \\\ 10=Sound,10
            \\\ 11=Movie,11
            \\\ 12=Theme,12
            \\\ 13=Country,13
            \\\ 14=Local,14
            \\\ 15=Facing,15
            \\\ 16=Building,16
            \\\ 17=Animation,17
            \\\ 18=Talk Bubble,18
            \\\ 19=Enter Status,19
            \\\ 20=Interger,0
            \\\ 21=Boolean,20
            \\\ 
        +) [ScriptsRA2] **
            (index = name, param, invisible, has param, description)
            {Contains a list of script types used for scripts}
            \\\ e.g. (by caco)
            \\\ [ScriptsRA2]
            \\\ 0=0 - Attack,1,0,1,Attack some general TARGET.
            \\\ 1=1 - Attack WP,2,0,1,Attack specified WAYPOINT (or THINGS on it).
            \\\ 2=2 - Go Berserk,0,1,0,Cyborgs go berserk (--Obsolete--)
            \\\ 3=3 - Move to WP,2,0,1,Move to WAYPOINT.
            \\\ 4=4 - Move to Cell,20,0,1,Move to specified CELL (formula to result: x+y*128).
            \\\ 5=5 - Guard in Sec,20,0,1,Do AREA GUARD for SECOND(S) defined by argument.
            \\\ 6=6 - Jump to Line #,3,0,1,Jump to specified LINE with scripts above done.
            \\\ 7=7 - Player Win,0,0,0,Force player to WIN.
            \\\ 8=8 - Unload,4,0,1,Kick ALL passengers. Use argument to set which type(s) should CONTINUE the script.
            \\\ 9=9 - Deploy,0,0,0,Deploy all deployable units.
            \\\ 10=10 - Follow friendlies,0,0,0,Follow the NEAREST friendly units.
            \\\ 11=11 - Do this,19,0,1,Cause the team to DO specified MISSION.
            \\\ 12=12 - Set Global var,5,0,1,Set a GLOBAL variable (1/On).
            \\\ 13=13 - Idle,0,0,0,Infantries in this team PLAY IDLE ANIMS.
            \\\ 14=14 - Load onto Transport,0,0,0,Let all units enter the transportation IF POSSIBLE.
            \\\ 15=15 - Spy into,0,1,0,(--Obsolete--)
            \\\ 16=16 - Patrol to WP,2,0,1,Patrol (Attack-Move) to WAYPOINT.
            \\\ 17=17 - Change Script,6,0,1,Change SCRIPT the taskforce used. 
            \\\ 18=18 - Change Team,7,0,1,Change TEAM the taskforce belong to. 
            \\\ 19=19 - Panic,0,0,0,Causes all units in the team to panic. (Usually for civilian use)
            \\\ 20=20 - Change Owner,13,0,1,Specified COUNTRY will own the whole team.
            \\\ 21=21 - Scatter,0,0,0,Scatter all units.
            \\\ 22=22 - Escape to Shroud,0,0,0,Cause all units escape to SHROUD.
            \\\ 23=23 - Player Lose,0,0,0,Force player to LOSE.
            \\\ 24=24 - Play EVA Speech,9,0,1,Play specified SPEECH.
            \\\ 25=25 - Play Sound,10,0,1,Play specified SOUND.
            \\\ 26=26 - Play Movie,11,0,1,Play specified MOVIE (on radar screen).
            \\\ 27=27 - Play Theme,12,0,1,Play specified THEME.
            \\\ 28=28 - Reduce Ore,0,0,0,Reduce the value of ORE AROUND TEAM MEMBERS.
            \\\ 29=29 - Begin Production,0,0,0,Cause the OWNER OF THIS TEAM produce (as planned).
            \\\ 30=30 - Sell 'n' Hunt,0,0,0,Cause AI SELL their buildings and HUNT their enemies.
            \\\ 31=31 - Self Destroy,0,0,0,Destroy the team ITSELF.
            \\\ 32=32 - Start Storm in Sec,20,0,1,Begin the Lightning Storm after specified SECOND(S).
            \\\ 33=33 - End Storm,0,0,0,End up the CURRENT Lightning Storm.
            \\\ 34=34 - Center focus on this team,20,0,1,Center focus on this team with specified MOVE SPEED.
            \\\ 35=35 - Reshroud Map,0,0,0,Reshroud current map.
            \\\ 36=36 - Reveal Map,0,0,0,Reveal ALL terrain of current map.
            \\\ 37=37 - Delete Team,0,0,0,Delete ALL members of this team.
            \\\ 38=38 - Clear Global Var,5,0,1,Clear specified GLOBAL var (0/Off).
            \\\ 39=39 - Set Local Var,14,0,1,Set specified LOCAL var (1/On).
            \\\ 40=40 - Clear Local Var,14,0,1,Clear specified LOCAL var (0/Off).
            \\\ 41=41 - Unpanic,0,0,0,Calm down all units in this team.
            \\\ 42=42 - Force Facing,15,0,1,Turn all units in this team to a specified direction.
            \\\ 43=43 - Wait till full,0,0,0,Wait until all passengers loaded.
            \\\ 44=44 - Truck unload,0,0,0,UNLOAD the goods as all trucks go empty.
            \\\ 45=45 - Truck load,0,0,0,LOAD the goods as all trucks go full.
            \\\ 46=46 - Attack enemy buildings,16,0,1,Attack specified BUILDINGS. (+0: MIN threat +65536: MAX threat +131072: nearest, +262144: furthest).
            \\\ 47=47 - Move to enemy buildings,16,0,1,Move to specified BUILDINGS. (+0: MIN threat +65536: MAX threat +131072: nearest, +262144: furthest).
            \\\ 48=48 - Scout,0,0,0,The team would scout the shroud area.
            \\\ 49=49 - Success,0,0,0,Put up the weight of AI trigger attached.
            \\\ 50=50 - Flash for frames,20,0,1,Flash this team for a number of FRAMES.
            \\\ 51=51 - Play Animation,17,0,1,Play specified anim on each unit.
            \\\ 52=52 - Talk bubble,18,0,1,Show a talk bubble on the FIRST UNIT of this team.
            \\\ 53=53 - Gather outside enemy,20,0,1,Gather outside the enemy's base. Arguments with positive or negative could affect the global distance since Ares 2.0.
            \\\ 54=54 - Gather outside team,20,0,1,Gather outside the team's base. Arguments with positive or negative could affect the global distance since Ares 2.0.
            \\\ 55=55 - Ask for SW,20,0,1,AI would queue a SuperWeapon for this team. Arguments decide which group of SW since Ares 2.0 (SW.Group).
            \\\ 56=56 - Chronoshift to Building,16,0,1,Chronoshift the team to specified buildings if possible. Need EXTRA orders however.
            \\\ 57=57 - Chronoshift to Target,1,0,1,Chronoshift the team to specified type if possible. Need EXTRA orders however.
            \\\ ;YR Only
            \\\ 58=58 - Move to friendlies buildings,16,0,1,Move to friendlies BUILDINGS. (+0: MIN threat +65536: MAX threat +131072: nearest, +262144: furthest).
            \\\ 59=59 - Attack (or Garrison) buildings on WP,2,0,1,Attack the building on specified WP. AI would usually try to GARRISON if possible.
            \\\ 60=60 - Enter Grinder,0,0,0,Get the team into nearest grinder.
            \\\ 61=61 - Enter Tank Bunker,0,0,0,Get EACH unit in the team into nearest tank bunker.
            \\\ 62=62 - Enter Bio Reactor,0,0,0,Get EACH infantry in the team into nearest bio reactor.
            \\\ 63=63 - Enter Battle Bunker,0,0,0,Get EACH infantry in the team into nearest battle bunker (if possible).
            \\\ 64=64 - Enter Neutral Buildings,0,0,0,Get EACH infantry in the team into nearest civilian buildings (if possible).
            \\\ ;Ares 3.0 Only
            \\\ 65=65 - Auxiliary Power (Ares 3.0 Only),20,0,1,Permanently changes the power output of the house owning the team.
            \\\ 66=66 - Kill Drivers (Ares 3.0 Only),0,0,0,Kills ALL drivers of the units in this team.
            \\\ 67=67 - Take Vehicles (Ares 3.0 Only),0,0,0,All CanDrive or VehicleThief infantry in this team will be assigned the closest vehicle they can drive or hijack.
            \\\ 68=68 - Convert Type (Ares 3.0 Only),0,0,0,Immediately changes all members of this team into their respective script conversion types (Convert.Script).
            \\\ 69=69 - Sonar Reveal (Ares 3.0 Only),20,0,1,Disables the ability of all team members to cloak themselves for a number of FRAMES.
            \\\ 70=70 - Disable Weapons (Ares 3.0 Only),20,0,1,Disables the ability of all team members to fire for a number of FRAMES.
        +) [VehicleVoxelBarrelsRA2]
    - FALanguage.ini
        *)  [CURRENTLANGUAGE-StringsRA2]
            [CURRENTLANGUAGE-Strings]
            [CURRENTLANGUAGE-TranslationsRA2]
            [CURRENTLANGUAGE-Translations]
                +) Menu.File = TEXT
                +) Menu.File.New = TEXT
                +) Menu.File.Open = TEXT
                +) Menu.File.Save = TEXT
                +) Menu.File.SaveAs = TEXT
                +) Menu.File.CheckMap = TEXT
                +) Menu.File.RunGame = TEXT
                +) Menu.File.Quit = TEXT
                +) Menu.Edit = TEXT
                +) Menu.Edit.Undo = TEXT
                +) Menu.Edit.Redo = TEXT
                +) Menu.Edit.Copy = TEXT
                +) Menu.Edit.CopyWholeMap = TEXT
                +) Menu.Edit.Paste = TEXT
                +) Menu.Edit.PasteCentered = TEXT
                +) Menu.Edit.Map = TEXT
                +) Menu.Edit.Basic = TEXT
                +) Menu.Edit.SpecialFlags = TEXT
                +) Menu.Edit.Lighting = TEXT
                +) Menu.Edit.Houses = TEXT
                +) Menu.Edit.TriggerEditor = TEXT
                +) Menu.Edit.TagEditor = TEXT
                +) Menu.Edit.Taskforces = TEXT
                +) Menu.Edit.Scripts = TEXT
                +) Menu.Edit.Teams = TEXT
                +) Menu.Edit.AITriggers = TEXT
                +) Menu.Edit.AITriggerEnable = TEXT
                +) Menu.Edit.LocalVariables = TEXT
                +) Menu.Edit.SingleplayerSettings = TEXT
                +) Menu.Edit.INIEditor = TEXT
                +) Menu.Terrain = TEXT
                +) Menu.Terrain.RaiseGround = TEXT
                +) Menu.Terrain.LowerGround = TEXT
                +) Menu.Terrain.FlattenGround = TEXT
                +) Menu.Terrain.HideTileset = TEXT
                +) Menu.Terrain.ShowEveryTileset = TEXT
                +) Menu.Terrain.HideSingleField = TEXT
                +) Menu.Terrain.ShowAllFields = TEXT
                +) Menu.Terrain.RaiseSingleTile = TEXT
                +) Menu.Terrain.LowerSingleTile = TEXT
                +) Menu.MapTools = TEXT
                +) Menu.MapTools.ChangeMapHeight = TEXT
                +) Menu.MapTools.AutoCreateShores = TEXT
                +) Menu.MapTools.AutoLevelUsingCliffs = TEXT
                +) Menu.MapTools.PaintCliffFront = TEXT
                +) Menu.MapTools.PaintCliffBack = TEXT
                +) Menu.MapTools.SearchWaypoint = TEXT
                +) Menu.MapTools.ToolScripts = TEXT
                +) Menu.Online = TEXT
                +) Menu.Online.Westwood = TEXT
                +) Menu.Online.FA2Fansite = TEXT
                +) Menu.Online.FA2Forum = TEXT
                +) Menu.Options = TEXT
                +) Menu.Options.Settings = TEXT
                +) Menu.Options.ShowMinimap = TEXT
                +) Menu.Options.Easymode = TEXT
                +) Menu.Options.Sounds = TEXT
                +) Menu.Options.ShowBuildingOutline = TEXT
                +) Menu.Options.DisableAutoShore = TEXT
                +) Menu.Options.DisableAutoLAT = TEXT
                +) Menu.Options.DisableSlopeCorrection = TEXT
                +) Menu.Help = TEXT
                +) Menu.Help.Manual = TEXT
                +) Menu.Help.Info = TEXT
                +) Menu.Help.Credits = TEXT
                +) Menu.Help.TipOfTheDay = TEXT
                +) Menu.Layers = TEXT
                +) Menu.Layers.Structures = TEXT
                +) Menu.Layers.Infantries = TEXT
                +) Menu.Layers.Units = TEXT
                +) Menu.Layers.Aircrafts = TEXT
                +) Menu.Layers.Basenodes = TEXT
                +) Menu.Layers.Waypoints = TEXT
                +) Menu.Layers.Celltags = TEXT
                +) Menu.Layers.MoneyOnMap = TEXT
                +) Menu.Layers.Overlays = TEXT
                +) Menu.Layers.Terrains = TEXT
                +) Menu.Layers.Smudges = TEXT
                +) Menu.Layers.Tubes = TEXT
                +) Menu.Layers.Bounds = TEXT
                +) AITriggerTitle = TEXT
                +) AITriggerList = TEXT
                +) AITriggerName = TEXT
                +) AITriggerTeam1 = TEXT
                +) AITriggerHouse = TEXT
                +) AITriggerTeam2 = TEXT
                +) AITriggerTechlevel = TEXT
                +) AITriggerType = TEXT
                +) AITriggerWeight = TEXT
                +) AITriggerMinWeight = TEXT
                +) AITriggerMaxWeight = TEXT
                +) AITriggerMinDiff = TEXT
                +) AITriggerSide = TEXT
                +) AITriggerTechnoType = TEXT
                +) AITriggerCondition = TEXT
                +) AITriggerNumber = TEXT
                +) AITriggerAdditionalDesc = TEXT
                +) AITriggerData = TEXT
                +) AITriggerEnabled = TEXT
                +) AITriggerAdd = TEXT
                +) AITriggerDel = TEXT
                +) AITriggerClo = TEXT
                +) AITriggerBaseDefense = TEXT
                +) AITriggerSkirmish = TEXT
                +) AITriggerEasy = TEXT
                +) AITriggerMedium = TEXT
                +) AITriggerHard = TEXT
                +) TaskforceTitle = TEXT
                +) TaskforceList = TEXT
                +) TaskforceUnits = TEXT
                +) TaskforceGroup = TEXT
                +) TaskforceUnitNumber = TEXT
                +) TaskforceUnitType = TEXT
                +) TaskforceSelected = TEXT
                +) TaskforceName = TEXT
                +) TaskforceNewTask = TEXT
                +) TaskforceDelTask = TEXT
                +) TaskforceCloTask = TEXT
                +) TaskforceNewUnit = TEXT
                +) TaskforceDelUnit = TEXT
                +) TaskforceCloUnit = TEXT
                +) TeamTypesTitle = TEXT
                +) TeamTypesNewTeam = TEXT
                +) TeamTypesDelTeam = TEXT
                +) TeamTypesCloTeam = TEXT
                +) TeamTypesMainDesc = TEXT
                +) TeamTypesCurrentTeamLabel = TEXT
                +) TeamTypesSelectedTeam = TEXT
                +) TeamTypesLabelName = TEXT
                +) TeamTypesLabelHouse = TEXT
                +) TeamTypesLabelTaskforce = TEXT
                +) TeamTypesLabelScript = TEXT
                +) TeamTypesLabelTag = TEXT
                +) TeamTypesLabelVeteranLevel = TEXT
                +) TeamTypesLabelPriority = TEXT
                +) TeamTypesLabelMax = TEXT
                +) TeamTypesLabelTechlevel = TEXT
                +) TeamTypesLabelTransportWaypoint = TEXT
                +) TeamTypesLabelGroup = TEXT
                +) TeamTypesLabelWaypoint = TEXT
                +) TeamTypesLabelMindControlDecision = TEXT
                +) TeamTypesCheckBoxLoadable = TEXT
                +) TeamTypesCheckBoxFull = TEXT
                +) TeamTypesCheckBoxAnnoyance = TEXT
                +) TeamTypesCheckBoxGuardSlower = TEXT
                +) TeamTypesCheckBoxRecruiter = TEXT
                +) TeamTypesCheckBoxAutoCreate = TEXT
                +) TeamTypesCheckBoxPrebuild = TEXT
                +) TeamTypesCheckBoxReinforce = TEXT
                +) TeamTypesCheckBoxCargoPlane = TEXT
                +) TeamTypesCheckBoxWhiner = TEXT
                +) TeamTypesCheckBoxLooseRecruit = TEXT
                +) TeamTypesCheckBoxAggressive = TEXT
                +) TeamTypesCheckBoxSuicide = TEXT
                +) TeamTypesCheckBoxOnTransOnly = TEXT
                +) TeamTypesCheckBoxAvoidThreats = TEXT
                +) TeamTypesCheckBoxIonImmune = TEXT
                +) TeamTypesCheckBoxTransportsReturnOnUnload = TEXT
                +) TeamTypesCheckBoxAreTeamMembersRecruitable = TEXT
                +) TeamTypesCheckBoxIsBaseDefense = TEXT
                +) TeamTypesCheckBoxOnlyTargetHouseEnemy = TEXT
                +) TriggerFrameTitle = TEXT
                +) TriggerFrameSelectedTrigger = TEXT
                +) TriggerFrameNew = TEXT
                +) TriggerFrameDel = TEXT
                +) TriggerFramePlace = TEXT
                +) TriggerFrameClone = TEXT
                +) TriggerOptionType = TEXT
                +) TriggerOptionName = TEXT
                +) TriggerOptionHouse = TEXT
                +) TriggerOptionAttached = TEXT
                +) TriggerOptionDisabled = TEXT
                +) TriggerOptionDisabledDesc = TEXT
                +) TriggerOptionEasy = TEXT
                +) TriggerOptionMedium = TEXT
                +) TriggerOptionHard = TEXT
                +) TriggerEventCurrent = TEXT
                +) TriggerEventNew = TEXT
                +) TriggerEventDel = TEXT
                +) TriggerEventClo = TEXT
                +) TriggerEventOptions = TEXT
                +) TriggerEventType = TEXT
                +) TriggerEventParameter = TEXT
                +) TriggerEventParamValue = TEXT
                +) TriggerEventDesc = TEXT
                +) TriggerActionCurrent = TEXT
                +) TriggerActionNew = TEXT
                +) TriggerActionDel = TEXT
                +) TriggerActionClo = TEXT
                +) TriggerActionOptions = TEXT
                +) TriggerActionType = TEXT
                +) TriggerActionParameter = TEXT
                +) TriggerActionParamValue = TEXT
                +) TriggerActionDesc = TEXT
                +) ScriptTypesTitle = TEXT
                +) ScriptTypesDesc = TEXT
                +) ScriptTypesSelectedScript = TEXT
                +) ScriptTypesName = TEXT
                +) ScriptTypesActions = TEXT
                +) ScriptTypesActionType = TEXT
                +) ScriptTypesActionDesc = TEXT
                +) ScriptTypesAddScript = TEXT
                +) ScriptTypesDelScript = TEXT
                +) ScriptTypesCloScript = TEXT
                +) ScriptTypesAddAction = TEXT
                +) ScriptTypesDelAction = TEXT
                +) ScriptTypesActionParam = TEXT
                +) ScriptTypesCloAction = TEXT
                +) ScriptTypesInsertMode = TEXT
                +) ScriptTypesExtraParam = TEXT
                +) ScriptTypesMoveUp = TEXT
                +) ScriptTypesMoveDown = TEXT

- WRITE IN THE END
This project was developed after FA2Copy with still many bugs to fix,
then Zero Fanker advised to use inline hooks instead of Win32API message hooks to implement
more functions and fix more bugs, and finally we comes to FA2sp. 

Thanks to AlexB, who gave me many suggestions and useful infomation while disassembling it.
(Chatting with him in the midnight because of time difference is quite interesting, too)

Zero Fanker has made a great contribution to the setting up of this project, with many
essential suggestions put forward.

Caco did quite much test works for this project, also bringing out many problems I haven't 
noticed before.

tomsons26 has made great assistance on disassembing it(REALLY HELPFUL).

thomassneddon provided me with vxl drawing lib and drawing stuff assistence, without I cannot draw the VXL stuffs.

(btw the code of FinalAlert 2 is really in a MESSY! Full of unnecessary constructors. I HATE IT!)
</pre>

这个项目从2020年的2月开始，当时它还是FA2Copy，因为我已经受够了FA2不能复制一些东西。
当时我也不会想到自己能在这个项目的进行过程中学到这么多的东西，回首看来，算上FA2PP我已经为这个项目写了4w多行代码。
FA2Copy在当年的5月6号迎来了最后一个版本，当时我放弃FA2Copy的原因其实非常简单：没有办法实现更多想要的功能了。
这个时候ZF找我，并向我介绍了基于Syringe的拓展方法，然后我也就此，从7月22号开始，开启了FA2的逆向+改进之旅。
这个项目之所以叫做FA2sp的原因我已经想不起来了，不过Kerb说的secsome's patch我觉得还是挺有道理的，就用这个解释也无妨。
一开始我也是一个对逆向一窍不通的小白，当初自己刚打完了OI，也是第一次接触到工程类软件的开发，一开始的代码毫无章法可言（可查看FA2Copy），完全就是乱成一坨。
现在我也大概入门了一个工程项目的架构搭建，能够写出算是另我自己满意且看的过去的代码了，这也算是一大提升。

现在看来，当时逆向遇到的最大瓶颈是CINI类，FA2因为用的是STL的map，一大堆内联展开直接就给我干趴下了。所以一开始我也是偷的AlexB的INI类在用，这里也要感谢
他的无私分享，初版的所属方颜色修复也是他给的。最后反正是按照时间往前慢慢推，我就去下了一个VC5，把VC5的map给直接搬了出来，当时我是一点一点地对着代码一个个
的比较，一个个的把函数给找出来并对应上去。

再后来也就没什么大不了的了，在这个过程中令我最印象深刻的就是第一次自己逆向出来FA2绘图数据存储的类（见Drawing.h中的ImageDataClass），依稀记得自己一点点
地调试输出，最后一点点地把每个成员的用途搞清楚，这个是我在开发过程中所做到最高兴的事情。

要说自己有什么感受，那最直观的就是能自己重写的就重写完事了。FA2的很多代码都是屎山，不管是对map的O(n^2)访问还是放的乱七八糟的建筑数据，我看的时候往往会怀疑自己
是不是看到正确的代码了，甚至还要怀疑是自己有问题还是什么。但事实很明显，FA2明显也是一个赶工出来的工具，他的设计者也没有考虑到在20年后还有人在用它开发着一个又一个
的精美地图。对于原版YR和RA2来说，它的功能已经绰绰有余，一些屎山代码也不会造成太大的影响。但是当我对它重置的时候，我就一定要考虑到这个，在我重写的时候，一定要考虑
好自己所写代码的效率究竟如何。

最后谈谈FA2的绘图问题，FA2的绘图是在第一次读取某个素材的时候对它进行缓存的，之后只是将它从内存中取出来再blt上去罢了。这个思路现在看来仍然是一个很好的思路，它有效
地控制了FA2的内存占用（点名批评RS）。所以在我发现这一点之后，我终于鼓起勇气替换了FA2的建筑，载具，飞行器，步兵，污染以及地形对象的绘制。这个东西看起来非常复杂，
我之前也尝试做过，但都因为种种原因半途而废了。最后实际做了下来发现只花了一个星期的时候其实我还是挺惊讶的，这也要多亏了偷猫的画图库，以及每天晚上一起抄VXLSE139到
凌晨四点。没有偷猫的库估计现在我还卡在VXL的绘制，最后这个绘图分支又会不了了之。

在开发过程中给予过我帮助的人有很多，包括但不局限于许多测试员，虽然他们总是延迟两个版本发现BUG，但最终我们共同努力，让FA2变得更加好用了许多。在这里不一一感谢了。

本项目以后也会更新，但大多数只会是FA2sp改的逻辑或带来的BUG的修复了，其余内容随心而为。
作为一个开源项目，当然也欢迎有实力的开发者来开几个PR玩玩，需要idb的也可以联系我，我也会提供（里面肯定很多BUG就是了）。

某书纪， 写于2021/08/20，19:03，1.0.4版本发布前夕
||这个写英文太麻烦了，就中文吧||
