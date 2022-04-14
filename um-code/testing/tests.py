UINT_25_MAX = 33554431

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