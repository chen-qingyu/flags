set_project("flags")
set_languages("c++20")
set_encodings("utf-8")

add_rules("mode.debug", "mode.release")

target("flags")
    add_rules("qt.widgetapp")
    add_headerfiles("src/*.h")
    add_files("src/*.cpp","src/*.h") -- add header files for qt.moc
