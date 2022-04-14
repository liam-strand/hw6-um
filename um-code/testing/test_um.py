import os.path
import subprocess as sp
import sys
from ctypes import *
from enum import Enum
from random import randint
import multiprocessing as mp
from tqdm import tqdm
from time import sleep
from pprint import pprint

TESTDIR = "testing/output/"
UINT_25_MAX = 33554431


def main():
    ul = CDLL("./testing/umlab.so")
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
        ], None),
        ("halt_test", [
            ul.halt()
        ], None),
        ("input_test", [
            ul.input(1),
            ul.load_value(2, 1),
            ul.add(3, 1, 2),
            ul.output(3),
            ul.halt(),
        ], "5"),
    ]

    # run_tests(tests)

    run_tests(generate_div_tests(ul))
    run_tests(generate_add_tests(ul))
    run_tests(generate_mul_tests(ul))
    run_tests(generate_and_tests(ul))
    run_tests(generate_cmov_tests(ul))
    run_tests(generate_seg_map_tests(ul))
    run_tests(generate_seg_unmap_tests(ul))
    run_tests(generate_load_seg_tests(ul))

def generate_div_tests(lib) -> list:

    tests = []

    for i in range(0, 10):
        for j in range(1, 100):
            tests.append(
                (f"div_{i}_{j}_test", [
                    lib.load_value(1, i),
                    lib.load_value(2, j),
                    lib.div(3, 1, 2),
                    lib.output(3),
                    lib.load_value(3, ord('\n')),
                    lib.output(3),
                    lib.halt(),
                ], None)
            )
    
    return tests

def generate_mul_tests(lib) -> list:

    tests = []
    for k in range(0, 8):
        for i in range(0, 10000000, 10000000):
            for j in range(1, 15):
                tests.append(
                    (f"mul_{i}_{j}_test", [
                        lib.load_value(k, i),
                        lib.load_value(2, j),
                        lib.mul(3, k, 2),
                        lib.load_value(4, 255),
                        lib.nand(3, 3, 4),
                        lib.nand(4, 3, 3),
                        lib.output(4),
                        lib.load_value(3, ord('\n')),
                        lib.output(3),
                        lib.halt(),
                    ], None)
                )
    
    return tests

def generate_add_tests(lib) -> list:

    tests = []

    for i in range(0, 128):
        for j in range(0, 100000, 10000):
            tests.append(
                (f"add_{i}_{j}_test", [
                    lib.load_value(1, i),
                    lib.load_value(2, j),
                    lib.add(3, 1, 2),
                    lib.load_value(4, 255),
                    lib.nand(3, 3, 4),
                    lib.nand(4, 3, 3),
                    lib.output(4),
                    lib.load_value(3, ord('\n')),
                    lib.output(3),
                    lib.halt(),
                ], None)
            )
    
    return tests

def generate_and_tests(lib) -> list:

    tests = []

    for i in range(0, UINT_25_MAX, 100000):
        tests.append(
            (f"and_{i}_255_test", [
                lib.load_value(1, 255),
                lib.load_value(2, i),
                lib.nand(3, 1, 2),
                lib.nand(4, 3, 3),
                lib.output(4),
                lib.load_value(3, ord('\n')),
                lib.output(3),
                lib.halt(),
            ], None)
        )
    
    return tests

def generate_or_tests(lib) -> list:

    tests = []

    for i in range(0, 256):
        for j in range(0, 10):
            tests.append(
                (f"or_{i}_{j}_test", [
                    lib.load_value(1, i),
                    lib.load_value(2, j),
                    lib.nand(3, 1, 2),
                    lib.nand(4, 3, 3),
                    lib.output(4),
                    lib.load_value(3, ord('\n')),
                    lib.output(3),
                    lib.halt(),
                ], None)
            )
    
    return tests

def generate_cmov_tests(lib) -> list:

    tests = []

    for i in range(1, 256):
        for k in range(0, 2):
            tests.append(
                (f"cmov_{i}_{k}test", [
                    lib.load_value(1, i),
                    lib.load_value(4, 0),
                    lib.load_value(3, k),
                    lib.conditional_move(1, 4, 3),
                    lib.output(4),
                    lib.load_value(3, ord('\n')),
                    lib.output(3),
                    lib.halt(),
                ], None)
            )
    
    return tests

def generate_seg_map_tests(lib) -> list:
    
    map_1000 = [lib.map_segment(0, 1)] * 100000

    map_1000.insert(0, lib.load_value(1, 1000))
    map_1000.append(lib.halt())

    return [("seg_map_stress_test", map_1000, None)]

def generate_seg_unmap_tests(lib) -> list:
    
    map_1000 = [
        lib.map_segment(1, 0),
        # lib.load_value(5, ord('0')),
        # lib.add(6, 5, 1),
        # lib.output(6),
        # lib.load_value(6, ord('\n')),
        # lib.output(6),
        lib.unmap_segment(1),
    ] * 1000000

    map_1000.insert(0, lib.load_value(1, 100))
    map_1000.append(lib.halt())

    return [("seg_unmap_stress_test", map_1000, None)]

def generate_load_seg_tests(lib) -> list:

    tests = []
    for i in range(0, 256):
        tests.append(
            (f"load_seg_{i}_test", [
                lib.load_value(0, i),
                lib.load_value(2, 1),
                lib.load_value(3, 0),
                lib.map_segment(1, 2),
                lib.segmented_store(1, 3, 0),
                lib.segmented_load(6, 1, 3),
                lib.output(6),
                lib.load_value(6, ord('\n')),
                lib.output(6),
                lib.halt(),
            ], None)
        )
    
    return tests

def run_tests(tests: list) -> None:
    # with mp.Pool(15) as pool:
    #     pool.map(apply_test, tests)
    for test in tqdm(tests):
        apply_test(test)
    

def apply_test(zipped_test) -> None:
    test_name, instrs, uinput = zipped_test
    print_test(instrs, test_name)
        
    if uinput:
        write_input(test_name, uinput)
        write_output(test_name, uinput)
    else:
        write_output(test_name)

    if uinput:
        run_test(test_name, infile=f"{test_name}.0")
    else:
        run_test(test_name)

def run_test(test_name, infile=None):
    # print("running test", file=sys.stderr)
    if infile:
        sp.run(f"cat {TESTDIR}{infile} | ./um {TESTDIR}{test_name}.um > {TESTDIR}{test_name}.out", shell=True)
    else:
        sp.run(f"./um {TESTDIR}{test_name}.um > {TESTDIR}{test_name}.out", shell=True)
    
    sp.run(f"diff -aqN {TESTDIR}{test_name}.1 {TESTDIR}{test_name}.out", shell=True)

def print_test(instructions: list, filename: str) -> None:
    # print("printing test", file=sys.stderr)
    with open(f"{TESTDIR}{filename}.um", "wb") as f:
        for inst in instructions:
            f.write(inst.to_bytes(4, "big"))

def write_input(name: str, provided_input: str) -> None:
    # print("printing input", file=sys.stderr)
    with open(f"{TESTDIR}{name}.0", "w", encoding="ascii") as f:
        f.write(provided_input)

def write_output(name: str, user_input=None) -> None:
    # print("printing output", file=sys.stderr)
    if user_input:
        sp.run(f"cat {TESTDIR}{name}.0 | um {TESTDIR}{name}.um > {TESTDIR}{name}.1", shell=True)
    else:
        sp.run(f"um {TESTDIR}{name}.um > {TESTDIR}{name}.1", shell=True)

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
