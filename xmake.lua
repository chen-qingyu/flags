add_rules("mode.debug", "mode.release")

target("flags")
    add_rules("qt.widgetapp")
    add_headerfiles("src/*.h")
    add_files("src/*.cpp")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("src/mainwindow.h")
