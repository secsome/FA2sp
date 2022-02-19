<pre>
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~////////// FINALALERT2 - SP CHANGELOG //////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

======================= Changes (2022-02-11 RELEASE 1.4.0.1) ==============================================================================================
*) Fixed the bug that Powerups are not being rendered in several cases
*) Fixed the bug that MoneyCounter is not working properly

======================= Changes (2022-02-10 RELEASE 1.4.0) ==============================================================================================
+) Now you can create a map with size up to 255*255
+) New ExtConfig: RecentFileLimit = INTEGER, defaults to 6, should be a integer between 4 and 9 
*) Optimized mouse attached building drawing
+) Reimplemented tube generation
+) Support for multi-selection, the detailed usage can be looked up in the document below
+) New ExtConfig : MultiSelectionColor = COLORREF, back color of selected tiles
+) Theater order in dropdown is now customizable and theaters can be disabled
+) New ExtConfig : Waypoint.Text.ExtraOffset = POINT, WP text offsets
+) New ExtConfig : SaveMap.DefaultPreviewOptionMP = INTEGER, SaveMap.DefaultPreviewOptionSP = INTEGER, read the doc below
*) ExtConfig : SaveMap tag has been removed, it will be forced to enable now

======================= Changes (2021-12-31 RELEASE 1.3.0) ==============================================================================================
***) The project now compiles under v143+/std:c++latest, Windows XP may not be able to use this dll
+) New ExtConfig: FastResize = BOOLEAN, enable it so resizing the map will be much more faster when expanding
+) Experimental Lighting, only for preview, not correct
+) More localization support
+) Added more internal param codes
*) You can now customize tile manager by regex
*) Reimplement waypoint drawing, reduce lag
*) Minor adjustments

======================= Changes (2021-11-20 RELEASE 1.2.2) ==============================================================================================
+) Now you can add more ramps to be auto generated in FA2 by setting [THEATERInfo] in fadata.ini
+) Now you can specify the display name of theaters
+) Support for ExtraMixes, will be read before any other mixes
+) Support for OverlayDisplayLimit, the frame after this number won't be displayed in the TilesetBrowserView, up to 60
*) ExtConfig : Stringtable tag has been removed, it will be forced to enable now
*) Minor fixes

======================= Changes (2021-11-12 RELEASE 1.2.1) ==============================================================================================
*) Remove a hook that might lead to some problem
*) Adjust some rc file
*) Fixed BrowserRedraw.SafeHouses not working correctly
*) Now property brush handles mouse move too

======================= Changes (2021-11-04 RELEASE 1.2.0) ==============================================================================================
+) New ObjectBrowser items: Property brushes (FALanguage has been updated)

======================= Changes (2021-11-02 RELEASE 1.1.3) ==============================================================================================
*) Fixed the bug that EVA(md).ini cannot be loaded
*) Now ScriptsRA2 will correctly read inconsistent keys
+) New ExtConfig: BrowserRedraw.SafeHouses, enable it so that the houses being displayed in ObjectBrowserView will be rearranged correctly but won't update until you load the map again

======================= Changes (2021-10-16 RELEASE 1.1.2) ==============================================================================================
*) Fixed the bug that FA2sp crashes while trying to read/write file on some systems

======================= Changes (2021-10-12 RELEASE 1.1.1) ==============================================================================================
*) Minor bugfixes
*) Now FA2sp will apply Visual Style depending on your system instead of keeping them look like Windows95 style

======================= Changes (2021-10-03 RELEASE 1.1.0) ==============================================================================================
+) Trigger sort, which will provide you some handy in trigger classification
+) Now you can directly edit [Ranking] in SingleplayerSettings
+) Now you can edit all stuff of [Lighting]
+) New ExtConfig: VerticalLayout = BOOLEAN, enable it so that FA2sp will make the bottom view go to the right side
*) Now you can delete a trigger and its celltags at the same time
*) Now you can custom script param typelist

======================= Changes (2021-09-28 RELEASE 1.0.7) ==============================================================================================
*) Changed the layout of CRightView::CTileSetBrowserFrame from [0, 1] to [1, 0], it's vertical now
*) Now FA2 will not only read default palettes from cache.mix but read them like the normal files
*) Fix the remaining autosave bug cannot removing earlier maps
*) Fix the bug that Multiplayer map cannot save PreviewPack correctly

======================= Changes (2021-09-23 RELEASE 1.0.6) ==============================================================================================
*) Fix the autosave bug caused by Loritas
*) Fix the problem that FA2 crashes after kill focus
*) Fix the problem that Allie Editor not being applied to the data automatically
*) Fix the bug that resize map not take basenodes and smudges into consideration

==  Known Bug : SaveMap = Yes will sometimes crashes the PreviewPack  ==
== consider to save it again with origin FA2 after finishing your map ==

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
    +) New ExtConfig: AdjustDropdownWidth.Factor = INTEGER, determines how long is a single char takes, defaults to 8
    +) New ExtConfig: AdjustDropdownWidth.Max = INTEGER, determines the max length of the combobox, defaults to 360
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
</pre>