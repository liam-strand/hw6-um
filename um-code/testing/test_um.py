import os.path
import subprocess as sp
import sys
from ctypes import *
from enum import Enum
from random import randint

def main():
    ul = CDLL("./umlab.so")
    prepare_library(ul)

    tests = [
        ("add_test", [
            ul.load_value(1, ord('0')),
            ul.load_value(2, 6),
            ul.add(3, 1, 2),
            ul.output(3),
            ul.load_value(3, ord('\n')),
            ul.output(3),
            ul.halt(),
        ], None, "6\n"),
        ("halt_test", [
            ul.halt()
        ], None, None),
        ("input_test", [
            ul.input(1),
            ul.load_value(2, 1),
            ul.add(3, 1, 2),
            ul.output(3),
            ul.halt(),
        ], None, None)
    ]

    run_tests(tests)

def run_tests(tests: list) -> None:
    for test_name, instrs, uinput, output in tests:
        print_test(instrs, test_name)
        
        if uinput:
            write_input(test_name, uinput)
        if output:
            write_output(test_name, output)

        if uinput and not output:
            run_test(test_name, infile=f"{test_name}.in")
        elif output and not uinput:
            run_test(test_name, outfile=f"{test_name}.out")
        elif uinput and output:
            run_test(test_name, infile=f"{test_name}.in", outfile=f"{test_name}.out")
        else:
            run_test(test_name)

def run_test(test_name, infile=None, outfile=None):
    
    if infile and not outfile:
        sp.run(f"cat {infile} | um {test_name}.um", shell=True)
    elif not infile and not outfile:
        sp.run(f"um {test_name}.um", shell=True)
    elif not infile and outfile:
        sp.run(f"um {test_name}.um > {test_name}.realout", shell=True)
        sp.run(f"diff {test_name}.realout, {outfile}", shell=True)
    else:
        sp.run(f"cat {infile} | um {test_name}.um > {test_name}.realout", shell=True)
        sp.run(f"diff {test_name}.realout, {outfile}", shell=True)

def print_test(instructions: list, filename: str) -> None:
    with open(f"{filename}.um", "wb") as f:
        for inst in instructions:
            f.write(inst.to_bytes(4, "big"))

def write_input(name: str, provided_input: str) -> None:
    with open(f"{name}.in", "w", encoding="ascii") as f:
        f.write(provided_input)

def write_output(name: str, expected_output: str) -> None:
    with open(f"{name}.out", "w", encoding="ascii") as f:
        f.write(expected_output)

def prepare_library(lib):
    lib.conditional_move.argtypes = [c_uint, c_uint, c_uint]
    lib.segmented_load.argtypes   = [c_uint, c_uint, c_uint]
    lib.segmented_store.argtypes  = [c_uint, c_uint, c_uint]
    lib.mul.argtypes              = [c_uint, c_uint, c_uint]
    lib.div.argtypes              = [c_uint, c_uint, c_uint]
    lib.add.argtypes              = [c_uint, c_uint, c_uint]
    lib.nand.argtypes             = [c_uint, c_uint, c_uint]
    lib.halt.argtypes             = []
    lib.map_segment.argtypes      = [c_uint, c_uint]
    lib.unmap_segment.argtypes    = [c_uint]
    lib.output.argtypes           = [c_uint]
    lib.input.argtypes            = [c_uint]
    lib.load_program.argtypes     = [c_uint, c_uint]
    lib.load_value.argtypes       = [c_uint, c_uint]

    lib.conditional_move.restype = c_uint
    lib.segmented_load.restype   = c_uint
    lib.segmented_store.restype  = c_uint
    lib.mul.restype              = c_uint
    lib.div.restype              = c_uint
    lib.add.restype              = c_uint
    lib.nand.restype             = c_uint
    lib.halt.restype             = c_uint
    lib.map_segment.restype      = c_uint
    lib.unmap_segment.restype    = c_uint
    lib.output.restype           = c_uint
    lib.input.restype            = c_uint
    lib.load_program.restype     = c_uint
    lib.load_value.restype       = c_uint


if __name__ == "__main__":
    main()
