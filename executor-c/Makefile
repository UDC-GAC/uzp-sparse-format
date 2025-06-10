##
## Written by Louis-Noel Pouchet <pouchet@colostate.edu>, 2023.
##
##


## Optimization flags for all files except generic executors for unincorporated
## points.
GCC_OPT = -O2 -ftree-vectorize -floop-unroll-and-jam -march=native
## Optimization flags for generic executors for unincorporated points.
GCC_OPT_CSR = -O2 -ftree-vectorize -floop-unroll-and-jam -march=native

## Compilers:
GCC = gcc
GCC_OMP = gcc -fopenmp

### DEBUG:
#GCC_DEBUG_FLAGS = -fopt-info-vec-all -fopt-info-vec -fopt-info-vec-missed
#GCC_OPT_FLAGS_AGGRESSIVE =  -fvect-cost-model=unlimited -fsimd-cost-model=unlimited
#GCC_OPT_FLAGS_AGGRESSIVE =  -fvect-cost-model=unlimited -fsimd-cost-model=unlimited

#GCC_OPT = -Ofast -floop-unroll-and-jam -march=native $(GCC_OPT_FLAGS_AGGRESSIVE)
#GCC = gcc $(GCC_DEBUG_FLAGS)
#GCC = gcc -g -ggdb
### !DEBUG.

## CPP flags.
CPPFLAGS = -I . -DPOLYBENCH_GFLOPS -DGEN_EXECUTOR_SPF_V3
#CPPFLAGS = -I . -DPOLYBENCH_TIME

## Binaries.
PROG_BIN_MV = spf_matvec
PROG_BIN_MM = spf_matmul
PROG_BIN_MV_OMP = spf_matvec_omp
PROG_BIN_MM_OMP = spf_matmul_omp
PROG_BIN_SPF_TUNNER = spf_tunner
PROG_BIN_SPF_TUNNER_OMP = spf_tunner_omp

## Source files.
SRC_FILES =					\
	polybench.c				\
	spf_structure.c				\
	spf_executors.c				\
	spf_executors_uninc.c

## Object files, for every binary, w/o and w/ OpenMP.
OBJ_FILES = $(SRC_FILES:%.c=%.o)
OBJ_FILES_OMP = $(SRC_FILES:%.c=%.openmp.o)
OBJ_FILES_MV = $(OBJ_FILES) spf_matvect.o
OBJ_FILES_MV_OMP = $(OBJ_FILES_OMP) spf_matvect.openmp.o
OBJ_FILES_MM = $(OBJ_FILES) spf_matmult.o
OBJ_FILES_MM_OMP = $(OBJ_FILES_OMP) spf_matmult.openmp.o
OBJ_FILES_SPF_TUNNER = $(OBJ_FILES) spf_tunner.o
OBJ_FILES_SPF_TUNNER_OMP = $(OBJ_FILES_OMP) spf_tunner.openmp.o


## Entry point.
all: $(PROG_BIN_MV) $(PROG_BIN_MM) $(PROG_BIN_MV_OMP) $(PROG_BIN_MM_OMP) $(PROG_BIN_SPF_TUNNER) $(PROG_BIN_SPF_TUNNER_OMP)

tunner: $(PROG_BIN_SPF_TUNNER) $(PROG_BIN_SPF_TUNNER_OMP)

## Default rule to compile source codes w/ OpenMP support.
%.openmp.o: %.c
	$(GCC_OMP) $(GCC_OPT) $(CPPFLAGS) -c $< -o $@

## Default rule to compile source codes.
.c.o:
	$(GCC) $(GCC_OPT) $(CPPFLAGS) -c $< -o $@

## Special rule to compile CSR/COO executor with different optimization flags.
spf_executors_uninc.o: spf_executors_uninc.c
	$(GCC) $(GCC_OPT_CSR) $(CPPFLAGS) -c spf_executors_uninc.c -o spf_executors_uninc.o
spf_executors_uninc.openmp.o: spf_executors_uninc.c
	$(GCC_OMP) $(GCC_OPT_CSR) $(CPPFLAGS) -c spf_executors_uninc.c -o spf_executors_uninc.openmp.o

## General rules.
$(PROG_BIN_MV): $(OBJ_FILES_MV)
	$(GCC) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_MV) -o $(PROG_BIN_MV) -lm

$(PROG_BIN_MM): $(OBJ_FILES_MM)
	$(GCC) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_MM) -o $(PROG_BIN_MM) -lm

$(PROG_BIN_MV_OMP): $(OBJ_FILES_MV_OMP)
	$(GCC_OMP) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_MV_OMP) -o $(PROG_BIN_MV_OMP) -lm

$(PROG_BIN_MM_OMP): $(OBJ_FILES_MM_OMP)
	$(GCC_OMP) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_MM_OMP) -o $(PROG_BIN_MM_OMP) -lm

$(PROG_BIN_SPF_TUNNER): $(OBJ_FILES_SPF_TUNNER)
	$(GCC) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_SPF_TUNNER) -o $(PROG_BIN_SPF_TUNNER) -lm $(LDFLAGS)

$(PROG_BIN_SPF_TUNNER_OMP): $(OBJ_FILES_SPF_TUNNER_OMP)
	$(GCC_OMP) $(GCC_OPT) $(CPPFLAGS) $(OBJ_FILES_SPF_TUNNER_OMP) -o $(PROG_BIN_SPF_TUNNER_OMP) -lm $(LDFLAGS)

## Clean.
clean:
	rm -f $(OBJ_FILES_MM) $(OBJ_FILES_MV) $(OBJ_FILES_MM_OMP) $(OBJ_FILES_MV_OMP) $(OBJ_FILES_SPF_TUNNER) $(OBJ_FILES_SPF_TUNNER_OMP)

distclean:
	rm -f $(PROG_BIN_MM) $(PROG_BIN_MV) $(PROG_BIN_MM_OMP) $(PROG_BIN_MV_OMP) $(PROG_BIN_SPF_TUNNER) $(PROG_BIN_SPF_TUNNER_OMP)

## Test.
test-double-mv: $(PROG_BIN_MV)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matvec "$$i" -stats; done

test-float-mv: $(PROG_BIN_MV)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matvec "$$i" -float -stats; done

test-double-mm: $(PROG_BIN_MM)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matmul "$$i" -stats; done

test-float-mm: $(PROG_BIN_MM)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matmul "$$i" -float -stats; done

test-double-mm-omp: $(PROG_BIN_MM_OMP)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matmul_omp "$$i" -stats; done

test-float-mm-omp: $(PROG_BIN_MM_OMP)
	for i in `ls *.spfdata`; do echo "$$i"; ./spf_matmul_omp "$$i" -float -stats; done
