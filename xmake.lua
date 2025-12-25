set_project("bankmgr")
set_version("1.0.0", {build = "%Y%m%d%H%M"})
set_license("MIT")

add_rules("mode.debug", "mode.release")
set_toolchains("mingw")
set_languages("c++20")
set_warnings("all")

-- 针对 Windows/MinGW 环境添加编码转换标志
if is_plat("windows", "mingw") then
    -- -finput-charset=UTF-8: 告诉编译器源码是 UTF-8 (通常默认就是，但显式指定更安全)
    -- -fexec-charset=GBK:  告诉编译器把字符串字面量转成 GBK 存入 exe
    add_cxflags("-finput-charset=UTF-8", "-fexec-charset=GBK")
end

target("bankmgr")
    set_kind("binary")
    add_files("src/*.cpp")
    add_files("src/main.cpp")
    add_includedirs(".")

-- xmake run bankmgr

-- 每个同学的独立测试程序
target("test-lxh")
    set_kind("binary")
    add_files("tests/test-lxh.cpp")
    add_files("src/*.cpp")
    add_includedirs("src")
    remove_files("src/main.cpp")
-- xmake run test-lxh

target("test-wzs")
    set_kind("binary")
    add_files("tests/test-wzs.cpp")
    add_files("src/*.cpp")
    add_includedirs("src")
    remove_files("src/main.cpp")
-- xmake run test-wzs

target("test-wj")
    set_kind("binary")
    add_files("tests/test-wj.cpp")
    add_files("src/*.cpp")
    add_includedirs("src")
    remove_files("src/main.cpp")
-- xmake run test-wj

target("test-wmk")
    set_kind("binary")
    add_files("tests/test-wmk.cpp")
    add_files("src/*.cpp")
    add_includedirs("src")
    remove_files("src/main.cpp")
-- xmake run test-wmk

target("test-lzy")
    set_kind("binary")
    add_files("tests/test-lzy.cpp")
    add_files("src/*.cpp")
    add_includedirs("src")
    remove_files("src/main.cpp")
-- xmake run test-lzy

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro definition
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

