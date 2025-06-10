# PLDI'25 Artifacts

This repository contains the artifacts for the paper:

**"Modular Construction and Optimization of the UZP Sparse Format for SpMV on CPUs"**

## Contents
- **lib**: this folder contains libraries and scripts required for the artifact, and is not intended to be modified by the user.
- **spmv-executors**: this folder contains codes and scripts to execute the SpMV kernel on different formats (SpMV and the baselines used in the submitted paper). A more complete description on how to replicate the experimentation in the paper is given below.
- **uzp-tuners**: the UZP format can be tuned for specific targets (compression, execution performance of specific kernels, etc.). This folder contains example tuners. A more complete description on it is given below.
- **z_polyhedrator**: this is the Rust tool mentioned in Sec. 4.1 of the paper that is used to generate UZP files. Refer to the README.md inside this folder for more details and instructions of usage. The tool is used automatically by the execution scripts in the "spmv-executors" folder.

## Running the spmv-executors

The "spmv-executors" folder contains the different SpMV versions used in Section 5 of the paper, and allows to automatically run experiments on any SuiteSparse matrix:

1. UZP GenEx: the code is contained in folder spmv-executors/uzp-genex. In order to automatically launch an experiment:
    * cd spmv-executors
    * ./uzp\_spmv.sh <group> <matrix> <datatype> <cache mode> <execution threads>
        * <group> and <matrix> are a Group name and Matrix name from SuiteSparse.
        * <datatype>: either "double" or "float" for double and single precision, respectively.
        * <cache mode>: either "hot" or "cold". Under cold cache settings, the SpMV kernel is run only once. Under hot cache settings, the kernel is run 100 times without cleaning the cache between repetitions.
        * <execution threads>: either "1th", "2th", or "8th".
    * See important notes below about repeatability, including operational frequency and pinning of threads to cores in the execution machine.
    * The script automatically downloads the required files from SuiteSparse to the /tmp folder of the execution machine, generates UZP files as needed, and launches the executor. By default, this script mines for patterns and tunes the UZP file as described in Sec. 4.3 in the paper. Refer to the subsections below about customizing UZP construction and tuning for more information.
    * The script outputs the obtained performance in GFLOPS. It can be modified to output performance counters instead, by modifying the "uzp\_spmv.sh" script to compile with OUTPUT\_TYPE=PAPI. In this case, a papi\_counters.list must be created inside folder "spmv-executors/uzp-genex" capturing the counters to measure. See PolyBench C/4.2.1 documentation for more details.
    * For instance: "./uzp\_spmv.sh QLi crashbasis double cold 1th" obtains a performance of approximately 6.8 GFLOPS on the Intel Core 12900K machine used for the tests when fixing the operational frequency at 3.2 GHz.

2. MKL executor: the code is contained in folder spmv-executors/spmv-mkl. In order to automatically launch the experiment:
    * cd spmv-executors
    * ./mkl\_spmv.sh <group> <matrix> <datatype> <cache mode> <execution threads>
        * <group> and <matrix> are a Group name and Matrix name from SuiteSparse.
        * <datatype>: either "double" or "float" for double and single precision, respectively.
        * <cache mode>: either "hot" or "cold". Under cold cache settings, the SpMV kernel is run only once. Under hot cache settings, the kernel is run 100 times without cleaning the cache between repetitions.
        * <execution threads>: either "1th", "2th", or "8th".
    * See important notes below about repeatability, including operational frequency and pinning of threads to cores in the execution machine.
    * The script automatically downloads the required files from SuiteSparse to the /tmp folder of the execution machine, and launches the executor. By default, this script uses the IEhint capabilities in MKL 2024.1. In order to disable them, comment the relevant lines in "spmv-mkl/spmv{d}\_mkl.c" (calls to mkl\_sparse\_set\_mv\_hint and mkl\_sparse\_optimize).
    * The script outputs the obtained performance in GFLOPS. It can be modified to output performance counters instead, by modifying the "spmv-mkl/Makefile" file to compile with -DPOLYBENCH\_PAPI, instead of -DPOLYBENCH\_GFLOPS. In this case, a papi\_counters.list must be created inside folder "spmv-executors/uzp-genex" capturing the counters to measure. See PolyBench C/4.2.1 documentation for more details.
    * For instance: "./mkl\_spmv.sh QLi crashbasis double cold 1th" obtains a performance of approximately 4.8 GFLOPS on the Intel Core 12900K machine used for the tests when fixing the operational frequency at 3.2 GHz.

3. MACVETH executor: the helper files are contained in folder spmv-executors/spmv-macveth. The source code are downloaded from the MACVETH artifact repository in GitHub by the script. In order to automatically launch the experiment:
    * cd spmv-executors
    * ./macveth\_spmv.sh <group> <matrix> <datatype> <cache mode> <execution threads>
        * <group> and <matrix> are a Group name and Matrix name from SuiteSparse.
        * <datatype>: only "float" is supported by MACVETH, using single-precision floating-point operations.
        * <cache mode>: either "hot" or "cold". Under cold cache settings, the SpMV kernel is run only once. Under hot cache settings, the kernel is run 100 times without cleaning the cache between repetitions.
        * <execution threads>: only "1th" is supported by the MACVETH artifact, using single-threaded execution.
    * See important notes below about repeatability, including operational frequency and pinning of threads to cores in the execution machine.
    * The script automatically downloads the required files from SuiteSparse to the /tmp folder of the execution machine, downloads the data-specific source codes from the GitHub repository containing the artifact for MACVETH, compiles the source (this step may take a long time, depending on the input matrix and target machine), and launches the executor. 
    * The script outputs the obtained performance in GFLOPS. It can be modified to output performance counters instead, by modifying the "spmv-macveth/Makefile" file to compile with -DPOLYBENCH\_PAPI, instead of -DPOLYBENCH\_GFLOPS. In this case, a papi\_counters.list must be created inside folder "spmv-executors/uzp-genex" capturing the counters to measure. See PolyBench C/4.2.1 documentation for more details.
    * For instance: "./macveth\_spmv.sh QLi crashbasis float cold 1th" obtains a performance of approximately 4.0 GFLOPS on the Intel Core 12900K machine used for the tests when fixing the operational frequency at 3.2 GHz. The compilation phase takes approximately 5 minutes.

4. CSR5 executor: the relevant section of the CSR5 artifact used for experimentation is contained in folder spmv-executors/spmv-csr5. In order to automatically launch the experiment:
    * cd spmv-executors
    * ./csr5\_spmv.sh <group> <matrix> <datatype> <cache mode> <execution threads>
        * <group> and <matrix> are a Group name and Matrix name from SuiteSparse.
        * <datatype>: only "double" is supported by CSR5, using double-precision floating-point operations.
        * <cache mode>: either "hot" or "cold". Under cold cache settings, the SpMV kernel is run only once. Under hot cache settings, the kernel is run 100 times without cleaning the cache between repetitions.
        * <execution threads>: either "1th", "2th", or "8th".
    * See important notes below about repeatability, including operational frequency and pinning of threads to cores in the execution machine.
    * The script automatically downloads the required files from SuiteSparse to the /tmp folder of the execution machine, and launches the executor. 
    * The script outputs the obtained performance in GFLOPS. It can be modified to output performance counters instead, by modifying the "spmv-csr5/CSR5\_avx2/Makefile" file to compile with -DPOLYBENCH\_PAPI, instead of -DPOLYBENCH\_GFLOPS. In this case, a papi\_counters.list must be created inside folder "spmv-executors/uzp-genex" capturing the counters to measure. See PolyBench C/4.2.1 documentation for more details.
    * For instance: "./csr5\_spmv.sh QLi crashbasis double cold 1th" obtains a performance of approximately 2.3 GFLOPS on the Intel Core 12900K machine used for the tests when fixing the operational frequency at 3.2 GHz.

5. Vanilla CSR executor: the code is contained in folder spmv-executors/spmv-csr. In order to automatically launch the experiment:
    * cd spmv-executors
    * ./csr\_spmv.sh <group> <matrix> <datatype> <cache mode> <execution threads>
        * <group> and <matrix> are a Group name and Matrix name from SuiteSparse.
        * <datatype>: either "double" or "float" for double and single precision, respectively.
        * <cache mode>: either "hot" or "cold". Under cold cache settings, the SpMV kernel is run only once. Under hot cache settings, the kernel is run 100 times without cleaning the cache between repetitions.
        * <execution threads>: either "1th", "2th", or "8th".
    * See important notes below about repeatability, including operational frequency and pinning of threads to cores in the execution machine.
    * The script automatically downloads the required files from SuiteSparse to the /tmp folder of the execution machine, and launches the executor.
    * The script outputs the obtained performance in GFLOPS. It can be modified to output performance counters instead, by modifying the "spmv-csr/Makefile" file to compile with -DPOLYBENCH\_PAPI, instead of -DPOLYBENCH\_GFLOPS. In this case, a papi\_counters.list must be created inside folder "spmv-executors/uzp-genex" capturing the counters to measure. See PolyBench C/4.2.1 documentation for more details.
    * For instance: "./csr\_spmv.sh QLi crashbasis double cold 1th" obtains a performance of approximately 2.6 GFLOPS on the Intel Core 12900K machine used for the tests when fixing the operational frequency at 3.2 GHz.
