#!/usr/bin/env bash
set -euxo pipefail
R=$(dirname $0)/..
O=${O:-$R/../build/$ARCH}
$R/compile.sh -isystem $R/source/include -c -o $O/dlmalloc.o $R/dlmalloc/src/dlmalloc.c
            