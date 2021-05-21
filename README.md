<pre>
I've decided to make this repository public so that more developers can help me improving it.
For now it had implemented all features that FA2Ext has and extended more logics than it.
The codes might be a messy, so I'd appreciate it if someone could help me to make them better arranged.

To clone the submodules, just run update_codes.bat.

SDK: Visual Studio 2017 - Windows XP (v141_xp)
C++ Standard: C++14 (Higher standard conflicts with INIClass right now)

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~////////// FINALALERT2 - SP CHANGELOG //////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

======================= Changes (2021-xx-xx) ==============================================================================================
+) New ExtConfig: CopySelectionBound.Color = COLORREF, custom the copy selection bound color, defaults to 255(0x0000FF)
+) New ExtConfig: CursorSelectionBound.Color = COLORREF, same as the above one, defaults to 3973180(0x3CA03C)
+) New ExtConfig: CursorSelectionBound.HeightIndicatorColor = COLORREF, same as the above one, defaults to 3947580(0x3C3C3C)

======================= Changes (2021-05-07) ==============================================================================================
+) New ExtConfig: SortByTriggerName = BOOLEAN, enable it so FA2 will sort the triggers dropdown and sort them by their name instead of ID
+) New ExtConfig: AdjustDropdownWidth = BOOLEAN, enable it so FA2 will adjust the param dropdown width automatically
    +) New ExtConfig: AdjustDropdownWidth.Factor = INTERGER, determines how long is a single char takes, defaults to 8
    +) New ExtConfig: AdjustDropdownWidth.Max = INTERGER, determins the max length of the combobox, defaults to 360
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
            +) CopySelectionBound.Color = COLORREF ; Determines the color of the selection boundary while copying, defaults to 255
            +) CursorSelectionBound.Color = COLORREF ; Determines the color of the boundary for current cell, defaults to 3973180
            +) HeightIndicatorColor.Color = COLORREF ; Determines the color of the height indicator for current cell, defaults to 3947580
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
    - FALanguage.ini
        *)  [CURRENTLANGUAGE-StringsRA2]
            [CURRENTLANGUAGE-Strings]
            [CURRENTLANGUAGE-TranslationsRA2]
            [CURRENTLANGUAGE-Translations]
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
                +) TriggerEventOptions = TEXT
                +) TriggerEventType = TEXT
                +) TriggerEventParameter = TEXT
                +) TriggerEventParamValue = TEXT
                +) TriggerEventDesc = TEXT
                +) TriggerActionCurrent = TEXT
                +) TriggerActionNew = TEXT
                +) TriggerActionDel = TEXT
                +) TriggerActionOptions = TEXT
                +) TriggerActionType = TEXT
                +) TriggerActionParameter = TEXT
                +) TriggerActionParamValue = TEXT
                +) TriggerActionDesc = TEXT

- WORK IN PROGRESS
    - Support for cloning scripts & taskforces & ai triggers
    - SHP turret rotation (currently doesn't change and always points to the north)
    - Custom palettes
    - ...

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

(btw the code of FinalAlert 2 is really in a MESSY! Full of unnecessary constructors. I HATE IT!)

- CONTACT ME
EMAIL : 3179369262@qq.com
Discord : secsome#5043
NO OTHER AVAILABLE METHODS ... FOR NOW ;D
</pre>
