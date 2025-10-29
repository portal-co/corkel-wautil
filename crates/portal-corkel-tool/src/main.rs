use std::path::PathBuf;

use clap::Parser;
use itertools::Itertools;

fn main() -> std::io::Result<()> {
    let args = Args::parse();
    match args.subcommand {
        Subcommand::GenBuild { src_dir } => {
            const SRCS: &'static [&'static str] = &["mman", "setjmp"];
            let build_cmd = |a: &str, p: &str| {
                format!("$R/compile.sh -isystem $R/source/include -c -o $O/{a}.o $R/{p}/{a}.c")
            };
            std::fs::write(
                src_dir.join("source").join("dlmalloc").join("build.sh"),
                format!(
                    r#"#!/usr/bin/env bash
set -euxo pipefail
R=$(dirname $0)/..
O=${{O:-$R/../build/$ARCH}}
{}
            "#,
                    build_cmd("dlmalloc", "dlmalloc/src")
                ),
            )?;
            std::fs::write(
                src_dir.join("build.sh"),
                format!(
                    r#"#!/usr/bin/env bash
set -euxo pipefail
R=$(dirname $0)
O=${{O:-$R/build/$ARCH}}
mkdir -p $O
export CFLAGS=${{CFLAGS:-}}
$R/compile.sh -isystem $R/source/include -c -o $O/setjmp_core.o $R/source/lib/setjmp_core_$ARCH.S
{}
$R/dlmalloc/build.sh

rm $O/libcorkel.a || echo "Creating Libcorkel"
$AR -rcD $O/libcorkel.a $O/dlmalloc.o $O/setjmp_core.o $O/setjmp.o $O/mman.o
                "#,
                    SRCS.iter().map(|a| build_cmd(a, "source/lib")).join("\n")
                ),
            )?;
            std::fs::write(
                src_dir.join("CMakeLists.txt"),
                format!(
                    r#"
project(corkel)
add_library(corkel STATIC {} source/dlmalloc/src/dlmalloc.c source/lib/setjmp_core_${{CMAKE_SYSTEM_PROCESSOR}}.S)
target_include_directories(corkel PUBLIC ${{CMAKE_CURRENT_SOURCE_DIR}}/source/include)
            "#,
                    SRCS.iter().map(|a| format!("source/lib/{a}.c")).join(" ")
                ),
            )?;
        }
    }
    Ok(())
}
#[derive(Parser, Debug)]
#[command(version, about)]
pub struct Args {
    #[command(subcommand)]
    pub subcommand: Subcommand,
}
#[derive(clap::Subcommand, Debug, Clone)]
pub enum Subcommand {
    GenBuild { src_dir: PathBuf },
}
