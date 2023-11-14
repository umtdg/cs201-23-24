import argparse
import sys
import time

# printing/logging
import logging

from rich import print
from rich.logging import RichHandler
from rich.table import Table as RichTable

# profiling
import psutil
import subprocess as sp

# data handling
import pandas as pd
import numpy as np


sample_sizes = [
    (64, 500),
    (128, 350),
    (250, 250),
    (512, 125),
    (1000, 100),
    (4096, 75),
    (10000, 30),
    (15364, 20),
    (25977, 10),
    (32768, 10)
]

sizes = [s for s,_ in sample_sizes]
O_logn = [np.log(s) for s in sizes]
O_n = sizes
O_nlogn = [s*np.log(s) for s in sizes]
O_n2 = [s**2 for s in sizes]

sort_methods = [
    "bubble",
    "quick",
    "merge"
]


def profile_subprocess(interval, *args, **kwargs) -> (int, int):
    proc = sp.Popen(*args, **kwargs)
    psutil_proc = psutil.Process(proc.pid)
    psutil_proc.cpu_affinity([0])

    max_mem_used = 0
    while proc.poll() is None:
        mem_used = psutil_proc.memory_info().rss
        if mem_used > max_mem_used:
            max_mem_used = mem_used

        time.sleep(interval)

    if proc.returncode != 0:
        print(f"Error: {proc.stderr.read()}")
    else:
        return int(proc.stdout.read()), max_mem_used

def negate(arr: np.ndarray, start, end) -> np.ndarray:
    part = np.negative(arr[start:end])
    return part

def reverse(arr: np.ndarray, start, end) -> np.ndarray:
    part = np.flip(arr[start:end])
    return part

def swap(arr: np.ndarray, i1, i2) -> np.ndarray:
    arr[i1], arr[i2] = arr[i2], arr[i1]
    return arr[i1:i2]

def sorted2almost(arr: np.ndarray):
    shuffle_funcs = [
        negate,
        reverse,
        swap
    ]

    # max_block_size = int(np.log(len(arr)))
    n = len(arr)
    # no_ops = int(np.log(n))
    no_ops = 4
    max_block_size = no_ops

    for _ in range(int(np.log(n))):
        shuffle_func = np.random.choice(shuffle_funcs)
        start = np.random.randint(0, n)

        end = start + np.random.randint(0, max_block_size)
        end = np.clip(end, 0, n-1)

        arr[start:end] = shuffle_func(arr, start, end)

def gen_samples(sample_size: int, number_of_runs: int,
                with_sorted: bool = False, descending: bool = False,
                almost_sorted: bool = False):
    samples = np.random.randint(0, 2147483647, (number_of_runs, sample_size))
    if with_sorted or descending or almost_sorted:
        samples = np.sort(samples, axis=1)

    if descending:
        samples = np.flip(samples, axis=1)

    if almost_sorted:
        for sample in samples:
            sorted2almost(sample)

    return samples

def benchmark(
        executable: str, sort_method: str, data_file: str,
        sample_size: int, number_of_runs: int, with_sorted: bool = False,
        descending: bool = False, almost_sorted: bool = False):
    logging.debug(f"Generating samples of size {number_of_runs}x{sample_size}")
    exec_args = [executable, sort_method, data_file, str(sample_size)]

    samples = gen_samples(sample_size, number_of_runs, with_sorted,
                          descending, almost_sorted)

    times = []
    memory_usages = []
    for i in range(number_of_runs):
        logging.debug(f"Running benchmark {i+1}/{number_of_runs}")
        np.savetxt(data_file, samples[i], fmt="%d")
        elapsed_time, used_memory = profile_subprocess(0.001, exec_args, stdout=sp.PIPE, stderr=sp.PIPE)

        times.append(elapsed_time)
        memory_usages.append(used_memory)

        logging.debug(f"{elapsed_time} ns, {used_memory} B")

    return [sort_method, sample_size, np.mean(times), np.mean(memory_usages)]

def batch_benchmark(args):
    columns = ["sample_size"] + sort_methods
    benchmark_results_time = pd.DataFrame(columns=columns)
    benchmark_results_memory = pd.DataFrame(columns=columns)

    for sample_size, number_of_runs in sample_sizes:
        row_time = [sample_size,]
        row_memory = [sample_size,]
        for sort_method in sort_methods:
            logging.info(
                f"Running benchmark on [bold green]{args.data_type}[/bold green] "
                + f"data with sample size {sample_size} and {number_of_runs} runs "
                + f"for [bold green]{sort_method}[/bold green]",
                extra={"markup": True}
            )
            result = benchmark(
                args.executable, sort_method, args.file, sample_size,
                number_of_runs, args.asc or args.desc,
                args.desc, args.almost
            )

            row_time.append(round(result[2], 2))
            row_memory.append(round(result[3]/1024, 2))

        benchmark_results_time.loc[len(benchmark_results_time)] = row_time
        benchmark_results_memory.loc[len(benchmark_results_memory)] = row_memory

    return benchmark_results_time, benchmark_results_memory

def create_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", "--data-file", type=str, default="/tmp/data.txt")
    parser.add_argument("-e", "--executable", type=str, required=True)
    parser.add_argument("--log-level", type=str, default="INFO", choices=["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"])

    data_type_group = parser.add_mutually_exclusive_group(required=True)
    data_type_group.add_argument("--asc", action="store_true")
    data_type_group.add_argument("--desc", action="store_true")
    data_type_group.add_argument("--almost", action="store_true")
    data_type_group.add_argument("--random", action="store_true")

    return parser

def main():
    parser = create_parser()
    args = parser.parse_args(sys.argv[1:])

    args.log_level = args.log_level.upper()
    logging.basicConfig(
        level=args.log_level,
        format="%(message)s",
        datefmt="[%X]",
        handlers=[RichHandler(omit_repeated_times=False)]
    )

    args.data_type = "random"
    if args.asc: args.data_type = "ascending"
    if args.desc: args.data_type = "descending"
    if args.almost: args.data_type = "almost sorted"

    benchmark_results_time, benchmark_results_memory = batch_benchmark(args)

    benchmark_results_time.to_csv(f"benchmark_results_time_{args.data_type}.csv", index=False)
    benchmark_results_memory.to_csv(f"benchmark_results_memory_{args.data_type}.csv", index=False)


if __name__ == "__main__":
    main()
