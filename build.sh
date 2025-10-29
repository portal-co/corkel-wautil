#!/usr/bin/env bash
set -euxo pipefail
R=$(dirname $0)
O=${O:-$R/build/$ARCH}
mkdir -p $O
export CFLAGS=${CFLAGS:-}
$R/compile.sh -isystem $R/source/include -c -o $O/setjmp_core.o $R/source/lib/setjmp_core_$ARCH.S
$R/compile.sh -isystem $R/source/include -c -o $O/mman.o $R/source/lib/mman.c
$R/compile.sh -isystem $R/source/include -c -o $O/setjmp.o $R/source/lib/setjmp.c
$R/dlmalloc/build.sh

rm $O/libcorkel.a || echo "Creating Libcorkel"
$AR -rcD $O/libcorkel.a $O/dlmalloc.o $O/setjmp_core.o $O/setjmp.o $O/mman.o
                