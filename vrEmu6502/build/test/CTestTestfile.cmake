# CMake generated Testfile for 
# Source directory: /data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test
# Build directory: /data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(6502_functional_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "6502" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_functional_test.hex")
set_tests_properties(6502_functional_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;27;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(65c02_functional_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_functional_test.hex")
set_tests_properties(65c02_functional_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;28;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(w65c02_functional_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "w65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_functional_test.hex")
set_tests_properties(w65c02_functional_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;29;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(r65c02_functional_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "r65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_functional_test.hex")
set_tests_properties(r65c02_functional_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;30;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(6502_decimal_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "6502" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_decimal_test.hex")
set_tests_properties(6502_decimal_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;32;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(65c02_decimal_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/65C02_decimal_test.hex")
set_tests_properties(65c02_decimal_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;33;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(w65c02_decimal_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "w65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/65C02_decimal_test.hex")
set_tests_properties(w65c02_decimal_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;34;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(r65c02_decimal_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "r65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/6502_decimal_test.hex")
set_tests_properties(r65c02_decimal_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;35;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(65c02_extended_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/65C02_extended_opcodes_test.hex")
set_tests_properties(65c02_extended_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;37;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(w65c02_extended_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "w65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/W65C02_extended_opcodes_test.hex")
set_tests_properties(w65c02_extended_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;38;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
add_test(r65c02_extended_test "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/build/bin/vrEmu6502Test" "-quiet" "-cpu" "r65c02" "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/programs/R65C02_extended_opcodes_test.hex")
set_tests_properties(r65c02_extended_test PROPERTIES  _BACKTRACE_TRIPLES "/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;39;add_test;/data/data/com.termux.nix/files/home/6502-OS/vrEmu6502/test/CMakeLists.txt;0;")
