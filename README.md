~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~////////// FINALALERT2 - SP CHANGELOG //////////~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\\\\//////////////////////////////////////\\\\\~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

======================= Changes (2021-01-XX) ==============================================================================================
*) Now use path from FinalAlert.ini instead of the one in registry
*) Coordinates are now shown as X / Y - H.
*) ObjectBrowserControl refactored
    +) Not only Buildings, but Infantrys, Aircrafts and Vehicles now have been classified into sides (1)
    +) Not only the original hardcoded overlays but also all overlays having Wall=yes will be auto connected
*) Now infantry's facing will be correctly shown
*) Overlay which has the index bigger than 255 will be ignored
+) Support Ares' += and #include functions (not recommended to use in maps)
+) Support Ares' stringtableXX.csf
+) ScriptTypes now use a different set of params and can be extended
+) Mix Extension and INI Filenames can be customed
+) Ctrl+S, Ctrl+O, Ctrl+N and Ctrl+Shift+S are now supported
+) Easy ciphered mix files will be correctly read
*) House colors will be correctly drawn instead of using a hardcoded set of colors (for most, yellow)
